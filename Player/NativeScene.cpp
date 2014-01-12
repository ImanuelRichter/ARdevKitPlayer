#include "stdafx.h"

#include "NativeScene.h"


NativeScene::NativeScene(QObject *parent) :
	SceneBase(parent)
{
}


NativeScene::~NativeScene()
{
}


void NativeScene::loadContent()
{
	// TODO: Load your own content here

	if (!m_pMetaioSDK->setTrackingConfiguration(projectPath + "/trackingconfigurations/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	metaio::IGeometry* geometry = m_pMetaioSDK->createGeometry(projectPath + "/augmentations/metaioman.md2");
	if (geometry)
		geometry->setScale(metaio::Vector3d(1.5f, 1.5f, 1.5f));
	else
		qCritical("Failed to load MD2 model file");
}


void NativeScene::performRendering()
{
	m_pMetaioSDK->render();
}