// HigpassFilDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fyf.h"
#include "HigpassFilDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHigpassFilDlg dialog


CHigpassFilDlg::CHigpassFilDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHigpassFilDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHigpassFilDlg)
	m_highfreq1 = 0;
	m_highfreq2 = 0;
	//}}AFX_DATA_INIT
}


void CHigpassFilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHigpassFilDlg)
	DDX_Text(pDX, IDC_EDIT1, m_highfreq1);
	DDX_Text(pDX, IDC_EDIT2, m_highfreq2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHigpassFilDlg, CDialog)
	//{{AFX_MSG_MAP(CHigpassFilDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHigpassFilDlg message handlers

void CHigpassFilDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	if(m_highfreq1>255||m_highfreq1<0||m_highfreq2>255||m_highfreq2<0)
	{
		AfxMessageBox ("所设频率参数不正确!",MB_OK);
		return;
	}
		
	CDialog::OnOK();
}
