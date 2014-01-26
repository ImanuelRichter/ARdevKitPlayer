#ifndef ARELSCENE_H
#define ARELSCENE_H

#include "SceneBase.h"

#include <QtWebKit/QGraphicsWebView>

#include <metaioSDK/IARELInterpreterCallback.h>


namespace metaio
{
	class IARELInterpreter;
}


/// Implementation of AREL scene
class ARELScene : public SceneBase, public metaio::IARELInterpreterCallback
{
	typedef SceneBase super;

	Q_OBJECT

public:
	ARELScene(QObject *parent = 0, QStatusBar *statusBar = 0);
	virtual ~ARELScene();

protected slots:
	/**
	 * Callback that's triggered when the web page was loaded in the web view
	 *
	 * \param ok Whether an error occurred while loading the web page
	 */
	void loadFinished(bool ok);

private:
	/// AREL interpreter
	metaio::IARELInterpreter*	m_pArelInterpreter;

	/// The WebView for HTML pages and javascript handling, needed for AREL
	QGraphicsWebView*			m_pWebView;


	virtual void afterMetaioSDKInitialized() override;
	
	virtual void resize() override;

	virtual void loadContent() override;

	virtual void onSDKReady() override;

	virtual void performRendering() override;
};

#endif