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

void CFYFView::OnDraw(CDC* pDC)                          //图片显示
{
  CFYFDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  // TODO: add draw code for native data here

    HGLOBAL hDIB = pDoc->GetHObject();
  // 判断DIB是否为空
  if (hDIB != NULL)
  {
    LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
    
    // 获取DIB宽度
    int cxDIB = (int) pDoc->m_dib.GetWidth(lpDibSection);
    
    // 获取DIB高度
    int cyDIB = (int) pDoc->m_dib.GetHeight(lpDibSection);

    ::GlobalUnlock((HGLOBAL) hDIB);
    
    CRect rcDIB;
    rcDIB.top = rcDIB.left = 0;
    rcDIB.right = cxDIB;
    rcDIB.bottom = cyDIB;
    
    CRect rcDest= rcDIB;  
    // 输出DIB
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
  CFYFDoc* pDoc = GetDocument();        // 获取当前文档
  LPSTR lpDIB;                    // 指向当前DIB的指针
  LPSTR    lpDIBBits;               // 指向当前DIB像素指针
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // 锁定DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // 找到DIB图像象素起始位置
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // 判断是否是256色位图
  {
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);        // 如果不是，提示用户
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // 解除锁定
    return;                   // 返回
  }
    CGrayEnhDlg gray;                 //重载灰度变换对话框类
  if (gray.DoModal() != IDOK)             // 显示对话框，提示用户设定参数
  {
    return;                   // 返回
  }
  //定义四个变量用于存贮对话框设置的参数
  int newhig;                     //新灰度上限
  int newlow;                   //新灰度下限
  int orahig;                     //旧灰度上限
  int oralow;                     //旧灰度下限
  newhig=gray.m_newhig;               // 获取用户设定的参数
  newlow=gray.m_newlow;               // 获取用户设定的参数
  orahig=gray.m_orahig;                 // 获取用户设定的参数
  oralow=gray.m_oralow;               // 获取用户设定的参数
  delete gray;                    // 删除对话框
  BeginWaitCursor();                  // 更改光标形状
  // 调用GrayLinTrans()函数进行灰度变换
  GrayLinTrans(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB),oralow, orahig, newlow, newhig);  
  pDoc->SetModifiedFlag(TRUE);              // 设置脏标记
  pDoc->UpdateAllViews(NULL);             // 更新视图
  EndWaitCursor();                  // 恢复光标
}

void CFYFView::OnGrayEnhance() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();        // 获取当前文档
  LPSTR lpDIB;                    // 指向当前DIB的指针
  LPSTR    lpDIBBits;               // 指向当前DIB像素指针
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // 锁定DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // 找到DIB图像象素起始位置
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // 判断是否是256色位图
  {
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);        // 如果不是，提示用户
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // 解除锁定
    return;                   // 返回
  }
  CGrayEnhDlg gray;                 //重载灰度变换对话框类
  if (gray.DoModal() != IDOK)             // 显示对话框，提示用户设定参数
  {
    return;                   // 返回
  }
  //定义四个变量用于存贮对话框设置的参数
  int newhig;                     //新灰度上限
  int newlow;                   //新灰度下限
  int orahig;                     //旧灰度上限
  int oralow;                     //旧灰度下限
  newhig=gray.m_newhig;               // 获取用户设定的参数
  newlow=gray.m_newlow;               // 获取用户设定的参数
  orahig=gray.m_orahig;                 // 获取用户设定的参数
  oralow=gray.m_oralow;               // 获取用户设定的参数
  delete gray;                    // 删除对话框
  BeginWaitCursor();                  // 更改光标形状
  // 调用GrayLinTrans()函数进行灰度变换
  GrayLinTrans(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB),oralow, orahig, newlow, newhig);  
  pDoc->SetModifiedFlag(TRUE);              // 设置脏标记
  pDoc->UpdateAllViews(NULL);             // 更新视图
  EndWaitCursor();                  // 恢复光标 
}

void CFYFView::OnHistEnh() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();        // 获取当前文档
  LPSTR lpDIB;                    // 指向当前DIB的指针
  LPSTR    lpDIBBits;               // 指向当前DIB像素指针
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // 锁定DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // 找到DIB图像象素起始位置
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // 判断是否是256色位图
  {
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);        // 如果不是，提示用户
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // 解除锁定
    return;                   // 返回
  }
  BeginWaitCursor();  // 更改光标形状
  //
  GrayHistEnhance(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB));//调用灰度直方图图像增强函数
  pDoc->SetModifiedFlag(TRUE);              // 设置脏标记
  pDoc->UpdateAllViews(NULL);             // 更新视图
  EndWaitCursor();                  // 恢复光标
}

