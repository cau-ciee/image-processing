// FYFView.cpp : implementation of the CFYFView class
//

#include "stdafx.h"
#include "FYF.h"
#include "GrayEnhDlg.h"
#include "MedianFiltDlg.h"
#include "HigpassFilDlg.h"
#include "LowpassFilDlg.h"
#include "LaplacTemDlg.h"
#include "ThreDivDlg.h"
#include "RegionGrow.h"
#include "EdgeDetDlg.h"
#include "EroDlg.h"
#include "DilDlg.h"
#include "OpenDig.h"
#include "CloseDlg.h"

#include "function.h"

#include "FYFDoc.h"
#include "FYFView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFYFView

IMPLEMENT_DYNCREATE(CFYFView, CView)

BEGIN_MESSAGE_MAP(CFYFView, CView)
  //{{AFX_MSG_MAP(CFYFView)
  ON_COMMAND(ID_MEDIAN_FIL, OnMedianFil)
  ON_COMMAND(ID_GRAY_ENHANCE, OnGrayEnhance)
  ON_COMMAND(ID_HIST_ENH, OnHistEnh)
  ON_COMMAND(ID_HIGHPASS_FIL, OnHighpassFil)
  ON_COMMAND(ID_LOWPASS_FIL, OnLowpassFil)
  ON_COMMAND(ID_MEAN_ENH, OnMeanEnh)
  ON_COMMAND(ID_LAPLAS_TEMP, OnLaplasTemp)
  ON_COMMAND(ID_THRESHOLD_DIV, OnThresholdDiv)
  ON_COMMAND(ID_REGION_GRO, OnRegionGro)
  ON_COMMAND(ID_EDGE_DIF, OnEdgeDif)
  ON_COMMAND(ID_HOUGH_TRA, OnHoughTra)
  ON_COMMAND(ID_EROSION_OPE, OnErosionOpe)
  ON_COMMAND(ID_DILATION_OPR, OnDilationOpr)
  ON_COMMAND(ID_OPEN_DLG, OnOpenDlg)
  ON_COMMAND(ID_MEDIAN_FIL, OnMedianFil)
  ON_COMMAND(ID_CLOSE_DLG, OnCloseDlg)
  //}}AFX_MSG_MAP
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFYFView construction/destruction

CFYFView::CFYFView()
{
  // TODO: add construction code here
//  m_pDbImage=NULL;
//  m_nDWTCurDepth=0;
}

CFYFView::~CFYFView()
{
}

BOOL CFYFView::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFYFView drawing

void CFYFView::OnDraw(CDC* pDC)                          //ͼƬ��ʾ
{
  CFYFDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  // TODO: add draw code for native data here

    HGLOBAL hDIB = pDoc->GetHObject();
  // �ж�DIB�Ƿ�Ϊ��
  if (hDIB != NULL)
  {
    LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
    
    // ��ȡDIB���
    int cxDIB = (int) pDoc->m_dib.GetWidth(lpDibSection);
    
    // ��ȡDIB�߶�
    int cyDIB = (int) pDoc->m_dib.GetHeight(lpDibSection);

    ::GlobalUnlock((HGLOBAL) hDIB);
    
    CRect rcDIB;
    rcDIB.top = rcDIB.left = 0;
    rcDIB.right = cxDIB;
    rcDIB.bottom = cyDIB;
    
    CRect rcDest= rcDIB;  
    // ���DIB
    pDoc->m_dib.DrawDib(pDC->m_hDC, &rcDest, pDoc->GetHObject(),
      &rcDIB, pDoc->GetDocPal());
  }
  
}

/////////////////////////////////////////////////////////////////////////////
// CFYFView printing

BOOL CFYFView::OnPreparePrinting(CPrintInfo* pInfo)
{
  // default preparation
  return DoPreparePrinting(pInfo);
}

void CFYFView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  // TODO: add extra initialization before printing
}

void CFYFView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFYFView diagnostics

#ifdef _DEBUG
void CFYFView::AssertValid() const
{
  CView::AssertValid();
}

