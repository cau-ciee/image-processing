// EdgeDetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fyf.h"
#include "EdgeDetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdgeDetDlg dialog


CEdgeDetDlg::CEdgeDetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEdgeDetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEdgeDetDlg)
	m_mode = -1;
	//}}AFX_DATA_INIT
}


void CEdgeDetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEdgeDetDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_mode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEdgeDetDlg, CDialog)
	//{{AFX_MSG_MAP(CEdgeDetDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdgeDetDlg message handlers

void CEdgeDetDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);	
	CDialog::OnOK();
}

void CEdgeDetDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_mode = 0;
	UpdateData(false);	
}

void CEdgeDetDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_mode = 1;
	UpdateData(false);	
}
