#ifndef NetworkHelper_h_
#define NetworkHelper_h_

#define LimitTimeOut 5000 //请求超时时间(毫秒)

enum E_NetworkReply
{
	E_NetOK,
	E_NetTimeOut,//超时
	E_NetReplyError,
};

typedef void (*ReceiveFun)(int errCode, const QByteArray& bytes, void* pCusData);

class NetworkHelper : public QObject
{
	Q_OBJECT
public:
	static void get(const QString& url, ReceiveFun receiver, void* data, int timeout = LimitTimeOut);
	static void post(const QString& url, const QString& content, ReceiveFun receiver, void* data, int timeout = LimitTimeOut);

private slots:
	void OnReplyFinished(QNetworkReply* reply);
	void OnTimer();

private:
	NetworkHelper(QString url, QString content, ReceiveFun receiver, void* pCusData, int timeout);
	~NetworkHelper();
	
	void excuteGet();
	void excutePost();

private:
	QNetworkAccessManager* m_pNetworkAccessManager;
	QTimer*		m_pTimer;

	QString		m_url;
	QString		m_content;	
	ReceiveFun  m_receiver;
	void*		m_pCusdata;
	int			m_timeout;
};

#endif//NetworkHelper_h_