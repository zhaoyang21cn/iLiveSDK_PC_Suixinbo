#ifndef WndList_h_
#define WndList_h_

#include "ui_WndList.h"

class WndList : public QDialog
{
	Q_OBJECT
public:
	static HWND GetSelectWnd(QWidget* parent = NULL);

private:
	WndList(QWidget *parent = 0, Qt::WindowFlags f = 0);
	int Refresh();

private slots:
	void on_btnOK_clicked();
	void on_btnCancel_clicked();
	void on_liWndList_itemDoubleClicked(QListWidgetItem* item);
	
private:
	static int									ms_nLastIndex;
	Vector< Pair<HWND/*id*/, String/*name*/> >	m_wndList;
	HWND										m_curhwnd;
	Ui::WndList									m_ui;
};

#endif //WndList_h_