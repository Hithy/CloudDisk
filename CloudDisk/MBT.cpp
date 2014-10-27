#include "stdafx.h"
#include "MBT.h"
#include "resource.h"


CMBT::CMBT()
{
	m_Tracked = FALSE;
}


CMBT::~CMBT()
{
}
BEGIN_MESSAGE_MAP(CMBT, CBitmapButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()


void CMBT::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_Tracked)
	{
		m_Tracked = TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = 10;
		_TrackMouseEvent(&tme);

		
		Invalidate(FALSE);
		//((CIndexLeft *)GetParent())->m_index_right->PostMessageW(WM_SHOWIMG, TRUE, m_IID);
		

	}
	CBitmapButton::OnMouseMove(nFlags, point);
}


void CMBT::OnMouseLeave()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//m_parent->m_index_right->PostMessageW(WM_SHOWIMG, FALSE, m_IID);
	
	m_Tracked = FALSE;
	this->LoadBitmaps(this->m_img_nm);
	if (m_IID)
	{
		GetParent()->PostMessageW(WM_SHOWIMGTMP, m_IID, FALSE);
	}
	Invalidate(FALSE);
	CBitmapButton::OnMouseLeave();
}



void CMBT::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	this->LoadBitmaps(this->m_img_ov);
	if (m_IID)
	{
		GetParent()->PostMessageW(WM_SHOWIMGTMP, m_IID, TRUE);
	}
	Invalidate(FALSE);
	CBitmapButton::OnMouseHover(nFlags, point);
}
