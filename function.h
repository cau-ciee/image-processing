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
// 常数π
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
 * \函数名称：
 *   GrayLinTrans()
 * \输入参数:
 *	 LPSTR lpDIBBits		//指向源图像的像素指针
 *	 LONG lmageWidth		//源图像的宽度
 *	 LONG lmageHeight		// 源图像的高度
 *   int   oralow			// 原始图像的灰度值集中区域－低值
 *   int   orahig			// 原始图像的灰度值集中区域－高值
 *   int   newlow			// 变换后图像灰度的动态范围－低值
 *   int   newhig			// 变换后图像灰度的动态范围－高值
 * \返回值:
 *   BOOL               // 成功返回TRUE，否则返回FALSE。
 * \说明:
 *   该函数用来对图像指定的灰度分布进行灰度变换主要用来实现灰度分布的扩展
*************************************************************************/
BOOL GrayLinTrans(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,int oralow, int orahig, int newlow, int newhig)
{
	unsigned char*	lpSrc;								// 指向源图像的指针
	int i;												// 循环变量
	int j;												// 循环变量
	BYTE	byMap[256];								// 定义灰度映射表
	for (i = 0; i <= oralow; i++)								//当灰度级小于要增强的灰度级时
	{
		if (newlow > 0)									//判断新灰度级是否大于0
		{
			byMap[i] = newlow;							//赋予新值
		}
		else
		{
			byMap[i] = 0;								//直接赋值为0
		}
	}
	for (; i <= orahig; i++)
	{
		if (orahig != oralow)								// 判断orahig是否等于oralow(防止
											 //分母为0)
		{
			//线性变换
			byMap[i] = newlow + (BYTE) ((newhig - newlow) * (i - oralow) / (orahig - oralow));
		}
		else
		{
			byMap[i] = newlow;							//直接赋值为newlow
		}
	}
	for (; i < newhig; i++)
	{
		if (newhig <= 255)								//判断d是否大于255
		{
			byMap[i] = newhig;							//直接赋值为newhig
		}
		else
		{
			byMap[i] = 255;								//直接赋值为255
		}
	}
	for(i = 0; i < lmageHeight; i++)							//对图像的每个像素值进行变换
	{
		for(j = 0; j < lmageWidth; j++)						//每列
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpSrc = byMap[*lpSrc];						//用新的灰度替代原有的灰度
		}
	}
	return TRUE;										//返回
}

/*************************************************************************
* \函数名称：
 *   GrayHistEnhance()
* \输入参数:
 *	 LPSTR lpDIBBits		//指向源图像的像素指针
 *	 LONG lmageWidth		//源图像的宽度
 *	 LONG lmageHeight		//源图像的高度
 * \返回值:
 *   BOOL		       	//成功则返回TRUE，否则返回FALSE
 * \说明:
 *   该函数对指定的图像进行直方图均衡化处理
*************************************************************************/
 BOOL GrayHistEnhance(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
 {
	unsigned char*	lpSrc;									//指向源图像的指针
	int	nTemp;											//临时变量
	int j;													//循环变量
	int i;													//循环变量
	BYTE	byMap[256];									//累积直方图，即灰度映射表
	int	nCount[256];										//直方图
	for (i = 0; i < 256; i ++)									//重置计数为0
	{
		nCount[i] = 0;										//清零
	}
	for(i = 0; i < lmageHeight; i++)								//每行
	{
		for(j = 0; j < lmageWidth; j++)							//每列
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			nCount[*(lpSrc)]++;								//计数加1
		}
	}
	for (i = 0; i < 256; i++)										//计算累积直方图
	{
		nTemp = 0;										//初始为0
		for (j = 0; j <= i ; j++)
		{
			nTemp += nCount[j];
		}
		byMap[i] = (BYTE) (nTemp * 255 / lmageHeight / lmageWidth); 	//计算对应的新灰度值
//说明：* 255实际上就是将新的灰度值也转换为0～255的范围。
	}
	for(i = 0; i < lmageHeight; i++)
	{
		for(j = 0; j < lmageWidth; j++)							//每列
		{
			//指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpSrc = byMap[*lpSrc];							//计算新的灰度值
		}
	}
	return TRUE;											//返回
}

/*************************************************************************
* 函数名称：
 *   MedianValue()
* 参数:
 *   unsigned char * FiltValue	- 指向要获取中值的数组指针
 *   int   iFilterLen				- 数组长度
* 返回值:
 *   unsigned char				- 返回指定数组的中值。
* 说明:
 *   该函数用冒泡法对一维数组进行排序，并返回数组元素的中值。
************************************************************************/

