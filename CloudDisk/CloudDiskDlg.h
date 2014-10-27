
// CloudDiskDlg.h : 头文件
//

#pragma once
#include "afxext.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "IndexLeft.h"
#include "IndexRight.h"
#include "MBT.h"
#include "config.h"
#include "Authority.h"



// CCloudDiskDlg 对话框
class CCloudDiskDlg : public CDialogEx
{
// 构造
public:
	CCloudDiskDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	CLogfile *m_config;
	TransList *m_trans_up;
	TransList *m_trans_down;

	CIndexLeft *indexleft;
	CIndexRight *indexright;

	CMBT m_main_left;
//	CButton m_main_upload;
//	CButton m_main_download;
//	CListCtrl m_main_list;
//	CStatic m_logo;
//	CStatic m_welcome;
	CRect m_main_rect;
	DWORD m_x;
	DWORD m_y;
	DWORD m_index;
	CImage m_img_black;
	CImage m_img_last_main;

	HINSTANCE m_hInstance;
	BLENDFUNCTION bf;
	afx_msg void OnBnClickedMainLeft();
protected:
	afx_msg LRESULT OnIndexToMain(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void InitMain();
	void InitChild();
	CMBT m_main_bt_upload;
//	CMBT m_main_bt_download;
	CStatic m_main_img_welcome;
//	CListCtrl m_main_ls_file;
	CStatic m_main_img_logo;
	CMBT m_main_bt_refresh;
	CButton m_trans_bt_up;
	CMBT m_trans_bt_down;
	CMBT m_config_bt_save;
	CMBT m_config_bt_load;
	CMBT m_new_bt_token_add;
	CMBT m_new_bt_reset;
	CMBT m_new_bt_save;
	CListCtrl m_main_ls_file;
	CListCtrl m_trans_ls_up;
	CListCtrl m_trans_ls_down;
	CListCtrl m_config_ls_token;
//	CListCtrl m_new_ls_tokne;
	CListCtrl m_new_ls_token;
	CEdit m_config_et_name;
	CEdit m_config_et_token_num;
	CEdit m_new_et_name;
	CEdit m_new_et_token_num;
	CEdit m_new_et_token_add;
	CStatic m_st_user_name;
	CStatic m_st_token_num;

	BOOL m_token_list_valid;
	//BOOL m_download;
	//DWORD pagestate;
	void showmain();
	void shownew();
	void showconfig();
	void showtrans();
	void hideall();
	void synctoken();
	void syncfile();
	void synctrans();
	
protected:
//	afx_msg LRESULT OnShowwnd(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedTransBtUp();
	afx_msg void OnBnClickedTransBtDown();
//	int m_new_et_token_num_vl;
	afx_msg void OnBnClickedNewBtSave();
	afx_msg void OnBnClickedNewBtTokenAdd();
	afx_msg void OnBnClickedNewBtReset();
	afx_msg void OnBnClickedConfigBtSave();
	afx_msg void OnBnClickedConfigBtLoad();
	afx_msg void OnNMRClickMainLsFile(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnDownloadFile(WPARAM wParam, LPARAM lParam);
public:
//	afx_msg void OnIdrMainFileMenu();
	afx_msg void OnDownload();
	afx_msg void OnBnClickedMainUpload();
	afx_msg void OnBnClickedMainRefresh();
protected:
	afx_msg LRESULT OnUploadComplete(WPARAM wParam, LPARAM lParam);
public:
	CStatic m_st_upload_ct;
	CStatic m_st_download_ct;
//	CButton m_main_bt_download;
	afx_msg void OnBnClickedMainDownload();
	CMBT m_main_bt_download;
};

BOOL LoadImageFromResource(IN CImage* pImage,
	IN UINT nResID,
	IN LPCWSTR lpTyp);

typedef struct _FileToThread
{
	CCloudDiskDlg *dlg;
	TransFile *file;
	CString path;
	DWORD index;
}FileBag;

void monitor(CCloudDiskDlg *dlg);
void udct_monitor(CCloudDiskDlg* dlg);
void upload(FileBag* bag);
void download(FileBag* bag);