void CFYFView::Dump(CDumpContext& dc) const
{
  CView::Dump(dc);
}

CFYFDoc* CFYFView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFYFDoc)));
  return (CFYFDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFYFView message handlers



void CFYFView::OnGrayEnhDlg() 
{
  CFYFDoc* pDoc = GetDocument();        // ��ȡ��ǰ�ĵ�
  LPSTR lpDIB;                    // ָ��ǰDIB��ָ��
  LPSTR    lpDIBBits;               // ָ��ǰDIB����ָ��
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // ����DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // �ҵ�DIBͼ��������ʼλ��
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // �ж��Ƿ���256ɫλͼ
  {
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);        // ������ǣ���ʾ�û�
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // �������
    return;                   // ����
  }
    CGrayEnhDlg gray;                 //���ػҶȱ任�Ի�����
  if (gray.DoModal() != IDOK)             // ��ʾ�Ի�����ʾ�û��趨����
  {
    return;                   // ����
  }
  //�����ĸ��������ڴ����Ի������õĲ���
  int newhig;                     //�»Ҷ�����
  int newlow;                   //�»Ҷ�����
  int orahig;                     //�ɻҶ�����
  int oralow;                     //�ɻҶ�����
  newhig=gray.m_newhig;               // ��ȡ�û��趨�Ĳ���
  newlow=gray.m_newlow;               // ��ȡ�û��趨�Ĳ���
  orahig=gray.m_orahig;                 // ��ȡ�û��趨�Ĳ���
  oralow=gray.m_oralow;               // ��ȡ�û��趨�Ĳ���
  delete gray;                    // ɾ���Ի���
  BeginWaitCursor();                  // ���Ĺ����״
  // ����GrayLinTrans()�������лҶȱ任
  GrayLinTrans(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB),oralow, orahig, newlow, newhig);  
  pDoc->SetModifiedFlag(TRUE);              // ��������
  pDoc->UpdateAllViews(NULL);             // ������ͼ
  EndWaitCursor();                  // �ָ����
}

void CFYFView::OnGrayEnhance() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();        // ��ȡ��ǰ�ĵ�
  LPSTR lpDIB;                    // ָ��ǰDIB��ָ��
  LPSTR    lpDIBBits;               // ָ��ǰDIB����ָ��
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // ����DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // �ҵ�DIBͼ��������ʼλ��
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // �ж��Ƿ���256ɫλͼ
  {
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);        // ������ǣ���ʾ�û�
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // �������
    return;                   // ����
  }
  CGrayEnhDlg gray;                 //���ػҶȱ任�Ի�����
  if (gray.DoModal() != IDOK)             // ��ʾ�Ի�����ʾ�û��趨����
  {
    return;                   // ����
  }
  //�����ĸ��������ڴ����Ի������õĲ���
  int newhig;                     //�»Ҷ�����
  int newlow;                   //�»Ҷ�����
  int orahig;                     //�ɻҶ�����
  int oralow;                     //�ɻҶ�����
  newhig=gray.m_newhig;               // ��ȡ�û��趨�Ĳ���
  newlow=gray.m_newlow;               // ��ȡ�û��趨�Ĳ���
  orahig=gray.m_orahig;                 // ��ȡ�û��趨�Ĳ���
  oralow=gray.m_oralow;               // ��ȡ�û��趨�Ĳ���
  delete gray;                    // ɾ���Ի���
  BeginWaitCursor();                  // ���Ĺ����״
  // ����GrayLinTrans()�������лҶȱ任
  GrayLinTrans(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB),oralow, orahig, newlow, newhig);  
  pDoc->SetModifiedFlag(TRUE);              // ��������
  pDoc->UpdateAllViews(NULL);             // ������ͼ
  EndWaitCursor();                  // �ָ���� 
}