unsigned char MedianValue(unsigned char * FiltValue, int mFilterLen)
{
	int		i;										// 循环变量
	int		j;										// 循环变量
	unsigned char Temp;									// 中间变量
	// 用冒泡法对数组进行排序
	for (j = 0; j < mFilterLen - 1; j ++)
	{
		for (i = 0; i < mFilterLen - j - 1; i ++)
		{
			if (FiltValue[i] > FiltValue[i + 1])					// 前面的值大于后面的
			{
				Temp = FiltValue[i];
				FiltValue[i] = FiltValue[i + 1];				// 二者的值互换
				FiltValue[i + 1] = Temp;
			}
		}
	}
	if ((mFilterLen & 1) > 0)								// 计算中值
	{
		//数组有奇数个元素，返回中间一个元素
		Temp = FiltValue[(mFilterLen + 1) / 2];
	}
	else
	{
		//数组有偶数个元素，返回中间两个元素平均值
		Temp = (FiltValue[mFilterLen / 2] + FiltValue[mFilterLen / 2 + 1]) / 2;
	}
	return Temp;										// 返回中值
}

/*************************************************************************
* 函数名称：
 *   MedianFilter()
* 参数:
 *   LPSTR lpDIBBits			- 指向源DIB图像指针
 *   LONG  lmageWidth		- 源图像宽度（象素数）
 *   LONG  lmageHeight		- 源图像高度（象素数）
 *   int   mFilterH				- 滤波器的高度
 *   int   mFilterW			- 滤波器的宽度
 *   int   mFilterMX			- 滤波器的中心元素X坐标
 *   int   mFilterMY			- 滤波器的中心元素Y坐标
* 返回值:
 *   BOOL					- 成功返回TRUE，否则返回FALSE。
 * 说明:
 *   该函数对DIB图像进行中值滤波。
************************************************************************/
BOOL MedianFilter(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,
				  int mFilterH, int mFilterW, int mFilterMX, int mFilterMY)
{
	unsigned char* lpSrc;                  //指向原图像的指针
	unsigned char* lpDst;                  //指向要复制区域的指针
	LPBYTE lpImage;                        //指向复制图像的指针
	unsigned char* FiltValue;              //指向滤波器数组的指针
	int i;                                 //循环变量
	int j;                                 //循环变量
	int k;                                 
	int l;
    lpImage = (LPBYTE) new char[lmageWidth *lmageHeight];
	if(lpImage == NULL)
	{
		return FALSE;
	}
	memcpy(lpImage, lpDIBBits, lmageWidth *lmageHeight);
	FiltValue = new unsigned char[mFilterH *mFilterW];			// 暂时分配内存，以保存滤波器数组
	if (FiltValue == NULL)								// 判断是否内存分配失败
	{
		delete[]lpImage;									// 释放已分配内存
		return FALSE;									// 分配内存失败
	}
	// 开始中值滤波
	for(i = mFilterMY; i < lmageHeight - mFilterH + mFilterMY + 1; i++)
	{
		for(j = mFilterMX; j < lmageWidth - mFilterW + mFilterMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			for (k = 0; k < mFilterH; k++)					// 读取滤波器数组
			{
				for (l = 0; l < mFilterW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lmageWidth  * (lmageHeight - 1 - i + mFilterMY 
						  - k) + j - mFilterMX + l;
					FiltValue[k * mFilterW + l] = *lpSrc;		// 保存象素值
				}
			}
			*lpDst= MedianValue(FiltValue, (mFilterH * mFilterW)); // 获取中值
		}
	}
	memcpy(lpDIBBits, lpImage, lmageWidth*lmageHeight);			// 复制变换后的图像
	delete[]lpImage;										// 释放内存
	delete[]FiltValue;
	return TRUE;										// 返回
}

/*************************************************************************
 *
 * \函数名称：
 *   FFT_1D()
 *
 * \输入参数:
 *   complex<double> * pCTData	- 指向时域数据的指针，输入的需要变换的数据
 *   complex<double> * pCFData	- 指向频域数据的指针，输出的经过变换的数据
 *   nLevel						－傅立叶变换蝶形算法的级数，2的幂数，
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   一维快速傅立叶变换。
 *
 *************************************************************************
 */
