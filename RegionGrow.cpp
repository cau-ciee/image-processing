// RegionGrow.cpp : implementation file
//

#include "stdafx.h"
#include "fyf.h"
#include "RegionGrow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegionGrow dialog


CRegionGrow::CRegionGrow(CWnd* pParent /*=NULL*/)
  : CDialog(CRegionGrow::IDD, pParent)
{
  //{{AFX_DATA_INIT(CRegionGrow)
  m_seedtype = -1;
  m_seedx = 0;
  m_seedy = 0;
  m_growthreshold = 0;
  //}}AFX_DATA_INIT
}


void CRegionGrow::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CRegionGrow)
  DDX_Control(pDX, IDC_EDIT1, m_seedyvisible);
  DDX_Control(pDX, IDC_EDIT2, m_seedxvisible);
  DDX_Radio(pDX, IDC_RADIO1, m_seedtype);
  DDX_Text(pDX, IDC_EDIT1, m_seedx);
  DDX_Text(pDX, IDC_EDIT2, m_seedy);
  DDX_Text(pDX, IDC_EDIT3, m_growthreshold);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegionGrow, CDialog)
  //{{AFX_MSG_MAP(CRegionGrow)
  ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
  ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegionGrow message handlers

void CRegionGrow::OnRadio1() 
{
  // TODO: Add your control notification handler code here
    m_seedtype =0;
    UpdateData(FALSE);
    m_seedxvisible.EnableWindow(false);
    m_seedyvisible.EnableWindow(false); 
}

void CRegionGrow::OnRadio2() 
{
  // TODO: Add your control notification handler code here
    m_seedtype =1;
    UpdateData(FALSE);
    m_seedxvisible.EnableWindow(true);
    m_seedyvisible.EnableWindow(true);  
}

void CRegionGrow::OnOK() 
{
  // TODO: Add extra validation here
  UpdateData(true);
  if(m_seedx>ImageWidth||m_seedx<0||m_seedy>ImageHeight||m_seedy<0)
  {
    AfxMessageBox ("所设种子坐标不正确!",MB_OK);
    return;
  }
    
  CDialog::OnOK();
}


