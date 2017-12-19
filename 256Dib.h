// -------------  256Dib.h s------------------------------
//----------------------------------------------------------
#if !defined(C256DIB_123_ABC_sdufwevmb)
#define      C256DIB_123_ABC_sdufwevmb

class C256Dib			//ͨ�õ�256ɫλͼ
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

//--------//����һ��8λ�Ҷ�ͼƬ---------------------------------------------
	int Create8BitGrayMap( SIZE size, char cDirect );	//����һ��8λ�Ҷ�ͼƬ
	int Create256Dib( int nWidth, int nHeight );
	int Create256Dib( SIZE size );
	int Create256Dib( int nWidth, int nHeight, char cDirect );
//=======================================================


	VOID DrawBmp(CDC *pDC, int x, int y, int n)const;
	BOOL IsLoadedBmp();




protected:
	POINT m_ptImageCenter;		//ͼ�������
	BOOL m_blLoaded;		//�Ƿ�װ��ͼƬ

	HGLOBAL m_hGlobal;		//�ڴ���
	PBYTE m_pbPixels;		//�洢���ص��׵�ַ
	int m_nRowLength;		//��ͼһ�е��ֽ���
	int m_nWidth;
	int m_nHeight;

	int m_nAmountOfPixels;	//ͼ������ظ�����m_nAmountOfPixels = m_nWidth*m_nHeight��

	int m_cDirection;		
};
//{{AFX_INSERT_LOCATION}}

#endif // !defined(C256DIB_123_ABC_sdufwevmb)