void FFT_1D(complex<double> * pCTData, complex<double> * pCFData, int nLevel)
{
		// 循环控制变量
	int		i;
	int     j;
	int     k;

	// 傅立叶变换点数
	int	nCount =0 ;

	// 计算傅立叶变换点数
	nCount =(int)pow(2,nLevel) ;
	
	// 某一级的长度
	int		nBtFlyLen;
	nBtFlyLen = 0 ;
	
	// 变换系数的角度 ＝2 * PI * i / nCount
	double	dAngle;
	
	complex<double> *pCW ;
	
	// 分配内存，存储傅立叶变化需要的系数表
	pCW  = new complex<double>[nCount / 2];

    // 计算傅立叶变换的系数
	for(i = 0; i < nCount / 2; i++)
	{
		dAngle = -2 * PI * i / nCount;
		pCW[i] = complex<double> ( cos(dAngle), sin(dAngle) );
	}

	// 变换需要的工作空间
	complex<double> *pCWork1,*pCWork2; 
	
	// 分配工作空间
	pCWork1 = new complex<double>[nCount];

	pCWork2 = new complex<double>[nCount];

	
	// 临时变量
	complex<double> *pCTmp;
	
	// 初始化，写入数据
	memcpy(pCWork1, pCTData, sizeof(complex<double>) * nCount);

	// 临时变量
	int nInter; 
	nInter = 0;

	// 蝶形算法进行快速傅立叶变换
	for(k = 0; k < nLevel; k++)
	{
		for(j = 0; j < (int)pow(2,k); j++)
		{
			//计算长度
			nBtFlyLen = (int)pow( 2,(nLevel-k) );
			
			//倒序重排，加权计算
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

		// 交换 pCWork1和pCWork2的数据
		pCTmp   = pCWork1	;
		pCWork1 = pCWork2	;
		pCWork2 = pCTmp		;
	}
	
	// 重新排序
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
	
	// 释放内存空间
	delete pCW;
	delete pCWork1;
	delete pCWork2;
	pCW		=	NULL	;
	pCWork1 =	NULL	;
	pCWork2 =	NULL	;

}

/*************************************************************************
 *
 * \函数名称：
 *   FFT_2D()
 *
 * \输入参数:
 *   complex<double> * pCTData	- 图像数据
 *   int    nWidth				- 数据宽度
 *   int    nHeight				- 数据高度
 *   complex<double> * pCFData	- 傅立叶变换后的结果
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   二维傅立叶变换。
 *
 ************************************************************************
 */
void FFT_2D(complex<double> * pCTData, int nWidth, int nHeight, complex<double> * pCFData)
{
	
	// 循环控制变量
	int	x;
	int	y;
	
	// 临时变量
	double	dTmpOne;
	double  dTmpTwo;
	
	// 进行傅立叶变换的宽度和高度，（2的整数次幂）
	// 图像的宽度和高度不一定为2的整数次幂
	int		nTransWidth;
	int 	nTransHeight;

	// 计算进行傅立叶变换的宽度	（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;
	
	// 计算进行傅立叶变换的高度 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;	
	
	// x，y（行列）方向上的迭代次数
	int		nXLev;
	int		nYLev;

	// 计算x，y（行列）方向上的迭代次数
	nXLev = (int) ( log(nTransWidth)/log(2) +  0.5 );
	nYLev = (int) ( log(nTransHeight)/log(2) + 0.5 );
	
	for(y = 0; y < nTransHeight; y++)
	{
		// x方向进行快速傅立叶变换
		FFT_1D(&pCTData[nTransWidth * y], &pCFData[nTransWidth * y], nXLev);
	}
	
	// pCFData中目前存储了pCTData经过行变换的结果
	// 为了直接利用FFT_1D，需要把pCFData的二维数据转置，再一次利用FFT_1D进行
	// 傅立叶行变换（实际上相当于对列进行傅立叶变换）
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTData[nTransHeight * x + y] = pCFData[nTransWidth * y + x];
		}
	}
	
	for(x = 0; x < nTransWidth; x++)
	{
		// 对x方向进行快速傅立叶变换，实际上相当于对原来的图象数据进行列方向的
		// 傅立叶变换
		FFT_1D(&pCTData[x * nTransHeight], &pCFData[x * nTransHeight], nYLev);
	}

	// pCFData中目前存储了pCTData经过二维傅立叶变换的结果，但是为了方便列方向
	// 的傅立叶变换，对其进行了转置，现在把结果转置回来
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
 * \函数名称：
 *   IFFT_2D()
 *
 * \输入参数:
 *   complex<double> * pCFData	- 频域数据
 *   complex<double> * pCTData	- 时域数据
 *   int    nWidth				- 图像数据宽度
 *   int    nHeight				- 图像数据高度
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   二维傅立叶反变换。
 *
 ************************************************************************
 */
