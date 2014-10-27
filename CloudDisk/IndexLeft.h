#pragma once
#include "afxext.h"
#include "MBT.h"
#include "IndexRight.h"


// CIndexLeft 对话框

class CIndexLeft : public CDialogEx
{
	DECLARE_DYNAMIC(CIndexLeft)

public:
	CIndexLeft(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIndexLeft();

// 对话框数据
	enum { IDD = IDD_INDEX_LEFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CIndexRight *m_index_right;

	CMBT m_index_back;
	CMBT m_index_trans;
	CMBT m_index_new;
	CMBT m_index_config;
	CMBT m_index_about;

	BOOL m_show;

	HINSTANCE m_hInstance;
	CImage img_left;
	CRect m_rect;
	afx_msg void OnBnClickedIndexBack();
	virtual BOOL OnInitDialog();
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
protected:
	afx_msg LRESULT OnShowctl(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHidectl(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowimgtmp(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedIndexTrans();
	afx_msg void OnBnClickedIndexNew();
	afx_msg void OnBnClickedIndexConfig();
};
