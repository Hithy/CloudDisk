
// CloudDiskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CloudDisk.h"
#include "CloudDiskDlg.h"
#include "afxdialogex.h"
#include "FileProcess.h"
#include "cloud.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCloudDiskDlg 对话框



CCloudDiskDlg::CCloudDiskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCloudDiskDlg::IDD, pParent)
	, m_index(INDEX_LEFT_LENGTH)
	, m_hInstance(AfxGetApp()->m_hInstance)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCloudDiskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_LEFT, m_main_left);
	DDX_Control(pDX, IDC_MAIN_UPLOAD, m_main_bt_upload);
	DDX_Control(pDX, IDC_WELCOME, m_main_img_welcome);
	DDX_Control(pDX, IDC_LOGO, m_main_img_logo);
	DDX_Control(pDX, IDC_MAIN_REFRESH, m_main_bt_refresh);
	DDX_Control(pDX, IDC_TRANS_BT_UP, m_trans_bt_up);
	DDX_Control(pDX, IDC_TRANS_BT_DOWN, m_trans_bt_down);
	DDX_Control(pDX, IDC_CONFIG_BT_SAVE, m_config_bt_save);
	DDX_Control(pDX, IDC_CONFIG_BT_LOAD, m_config_bt_load);
	DDX_Control(pDX, IDC_NEW_BT_TOKEN_ADD, m_new_bt_token_add);
	DDX_Control(pDX, IDC_NEW_BT_RESET, m_new_bt_reset);
	DDX_Control(pDX, IDC_NEW_BT_SAVE, m_new_bt_save);
	DDX_Control(pDX, IDC_MAIN_LS_FILE, m_main_ls_file);
	DDX_Control(pDX, IDC_TRANS_LS_UP, m_trans_ls_up);
	DDX_Control(pDX, IDC_TRANS_LS_DOWN, m_trans_ls_down);
	DDX_Control(pDX, IDC_CONFIG_LS_TOKEN, m_config_ls_token);
	DDX_Control(pDX, IDC_NEW_LS_TOKEN, m_new_ls_token);
	DDX_Control(pDX, IDC_CONFIG_ET_NAME, m_config_et_name);
	DDX_Control(pDX, IDC_CONFIG_ET_TOKEN_NUM, m_config_et_token_num);
	DDX_Control(pDX, IDC_NEW_ET_NAME, m_new_et_name);
	DDX_Control(pDX, IDC_NEW_ET_TOKEN_NUM, m_new_et_token_num);
	DDX_Control(pDX, IDC_NEW_ET_TOKEN_ADD, m_new_et_token_add);
	DDX_Control(pDX, IDC_ST_USER_NAME, m_st_user_name);
	DDX_Control(pDX, IDC_ST_TOKEN_NUM, m_st_token_num);
	//  DDX_Text(pDX, IDC_NEW_ET_TOKEN_NUM, m_new_et_token_num_vl);
	DDX_Control(pDX, IDC_ST_UPLOAD_CT, m_st_upload_ct);
	DDX_Control(pDX, IDC_ST_DOWNLOAD_CT, m_st_download_ct);
	//  DDX_Control(pDX, IDC_MAIN_DOWNLOAD, m_main_bt_download);
	DDX_Control(pDX, IDC_MAIN_DOWNLOAD, m_main_bt_download);
}

BEGIN_MESSAGE_MAP(CCloudDiskDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MAIN_LEFT, &CCloudDiskDlg::OnBnClickedMainLeft)
	ON_MESSAGE(WM_INDEX_TO_MAIN, &CCloudDiskDlg::OnIndexToMain)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_TRANS_BT_UP, &CCloudDiskDlg::OnBnClickedTransBtUp)
	ON_BN_CLICKED(IDC_TRANS_BT_DOWN, &CCloudDiskDlg::OnBnClickedTransBtDown)
	ON_BN_CLICKED(IDC_NEW_BT_SAVE, &CCloudDiskDlg::OnBnClickedNewBtSave)
	ON_BN_CLICKED(IDC_NEW_BT_TOKEN_ADD, &CCloudDiskDlg::OnBnClickedNewBtTokenAdd)
	ON_BN_CLICKED(IDC_NEW_BT_RESET, &CCloudDiskDlg::OnBnClickedNewBtReset)
	ON_BN_CLICKED(IDC_CONFIG_BT_SAVE, &CCloudDiskDlg::OnBnClickedConfigBtSave)
	ON_BN_CLICKED(IDC_CONFIG_BT_LOAD, &CCloudDiskDlg::OnBnClickedConfigBtLoad)
	ON_NOTIFY(NM_RCLICK, IDC_MAIN_LS_FILE, &CCloudDiskDlg::OnNMRClickMainLsFile)
	ON_MESSAGE(WM_DOWNLOAD_FILE, &CCloudDiskDlg::OnDownloadFile)
//	ON_COMMAND(IDR_MAIN_FILE_MENU, &CCloudDiskDlg::OnIdrMainFileMenu)
	ON_COMMAND(ID_DOWNLOAD, &CCloudDiskDlg::OnDownload)
	ON_BN_CLICKED(IDC_MAIN_UPLOAD, &CCloudDiskDlg::OnBnClickedMainUpload)
	ON_BN_CLICKED(IDC_MAIN_REFRESH, &CCloudDiskDlg::OnBnClickedMainRefresh)
	ON_MESSAGE(WM_UPLOAD_COMPLETE, &CCloudDiskDlg::OnUploadComplete)
	ON_BN_CLICKED(IDC_MAIN_DOWNLOAD, &CCloudDiskDlg::OnBnClickedMainDownload)
