#if !defined(AFX_OPENDIG_H__DE2283B5_D524_4F1F_BDED_865DA35AEF97__INCLUDED_)
#define AFX_OPENDIG_H__DE2283B5_D524_4F1F_BDED_865DA35AEF97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenDig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenDig dialog

class COpenDig : public CDialog
{
// Construction
public:
	COpenDig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenDig)
	enum { IDD = IDD_OPENDLG };
	int		m_type;
	int		m_num;
	int     numvalue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenDig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenDig)
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

#endif // !defined(AFX_OPENDIG_H__DE2283B5_D524_4F1F_BDED_865DA35AEF97__INCLUDED_)
