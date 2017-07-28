#include "stdafx.h"
#include "WndList.h"


int WndList::ms_nLastIndex = 0;

WndList::WndList( QWidget *parent/* = 0*/, Qt::WindowFlags f/* = 0*/ )
	:QDialog(parent, f)
{
	m_ui.setupUi(this);
}

HWND WndList::GetSelectWnd(QWidget* parent /*= NULL*/)
{
	WndList* wndlist = new WndList(parent);
	int nRet = wndlist->Refresh();
	if (nRet != NO_ERR)
	{
		if (nRet==1301)//AV_ERR_DEVICE_NOT_EXIST 没有可供分享的窗口
		{
			ShowCodeErrorTips( nRet, FromBits("没有可供分享的窗口."), parent );
		}
		else
		{
			ShowCodeErrorTips( nRet, "Get window list failed.", parent );
		}
	}
	else
	{
		wndlist->exec();
	}
	HWND hwnd = wndlist->m_curhwnd;
	delete wndlist;
	return hwnd;
}

int WndList::Refresh()
{
	m_curhwnd = NULL;
	m_ui.liWndList->clear();
	int nRet = GetILive()->getWndList(m_wndList);
	if (nRet == NO_ERR)
	{
		for ( int i = 0; i<m_wndList.size(); ++i )
		{
			m_ui.liWndList->addItem( new QListWidgetItem( FromBits( m_wndList[i].second.c_str() ) ) );
		}
		ms_nLastIndex = iliveMin( m_wndList.size()-1, iliveMax(0, ms_nLastIndex) );
		m_ui.liWndList->setCurrentRow(ms_nLastIndex);
	}
	return nRet;
}

void WndList::on_btnOK_clicked()
{
	ms_nLastIndex = m_ui.liWndList->currentRow();
	m_curhwnd = m_wndList[ms_nLastIndex].first;
	close();
}

void WndList::on_btnCancel_clicked()
{
	close();
}

void WndList::on_liWndList_itemDoubleClicked( QListWidgetItem* item )
{
	ms_nLastIndex = m_ui.liWndList->currentRow();
	m_curhwnd = m_wndList[ms_nLastIndex].first;
	close();
}
