#if !defined(AFX_LAPLACTEMDLG_H__94615E8A_EBD0_45DB_BEAE_515251774DE4__INCLUDED_)
#define AFX_LAPLACTEMDLG_H__94615E8A_EBD0_45DB_BEAE_515251774DE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LaplacTemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLaplacTemDlg dialog

class CLaplacTemDlg : public CDialog
{
// Construction
public:
  CLaplacTemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CLaplacTemDlg)
  enum { IDD = IDD_LAPLAC_TEMP };
  int   m_laplac;
  double  laplacvalue[9];
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLaplacTemDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CLaplacTemDlg)
  virtual void OnOK();
  afx_msg void OnRadio1();
  afx_msg void OnRadio2();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAPLACTEMDLG_H__94615E8A_EBD0_45DB_BEAE_515251774DE4__INCLUDED_)
