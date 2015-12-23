// MedianFiltDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FYF.h"
#include "MedianFiltDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedianFiltDlg dialog


CMedianFiltDlg::CMedianFiltDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMedianFiltDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedianFiltDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMedianFiltDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedianFiltDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedianFiltDlg, CDialog)
	//{{AFX_MSG_MAP(CMedianFiltDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedianFiltDlg message handlers

void CMedianFiltDlg::OnOK() 
{
	// TODO: Add extra validation here
	// 将用户设定的数据传递给相应的对话框变量
	UpdateData(TRUE);	
	CDialog::OnOK();
}

void CMedianFiltDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
    //表示3X3的滤波器选中
	m_mediantype = 0;
	//滤波器的高度为3
	mFilterH = 3;
	//滤波器的宽度为3
	mFilterW = 3;
	//滤波器中心点的横坐标为1
	mFilterMX= 1;
	//滤波器中心点的纵坐标为1
	mFilterMY= 1;
}

void CMedianFiltDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	//表示5X5的滤波器选中
	m_mediantype = 1;
	//滤波器的高度为5
	mFilterH = 5;
	//滤波器的宽度为5
	mFilterW = 5;
	//滤波器中心点的横坐标为2
	mFilterMX= 2;
	//滤波器中心点的纵坐标为2
	mFilterMY= 2;	
}

void CMedianFiltDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	m_mediantype = 2;
	//滤波器的高度为7
	mFilterH = 7;
	//滤波器的宽度为7
	mFilterW = 7;
	//滤波器中心点的横坐标为3
	mFilterMX= 3;
	//滤波器中心点的纵坐标为3
	mFilterMY= 3;	
}
