#pragma once
#include "afxwin.h"


// CIndexRight �Ի���

class CIndexRight : public CDialogEx
{
	DECLARE_DYNAMIC(CIndexRight)

public:
	CIndexRight(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIndexRight();

// �Ի�������
	enum { IDD = IDD_INDEX_RIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CImage m_img;
	CImage m_img_bg;
	CImage m_img_lg;

	CStatic m_index_index;
	CStatic m_index_show;
protected:
	afx_msg LRESULT OnShowimg(WPARAM wParam, LPARAM lParam);
};

BOOL LoadImageFromResource(IN CImage* pImage,
	IN UINT nResID,
	IN LPCWSTR lpTyp);