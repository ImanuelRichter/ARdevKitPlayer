#ifndef CONNECTIONCONTROLLER_H
#define CONNECTIONCONTROLLER_H

#include <QObject>
#include <qthread.h>
#include <qudpsocket.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qfile.h>
#include <qiodevice.h>

class ConnectionController : public QObject
{
	Q_OBJECT

public:
	ConnectionController(QObject *parent);
	~ConnectionController();

public slots:
	void incomingBroadcast();
	void handleTcpRequest();

signals:
	void newProject();

private:
	QThread t;
	QUdpSocket * udpSocket;
	QTcpServer  * tcpServer;
	
};

#endif // CONNECTIONCONTROLLER_H
