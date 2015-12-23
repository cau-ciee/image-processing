#if !defined(AFX_EDGEDETDLG_H__4AF52BFC_C92C_40BB_803A_05C34CFE4045__INCLUDED_)
#define AFX_EDGEDETDLG_H__4AF52BFC_C92C_40BB_803A_05C34CFE4045__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EdgeDetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEdgeDetDlg dialog

class CEdgeDetDlg : public CDialog
{
// Construction
public:
	CEdgeDetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEdgeDetDlg)
	enum { IDD = IDD_EDGE_DETECTION };
	int		m_mode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdgeDetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEdgeDetDlg)
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDGEDETDLG_H__4AF52BFC_C92C_40BB_803A_05C34CFE4045__INCLUDED_)