void CFYFView::OnMedianFil() 
{
  // TODO: Add your command handler code here
  // 获取文档
  CFYFDoc* pDoc = GetDocument();
  // 指向DIB的指针
  LPSTR lpDIB;
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
  // 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图，其它的可以类推）
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持查看256色位图灰度直方图！", "系统提示" , MB_ICONINFORMATION | MB_OK); 
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject()); 
    // 返回
    return;
  }
  int mFilterH;
  int mFilterW; 
  int mFilterMX; 
  int mFilterMY;  
  // 创建对话框
  CMedianFiltDlg medianfilter;  
  // 显示对话框，提示用户设定平移量
  if (medianfilter.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  mFilterH=medianfilter.mFilterH;
  mFilterW=medianfilter.mFilterW;
  mFilterMX=medianfilter.mFilterMX; 
  mFilterMY=medianfilter.mFilterMY;
  delete medianfilter;
  BeginWaitCursor();           // 更改光标形状
  //
  MedianFilter(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB), 
             mFilterH, mFilterW, 
             mFilterMX, mFilterMY);
  // 设置脏标记
  pDoc->SetModifiedFlag(TRUE);
  // 更新视图
  pDoc->UpdateAllViews(NULL);
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnHighpassFil() 
{
  // TODO: Add your command handler code here
  // 获取文档
  CFYFDoc* pDoc = GetDocument();
  // 指向DIB的指针
  LPSTR lpDIB;
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
  // 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图，其它的可以类推）
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持查看256色位图灰度直方图！", "系统提示" , MB_ICONINFORMATION | MB_OK); 
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject()); 
    // 返回
    return;
  }
  int mhighfreq1;
  int mhighfreq2; 
  // 创建对话框
  CHigpassFilDlg HigpassFilDlg; 
  // 显示对话框，提示用户设定平移量
  if (HigpassFilDlg.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  mhighfreq1=HigpassFilDlg.m_highfreq1;           //读取对话框的低通滤波参数
  mhighfreq2=HigpassFilDlg.m_highfreq2;           //读取对话框的低通滤波参数
  delete HigpassFilDlg;
  BeginWaitCursor();           // 更改光标形状
  //
  if ( ButterWorthHighPass(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),mhighfreq1))
    { 
      pDoc->SetModifiedFlag(TRUE);          // 设置脏标记
      pDoc->UpdateAllViews(NULL);         // 更新视图
    }
  else
    {
      // 提示用户
      MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
    }
  // 设置脏标记
  pDoc->SetModifiedFlag(TRUE);
  // 更新视图
  pDoc->UpdateAllViews(NULL);
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnLowpassFil() 
{
  // TODO: Add your command handler code here
  // 获取文档
  CFYFDoc* pDoc = GetDocument();
  // 指向DIB的指针
  LPSTR lpDIB;
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
  // 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图，其它的可以类推）
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持查看256色位图灰度直方图！", "系统提示" , MB_ICONINFORMATION | MB_OK); 
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject()); 
    // 返回
    return;
  }
  int mlowfreq1;
  int mlowfreq2; 
  // 创建对话框
  CLowpassFilDlg LowpassFilDlg; 
  // 显示对话框，提示用户设定平移量
  if (LowpassFilDlg.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  mlowfreq1=LowpassFilDlg.m_lowfreq1;           //读取对话框的低通滤波参数
  mlowfreq2=LowpassFilDlg.m_lowfreq2;           //读取对话框的低通滤波参数
  delete LowpassFilDlg;
  BeginWaitCursor();           // 更改光标形状
  //
  if ( ButterWorthLowPass(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),mlowfreq1))
    { 
      pDoc->SetModifiedFlag(TRUE);          // 设置脏标记
      pDoc->UpdateAllViews(NULL);         // 更新视图
    }
  else
    {
      // 提示用户
      MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
    }
  // 设置脏标记
  pDoc->SetModifiedFlag(TRUE);
  // 更新视图
  pDoc->UpdateAllViews(NULL);
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnMeanEnh() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();        // 获取当前文档
  LPSTR lpDIB;                    // 指向当前DIB的指针
  LPSTR    lpDIBBits;               // 指向当前DIB像素指针
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // 锁定DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // 找到DIB图像象素起始位置
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // 判断是否是256色位图
  {
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);        // 如果不是，提示用户
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // 解除锁定
    return;                   // 返回
  }
  int   nTempHeight;                // 模板高度
  int   nTempWidth;               // 模板宽度
  double    dbTempCoef;             // 模板系数
  int   nTempCenX;                // 模板中心元素X坐标
  int   nTempCenY;                // 模板中心元素Y坐标
  double  pdbTemp[9];               // 模板元素数组
  pdbTemp[0] = 1.0;                 // 给模板数组赋初值
  pdbTemp[1] = 2.0;
  pdbTemp[2] = 1.0;
  pdbTemp[3] = 2.0;
  pdbTemp[4] = 4.0;
  pdbTemp[5] = 2.0;
  pdbTemp[6] = 1.0;
  pdbTemp[7] = 2.0;
  pdbTemp[8] = 1.0;
  nTempHeight   = 3;                  // 设定模板算子的参数
  nTempWidth  = 3;                  // 设定模板算子的参数
  nTempCenX = 1;                  // 设定模板算子的参数
  nTempCenY = 1;                  // 设定模板算子的参数
  dbTempCoef  = 0.0625;               // 设定模板算子的参数
  BeginWaitCursor();                  // 更改光标形状
  // 调用Template()函数进行图像的平滑处理
  if (Template(lpDIBBits,pDoc->m_dib.GetWidth(lpDIB),pDoc->m_dib.GetHeight(lpDIB),
    nTempWidth, nTempHeight, nTempCenX, nTempCenY, pdbTemp, dbTempCoef))
  {   
    pDoc->SetModifiedFlag(TRUE);            // 设置脏标记
    pDoc->UpdateAllViews(NULL);           // 更新视图
  }
  else
  {
    // 提示用户
    MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
  }
  EndWaitCursor();                  // 恢复光标 
}

