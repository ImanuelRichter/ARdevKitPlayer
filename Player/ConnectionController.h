#ifndef CONNECTIONCONTROLLER_H
#define CONNECTIONCONTROLLER_H

#include <iostream>
#include <sstream>
#include <QObject>
#include <qthread.h>
#include <qudpsocket.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qfile.h>
#include <qiodevice.h>
#include <stdio.h>
#include <quazip.h>
#include <qdir.h>
#include "JlCompress.h"

/// <summary>
/// this class offers methods for listening to the local network
/// in order to accept incoming Files, or send DebugInformation,
/// which are redirected from stdout.
/// </summary>
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
	void handleProjectRequests(QTcpSocket * socket);
	void handleDebugRequests(QTcpSocket * socket);	
};

#endif // CONNECTIONCONTROLLER_H