END_MESSAGE_MAP()


// CCloudDiskDlg 消息处理程序

BOOL CCloudDiskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	this->SetWindowPos(NULL, 300, 150, 640, 400, NULL);
	this->GetWindowRect(&m_main_rect);
	this->SetBackgroundImage(IDB_MAIN_BK);
	m_x = m_main_rect.right - m_main_rect.left;
	m_y = m_main_rect.bottom - m_main_rect.top;

	((CCloudDiskApp*)AfxGetApp())->flag = TRUE;
	//this->SetBackgroundImage(IDB_MAIN_BK);
	

	m_token_list_valid = FALSE;
	m_config = new CLogfile;
	m_trans_up = new TransList;
	m_trans_down = new TransList;
	InitMain();
	InitChild();
	showmain();

	m_main_left.SetWindowPos(NULL, 0, 20, 175, 60, NULL);
	m_main_left.LoadBitmaps(IDB_MENU_NM);
	m_main_left.m_img_nm = IDB_MENU_NM;
	m_main_left.m_img_ov = IDB_MENU_OV;
	
	HBITMAP hbmp = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_MAIN_TITLE));
	//LoadImageFromResource(&main_logo, IDB_IR_CONFIG, L"PNG");
	//main_logo->LoadFromResource(m_hInstance, IDB_MAIN_TITLE);
	m_main_img_logo.ShowWindow(SW_SHOW);
	m_main_img_logo.SetWindowPos(NULL, 190, 0, 450, 100, SWP_SHOWWINDOW);
	m_main_img_logo.SetBitmap(hbmp);

	
	//
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)monitor, this, 0, NULL);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)udct_monitor, this, 0, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCloudDiskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCloudDiskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//进入索引界面
void CCloudDiskDlg::OnBnClickedMainLeft()
{
	CDC *dc;
	CDC memdc;
	hideall();
	indexleft->m_show = TRUE;
	dc = GetDC();
	memdc.CreateCompatibleDC(dc);
	memdc.SelectObject(m_img_last_main);
	memdc.BitBlt(0, 0, m_x, m_y, dc, 0, 0, SRCCOPY);
	CImage black;
	black.LoadFromResource(m_hInstance, IDB_BLACK);
	memdc.SelectObject(black);
	bf.SourceConstantAlpha = 5;
	GetWindowRect(&m_main_rect);
	for (int i = 0; i < INDEX_LEFT_LENGTH; i += 5)
	{
		indexleft->SetWindowPos(NULL, m_main_rect.left, m_main_rect.top, i, m_y, SWP_SHOWWINDOW);
		dc->AlphaBlend(0, 0, m_x, m_y, &memdc, 0, 0, m_x, m_y, bf);
		Sleep(1);
	}
	
	//black.Detach();
	memdc.SelectObject(indexright->m_img_bg);
	memdc.BitBlt(0, 0, m_x - INDEX_LEFT_LENGTH, m_y, dc, INDEX_LEFT_LENGTH, 0, SRCCOPY);
	
	ReleaseDC(dc);
	ReleaseDC(&memdc);


	
	
	if (((CCloudDiskApp*)AfxGetApp())->flag)
		indexright->SetBackgroundImage(indexright->m_img_bg);
	indexright->SetWindowPos(NULL, m_main_rect.left + INDEX_LEFT_LENGTH, m_main_rect.top, m_x - INDEX_LEFT_LENGTH, m_y, SWP_SHOWWINDOW);
	indexleft->PostMessageW(WM_SHOWCTL, 0, 0);

	
	
	// TODO:  在此添加控件通知处理程序代码
}

//回到主界面
afx_msg LRESULT CCloudDiskDlg::OnIndexToMain(WPARAM wParam, LPARAM lParam)
{
	CDC *dc;
	CDC memdc;
	HBITMAP hbmp;
	//indexright->m_index_index.SetBitmap()
	
	indexleft->PostMessageW(WM_HIDECTL, 0, 0);
	GetWindowRect(&m_main_rect);
	dc = GetDC();
	memdc.CreateCompatibleDC(dc);
	memdc.SelectObject(m_img_last_main);
	bf.SourceConstantAlpha = 10;
	indexright->ShowWindow(SW_HIDE);
	for (int i = INDEX_LEFT_LENGTH; i > 0; i -= 5)
	{
		indexleft->SetWindowPos(NULL, m_main_rect.left, m_main_rect.top, i, m_y, NULL);
		dc->AlphaBlend(0, 0, m_x , m_y, &memdc, 0, 0, m_x , m_y, bf);
		Sleep(1);
	}
	indexleft->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	dc->BitBlt(0, 0, m_x, m_y, &memdc, 0, 0, SRCCOPY);
	ReleaseDC(dc);
	ReleaseDC(&memdc);
	((CCloudDiskApp*)AfxGetApp())->flag = FALSE;


	hbmp = m_main_img_logo.SetBitmap(NULL);
	if (hbmp != NULL)
		DeleteObject(hbmp);
	switch (wParam)
	{
	case IDC_INDEX_BACK:
		showmain();
		syncfile();
		hbmp = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_MAIN_TITLE));
		break;
	case IDC_INDEX_CONFIG:
		showconfig();
		hbmp = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CONFIG_TITLE));
		break;
	case IDC_INDEX_NEW:
		hbmp = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_NEW_TITLE));
		shownew();
		break;
	case IDC_INDEX_TRANS:
		hbmp = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_TRANS_TITLE));
		showtrans();
		break;
	default:
		break;
	}
	m_main_img_logo.SetBitmap(hbmp);
	m_main_left.PostMessageW(WM_MOUSELEAVE);
	indexleft->m_show = FALSE;

	return 0;
}