void CFYFView::OnHistEnh() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();        // ��ȡ��ǰ�ĵ�
  LPSTR lpDIB;                    // ָ��ǰDIB��ָ��
  LPSTR    lpDIBBits;               // ָ��ǰDIB����ָ��
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // ����DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // �ҵ�DIBͼ��������ʼλ��
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // �ж��Ƿ���256ɫλͼ
  {
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);        // ������ǣ���ʾ�û�
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // �������
    return;                   // ����
  }
  BeginWaitCursor();  // ���Ĺ����״
  //
  GrayHistEnhance(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB));//���ûҶ�ֱ��ͼͼ����ǿ����
  pDoc->SetModifiedFlag(TRUE);              // ��������
  pDoc->UpdateAllViews(NULL);             // ������ͼ
  EndWaitCursor();                  // �ָ����
}

void CFYFView::OnMedianFil() 
{
  // TODO: Add your command handler code here
  // ��ȡ�ĵ�
  CFYFDoc* pDoc = GetDocument();
  // ָ��DIB��ָ��
  LPSTR lpDIB;
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
  // �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�������Ŀ������ƣ�
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧�ֲ鿴256ɫλͼ�Ҷ�ֱ��ͼ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK); 
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject()); 
    // ����
    return;
  }
  int mFilterH;
  int mFilterW; 
  int mFilterMX; 
  int mFilterMY;  
  // �����Ի���
  CMedianFiltDlg medianfilter;  
  // ��ʾ�Ի�����ʾ�û��趨ƽ����
  if (medianfilter.DoModal() != IDOK)
  {
    // ����
    return;
  }
  mFilterH=medianfilter.mFilterH;
  mFilterW=medianfilter.mFilterW;
  mFilterMX=medianfilter.mFilterMX; 
  mFilterMY=medianfilter.mFilterMY;
  delete medianfilter;
  BeginWaitCursor();           // ���Ĺ����״
  //
  MedianFilter(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB), 
             mFilterH, mFilterW, 
             mFilterMX, mFilterMY);
  // ��������
  pDoc->SetModifiedFlag(TRUE);
  // ������ͼ
  pDoc->UpdateAllViews(NULL);
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnHighpassFil() 
{
  // TODO: Add your command handler code here
  // ��ȡ�ĵ�
  CFYFDoc* pDoc = GetDocument();
  // ָ��DIB��ָ��
  LPSTR lpDIB;
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
  // �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�������Ŀ������ƣ�
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧�ֲ鿴256ɫλͼ�Ҷ�ֱ��ͼ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK); 
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject()); 
    // ����
    return;
  }
  int mhighfreq1;
  int mhighfreq2; 
  // �����Ի���
  CHigpassFilDlg HigpassFilDlg; 
  // ��ʾ�Ի�����ʾ�û��趨ƽ����
  if (HigpassFilDlg.DoModal() != IDOK)
  {
    // ����
    return;
  }
  mhighfreq1=HigpassFilDlg.m_highfreq1;           //��ȡ�Ի���ĵ�ͨ�˲�����
  mhighfreq2=HigpassFilDlg.m_highfreq2;           //��ȡ�Ի���ĵ�ͨ�˲�����
  delete HigpassFilDlg;
  BeginWaitCursor();           // ���Ĺ����״
  //
  if ( ButterWorthHighPass(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),mhighfreq1))
    { 
      pDoc->SetModifiedFlag(TRUE);          // ��������
      pDoc->UpdateAllViews(NULL);         // ������ͼ
    }
  else
    {
      // ��ʾ�û�
      MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
    }
  // ��������
  pDoc->SetModifiedFlag(TRUE);
  // ������ͼ
  pDoc->UpdateAllViews(NULL);
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnLowpassFil() 
{
  // TODO: Add your command handler code here
  // ��ȡ�ĵ�
  CFYFDoc* pDoc = GetDocument();
  // ָ��DIB��ָ��
  LPSTR lpDIB;
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
  // �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�������Ŀ������ƣ�
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧�ֲ鿴256ɫλͼ�Ҷ�ֱ��ͼ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK); 
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject()); 
    // ����
    return;
  }
  int mlowfreq1;
  int mlowfreq2; 
  // �����Ի���
  CLowpassFilDlg LowpassFilDlg; 
  // ��ʾ�Ի�����ʾ�û��趨ƽ����
  if (LowpassFilDlg.DoModal() != IDOK)
  {
    // ����
    return;
  }
  mlowfreq1=LowpassFilDlg.m_lowfreq1;           //��ȡ�Ի���ĵ�ͨ�˲�����
  mlowfreq2=LowpassFilDlg.m_lowfreq2;           //��ȡ�Ի���ĵ�ͨ�˲�����
  delete LowpassFilDlg;
  BeginWaitCursor();           // ���Ĺ����״
  //
  if ( ButterWorthLowPass(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),mlowfreq1))
    { 
      pDoc->SetModifiedFlag(TRUE);          // ��������
      pDoc->UpdateAllViews(NULL);         // ������ͼ
    }
  else
    {
      // ��ʾ�û�
      MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
    }
  // ��������
  pDoc->SetModifiedFlag(TRUE);
  // ������ͼ
  pDoc->UpdateAllViews(NULL);
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnMeanEnh() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();        // ��ȡ��ǰ�ĵ�
  LPSTR lpDIB;                    // ָ��ǰDIB��ָ��
  LPSTR    lpDIBBits;               // ָ��ǰDIB����ָ��
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // ����DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // �ҵ�DIBͼ��������ʼλ��
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // �ж��Ƿ���256ɫλͼ
  {
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);        // ������ǣ���ʾ�û�
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // �������
    return;                   // ����
  }
  int   nTempHeight;                // ģ��߶�
  int   nTempWidth;               // ģ����
  double    dbTempCoef;             // ģ��ϵ��
  int   nTempCenX;                // ģ������Ԫ��X����
  int   nTempCenY;                // ģ������Ԫ��Y����
  double  pdbTemp[9];               // ģ��Ԫ������
  pdbTemp[0] = 1.0;                 // ��ģ�����鸳��ֵ
  pdbTemp[1] = 2.0;
  pdbTemp[2] = 1.0;
  pdbTemp[3] = 2.0;
  pdbTemp[4] = 4.0;
  pdbTemp[5] = 2.0;
  pdbTemp[6] = 1.0;
  pdbTemp[7] = 2.0;
  pdbTemp[8] = 1.0;
  nTempHeight   = 3;                  // �趨ģ�����ӵĲ���
  nTempWidth  = 3;                  // �趨ģ�����ӵĲ���
  nTempCenX = 1;                  // �趨ģ�����ӵĲ���
  nTempCenY = 1;                  // �趨ģ�����ӵĲ���
  dbTempCoef  = 0.0625;               // �趨ģ�����ӵĲ���
  BeginWaitCursor();                  // ���Ĺ����״
  // ����Template()��������ͼ���ƽ������
  if (Template(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB),
    nTempWidth, nTempHeight, nTempCenX, nTempCenY, pdbTemp, dbTempCoef))
  {   
    pDoc->SetModifiedFlag(TRUE);            // ��������
    pDoc->UpdateAllViews(NULL);           // ������ͼ
  }
  else
  {
    // ��ʾ�û�
    MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
  }
  EndWaitCursor();                  // �ָ���� 
}

