#include "stdafx.h"

#include "ARELScene.h"

#include <metaioSDK/IARELInterpreter.h>
#include <QMessageBox>
#include <QDebug>


ARELScene::ARELScene(QObject *parent, QStatusBar *statusBar) :
	SceneBase(parent, statusBar),
	m_pArelInterpreter(0),
	m_pWebView(0)
{
	// Create a webview	and connect the load finished event
	m_pWebView = new QGraphicsWebView();
	QObject::connect(m_pWebView, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
	m_pWebView->hide();
	addItem(m_pWebView);
	m_pWebView->resize(m_viewportWidth, m_viewportHeight);

	// Create the AREL interpreter
	m_pArelInterpreter = metaio::CreateARELInterpreterQT(this, m_pWebView);
}


ARELScene::~ARELScene()
{
	delete m_pArelInterpreter;

	removeItem(m_pWebView);
	delete m_pWebView;
}


void ARELScene::afterMetaioSDKInitialized()
{
	// After Metaio SDK instance is created and initialized, we need to initialize the AREL interpreter

	// As opposed to NativeScene, we don't need to register the callback on the SDK instance, but
	// should instead do it on the AREL interpreter. It will trigger the onSDKReady event, too.
	m_pMetaioSDK->registerCallback(0);

	// Update StatusBar
	m_pStatusBar->showMessage(m_pStatusBar->currentMessage() + " - running in ARELmode");

	m_pArelInterpreter->initialize(m_pMetaioSDK, m_pGestureHandler);
	m_pArelInterpreter->registerCallback(this);
}

void ARELScene::resize()
{
	m_pWebView->resize(m_viewportWidth - 10, m_viewportHeight - 10);
}

void ARELScene::loadContent()
{
	std::string configFilePath = projectPath + "\\arelConfig.xml";
	qDebug(("Trying to load: " + configFilePath).c_str());
	m_pArelInterpreter->loadARELFile(configFilePath);
}


void ARELScene::loadFinished(bool ok)
{
	if (ok)
	{
		m_pArelInterpreter->loadFinished();

		// Show the web view after content is loaded and splash screen is finished
		m_pWebView->show();
	}
	else
		qCritical("loadFinished event: An error occurred while loading the HTML page");
}


void ARELScene::onSDKReady()
{
	loadContent();
}


void ARELScene::performRendering()
{
	m_pArelInterpreter->update();
}