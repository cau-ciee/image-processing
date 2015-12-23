// function.h: interface for the function class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)
#define AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dib.h"
#include <math.h>
// ������
#define pi 3.1415926535
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#include <direct.h>
#include <complex>
using namespace std;
#define PI 3.14159265358979323846

//#endif // !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)

typedef struct{
	int Value;
	int Dist;
	int AngleNumber;
}	MaxValue;

/*************************************************************************
 * \�������ƣ�
 *   GrayLinTrans()
 * \�������:
 *	 LPSTR lpDIBBits		//ָ��Դͼ�������ָ��
 *	 LONG lmageWidth		//Դͼ��Ŀ��
 *	 LONG lmageHeight		// Դͼ��ĸ߶�
 *   int   oralow			// ԭʼͼ��ĻҶ�ֵ�������򣭵�ֵ
 *   int   orahig			// ԭʼͼ��ĻҶ�ֵ�������򣭸�ֵ
 *   int   newlow			// �任��ͼ��ҶȵĶ�̬��Χ����ֵ
 *   int   newhig			// �任��ͼ��ҶȵĶ�̬��Χ����ֵ
 * \����ֵ:
 *   BOOL               // �ɹ�����TRUE�����򷵻�FALSE��
 * \˵��:
 *   �ú���������ͼ��ָ���ĻҶȷֲ����лҶȱ任��Ҫ����ʵ�ֻҶȷֲ�����չ
*************************************************************************/
BOOL GrayLinTrans(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,int oralow, int orahig, int newlow, int newhig)
{
	unsigned char*	lpSrc;								// ָ��Դͼ���ָ��
	int i;												// ѭ������
	int j;												// ѭ������
	BYTE	byMap[256];								// ����Ҷ�ӳ���
	for (i = 0; i <= oralow; i++)								//���Ҷȼ�С��Ҫ��ǿ�ĻҶȼ�ʱ
	{
		if (newlow > 0)									//�ж��»Ҷȼ��Ƿ����0
		{
			byMap[i] = newlow;							//������ֵ
		}
		else
		{
			byMap[i] = 0;								//ֱ�Ӹ�ֵΪ0
		}
	}
	for (; i <= orahig; i++)
	{
		if (orahig != oralow)								// �ж�orahig�Ƿ����oralow(��ֹ
											 //��ĸΪ0)
		{
			//���Ա任
			byMap[i] = newlow + (BYTE) ((newhig - newlow) * (i - oralow) / (orahig - oralow));
		}
		else
		{
			byMap[i] = newlow;							//ֱ�Ӹ�ֵΪnewlow
		}
	}
	for (; i < newhig; i++)
	{
		if (newhig <= 255)								//�ж�d�Ƿ����255
		{
			byMap[i] = newhig;							//ֱ�Ӹ�ֵΪnewhig
		}
		else
		{
			byMap[i] = 255;								//ֱ�Ӹ�ֵΪ255
		}
	}
	for(i = 0; i < lmageHeight; i++)							//��ͼ���ÿ������ֵ���б任
	{
		for(j = 0; j < lmageWidth; j++)						//ÿ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpSrc = byMap[*lpSrc];						//���µĻҶ����ԭ�еĻҶ�
		}
	}
	return TRUE;										//����
}

/*************************************************************************
* \�������ƣ�
 *   GrayHistEnhance()
* \�������:
 *	 LPSTR lpDIBBits		//ָ��Դͼ�������ָ��
 *	 LONG lmageWidth		//Դͼ��Ŀ��
 *	 LONG lmageHeight		//Դͼ��ĸ߶�
 * \����ֵ:
 *   BOOL		       	//�ɹ��򷵻�TRUE�����򷵻�FALSE
 * \˵��:
 *   �ú�����ָ����ͼ�����ֱ��ͼ���⻯����
*************************************************************************/
 BOOL GrayHistEnhance(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
 {
	unsigned char*	lpSrc;									//ָ��Դͼ���ָ��
	int	nTemp;											//��ʱ����
	int j;													//ѭ������
	int i;													//ѭ������
	BYTE	byMap[256];									//�ۻ�ֱ��ͼ�����Ҷ�ӳ���
	int	nCount[256];										//ֱ��ͼ
	for (i = 0; i < 256; i ++)									//���ü���Ϊ0
	{
		nCount[i] = 0;										//����
	}
	for(i = 0; i < lmageHeight; i++)								//ÿ��
	{
		for(j = 0; j < lmageWidth; j++)							//ÿ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			nCount[*(lpSrc)]++;								//������1
		}
	}
	for (i = 0; i < 256; i++)										//�����ۻ�ֱ��ͼ
	{
		nTemp = 0;										//��ʼΪ0
		for (j = 0; j <= i ; j++)
		{
			nTemp += nCount[j];
		}
		byMap[i] = (BYTE) (nTemp * 255 / lmageHeight / lmageWidth); 	//�����Ӧ���»Ҷ�ֵ
//˵����* 255ʵ���Ͼ��ǽ��µĻҶ�ֵҲת��Ϊ0��255�ķ�Χ��
	}
	for(i = 0; i < lmageHeight; i++)
	{
		for(j = 0; j < lmageWidth; j++)							//ÿ��
		{
			//ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpSrc = byMap[*lpSrc];							//�����µĻҶ�ֵ
		}
	}
	return TRUE;											//����
}

/*************************************************************************
* �������ƣ�
 *   MedianValue()
* ����:
 *   unsigned char * FiltValue	- ָ��Ҫ��ȡ��ֵ������ָ��
 *   int   iFilterLen				- ���鳤��
* ����ֵ:
 *   unsigned char				- ����ָ���������ֵ��
* ˵��:
 *   �ú�����ð�ݷ���һά����������򣬲���������Ԫ�ص���ֵ��
************************************************************************/