//加载资源PNG图片
BOOL LoadImageFromResource(IN CImage* pImage,
	IN UINT nResID,
	IN LPCWSTR lpTyp)
{
	if (pImage == NULL) return false;

	pImage->Destroy();

	// 查找资源
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL) return false;

	// 加载资源
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid = ::LockResource(hImgData);

	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// 解除内存中的指定资源
	::GlobalUnlock(hNew);

	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
	}
	else
	{
		// 加载图片
		pImage->Load(pStream);
		GlobalFree(hNew);
	}

	// 释放资源
	::FreeResource(hImgData);

	return true;
}


//拖动处理
void CCloudDiskDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonDown(nFlags, point);
	GetWindowRect(&m_main_rect);
	if (point.x > m_main_rect.right - m_main_rect.left - 20 && point.x < m_main_rect.right - m_main_rect.left && point.y > 0 && point.y < 20)
		this->OnOK();

	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}


//建立各个窗口
void CCloudDiskDlg::InitChild()
{
	bf.AlphaFormat = 0;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	m_img_black.LoadFromResource(m_hInstance, IDB_BLACK);
	m_img_last_main.Create(m_x, m_y, 32);
	

	indexleft = new CIndexLeft;
	indexright = new CIndexRight;
	indexleft->Create(IDD_INDEX_LEFT, this);
	indexright->Create(IDD_INDEX_RIGHT, this);

	indexleft->m_index_right = indexright;
	indexleft->m_show = FALSE;

	indexleft->SetBackgroundImage(IDB_IL_BG);
	indexright->m_img_bg.Create(m_x - INDEX_LEFT_LENGTH, m_y, 32);
	//LoadImageFromResource(&indexright->m_img_lg, IDB_LOGO, L"PNG");
	//indexright->m_index_index.SetBitmap(indexright->m_img_lg);
	//LoadImageFromResource(&(indexright->m_img), IDB_IR_TRANS, L"PNG");
	//indexright->m_index_show.SetBitmap(indexright->m_img);

	CRect rect;
	m_trans_ls_down.GetClientRect(&rect);
	m_trans_ls_down.InsertColumn(0, L"下载中的文件");
	m_trans_ls_down.SetColumnWidth(0, 7 * rect.Width() / 10);
	m_trans_ls_down.InsertColumn(1, L"下载进度");
	m_trans_ls_down.SetColumnWidth(1, 3 * rect.Width() / 10);


	m_trans_ls_up.GetClientRect(&rect);
	m_trans_ls_up.InsertColumn(0, L"上传中的文件");
	m_trans_ls_up.SetColumnWidth(0, 7 * rect.Width() / 10);
	m_trans_ls_up.InsertColumn(1, L"上传进度");
	m_trans_ls_up.SetColumnWidth(1, 3 * rect.Width() / 10);

	m_new_ls_token.GetClientRect(&rect);
	m_new_ls_token.InsertColumn(0, L"序号");
	m_new_ls_token.SetColumnWidth(0, 1 * rect.Width() / 10);
	m_new_ls_token.InsertColumn(1, L"Token");
	m_new_ls_token.SetColumnWidth(1, 9 * rect.Width() / 10);

	m_config_ls_token.GetClientRect(&rect);
	m_config_ls_token.InsertColumn(0, L"序号");
	m_config_ls_token.SetColumnWidth(0, 1 * rect.Width() / 10);
	m_config_ls_token.InsertColumn(1, L"Token");
	m_config_ls_token.SetColumnWidth(1, 9 * rect.Width() / 10);

	m_main_ls_file.GetClientRect(&rect);
	m_main_ls_file.InsertColumn(0, L"序号");
	m_main_ls_file.SetColumnWidth(0, 1 * rect.Width() / 10);
	m_main_ls_file.InsertColumn(1, L"文件名");
	m_main_ls_file.SetColumnWidth(1, 9 * rect.Width() / 10);
	
	/*m_main_ls_file.SetBkColor(RGB(240, 240, 240));
	m_main_ls_file.SetTextBkColor(RGB(240, 240, 240));
	m_config_ls_token.SetBkColor(RGB(240, 240, 240));
	m_config_ls_token.SetTextBkColor(RGB(240, 240, 240));
	m_new_ls_token.SetBkColor(RGB(240, 240, 240));
	m_new_ls_token.SetTextBkColor(RGB(240, 240, 240));
	m_trans_ls_up.SetBkColor(RGB(240, 240, 240));
	m_trans_ls_up.SetTextBkColor(RGB(240, 240, 240));
	m_trans_ls_down.SetBkColor(RGB(240, 240, 240));
	m_trans_ls_down.SetTextBkColor(RGB(240, 240, 240));*/

	m_main_ls_file.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_trans_ls_down.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_trans_ls_up.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_new_ls_token.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_config_ls_token.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_main_bt_upload.LoadBitmaps(IDB_MAIN_BT_UPLOAD_NM);
	m_main_bt_upload.m_img_nm = IDB_MAIN_BT_UPLOAD_NM;
	m_main_bt_upload.m_img_ov = IDB_MAIN_BT_UPLOAD_OV;
	m_main_bt_refresh.LoadBitmaps(IDB_MAIN_BT_REFRESH_NM);
	m_main_bt_refresh.m_img_nm = IDB_MAIN_BT_REFRESH_NM;
	m_main_bt_refresh.m_img_ov = IDB_MAIN_BT_REFRESH_OV;
	m_main_bt_download.LoadBitmaps(IDB_MAIN_BT_DOWNLOAD_NM);
	m_main_bt_download.m_img_nm = IDB_MAIN_BT_DOWNLOAD_NM;
	m_main_bt_download.m_img_ov = IDB_MAIN_BT_DOWNLOAD_OV;

	return;
}

