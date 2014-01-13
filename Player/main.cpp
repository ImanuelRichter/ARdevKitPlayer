#include "stdafx.h"
#include "Player.h"

#include <QtGui/QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Player p;

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
		projectPath = "..\\res";

	std::string testFilePath;
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
		testFilePath = "..\\res\\testimage.png";

	std::string msg;
	QMessageBox msgBox;
	msgBox.setMinimumWidth(500);
	msgBox.setText("Configuration:");
	msg = "ProjectPath:\n" + projectPath + "\n\n";
	msg += "TestFilePath:\n" + testFilePath + "\n";
	msgBox.setInformativeText(msg.c_str());
	msgBox.exec();

	p.setProjectPath(projectPath);
	p.setTestFilePath(testFilePath);
	p.show();
	return a.exec();
}
