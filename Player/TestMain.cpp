#include "stdafx.h"
#include "Player.h"

#include "shlwapi.h"

#include <QtGui/QApplication>
#include <iostream>
#include <stdio.h>

/// <summary>
/// Implements a new message handler for the qDebug() call.
/// </summary>
/// <param name="type">The type of the message</param>
/// <param name="msg">The MSG, as string</param>
void myMessageOutput(QtMsgType type, const char * msg)
{
	switch(type)
	{
		case QtDebugMsg:
			fprintf(stdout,"Debug: %s\n", msg);
			break;
		
		case QtWarningMsg:
			fprintf(stdout,"Warning: %s\n", msg);
			break;

		case QtCriticalMsg:
			fprintf(stdout,"Critical: %s\n", msg);
			break;

		case QtFatalMsg:
			fprintf(stdout,"Fatal: %s\n", msg);
			break;
	}
}

/// <summary>
/// init.
/// </summary>
/// <param name="argc">The argc.</param>
/// <param name="argv">The argv, containing Resolution, projectPath,
///		execution mode [IMAGE/VIDEO/CAMERA], testFilePath, fps</param>
/// <returns>the exit code of the application</returns>
int init(int argc, char *argv[])
{
	// Set qDebug output to std
	qInstallMsgHandler(myMessageOutput);

	// Get resolution
	std::string res = "Resolution: ";
	int i = 1;
	int width = 0; 
	if (i < argc)
	{
		std::string tmp = argv[i] + 1;
		res += tmp + "x";
		width = atoi(tmp.c_str());
		i++;
	}
	int height = 0;
	if (i < argc)
	{
		std::string tmp = argv[i] + 1;
		res += tmp;
		height = atoi(tmp.c_str());
		i++;
	}
	if (width == 0 && height == 0)
		qDebug("Fullscreen");
	else
		qDebug(res.c_str());


	// Get projectPath
	std::string projectPath;
	int n = i;
	if (i < argc)
	{
		do {
			if (i > n)
				projectPath += " ";
			projectPath += std::string(argv[i] + 1);
			i++;
		}
		while (i < argc && !((std::string(argv[i])).length() >= 2 && (argv[i][0] == '-')));
	}
	else
		projectPath = "currentProject";
		qDebug(("Trying to open project at: " + projectPath).c_str());
	
	// Get mode
	int mode = CAMERA;
	if (i < argc)
	{
		mode = argv[i][1] - '0';
		i++;
	}
	switch (mode)
	{
		case (IMAGE):
			qDebug("Mode: IMAGE");
			break;
		case (VIDEO):
			qDebug("Mode: VIDEO");
			break;
		case (CAMERA):
			qDebug("Mode: CAMERA");
			break;
	}

	// Get testFilePath
	std::string testFilePath = "";
	n = i;
	if (i < argc)
	{
		do {
			if (i > n)
				testFilePath += " ";
			if (i == n)
				testFilePath += std::string(argv[i] + 1);
			else
				testFilePath += std::string(argv[i]);
			i++;
		}
		while (i < argc && !((std::string(argv[i])).length() >= 2 && (argv[i][0] == '-')));
	}
	std::ifstream testFilePathIsValid(testFilePath);
	if (testFilePathIsValid)
		qDebug(("Loading test file from valid path: " + testFilePath).c_str());
	else if (testFilePath == "")
		qDebug("No test file defined");
	else
		qDebug(("Invalid test file path: " + testFilePath).c_str());

	// Get fps
	int fps = 25;
	if (i < argc)
	{
		fps = atoi(argv[i] + 1);
		i++;
	}
	char fpsOut[3];
	std::string suffix = std::string(itoa(fps, fpsOut, 10)) + " fps";
	qDebug(("Starting with: " + suffix).c_str());

	// Start app
	QApplication a(argc, argv);
	Player p;
	if (width == 0 && height == 0)
		p.showFullScreen();
	else
		p.resize(width, height);

	// Pass configurations
	p.setConfig(projectPath, mode, testFilePath, fps);
	p.show();

	int exitcode =  a.exec();
	
	p.m_pScene->~SceneBase();
	p.deleteLater();

	return exitcode;
}