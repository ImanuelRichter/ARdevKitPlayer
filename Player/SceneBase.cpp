#include "stdafx.h"
#include "SceneBase.h"

#include <QtGui/QPainter>
#include <QtOpenGL/QtOpenGL>

#include <GL/gl.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#include <metaioSDK/IMetaioSDKWin32.h>
#include <metaioSDK/GestureHandler.h>


SceneBase::SceneBase(QObject *parent, QStatusBar *statusBar) :
	QGraphicsScene(parent),
	m_initialized(false),
	m_pGestureHandler(0),
	m_pMetaioSDK(0),
	m_viewportWidth(0),
	m_viewportHeight(0)
{
	m_pStatusBar = statusBar;
	fps = 25;
}

SceneBase::~SceneBase()
{
	// Shut down SDK instance here. If you register your own sensors component, make sure you
	// delete it after these lines:
	/*if (m_pMetaioSDK)
	{
		m_pMetaioSDK->registerCallback(0);
		m_pMetaioSDK->registerSensorsComponent(0);
	}*/

	delete m_pMetaioSDK;

	delete m_pGestureHandler;
}

void SceneBase::setProjectPath(std::string path)
{
	projectPath = path;
}

void SceneBase::setTestFilePath(std::string path)
{
	testFilePath = path;
}

void SceneBase::setMode(int _mode)
{
	mode = _mode;
}


void SceneBase::drawBackground(QPainter* painter, const QRectF& rect)
{
	painter->save();
	if (painter->paintEngine()->type() != QPaintEngine::OpenGL2)
	{
		qCritical("SceneBase: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
		return;
	}

	const unsigned int viewportWidth = (unsigned int)(0 < rect.width() ? rect.width() : 0);
	const unsigned int viewportHeight = (unsigned int)(0 < rect.height() ? rect.height() : 0);

	//const unsigned int viewportWidth = (unsigned int)max(0, rect.width());
	//const unsigned int viewportHeight = (unsigned int)max(0, rect.height());

	if (!m_initialized)
	{

		m_pMetaioSDK = metaio::CreateMetaioSDKWin32();
		// Update StatusBar
		m_pStatusBar->showMessage((m_pMetaioSDK->getVersion()).c_str());
		m_pMetaioSDK->initializeRenderer((int)viewportWidth, (int)viewportHeight, metaio::ESCREEN_ROTATION_0, metaio::ERENDER_SYSTEM_OPENGL_EXTERNAL);
		
		// TODO: Set your preferred camera resolution. On desktop platforms, one typically has more
		//       performance and thus can use a higher resolution for tracking and rendering.
		//       4:3 resolutions are recommended because many standard USB cameras behave differently
		//       in widescreen capturing mode, i.e. have different calibration parameters. For best
		//       results, use m_pMetaioSDK->setCameraParameters(...) to load your own calibration
		//       for the camera model you're using.
		std::vector<metaio::Camera> cameras = m_pMetaioSDK->getCameraList();
		if(cameras.size()>0)
		{
			// set the resolution to 640x480
			cameras[0].resolution = metaio::Vector2di(640,480);
			m_pMetaioSDK->startCamera( cameras[0] );
		}

		// Listen to onSDKReady and other events that we may want to handle
		m_pMetaioSDK->registerCallback(this);

		m_initialized = true;

		m_pGestureHandler = new metaio::GestureHandler(m_pMetaioSDK);
		
		afterMetaioSDKInitialized();

		// At this point, the SDK and its renderer is initialized. Since we registered ourself as
		// callback, we will receive the onSDKReady event next, and load our content there.
	}

	if (m_viewportWidth != viewportWidth || m_viewportHeight != viewportHeight)
	{
		m_pMetaioSDK->resizeRenderer((int)viewportWidth, (int)viewportHeight);

		m_viewportWidth = viewportWidth;
		m_viewportHeight = viewportHeight;
	}

	// Enable anti-aliasing
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	
	// Load image or video
	switch (mode)
	{
		case (IMAGE):
			if ((m_pMetaioSDK->setImage(testFilePath)) == metaio::Vector2di(0, 0))
			{
				std::string msg = "loading " + testFilePath + " failed";
				qCritical(msg.c_str());
			}
			break;
		case (VIDEO):
			//TODO Implement code for using a video as source here
			break;
		case (CAMERA):
			break;
	}
	performRendering();

	glPopAttrib();

	// Trigger an update at least every 20 milliseconds, change this if you need higher FPS, or no
	// continuous rendering
	QTimer::singleShot(fps, this, SLOT(update()));

	painter->restore();

	// This is a workaround to render the web pages correctly
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}


void SceneBase::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	super::mouseMoveEvent(mouseEvent);

	// mouseEvent->screenPos() and mouseEvent->pos() seem to be always return (0,0) and scenePos()
	// has its origin in the middle of the rendering pane
	const int x = mouseEvent->scenePos().x() + (int)m_viewportWidth/2;
	const int y = mouseEvent->scenePos().y() + (int)m_viewportHeight/2;

	// Forward event to gesture handler (needed for drag gesture, just like the mouse press/release events)
	if (m_pGestureHandler)
		m_pGestureHandler->touchesMoved(x, y);
}


void SceneBase::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	super::mousePressEvent(mouseEvent);

	// See comment in mouseMoveEvent()
	const int x = mouseEvent->scenePos().x() + (int)m_viewportWidth/2;
	const int y = mouseEvent->scenePos().y() + (int)m_viewportHeight/2;

	// Forward event to gesture handler
	if (m_pGestureHandler)
		m_pGestureHandler->touchesBegan(x, y);
}


void SceneBase::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	super::mouseReleaseEvent(mouseEvent);

	// See comment in mouseMoveEvent()
	const int x = mouseEvent->scenePos().x() + (int)m_viewportWidth/2;
	const int y = mouseEvent->scenePos().y() + (int)m_viewportHeight/2;

	// Forward event to gesture handler
	if (m_pGestureHandler)
		m_pGestureHandler->touchesEnded(x, y);
}


void SceneBase::onSDKReady()
{
	loadContent();
}
