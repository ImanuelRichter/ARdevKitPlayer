#ifndef TEMPLATEWINDOW_H
#define TEMPLATEWINDOW_H

#include "ui_Player.h"
#include "SceneBase.h"

#include <QtGui/QMainWindow>


class Player : public QMainWindow
{
	typedef QMainWindow super;

	Q_OBJECT

public:
	Player(QWidget *parent = 0);
	~Player();
	void setProjectPath(std::string path);

private:
	Ui::TemplateWindowClass		ui;

	SceneBase*					m_pScene;
};

#endif // TEMPLATEWINDOW_H
