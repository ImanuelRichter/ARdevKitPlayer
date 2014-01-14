#include "stdafx.h"
#include "Player.h"

#include <fstream>

#include <QtGui/QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
	// Get projectPath
	std::string projectPath;
	int i = 1;
	while (i < argc && ((std::string(argv[i])).length() > 2 && (argv[i][0] != '-' || argv[i][1] == ' ')))
	{
		if (i > 1)
			projectPath += " ";
		projectPath += std::string(argv[i]);
		i++;
	}
	if (projectPath == "")
		projectPath = "..\\src\\project";
	
	std::ifstream projectPathIsValid(projectPath);
	
	// Get mode
	int mode = CAMERA;
	if (i < argc)
		mode = argv[i][1] - '0';

	// Get testFilePath
	std::string testFilePath = "";
	i++;
	int n = i;
	while (i < argc)
	{
		if (i > n)
			testFilePath += " ";
		if (i == n)
			testFilePath += std::string(argv[i] + 1);
		else
			testFilePath += std::string(argv[i]);
		i++;
	}
	
	if (testFilePath == "")
		switch (mode)
		{
			case (IMAGE) :
				testFilePath = "..\\src\\test\\testImage.png";
				break;
			case (VIDEO) :
				testFilePath = "..\\src\\test\\testVideo.mp4";
			break;
		}

	std::ifstream testFilePathIsValid(testFilePath);

	// Start app
	QApplication a(argc, argv);
	Player p;

	std::string msg = "ProjectPath:\n" + projectPath + "\n\n";
	QMessageBox msgBox;
	msgBox.setMinimumWidth(500);
	msgBox.setText("Configuration:");
	switch (mode)
	{
		case (IMAGE):
			if (testFilePathIsValid)
				msg += "ImageFilePath (valid):\n";
			else
				msg += "ImageFilePath (invalid):\n";
			break;
		case (VIDEO):
			if (testFilePathIsValid)
				msg += "VideoFilePath (valid):\n";
			else
				msg += "VideoFilePath (invalid):\n";
			break;
		case (CAMERA):
			msg += "Using camera\n";
			break;
	}
	msg += testFilePath + "\n";
	msgBox.setInformativeText(msg.c_str());
	msgBox.exec();

	p.setProjectPath(projectPath);
	p.setMode(mode);
	p.setTestFilePath(testFilePath);
	p.show();
	return a.exec();
}
