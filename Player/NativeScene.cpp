#include "stdafx.h"

#include "NativeScene.h"


NativeScene::NativeScene(QObject *parent, QStatusBar *statusBar) :
	SceneBase(parent, statusBar)
{
}


NativeScene::~NativeScene()
{
}


void NativeScene::loadContent()
{
	// Update StatusBar
	m_pStatusBar->showMessage(m_pStatusBar->currentMessage() + " - running in Nativemode");

	// TODO: Load your own content here

	if (!m_pMetaioSDK->setTrackingConfiguration(projectPath + "\\trackingconfigurations\\TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	metaio::IGeometry* geometry = m_pMetaioSDK->createGeometry(projectPath + "\\augmentations\\metaioman.md2");
	if (geometry)
		geometry->setScale(metaio::Vector3d(1.5f, 1.5f, 1.5f));
	else
		qCritical("Failed to load MD2 model file");
}


void NativeScene::performRendering()
{
	m_pMetaioSDK->render();
}