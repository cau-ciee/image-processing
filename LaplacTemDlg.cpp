// LaplacTemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fyf.h"
#include "LaplacTemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLaplacTemDlg dialog


CLaplacTemDlg::CLaplacTemDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CLaplacTemDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CLaplacTemDlg)
  m_laplac = -1;

  //}}AFX_DATA_INIT
}


void CLaplacTemDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CLaplacTemDlg)
  DDX_Radio(pDX, IDC_RADIO1, m_laplac);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLaplacTemDlg, CDialog)
  //{{AFX_MSG_MAP(CLaplacTemDlg)
  ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
  ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLaplacTemDlg message handlers

void CLaplacTemDlg::OnOK() 
{
  // TODO: Add extra validation here
  UpdateData(true);
  //调用默认的对话框处理函数  
  CDialog::OnOK();
}


void CLaplacTemDlg::OnRadio1() 
{
  // TODO: Add your control notification handler code here
  m_laplac = 0;
  laplacvalue[0]=0;
  laplacvalue[1]=1;
  laplacvalue[2]=0;
  laplacvalue[3]=1;
  laplacvalue[4]=4;
  laplacvalue[5]=1;
  laplacvalue[6]=0;
  laplacvalue[7]=1;
  laplacvalue[8]=0; 
}

void CLaplacTemDlg::OnRadio2() 
{
  // TODO: Add your control notification handler code here
  m_laplac = 1;
  laplacvalue[0]=-1;
  laplacvalue[1]=-1;
  laplacvalue[2]=-1;
  laplacvalue[3]=-1;
  laplacvalue[4]= 8;
  laplacvalue[5]=-1;
  laplacvalue[6]=-1;
  laplacvalue[7]=-1;
  laplacvalue[8]=-1;  
}
