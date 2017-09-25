#ifndef VideoRender_h_
#define VideoRender_h_

class VideoRender : public QWidget
{
	Q_OBJECT
public:
	VideoRender(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~VideoRender();
	void	DoRender(const LiveVideoFrame *pFrameData);
	void	Clear();

	void	pauseRender();
	void	recoverRender();

	void	enterFullScreen();//全屏
	void	exitFullScreen();//退出全屏
	std::string getId();

signals:
	void	applyFullScreen(VideoRender* pRender);
	void	exitFullScreen(VideoRender* pRender);

protected:
	void	paintEvent(QPaintEvent * event) override;
	void	mouseDoubleClickEvent( QMouseEvent * event ) override;

private:
	void	paintPic(uint8* pData);

private:
	std::string	m_identifier;
	E_ColorFormat m_colorFormat;
	uint32		m_frameDataBufLen;	//帧数据长度
	uint8*		m_pFrameDataBuf;	//帧数据缓存
	uint8*		m_pBkgDataBuf;		//背景缓存

	uint32		m_frameWidth;		//帧宽度
	uint32		m_frameHeight;		//帧高度

	uint32		m_nRenderDataBufLen;//渲染缓存大小
	uint8*		m_pRenderDataBuf;	//渲染缓存

	QWidget*	m_pParentWidget;
	QRect		m_Rect;
	bool		m_bPause;//是否暂停渲染	

	clock_t		m_lastClock;
	int			m_nFpsCounter;
	int			m_nFps;
};

#endif //VideoRender_h_