unsigned char MedianValue(unsigned char * FiltValue, int mFilterLen)
{
	int		i;										// ѭ������
	int		j;										// ѭ������
	unsigned char Temp;									// �м����
	// ��ð�ݷ��������������
	for (j = 0; j < mFilterLen - 1; j ++)
	{
		for (i = 0; i < mFilterLen - j - 1; i ++)
		{
			if (FiltValue[i] > FiltValue[i + 1])					// ǰ���ֵ���ں����
			{
				Temp = FiltValue[i];
				FiltValue[i] = FiltValue[i + 1];				// ���ߵ�ֵ����
				FiltValue[i + 1] = Temp;
			}
		}
	}
	if ((mFilterLen & 1) > 0)								// ������ֵ
	{
		//������������Ԫ�أ������м�һ��Ԫ��
		Temp = FiltValue[(mFilterLen + 1) / 2];
	}
	else
	{
		//������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ
		Temp = (FiltValue[mFilterLen / 2] + FiltValue[mFilterLen / 2 + 1]) / 2;
	}
	return Temp;										// ������ֵ
}

/*************************************************************************
* �������ƣ�
 *   MedianFilter()
* ����:
 *   LPSTR lpDIBBits			- ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth		- Դͼ���ȣ���������
 *   LONG  lmageHeight		- Դͼ��߶ȣ���������
 *   int   mFilterH				- �˲����ĸ߶�
 *   int   mFilterW			- �˲����Ŀ��
 *   int   mFilterMX			- �˲���������Ԫ��X����
 *   int   mFilterMY			- �˲���������Ԫ��Y����
* ����ֵ:
 *   BOOL					- �ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 *   �ú�����DIBͼ�������ֵ�˲���
************************************************************************/
BOOL MedianFilter(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,
				  int mFilterH, int mFilterW, int mFilterMX, int mFilterMY)
{
	unsigned char* lpSrc;                  //ָ��ԭͼ���ָ��
	unsigned char* lpDst;                  //ָ��Ҫ���������ָ��
	LPBYTE lpImage;                        //ָ����ͼ���ָ��
	unsigned char* FiltValue;              //ָ���˲��������ָ��
	int i;                                 //ѭ������
	int j;                                 //ѭ������
	int k;                                 
	int l;
    lpImage = (LPBYTE) new char[lmageWidth *lmageHeight];
	if(lpImage == NULL)
	{
		return FALSE;
	}
	memcpy(lpImage, lpDIBBits, lmageWidth *lmageHeight);
	FiltValue = new unsigned char[mFilterH *mFilterW];			// ��ʱ�����ڴ棬�Ա����˲�������
	if (FiltValue == NULL)								// �ж��Ƿ��ڴ����ʧ��
	{
		delete[]lpImage;									// �ͷ��ѷ����ڴ�
		return FALSE;									// �����ڴ�ʧ��
	}
	// ��ʼ��ֵ�˲�
	for(i = mFilterMY; i < lmageHeight - mFilterH + mFilterMY + 1; i++)
	{
		for(j = mFilterMX; j < lmageWidth - mFilterW + mFilterMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			for (k = 0; k < mFilterH; k++)					// ��ȡ�˲�������
			{
				for (l = 0; l < mFilterW; l++)
				{
					// ָ��DIB��i - iFilterMY + k�У���j - iFilterMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lmageWidth  * (lmageHeight - 1 - i + mFilterMY 
						  - k) + j - mFilterMX + l;
					FiltValue[k * mFilterW + l] = *lpSrc;		// ��������ֵ
				}
			}
			*lpDst= MedianValue(FiltValue, (mFilterH * mFilterW)); // ��ȡ��ֵ
		}
	}
	memcpy(lpDIBBits, lpImage, lmageWidth*lmageHeight);			// ���Ʊ任���ͼ��
	delete[]lpImage;										// �ͷ��ڴ�
	delete[]FiltValue;
	return TRUE;										// ����
}

/*************************************************************************
 *
 * \�������ƣ�
 *   FFT_1D()
 *
 * \�������:
 *   complex<double> * pCTData	- ָ��ʱ�����ݵ�ָ�룬�������Ҫ�任������
 *   complex<double> * pCFData	- ָ��Ƶ�����ݵ�ָ�룬����ľ����任������
 *   nLevel						������Ҷ�任�����㷨�ļ�����2��������
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   һά���ٸ���Ҷ�任��
 *
 *************************************************************************
 */
void FFT_1D(complex<double> * pCTData, complex<double> * pCFData, int nLevel)
{
		// ѭ�����Ʊ���
	int		i;
	int     j;
	int     k;

	// ����Ҷ�任����
	int	nCount =0 ;

	// ���㸵��Ҷ�任����
	nCount =(int)pow(2,nLevel) ;
	
	// ĳһ���ĳ���
	int		nBtFlyLen;
	nBtFlyLen = 0 ;
	
	// �任ϵ���ĽǶ� ��2 * PI * i / nCount
	double	dAngle;
	
	complex<double> *pCW ;
	
	// �����ڴ棬�洢����Ҷ�仯��Ҫ��ϵ����
	pCW  = new complex<double>[nCount / 2];

    // ���㸵��Ҷ�任��ϵ��
	for(i = 0; i < nCount / 2; i++)
	{
		dAngle = -2 * PI * i / nCount;
		pCW[i] = complex<double> ( cos(dAngle), sin(dAngle) );
	}

	// �任��Ҫ�Ĺ����ռ�
	complex<double> *pCWork1,*pCWork2; 
	
	// ���乤���ռ�
	pCWork1 = new complex<double>[nCount];

	pCWork2 = new complex<double>[nCount];

	
	// ��ʱ����
	complex<double> *pCTmp;
	
	// ��ʼ����д������
	memcpy(pCWork1, pCTData, sizeof(complex<double>) * nCount);

	// ��ʱ����
	int nInter; 
	nInter = 0;

	// �����㷨���п��ٸ���Ҷ�任
	for(k = 0; k < nLevel; k++)
	{
		for(j = 0; j < (int)pow(2,k); j++)
		{
			//���㳤��
			nBtFlyLen = (int)pow( 2,(nLevel-k) );
			
			//�������ţ���Ȩ����
			for(i = 0; i < nBtFlyLen/2; i++)
			{
				nInter = j * nBtFlyLen;
				pCWork2[i + nInter] = 
					pCWork1[i + nInter] + pCWork1[i + nInter + nBtFlyLen / 2];
				pCWork2[i + nInter + nBtFlyLen / 2] =
					(pCWork1[i + nInter] - pCWork1[i + nInter + nBtFlyLen / 2]) 
					* pCW[(int)(i * pow(2,k))];
			}
		}

		// ���� pCWork1��pCWork2������
		pCTmp   = pCWork1	;
		pCWork1 = pCWork2	;
		pCWork2 = pCTmp		;
	}
	
	// ��������
	for(j = 0; j < nCount; j++)
	{
		nInter = 0;
		for(i = 0; i < nLevel; i++)
		{
			if ( j&(1<<i) )
			{
				nInter += 1<<(nLevel-i-1);
			}
		}
		pCFData[j]=pCWork1[nInter];
	}
	
	// �ͷ��ڴ�ռ�
	delete pCW;
	delete pCWork1;
	delete pCWork2;
	pCW		=	NULL	;
	pCWork1 =	NULL	;
	pCWork2 =	NULL	;

}