void CFYFView::OnLaplasTemp() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();        // 获取当前文档
  LPSTR lpDIB;                    // 指向当前DIB的指针
  LPSTR    lpDIBBits;               // 指向当前DIB像素指针
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject()); // 锁定DIB
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);           // 找到DIB图像象素起始位置
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)            // 判断是否是256色位图
  {
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);        // 如果不是，提示用户
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());     // 解除锁定
    return;                   // 返回
  }
  int   mTempH;                 // 模板高度
  int   mTempW;                 // 模板宽度
  FLOAT mTempCof;               // 模板系数
  int   mTempMX;                // 模板中心元素X坐标
  int   mTempMY;                // 模板中心元素Y坐标
  double  laplacValue[9];               // 模板元素数组
  BeginWaitCursor();                  // 更改光标形状
  mTempW = 3;                   // 设置拉普拉斯模板参数
  mTempH = 3;                   // 设置拉普拉斯模板参数
  mTempCof = 1.0;                 // 设置拉普拉斯模板参数
  mTempMX = 1;                    // 设置拉普拉斯模板参数
  mTempMY = 1;                    // 设置拉普拉斯模板参数
  CLaplacTemDlg laplactem;                // 实例化对话框
  if (laplactem.DoModal() != IDOK)            // 显示对话框，用户设置参数
  {
    return;                   // 返回
  }
  //读取对话框用户选择的拉普拉斯模板参数
  laplacValue[0] = laplactem.laplacvalue[0];
  laplacValue[1] = laplactem.laplacvalue[1];
  laplacValue[2] = laplactem.laplacvalue[2];
  laplacValue[3] = laplactem.laplacvalue[3];
  laplacValue[4] = laplactem.laplacvalue[4];
  laplacValue[5] = laplactem.laplacvalue[5];
  laplacValue[6] = laplactem.laplacvalue[6];
  laplacValue[7] = laplactem.laplacvalue[7];
  laplacValue[8] = laplactem.laplacvalue[8];
  delete laplactem;                 // 删除对话框
  // 调用Template()函数用拉普拉斯模板锐化DIB
  if ( Template(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB), 
      mTempH, mTempW, mTempMX, mTempMY, laplacValue, mTempCof))
  { 
    pDoc->SetModifiedFlag(TRUE);            // 设置脏标记
    pDoc->UpdateAllViews(NULL);           // 更新视图
  }
  else
  {
    // 提示用户
    MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
  }
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());       // 解除锁定
  EndWaitCursor();                  // 恢复光标 
}