void CCloudDiskDlg::InitMain()
{
	m_st_upload_ct.SetWindowPos(NULL, 527, 380, 30, 30, NULL);
	m_st_download_ct.SetWindowPos(NULL, 590, 380, 30, 30, NULL);

	m_main_bt_refresh.SetWindowPos(NULL, 70, 280, 53, 53, NULL);
	m_main_bt_upload.SetWindowPos(NULL, 70, 140, 53, 53, NULL);
	m_main_bt_download.SetWindowPos(NULL, 70, 210, 53, 53, NULL);
	m_main_ls_file.SetWindowPos(NULL, 160, 130, 400, 220, NULL);
	

	m_trans_bt_up.SetWindowPos(NULL, 70, 320, 250, 40, NULL);
	m_trans_bt_down.SetWindowPos(NULL, 320, 320, 250, 40, NULL);
	m_trans_ls_up.SetWindowPos(NULL, 70, 120, 500, 200, NULL);
	m_trans_ls_down.SetWindowPos(NULL, 70, 120, 500, 200, SWP_HIDEWINDOW);

	m_config_bt_save.SetWindowPos(NULL, 70, 270, 80, 40, NULL);
	m_config_bt_load.SetWindowPos(NULL, 70, 200, 80, 40, NULL);
	m_st_user_name.SetWindowPos(NULL, 70, 130, 50, 30, NULL);
	m_config_et_name.SetWindowPos(NULL, 120, 125, 230, 30, NULL);
	m_st_token_num.SetWindowPos(NULL, 420, 130, 80, 30, NULL);
	m_config_et_token_num.SetWindowPos(NULL, 500, 125, 60, 30, NULL);
	m_config_ls_token.SetWindowPos(NULL, 180, 170, 380, 180, NULL);


	m_new_bt_save.SetWindowPos(NULL, 70, 240, 80, 40, NULL);
	m_new_bt_reset.SetWindowPos(NULL, 70, 180, 80, 40, NULL);
	m_new_bt_token_add.SetWindowPos(NULL, 70, 300, 80, 40, NULL);
	m_new_et_name.SetWindowPos(NULL, 120, 125, 230, 30, NULL);
	m_new_et_token_num.SetWindowPos(NULL, 500, 125, 60, 30, NULL);
	
	m_new_ls_token.SetWindowPos(NULL, 180, 170, 380, 180, NULL);
}

void CCloudDiskDlg::showmain()
{
	m_st_token_num.ShowWindow(SW_HIDE);
	m_st_user_name.ShowWindow(SW_HIDE);

	m_main_bt_refresh.ShowWindow(SW_SHOW);
	m_main_bt_upload.ShowWindow(SW_SHOW);
	m_main_bt_download.ShowWindow(SW_SHOW);
	m_main_ls_file.ShowWindow(SW_SHOW);

	m_trans_bt_up.ShowWindow(SW_HIDE);
	m_trans_bt_down.ShowWindow(SW_HIDE);
	m_trans_ls_up.ShowWindow(SW_HIDE);
	m_trans_ls_down.ShowWindow(SW_HIDE);

	m_config_bt_load.ShowWindow(SW_HIDE);
	m_config_bt_save.ShowWindow(SW_HIDE);
	m_config_et_name.ShowWindow(SW_HIDE);
	m_config_et_token_num.ShowWindow(SW_HIDE);
	m_config_ls_token.ShowWindow(SW_HIDE);

	m_new_bt_reset.ShowWindow(SW_HIDE);
	m_new_bt_save.ShowWindow(SW_HIDE);
	m_new_bt_token_add.ShowWindow(SW_HIDE);
	m_new_et_name.ShowWindow(SW_HIDE);
	m_new_et_token_num.ShowWindow(SW_HIDE);
	m_new_et_token_add.ShowWindow(SW_HIDE);
	m_new_ls_token.ShowWindow(SW_HIDE);
}

void CCloudDiskDlg::showtrans()
{
	m_st_token_num.ShowWindow(SW_HIDE);
	m_st_user_name.ShowWindow(SW_HIDE);

	m_main_bt_refresh.ShowWindow(SW_HIDE);
	m_main_bt_upload.ShowWindow(SW_HIDE);
	m_main_bt_download.ShowWindow(SW_HIDE);
	m_main_ls_file.ShowWindow(SW_HIDE);

	m_trans_bt_up.ShowWindow(SW_SHOW);
	m_trans_bt_down.ShowWindow(SW_SHOW);
	if (!m_trans_bt_down.IsWindowEnabled())
	{
		m_trans_ls_up.ShowWindow(SW_HIDE);
		m_trans_ls_down.ShowWindow(SW_SHOW);
	}
	else
	{
		m_trans_ls_up.ShowWindow(SW_SHOW);
		m_trans_ls_down.ShowWindow(SW_HIDE);
	}

	m_config_bt_load.ShowWindow(SW_HIDE);
	m_config_bt_save.ShowWindow(SW_HIDE);
	m_config_et_name.ShowWindow(SW_HIDE);
	m_config_et_token_num.ShowWindow(SW_HIDE);
	m_config_ls_token.ShowWindow(SW_HIDE);

	m_new_bt_reset.ShowWindow(SW_HIDE);
	m_new_bt_save.ShowWindow(SW_HIDE);
	m_new_bt_token_add.ShowWindow(SW_HIDE);
	m_new_et_name.ShowWindow(SW_HIDE);
	m_new_et_token_num.ShowWindow(SW_HIDE);
	m_new_et_token_add.ShowWindow(SW_HIDE);
	m_new_ls_token.ShowWindow(SW_HIDE);
}

