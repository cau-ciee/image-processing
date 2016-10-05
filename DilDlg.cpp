// DilDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fyf.h"
#include "DilDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDilDlg dialog


CDilDlg::CDilDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CDilDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDilDlg)
  m_type = -1;
  m_num = -1;
  numvalue = 3;
  //}}AFX_DATA_INIT
}


void CDilDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDilDlg)
  DDX_Radio(pDX, IDC_RADIO1, m_type);
  DDX_Radio(pDX, IDC_RADIO3, m_num);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDilDlg, CDialog)
  //{{AFX_MSG_MAP(CDilDlg)
  ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
  ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
  ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
  ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
  ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDilDlg message handlers

void CDilDlg::OnRadio1() 
{
  // TODO: Add your control notification handler code here
  m_type = 0;
  UpdateData(FALSE);  
}

void CDilDlg::OnRadio2() 
{
  // TODO: Add your control notification handler code here
  m_type = 1;
  UpdateData(FALSE);  
}

void CDilDlg::OnRadio3() 
{
  // TODO: Add your control notification handler code here
  m_num = 0;
  numvalue= 3;
  UpdateData(FALSE);  
}

void CDilDlg::OnRadio4() 
{
  // TODO: Add your control notification handler code here
  m_num = 1;
  numvalue= 5;
  UpdateData(FALSE);  
}

void CDilDlg::OnRadio5() 
{
  // TODO: Add your control notification handler code here
  m_num = 2;
  numvalue= 7;
  UpdateData(FALSE);  
}

void CDilDlg::OnOK() 
{
  // TODO: Add extra validation here
  UpdateData(true); 
  CDialog::OnOK();
}
