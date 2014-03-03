#include "StdAfx.h"
#include "ConnectionController.h"

/// <summary>
/// Starts the requiered sockets and bides some of them to
/// the ports, on which they listen on.
/// </summary>
/// <param name="parent">The parent.</param>
/// <returns></returns>
ConnectionController::ConnectionController(QObject *parent)
	: QObject(parent)
{
	udpSocket = new QUdpSocket(this);
	tcpServer = new QTcpServer(this);
	udpSocket->bind(QHostAddress::Any, 12345);
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(incomingBroadcast()));
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(handleTcpRequest()));
	tcpServer->listen(QHostAddress::Any, 12345);
	moveToThread(&t);
    t.start();
}

/// <summary>
/// Finalizes an instance of the <see cref="ConnectionController"/> class.
/// </summary>
ConnectionController::~ConnectionController()
{
	udpSocket->close();
	tcpServer->close();
	t.quit();
    t.wait();
}

/// <summary>
/// Reacts to a incoming UDP broadcast. 
/// </summary>
void ConnectionController::incomingBroadcast()
{
	QByteArray sendmsg = QByteArray("OK:12345");
	QByteArray buffer;
	buffer.resize(udpSocket->pendingDatagramSize());

	QHostAddress sender;
	quint16 senderPort;
	udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

	udpSocket->writeDatagram(sendmsg, sender, senderPort); 
}

/// <summary>
/// Handles a TCP request by analysing the sent command and uses the 
/// dedicated method for either a project send or a debug request.
/// It sends a  positive response on success and closes the sockets afterwards. 
/// </summary>
void ConnectionController::handleTcpRequest()
{
	//generic handle method, which uses different methods 
	QTcpSocket * socket = tcpServer->nextPendingConnection();	
	if(!socket->waitForReadyRead(30000))
	{	
		qDebug() <<"Client does not respond anymore";
		return;
	}
	QByteArray cmdBuf(10, 0);
	qint64 lineLength = socket->readLine(cmdBuf.data(), cmdBuf.length());
    if (lineLength == -1) {
        qDebug() << "an Error occured try to read the command";
    }
	if(cmdBuf.contains("project"))
	{
		this->handleProjectRequests(socket);
	}
	if(cmdBuf.contains("debug"))
	{
		this->handleDebugRequests(socket);
		
	}
	if(socket->state() == QAbstractSocket::ConnectedState)
	{
		socket->write("OK");
		socket->flush();
		socket->disconnectFromHost();
	}	
	socket->close();
}

/// <summary>
/// Handles the project requests, by saving the data, unzipping the package and
/// restarting the Player in order to show the project
/// </summary>
/// <param name="socket">The remote socket, which sends the project</param>
void ConnectionController::handleProjectRequests(QTcpSocket * socket)
{
	//check if file to write to exist already
	if(QFile::exists(".\\currentProject.zip"))
	{
		QFile::remove(".\\currentProject.zip");
	}
	QFile project(".\\currentProject.zip");
	QByteArray msgSizeBytes(8,0);
	quint64 msgSize = 0;
	//wait for remote socket to write on stream
	if(socket->bytesAvailable() == 0)
	{
		if(!socket->waitForReadyRead(30000))
		{	
			qDebug() <<"Request was not completly sent";
			return;
		}	
	}
	//read all bytes for project length
	for(int i = 0; msgSize < 8; ++i)
	{
		msgSize = socket->read(msgSizeBytes.data() + msgSize, 8 - msgSize);
	}
	msgSize = 0;
	//calc Project length
	for(int i = 0; i < msgSizeBytes.size(); ++i)
	{
		msgSize += (quint8)msgSizeBytes.at(i) << (8*i);
	}
	if(msgSize > 0)
	{
		QByteArray buffer(1024*8, 0);
		quint64 alreadyRead = 0;
		quint64 currentlyRead = 0;

		if(!project.open(QIODevice::WriteOnly))
		{
			qDebug() << "The requested File could not be accessed.";
			return;
		}
		//try to read from stream and write to file
		while(alreadyRead < msgSize)
		{
			if(socket->bytesAvailable() == 0)
			{
				if(!socket->waitForReadyRead(30000))
				{	
					qDebug() <<"Project was not send succesfully";
					return;
				}	
			}
			currentlyRead = socket->read(buffer.data(), 1024*8);
			project.write(buffer, currentlyRead);
			alreadyRead += currentlyRead;
		}
		project.close();
		if(QDir("currentProject").exists())
		{
			QDir().remove("currentProject");
		}
		//unzip Project and restart Player
		JlCompress::extractDir("currentProject.zip", "currentProject");
		emit newProject();
	}
}

/// <summary>
/// Handles the debug requests, by writing the buffer of stdout to 
/// the networking socket, until a message is received.
/// </summary>
/// <param name="socket">The socket, which receives the debuginformation</param>
void ConnectionController::handleDebugRequests(QTcpSocket * socket)
{
	//initialise Buffer for stdout
	char bigOutBuf[8192];
	memset(bigOutBuf, 0, 8192);

	//set as stdoutBuffer
	fflush(stdout);
	setvbuf(stdout, bigOutBuf, _IOFBF, 8192);
	int i = 0;
	while(socket->bytesAvailable() < 2)
	{
		for(int i = 0; i < 8192; ++i)
		{
			if(bigOutBuf[i]!=0)
			{
				socket->write(&bigOutBuf[i], 1);
				socket->waitForBytesWritten();
				bigOutBuf[i] = 0;
			}
		}
		if(socket->waitForDisconnected(1000))
		{
			qDebug() << "disconnected from Host";
			setbuf(stdout, NULL);
			return;
		}
	}
	//wait for response
	QByteArray result(socket->readAll());
	if(result.contains("OK"))
	{
		qDebug() << "Debugcall successfully finished";
	}
	else
	{
		qDebug() << "Debugcall not succesfully finished";
	}
	//restore normal stdout buffer
	setbuf(stdout, NULL);
}