#if !defined(AFX_REGIONGROW_H__FC604DBA_F6DA_4121_AEE0_1EBFDB09FB25__INCLUDED_)
#define AFX_REGIONGROW_H__FC604DBA_F6DA_4121_AEE0_1EBFDB09FB25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegionGrow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegionGrow dialog

class CRegionGrow : public CDialog
{
// Construction
public:
  CRegionGrow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CRegionGrow)
  enum { IDD = IDD_REGION_GROW };
  CEdit m_seedyvisible;
  CEdit m_seedxvisible;
  int   m_seedtype;
  int   m_seedx;
  int   m_seedy;
  int   m_growthreshold;

  int   ImageWidth;
  int     ImageHeight;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CRegionGrow)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CRegionGrow)
  virtual void OnOK();
  afx_msg void OnRadio1();
  afx_msg void OnRadio2();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGIONGROW_H__FC604DBA_F6DA_4121_AEE0_1EBFDB09FB25__INCLUDED_)
