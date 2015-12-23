// ThreDivDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fyf.h"
#include "ThreDivDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreDivDlg dialog


CThreDivDlg::CThreDivDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreDivDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CThreDivDlg)
	m_threshold = 0;
	m_type = 0;
	//}}AFX_DATA_INIT
}


void CThreDivDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThreDivDlg)
	DDX_Control(pDX, IDC_EDIT1, m_visible);
	DDX_Text(pDX, IDC_EDIT1, m_threshold);
	DDX_Radio(pDX, IDC_RADIO1, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThreDivDlg, CDialog)
	//{{AFX_MSG_MAP(CThreDivDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreDivDlg message handlers


void CThreDivDlg::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData(TRUE);
	if(m_threshold>255||m_threshold<0)
	{
		AfxMessageBox ("所设频率参数不正确!",MB_OK);
		return;
	}
	CDialog::OnOK();
}

void CThreDivDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_type = 0;
	UpdateData(FALSE);
	m_visible.EnableWindow(true);	
}

void CThreDivDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_type = 1;
	UpdateData(FALSE);
	m_visible.EnableWindow(false);	
}