void CCloudDiskDlg::showconfig()
{
	m_st_token_num.ShowWindow(SW_SHOW);
	m_st_user_name.ShowWindow(SW_SHOW);

	m_main_bt_refresh.ShowWindow(SW_HIDE);
	m_main_bt_upload.ShowWindow(SW_HIDE);
	m_main_bt_download.ShowWindow(SW_HIDE);
	m_main_ls_file.ShowWindow(SW_HIDE);

	m_trans_bt_up.ShowWindow(SW_HIDE);
	m_trans_bt_down.ShowWindow(SW_HIDE);
	m_trans_ls_up.ShowWindow(SW_HIDE);
	m_trans_ls_down.ShowWindow(SW_HIDE);

	m_config_bt_load.ShowWindow(SW_SHOW);
	m_config_bt_save.ShowWindow(SW_SHOW);
	m_config_et_name.ShowWindow(SW_SHOW);
	m_config_et_token_num.ShowWindow(SW_SHOW);
	m_config_ls_token.ShowWindow(SW_SHOW);

	m_new_bt_reset.ShowWindow(SW_HIDE);
	m_new_bt_save.ShowWindow(SW_HIDE);
	m_new_bt_token_add.ShowWindow(SW_HIDE);
	m_new_et_name.ShowWindow(SW_HIDE);
	m_new_et_token_num.ShowWindow(SW_HIDE);
	m_new_et_token_add.ShowWindow(SW_HIDE);
	m_new_ls_token.ShowWindow(SW_HIDE);
}

void CCloudDiskDlg::shownew()
{
	m_st_token_num.ShowWindow(SW_SHOW);
	m_st_user_name.ShowWindow(SW_SHOW);

	m_main_bt_refresh.ShowWindow(SW_HIDE);
	m_main_bt_upload.ShowWindow(SW_HIDE);
	m_main_bt_download.ShowWindow(SW_HIDE);
	m_main_ls_file.ShowWindow(SW_HIDE);

	m_trans_bt_up.ShowWindow(SW_HIDE);
	m_trans_bt_down.ShowWindow(SW_HIDE);
	m_trans_ls_up.ShowWindow(SW_HIDE);
	m_trans_ls_down.ShowWindow(SW_HIDE);

	m_config_bt_load.ShowWindow(SW_HIDE);
	m_config_bt_save.ShowWindow(SW_HIDE);
	m_config_et_name.ShowWindow(SW_HIDE);
	m_config_et_token_num.ShowWindow(SW_HIDE);
	m_config_ls_token.ShowWindow(SW_HIDE);

	m_new_bt_reset.ShowWindow(SW_SHOW);
	m_new_bt_save.ShowWindow(SW_SHOW);
	m_new_bt_token_add.ShowWindow(SW_SHOW);
	m_new_et_name.ShowWindow(SW_SHOW);
	m_new_et_token_num.ShowWindow(SW_SHOW);
	m_new_et_token_add.ShowWindow(SW_HIDE);
	m_new_ls_token.ShowWindow(SW_SHOW);

	
}

void CCloudDiskDlg::hideall()
{
	m_st_token_num.ShowWindow(SW_HIDE);
	m_st_user_name.ShowWindow(SW_HIDE);

	m_main_bt_refresh.ShowWindow(SW_HIDE);
	m_main_bt_upload.ShowWindow(SW_HIDE);
	m_main_bt_download.ShowWindow(SW_HIDE);
	m_main_ls_file.ShowWindow(SW_HIDE);

	m_trans_bt_up.ShowWindow(SW_HIDE);
	m_trans_bt_down.ShowWindow(SW_HIDE);
	m_trans_ls_up.ShowWindow(SW_HIDE);
	m_trans_ls_down.ShowWindow(SW_HIDE);

	m_config_bt_load.ShowWindow(SW_HIDE);
	m_config_bt_save.ShowWindow(SW_HIDE);
	m_config_et_name.ShowWindow(SW_HIDE);
	m_config_et_token_num.ShowWindow(SW_HIDE);
	m_config_ls_token.ShowWindow(SW_HIDE);

	m_new_bt_reset.ShowWindow(SW_HIDE);
	m_new_bt_save.ShowWindow(SW_HIDE);
	m_new_bt_token_add.ShowWindow(SW_HIDE);
	m_new_et_name.ShowWindow(SW_HIDE);
	m_new_et_token_num.ShowWindow(SW_HIDE);
	m_new_et_token_add.ShowWindow(SW_HIDE);
	m_new_ls_token.ShowWindow(SW_HIDE);


}

void CCloudDiskDlg::synctoken()
{
	if (!m_token_list_valid)
		return;
	CString tmp;
	m_config_ls_token.DeleteAllItems();
	m_new_ls_token.DeleteAllItems();
	m_config_et_name.SetWindowTextW(m_config->username);
	m_new_et_name.SetWindowTextW(m_config->username);
	tmp.Format(L"%d", m_config->tokennum);
	m_config_et_token_num.SetWindowTextW(tmp);
	m_new_et_token_num.SetWindowTextW(tmp);
	for (int i = 0; i < m_config->tokennum; i++)
	{
		tmp.Format(L"%d", i + 1);
		m_config_ls_token.InsertItem(i, tmp);
		m_config_ls_token.SetItemText(i, 1, m_config->token[i]);
		m_new_ls_token.InsertItem(i, tmp);
		m_new_ls_token.SetItemText(i, 1, m_config->token[i]);
	}
	m_token_list_valid = FALSE;
}

