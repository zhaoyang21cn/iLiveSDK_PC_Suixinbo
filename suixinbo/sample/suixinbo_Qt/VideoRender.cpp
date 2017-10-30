#include "stdafx.h"
#include "VideoRender.h"

VideoRender::VideoRender( QWidget *parent /*= NULL*/ )
	: QWidget(parent)
	, m_pRootView(NULL)
	, m_bFree(true)
	, m_bgColor(0xFF000000)
	, m_pParentWidget(parent)
{
	
}

VideoRender::~VideoRender()
{
	if (m_pRootView)
	{
		m_pRootView->uninit();
		m_pRootView->destroy();
	}
}

bool VideoRender::isFree()
{
	return m_bFree;
}

String VideoRender::getIdentifier()
{
	return m_identifier;
}

void VideoRender::setView( String identifier, E_VideoSrc type )
{
	m_identifier = identifier;
	iLiveView view;
	view.mode = VIEW_MODE_HIDDEN;	//按比例缩放，填充黑边;
	//view.mode = VIEW_MODE_FIT;	//拉伸画面到控件大小;
	view.exclusive = true;
	m_pRootView->setView(m_identifier, type, view, false);
	m_bFree = false;
}

void VideoRender::setBackgroundColor( uint32 argb )
{
	m_bgColor = argb;
}

void VideoRender::doRender( const LiveVideoFrame* frame )
{
	m_pRootView->doRender(frame);
}

void VideoRender::remove()
{
	exitFullScreen();
	m_pRootView->removeAllView(true);
	m_identifier = "";
	m_bFree = true;
}

void VideoRender::showEvent( QShowEvent *event )
{
	if (!m_pRootView)
	{
		m_pRootView = iLiveCreateRootView();
		bool bRet = m_pRootView->init((HWND)winId());
		assert(bRet);
	}
	m_pRootView->setBackgroundColor(m_bgColor);//灰色
}

void VideoRender::paintEvent( QPaintEvent *event )
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
	QWidget::paintEvent(event);
}

void VideoRender::mouseDoubleClickEvent( QMouseEvent * event )
{
	if ( isFullScreen() )
	{
		exitFullScreen();
	}
	else
	{
		enterFullScreen();
	}
}

void VideoRender::enterFullScreen()
{
	if ( !isFullScreen() )
	{
		m_pParentWidget = parentWidget();
		m_Rect = geometry();
		this->setParent(NULL);
		this->showFullScreen();
	}
}

void VideoRender::exitFullScreen()
{
	if ( isFullScreen() )
	{
		this->setParent(m_pParentWidget);
		this->setGeometry(m_Rect);
		this->showNormal();
	}
}