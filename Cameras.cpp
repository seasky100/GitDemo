#include "StdAfx.h"
#include "Cameras.h"


CCameras::CCameras(void)
{
}


CCameras::~CCameras(void)
{
	DestroyObjects_1();

	// Delete all objects
   if (m_View_1)			delete m_View_1;
	if (m_Xfer_1)			delete m_Xfer_1;
	if (m_Buffers_1)		delete m_Buffers_1;
	if (m_AcqDevice_1)	delete m_AcqDevice_1;
}


int CCameras::GetCameraCount(void)
{
	int iCameraCount=0;
	int iServerCount=SapManager::GetServerCount();
	for(int i=0;i<iServerCount;i++)
	{
		int iAcqDeviceNum=SapManager::GetResourceCount(i,SapManager::ResourceAcqDevice);
		int iAcqNum=SapManager::GetResourceCount(i,SapManager::ResourceAcq);
		if(iAcqDeviceNum>0||iAcqNum>0)
		{
			SapManager::GetServerSerialNumber(i,dl[i].SN);
			dl[i].Index=i;
			iCameraCount++;
		}
	}

	return iCameraCount;
}


bool CCameras::CreateCamera(CString SerialNumber,CString ConfigFile,SapXferCallback pCallback,void *pContext,CImageExWnd *pImageWnd)
{
		//m_AcqDevice_1	= new SapAcqDevice(SapLocation(dl[1].Index,0),"C:\\T_Linea_M2048-7um_12080124_3M.ccf");
	m_AcqDevice_1	= new SapAcqDevice(SapLocation(1,0),"C:\\T_Linea_M2048-7um_Default_Default.ccf");
		//m_AcqDevice_1	= new SapAcqDevice(SapLocation(dl[1].Index,0),"C:\\Program Files\\Teledyne DALSA\\Sapera\\Examples\\NET\\GitDemo\\GitDemo\\T_Linea_M2048-7um_12080124_3M.ccf");
		//m_AcqDevice_1	= new SapAcqDevice(SapLocation(dl[1].Index,0),m_configFileName_1);

	//m_AcqDevice_1	= new SapAcqDevice(SapLocation(m_serverName_1,m_resourceIndex_1),m_configFileName_1);
	m_Buffers_1	= new SapBufferWithTrash(2, m_AcqDevice_1);
	//m_Bayer     = new SapColorConversion(m_Buffers_1);
	//m_Xfer_1		= new SapAcqDeviceToBuf(m_AcqDevice_1, m_Buffers_1, pCallback, pContext);
	m_View_1      = new SapView(m_Buffers_1);
	
    // Attach sapview to image viewer 1
    pImageWnd->AttachSapView(m_View_1);

   if (!CreateObjects_1()) {return FALSE; }

	
   ////m_ImageWnd_1.AttachEventHandler(this);
   //m_ImageWnd_1.CenterImage();
   //m_ImageWnd_1.Reset();

   ////FitToWindow(m_View_1);
   //m_ImageWnd_1.Refresh();

	return false;
}

BOOL CCameras::CreateObjects_1()
{
	CWaitCursor wait;

	// Create acquisition object
	if (m_AcqDevice_1 && !*m_AcqDevice_1 && !m_AcqDevice_1->Create())
   {
      DestroyObjects_1();
      return FALSE;
   }

	// Create buffer object
	if ((m_Buffers_1 && !*m_Buffers_1))
	{
		if( !m_Buffers_1->Create())
		{
			DestroyObjects_1();
			return FALSE;
		}
		// Clear all buffers
		m_Buffers_1->Clear();
		
	}
	//if(m_iBayerEnable == 1)
	//{
	//	bool bSet = m_Bayer->SetOutputFormat(SapFormatRGB888);
	//	if(bSet == FALSE)
	//		return false;

	//	bSet = m_Bayer->Enable(1, 0);
	//	if(bSet == FALSE)
	//		return false;
	//	
	//	/*创建贝尔滤波*/
	//	if(!m_Bayer->Create())
	//	{
	//		return false;
	//	}

	//	SapBuffer* bayerBuffer = m_Bayer->GetOutputBuffer();
 //       if (bayerBuffer && *bayerBuffer)
	//		m_View_1->SetBuffer(bayerBuffer);
 //       else
	//		m_View_1->SetBuffer(m_Buffers_1);

	//	// Set alignment 
	//	m_Bayer->SetAlign(m_align[m_iBayerType]);

	//	// Set interpolation method
	//	m_Bayer->SetMethod(SapBayer::Method1);
	//}

	// Create view object
	if (m_View_1 && !*m_View_1 && !m_View_1->Create())
   {
      DestroyObjects_1();
      return FALSE;
   }

   // Set next empty with trash cycle mode for transfer
   if (m_Xfer_1 && m_Xfer_1->GetPair(0))
   {
	   //if (!m_Xfer_1->GetPair(0)->SetCycleMode(SapXferPair::EventEndOfFrame))
	  if (!m_Xfer_1->GetPair(0)->SetCycleMode(SapXferPair::CycleNextWithTrash))
      {
         DestroyObjects_1();
         return FALSE;
      }
   }

	// Create transfer object
	if (m_Xfer_1 && !*m_Xfer_1 && !m_Xfer_1->Create())
   {
      DestroyObjects_1();
      return FALSE;
   }

	return TRUE;
}

BOOL CCameras::DestroyObjects_1()
{
	// Destroy transfer object
	if (m_Xfer_1 && *m_Xfer_1) m_Xfer_1->Destroy();

	// Destroy view object
	if (m_View_1 && *m_View_1) m_View_1->Destroy();

	//if(m_iBayerEnable == 1)
	//{
	//	if (m_Bayer && *m_Bayer) m_Bayer->Destroy();
	//}

	// Destroy buffer object
	if (m_Buffers_1 && *m_Buffers_1) m_Buffers_1->Destroy();

	// Destroy acquisition object
	if (m_AcqDevice_1 && *m_AcqDevice_1) m_AcqDevice_1->Destroy();

	return TRUE;
}
