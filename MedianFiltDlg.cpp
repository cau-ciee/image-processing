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
	// ���û��趨�����ݴ��ݸ���Ӧ�ĶԻ������
	UpdateData(TRUE);	
	CDialog::OnOK();
}

void CMedianFiltDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
    //��ʾ3X3���˲���ѡ��
	m_mediantype = 0;
	//�˲����ĸ߶�Ϊ3
	mFilterH = 3;
	//�˲����Ŀ��Ϊ3
	mFilterW = 3;
	//�˲������ĵ�ĺ�����Ϊ1
	mFilterMX= 1;
	//�˲������ĵ��������Ϊ1
	mFilterMY= 1;
}

void CMedianFiltDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	//��ʾ5X5���˲���ѡ��
	m_mediantype = 1;
	//�˲����ĸ߶�Ϊ5
	mFilterH = 5;
	//�˲����Ŀ��Ϊ5
	mFilterW = 5;
	//�˲������ĵ�ĺ�����Ϊ2
	mFilterMX= 2;
	//�˲������ĵ��������Ϊ2
	mFilterMY= 2;	
}

void CMedianFiltDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	m_mediantype = 2;
	//�˲����ĸ߶�Ϊ7
	mFilterH = 7;
	//�˲����Ŀ��Ϊ7
	mFilterW = 7;
	//�˲������ĵ�ĺ�����Ϊ3
	mFilterMX= 3;
	//�˲������ĵ��������Ϊ3
	mFilterMY= 3;	
}
