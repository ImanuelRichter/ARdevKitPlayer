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
	if(QFile::exists("currentProject.zip"))
	{
		QFile::remove("currentProject.zip");
	}
	QFile project("currentProject.zip");
	while(socket->bytesAvailable() == 0)
	{	
		if(socket->waitForReadyRead(30000))
		{	
			break;
		}
	}
	QByteArray msgSizeBytes(8,0);
	quint64 msgSize = 0;
	msgSizeBytes = socket->read(8);
	for(int i = 0; i < msgSizeBytes.length(); ++i)
	{
		msgSizeBytes += (quint8)msgSizeBytes.at(i) << (8*i);
	}
	if(msgSize > 0)
	{
		QByteArray buffer(1024*8, 0);
		quint64 alreadyRead = 0;
		if(!socket->waitForReadyRead(50000))
		{
			qDebug() << "something went wrong!!";
		}
		if(!project.open(QIODevice::OpenModeFlag::WriteOnly))
		{
			return;
		}
		while(alreadyRead < msgSize)
		{
			quint64 testbytes = socket->bytesAvailable();
			alreadyRead += socket->read(buffer.data(), 1024*8);
			project.write(buffer, 1024*8);
		}
		project.close();
	}
	socket->disconnectFromHost();
	socket->close();
}