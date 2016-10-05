// FYFDoc.cpp : implementation of the CFYFDoc class
//

#include "stdafx.h"
#include "FYF.h"

#include "FYFDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFYFDoc

IMPLEMENT_DYNCREATE(CFYFDoc, CDocument)

BEGIN_MESSAGE_MAP(CFYFDoc, CDocument)
  //{{AFX_MSG_MAP(CFYFDoc)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFYFDoc construction/destruction

CFYFDoc::CFYFDoc()
{
  // TODO: add one-time construction code here
  m_hDIB = NULL;// 初始化变量
  m_palDIB = NULL;
  m_sizeDoc = CSize(1,1);
}

CFYFDoc::~CFYFDoc()
{
    if (m_hDIB != NULL)// 判断是否有DIB对象
  {   
    ::GlobalFree((HGLOBAL) m_hDIB);
  }
  
  
  if (m_palDIB != NULL)// 判断调色板是否存在
  {
    delete m_palDIB;
  }
}

BOOL CFYFDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFYFDoc serialization

void CFYFDoc::Serialize(CArchive& ar)
{
  if (ar.IsStoring())
  {
    // TODO: add storing code here
  }
  else
  {
    // TODO: add loading code here
  }
}

/////////////////////////////////////////////////////////////////////////////
// CFYFDoc diagnostics

#ifdef _DEBUG
void CFYFDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CFYFDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFYFDoc commands

BOOL CFYFDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
  CFile file;
  if (!file.Open(lpszPathName, CFile::modeRead | 
    CFile::shareDenyWrite))// 打开文件
  {         
    return FALSE;// 返回FALSE
  } 
  DeleteContents();
  m_hDIB=m_dib.LoadFile(file);
  if(m_hDIB==NULL)// 调用ReadDIBFile()读取图象
  {     
    return FALSE;
  }   
  SetDib();// 初始化DIB
  if (m_hDIB == NULL) // 判断读取文件是否成功
  {   
    AfxMessageBox("读取图象时出错");// 提示出错       
    return FALSE;// 返回FALSE
  }   
  SetPathName(lpszPathName);// 设置文件名称   
  SetModifiedFlag(FALSE);// 初始化胀标记为FALSE   
  return TRUE;// 返回TRUE
}

void CFYFDoc::SetDib()
{   
  LPSTR lpdib = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB); 
  
  if (m_dib.GetWidth(lpdib) > INT_MAX ||m_dib.GetHeight(lpdib) > INT_MAX)// 判断图象是否过大
  {
    ::GlobalUnlock((HGLOBAL) m_hDIB);       
    ::GlobalFree((HGLOBAL) m_hDIB); // 释放DIB对象      
    m_hDIB = NULL;// 设置DIB为空    
    AfxMessageBox("初始化失败");    
    return;
  } 
  m_sizeDoc = CSize((int)m_dib.GetWidth(lpdib), (int)m_dib.GetHeight(lpdib));// 设置文档大小  
  ::GlobalUnlock((HGLOBAL) m_hDIB); 
  m_palDIB = new CPalette;// 创建新调色板   
  if (m_palDIB == NULL)// 判断是否创建成功
  {   
    ::GlobalFree((HGLOBAL) m_hDIB); // 失败   
    m_hDIB = NULL;// 设置DIB对象为空
    return;
  } 
  // 调用CreateDIBPalette来创建调色板
  if (m_dib.ConstructPalette(m_hDIB, m_palDIB) == NULL)
  {       
    delete m_palDIB;// 删除       
    m_palDIB = NULL;// 设置为空 
    return;// 返回空
  }
}

BOOL CFYFDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
  // TODO: Add your specialized code here and/or call the base class
  CFile file;
  if(!file.Open(lpszPathName, CFile::modeCreate |// 打开文件
    CFile::modeReadWrite | CFile::shareExclusive))
  {
    return FALSE;// 返回FALSE
  }
  BOOL bSuccess = FALSE;  
  bSuccess = m_dib.SaveFile(m_hDIB, file);  // 保存图象 
  file.Close();// 关闭文件  
  SetModifiedFlag(FALSE);// 重置胀标记为FALSE
  if (!bSuccess)
  {     
    AfxMessageBox("保存BMP图象时出错");// 提示出错
  } 
  return bSuccess;
}


void CFYFDoc::UpdateObject(HGLOBAL hDIB)
{   
  if (m_hDIB != NULL)               // 判断DIB是否为空
  {   
    ::GlobalFree((HGLOBAL) m_hDIB);// 非空，则清除
  } 
  m_hDIB = hDIB;                     // 替换成新的DIB对象 
}
