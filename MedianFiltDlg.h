#if !defined(AFX_MEDIANFILTDLG_H__D7AEA31E_BBF6_41D3_9022_F40F90E2C88B__INCLUDED_)
#define AFX_MEDIANFILTDLG_H__D7AEA31E_BBF6_41D3_9022_F40F90E2C88B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedianFiltDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedianFiltDlg dialog

class CMedianFiltDlg : public CDialog
{
// Construction
public:
  CMedianFiltDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CMedianFiltDlg)
  enum { IDD = IDD_MEDIAN_FILTER };
  int   m_mediantype;
  int   mFilterH;
  int   mFilterW; 
  int   mFilterMX;
  int   mFilterMY;
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMedianFiltDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CMedianFiltDlg)
  virtual void OnOK();
  afx_msg void OnRadio1();
  afx_msg void OnRadio2();
  afx_msg void OnRadio3();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIANFILTDLG_H__D7AEA31E_BBF6_41D3_9022_F40F90E2C88B__INCLUDED_)