void IFFT_2D(complex<double> * pCFData, complex<double> * pCTData, int nWidth, int nHeight)
{
	// 循环控制变量
	int	x;
	int	y;
	
	// 临时变量
	double	dTmpOne;
	double  dTmpTwo;
	
	// 进行傅立叶变换的宽度和高度，（2的整数次幂）
	// 图像的宽度和高度不一定为2的整数次幂
	int		nTransWidth;
	int 	nTransHeight;

	// 计算进行傅立叶变换的宽度	（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;
	
	// 计算进行傅立叶变换的高度 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;
	
	// 分配工作需要的内存空间
	complex<double> *pCWork= new complex<double>[nTransWidth * nTransHeight];

	//临时变量
	complex<double> *pCTmp ;
	
	// 为了利用傅立叶正变换,可以把傅立叶频域的数据取共轭
	// 然后直接利用正变换，输出结果就是傅立叶反变换结果的共轭
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTmp = &pCFData[nTransWidth * y + x] ;
			pCWork[nTransWidth * y + x] = complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// 调用傅立叶正变换
	FFT_2D(pCWork, nWidth, nHeight, pCTData) ;
	
	// 求时域点的共轭，求得最终结果
	// 根据傅立叶变换原理，利用这样的方法求得的结果和实际的时域数据
	// 相差一个系数
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
 * \函数名称：
 *   ButterWorthHighPass()
 * \输入参数:
 *	 LPSTR lpDIBBits					- 指向需要滤波的图像像素指针
 *   int nWidth							- 数据宽度
 *   int nHeight						- 数据高度
 *   int nRadius            - ButterWorth高通滤波的"半功率"点
* \返回值:
 *    BOOL								// 成功返回TRUE，否则返回FALSE。
* \说明:
 *  pDIBBits 是指向需要滤波的图像像素指针。
 *  经过ButterWorth高通滤波的数据仍然存储在lpDIBBits 当中。
 **************************************************************************/
BOOL ButterWorthHighPass(LPSTR lpDIBBits, LONG nWidth, LONG nHeight, int nRadius)
{
	unsigned char*	lpSrc;							// 指向源图像的指针
	int y ;										// 循环控制变量
	int x ;										// 循环控制变量
	double dTmpOne ;								//存放临时变量
	double dTmpTwo ;								//存放临时变量
	double H ;										// ButterWorth 滤波系数
	int nTransWidth ;								// 傅立叶变换的宽度（2的整数次幂）
	int nTransHeight;								// 傅立叶变换的高度（2的整数次幂）
	double dReal ;									// 傅立叶变换的实部
	double dImag;									// 傅立叶变换的虚部
	double unchValue;								// 存贮图像各像素灰度的临时变量
	complex<double> * pCTData ;						// 指向时域数据的指针
	complex<double> * pCFData ;						// 指向频域数据的指针
	// 计算进行傅立叶变换的点数－横向（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// 计算进行傅立叶变换的点数－纵向 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;	
	pCTData=new complex<double>[nTransWidth * nTransHeight];	// 分配内存
	pCFData=new complex<double>[nTransWidth * nTransHeight];	// 分配内存
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData有一部分数据需要补0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// 补零
		}
	}
	for(y=0; y<nHeight; y++)						// 把图像数据传给pCTData
	{
		for(x=0; x<nWidth; x++)
		{
		// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;		// 傅立叶正变换
	for(y=0; y<nTransHeight; y++)					// 下面开始实施ButterWorth高通滤波
	{
		for(x=0; x<nTransWidth; x++)
		{
			H = (double)(y*y+x*x) ; 
			H = (nRadius * nRadius) / H ; 
			H = 1/(1+H);						// 求H值
			pCFData[y*nTransWidth + x]=complex<double>(H*(pCFData[y*nTransWidth + x].real()),
					 H*(pCFData[y*nTransWidth + x].imag())  );
		}
	}
	// 经过ButterWorth高通滤波的图象进行反变换
	IFFT_2D(pCFData, pCTData, nWidth, nHeight);
	for(y=0; y<nHeight; y++)						// 反变换的数据传给lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue = max(0,min(255,sqrt(dReal*dReal+dImag*dImag)+100 ));
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}	
	delete pCTData;									// 释放内存
	delete pCFData;									// 释放内存
	pCTData = NULL;
	pCFData = NULL;
	return (true);									// 返回结果
}

/*************************************************************************
* \函数名称：
 *   ButterWorthLowPass()
* \输入参数:
 *	 LPSTR lpDIBBits					- 指向需要滤波的图像像素指针
 *   int nWidth						- 数据宽度
 *   int nHeight						- 数据高度
 *   int nRadius						- ButterWorth低通滤波的"半功率"点
* \返回值:
 *    BOOL								// 成功返回TRUE，否则返回FALSE。
* \说明:
 *  pDIBBits 是指向需要滤波的图像像素指针。
 *  经过ButterWorth低通滤波的数据仍然存储在lpDIBBits 当中。
 **************************************************************************/
BOOL ButterWorthLowPass(LPSTR lpDIBBits, LONG nWidth, LONG nHeight, int nRadius)
{
	unsigned char*	lpSrc;							// 指向源图像的指针
	int y ;										// 循环控制变量
	int x ;										// 循环控制变量
	double dTmpOne ;								//存放临时变量
	double dTmpTwo ;								//存放临时变量
	double H ;										// ButterWorth 滤波系数
	int nTransWidth ;								// 傅立叶变换的宽度（2的整数次幂）
	int nTransHeight;								// 傅立叶变换的高度（2的整数次幂）
	double dReal ;									// 傅立叶变换的实部
	double dImag;									// 傅立叶变换的虚部
	double unchValue;								// 存贮图像各像素灰度的临时变量
	complex<double> * pCTData ;						// 指向时域数据的指针
	complex<double> * pCFData ;						// 指向频域数据的指针
	// 计算进行傅立叶变换的点数－横向	（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// 计算进行傅立叶变换的点数－纵向 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;	
	pCTData=new complex<double>[nTransWidth * nTransHeight]; // 分配内存
	pCFData=new complex<double>[nTransWidth * nTransHeight]; // 分配内存
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData有一部分数据需要补0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// 补零
		}
	}
	for(y=0; y<nHeight; y++)							// 把图像数据传给pCTData
	{
		for(x=0; x<nWidth; x++)
		{
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}	
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;			// 傅立叶正变换
	for(y=0; y<nTransHeight; y++)						// 开始实施ButterWorth低通滤波
	{
		for(x=0; x<nTransWidth; x++)
		{
			H = (double)(y*y+x*x) ; 
			H = H / (nRadius * nRadius); 
			H = 1/(1+H)  ;							// 求H值
			pCFData[y*nTransWidth + x]=complex<double>(pCFData[y*nTransWidth + x].real()*H, 
			pCFData[y*nTransWidth + x].imag()*H);
		}
	}
	// 经过ButterWorth低通滤波的图象进行反变换
	IFFT_2D(pCFData, pCTData, nWidth, nHeight);
	for(y=0; y<nHeight; y++)							// 反变换的数据传给lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue = max(0,min(255,sqrt(dReal*dReal+dImag*dImag) ));
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}
	delete pCTData;									// 释放内存
	delete pCFData;									// 释放内存
	pCTData = NULL;
	pCFData = NULL;
	return (true);									//返回结果	
}

