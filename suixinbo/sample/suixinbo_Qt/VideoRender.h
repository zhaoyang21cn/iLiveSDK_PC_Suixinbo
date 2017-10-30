#ifndef VideoRender_h_
#define VideoRender_h_

class VideoRender : public QWidget
{
	Q_OBJECT
public:
	VideoRender(QWidget *parent = NULL);
	~VideoRender();

	bool isFree();
	String getIdentifier();
	void setView(String identifier, E_VideoSrc type);
	void setBackgroundColor(uint32 argb);
	void doRender(const LiveVideoFrame* frame);
	void remove();

protected:
	void showEvent(QShowEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent * event) override;

private:
	void enterFullScreen();	//进入全屏
	void exitFullScreen();	//退出全屏

private:
	iLiveRootView*	m_pRootView;
	String			m_identifier;
	bool			m_bFree;
	uint32			m_bgColor;

	QWidget*		m_pParentWidget;
	QRect			m_Rect;
};

#endif //VideoRender_h_
