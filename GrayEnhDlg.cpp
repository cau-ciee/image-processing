// GrayEnhDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FYF.h"
#include "GrayEnhDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrayEnhDlg dialog


CGrayEnhDlg::CGrayEnhDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGrayEnhDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrayEnhDlg)
	m_oralow = 0;
	m_orahig = 0;
	m_newhig = 0;
	m_newlow = 0;
	//}}AFX_DATA_INIT
}


void CGrayEnhDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrayEnhDlg)
	DDX_Text(pDX, IDC_EDIT1, m_oralow);
	DDX_Text(pDX, IDC_EDIT2, m_orahig);
	DDX_Text(pDX, IDC_EDIT3, m_newhig);
	DDX_Text(pDX, IDC_EDIT4, m_newlow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrayEnhDlg, CDialog)
	//{{AFX_MSG_MAP(CGrayEnhDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrayEnhDlg message handlers

void CGrayEnhDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	// 判断设置是否有效
	if ((m_oralow < 0) || (m_orahig > 255) ||(m_oralow > m_orahig)||
		(m_newlow < 0) || (m_newhig > 255)||(m_newlow > m_newhig))
	{
		// 提示用户参数设置错误
		MessageBox("参数设置错误！", "系统提示" , MB_ICONINFORMATION | MB_OK);
		
		// 返回
		return;
	}
		
	CDialog::OnOK();
}