void CFYFView::OnLaplasTemp() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();        // ��ȡ��ǰ�ĵ�
  LPSTR lpDIB;                    // ָ��ǰDIB��ָ��
  LPSTR    lpDIBBits;               // ָ��ǰDIB����ָ��
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // ����DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // �ҵ�DIBͼ��������ʼλ��
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // �ж��Ƿ���256ɫλͼ
  {
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);        // ������ǣ���ʾ�û�
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // �������
    return;                   // ����
  }
  int   mTempH;                 // ģ��߶�
  int   mTempW;                 // ģ����
  FLOAT mTempCof;               // ģ��ϵ��
  int   mTempMX;                // ģ������Ԫ��X����
  int   mTempMY;                // ģ������Ԫ��Y����
  double  laplacValue[9];               // ģ��Ԫ������
  BeginWaitCursor();                  // ���Ĺ����״
  mTempW = 3;                   // ����������˹ģ�����
  mTempH = 3;                   // ����������˹ģ�����
  mTempCof = 1.0;                 // ����������˹ģ�����
  mTempMX = 1;                    // ����������˹ģ�����
  mTempMY = 1;                    // ����������˹ģ�����
  CLaplacTemDlg laplactem;                // ʵ�����Ի���
  if (laplactem.DoModal() != IDOK)            // ��ʾ�Ի����û����ò���
  {
    return;                   // ����
  }
  //��ȡ�Ի����û�ѡ���������˹ģ�����
  laplacValue[0] = laplactem.laplacvalue[0];
  laplacValue[1] = laplactem.laplacvalue[1];
  laplacValue[2] = laplactem.laplacvalue[2];
  laplacValue[3] = laplactem.laplacvalue[3];
  laplacValue[4] = laplactem.laplacvalue[4];
  laplacValue[5] = laplactem.laplacvalue[5];
  laplacValue[6] = laplactem.laplacvalue[6];
  laplacValue[7] = laplactem.laplacvalue[7];
  laplacValue[8] = laplactem.laplacvalue[8];
  delete laplactem;                 // ɾ���Ի���
  // ����Template()������������˹ģ����DIB
  if ( Template(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB), 
      mTempH, mTempW, mTempMX, mTempMY, laplacValue, mTempCof))
  { 
    pDoc->SetModifiedFlag(TRUE);            // ��������
    pDoc->UpdateAllViews(NULL);           // ������ͼ
  }
  else
  {
    // ��ʾ�û�
    MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
  }
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());       // �������
  EndWaitCursor();                  // �ָ���� 
}