void CFYFView::OnThresholdDiv() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();  // 获取文档
  // 指向DIB的指针
  LPSTR lpDIB;  
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // 判断是否是8-bpp位图
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);  
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // 返回
    return;
  } 
  int threshold; //阈值
  int type;  //阈值分割类型
  // 显示对话框，用户设置参数
  CThreDivDlg thresholddivide;  
  if (thresholddivide.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  //读入用户设置的参数
  threshold=thresholddivide.m_threshold;
  type=thresholddivide.m_type;
  delete thresholddivide;//删除对话框实例
  // 更改光标形状
  BeginWaitCursor();
  if(type==0)
  {
    if ( RegionDivideThreshold(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),threshold))
    { 
      // 设置脏标记
      pDoc->SetModifiedFlag(TRUE);
      // 更新视图
      pDoc->UpdateAllViews(NULL);
    }
  
    else
    {
      // 提示用户
      MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
    }
  
  }
  else if(type==1)
  {
    if ( RegionDivideAdaptive(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB)))
    { 
      // 设置脏标记
      pDoc->SetModifiedFlag(TRUE);
      // 更新视图
      pDoc->UpdateAllViews(NULL);
    }
  
    else
    {
      // 提示用户
      MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
    }
  }
    // 解除锁定
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnRegionGro() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();  // 获取文档
  // 指向DIB的指针
  LPSTR lpDIB;  
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // 判断是否是8-bpp位图
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);  
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // 返回
    return;
  }
   int nThreshold;  //生长门限
   int seedx;     //种子点X坐标
   int seedy;     //种子点Y坐标
   int mode;      //种子点类型
   CRegionGrow regiongrow;  //实例化对话框类
   regiongrow.ImageHeight=pDoc->m_dib.GetHeight(lpDIB); //读入图像高度
   regiongrow.ImageWidth=pDoc->m_dib.GetWidth(lpDIB); //读入图像宽度
  if (regiongrow.DoModal() != IDOK)     //调用对话框
  {
    // 返回
    return;
  }
  delete regiongrow;//删除对话框实例
  //读入对话框用户设置的参数
   nThreshold=regiongrow.m_growthreshold;
   seedx=regiongrow.m_seedx;
   seedy=regiongrow.m_seedy;
   mode=regiongrow.m_seedtype;
   //进行区域增长处理
   if ( RegionGrow(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),nThreshold,seedx,seedy,mode))
    { 
      // 设置脏标记
      pDoc->SetModifiedFlag(TRUE);
      // 更新视图
      pDoc->UpdateAllViews(NULL);
    }
  
   else
   {
    // 提示用户
    MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
   }
   // 解除锁定
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // 恢复光标
  EndWaitCursor();  
}


