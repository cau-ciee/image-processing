#if !defined(AFX_THREDIVDLG_H__94E53B97_62F5_424C_9EE4_E34654E23C8A__INCLUDED_)
#define AFX_THREDIVDLG_H__94E53B97_62F5_424C_9EE4_E34654E23C8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreDivDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThreDivDlg dialog

class CThreDivDlg : public CDialog
{
// Construction
public:
	CThreDivDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CThreDivDlg)
	enum { IDD = IDD_THREDivDlg };
	CEdit	m_visible;
	int		m_threshold;
	int		m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreDivDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThreDivDlg)
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREDIVDLG_H__94E53B97_62F5_424C_9EE4_E34654E23C8A__INCLUDED_)
