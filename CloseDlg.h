#if !defined(AFX_CLOSEDLG_H__B08D9116_4B58_4A33_A622_B18A83837F4F__INCLUDED_)
#define AFX_CLOSEDLG_H__B08D9116_4B58_4A33_A622_B18A83837F4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CloseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCloseDlg dialog

class CCloseDlg : public CDialog
{
// Construction
public:
  CCloseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CCloseDlg)
  enum { IDD = IDD_CLOSEDLG };
  int   m_type;
  int   m_num;
  int     numvalue;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CCloseDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CCloseDlg)
  afx_msg void OnRadio1();
  afx_msg void OnRadio2();
  afx_msg void OnRadio3();
  afx_msg void OnRadio4();
  afx_msg void OnRadio5();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEDLG_H__B08D9116_4B58_4A33_A622_B18A83837F4F__INCLUDED_)
