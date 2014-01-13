#ifndef TEMPLATEWINDOW_H
#define TEMPLATEWINDOW_H

#include "ui_Player.h"
#include "SceneBase.h"

#include <QtGui/QMainWindow>

// TODO: Decide whether you want to use the SDK via native code (leave the following line) or want
//       to use AREL (our cross-platform JavaScript bridge; code can even be exported from Metaio
//       Creator in case you're using Creator)
//#define METAIO_SDK_NATIVE


class Player : public QMainWindow
{
	typedef QMainWindow super;

	Q_OBJECT

public:
	Player(QWidget *parent = 0);
	~Player();
	void setProjectPath(std::string path);
	void setTestFilePath(std::string path);

private:
	Ui::TemplateWindowClass		ui;

	SceneBase*					m_pScene;
};

#endif // TEMPLATEWINDOW_H