void CCloudDiskDlg::syncfile()
{
	CString tmp;
	CItem *file;
	int i = 0;
	m_main_ls_file.DeleteAllItems();
	file = m_config->filehead->pnextfile;
	while (file)
	{
		tmp.Format(L"%d", i + 1);
		m_main_ls_file.InsertItem(i, tmp);
		m_main_ls_file.SetItemText(i, 1, file->filename);
		file = file->pnextfile;
		i++;
	}
}

void CCloudDiskDlg::synctrans()
{
	CString tmp;
	TransFile *file;
	int process;
	int i = 0;
	m_trans_ls_down.DeleteAllItems();
	m_trans_ls_up.DeleteAllItems();

	file = m_trans_down->head->next;
	while (file)
	{
		m_trans_ls_down.InsertItem(i, file->filename);
		process = 0;
		for (int j = 0; j < file->childnum; j++)
		{
			process += file->childprocess[j];
		}
		if (file->error == TRUE)
		{
			tmp = L"传输错误";
			m_trans_ls_down.SetItemText(i, 1, tmp);
			file = file->next;
			continue;
		}
		process /= file->childnum;
		if (process == 100)
		{
			//if (!file->completed)
				m_trans_ls_down.SetItemText(i, 1, L"下载完成");
			file->completed = TRUE;
		}
		else
		{
			tmp.Format(L"%d", process);
			m_trans_ls_down.SetItemText(i, 1, tmp);
		}
		i++;
		file = file->next;
	}
	
	file = m_trans_up->head->next;
	while (file)
	{
		m_trans_ls_up.InsertItem(i, file->filename);
		process = 0;
		for (int j = 0; j < file->childnum; j++)
		{
			process += file->childprocess[j];
		}
		if (file->error == TRUE)
		{
			tmp = L"传输错误";
			m_trans_ls_up.SetItemText(i, 1, tmp);
			file = file->next;
			continue;
		}
		process /= file->childnum;
		if (process == 100)
		{
			file->completed = TRUE;
			m_trans_ls_up.SetItemText(i, 1, L"上传完成");
		}
		else
		{
			tmp.Format(L"%d", process);
			m_trans_ls_up.SetItemText(i, 1, tmp);
		}
		i++;
		file = file->next;
	}
}

//TRANS按钮处理
void CCloudDiskDlg::OnBnClickedTransBtUp()
{
	m_trans_bt_up.EnableWindow(FALSE);
	m_trans_bt_down.EnableWindow(TRUE);
	m_trans_ls_down.ShowWindow(SW_HIDE);
	m_trans_ls_up.ShowWindow(SW_SHOW);
	/*for (int i = 0; i < 600; i += 1)
	{
		m_trans_ls_up.SetWindowPos(NULL, 80 + i - 600, 120, 400, 250, SWP_SHOWWINDOW);
		m_trans_ls_down.SetWindowPos(NULL, 680 + i - 600, 120, 400, 250, SWP_SHOWWINDOW);
	}*/
	// TODO:  在此添加控件通知处理程序代码
}


void CCloudDiskDlg::OnBnClickedTransBtDown()
{
	m_trans_bt_up.EnableWindow(TRUE);
	m_trans_bt_down.EnableWindow(FALSE);
	m_trans_ls_up.ShowWindow(SW_HIDE);
	m_trans_ls_down.ShowWindow(SW_SHOW);
	/*for (int i = 0; i < 600; i += 1)
	{
		m_trans_ls_up.SetWindowPos(NULL, 80 - i, 120, 400, 250, SWP_SHOWWINDOW);
		m_trans_ls_down.SetWindowPos(NULL, 680 - i, 120, 400, 250, SWP_SHOWWINDOW);
	}*/
	// TODO:  在此添加控件通知处理程序代码
}


void CCloudDiskDlg::OnBnClickedNewBtSave()
{
	CString name;
	m_new_et_name.GetWindowTextW(name);
	m_config->set_user_name(name);
	m_token_list_valid = TRUE;
	synctoken();
	MessageBox(L"保存成功", L"提示", MB_OK);

	// TODO:  在此添加控件通知处理程序代码
}


void CCloudDiskDlg::OnBnClickedNewBtTokenAdd()
{
	CString GetToken;
	CString tmp;
	CAuthority dlg;

	//////////////////////获取Token模块
	GetToken = dlg.gettoken();
	//////////////////////////
	
	if (GetToken == L"")
		return;

	m_config->addtoken(GetToken);
	m_token_list_valid = TRUE;
	synctoken();
}


void CCloudDiskDlg::OnBnClickedNewBtReset()
{
	delete m_config;
	m_config = new CLogfile;
	m_token_list_valid = TRUE;
	synctoken();
	// TODO:  在此添加控件通知处理程序代码
}


void CCloudDiskDlg::OnBnClickedConfigBtSave()
{
	CFileDialog save(true);
	save.DoModal();
	CString path = save.GetPathName();
	m_config->savelog(path, 0);
	// TODO:  在此添加控件通知处理程序代码
}