/*************************************************************************
 *
 * \�������ƣ�
 *   FFT_2D()
 *
 * \�������:
 *   complex<double> * pCTData	- ͼ������
 *   int    nWidth				- ���ݿ��
 *   int    nHeight				- ���ݸ߶�
 *   complex<double> * pCFData	- ����Ҷ�任��Ľ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ��ά����Ҷ�任��
 *
 ************************************************************************
 */
void FFT_2D(complex<double> * pCTData, int nWidth, int nHeight, complex<double> * pCFData)
{
	
	// ѭ�����Ʊ���
	int	x;
	int	y;
	
	// ��ʱ����
	double	dTmpOne;
	double  dTmpTwo;
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		nTransWidth;
	int 	nTransHeight;

	// ������и���Ҷ�任�Ŀ��	��2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;
	
	// ������и���Ҷ�任�ĸ߶� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;	
	
	// x��y�����У������ϵĵ�������
	int		nXLev;
	int		nYLev;

	// ����x��y�����У������ϵĵ�������
	nXLev = (int) ( log(nTransWidth)/log(2) +  0.5 );
	nYLev = (int) ( log(nTransHeight)/log(2) + 0.5 );
	
	for(y = 0; y < nTransHeight; y++)
	{
		// x������п��ٸ���Ҷ�任
		FFT_1D(&pCTData[nTransWidth * y], &pCFData[nTransWidth * y], nXLev);
	}
	
	// pCFData��Ŀǰ�洢��pCTData�����б任�Ľ��
	// Ϊ��ֱ������FFT_1D����Ҫ��pCFData�Ķ�ά����ת�ã���һ������FFT_1D����
	// ����Ҷ�б任��ʵ�����൱�ڶ��н��и���Ҷ�任��
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTData[nTransHeight * x + y] = pCFData[nTransWidth * y + x];
		}
	}
	
	for(x = 0; x < nTransWidth; x++)
	{
		// ��x������п��ٸ���Ҷ�任��ʵ�����൱�ڶ�ԭ����ͼ�����ݽ����з����
		// ����Ҷ�任
		FFT_1D(&pCTData[x * nTransHeight], &pCFData[x * nTransHeight], nYLev);
	}

	// pCFData��Ŀǰ�洢��pCTData������ά����Ҷ�任�Ľ��������Ϊ�˷����з���
	// �ĸ���Ҷ�任�����������ת�ã����ڰѽ��ת�û���
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTData[nTransWidth * y + x] = pCFData[nTransHeight * x + y];
		}
	}

	memcpy(pCTData, pCFData, sizeof(complex<double>) * nTransHeight * nTransWidth );
}

/*************************************************************************
 *
 * \�������ƣ�
 *   IFFT_2D()
 *
 * \�������:
 *   complex<double> * pCFData	- Ƶ������
 *   complex<double> * pCTData	- ʱ������
 *   int    nWidth				- ͼ�����ݿ��
 *   int    nHeight				- ͼ�����ݸ߶�
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ��ά����Ҷ���任��
 *
 ************************************************************************
 */
void IFFT_2D(complex<double> * pCFData, complex<double> * pCTData, int nWidth, int nHeight)
{
	// ѭ�����Ʊ���
	int	x;
	int	y;
	
	// ��ʱ����
	double	dTmpOne;
	double  dTmpTwo;
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		nTransWidth;
	int 	nTransHeight;

	// ������и���Ҷ�任�Ŀ��	��2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;
	
	// ������и���Ҷ�任�ĸ߶� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;
	
	// ���乤����Ҫ���ڴ�ռ�
	complex<double> *pCWork= new complex<double>[nTransWidth * nTransHeight];

	//��ʱ����
	complex<double> *pCTmp ;
	
	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTmp = &pCFData[nTransWidth * y + x] ;
			pCWork[nTransWidth * y + x] = complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// ���ø���Ҷ���任
	FFT_2D(pCWork, nWidth, nHeight, pCTData) ;
	
	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTmp = &pCTData[nTransWidth * y + x] ;
			pCTData[nTransWidth * y + x] = 
				complex<double>( pCTmp->real()/(nTransWidth*nTransHeight),
								 -pCTmp->imag()/(nTransWidth*nTransHeight) );
		}
	}
	delete pCWork ;
	pCWork = NULL ;
}

/*************************************************************************
 * \�������ƣ�
 *   ButterWorthHighPass()
 * \�������:
 *	 LPSTR lpDIBBits					- ָ����Ҫ�˲���ͼ������ָ��
 *   int nWidth							- ���ݿ��
 *   int nHeight						- ���ݸ߶�
 *   int nRadius            - ButterWorth��ͨ�˲���"�빦��"��
* \����ֵ:
 *    BOOL								// �ɹ�����TRUE�����򷵻�FALSE��
* \˵��:
 *  pDIBBits ��ָ����Ҫ�˲���ͼ������ָ�롣
 *  ����ButterWorth��ͨ�˲���������Ȼ�洢��lpDIBBits ���С�
 **************************************************************************/
