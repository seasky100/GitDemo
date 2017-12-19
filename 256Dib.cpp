//--------- 256Dib.cpp --t----------------------------------

#include "stdafx.h"
#include "256Dib.h"
#include <math.h>


C256Dib::C256Dib()
{
//----------------------------------------------
	m_nMemAlloc = 0;
	m_blLoaded = FALSE;
	m_hGlobal = NULL;
	m_pbPixels = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nAmountOfPixels = 0;
	m_cDirection = 1;
	m_nRowLength = 0;
	m_dwSizeImage = 0;

	m_ptImageCenter.x = 0;
	m_ptImageCenter.y = 0;



	// ----------------------------------------------------------------
    UINT32 bitmapInfoSize = 0 ;
	int i;

	bitmapInfoSize = sizeof(BITMAPINFOHEADER) + 256*sizeof(RGBQUAD);
	m_pBitmapInfoY8 = (BITMAPINFO *) new BYTE[bitmapInfoSize];

	m_pBitmapInfoY8->bmiHeader.biSize=40;
	m_pBitmapInfoY8->bmiHeader.biPlanes = 1;
	m_pBitmapInfoY8->bmiHeader.biBitCount = 8;
	m_pBitmapInfoY8->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfoY8->bmiHeader.biSizeImage = 0 ;
	m_pBitmapInfoY8->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfoY8->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfoY8->bmiHeader.biClrUsed = 0;
	m_pBitmapInfoY8->bmiHeader.biClrImportant = 0;
	m_pBitmapInfoY8->bmiHeader.biWidth = 0 ;
	m_pBitmapInfoY8->bmiHeader.biHeight = 0 ;
	for(i=0; i<256; i++)
	{
		m_pBitmapInfoY8->bmiColors[i].rgbBlue  = i;
		m_pBitmapInfoY8->bmiColors[i].rgbGreen = i;
		m_pBitmapInfoY8->bmiColors[i].rgbRed   = i;
	}

//------------------------------------------------------------------
}

C256Dib::~C256Dib()
{
	if( m_blLoaded )
	{
		if( m_nMemAlloc == 1 )
		{
			::GlobalUnlock( m_hGlobal );
			::GlobalFree( m_hGlobal );
		}
	}
	if (m_pBitmapInfoY8) 
		delete m_pBitmapInfoY8 ;
}

VOID C256Dib::DrawBmp(CDC *pDC, int x, int y, int n)const
{
	CString str;

	if( m_blLoaded )	//如果已经载入图片，则画出
	{
/*
		::StretchDIBits(	pDC->GetSafeHdc(),
							x, y,
							m_nWidth,
							m_nHeight,
							0,0,
							m_nWidth,
							m_nHeight,
							m_pbPixes,
							m_lpbmif,
							DIB_RGB_COLORS,
							SRCCOPY);
*/
		::SetDIBitsToDevice (	pDC->GetSafeHdc(),	//1
								x,					//2
								y,					//3
								m_nWidth,	//4
								m_nHeight,	//5
								0,				//6
								0,				//7
								0,				//8
								m_nHeight, //9
								m_pbPixels, //10
								m_pBitmapInfoY8,	//11
								DIB_RGB_COLORS);	//12
		if( n >= 1 )
		{
//			str.Format("W=%d,H=%d,标准差=%d     ",m_nWidth, m_nHeight, m_nVariance );
			str.Format("W=%d,H=%d     ",m_nWidth, m_nHeight );
			pDC->TextOut(x,y+m_nHeight, str);
		}
		if( n > 5 )
		{
			str.Format( "bfType = %x, bfSize = %d, bfOffBits = %d", 
				m_bmfHeader.bfType, m_bmfHeader.bfSize, m_bmfHeader.bfOffBits );
			pDC->TextOut( x, y+m_nHeight+20, str);

		}
	}
}

BOOL C256Dib::IsLoadedBmp()		//是否已经载入了图片，如果是则返回TRUE
{
	return m_blLoaded;
}


//最终都是调用该函数创建8位位图的
int C256Dib::Create8BitGrayMap( SIZE size, char cDirect )
{
	int i,j;
	unsigned char cClr;

	if( (cDirect != 1) && ( cDirect != -1) )
	{
		return 0;
	}

	int nWidth	= abs( size.cx );
	int nHeight = abs( size.cy );	

	if( m_blLoaded )	//if DIB exist
	{
		if( (nWidth==m_nWidth) && (nHeight==m_nHeight) )	//if the size will be created equal to the size before
		{
			if( m_cDirection != cDirect )
			{
				if( cDirect == 1 )
					m_pBitmapInfoY8->bmiHeader.biHeight = nHeight;
				else
					m_pBitmapInfoY8->bmiHeader.biHeight = -nHeight;

				m_cDirection = cDirect;
			}
			return 1;
		}
	}

	m_cDirection = cDirect;
	m_nRowLength = 4 * ((nWidth*8+31)/32);
	m_dwSizeImage = m_nRowLength * nHeight;

	m_hGlobal = ::GlobalAlloc( GMEM_MOVEABLE|GMEM_ZEROINIT, m_dwSizeImage);
	if (!m_hGlobal)
	{
		return 0; 
	}
	else
	{
		m_nWidth  = nWidth;
		m_nHeight = nHeight;
		m_nAmountOfPixels = nWidth * nHeight;

		m_ptImageCenter.x = m_nWidth/2;
		m_ptImageCenter.y = m_nHeight/2;
//------------------------------------------------------------------
		m_pbPixels = (PBYTE)::GlobalLock( m_hGlobal );
		m_nMemAlloc = 1;

		m_pBitmapInfoY8->bmiHeader.biWidth = m_nWidth;
		if( cDirect == 1 )
			m_pBitmapInfoY8->bmiHeader.biHeight = m_nHeight;
		else
			m_pBitmapInfoY8->bmiHeader.biHeight = -m_nHeight;

		m_pBitmapInfoY8->bmiHeader.biSizeImage = m_dwSizeImage;


		for(i = 0, cClr=0xff; i<min(256,size.cy); i++,cClr--)			//初始值
		{
			for(j=0; j<size.cx; j++)
			{
				*(m_pbPixels + m_nRowLength*i+j)=cClr;
			}
		}

	}
	m_blLoaded = TRUE;
	return 1;

}

int C256Dib::Create256Dib(int nWidth, int nHeight)
{
	if( nWidth <= 0 ) return 0;
	if( nHeight == 0 ) return 0;

	SIZE size;
	size.cx = abs(nWidth);
	size.cy = abs(nHeight);

	if( nHeight > 0 )
		return Create8BitGrayMap( size, 1 );
	else
		return Create8BitGrayMap( size, -1 );
}

int C256Dib::Create256Dib(int nWidth, int nHeight, char cDirect)
{
	SIZE size;
	size.cx = abs(nWidth);
	size.cy = abs(nHeight);
	return Create8BitGrayMap( size, cDirect );
}

int C256Dib::Create256Dib( SIZE size )
{
	size.cx = abs( size.cx );
	size.cy = abs( size.cy );
	return Create8BitGrayMap( size, 1 );
}




//----拷贝像素--------------------------------------
void C256Dib::CopyPixels(PVOID pbSource)	//拷贝像素
{
	::CopyMemory( m_pbPixels, pbSource, m_dwSizeImage );
}





