
// CloudDisk.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCloudDiskApp: 
// �йش����ʵ�֣������ CloudDisk.cpp
//

class CCloudDiskApp : public CWinApp
{
public:
	CCloudDiskApp();

// ��д
public:
	virtual BOOL InitInstance();
	BOOL flag;
// ʵ��

	DECLARE_MESSAGE_MAP()
//	afx_msg void OnDownload();
};

extern CCloudDiskApp theApp;