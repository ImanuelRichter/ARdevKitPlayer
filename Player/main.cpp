#include "stdafx.h"
#include "Player.h"

#include <fstream>

#include <QtGui/QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
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
		while (i < argc && ((std::string(argv[i])).length() > 2 && (argv[i][0] != '-' || argv[i][1] == ' ')));
	}
	else
		projectPath = "currentProject";
	qDebug(("Project to load: " + projectPath).c_str());
	
	std::ifstream projectPathIsValid(projectPath);
	
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
		while (i < argc && ((std::string(argv[i])).length() > 2 && (argv[i][0] != '-' || argv[i][1] == ' ')));
	}
	else
	{
		switch (mode)
		{
			case (IMAGE) :
				testFilePath = "..\\src\\test\\testImage.png";
				break;
			case (VIDEO) :
				testFilePath = "..\\src\\test\\testVideo.mp4";
			break;
		}
	}
	qDebug(("Testfile: " + testFilePath).c_str());

	std::ifstream testFilePathIsValid(testFilePath);

	// Start app
	QApplication a(argc, argv);
	Player p;
	if (width == 0 && height == 0)
		p.showFullScreen();
	else
		p.resize(width, height);

	p.setProjectPath(projectPath);
	p.setMode(mode);
	p.setTestFilePath(testFilePath);
	p.show();
	return a.exec();
}