/*************************************************************************
 * \函数名称：
 *  Template()
 * \输入参数:
 *	 LPSTR lpDIBBits		- 指向源图像的像素指针
 *	 LONG lmageWidth		- 源图像的宽度
 *	 LONG lmageHeight		- 源图像的高度
 *   int nTempWidth		- 模板的宽度
 *   int nTempHeight		- 模板的高度
 *   int nTempCenX		- 模板中心的X坐标（相对于模板）
 *   int nTempCenY		- 模板中心的Y坐标（相对于模板）
 *   double* Tempdata		- 模板数组的指针
 *   double* TempCoef		- 模板的系数
 * \返回值:
 *   BOOL			- 成功则返回TRUE，否则返回FALSE
 * \说明:
 *   该函数用指定的模板对lpDIBBits指向的图象进行模板操作。模板的定义了宽度，高度，中心坐标
*和系数，模板的数据存放在Tempdata中。对图象进行模板操作后，仍然存放在lpDIBBits指向的对象
*中。需要注意的是，该函数只能处理8位的图象，否则，指向的数据将出错。
 **************************************************************************/
BOOL  Template(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,
					 int nTempWidth, int nTempHeight, 
					 int nTempCenX, int nTempCenY,
					 double* Tempdata, double TempCoef)
{
	LPBYTE			lpImage;								// 临时存放图像数据的指针
	int 		i;											// 循环变量
	int		j;											// 循环变量
	int 		k;											// 循环变量
	int 		l;											// 循环变量
	unsigned char*	lpSrc;									// 指向源图像的指针
	unsigned char*	lpDst;									// 指向要复制区域的指针
	double	dbResult;										// 计算结果
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];			// 分配内存
	if (lpImage == NULL)										// 判断是否内存分配失败
	{
		return FALSE;										// 分配内存失败
	}
	
	// 将原始图像的数据拷贝到临时存放内存中
	memcpy(lpImage, lpDIBBits, lmageWidth*lmageHeight);
	// 进行模板计算，行(除去边缘几行)
	for(i = nTempCenY ; i <lmageHeight - nTempHeight + nTempCenY + 1; i++)
	{
		// 列(除去边缘几列)
		for(j = nTempCenX; j < lmageWidth - nTempWidth + nTempCenX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			dbResult = 0;										// 置0
			for (k = 0; k < nTempHeight; k++)
			{
				for (l = 0; l < nTempWidth; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i + nTempCenY - k) + j - nTempCenX + l;
					dbResult += (* lpSrc) * Tempdata[k * nTempWidth + l];	// 保存象素值
				}
			}
			dbResult *= TempCoef;								// 乘上系数
			dbResult = (double ) fabs(dbResult);						// 取绝对值
			if(dbResult > 255)									// 判断是否超过255
			{
				* lpDst = 255;									// 直接赋值为255
			}
			else
			{
				* lpDst = (unsigned char) (dbResult + 0.5);				// 赋值
			}
		}
	}
	memcpy(lpDIBBits, lpImage, lmageWidth*lmageHeight);				//复制变换后的图像
	delete[] lpImage;												// 释放内存
	return TRUE;												// 返回
}

/*************************************************************************
 * 函数名称：
 *   RegionDivideThreshold()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int threshold		- 分割门限
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对图像进行固定阈值分割。
 ************************************************************************/
BOOL RegionDivideThreshold(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int threshold)
{
	int i;  //循环变量
	int j;	//循环变量
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	//像素值
	unsigned char pixeltemp;
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= threshold)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}
	return true;
}

/*************************************************************************
 * \函数名称：
 *   RegionDivideAdaptive()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对图像进行自适应阈值分割。把图像分成四个子图象，然后计算每个子图象的均值，
 *  根据均值设置阈值，阈值只是应用在对应的子图像
 **************************************************************************/
