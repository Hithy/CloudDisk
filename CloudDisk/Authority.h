#pragma once
#include "explorer1.h"


// CAuthority �Ի���

class CAuthority : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthority)

public:
	CAuthority(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAuthority();

// �Ի�������
	enum { IDD = IDD_AUTHORITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