BOOL ButterWorthHighPass(LPSTR lpDIBBits, LONG nWidth, LONG nHeight, int nRadius)
{
	unsigned char*	lpSrc;							// ָ��Դͼ���ָ��
	int y ;										// ѭ�����Ʊ���
	int x ;										// ѭ�����Ʊ���
	double dTmpOne ;								//�����ʱ����
	double dTmpTwo ;								//�����ʱ����
	double H ;										// ButterWorth �˲�ϵ��
	int nTransWidth ;								// ����Ҷ�任�Ŀ�ȣ�2���������ݣ�
	int nTransHeight;								// ����Ҷ�任�ĸ߶ȣ�2���������ݣ�
	double dReal ;									// ����Ҷ�任��ʵ��
	double dImag;									// ����Ҷ�任���鲿
	double unchValue;								// ����ͼ������ػҶȵ���ʱ����
	complex<double> * pCTData ;						// ָ��ʱ�����ݵ�ָ��
	complex<double> * pCFData ;						// ָ��Ƶ�����ݵ�ָ��
	// ������и���Ҷ�任�ĵ���������2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// ������и���Ҷ�任�ĵ��������� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;	
	pCTData=new complex<double>[nTransWidth * nTransHeight];	// �����ڴ�
	pCFData=new complex<double>[nTransWidth * nTransHeight];	// �����ڴ�
	// ͼ�����ݵĿ�͸߲�һ����2���������ݣ�����pCTData��һ����������Ҫ��0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// ����
		}
	}
	for(y=0; y<nHeight; y++)						// ��ͼ�����ݴ���pCTData
	{
		for(x=0; x<nWidth; x++)
		{
		// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;		// ����Ҷ���任
	for(y=0; y<nTransHeight; y++)					// ���濪ʼʵʩButterWorth��ͨ�˲�
	{
		for(x=0; x<nTransWidth; x++)
		{
			H = (double)(y*y+x*x) ; 
			H = (nRadius * nRadius) / H ; 
			H = 1/(1+H);						// ��Hֵ
			pCFData[y*nTransWidth + x]=complex<double>(H*(pCFData[y*nTransWidth + x].real()),
					 H*(pCFData[y*nTransWidth + x].imag())  );
		}
	}
	// ����ButterWorth��ͨ�˲���ͼ����з��任
	IFFT_2D(pCFData, pCTData, nWidth, nHeight);
	for(y=0; y<nHeight; y++)						// ���任�����ݴ���lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue = max(0,min(255,sqrt(dReal*dReal+dImag*dImag)+100 ));
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}	
	delete pCTData;									// �ͷ��ڴ�
	delete pCFData;									// �ͷ��ڴ�
	pCTData = NULL;
	pCFData = NULL;
	return (true);									// ���ؽ��
}

/*************************************************************************
* \�������ƣ�
 *   ButterWorthLowPass()
* \�������:
 *	 LPSTR lpDIBBits					- ָ����Ҫ�˲���ͼ������ָ��
 *   int nWidth						- ���ݿ��
 *   int nHeight						- ���ݸ߶�
 *   int nRadius						- ButterWorth��ͨ�˲���"�빦��"��
* \����ֵ:
 *    BOOL								// �ɹ�����TRUE�����򷵻�FALSE��
* \˵��:
 *  pDIBBits ��ָ����Ҫ�˲���ͼ������ָ�롣
 *  ����ButterWorth��ͨ�˲���������Ȼ�洢��lpDIBBits ���С�
 **************************************************************************/
BOOL ButterWorthLowPass(LPSTR lpDIBBits, LONG nWidth, LONG nHeight, int nRadius)
{
	unsigned char*	lpSrc;							// ָ��Դͼ���ָ��
	int y ;										// ѭ�����Ʊ���
	int x ;										// ѭ�����Ʊ���
	double dTmpOne ;								//�����ʱ����
	double dTmpTwo ;								//�����ʱ����
	double H ;										// ButterWorth �˲�ϵ��
	int nTransWidth ;								// ����Ҷ�任�Ŀ�ȣ�2���������ݣ�
	int nTransHeight;								// ����Ҷ�任�ĸ߶ȣ�2���������ݣ�
	double dReal ;									// ����Ҷ�任��ʵ��
	double dImag;									// ����Ҷ�任���鲿
	double unchValue;								// ����ͼ������ػҶȵ���ʱ����
	complex<double> * pCTData ;						// ָ��ʱ�����ݵ�ָ��
	complex<double> * pCFData ;						// ָ��Ƶ�����ݵ�ָ��
	// ������и���Ҷ�任�ĵ���������	��2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// ������и���Ҷ�任�ĵ��������� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;	
	pCTData=new complex<double>[nTransWidth * nTransHeight]; // �����ڴ�
	pCFData=new complex<double>[nTransWidth * nTransHeight]; // �����ڴ�
	// ͼ�����ݵĿ�͸߲�һ����2���������ݣ�����pCTData��һ����������Ҫ��0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// ����
		}
	}
	for(y=0; y<nHeight; y++)							// ��ͼ�����ݴ���pCTData
	{
		for(x=0; x<nWidth; x++)
		{
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}	
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;			// ����Ҷ���任
	for(y=0; y<nTransHeight; y++)						// ��ʼʵʩButterWorth��ͨ�˲�
	{
		for(x=0; x<nTransWidth; x++)
		{
			H = (double)(y*y+x*x) ; 
			H = H / (nRadius * nRadius); 
			H = 1/(1+H)  ;							// ��Hֵ
			pCFData[y*nTransWidth + x]=complex<double>(pCFData[y*nTransWidth + x].real()*H, 
			pCFData[y*nTransWidth + x].imag()*H);
		}
	}
	// ����ButterWorth��ͨ�˲���ͼ����з��任
	IFFT_2D(pCFData, pCTData, nWidth, nHeight);
	for(y=0; y<nHeight; y++)							// ���任�����ݴ���lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue = max(0,min(255,sqrt(dReal*dReal+dImag*dImag) ));
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}
	delete pCTData;									// �ͷ��ڴ�
	delete pCFData;									// �ͷ��ڴ�
	pCTData = NULL;
	pCFData = NULL;
	return (true);									//���ؽ��	
}

