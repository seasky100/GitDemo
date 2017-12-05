#pragma once
#include "SapClassBasic.h"
#include "SapClassGui.h"
#include "ZLBCommonLib.h"
#include "ZLBImageLib.h"

class CCameras
{
public:
	CCameras(void);
	~CCameras(void);
public:
	struct DeviceList
	{
		int Index;
		char SN[128];
	};
	DeviceList dl[3];
	CImageExWnd    m_ImageWnd_1;
	CString m_configFileName_1;
	SapAcqDevice	*m_AcqDevice_1;
	SapBuffer		*m_Buffers_1;
	SapTransfer		*m_Xfer_1;
	SapView        *m_View_1;
	int GetCameraCount(void);

};

