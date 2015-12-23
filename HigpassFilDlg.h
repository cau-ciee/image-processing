#if !defined(AFX_HIGPASSFILDLG_H__F07C1D26_330D_4EC2_A3AD_10EDBEA086C0__INCLUDED_)
#define AFX_HIGPASSFILDLG_H__F07C1D26_330D_4EC2_A3AD_10EDBEA086C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HigpassFilDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHigpassFilDlg dialog

class CHigpassFilDlg : public CDialog
{
// Construction
public:
	CHigpassFilDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHigpassFilDlg)
	enum { IDD = IDD_HIGHPASS_FILTER };
	int		m_highfreq1;
	int		m_highfreq2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHigpassFilDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHigpassFilDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIGPASSFILDLG_H__F07C1D26_330D_4EC2_A3AD_10EDBEA086C0__INCLUDED_)