void CFYFView::OnEdgeDif() 
{
  // TODO: Add your command handler code here
  // 获取文档
  CFYFDoc* pDoc = GetDocument();
  // 指向DIB的指针
  LPSTR lpDIB;  
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  //检测算子的类型（横向还是纵向）
  int     type;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // 判断是否是8-bpp位图
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);  
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // 返回
    return;
  }
  // 显示对话框，用户设置参数
  CEdgeDetDlg edgedetection;  
  if (edgedetection.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  //读取对话框用户选择的腐蚀运算的参数
  type=edgedetection.m_mode;
  //删除对话框
  delete edgedetection;
  // 更改光标形状
  BeginWaitCursor();
  //进行图像膨胀运算
  if ( EdgeDetection(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type))
  { 
    // 设置脏标记
    pDoc->SetModifiedFlag(TRUE);
    // 更新视图
    pDoc->UpdateAllViews(NULL);
  }
  else
  {
    // 提示用户
    MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
  }

  // 解除锁定
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnHoughTra() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();  // 获取文档
  // 指向DIB的指针
  LPSTR lpDIB;  
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // 判断是否是8-bpp位图
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);  
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // 返回
    return;
  }
    // 更改光标形状
  BeginWaitCursor();
  //进行图像细化运算
  if ( HoughTrans(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB)))
  { 
    // 设置脏标记
    pDoc->SetModifiedFlag(TRUE);
    // 更新视图
    pDoc->UpdateAllViews(NULL);
  }
  
  else
  {
    // 提示用户
    MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
  }

  // 解除锁定
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnErosionOpe() 
{
  // TODO: Add your command handler code here
  // 获取文档
  CFYFDoc* pDoc = GetDocument();
  // 指向DIB的指针
  LPSTR lpDIB;  
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 结构元素的长度（高度）
  int     num;
  //结构元素的类型（横向还是纵向）
  int     type;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // 判断是否是8-bpp位图
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);  
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // 返回
    return;
  }
  // 显示对话框，用户设置参数
  CEroDlg erosionpara;  
  if (erosionpara.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  //读取对话框用户选择的腐蚀运算的参数
  type=erosionpara.m_type;
  num=erosionpara.numvalue;
  //删除对话框
  delete erosionpara;
  // 更改光标形状
  BeginWaitCursor();
  if ( Erosion(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
  { 
    // 设置脏标记
    pDoc->SetModifiedFlag(TRUE);
    // 更新视图
    pDoc->UpdateAllViews(NULL);
  }
  else
  {
    // 提示用户
    MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
  }

  // 解除锁定
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnDilationOpr() 
{
  // TODO: Add your command handler code here
  CFYFDoc* pDoc = GetDocument();
  // 指向DIB的指针
  LPSTR lpDIB;  
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 结构元素的长度（高度）
  int     num;
  //结构元素的类型（横向还是纵向）
  int     type;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // 判断是否是8-bpp位图
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);  
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // 返回
    return;
  }
  // 显示对话框，用户设置参数
  CDilDlg dilationpara; 
  if (dilationpara.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  //读取对话框用户选择的腐蚀运算的参数
  type=dilationpara.m_type;
  num=dilationpara.numvalue;
  //删除对话框
  delete dilationpara;
  // 更改光标形状
  BeginWaitCursor();
  //进行图像膨胀运算
  if ( Dilation(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
  { 
    // 设置脏标记
    pDoc->SetModifiedFlag(TRUE);
    // 更新视图
    pDoc->UpdateAllViews(NULL);
  }
  else
  {
    // 提示用户
    MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
  }

  // 解除锁定
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnOpenDlg() 
{
  // TODO: Add your command handler code here
  // 获取文档
  CFYFDoc* pDoc = GetDocument();
  // 指向DIB的指针
  LPSTR lpDIB;  
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 结构元素的长度（高度）
  int     num;
  //结构元素的类型（横向还是纵向）
  int     type;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // 判断是否是8-bpp位图
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);  
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // 返回
    return;
  }
  // 显示对话框，用户设置参数
  COpenDig openclosepara; 
  if (openclosepara.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  //读取对话框用户选择运算的参数
  type=openclosepara.m_type;
  num=openclosepara.numvalue;
  //删除对话框
  delete openclosepara;
  // 更改光标形状
  BeginWaitCursor();
  //开运算
    //进行腐蚀运算
    if ( Erosion(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
    { 
      // 设置脏标记
      pDoc->SetModifiedFlag(TRUE);
    }
    else
    {
      // 提示用户
      MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
    }
    //进行膨胀运算
    if ( Dilation(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
    { 
      // 设置脏标记
      pDoc->SetModifiedFlag(TRUE);
      // 更新视图
      pDoc->UpdateAllViews(NULL);
    }
  
    else
    {
      // 提示用户
      MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
    }
  // 解除锁定
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // 恢复光标
  EndWaitCursor();  
}

void CFYFView::OnCloseDlg() 
{
  // TODO: Add your command handler code here
  // 获取文档
  CFYFDoc* pDoc = GetDocument();
  // 指向DIB的指针
  LPSTR lpDIB;  
  // 指向DIB象素指针
  LPSTR    lpDIBBits;
  // 结构元素的长度（高度）
  int     num;
  //结构元素的类型（横向还是纵向）
  int     type;
  // 锁定DIB
  lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());
  // 找到DIB图像象素起始位置
  lpDIBBits = pDoc->m_dib.GetBits(lpDIB);   
  // 判断是否是8-bpp位图
  if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
  {
    // 提示用户
    MessageBox("目前只支持256色位图！", "系统提示" , 
      MB_ICONINFORMATION | MB_OK);  
    // 解除锁定
    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
    // 返回
    return;
  }
  // 显示对话框，用户设置参数
  CCloseDlg openclosepara;  
  if (openclosepara.DoModal() != IDOK)
  {
    // 返回
    return;
  }
  //读取对话框用户选择运算的参数
  type=openclosepara.m_type;
  num=openclosepara.numvalue;
  //删除对话框
  delete openclosepara;
  // 更改光标形状
  BeginWaitCursor();
  //闭合运算
    //进行膨胀运算
    if ( Dilation(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
    { 
      // 设置脏标记
      pDoc->SetModifiedFlag(TRUE);
      // 更新视图
      pDoc->UpdateAllViews(NULL);
    }
  
    else
    {
      // 提示用户
      MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
    }
    //进行腐蚀运算
    if ( Erosion(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB),type,num))
    { 
      // 设置脏标记
      pDoc->SetModifiedFlag(TRUE);
    }
    else
    {
      // 提示用户
      MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
    }
  // 解除锁定
  ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());
  // 恢复光标
  EndWaitCursor();    
}
