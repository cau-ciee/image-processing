#if !defined(AFX_GRAYENHDLG_H__589BE34F_017C_4ACC_88F4_EC586E5E5679__INCLUDED_)
#define AFX_GRAYENHDLG_H__589BE34F_017C_4ACC_88F4_EC586E5E5679__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrayEnhDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrayEnhDlg dialog

class CGrayEnhDlg : public CDialog
{
// Construction
public:
	CGrayEnhDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrayEnhDlg)
	enum { IDD = IDD_GRAY_ENHANCEDlg };
	int		m_oralow;
	int		m_orahig;
	int		m_newhig;
	int		m_newlow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrayEnhDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrayEnhDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAYENHDLG_H__589BE34F_017C_4ACC_88F4_EC586E5E5679__INCLUDED_)