/*************************************************************************
 * \�������ƣ�
 *  Template()
 * \�������:
 *	 LPSTR lpDIBBits		- ָ��Դͼ�������ָ��
 *	 LONG lmageWidth		- Դͼ��Ŀ��
 *	 LONG lmageHeight		- Դͼ��ĸ߶�
 *   int nTempWidth		- ģ��Ŀ��
 *   int nTempHeight		- ģ��ĸ߶�
 *   int nTempCenX		- ģ�����ĵ�X���꣨�����ģ�壩
 *   int nTempCenY		- ģ�����ĵ�Y���꣨�����ģ�壩
 *   double* Tempdata		- ģ�������ָ��
 *   double* TempCoef		- ģ���ϵ��
 * \����ֵ:
 *   BOOL			- �ɹ��򷵻�TRUE�����򷵻�FALSE
 * \˵��:
 *   �ú�����ָ����ģ���lpDIBBitsָ���ͼ�����ģ�������ģ��Ķ����˿�ȣ��߶ȣ���������
*��ϵ����ģ������ݴ����Tempdata�С���ͼ�����ģ���������Ȼ�����lpDIBBitsָ��Ķ���
*�С���Ҫע����ǣ��ú���ֻ�ܴ���8λ��ͼ�󣬷���ָ������ݽ�����
 **************************************************************************/
BOOL  Template(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,
					 int nTempWidth, int nTempHeight, 
					 int nTempCenX, int nTempCenY,
					 double* Tempdata, double TempCoef)
{
	LPBYTE			lpImage;								// ��ʱ���ͼ�����ݵ�ָ��
	int 		i;											// ѭ������
	int		j;											// ѭ������
	int 		k;											// ѭ������
	int 		l;											// ѭ������
	unsigned char*	lpSrc;									// ָ��Դͼ���ָ��
	unsigned char*	lpDst;									// ָ��Ҫ���������ָ��
	double	dbResult;										// ������
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];			// �����ڴ�
	if (lpImage == NULL)										// �ж��Ƿ��ڴ����ʧ��
	{
		return FALSE;										// �����ڴ�ʧ��
	}
	
	// ��ԭʼͼ������ݿ�������ʱ����ڴ���
	memcpy(lpImage, lpDIBBits, lmageWidth*lmageHeight);
	// ����ģ����㣬��(��ȥ��Ե����)
	for(i = nTempCenY ; i <lmageHeight - nTempHeight + nTempCenY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = nTempCenX; j < lmageWidth - nTempWidth + nTempCenX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			dbResult = 0;										// ��0
			for (k = 0; k < nTempHeight; k++)
			{
				for (l = 0; l < nTempWidth; l++)
				{
					// ָ��DIB��i - iFilterMY + k�У���j - iFilterMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i + nTempCenY - k) + j - nTempCenX + l;
					dbResult += (* lpSrc) * Tempdata[k * nTempWidth + l];	// ��������ֵ
				}
			}
			dbResult *= TempCoef;								// ����ϵ��
			dbResult = (double ) fabs(dbResult);						// ȡ����ֵ
			if(dbResult > 255)									// �ж��Ƿ񳬹�255
			{
				* lpDst = 255;									// ֱ�Ӹ�ֵΪ255
			}
			else
			{
				* lpDst = (unsigned char) (dbResult + 0.5);				// ��ֵ
			}
		}
	}
	memcpy(lpDIBBits, lpImage, lmageWidth*lmageHeight);				//���Ʊ任���ͼ��
	delete[] lpImage;												// �ͷ��ڴ�
	return TRUE;												// ����
}

/*************************************************************************
 * �������ƣ�
 *   RegionDivideThreshold()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int threshold		- �ָ�����
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶ�ͼ����й̶���ֵ�ָ
 ************************************************************************/
BOOL RegionDivideThreshold(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int threshold)
{
	int i;  //ѭ������
	int j;	//ѭ������
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	//����ֵ
	unsigned char pixeltemp;
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= threshold)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}
	return true;
}

/*************************************************************************
 * \�������ƣ�
 *   RegionDivideAdaptive()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶ�ͼ���������Ӧ��ֵ�ָ��ͼ��ֳ��ĸ���ͼ��Ȼ�����ÿ����ͼ��ľ�ֵ��
 *  ���ݾ�ֵ������ֵ����ֵֻ��Ӧ���ڶ�Ӧ����ͼ��
 **************************************************************************/
BOOL RegionDivideAdaptive(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	int i;  //ѭ������
	int j;	//ѭ������
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	//����ֵ
	unsigned char pixeltemp;	
	// ��ͼ��Ҷȵ�ƽ��ֵ
	int nAvg ;
	nAvg = 0 ; //��ʼ��Ϊ0
	// ������ͼ�����ɨ�裺
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//�Ҷȵ��ۼ�
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// �����ֵ
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// ������ͼ�����ɨ�裺
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

	nAvg =0;   //��ʼ��Ϊ0

	// ������ͼ�����ɨ�裺
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//�Ҷȵ��ۼ�
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// �����ֵ
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// ������ͼ�����ɨ�裺
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

	nAvg =0;   //��ʼ��Ϊ0

	// ������ͼ�����ɨ�裺
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//�Ҷȵ��ۼ�
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// �����ֵ
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// ������ͼ�����ɨ�裺
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

		nAvg =0;   //��ʼ��Ϊ0

	// ������ͼ�����ɨ�裺
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//�Ҷȵ��ۼ�
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// �����ֵ
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// ������ͼ�����ɨ�裺
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}
	return true;
}

/*************************************************************************
 * \�������ƣ�
 *   RegionGrow()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 *	 int nThreshold			- ������������
 *	 int seedx				- �����������ӵĺ�����
 *	 int seedy				- �����������ӵ�������
  *	 int mode				- �����������ӵ�ѡȡ����
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * \˵��:
 *   �������Ĵ������ǽ�������������ʾΪ��ɫ���أ�δ���������ʾΪ��ɫ���ء�
 *   ��������һ����������Ƚ���Ҫ�����⣺
 *		1. ���ӵ��ѡȡ
 *		2. ����׼��
 *		3. ��ֹ����
 *	 ������Ϊ��������������Ҫ�������������ÿ���������ĺû�ֱ�ӹ�ϵ��
 *	 ���������Ľ����
 *************************************************************************/
