#ifndef SCENEBASE_H
#define SCENEBASE_H

#include <fstream>

#include <QtGui/QGraphicsScene>
#include <QStatusBar>

#include <metaioSDK/IMetaioSDKCallback.h>
#include <metaioSDK/IMetaioSDKWin32.h>

#define IMAGE 0
#define VIDEO 1
#define CAMERA 2

namespace metaio
{
	class GestureHandler;
}

/// Implementation of non-AREL scene
class SceneBase : public QGraphicsScene, public metaio::IMetaioSDKCallback
{
	typedef QGraphicsScene super;

	Q_OBJECT

public:
	virtual ~SceneBase();
	void setConfig(std::string _projectPath, int mode, std::string _testFilePath, int _fps);

protected:
	SceneBase(QObject *parent = 0, QStatusBar *statusBar = 0);
	
	/// StatusBat showing version and mode
	QStatusBar*					m_pStatusBar;

	/// true if the scene has been initialized
	bool						m_initialized;

	/// Gesture handler for touch events
	metaio::GestureHandler*		m_pGestureHandler;

	/// Metaio SDK instance
	metaio::IMetaioSDKWin32*	m_pMetaioSDK;

	/// Current viewport width
	unsigned int				m_viewportWidth;

	/// Current viewport height
	unsigned int				m_viewportHeight;

	/// Path to the current projekt
	std::string					projectPath;

	/// Path to the testfile
	std::string					testFilePath;

	/// The current mode
	int							mode;

	/// Sets up the updateintervall
	int							fps;

	int							frameCounter;

	std::string					framePath;

	/**
	 * Called directly after Metaio SDK was created and its renderer initialized
	 */
	virtual void afterMetaioSDKInitialized() {};

	/**
	* Resizes webView
	*/
	virtual void resize() {};

	/**
	 * QGraphicsScene inherited drawBackground function
	 *
	 * \param painter QPainter instance
	 * \param rect Exposed rectangle
	 */
	virtual void drawBackground(QPainter* painter, const QRectF & rect) override;

	/**
	 * Load our content, e.g. tracking configuration and 3D model
	 */
	virtual void loadContent() = 0;

	/**
	 * Handles the Metaio SDK ready event
	 */
	virtual void onSDKReady() override;

	/**
	 * QGraphicsScene inherited method for handling mouse move event
	 *
	 * \param mouseEvent QGraphicsSceneMouseEvent mouse event
	 */
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

	/**
	 * QGraphicsScene inherited method for handling mouse press event
	 *
	 * \param mouseEvent the QGraphicsSceneMouseEvent mouse event
	 */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

	/**
	 * QGraphicsScene inherited method for handling mouse release event
	 *
	 * \param mouseEvent the QGraphicsSceneMouseEvent mouse event
	 */
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

	/**
	 * Perform the rendering. This will be different in native vs. AREL scene
	 */
	virtual void performRendering() = 0;
};

#endif