BOOL RegionDivideAdaptive(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	int i;  //循环变量
	int j;	//循环变量
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	//像素值
	unsigned char pixeltemp;	
	// 子图像灰度的平均值
	int nAvg ;
	nAvg = 0 ; //初始化为0
	// 对左下图像逐点扫描：
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//灰度的累计
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// 计算均值
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// 对左下图像逐点扫描：
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

	nAvg =0;   //初始化为0

	// 对左上图像逐点扫描：
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//灰度的累计
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// 计算均值
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// 对左上图像逐点扫描：
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

	nAvg =0;   //初始化为0

	// 对右上图像逐点扫描：
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//灰度的累计
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// 计算均值
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// 对右上图像逐点扫描：
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

		nAvg =0;   //初始化为0

	// 对右下图像逐点扫描：
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//灰度的累计
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// 计算均值
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// 对右下图像逐点扫描：
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}
	return true;
}

/*************************************************************************
 * \函数名称：
 *   RegionGrow()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 *	 int nThreshold			- 区域生长门限
 *	 int seedx				- 区域生长种子的横坐标
 *	 int seedy				- 区域生长种子的纵坐标
  *	 int mode				- 区域生长种子的选取类型
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * \说明:
 *   本函数的处理结果是将生长后的区域表示为黑色像素，未生长区域表示为白色像素。
 *   区域生长一般包含三个比较重要的问题：
 *		1. 种子点的选取
 *		2. 生长准则
 *		3. 终止条件
 *	 可以认为，这三个问题需要具体分析，而且每个问题解决的好坏直接关系到
 *	 区域生长的结果。
 *************************************************************************/
BOOL RegionGrow(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int nThreshold,int seedx,int seedy,int mode)
{	
	//设置用于处理四临域的数组
	static int Dx[]={-1,0,1,0};	//X向
	static int Dy[]={0,1,0,-1};	//y向
	// 临时存放图像数据的指针
	LPBYTE			lpImage;	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	unsigned char*	lpSrc1;
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 分配内存
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 将目标图像所有像素初始化为白点
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);
	// 种子点
	CPoint seed;
	if(mode==0) // 如果选择种子点为图像的中心
	{
		// 设置种子点为图像的中心
		seed.x=lmageWidth/2;
		seed.y=lmageHeight/2;
	}
	else //自己设置种子点
	{
		// 设置种子点为输入点
		seed.x=seedx;
		seed.y=seedy;
	}

	// 定义堆栈，分别存贮X Y坐标
	int * GrowX ;
	int * GrowY ;
	
	// 分配空间，最大为图像的像素数目
	GrowX = new int [ lmageWidth * lmageHeight];
	GrowY = new int [ lmageWidth * lmageHeight];

	
	// 定义堆栈的起点和终点
	// 当Start=End, 表示堆栈中只有一个点
	int Start ;
	int End   ;
	//初始化
	Start = 0 ;
	End   = 0 ;
	// 把种子点的坐标压入栈
	GrowX[End] = seed.x;
	GrowY[End] = seed.y;
	// 当前正在处理的象素
	CPoint Current;
	// 循环控制变量
	int k ;
	// 图象的横纵坐标,用来对当前象素的4邻域进行遍历
	int xx;
	int yy;
	while (Start<=End)
	{
		// 当前种子点的坐标
		Current.x = GrowX[Start];
		Current.y = GrowY[Start];
		// 对当前点的4邻域进行遍历
		for (k=0; k<4; k++)	
		{	
			// 4邻域象素的坐标
			xx = Current.x+Dx[k];
			yy = Current.y+Dy[k];
			
			// 判断象素(xx，yy) 是否在图像内部
			// 判断象素(xx，yy) 是否已经处理过
			// *lpDst==255 表示还没有处理
			// 指向源图像(xx，yy)象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * (lmageHeight-yy) + xx;
			lpSrc1 = (unsigned char *)lpDIBBits + lmageWidth * (lmageHeight-Current.y) + Current.x;
			// 指向目标图像第j行，第i个象素的指针			
			lpDst = (unsigned char *)lpImage + lmageWidth * (lmageHeight-yy) + xx;
			// 生长条件：判断象素(xx，yy)和当前象素(nCurrX,nCurrY) 象素值差的绝对值
			if ((xx < lmageWidth) && (xx>=0) && (yy<lmageHeight) && (yy>=0) && (*lpDst==255) 
					&& abs(*lpSrc-*lpSrc1)<nThreshold )
			{
				// 堆栈的尾部指针后移一位
				End++;
				// 象素(xx，yy) 压入栈
				GrowX[End] = xx;
				GrowY[End] = yy;
				// 目标图像为黑点，同时也表明该象素处理过
				*lpDst=0 ;
			}
		}
		Start++;
	}
	// 复制区域生长后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// 释放内存
	delete[] lpImage;
	delete[] GrowX;
	delete[] GrowY;
	// 返回
	return TRUE;
}

/*************************************************************************
 * 函数名称：
 *   EdgeDetection()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *	 int mode			- 算子类型
 * 返回值:
 *   BOOL               - 边缘检测成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用Sobel、LOG边缘检测算子对图像进行边缘检测运算。
 * 要求目标图像为灰度图像。
 ************************************************************************/
