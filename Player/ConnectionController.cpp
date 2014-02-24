#include "StdAfx.h"
#include "ConnectionController.h"

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

ConnectionController::~ConnectionController()
{
	udpSocket->close();
	tcpServer->close();
	t.quit();
    t.wait();
}

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

void ConnectionController::handleTcpRequest()
{
	QTcpSocket * socket = tcpServer->nextPendingConnection();	
	if(!socket->waitForReadyRead(30000))
	{	
		qDebug() <<"Client meldet sich nichtmehr";
		return;
	}
	QByteArray cmdBuf(10, 0);
	qint64 lineLength = socket->readLine(cmdBuf.data(), cmdBuf.length());
    if (lineLength == -1) {
        qDebug() << "an Error occured try to read the command";
    }
	if(cmdBuf.contains("project"))
	{
		qDebug() << socket->bytesAvailable();
		this->handleProjectRequests(socket);
		socket->write("OK");
	}
	if(cmdBuf.contains("debug"))
	{
		this->handleDebugRequests(socket);
		socket->write("OK");
	}
	socket->flush();
	socket->disconnectFromHost();
	socket->close();
}

void ConnectionController::handleProjectRequests(QTcpSocket * socket)
{
	if(QFile::exists(".\\currentProject.zip"))
	{
		QFile::remove(".\\currentProject.zip");
	}
	QFile project(".\\currentProject.zip");
	QByteArray msgSizeBytes(8,0);
	quint64 msgSize = 0;
	if(socket->bytesAvailable() == 0)
	{
		if(!socket->waitForReadyRead(30000))
		{	
			qDebug() <<"Request was not completly sent";
			return;
		}	

	}
	for(int i = 0; msgSize < 8; ++i)
	{
		msgSize = socket->read(msgSizeBytes.data() + msgSize, 8 - msgSize);
	}
	msgSize = 0;
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
			qDebug() << "The requested File could not be accesed.";
			return;
		}
		while(alreadyRead < msgSize)
		{
			if(socket->bytesAvailable() == 0)
			{
				if(!socket->waitForReadyRead(30000))
				{	
					qDebug() <<"Project wurde nicht vollständig gesendet";
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
		JlCompress::extractDir("currentProject.zip", "currentProject");
	}
}

void ConnectionController::handleDebugRequests(QTcpSocket * socket)
{
	freopen("debug_output_file", "w", stdout);
	QFile f("debug_output_file");
	f.open(QIODevice::ReadOnly);
	while(socket->bytesAvailable() < 2)
	{
		if(f.waitForReadyRead(10000))
		{
			socket->write(f.readLine());
			socket->waitForBytesWritten();
		}
	}
	QByteArray result(socket->readAll());
	if(!result.contains("OK"))
	{
		qDebug() << "failure on Debugcall";
	}
}