BOOL RegionGrow(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int nThreshold,int seedx,int seedy,int mode)
{	
	//�������ڴ��������������
	static int Dx[]={-1,0,1,0};	//X��
	static int Dy[]={0,1,0,-1};	//y��
	// ��ʱ���ͼ�����ݵ�ָ��
	LPBYTE			lpImage;	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	unsigned char*	lpSrc1;
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// �����ڴ�
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	// ��Ŀ��ͼ���������س�ʼ��Ϊ�׵�
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);
	// ���ӵ�
	CPoint seed;
	if(mode==0) // ���ѡ�����ӵ�Ϊͼ�������
	{
		// �������ӵ�Ϊͼ�������
		seed.x=lmageWidth/2;
		seed.y=lmageHeight/2;
	}
	else //�Լ��������ӵ�
	{
		// �������ӵ�Ϊ�����
		seed.x=seedx;
		seed.y=seedy;
	}

	// �����ջ���ֱ����X Y����
	int * GrowX ;
	int * GrowY ;
	
	// ����ռ䣬���Ϊͼ���������Ŀ
	GrowX = new int [ lmageWidth * lmageHeight];
	GrowY = new int [ lmageWidth * lmageHeight];

	
	// �����ջ�������յ�
	// ��Start=End, ��ʾ��ջ��ֻ��һ����
	int Start ;
	int End   ;
	//��ʼ��
	Start = 0 ;
	End   = 0 ;
	// �����ӵ������ѹ��ջ
	GrowX[End] = seed.x;
	GrowY[End] = seed.y;
	// ��ǰ���ڴ��������
	CPoint Current;
	// ѭ�����Ʊ���
	int k ;
	// ͼ��ĺ�������,�����Ե�ǰ���ص�4������б���
	int xx;
	int yy;
	while (Start<=End)
	{
		// ��ǰ���ӵ������
		Current.x = GrowX[Start];
		Current.y = GrowY[Start];
		// �Ե�ǰ���4������б���
		for (k=0; k<4; k++)	
		{	
			// 4�������ص�����
			xx = Current.x+Dx[k];
			yy = Current.y+Dy[k];
			
			// �ж�����(xx��yy) �Ƿ���ͼ���ڲ�
			// �ж�����(xx��yy) �Ƿ��Ѿ������
			// *lpDst==255 ��ʾ��û�д���
			// ָ��Դͼ��(xx��yy)���ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * (lmageHeight-yy) + xx;
			lpSrc1 = (unsigned char *)lpDIBBits + lmageWidth * (lmageHeight-Current.y) + Current.x;
			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (unsigned char *)lpImage + lmageWidth * (lmageHeight-yy) + xx;
			// �����������ж�����(xx��yy)�͵�ǰ����(nCurrX,nCurrY) ����ֵ��ľ���ֵ
			if ((xx < lmageWidth) && (xx>=0) && (yy<lmageHeight) && (yy>=0) && (*lpDst==255) 
					&& abs(*lpSrc-*lpSrc1)<nThreshold )
			{
				// ��ջ��β��ָ�����һλ
				End++;
				// ����(xx��yy) ѹ��ջ
				GrowX[End] = xx;
				GrowY[End] = yy;
				// Ŀ��ͼ��Ϊ�ڵ㣬ͬʱҲ���������ش����
				*lpDst=0 ;
			}
		}
		Start++;
	}
	// ���������������ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// �ͷ��ڴ�
	delete[] lpImage;
	delete[] GrowX;
	delete[] GrowY;
	// ����
	return TRUE;
}

/*************************************************************************
 * �������ƣ�
 *   EdgeDetection()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *	 int mode			- ��������
 * ����ֵ:
 *   BOOL               - ��Ե���ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú�����Sobel��LOG��Ե������Ӷ�ͼ����б�Ե������㡣
 * Ҫ��Ŀ��ͼ��Ϊ�Ҷ�ͼ��
 ************************************************************************/