BOOL EdgeDetection(LPSTR lpDIBBits,LONG lmageWidth,LONG lmageHeight,int mode)
{
	int nTempWidth;		//模板的宽度
    int nTempHeight;	 // 模板的高度
    int nTempCenX;		//模板中心的X坐标（相对于模板）
    int nTempCenY;		//模板中心的Y坐标（相对于模板）
    double* Tempdata;	//模板数组的指针	
	double TempCoef;	//模板系数
	//循环变量
	int i;
	int j;
	if(mode==0)
	{
		//指向缓存图像的指针
		unsigned char* lpDst1;
		unsigned char* lpDst2;
		LPBYTE lpImage1;
		LPBYTE lpImage2;
		//暂时分配内存，以保存新图像
		lpImage1 = (LPBYTE) new char[lmageWidth*lmageHeight];
		lpImage2 = (LPBYTE) new char[lmageWidth*lmageHeight];
		//判断是否内存分配失败
		if (lpImage1 == NULL)
		{
			//分配内存失败
			return FALSE;
		}
		//判断是否内存分配失败
		if (lpImage2 == NULL)
		{
			// 分配内存失败
			return FALSE;
		}
		// 初始化图像为原始图像
		memcpy(lpImage1, lpDIBBits, lmageWidth*lmageHeight);
		memcpy(lpImage2, lpDIBBits, lmageWidth*lmageHeight);
		lpDst1 = (unsigned char*)lpImage1;
		lpDst2 = (unsigned char*)lpImage2;
		//Sobel算子水平检测模板参数
		nTempWidth=3;
		nTempHeight=3;
		nTempCenX=1;
		nTempCenY=1;
		TempCoef=1;
		Tempdata=new double[9];//Sobel算子模板为3X3
		//水平向模板参数
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
		//垂直方向模板参数
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
		//求两幅缓存图像的最大值
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{

				// 指向缓存图像1倒数第j行，第i个象素的指针			
				lpDst1 = (unsigned char*)lpImage1 + lmageWidth * j + i;

				// 指向缓存图像2倒数第j行，第i个象素的指针			
				lpDst2 = (unsigned char*)lpImage2 + lmageWidth * j + i;
			
				if(*lpDst2 > *lpDst1)
				{
					*lpDst1 = *lpDst2;
				}
		
			}
		}
		//复制经过模板运算后的图像到源图像
		memcpy(lpDIBBits, lpImage1,lmageWidth*lmageHeight);
		return TRUE;
	}
	if(mode==1)		//LOG算子
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
 * 函数名称：
 *   HoughTrans()
 * 参数:
 *   LPSTR lpDIBBits       - 指向源DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对检测图像中的两条最长的直线。
 * 要求目标图像为只有0和255两个灰度值的灰度图像。
 ************************************************************************/
BOOL  HoughTrans(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;		
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向变换域的指针
	unsigned char*  lpTrans;
	// 指向复制图像的指针
	LPBYTE lpImage;
	//指向变换域的指针
	LPBYTE lptransImage;
	//变换域的尺寸
	int mMaxDist;//长度
	int mMaxAngleNumber;//角度
	//变换域的坐标
	int mDist;
	int mAngleNumber;
	//循环变量
	int i;
	int j;
	//像素值
	unsigned char pixel;
	//临时像素变量
	unsigned char pixeltemp;

	//存储变换域中的最大值
	MaxValue MaxValue1;
	MaxValue MaxValue2;

	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	
	// 初始化新分配的内存，设定初始值为255
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth*lmageHeight);
	//计算变换域的尺寸
	//最大距离
	mMaxDist = (int) sqrt(lmageWidth*lmageWidth + lmageHeight*lmageHeight);
	//角度从0－180，每格2度
	mMaxAngleNumber = 90;
	//为变换域分配内存
	lptransImage = (LPBYTE) new  int[lmageWidth*lmageHeight];
	if (lptransImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 初始化新分配的内存，设定初始值为255
	lpTrans = (unsigned char *)lptransImage;
	memset(lpTrans, 0, lmageWidth*lmageHeight);

	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}

			pixel = (unsigned char)*lpSrc;
				//如果是黑点，则在变换域的对应各点上加1
			if(pixel == 0)
			{
				//注意步长是2度
				for(mAngleNumber=0; mAngleNumber<mMaxAngleNumber; mAngleNumber++)
				{
					mDist = (int) fabs(i*cos(mAngleNumber*2*PI/180.0) + j*sin(mAngleNumber*2*PI/180.0));
				
					//变换域的对应点上加1
					*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber) = *(lptransImage+mDist*mMaxAngleNumber+mAngleNumber) +1;
				}
			}

		}
	}
	//找到变换域中的最大值点
	MaxValue1.Value=0;
	MaxValue2.Value=0;

	//找到第一个最大值点
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

	//将第一个最大值点附近清零
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

	//找到第二个最大值点
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
			// 指向缓存图像倒数第j行，第i个象素的指针			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;	
			//如果该点在某一条直线上，则在缓存图像上将该点赋为黑		
			//在第一条直线上
			mDist = (int) fabs(i*cos(MaxValue1.AngleNumber*2*PI/180.0) + j*sin(MaxValue1.AngleNumber*2*PI/180.0));
			if ((mDist == MaxValue1.Dist)&&(*lpSrc==(unsigned char)0))
			{
				*lpDst = (unsigned char)0;
			}

			//在第二条直线上
			mDist = (int) fabs(i*cos(MaxValue2.AngleNumber*2*PI/180.0) + j*sin(MaxValue2.AngleNumber*2*PI/180.0));
			if ((mDist == MaxValue2.Dist)&&(*lpSrc==(unsigned char)0))
			{
			*lpDst = (unsigned char)0;
			}
		}
	}
	// 复制霍夫变换后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	delete[] lpImage;
	delete[] lptransImage;
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   Erosion()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth   - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight  - 源图像高度（象素数）
 *   int   type			- 腐蚀方式，0表示水平方向，1表示垂直方向。
 *	 int   num			- 结构元素的个数（水平方向和垂直方向）。
 *
 * 返回值:
 *   BOOL               - 腐蚀成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行腐蚀运算。结构元素为水平方向或垂直方向，个数由用户选择
 * 为3，5或7，结构原点位于其中心。
 * 要求目标图像为只有0和255两个灰度值的灰度图像，如果不满足，则强行转换。
 ************************************************************************/

