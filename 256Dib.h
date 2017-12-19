// -------------  256Dib.h s------------------------------
//----------------------------------------------------------
#if !defined(C256DIB_123_ABC_sdufwevmb)
#define      C256DIB_123_ABC_sdufwevmb

class C256Dib			//通用的256色位图
{
private:
	BITMAPFILEHEADER m_bmfHeader;
	BITMAPINFOHEADER m_bmifHeader;
	LPBITMAPINFO m_pBitmapInfoY8;

	CString m_strFileName;
	int m_nMemAlloc;
	DWORD m_dwSizeImage;


public:
	C256Dib();
	~C256Dib();
	void CopyPixels(PVOID pbSource);

//--------//创建一个8位灰度图片---------------------------------------------
	int Create8BitGrayMap( SIZE size, char cDirect );	//创建一个8位灰度图片
	int Create256Dib( int nWidth, int nHeight );
	int Create256Dib( SIZE size );
	int Create256Dib( int nWidth, int nHeight, char cDirect );
//=======================================================


	VOID DrawBmp(CDC *pDC, int x, int y, int n)const;
	BOOL IsLoadedBmp();




protected:
	POINT m_ptImageCenter;		//图像的中心
	BOOL m_blLoaded;		//是否装入图片

	HGLOBAL m_hGlobal;		//内存句柄
	PBYTE m_pbPixels;		//存储像素的首地址
	int m_nRowLength;		//本图一行的字节数
	int m_nWidth;
	int m_nHeight;

	int m_nAmountOfPixels;	//图像的像素个数，m_nAmountOfPixels = m_nWidth*m_nHeight；

	int m_cDirection;		
};
//{{AFX_INSERT_LOCATION}}

#endif // !defined(C256DIB_123_ABC_sdufwevmb)