void CFYFView::OnThresholdDiv() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();  // ��ȡ�ĵ�
  // ָ��DIB��ָ��
  LPSTR lpDIB;  
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // �ж��Ƿ���8-bppλͼ
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);  
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // ����
    return;
  } 
  int threshold; //��ֵ
  int type;  //��ֵ�ָ�����
  // ��ʾ�Ի����û����ò���
  CThreDivDlg thresholddivide;  
  if (thresholddivide.DoModal() != IDOK)
  {
    // ����
    return;
  }
  //�����û����õĲ���
  threshold=thresholddivide.m_threshold;
  type=thresholddivide.m_type;
  delete thresholddivide;//ɾ���Ի���ʵ��
  // ���Ĺ����״
  BeginWaitCursor();
  if(type==0)
  {
    if ( RegionDivideThreshold(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),threshold))
    { 
      // ��������
      pDoc->SetModifiedFlag(TRUE);
      // ������ͼ
      pDoc->UpdateAllViews(NULL);
    }
  
    else
    {
      // ��ʾ�û�
      MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
    }
  
  }
  else if(type==1)
  {
    if ( RegionDivideAdaptive(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB)))
    { 
      // ��������
      pDoc->SetModifiedFlag(TRUE);
      // ������ͼ
      pDoc->UpdateAllViews(NULL);
    }
  
    else
    {
      // ��ʾ�û�
      MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
    }
  }
    // �������
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnRegionGro() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();  // ��ȡ�ĵ�
  // ָ��DIB��ָ��
  LPSTR lpDIB;  
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // �ж��Ƿ���8-bppλͼ
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);  
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // ����
    return;
  }
   int nThreshold;  //��������
   int seedx;     //���ӵ�X����
   int seedy;     //���ӵ�Y����
   int mode;      //���ӵ�����
   CRegionGrow regiongrow;  //ʵ�����Ի�����
   regiongrow.ImageHeight=pDoc->m_dib.GetHeight(lpDIB); //����ͼ��߶�
   regiongrow.ImageWidth=pDoc->m_dib.GetWidth(lpDIB); //����ͼ����
  if (regiongrow.DoModal() != IDOK)     //���öԻ���
  {
    // ����
    return;
  }
  delete regiongrow;//ɾ���Ի���ʵ��
  //����Ի����û����õĲ���
   nThreshold=regiongrow.m_growthreshold;
   seedx=regiongrow.m_seedx;
   seedy=regiongrow.m_seedy;
   mode=regiongrow.m_seedtype;
   //����������������
   if ( RegionGrow(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),nThreshold,seedx,seedy,mode))
    { 
      // ��������
      pDoc->SetModifiedFlag(TRUE);
      // ������ͼ
      pDoc->UpdateAllViews(NULL);
    }
  
   else
   {
    // ��ʾ�û�
    MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
   }
   // �������
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // �ָ����
  EndWaitCursor();  
}


