// FYFDoc.h : interface of the CFYFDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FYFDOC_H__1CB1ECA8_7BFB_4E33_B2FA_15FDFA78685D__INCLUDED_)
#define AFX_FYFDOC_H__1CB1ECA8_7BFB_4E33_B2FA_15FDFA78685D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dib.h"
extern  m_dib;          //声明一个可用的外部成员变量
class CFYFDoc : public CDocument
{
protected: // create from serialization only
  CFYFDoc();
  DECLARE_DYNCREATE(CFYFDoc)

// Attributes
public:
    CDib m_dib;                               //声明一个Dib对象

// Operations
public:
  HGLOBAL GetHObject() const  //获取Dib对象的句柄
    { return m_hDIB; }
  CPalette* GetDocPal() const //获取调色板指针
    { return m_palDIB; }
  CSize GetDocDimension() const//获取调色板大小
    { return m_sizeDoc; }
  void UpdateObject(HGLOBAL hDIB);//更新dib对象

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFYFDoc)
  public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);
  virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
  virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CFYFDoc();
  void SetDib();                             //初始化dib对象
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

  HGLOBAL m_hDIB;
  CPalette* m_palDIB;
  CSize m_sizeDoc;
// Generated message map functions
protected:
  //{{AFX_MSG(CFYFDoc)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FYFDOC_H__1CB1ECA8_7BFB_4E33_B2FA_15FDFA78685D__INCLUDED_)
