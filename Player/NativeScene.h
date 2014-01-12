#ifndef NATIVESCENE_H
#define NATIVESCENE_H

#include "SceneBase.h"


/// Implementation of non-AREL scene
class NativeScene : public SceneBase, public metaio::IMetaioSDKCallback
{
	typedef SceneBase super;

	Q_OBJECT

public:
	NativeScene(QObject *parent = 0);
	virtual ~NativeScene();

private:
	virtual void loadContent() override;

	virtual void performRendering() override;
};

#endif