
// GitDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

//#include   "GdiPlus.h "
//using   namespace   Gdiplus;

// CGitDemoApp:
// �йش����ʵ�֣������ GitDemo.cpp
//

class CGitDemoApp : public CWinApp
{
public:
	CGitDemoApp();
	ULONG_PTR        m_gdiplusToken;
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CGitDemoApp theApp;