void CCloudDiskDlg::OnBnClickedConfigBtLoad()
{
	CFileDialog load(true);
	load.DoModal();
	CString path = load.GetPathName();
	m_config->loadlog(path);
	m_token_list_valid = TRUE;
	synctoken();
	syncfile();
	// TODO:  在此添加控件通知处理程序代码
}


void CCloudDiskDlg::OnNMRClickMainLsFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		CMenu menu;
		menu.LoadMenu(IDR_MAIN_FILE_MENU);
		CMenu* popup = menu.GetSubMenu(0);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void ctldownload(FileBag *bag)
{
	TransFile *file = bag->file;
	CCloudDiskDlg *dlg = bag->dlg;
	CString filename = file->filename;

	CString part1(filename + L"part1");
	CString part2(filename + L"part2");
	CString part3(filename + L"part3");
	CString part4(filename + L"part4");
	CString part5(filename + L"part5");
	CString part6(filename + L"part6");
	CString *part[6] = { &part1, &part2, &part3, &part4, &part5, &part6 };

	char hehe1[128] = { 0 };
	char hehe2[128] = { 0 };
	char hehe3[128] = { 0 };
	char hehe4[128] = { 0 };
	char hehe5[128] = { 0 };
	char hehe6[128] = { 0 };
	char *hehe[6] = { hehe1, hehe2, hehe3, hehe4, hehe5, hehe6 };

	HANDLE *thread = new HANDLE[dlg->m_config->tokennum];

	FileBag tmp;
	tmp.dlg = dlg;
	tmp.file = file;

	for (int i = 0; i < dlg->m_config->tokennum; i++)
	{
		tmp.path = *(part[i]);
		tmp.index = i;
		thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)download, &tmp, 0, NULL);
		//WaitForSingleObject(thread[i], INFINITE); //是否启用多线程
		Sleep(100);
	}

	int k = 0;

	while (!file->completed)
	{
		if (file->error)
		{
			k++;
			if (k <= 2)
			{
				file->error = FALSE;
				continue;
			}
			for (int i = 0; i < dlg->m_config->tokennum; i++)
			{
				TerminateThread(thread[i], 0);
			}
			break;
		}
		Sleep(1000);
	}
	CFile open;
	if (!file->error)
	{
		for (int i = 0,j=0; i < dlg->m_config->tokennum - k; i++,j++)
		{
			while (!open.Open(*part[j], CFile::readOnly))
			{
				j++;
			}
			open.Close();
			::WideCharToMultiByte(0, 0, part[j]->GetBuffer(), part[j]->GetLength(), hehe[i], 128, NULL, NULL);
		}
	}
	file_recover(hehe, 4);
	for (int i = 0; i < dlg->m_config->tokennum - k; i++)
	{
		remove(hehe[i]);
	}

	delete bag;
}


afx_msg LRESULT CCloudDiskDlg::OnDownloadFile(WPARAM wParam, LPARAM lParam)
{
	CItem *file;
	file = m_config->getAT(wParam);

	if (!file)
		return FALSE;
	CString name = file->filename;

	TransFile *dfile = new TransFile;
	dfile->childnum = m_config->tokennum;
	dfile->filename = name;
	m_trans_down->addfile(dfile);
	synctrans();

	FileBag *tmp = new FileBag;
	tmp->dlg = this;
	tmp->file = dfile;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ctldownload, tmp, 0, NULL);
	
	return 0;
}



void CCloudDiskDlg::OnDownload()
{
	int i, iState;
	int nItemSelected = m_main_ls_file.GetSelectedCount();
	int nItemCount = m_main_ls_file.GetItemCount();

	if (nItemSelected<1)
		return;

	for (i = nItemCount - 1; i >= 0; i--)
	{
		iState = m_main_ls_file.GetItemState(i, LVIS_SELECTED);
		if (iState != 0)
		{
			PostMessage(WM_DOWNLOAD_FILE, i + 1, 0);
			return;
		}
	}
	// TODO:  在此添加命令处理程序代码
}


void upload(FileBag* bag)
{
	CCloudDiskDlg *dlg = bag->dlg;

	TransFile *file = bag->file;
	CString name = bag->file->filename;
	CString path = bag->path;
	CString token = bag->dlg->m_config->token[bag->index];
	DWORD *process = &(bag->file->childprocess[bag->index]);
	if (!baidu_upload(path, token, name, process))
		file->error = TRUE;
	dlg->PostMessageW(WM_UPLOAD_COMPLETE, 0, 0);

	return;
}



void download(FileBag* bag)
{
	CCloudDiskDlg *dlg = bag->dlg;
	TransFile *file = bag->file;
	CString name = bag->file->filename;
	CString path = bag->path;
	CString token = dlg->m_config->token[bag->index];
	DWORD *process = &(bag->file->childprocess[bag->index]);
	if (!baidu_download(path, token, name, process))
		file->error = TRUE;
	dlg->synctrans();
}


