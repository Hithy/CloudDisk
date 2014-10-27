// IndexLeft.cpp : 实现文件
//

#include "stdafx.h"
#include "CloudDisk.h"
#include "IndexLeft.h"

#include "afxdialogex.h"


// CIndexLeft 对话框

IMPLEMENT_DYNAMIC(CIndexLeft, CDialogEx)

CIndexLeft::CIndexLeft(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIndexLeft::IDD, pParent)
{
}

CIndexLeft::~CIndexLeft()
{
}

void CIndexLeft::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INDEX_BACK, m_index_back);
	DDX_Control(pDX, IDC_INDEX_TRANS, m_index_trans);
	DDX_Control(pDX, IDC_INDEX_NEW, m_index_new);
	DDX_Control(pDX, IDC_INDEX_CONFIG, m_index_config);
	DDX_Control(pDX, IDC_INDEX_ABOUT, m_index_about);
}


BEGIN_MESSAGE_MAP(CIndexLeft, CDialogEx)
	ON_BN_CLICKED(IDC_INDEX_BACK, &CIndexLeft::OnBnClickedIndexBack)
//	ON_WM_SHOWWINDOW()
ON_MESSAGE(WM_SHOWCTL, &CIndexLeft::OnShowctl)
ON_MESSAGE(WM_HIDECTL, &CIndexLeft::OnHidectl)
ON_MESSAGE(WM_SHOWIMGTMP, &CIndexLeft::OnShowimgtmp)
ON_BN_CLICKED(IDC_INDEX_TRANS, &CIndexLeft::OnBnClickedIndexTrans)
ON_BN_CLICKED(IDC_INDEX_NEW, &CIndexLeft::OnBnClickedIndexNew)
ON_BN_CLICKED(IDC_INDEX_CONFIG, &CIndexLeft::OnBnClickedIndexConfig)
END_MESSAGE_MAP()


// CIndexLeft 消息处理程序


void CIndexLeft::OnBnClickedIndexBack()
{
	//m_show = FALSE;

	m_index_right->PostMessageW(WM_SHOWIMG, 0, 0);
	//this->GetParent()->PostMessageW(WM_SHOWWND, IDC_INDEX_BACK, 0);
	this->GetParent()->PostMessageW(WM_INDEX_TO_MAIN, IDC_INDEX_BACK, 0);
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CIndexLeft::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	m_hInstance = AfxGetApp()->m_hInstance;
	//img_left.LoadFromResource(m_hInstance, IDB_TRANS_NM);
	m_index_trans.LoadBitmaps(IDB_TRANS_NM);
	m_index_new.LoadBitmaps(IDB_NEW_NM);
	m_index_about.LoadBitmaps(IDB_ABOUT_NM);
	m_index_config.LoadBitmaps(IDB_CONFIG_NM);
	m_index_back.LoadBitmaps(IDB_BACK_NM);

	m_index_back.SetWindowPos(NULL, 0, 345, 180, 40, NULL);
	m_index_trans.SetWindowPos(NULL, 0, 100, 180, 40, NULL);
	m_index_new.SetWindowPos(NULL, 0, 140, 180, 40, NULL);
	m_index_config.SetWindowPos(NULL, 0, 180, 180, 40, NULL);
	m_index_about.SetWindowPos(NULL, 0, 220, 180, 40, NULL);

	m_index_back.m_IID = IDC_INDEX_BACK;
	m_index_config.m_IID = IDC_INDEX_CONFIG;
	m_index_about.m_IID = IDC_INDEX_ABOUT;
	m_index_new.m_IID = IDC_INDEX_NEW;
	m_index_trans.m_IID = IDC_INDEX_TRANS;

	/*m_index_back.m_parent = this;
	m_index_config.m_parent = this;
	m_index_about.m_parent = this;
	m_index_new.m_parent = this;
	m_index_trans.m_parent = this;*/

	m_index_trans.m_img_nm = IDB_TRANS_NM;
	m_index_trans.m_img_ov = IDB_TRANS_OV;
	m_index_back.m_img_nm = IDB_BACK_NM;
	m_index_back.m_img_ov = IDB_BACK_OV;
	m_index_new.m_img_nm = IDB_NEW_NM;
	m_index_new.m_img_ov = IDB_NEW_OV;
	m_index_config.m_img_nm = IDB_CONFIG_NM;
	m_index_config.m_img_ov = IDB_CONFIG_OV;
	m_index_about.m_img_nm = IDB_ABOUT_NM;
	m_index_about.m_img_ov = IDB_ABOUT_OV;
	// TODO:  在此添加额外的初始化
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



afx_msg LRESULT CIndexLeft::OnShowctl(WPARAM wParam, LPARAM lParam)
{
	m_index_about.ShowWindow(SW_SHOW);
	m_index_new.ShowWindow(SW_SHOW);
	m_index_back.ShowWindow(SW_SHOW);
	m_index_trans.ShowWindow(SW_SHOW);
	m_index_config.ShowWindow(SW_SHOW);
	return 0;
}


afx_msg LRESULT CIndexLeft::OnHidectl(WPARAM wParam, LPARAM lParam)
{
	m_index_about.ShowWindow(SW_HIDE);
	m_index_new.ShowWindow(SW_HIDE);
	m_index_back.ShowWindow(SW_HIDE);
	m_index_trans.ShowWindow(SW_HIDE);
	m_index_config.ShowWindow(SW_HIDE);
	return 0;
}


afx_msg LRESULT CIndexLeft::OnShowimgtmp(WPARAM wParam, LPARAM lParam)
{
	//if (m_show)
	//{
		m_index_right->PostMessageW(WM_SHOWIMG, wParam, lParam);
	//}
	return 0;
}


void CIndexLeft::OnBnClickedIndexTrans()
{
	m_index_right->PostMessageW(WM_SHOWIMG, 0, 0);
	//this->GetParent()->PostMessageW(WM_SHOWWND, IDC_INDEX_TRANS, 0);
	this->GetParent()->PostMessageW(WM_INDEX_TO_MAIN, IDC_INDEX_TRANS, 0);
	//m_index_right->PostMessageW(WM_SHOWIMG, 1007, 1);
	// TODO:  在此添加控件通知处理程序代码
}


void CIndexLeft::OnBnClickedIndexNew()
{
	m_index_right->PostMessageW(WM_SHOWIMG, 0, 0);
	//this->GetParent()->PostMessageW(WM_SHOWWND, IDC_INDEX_NEW, 0);
	this->GetParent()->PostMessageW(WM_INDEX_TO_MAIN, IDC_INDEX_NEW, 0);
	// TODO:  在此添加控件通知处理程序代码
}


void CIndexLeft::OnBnClickedIndexConfig()
{
	m_index_right->PostMessageW(WM_SHOWIMG, 0, 0);
	//this->GetParent()->PostMessageW(WM_SHOWWND, IDC_INDEX_CONFIG, 0);
	this->GetParent()->PostMessageW(WM_INDEX_TO_MAIN, IDC_INDEX_CONFIG, 0);
	// TODO:  在此添加控件通知处理程序代码
}