void CFYFView::OnEdgeDif() 
{
  // TODO: Add your command handler code here
  // ��ȡ�ĵ�
  CFYFDoc* pDoc = GetDocument();
  // ָ��DIB��ָ��
  LPSTR lpDIB;  
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  //������ӵ����ͣ�����������
  int     type;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // �ж��Ƿ���8-bppλͼ
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);  
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // ����
    return;
  }
  // ��ʾ�Ի����û����ò���
  CEdgeDetDlg edgedetection;  
  if (edgedetection.DoModal() != IDOK)
  {
    // ����
    return;
  }
  //��ȡ�Ի����û�ѡ��ĸ�ʴ����Ĳ���
  type=edgedetection.m_mode;
  //ɾ���Ի���
  delete edgedetection;
  // ���Ĺ����״
  BeginWaitCursor();
  //����ͼ����������
  if ( EdgeDetection(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type))
  { 
    // ��������
    pDoc->SetModifiedFlag(TRUE);
    // ������ͼ
    pDoc->UpdateAllViews(NULL);
  }
  else
  {
    // ��ʾ�û�
    MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
  }

  // �������
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnHoughTra() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();  // ��ȡ�ĵ�
  // ָ��DIB��ָ��
  LPSTR lpDIB;  
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // �ж��Ƿ���8-bppλͼ
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);  
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // ����
    return;
  }
    // ���Ĺ����״
  BeginWaitCursor();
  //����ͼ��ϸ������
  if ( HoughTrans(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB)))
  { 
    // ��������
    pDoc->SetModifiedFlag(TRUE);
    // ������ͼ
    pDoc->UpdateAllViews(NULL);
  }
  
  else
  {
    // ��ʾ�û�
    MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
  }

  // �������
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnErosionOpe() 
{
  // TODO: Add your command handler code here
  // ��ȡ�ĵ�
  CFYFDoc* pDoc = GetDocument();
  // ָ��DIB��ָ��
  LPSTR lpDIB;  
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // �ṹԪ�صĳ��ȣ��߶ȣ�
  int     num;
  //�ṹԪ�ص����ͣ�����������
  int     type;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // �ж��Ƿ���8-bppλͼ
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);  
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // ����
    return;
  }
  // ��ʾ�Ի����û����ò���
  CEroDlg erosionpara;  
  if (erosionpara.DoModal() != IDOK)
  {
    // ����
    return;
  }
  //��ȡ�Ի����û�ѡ��ĸ�ʴ����Ĳ���
  type=erosionpara.m_type;
  num=erosionpara.numvalue;
  //ɾ���Ի���
  delete erosionpara;
  // ���Ĺ����״
  BeginWaitCursor();
  if ( Erosion(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
  { 
    // ��������
    pDoc->SetModifiedFlag(TRUE);
    // ������ͼ
    pDoc->UpdateAllViews(NULL);
  }
  else
  {
    // ��ʾ�û�
    MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
  }

  // �������
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnDilationOpr() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();
  // ָ��DIB��ָ��
  LPSTR lpDIB;  
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // �ṹԪ�صĳ��ȣ��߶ȣ�
  int     num;
  //�ṹԪ�ص����ͣ�����������
  int     type;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // �ж��Ƿ���8-bppλͼ
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);  
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // ����
    return;
  }
  // ��ʾ�Ի����û����ò���
  CDilDlg dilationpara; 
  if (dilationpara.DoModal() != IDOK)
  {
    // ����
    return;
  }
  //��ȡ�Ի����û�ѡ��ĸ�ʴ����Ĳ���
  type=dilationpara.m_type;
  num=dilationpara.numvalue;
  //ɾ���Ի���
  delete dilationpara;
  // ���Ĺ����״
  BeginWaitCursor();
  //����ͼ����������
  if ( Dilation(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
  { 
    // ��������
    pDoc->SetModifiedFlag(TRUE);
    // ������ͼ
    pDoc->UpdateAllViews(NULL);
  }
  else
  {
    // ��ʾ�û�
    MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
  }

  // �������
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnOpenDlg() 
{
  // TODO: Add your command handler code here
  // ��ȡ�ĵ�
  CFYFDoc* pDoc = GetDocument();
  // ָ��DIB��ָ��
  LPSTR lpDIB;  
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // �ṹԪ�صĳ��ȣ��߶ȣ�
  int     num;
  //�ṹԪ�ص����ͣ�����������
  int     type;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // �ж��Ƿ���8-bppλͼ
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);  
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // ����
    return;
  }
  // ��ʾ�Ի����û����ò���
  COpenDig openclosepara; 
  if (openclosepara.DoModal() != IDOK)
  {
    // ����
    return;
  }
  //��ȡ�Ի����û�ѡ������Ĳ���
  type=openclosepara.m_type;
  num=openclosepara.numvalue;
  //ɾ���Ի���
  delete openclosepara;
  // ���Ĺ����״
  BeginWaitCursor();
  //������
    //���и�ʴ����
    if ( Erosion(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
    { 
      // ��������
      pDoc->SetModifiedFlag(TRUE);
    }
    else
    {
      // ��ʾ�û�
      MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
    }
    //������������
    if ( Dilation(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
    { 
      // ��������
      pDoc->SetModifiedFlag(TRUE);
      // ������ͼ
      pDoc->UpdateAllViews(NULL);
    }
  
    else
    {
      // ��ʾ�û�
      MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
    }
  // �������
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // �ָ����
  EndWaitCursor();  
}

void CFYFView::OnCloseDlg() 
{
  // TODO: Add your command handler code here
  // ��ȡ�ĵ�
  CFYFDoc* pDoc = GetDocument();
  // ָ��DIB��ָ��
  LPSTR lpDIB;  
  // ָ��DIB����ָ��
  LPSTR    lpDIBBits;
  // �ṹԪ�صĳ��ȣ��߶ȣ�
  int     num;
  //�ṹԪ�ص����ͣ�����������
  int     type;
  // ����DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // �ҵ�DIBͼ��������ʼλ��
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // �ж��Ƿ���8-bppλͼ
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // ��ʾ�û�
    MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , 
      MB_ICONINFORMATION | MB_OK);  
    // �������
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // ����
    return;
  }
  // ��ʾ�Ի����û����ò���
  CCloseDlg openclosepara;  
  if (openclosepara.DoModal() != IDOK)
  {
    // ����
    return;
  }
  //��ȡ�Ի����û�ѡ������Ĳ���
  type=openclosepara.m_type;
  num=openclosepara.numvalue;
  //ɾ���Ի���
  delete openclosepara;
  // ���Ĺ����״
  BeginWaitCursor();
  //�պ�����
    //������������
    if ( Dilation(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
    { 
      // ��������
      pDoc->SetModifiedFlag(TRUE);
      // ������ͼ
      pDoc->UpdateAllViews(NULL);
    }
  
    else
    {
      // ��ʾ�û�
      MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
    }
    //���и�ʴ����
    if ( Erosion(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
    { 
      // ��������
      pDoc->SetModifiedFlag(TRUE);
    }
    else
    {
      // ��ʾ�û�
      MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
    }
  // �������
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // �ָ����
  EndWaitCursor();    
}
