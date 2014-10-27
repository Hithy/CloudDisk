#pragma once
#include "afxext.h"
//#include "IndexLeft.h"

class CMBT :
	public CBitmapButton
{
public:
	CMBT();
	~CMBT();

	DECLARE_MESSAGE_MAP()

public:

	BOOL m_Tracked;
	DWORD m_IID;
	DWORD m_img_nm;
	DWORD m_img_ov;
	DWORD m_img_cl;
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
};