BOOL  Erosion(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int type , int num)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向复制图像的指针
	LPBYTE lpImage;
	// 循环变量
	int			i;
	int			j;
	int			k;		
	// 暂时分配内存，以保存新图像
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	//像素值
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
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
		//使用水平方向的结构元素进行腐蚀
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = (num-1)/2;i <lmageWidth-(num-1)/2; i++)
			{
				//由于使用1×num的结构元素，为防止越界，所以不处理最左边和最右边的(num-1)/2列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;
				
				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者左右有(num-1)/2个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (k = 0;k < num;k++ )
				{
					//读取像素灰度值
					pixeltemp = *(lpSrc+k-(num-1)/2);
					//发现一个白点
					if (pixeltemp == 255 )
					{
						//该点设置为白点
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	else if(type == 1)
	{
		//使用垂直方向的结构元素进行腐蚀
		for(j = (num-1)/2; j <lmageHeight-(num-1)/2; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{
				//由于使用1×num的结构元素，为防止越界，所以不处理最上边和最下边的(num-1)/2列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者上下有(num-1)/2个点不是黑色，，
				//则将目标图像中的当前点赋成白色
				for (k = 0;k < num;k++ )
				{	
					//读取像素灰度值
					pixeltemp = *(lpSrc+(k-(num-1)/2)*lmageWidth);
					//发现一个白点
					if (pixeltemp == 255 )
					{
						//该点设置为白点
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);

	// 释放内存
	delete[] lpImage;

	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   Dilation()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth   - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight  - 源图像高度（象素数）
 *   int   type			- 膨胀方式，0表示水平方向，1表示垂直方向。
 *	 int   num			- 结构元素的个数（水平方向和垂直方向）。
 *
 * 返回值:
 *   BOOL               - 膨胀成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行膨胀运算。结构元素为水平方向或垂直方向，个数由用户选择
 * 为3，5或7，结构原点位于其中心。
 * 要求目标图像为只有0和255两个灰度值的灰度图像，如果不满足，则强行转换。
 ************************************************************************/
BOOL  Dilation(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int type , int num)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向复制图像的指针
	LPBYTE lpImage;
	// 循环变量
	int			i;
	int			j;
	int			k;		
	// 暂时分配内存，以保存新图像
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	//像素值
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
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
		//使用水平方向的结构元素进行膨胀
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = (num-1)/2;i <lmageWidth-(num-1)/2; i++)
			{
				//由于使用1×num的结构元素，为防止越界，所以不处理最左边和最右边的(num-1)/2列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;
				
				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//如果源图像中当前点自身或者左右各(num-1)/2只要有个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (k = 0;k < num;k++ )
				{
					//读取像素灰度值
					pixeltemp = *(lpSrc+k-(num-1)/2);
					//发现一个黑点
					if (pixeltemp == 0 )
					{
						//该点设置为黑点
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	else if(type == 1)
	{
		//使用垂直方向的结构元素进行膨胀
		for(j = (num-1)/2; j <lmageHeight-(num-1)/2; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{
				//由于使用1×num的结构元素，为防止越界，所以不处理最上边和最下边的(num-1)/2列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//如果源图像中当前点自身或者上下各(num-1)/2只要有个点是黑色，
				//则将目标图像中的当前点赋成白色
				for (k = 0;k < num;k++ )
				{	
					//读取像素灰度值
					pixeltemp = *(lpSrc+(k-(num-1)/2)*lmageWidth);
					//发现一个白点
					if (pixeltemp == 0 )
					{
						//该点设置为白点
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	// 复制膨胀后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);

	// 释放内存
	delete[] lpImage;

	// 返回
	return TRUE;
}

#endif // !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)