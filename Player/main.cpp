#include "stdafx.h"
#include "Player.h"

#include <QtGui/QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Player p;

	std::string path;
	int i = 1;
	while (i < argc)
	{
		if (i > 1)
			path += " ";
		path += std::string(argv[i]);
		i++;
	}

	std::string out;
	QMessageBox msgBox;
	msgBox.setMinimumWidth(500);
	msgBox.setText("Following path is going to be set for configuration:");
#ifdef METAIO_SDK_NATIVE
	out = "Using Native:\n" + path;
#else
	out = "Using Arel:\n" + path;
#endif
	msgBox.setInformativeText(out.c_str());
	msgBox.exec();

	p.setProjectPath(path);
	p.show();
	return a.exec();
}
