// CloseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fyf.h"
#include "CloseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCloseDlg dialog


CCloseDlg::CCloseDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CCloseDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CCloseDlg)
  m_type = -1;
  m_num = -1;
  numvalue = 3;
  //}}AFX_DATA_INIT
}


void CCloseDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CCloseDlg)
  DDX_Radio(pDX, IDC_RADIO1, m_type);
  DDX_Radio(pDX, IDC_RADIO3, m_num);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCloseDlg, CDialog)
  //{{AFX_MSG_MAP(CCloseDlg)
  ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
  ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
  ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
  ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
  ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloseDlg message handlers

void CCloseDlg::OnRadio1() 
{
  // TODO: Add your control notification handler code here
  m_type = 0;
  UpdateData(FALSE);  
}

void CCloseDlg::OnRadio2() 
{
  // TODO: Add your control notification handler code here
  m_type = 1;
  UpdateData(FALSE);  
}

void CCloseDlg::OnRadio3() 
{
  // TODO: Add your control notification handler code here
  m_num = 0;
  numvalue= 3;
  UpdateData(FALSE);  
}

void CCloseDlg::OnRadio4() 
{
  // TODO: Add your control notification handler code here
  m_num = 1;
  numvalue= 5;
  UpdateData(FALSE);  
}

void CCloseDlg::OnRadio5() 
{
  // TODO: Add your control notification handler code here
  m_num = 2;
  numvalue= 7;
  UpdateData(FALSE);  
}

void CCloseDlg::OnOK() 
{
  // TODO: Add extra validation here
    UpdateData(true);
  CDialog::OnOK();
}