BOOL EdgeDetection(LPSTR lpDIBBits,LONG lmageWidth,LONG lmageHeight,int mode)
{
	int nTempWidth;		//ģ��Ŀ��
    int nTempHeight;	 // ģ��ĸ߶�
    int nTempCenX;		//ģ�����ĵ�X���꣨�����ģ�壩
    int nTempCenY;		//ģ�����ĵ�Y���꣨�����ģ�壩
    double* Tempdata;	//ģ�������ָ��	
	double TempCoef;	//ģ��ϵ��
	//ѭ������
	int i;
	int j;
	if(mode==0)
	{
		//ָ�򻺴�ͼ���ָ��
		unsigned char* lpDst1;
		unsigned char* lpDst2;
		LPBYTE lpImage1;
		LPBYTE lpImage2;
		//��ʱ�����ڴ棬�Ա�����ͼ��
		lpImage1 = (LPBYTE) new char[lmageWidth*lmageHeight];
		lpImage2 = (LPBYTE) new char[lmageWidth*lmageHeight];
		//�ж��Ƿ��ڴ����ʧ��
		if (lpImage1 == NULL)
		{
			//�����ڴ�ʧ��
			return FALSE;
		}
		//�ж��Ƿ��ڴ����ʧ��
		if (lpImage2 == NULL)
		{
			// �����ڴ�ʧ��
			return FALSE;
		}
		// ��ʼ��ͼ��Ϊԭʼͼ��
		memcpy(lpImage1, lpDIBBits, lmageWidth*lmageHeight);
		memcpy(lpImage2, lpDIBBits, lmageWidth*lmageHeight);
		lpDst1 = (unsigned char*)lpImage1;
		lpDst2 = (unsigned char*)lpImage2;
		//Sobel����ˮƽ���ģ�����
		nTempWidth=3;
		nTempHeight=3;
		nTempCenX=1;
		nTempCenY=1;
		TempCoef=1;
		Tempdata=new double[9];//Sobel����ģ��Ϊ3X3
		//ˮƽ��ģ�����
		Tempdata[0]=-1;
		Tempdata[1]=-2;
		Tempdata[2]=-1;
		Tempdata[3]=0;
		Tempdata[4]=0;
		Tempdata[5]=0;
		Tempdata[6]=1;
		Tempdata[7]=2;
		Tempdata[8]=1;
		if (!Template((LPSTR)lpImage1, lmageWidth, lmageHeight,nTempWidth, nTempHeight, 
				nTempCenX, nTempCenY,Tempdata, TempCoef))
		{
			return FALSE;
		}
		//��ֱ����ģ�����
		Tempdata[0]=-1;
		Tempdata[1]=0;
		Tempdata[2]=1;
		Tempdata[3]=-2;
		Tempdata[4]=0;
		Tempdata[5]=2;
		Tempdata[6]=-1;
		Tempdata[7]=0;
		Tempdata[8]=1;
		if (!Template((LPSTR)lpImage2, lmageWidth, lmageHeight,nTempWidth, nTempHeight, 
				nTempCenX, nTempCenY,Tempdata, TempCoef))
		{
			return FALSE;
		}
		delete[] Tempdata;
		//����������ͼ������ֵ
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{

				// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
				lpDst1 = (unsigned char*)lpImage1 + lmageWidth * j + i;

				// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
				lpDst2 = (unsigned char*)lpImage2 + lmageWidth * j + i;
			
				if(*lpDst2 > *lpDst1)
				{
					*lpDst1 = *lpDst2;
				}
		
			}
		}
		//���ƾ���ģ��������ͼ��Դͼ��
		memcpy(lpDIBBits, lpImage1,lmageWidth*lmageHeight);
		return TRUE;
	}
	if(mode==1)		//LOG����
	{
		nTempWidth=5;
		nTempHeight=5;
		nTempCenX=2;
		nTempCenY=2;
		TempCoef=1;
		Tempdata=new double[25];
		Tempdata[0]=-2;
		Tempdata[1]=-4;
		Tempdata[2]=-4;
		Tempdata[3]=-4;
		Tempdata[4]=-2;
		Tempdata[5]=-4;
		Tempdata[6]=0;
		Tempdata[7]=8;
		Tempdata[8]=0;
		Tempdata[9]=-4;
		Tempdata[10]=-4;
		Tempdata[11]=8;
		Tempdata[12]=24;
		Tempdata[13]=8;
		Tempdata[14]=-4;
		Tempdata[15]=-4;
		Tempdata[16]=0;
		Tempdata[17]=8;
		Tempdata[18]=0;
		Tempdata[19]=-4;
		Tempdata[20]=-2;
		Tempdata[21]=-4;
		Tempdata[22]=-4;
		Tempdata[23]=-4;
		Tempdata[24]=-2;
		if (!Template(lpDIBBits, lmageWidth, lmageHeight,nTempWidth, nTempHeight, 
				nTempCenX, nTempCenY,Tempdata, TempCoef))
		{
			return FALSE;
		}
		delete[] Tempdata;
		return TRUE;
	}
		return TRUE;
}

/*************************************************************************
 * �������ƣ�
 *   HoughTrans()
 * ����:
 *   LPSTR lpDIBBits       - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶԼ��ͼ���е��������ֱ�ߡ�
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/
BOOL  HoughTrans(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;		
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ��任���ָ��
	unsigned char*  lpTrans;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	//ָ��任���ָ��
	LPBYTE lptransImage;
	//�任��ĳߴ�
	int mMaxDist;//����
	int mMaxAngleNumber;//�Ƕ�
	//�任�������
	int mDist;
	int mAngleNumber;
	//ѭ������
	int i;
	int j;
	//����ֵ
	unsigned char pixel;
	//��ʱ���ر���
	unsigned char pixeltemp;

	//�洢�任���е����ֵ
	MaxValue MaxValue1;
	MaxValue MaxValue2;

	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth*lmageHeight);
	//����任��ĳߴ�
	//������
	mMaxDist = (int) sqrt(lmageWidth*lmageWidth + lmageHeight*lmageHeight);
	//�Ƕȴ�0��180��ÿ��2��
	mMaxAngleNumber = 90;
	//Ϊ�任������ڴ�
	lptransImage = (LPBYTE) new  int[lmageWidth*lmageHeight];
	if (lptransImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpTrans = (unsigned char *)lptransImage;
	memset(lpTrans, 0, lmageWidth*lmageHeight);

	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}

			pixel = (unsigned char)*lpSrc;
				//����Ǻڵ㣬���ڱ任��Ķ�Ӧ�����ϼ�1
			if(pixel == 0)
			{
				//ע�ⲽ����2��
				for(mAngleNumber=0; mAngleNumber<mMaxAngleNumber; mAngleNumber++)
				{
					mDist = (int) fabs(i*cos(mAngleNumber*2*PI/180.0) + j*sin(mAngleNumber*2*PI/180.0));
				
					//�任��Ķ�Ӧ���ϼ�1
					*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber) = *(lptransImage+mDist*mMaxAngleNumber+mAngleNumber) +1;
				}
			}

		}
	}
	//�ҵ��任���е����ֵ��
	MaxValue1.Value=0;
	MaxValue2.Value=0;

	//�ҵ���һ�����ֵ��
	for (mDist=0; mDist<mMaxDist;mDist++)
	{
		for(mAngleNumber=0; mAngleNumber<mMaxAngleNumber; mAngleNumber++)
		{
			if((int)*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber)>=MaxValue1.Value)
			{
				MaxValue1.Value = (int)*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber);
				MaxValue1.Dist = mDist;
				MaxValue1.AngleNumber = mAngleNumber;
			}

		}
	}

	//����һ�����ֵ�㸽������
	for (mDist = -9;mDist < 10;mDist++)
	{
		for(mAngleNumber=-1; mAngleNumber<2; mAngleNumber++)
		{
			if(mDist+MaxValue1.Dist>=0 && mDist+MaxValue1.Dist<mMaxDist \
				&& mAngleNumber+MaxValue1.AngleNumber>=0 && mAngleNumber+MaxValue1.AngleNumber<=mMaxAngleNumber)
			{
				*(lptransImage+(mDist+MaxValue1.Dist)*mMaxAngleNumber+\
					(mAngleNumber+MaxValue1.AngleNumber))=0;
			}
		}
	}

	//�ҵ��ڶ������ֵ��
	for (mDist=0; mDist<mMaxDist;mDist++)
	{
		for(mAngleNumber=0; mAngleNumber<mMaxAngleNumber; mAngleNumber++)
		{
			if((int)*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber)>=MaxValue2.Value)
			{
				MaxValue2.Value = (int)*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber);
				MaxValue2.Dist = mDist;
				MaxValue2.AngleNumber = mAngleNumber;
			}

		}
	}

	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{	
			lpSrc=(unsigned char *)lpDIBBits + lmageWidth * j + i;
			// ָ�򻺴�ͼ������j�У���i�����ص�ָ��			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;	
			//����õ���ĳһ��ֱ���ϣ����ڻ���ͼ���Ͻ��õ㸳Ϊ��		
			//�ڵ�һ��ֱ����
			mDist = (int) fabs(i*cos(MaxValue1.AngleNumber*2*PI/180.0) + j*sin(MaxValue1.AngleNumber*2*PI/180.0));
			if ((mDist == MaxValue1.Dist)&&(*lpSrc==(unsigned char)0))
			{
				*lpDst = (unsigned char)0;
			}

			//�ڵڶ���ֱ����
			mDist = (int) fabs(i*cos(MaxValue2.AngleNumber*2*PI/180.0) + j*sin(MaxValue2.AngleNumber*2*PI/180.0));
			if ((mDist == MaxValue2.Dist)&&(*lpSrc==(unsigned char)0))
			{
			*lpDst = (unsigned char)0;
			}
		}
	}
	// ���ƻ���任���ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	delete[] lpImage;
	delete[] lptransImage;
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   Erosion()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth   - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight  - Դͼ��߶ȣ���������
 *   int   type			- ��ʴ��ʽ��0��ʾˮƽ����1��ʾ��ֱ����
 *	 int   num			- �ṹԪ�صĸ�����ˮƽ����ʹ�ֱ���򣩡�
 *
 * ����ֵ:
 *   BOOL               - ��ʴ�ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����и�ʴ���㡣�ṹԪ��Ϊˮƽ�����ֱ���򣬸������û�ѡ��
 * Ϊ3��5��7���ṹԭ��λ�������ġ�
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ����������㣬��ǿ��ת����
 ************************************************************************/

