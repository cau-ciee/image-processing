// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__DAEA04C7_4542_46FD_BEB4_41F60281AE96__INCLUDED_)
#define AFX_DIB_H__DAEA04C7_4542_46FD_BEB4_41F60281AE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PalVersion   0x300                                 // ��ɫ��汾

class CDib : public CObject  
{
public:
  CDib();
  virtual ~CDib();
//����
public:
  //���ڲ���DIB�ĺ�������
  BOOL   DrawDib(HDC,LPRECT,HGLOBAL,LPRECT,CPalette*); //��ʾλͼ
    BOOL   ConstructPalette(HGLOBAL,CPalette*);          //�����߼���ɫ��
  LPSTR  GetBits(LPSTR);                               //ȡ��λͼ���������
  DWORD  GetWidth(LPSTR);                              //ȡ��λͼ�Ŀ��
  DWORD  GetHeight(LPSTR);                             //ȡ��λͼ�ĸ߶�
  WORD   GetPalSize(LPSTR);                            //ȡ�õ�ɫ��Ĵ�С
  WORD   GetColorNum(LPSTR);                           //ȡ��λͼ��������ɫ��Ŀ
  WORD   GetBitCount(LPSTR);                           //ȡ��λͼ����ɫ���
  HGLOBAL CopyObject(HGLOBAL);                         //���ڸ���λͼ����

  BOOL   SaveFile(HGLOBAL , CFile&);                    //�洢λͼΪ�ļ�
  HGLOBAL   LoadFile(CFile&);                          //���ļ��м���λͼ


//  ��ƺ���GetRequireWidth�����������λͼ���ֽڿ�ȱ�����4�ı�������һҪ��
  int     GetReqByteWidth(int );                     //ת������ֽ���GetRequireByteWidth
  long    GetRectWidth(LPCRECT );                    //ȡ������Ŀ��
  long    GetRectHeight(LPCRECT);                    //ȡ������ĸ߶�
public:
  void ClearMemory();
  void InitMembers();
public:
  LPBITMAPINFO        lpbminfo; // ָ��BITMAPINFO�ṹ��ָ��
  LPBITMAPINFOHEADER  lpbmihrd; //ָ��BITMAPINFOHEADER�ṹ��ָ��
  BITMAPFILEHEADER  bmfHeader;  //BITMAPFILEHEADER�ṹ
  LPSTR       lpdib;      //ָ��DIB��ָ��
  LPSTR       lpDIBBits;  // DIB����ָ��
  DWORD       dwDIBSize;  //DIB��С

  HGLOBAL       m_hDib;//DIB����ľ��
  
  RGBQUAD*      lpRgbQuag;//ָ����ɫ���ָ��
};

#endif // !defined(AFX_DIB_H__DAEA04C7_4542_46FD_BEB4_41F60281AE96__INCLUDED_)
