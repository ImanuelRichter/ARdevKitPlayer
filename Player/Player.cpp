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
	ConnectionController *controller = new ConnectionController(0);
	connect(controller, SIGNAL(newProject()), this, SLOT(reload()));

	ui.setupUi(this);
	connect(ui.menu_file_close, SIGNAL(triggered()), this, SLOT(close()));
	this->
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

/// <summary>
/// Sets the configuration passed to the player.
/// </summary>
/// <param name="_projectPath">The _project path.</param>
/// <param name="_mode">The _mode.</param>
/// <param name="_testFilePath">The _test file path.</param>
/// <param name="_fps">The _FPS.</param>
void Player::setConfig(std::string _projectPath, int _mode, std::string _testFilePath, int _fps)
{
	m_pScene->setConfig(_projectPath, _mode, _testFilePath, _fps);
}

Player::~Player()
{
	ui.graphicsView->~QGraphicsView();
	// Do not delete m_pScene, its parent is ui.graphicsView, so it will be destroyed automatically
}

void Player::reload()
{
	std::string projectPath = m_pScene->getProjectPath();
	std::string testFilePath = m_pScene->getTestFilePath();
	int mode = m_pScene->getMode();
	int fps = m_pScene->getFps();
	m_pScene->~SceneBase();

#ifdef METAIO_SDK_NATIVE
	m_pScene = new NativeScene(ui.graphicsView, ui.statusBar);
#else
	m_pScene = new ARELScene(ui.graphicsView, ui.statusBar);
#endif

	ui.graphicsView->setScene(m_pScene);

#ifndef METAIO_SDK_TEMPLATE_NATIVE
	// If you want to disable the web view's context menu for an AREL scene, enable this line
	ui.graphicsView->setContextMenuPolicy(Qt::NoContextMenu);
#endif

	setConfig(projectPath, mode, testFilePath, fps);
}

void Player::reload(std::string _projectPath, int _mode, std::string _testFilePath, int _fps)
{
	m_pScene->~SceneBase();

#ifdef METAIO_SDK_NATIVE
	m_pScene = new NativeScene(ui.graphicsView, ui.statusBar);
#else
	m_pScene = new ARELScene(ui.graphicsView, ui.statusBar);
#endif

	ui.graphicsView->setScene(m_pScene);

#ifndef METAIO_SDK_TEMPLATE_NATIVE
	// If you want to disable the web view's context menu for an AREL scene, enable this line
	ui.graphicsView->setContextMenuPolicy(Qt::NoContextMenu);
#endif
	setConfig(_projectPath, _mode, _testFilePath, _fps);
}