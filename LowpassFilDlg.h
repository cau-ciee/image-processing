#if !defined(AFX_LOWPASSFILDLG_H__12767276_65C5_4CAD_BBD4_A229E0541812__INCLUDED_)
#define AFX_LOWPASSFILDLG_H__12767276_65C5_4CAD_BBD4_A229E0541812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LowpassFilDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLowpassFilDlg dialog

class CLowpassFilDlg : public CDialog
{
// Construction
public:
  CLowpassFilDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CLowpassFilDlg)
  enum { IDD = IDD_LOWPASS_FILTER };
  int   m_lowfreq2;
  int   m_lowfreq1;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLowpassFilDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CLowpassFilDlg)
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOWPASSFILDLG_H__12767276_65C5_4CAD_BBD4_A229E0541812__INCLUDED_)