BOOL  Erosion(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int type , int num)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	// ѭ������
	int			i;
	int			j;
	int			k;		
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	//����ֵ
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}
		}
	}


	if(type == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = (num-1)/2;i <lmageWidth-(num-1)/2; i++)
			{
				//����ʹ��1��num�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ�(num-1)/2������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;
				
				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������(num-1)/2���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (k = 0;k < num;k++ )
				{
					//��ȡ���ػҶ�ֵ
					pixeltemp = *(lpSrc+k-(num-1)/2);
					//����һ���׵�
					if (pixeltemp == 255 )
					{
						//�õ�����Ϊ�׵�
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	else if(type == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ��и�ʴ
		for(j = (num-1)/2; j <lmageHeight-(num-1)/2; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{
				//����ʹ��1��num�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ�(num-1)/2������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������(num-1)/2���㲻�Ǻ�ɫ����
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (k = 0;k < num;k++ )
				{	
					//��ȡ���ػҶ�ֵ
					pixeltemp = *(lpSrc+(k-(num-1)/2)*lmageWidth);
					//����һ���׵�
					if (pixeltemp == 255 )
					{
						//�õ�����Ϊ�׵�
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);

	// �ͷ��ڴ�
	delete[] lpImage;

	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   Dilation()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth   - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight  - Դͼ��߶ȣ���������
 *   int   type			- ���ͷ�ʽ��0��ʾˮƽ����1��ʾ��ֱ����
 *	 int   num			- �ṹԪ�صĸ�����ˮƽ����ʹ�ֱ���򣩡�
 *
 * ����ֵ:
 *   BOOL               - ���ͳɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ������������㡣�ṹԪ��Ϊˮƽ�����ֱ���򣬸������û�ѡ��
 * Ϊ3��5��7���ṹԭ��λ�������ġ�
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ����������㣬��ǿ��ת����
 ************************************************************************/
BOOL  Dilation(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int type , int num)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	// ѭ������
	int			i;
	int			j;
	int			k;		
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	//����ֵ
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}
		}
	}


	if(type == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ�������
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = (num-1)/2;i <lmageWidth-(num-1)/2; i++)
			{
				//����ʹ��1��num�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ�(num-1)/2������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;
				
				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//���Դͼ���е�ǰ������������Ҹ�(num-1)/2ֻҪ�и����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				for (k = 0;k < num;k++ )
				{
					//��ȡ���ػҶ�ֵ
					pixeltemp = *(lpSrc+k-(num-1)/2);
					//����һ���ڵ�
					if (pixeltemp == 0 )
					{
						//�õ�����Ϊ�ڵ�
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	else if(type == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ�������
		for(j = (num-1)/2; j <lmageHeight-(num-1)/2; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{
				//����ʹ��1��num�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ�(num-1)/2������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//���Դͼ���е�ǰ������������¸�(num-1)/2ֻҪ�и����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (k = 0;k < num;k++ )
				{	
					//��ȡ���ػҶ�ֵ
					pixeltemp = *(lpSrc+(k-(num-1)/2)*lmageWidth);
					//����һ���׵�
					if (pixeltemp == 0 )
					{
						//�õ�����Ϊ�׵�
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	// �������ͺ��ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);

	// �ͷ��ڴ�
	delete[] lpImage;

	// ����
	return TRUE;
}

#endif // !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)