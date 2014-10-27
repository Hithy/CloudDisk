// Authority.cpp : 实现文件
//

#include "stdafx.h"
#include "CloudDisk.h"
#include "Authority.h"
#include "afxdialogex.h"
#include <MsHTML.h>


// CAuthority 对话框

IMPLEMENT_DYNAMIC(CAuthority, CDialogEx)

CAuthority::CAuthority(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAuthority::IDD, pParent)
{

}

CAuthority::~CAuthority()
{
}

void CAuthority::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
}


BEGIN_MESSAGE_MAP(CAuthority, CDialogEx)
END_MESSAGE_MAP()


// CAuthority 消息处理程序


BOOL CAuthority::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	VARIANT v;
	flag = 0;
	token = L"";
	v.vt = VT_BSTR;
	v.bstrVal = L"http://openapi.baidu.com/oauth/2.0/authorize?response_type=token&client_id=qfOBCu7glinnkfMjOGWRrP0I&redirect_uri=oob&scope=netdisk";
	//m_web.ModifyStyle(WS_HSCROLL | WS_VSCROLL, 0, 0);
	m_web.Navigate2(&v, NULL, NULL, NULL, NULL);

	return TRUE;   // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
BEGIN_EVENTSINK_MAP(CAuthority, CDialogEx)
	ON_EVENT(CAuthority, IDC_EXPLORER1, 259, CAuthority::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()


void CAuthority::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	HRESULT hr;
	LPUNKNOWN lpUnknown;
	LPUNKNOWN lpUnknownWB = NULL;;
	LPUNKNOWN lpUnknownDC = NULL;
	lpUnknown = m_web.GetControlUnknown();
	if (lpUnknown)
	{
		hr = lpUnknown->QueryInterface(IID_IUnknown, (LPVOID*)&lpUnknownWB);

		if (FAILED(hr))
		{
			return;
		}
		hr = pDisp->QueryInterface(IID_IUnknown, (LPVOID*)&lpUnknownDC);

		if (SUCCEEDED(hr) && lpUnknownWB == lpUnknownDC)
		{
			//MessageBox(L"网页加载成功！", NULL, 0);

			CString url1, url2;
			url1 = L"http://openapi.baidu.com/oauth/2.0/authorize?response_type=token&client_id=qfOBCu7glinnkfMjOGWRrP0I&redirect_uri=oob&scope=netdisk";
			url2 = m_web.get_LocationURL();
			if (url1 == url2)
			{
				IDispatch * pDispatch = NULL;
				IHTMLDocument2 * pDoc = NULL;
				IHTMLElement* pBody;
				IHTMLElementCollection * objAllElement = NULL;
				// element collections long nElementCount;
				// the count of elements
				pDispatch = m_web.get_Document();
				ASSERT(pDispatch);
				HRESULT hr = pDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pDoc);
				pDoc->get_all(&objAllElement);
				////////////////////////////////////////////////// IHTMLElement *pBody = NULL;
				//主体
				hr = pDoc->get_body(&pBody);
				ASSERT(SUCCEEDED(hr));
				ASSERT(pBody);// 从body获得IHTMLElement2接口指针，用以访问滚动条
				IHTMLElement2 *plement = NULL;
				hr = pBody->QueryInterface(IID_IHTMLElement2, (void**)&plement);
				IHTMLWindow2* pWnd = NULL;
				pDoc->get_parentWindow(&pWnd);
				pWnd->scrollTo(20, 100);// 这里要滚动的目标位置
				flag = 2;

			}

			else if (flag == 2)
			{
				CString url = m_web.get_LocationURL();

				int posbegin, posend;

				posbegin = url.Find(L"access_token=");
				posbegin += 13;
				posend = url.Find(L"&session_secret");
				posend -= 1;
				token = url.Mid(posbegin, posend - posbegin + 1);
				VARIANT v;
				v.vt = VT_BSTR;
				v.bstrVal = L"	https://passport.baidu.com/?logout";
				m_web.Navigate2(&v, NULL, NULL, NULL, NULL);
				flag = 3;
			}
			else	if (flag == 3)
			{
				flag = 0;
				this->OnOK();
			}
			else
			{
				VARIANT v;
				v.vt = VT_BSTR;
				v.bstrVal = L"	https://passport.baidu.com/?logout";
				m_web.Navigate2(&v, NULL, NULL, NULL, NULL);
				flag = 3;
			}
		}
	}
	// TODO:  在此处添加消息处理程序代码
}


CString CAuthority::gettoken()
{
	this->DoModal();
	return token;
}