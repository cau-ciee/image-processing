// FYFView.h : interface of the CFYFView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FYFVIEW_H__8E9680ED_A3A6_4763_8667_2A8668263E91__INCLUDED_)
#define AFX_FYFVIEW_H__8E9680ED_A3A6_4763_8667_2A8668263E91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFYFView : public CView
{
protected: // create from serialization only
  CFYFView();
  DECLARE_DYNCREATE(CFYFView)

// Attributes
public:
  CFYFDoc* GetDocument();

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFYFView)
  public:
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  
  protected:
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CFYFView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  //{{AFX_MSG(CFYFView)
  afx_msg void OnTranspose();
  afx_msg void OnMirror();
  afx_msg void OnHistogram();
  afx_msg void OnGrayEqual();
  afx_msg void OnRotation();
  afx_msg void OnTranslation();
  afx_msg void OnZoom();
  afx_msg void OnLiner();
  afx_msg void OnStretch();
  afx_msg void OnThreshold();
  afx_msg void OnWindow();
  afx_msg void OnDct();
  afx_msg void OnWalhHar();
  afx_msg void OnLog();
  afx_msg void OnFourier();
  afx_msg void OnKL();
  afx_msg void OnInverRestore();
  afx_msg void OnWinnerRestore();
  afx_msg void OnGrayEnhDlg();    //灰度变换增强
  afx_msg void OnMedianFil();
  afx_msg void OnLaplasSharp();
  afx_msg void OnLowpassFiler();
  afx_msg void OnErosionCalculation();
  afx_msg void OnDilationCalculation();
  afx_msg void OnOpencloseCalculation();
  afx_msg void OnThiningCalculation();
  afx_msg void OnEdgeDetection();
  afx_msg void OnHoughTrans();
  afx_msg void OnOutline();
  afx_msg void OnContourtrace();
  afx_msg void OnThresholdDivide();
  afx_msg void OnProjection();
  afx_msg void OnSubtract();
  afx_msg void OnTempletematch();
  afx_msg void OnHuffmancoding();
  afx_msg void OnShannoncoding();
  afx_msg void OnRlecoding();
  afx_msg void OnGiflzw();
  afx_msg void OnWl();
  afx_msg void OnGrayEnhance();
  afx_msg void OnHistEnhance();
  afx_msg void OnHistEnh();
  afx_msg void OnHighpassFiler();
  afx_msg void OnHighpassFil();
  afx_msg void OnLowpassFil();
  afx_msg void OnSmoothEnhance();
  afx_msg void OnMeanEnh();
  afx_msg void OnLaplasTemp();
  afx_msg void OnThresholdDiv();
  afx_msg void OnRegionGrow();
  afx_msg void OnRegionGro();
  afx_msg void OnEdgeDif();
  afx_msg void OnHoughTra();
  afx_msg void OnErosionOpe();
  afx_msg void OnDilationOpr();
  afx_msg void OnOpenDlg();
  afx_msg void OnCloseDlg();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FYFView.cpp
inline CFYFDoc* CFYFView::GetDocument()
   { return (CFYFDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FYFVIEW_H__8E9680ED_A3A6_4763_8667_2A8668263E91__INCLUDED_)
