#pragma once
#include "explorer1.h"


// CAuthority 对话框

class CAuthority : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthority)

public:
	CAuthority(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAuthority();

// 对话框数据
	enum { IDD = IDD_AUTHORITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_web;
	BOOL OnInitDialog();
	int flag;
	CString token;
	CString gettoken();
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);
};