void monitor(CCloudDiskDlg* dlg)
{
	DWORD process;
	TransFile *file;
	CString tmp;
	while (true)
	{
		file = dlg->m_trans_up->head;
		for (int i = 0; i < dlg->m_trans_up->filenum; i++)
		{
			file = file->next;
			if (file->error == TRUE)
			{
				tmp = L"传输错误";
				dlg->m_trans_ls_up.SetItemText(i, 1, tmp);
				continue;
			}			
			if (file->completed)
			{
				dlg->m_trans_ls_up.SetItemText(i, 1, L"上传完成");
			}
			else
			{
				process = 0;
				for (int k = 0; k<file->childnum; k++)
				{
					process += file->childprocess[k];
				}
				process /= file->childnum;
				tmp.Format(L"%d", process);
				dlg->m_trans_ls_up.SetItemText(i, 1, tmp);
			}
			
		}

		file = dlg->m_trans_down->head;
		for (int i = 0; i < dlg->m_trans_down->filenum; i++)
		{
			file = file->next;
			if (file->error == TRUE)
			{
				tmp = L"传输错误";
				dlg->m_trans_ls_down.SetItemText(i, 1, tmp);
				continue;
			}
			if (file->completed)
				continue;
			process = 0;
			for (int k = 0; k<file->childnum; k++)
			{
				process += file->childprocess[k];
			}
			process /= file->childnum;
			tmp.Format(L"%d", process);
			dlg->m_trans_ls_down.SetItemText(i, 1, tmp);
		}

		Sleep(1000);
	}
}

void udct_monitor(CCloudDiskDlg* dlg)
{
	CString tmp;
	TransFile *item;
	int i = 0;

	while (true)
	{
		item = dlg->m_trans_down->head->next;
		i = 0;
		while (item)
		{
			if (item->completed != TRUE)
				i++;
			item = item->next;
		}
		tmp.Format(L"%d", i);

		if (!dlg->indexleft->m_show)
		{
			dlg->m_st_download_ct.ShowWindow(SW_HIDE);
			dlg->m_st_download_ct.SetWindowTextW(tmp);
			dlg->m_st_download_ct.ShowWindow(SW_SHOW);
		}

		item = dlg->m_trans_up->head->next;
		i = 0;
		while (item)
		{
			if (item->completed != TRUE)
				i++;
			item = item->next;
		}
		tmp.Format(L"%d", i);
		if (!dlg->indexleft->m_show)
		{
			dlg->m_st_upload_ct.ShowWindow(SW_HIDE);
			dlg->m_st_upload_ct.SetWindowTextW(tmp);
			dlg->m_st_upload_ct.ShowWindow(SW_SHOW);
		}

		Sleep(1000);
	}
	
}

void ctlupload(FileBag *lppath)
{
	CString path = lppath->path;
	CString name = &path.GetBuffer()[path.ReverseFind('\\') + 1];

	char filename[128] = { 0 };
	::WideCharToMultiByte(0, 0, path.GetBuffer(), path.GetLength(), filename, 128, NULL, NULL);

	char hehe1[128] = "part1";
	char hehe2[128] = "part2";
	char hehe3[128] = "part3";
	char hehe4[128] = "part4";
	char hehe5[128] = "part5";
	char hehe6[128] = "part6";
	char *hehe[6] = { hehe1, hehe2, hehe3, hehe4, hehe5, hehe6 };


	TransFile *file = new TransFile;
	file->childnum = lppath->dlg->m_config->tokennum;
	file->filename = name;
	lppath->dlg->m_trans_up->addfile(file);
	lppath->dlg->synctrans();

	file_divide(filename, hehe, 6);


	CString part1(L"part1" + name);
	CString part2(L"part2" + name);
	CString part3(L"part3" + name);
	CString part4(L"part4" + name);
	CString part5(L"part5" + name);
	CString part6(L"part6" + name);

	CString *part[6] = { &part1, &part2, &part3, &part4, &part5, &part6 };

	HANDLE *thread = new HANDLE[lppath->dlg->m_config->tokennum];
	FileBag tmp;
	tmp.dlg = lppath->dlg;
	tmp.file = file;

	for (int i = 0; i < lppath->dlg->m_config->tokennum; i++)
	{
		tmp.path = *(part[i]);
		tmp.index = i;
		thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)upload, &tmp, 0, NULL);
		//WaitForSingleObject(thread[i], INFINITE); //是否启用多线程
		Sleep(100);
	}

	while (!file->completed)
	{
		if (file->error)
		{
			for (int i = 0; i < lppath->dlg->m_config->tokennum; i++)
			{
				TerminateThread(thread[i], 0);
			}
			break;
		}
		Sleep(1000);
	}

	for (int i = 0; i < lppath->dlg->m_config->tokennum; i++)
	{
		DeleteObject(thread[i]);
	}

	CFile fp;
	for (int i = 0; i < 6; i++)
	{
		fp.Remove(*(part[i]));
	}

	delete lppath;
}

void CCloudDiskDlg::OnBnClickedMainUpload()
{
	CFileDialog open(true);
	open.DoModal();
	CString path = open.GetPathName();
	FileBag *tmp = new FileBag;
	tmp->dlg = this;
	tmp->path = path;

	if (path == L"")
		return;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ctlupload, tmp, 0, NULL);

	
	// TODO:  在此添加控件通知处理程序代码
}


void CCloudDiskDlg::OnBnClickedMainRefresh()
{
	syncfile();
}


afx_msg LRESULT CCloudDiskDlg::OnUploadComplete(WPARAM wParam, LPARAM lParam)
{
	TransFile *tmp;
	CItem *save;
	synctrans();
	tmp = m_trans_up->head->next;

	while (tmp)
	{
		if (tmp->saved == FALSE && tmp->completed == TRUE)
		{
			save = new CItem;
			save->filename = tmp->filename;
			save->piecenum = 0;
			save->pnextfile = NULL;
			for (int i = 0; i < m_config->tokennum; i++)
			{
				save->appendToken(m_config->token[i]);
			}
			m_config->appendFile(save);
			tmp->saved = TRUE;
		}
		tmp = tmp->next;
	}

	return 0;
}


void CCloudDiskDlg::OnBnClickedMainDownload()
{
	OnDownload();
	// TODO:  在此添加控件通知处理程序代码
}
