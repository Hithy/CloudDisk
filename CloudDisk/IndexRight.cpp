// IndexRight.cpp : 实现文件
//

#include "stdafx.h"
#include "CloudDisk.h"
#include "IndexRight.h"
#include "afxdialogex.h"


// CIndexRight 对话框

IMPLEMENT_DYNAMIC(CIndexRight, CDialogEx)

CIndexRight::CIndexRight(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIndexRight::IDD, pParent)
{
}

CIndexRight::~CIndexRight()
{
}

void CIndexRight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INDEX_INDEX, m_index_index);
	DDX_Control(pDX, IDC_INDEX_SHOW, m_index_show);
}


BEGIN_MESSAGE_MAP(CIndexRight, CDialogEx)
	ON_MESSAGE(WM_SHOWIMG, &CIndexRight::OnShowimg)
END_MESSAGE_MAP()


// CIndexRight 消息处理程序


afx_msg LRESULT CIndexRight::OnShowimg(WPARAM wParam, LPARAM lParam)
{
	CBitmap cb;
	CImage cbmp;
	CImage tmp1;
	HBITMAP tmp;
	if (!lParam)
	{
		m_index_show.ShowWindow(SW_HIDE);
		tmp = m_index_show.SetBitmap(NULL);
		if (tmp)
		{
			DeleteObject(tmp);
		}
		return TRUE;
	}
	m_index_show.ShowWindow(SW_SHOW);
	switch (wParam)
	{
	case IDC_INDEX_TRANS:
		LoadImageFromResource(&cbmp, IDB_IR_TRANS, L"PNG");
		break;
	case IDC_INDEX_CONFIG:
		LoadImageFromResource(&cbmp, IDB_IR_CONFIG, L"PNG");
		break;
	case IDC_INDEX_ABOUT:
		LoadImageFromResource(&cbmp, IDB_IR_ABOUT, L"PNG");
		break;
	case IDC_INDEX_NEW:
		LoadImageFromResource(&cbmp, IDB_IR_NEW, L"PNG");
		break;
	default:
		break;
	}
	if (m_index_show.GetBitmap() != NULL)
	{
		tmp = m_index_show.SetBitmap(NULL);
		DeleteObject(tmp);
	}
	m_index_show.SetBitmap(cbmp);
	return 0;
}

