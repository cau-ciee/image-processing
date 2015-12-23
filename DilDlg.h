#if !defined(AFX_DILDLG_H__2DB0069A_6D8F_4FBC_863F_6F46498CE59D__INCLUDED_)
#define AFX_DILDLG_H__2DB0069A_6D8F_4FBC_863F_6F46498CE59D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DilDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDilDlg dialog

class CDilDlg : public CDialog
{
// Construction
public:
	CDilDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDilDlg)
	enum { IDD = IDD_DILDLG };
	int		m_type;
	int		m_num;
	int     numvalue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDilDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDilDlg)
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

#endif // !defined(AFX_DILDLG_H__2DB0069A_6D8F_4FBC_863F_6F46498CE59D__INCLUDED_)
