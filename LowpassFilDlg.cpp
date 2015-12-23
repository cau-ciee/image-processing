// LowpassFilDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fyf.h"
#include "LowpassFilDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLowpassFilDlg dialog


CLowpassFilDlg::CLowpassFilDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLowpassFilDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLowpassFilDlg)
	m_lowfreq2 = 0;
	m_lowfreq1 = 0;
	//}}AFX_DATA_INIT
}


void CLowpassFilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLowpassFilDlg)
	DDX_Text(pDX, IDC_EDIT2, m_lowfreq2);
	DDX_Text(pDX, IDC_EDIT1, m_lowfreq1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLowpassFilDlg, CDialog)
	//{{AFX_MSG_MAP(CLowpassFilDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLowpassFilDlg message handlers

void CLowpassFilDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	if(m_lowfreq1>255||m_lowfreq1<0||m_lowfreq2>255||m_lowfreq2<0)
	{
		AfxMessageBox ("所设频率参数不正确!",MB_OK);
		return;
	}
		
	CDialog::OnOK();
}
