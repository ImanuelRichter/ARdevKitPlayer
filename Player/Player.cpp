#include "stdafx.h"

#include "Player.h"
#include "ConnectionController.h"

#include <QtOpenGL/QGLWidget>

#ifdef METAIO_SDK_NATIVE
	#include "NativeScene.h"
#else
	#include "ARELScene.h"
#endif


Player::Player(QWidget *parent) :
	QMainWindow(parent),
	m_pScene(0)
{
	// Start ConnectionController
	ConnectionController * controller = new ConnectionController(0);
	connect(controller, SIGNAL(newProject()), this, SLOT(reload()));

	ui.setupUi(this);

#ifdef METAIO_SDK_NATIVE
	m_pScene = new NativeScene(ui.graphicsView, ui.statusBar);
#else
	m_pScene = new ARELScene(ui.graphicsView, ui.statusBar);
#endif

	QGLWidget* glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers), ui.graphicsView);
	ui.graphicsView->setScene(m_pScene);
	ui.graphicsView->setViewport(glWidget);

#ifndef METAIO_SDK_TEMPLATE_NATIVE
	// If you want to disable the web view's context menu for an AREL scene, enable this line
	ui.graphicsView->setContextMenuPolicy(Qt::NoContextMenu);
#endif
}

void Player::setConfig(std::string _projectPath, int _mode, std::string _testFilePath, int _fps)
{
	m_pScene->setConfig(_projectPath, _mode, _testFilePath, _fps);
}

Player::~Player()
{
	// Do not delete m_pScene, its parent is ui.graphicsView, so it will be destroyed automatically
}

void Player::reload()
{
	ui.setupUi(this);

#ifdef METAIO_SDK_NATIVE
	m_pScene = new NativeScene(ui.graphicsView, ui.statusBar);
#else
	m_pScene = new ARELScene(ui.graphicsView, ui.statusBar);
#endif

	QGLWidget* glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers), ui.graphicsView);
	ui.graphicsView->setScene(m_pScene);
	ui.graphicsView->setViewport(glWidget);

#ifndef METAIO_SDK_TEMPLATE_NATIVE
	// If you want to disable the web view's context menu for an AREL scene, enable this line
	ui.graphicsView->setContextMenuPolicy(Qt::NoContextMenu);
#endif
}
