#include "stdafx.h"

#include "Player.h"

#include <QtOpenGL/QGLWidget>


// TODO: Decide whether you want to use the SDK via native code (leave the following line) or want
//       to use AREL (our cross-platform JavaScript bridge; code can even be exported from Metaio
//       Creator in case you're using Creator)
//#define METAIO_SDK_NATIVE


#ifdef METAIO_SDK_NATIVE
	#include "NativeScene.h"
#else
	#include "ARELScene.h"
#endif


Player::Player(QWidget *parent) :
	QMainWindow(parent),
	m_pScene(0)
{
	ui.setupUi(this);

#ifdef METAIO_SDK_NATIVE
	m_pScene = new NativeScene(ui.graphicsView);
#else
	m_pScene = new ARELScene(ui.graphicsView);
#endif

	QGLWidget* glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers), ui.graphicsView);
	ui.graphicsView->setScene(m_pScene);
	ui.graphicsView->setViewport(glWidget);

#ifndef METAIO_SDK_TEMPLATE_NATIVE
	// If you want to disable the web view's context menu for an AREL scene, enable this line
	// ui.graphicsView->setContextMenuPolicy(Qt::NoContextMenu);
#endif
}


Player::~Player()
{
	// Do not delete m_pScene, its parent is ui.graphicsView, so it will be destroyed automatically
}

void Player::setProjectPath(std::string path)
{
	m_pScene->setProjectPath(path);
}
