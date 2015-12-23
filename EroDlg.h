#if !defined(AFX_ERODLG_H__662A6DE9_4C27_4F37_B8AD_978FA07015F3__INCLUDED_)
#define AFX_ERODLG_H__662A6DE9_4C27_4F37_B8AD_978FA07015F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EroDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEroDlg dialog

class CEroDlg : public CDialog
{
// Construction
public:
	CEroDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEroDlg)
	enum { IDD = IDD_ERODLG };
	int		m_type;
	int		m_num;
	int		numvalue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEroDlg)
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

#endif // !defined(AFX_ERODLG_H__662A6DE9_4C27_4F37_B8AD_978FA07015F3__INCLUDED_)
