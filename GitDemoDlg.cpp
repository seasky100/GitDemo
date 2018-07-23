
// GitDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GitDemo.h"
#include "GitDemoDlg.h"
#include "afxdialogex.h"
#include "Cameras.h"
#include "256Dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGitDemoDlg 对话框




CGitDemoDlg::CGitDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGitDemoDlg::IDD, pParent)
	, m_dbSpeed(0)
	, m_dbVoltage_1(0)
	, m_dbVoltage_2(0)
	, m_ulTriggerNumber_1(0)
	,m_pfLog_1(NULL)
	, m_ulSaveNumber_1(0)
	, m_bDirectoryExists_1(false)
	, m_TriggerNumber_1(0)
	, m_SaveNumber_1(0)
	//,m_strLeftPath("")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGitDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIEW_WND1, m_ImageWnd_1);
	DDX_Control(pDX, IDC_VIEW_WND2, m_ImageWnd_2);
	DDX_Text(pDX, IDC_EDIT3, m_dbSpeed);
	DDX_Text(pDX, IDC_EDIT1, m_dbVoltage_1);
	DDX_Text(pDX, IDC_EDIT2, m_dbVoltage_2);
	DDX_Text(pDX, IDC_EDIT4, m_TriggerNumber_1);
	DDX_Text(pDX, IDC_EDIT5, m_SaveNumber_1);
}

BEGIN_MESSAGE_MAP(CGitDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveData)
	//ON_MESSAGE(WM_COMM_RXCHAR, &CGitDemoDlg::OnReceiveData)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CGitDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGitDemoDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGitDemoDlg 消息处理程序

double ReadFreeSpace(CString strPath)
{
	HANDLE hFile=NULL;
	char szVolumeFile[10];
	double dRet=-1.0;
	DWORD dwSectPerClust,dwBytePerSect,dwNumberOfFreeClusters;
	sprintf_s(szVolumeFile,"%s:\\",strPath.Left(1));
	if(!GetDiskFreeSpace(szVolumeFile,&dwSectPerClust,&dwBytePerSect,&dwNumberOfFreeClusters,NULL))
	{
		dRet=-1.0;
	}
	else
	{
		dRet=(DWORD64)dwSectPerClust*(DWORD64)dwBytePerSect*(DWORD64)dwNumberOfFreeClusters/1024.0/1024.0/1024.0;
		//sprintf(szVolumeFile,"free size:%.02f",dRet);
	}
	return dRet;
}

BOOL CGitDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	struct DeviceList
	{
		int Index;
		char SN[128];
	};
	DeviceList dl[3];
	int iServerCount=SapManager::GetServerCount();


	for(int i=0;i<iServerCount;i++)
	{
		int iAcqDeviceNum=SapManager::GetResourceCount(i,SapManager::ResourceAcqDevice);
		int iAcqNum=SapManager::GetResourceCount(i,SapManager::ResourceAcq);
		if(iAcqDeviceNum>0||iAcqNum>0)
		{
			//char ServerName[128];
			//char DeviceName[128];
			//memset(ServerName,0x00,128);
			//SapManager::GetServerName(i,ServerName,sizeof(ServerName));
			//SapManager::GetServerSerialNumber(i,ServerName);
			SapManager::GetServerSerialNumber(i,dl[i].SN);
			dl[i].Index=i;
		}
	}
	

 //SapAcqToBuf(SapAcquisition *pAcq, SapBuffer *pBuf, SapXferCallback pCallback = NULL, void *pContext = NULL)
 //SapMultiAcqToBuf(SapAcquisition *pAcq[], SapBuffer *pBuf[], int numPairs, SapXferCallback pCallback = NULL, void *pContext = NULL)
	//CCameras ss;
	//ss.CreateCamera("sss","ddd",XferCallback_1,this,&m_ImageWnd_1);
		//m_AcqDevice_1	= new SapAcqDevice(SapLocation(dl[1].Index,0),"C:\\T_Linea_M2048-7um_12080124_3M.ccf");
	m_AcqDevice_1	= new SapAcqDevice(SapLocation(dl[1].Index,0),"C:\\T_Linea_M2048-7um_Default_Default.ccf");
		//m_AcqDevice_1	= new SapAcqDevice(SapLocation(dl[1].Index,0),"C:\\Program Files\\Teledyne DALSA\\Sapera\\Examples\\NET\\GitDemo\\GitDemo\\T_Linea_M2048-7um_12080124_3M.ccf");
		//m_AcqDevice_1	= new SapAcqDevice(SapLocation(dl[1].Index,0),m_configFileName_1);


	//m_AcqDevice_1	= new SapAcqDevice(SapLocation(m_serverName_1,m_resourceIndex_1),m_configFileName_1);
	m_Buffers_1	= new SapBufferWithTrash(2, m_AcqDevice_1);
	//m_Bayer     = new SapColorConversion(m_Buffers_1);
	m_Xfer_1		= new SapAcqDeviceToBuf(m_AcqDevice_1, m_Buffers_1, XferCallback_1, this);
	m_View_1      = new SapView(m_Buffers_1);
	
    // Attach sapview to image viewer 1
    m_ImageWnd_1.AttachSapView(m_View_1);

   if (!CreateObjects_1()) { EndDialog(TRUE); return FALSE; }

   //m_ImageWnd_1.AttachEventHandler(this);
   m_ImageWnd_1.CenterImage();
   m_ImageWnd_1.Reset();

   //FitToWindow(m_View_1);
   m_ImageWnd_1.Refresh();

 //  	SYSTEMTIME time;
	//::GetLocalTime(&time);
	//m_pTimeFileName = ZLBGetFormatTime(time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
	//m_strLeftPath.Format("%s\\%s\\Left",m_strStoragePath.GetBuffer(),m_pTimeFileName);
	//m_strRightPath.Format("%s\\%s\\Right",m_strStoragePath.GetBuffer(),m_pTimeFileName);
	//m_cSavePath_1=m_strLeftPath.GetBuffer();
	//m_cSavePath_2=m_strRightPath.GetBuffer();
    double m_dFreeSpaceG;
	m_dFreeSpaceG=ReadFreeSpace(m_strStoragePath);

	//CString temp;
	//temp.Format("#FreeSize:%.02fGB,Ready...$\r\n",m_dFreeSpaceG);

   CString m_strLeftPath;
   m_strLeftPath="D:\\Image";
   memcpy(m_cSavePath_1,m_strLeftPath.GetBuffer(),m_strLeftPath.GetLength());

    SYSTEMTIME time;
	::GetLocalTime(&time);
   	//if(m_pfLog_1 == NULL)
	//{	
	//	str.Format("L%d%02d%02d%02d%02d%02d%03d.log",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
	//	m_pfLog_1 = _tfopen(str,_T("wb"));
	//	//m_pfLog_1 = fopen("D:\\Leftlog.log","wb");
	//}

	//if(m_SerialPortOne.InitPort(this,1,9600,'N',8,1,EV_RXCHAR|EV_CTS,512))
	//{
	//	m_SerialPortOne.StartMonitoring();
	//}
	
	if(m_SerialPortTwo.InitPort(this,3,9600,'N',8,1,EV_RXCHAR|EV_CTS,512))
	{
		m_SerialPortTwo.StartMonitoring();
		//SetTimer(1,500,NULL);
	}
	SetTimer(1,500,NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//bool CNetWorkListDlg::ListAllCamera(int iMode)
//{
//	m_vecDeviceName.clear();
//	m_vecServerName.clear();
//
//	for(int i = 0; i < SapManager::GetServerCount(); i++)
//	{
//		m_iServerCount++;
//		// when m_serverCategory is ServerAcqDevice, show only servers that have only one resource that is an acqdevice and no acq
//		int iAcqDeviceNum =  SapManager::GetResourceCount(i, SapManager::ResourceAcqDevice);
//		int iAcqNum       =  SapManager::GetResourceCount(i, SapManager::ResourceAcq);
//		if (iAcqDeviceNum > 0 || iAcqNum > 0)
//		{
//			/*获取服务器名字*/
//			char ServerName[128];
//			char DeviceName[128];
//			string strDeviceName;
//			string strServerName;
//			memset(ServerName,0x00,128);
//
//			if(SapManager::GetServerName(i, ServerName, sizeof(ServerName)))
//			{
//				strServerName = string(ServerName);
//				m_vecServerName.push_back(strServerName);
//				//int index = SapManager::GetServerIndex()
//				/*遍历该Server下所有的采集卡*/
//				for(int iDeviceIndex = 0 ;iDeviceIndex < SapManager::GetResourceCount(ServerName, SapManager::ResourceAcq);iDeviceIndex++)
//				{
//					memset(DeviceName,0x00,128);
//					/*获取相机名称*/
//					if (SapManager::GetResourceName(ServerName, SapManager::ResourceAcq, iDeviceIndex, DeviceName, sizeof(DeviceName)))
//					{
//						//strcpy(m_pDeviceInfoStruct[iCameraCount]->chCameraSn,DeviceName);
//						strDeviceName = string(DeviceName);
//						m_vecDeviceName.push_back(strDeviceName);
//						m_vecServerIndex.push_back(iDeviceIndex);
//					}
//					//m_pDeviceInfoStruct[iCameraCount]->iCameraInterFace = 0x03;
//					m_iDeviceCount++;
//				}
//				/*遍历该Server下所有的设备*/
//				for(int iDeviceIndex = 0 ;iDeviceIndex < SapManager::GetResourceCount(ServerName, SapManager::ResourceAcqDevice);iDeviceIndex++)
//				{
//					memset(DeviceName,0x00,128);
//					//strcpy(m_pDeviceInfoStruct[iCameraCount]->chCameraReserved,ServerName);
//					//m_pDeviceInfoStruct[iCameraCount]->chCameraSdkVersion[0] = (char)iDeviceIndex;
//					/*获取相机名称*/
//					if (SapManager::GetResourceName(ServerName, SapManager::ResourceAcqDevice, iDeviceIndex, DeviceName, sizeof(DeviceName)))
//					{
//						//SapManager::GetServerName(i, ServerName, sizeof(serverName));
//						//SapAcqDevice camera(ServerName);
//						//BOOL status = camera.Create();
//						//if (status)
//						//{
//						////	// Get Serial Number Feature Value
//						//   char serialNumberName[255];
//						//	memset(serialNumberName,0x00,255);
//						//	status = camera.GetFeatureValue("DeviceID", serialNumberName, sizeof(serialNumberName));
//						//	if (status)
//						//	{
//								strDeviceName = string(DeviceName);
//								m_vecDeviceName.push_back(strDeviceName);
//								m_vecServerIndex.push_back(iDeviceIndex);
//							/*}
//						}*/
//							//if (!camera.Destroy()) return;
//							
//					}
//					//m_pDeviceInfoStruct[iCameraCount]->iCameraInterFace = 0x00;
//				}
//			}
//		}
//	}
//
//	if(m_vecDeviceName.size() == 0)
//	{
//		printf("@@iThreadCount = %d Can not Find Device\n",m_iServerCount);
//	}
//		
//	/*打印所有的服务器名字以及设备名字*/
//	for(int i = 0;i < m_vecDeviceName.size(); i++)
//	{
//		string strDeviceName = m_vecDeviceName.at 
//
//(i);
//		//printf("@@%d DeviceCount = %d DeivceServer = %s DeviceName = %s\n",iThreadCount,m_vecDeviceName.size(),m_vecServerName.at 
//
//(i).c_str(),strDeviceName.c_str());
//
//		CString str;
//		if(iMode == 0)
//		{
//			str.Format("@@%d List DeviceCount = %d DeivceServer = %s DeviceName = %s\n",i,m_vecDeviceName.size(),m_vecServerName.at 
//
//(i).c_str(),strDeviceName.c_str());
//		}
//		else if(iMode == 1)
//		{
//			str.Format("@@%d CallBack DeviceCount = %d DeivceServer = %s DeviceName = %s\n",i,m_vecDeviceName.size(),m_vecServerName.at 
//
//(i).c_str(),strDeviceName.c_str());
//		}
//		int iIndex = m_list.AddString(str);		
//		m_list.SetCurSel(iIndex);
//	}
//
//	return true;
//}


void CGitDemoDlg::FitToWindow(SapView *pView)
{

	int viewWidth;
	int viewHeight;

	
	BOOL	m_bLockAspectRatio=false;
	DWORD	scaleHeight;
	DWORD	scaleWidth;
	float	scaleHeightFactor;
	float	scaleWidthFactor;

	pView->GetViewArea( &viewWidth, &viewHeight);

	scaleWidthFactor = 100.0f * viewWidth/pView->GetBuffer()->GetWidth();
	scaleHeightFactor= 100.0f * viewHeight/pView->GetBuffer()->GetHeight();

	//if( m_bLockAspectRatio)
	//{
		if( scaleWidthFactor < scaleHeightFactor)
		{
			scaleHeightFactor= scaleWidthFactor;
		}
		else
		{
			scaleWidthFactor= scaleHeightFactor;
		}
	//}

	scaleWidth = (DWORD)floor(pView->GetBuffer()->GetWidth()  * scaleWidthFactor/100 + 0.5f);
	scaleHeight= (DWORD)floor(pView->GetBuffer()->GetHeight() * scaleHeightFactor/100 + 0.5f);

	scaleWidthFactor = 100.0f * scaleWidth / pView->GetBuffer()->GetWidth();
	scaleHeightFactor= 100.0f * scaleHeight / pView->GetBuffer()->GetHeight();
	//scaleWidthFactor=(float)23.584;
	//scaleHeightFactor=(float)25.5859;
	pView->SetScalingMode( scaleWidthFactor/100.0f, scaleHeightFactor/100.0f);
	UpdateData( FALSE);

	//	int viewWidth;
	//int viewHeight;

	//m_pView->GetViewArea( &viewWidth, &viewHeight);

	//m_scaleWidthFactor = 100.0f * viewWidth/m_pView->GetBuffer()->GetWidth();
	//m_scaleHeightFactor= 100.0f * viewHeight/m_pView->GetBuffer()->GetHeight();

	//if( m_bLockAspectRatio)
	//{
	//	if( m_scaleWidthFactor < m_scaleHeightFactor)
	//	{
	//		m_scaleHeightFactor= m_scaleWidthFactor;
	//	}
	//	else
	//	{
	//		m_scaleWidthFactor= m_scaleHeightFactor;
	//	}
	//}

	//m_scaleWidth = (DWORD)floor(m_pView->GetBuffer()->GetWidth()  * m_scaleWidthFactor/100 + 0.5f);
	//m_scaleHeight= (DWORD)floor(m_pView->GetBuffer()->GetHeight() * m_scaleHeightFactor/100 + 0.5f);

	//m_scaleWidthFactor = 100.0f * m_scaleWidth / m_pView->GetBuffer()->GetWidth();
	//m_scaleHeightFactor= 100.0f * m_scaleHeight / m_pView->GetBuffer()->GetHeight();

	//UpdateData( FALSE);
}

void CGitDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGitDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGitDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CGitDemoDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	static BYTE RBufOne[25]={0};
	static int RPosOne=0;
	static BYTE RBufTwo[25]={0};
	static int RPosTwo=0;
	INT16 revint16[4],rint16[8];
	int iTemp;
	switch((UINT)lParam)
	{
	case 1:
		RBufOne[RPosOne++]=(UINT)wParam;
		if(RPosOne>13){
			for(int i=3,j=0;i<11;j++,i+=2)
				revint16[j] =RBufOne[i] * 256+ RBufOne[i + 1];
			iTemp=(int)(revint16[0]/100.0);
			m_dbVoltage_1=iTemp/10.0;
			//iTemp=(int)(revint16[1]/100.0);
			//pThis->m_dbSpeed =iTemp/10.0;
			iTemp=(int)(revint16[2]/100.0);
			m_dbVoltage_2 =iTemp/10.0;
			RPosOne=0;
		}
		break;
	case 3:
		RBufTwo[RPosTwo++]=(UINT)wParam;
		if(RPosTwo>20){
			for(int m=3,n=0;m<19;n++,m+=2)
				rint16[n] =RBufTwo[m] * 256+ RBufTwo[m + 1];
			iTemp=(int)(rint16[4]+rint16[5]);
			m_dbSpeed =iTemp/1.0;
			RPosTwo=0;
		}
		break;
	}
	m_dbVoltage_1=0.0001;
	m_dbVoltage_2=0.0002;
	UpdateData(false);
	return 0;
}

void CGitDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	//byte sendvoltage[] = {0x01,0x03,0x02,0x58,0x00,0x04,0xC4,0x62};
	//byte sendfrequency[]={0x01,0x03,0x00,0x00,0x00,0x08,0x44,0x0C};
	////m_SerialPortOne.WriteToPort((char*)sendvoltage,8);
	//m_SerialPortTwo.WriteToPort((char*)sendfrequency,8);
	//KillTimer(1);

	m_TriggerNumber_1=m_ulTriggerNumber_1;
   m_SaveNumber_1=m_ulSaveNumber_1;
   UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}


void CGitDemoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//KillTimer(1);

	DestroyObjects_1();

	// Delete all objects
   if (m_View_1)			delete m_View_1;
	if (m_Xfer_1)			delete m_Xfer_1;
	if (m_Buffers_1)		delete m_Buffers_1;
	if (m_AcqDevice_1)	delete m_AcqDevice_1;

	if(m_pfLog_1)
	{
		fclose(m_pfLog_1);
		m_pfLog_1 = NULL;
	}
}

BOOL CGitDemoDlg::CreateObjects_1()
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

BOOL CGitDemoDlg::DestroyObjects_1()
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

void  LoadMemImage( void *  pMemData,  long  len)
{
HGLOBAL hGlobal  =  GlobalAlloc(GMEM_MOVEABLE, len);
void *  pData  =  GlobalLock(hGlobal);
memcpy(pData, pMemData, len);
GlobalUnlock(hGlobal);
IStream *  pStream  =  NULL;
if  (CreateStreamOnHGlobal(hGlobal, TRUE,  & pStream)  ==  S_OK)
{
CImage image;
if (SUCCEEDED(image.Load(pStream)))
    {
		image.Save("D:\\111.jpg");
 
}
pStream -> Release();    
}
GlobalFree(hGlobal);
}


void Save_Bitmap(CString strFilePath, CBitmap* Bitmap)
{
if ( Bitmap->m_hObject )
{
CImage imgTemp; // CImage是MFC中的类。
imgTemp.Attach(Bitmap->operator HBITMAP());
imgTemp.Save(strFilePath);
}
}
//
//int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)   
//{   
//    UINT num = 0;                     // number of image encoders   
//    UINT size = 0;                   // size of the image encoder array in bytes   
//    ImageCodecInfo* pImageCodecInfo = NULL;   
//    GetImageEncodersSize(&num, &size);   
//    if(size == 0)   
//        return -1;     //   Failure   
//    
//    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));   
//    if(pImageCodecInfo == NULL)   
//        return -1;     //   Failure   
//    
//    GetImageEncoders(num, size, pImageCodecInfo);   
//    for(UINT j = 0; j < num; ++j)   
//    {   
//        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )   
//        {   
//            *pClsid = pImageCodecInfo[j].Clsid;   
//            free(pImageCodecInfo);   
//            return j;     //   Success   
//        }           
//    }   
//    free(pImageCodecInfo);   
//    return -1;     //   Failure   
//}

//void SaveFile(Bitmap* pImage, const wchar_t* pFileName)//
//{
//    EncoderParameters encoderParameters;
//    CLSID jpgClsid; 
//	GetEncoderClsid(L"image/jpeg", &jpgClsid);
//    encoderParameters.Count = 1;
//    encoderParameters.Parameter[0].Guid = EncoderQuality;
//    encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
//    encoderParameters.Parameter[0].NumberOfValues = 1;
//    // Save the image as a JPEG with quality level 100.
//    ULONG             quality;
//    quality = 100;
//    encoderParameters.Parameter[0].Value = &quality;
//    Status status = pImage->Save(pFileName, &jpgClsid, &encoderParameters);
//    if (status != Ok) 
//    {
//        wprintf(L"%d Attempt to save %s failed./n", status, pFileName);
//    }
//}

void FillBitmapInfo( BITMAPINFO *bmi, int width, int height, int bpp,int pitch )
{
 BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);
 memset( bmih, 0, sizeof(*bmih));
 bmih->biWidth  = width;
 bmih->biHeight = pitch*height;
 bmih->biPlanes = 1;
 bmih->biBitCount = bpp;
 bmih->biCompression = BI_RGB; 
 bmih->biSize   = sizeof(BITMAPINFOHEADER);
 if( bpp == 8 )
 {
  RGBQUAD* palette = bmi->bmiColors;
  int i;
  for( i = 0; i < 256; i++ )
  {
   palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
   palette[i].rgbReserved = 0;
  }
 }
}
void CGitDemoDlg::XferCallback_1(SapXferCallbackInfo * pInfo)
{
	CGitDemoDlg *pDlg= (CGitDemoDlg *) pInfo->GetContext();
	int iCounter,iWidth,iHeight = 0;
		int iImageType = 0;
    void *pImageData_1 = NULL;
    BOOL iSucceed = 0;
    SapBuffer *pBuffer_1 = NULL;
	char ch_ImageFileName_1[4096];
	int iCount = 0;
	time_t start;
	time_t end;
	double timeSpace;
    
	pDlg->m_View_1->Show();
	
	HDC view;
	pDlg->m_View_1->GetDC(&view);
	//BOOL Rectangle(HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect)；
	CPen penRed(PS_SOLID, 1, RGB(255,255,255));
	SelectObject(view, penRed);
	MoveToEx(view,10,10,NULL);
	LineTo(view,200,200 );
	//Rectangle(view, 10, 10, 100, 100);
	


//
//	CDC MemDC; //首先定义一个显示设备对象
//CBitmap MemBitmap;//定义一个位图对象
////随后建立与屏幕显示兼容的内存显示设备
//MemDC.CreateCompatibleDC(NULL);
////这时还不能绘图，因为没有地方画 ^_^
////下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小，也可以自己定义（如：有滚动条时就要大于当前窗口的大小，在BitBlt时决定拷贝内存的哪部分到屏幕上）
////MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
//CBitmap  MemBitmap.CreateBitmap(bmp.bmWidth,bmp.bmHeight,1,24,pBits);
//MemBitmap.SetBitmapBits(
////将位图选入到内存显示设备中
////只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
//CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
////先用背景色将位图清除干净，这里我用的是白色作为背景
////你也可以用自己应该用的颜色
//MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));
//	CDC MemDC; //首先定义一个显示设备对象
//CBitmap MemBitmap;//定义一个位图对象
////随后建立与屏幕显示兼容的内存显示设备
//MemDC.CreateCompatibleDC(NULL);
////这时还不能绘图，因为没有地方画 ^_^
////下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小，也可以自己定义（如：有滚动条时就要大于当前窗口的大小，在BitBlt时决定拷贝内存的哪部分到屏幕上）
//MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
//
//
////将位图选入到内存显示设备中
////只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
//CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
////先用背景色将位图清除干净，这里我用的是白色作为背景
////你也可以用自己应该用的颜色
//MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));
////绘图
//MemDC.MoveTo(……);
//MemDC.LineTo(……);
//
//
////将内存中的图拷贝到屏幕上进行显示
//pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
////绘图完成后的清理
//MemBitmap.DeleteObject();
//MemDC.DeleteDC();


	pBuffer_1 = pDlg->m_Buffers_1;
	iCount =  pInfo->GetEventCount();
   pDlg->m_ulTriggerNumber_1++;
   iSucceed = (pBuffer_1->GetAddress(&pImageData_1));
   if(iSucceed)
   {


	   
//	   CImage imgTemp; // CImage是MFC中的类。
//	   IStream p(pImageData_1);
//
//	   imgTemp.Load((IStream*)pImageData_1);
//	   sprintf_s(ch_ImageFileName_1,1024,"%s\\%08d.bmp",pDlg->m_cSavePath_1,++pDlg->m_ulSaveNumber_1);
//imgTemp.Save(ch_ImageFileName_1);


	//    CPaintDC l_PaintDC( this ) ; 
 //CRect l_rcClient ; 
 //GetClientRect( &l_rcClient ) ; 
 //CDC l_MaskDC ; 
 //l_MaskDC.CreateCompatibleDC( &l_PaintDC ) ; 
 //CBitmap l_MaskBitmap ; 
 //l_MaskBitmap.CreateBitmap( l_rcClient.Width(),  l_rcClient.Height(), 1, 1, NULL ) ; 
 //CBitmap* l_pOldMaskBitmap = l_MaskDC.SelectObject( &l_MaskBitmap ) ; 
 //CDC l_MemoryDC ;
 //l_MemoryDC.CreateCompatibleDC( &l_PaintDC ) ; 
 //CBitmap* l_pOldMemoryBitmap = l_MemoryDC.SelectObject( CBitmap::FromHandle( l_hbmpBitmap ) ) ; 
 //COLORREF l_crOldBack =l_MemoryDC.SetBkColor( RGB( 255, 0, 255 ) ) ; 
 //l_MaskDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MemoryDC, 0, 0, SRCCOPY ) ; 
 //l_PaintDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MemoryDC, 0, 0, SRCINVERT ) ; 
 //l_PaintDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MaskDC, 0, 0, SRCAND ) ; 
 //l_PaintDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MemoryDC, 0, 0, SRCINVERT ) ; 
 //l_MemoryDC.SelectObject( l_pOldMemoryBitmap ) ; 
 //l_MaskDC.SelectObject( l_pOldMaskBitmap ) ; 

	   		CDC *pDC;
		pDC=pDlg->GetDC();
	   CDC MemDC; //首先定义一个显示设备对象
		CBitmap  MemBitmap;
		iWidth = pBuffer_1->GetWidth();//图像宽度
		iHeight = pBuffer_1->GetHeight();//图像的高度
		
		//LoadMemImage(pImageData_1,iWidth*iHeight);
		//随后建立与屏幕显示兼容的内存显示设备
		//MemDC.CreateCompatibleDC(NULL);
		//MemBitmap.CreateCompatibleBitmap(&MemDC,iWidth,iHeight);
		
		MemDC.CreateCompatibleDC(pDC);
		MemBitmap.CreateCompatibleBitmap(pDC,iWidth/4,iHeight/4);
		//MemBitmap.CreateBitmapIndirect
		//MemBitmap.CreateBitmap(iWidth,iHeight,1,24,pImageData_1);

		//MemBitmap.CreateBitmap(iWidth,iHeight,1,8,NULL);
		//
		////MemBitmap.CreateCompatibleBitmap(pDC,iWidth/4,iHeight/4);
		//MemBitmap.SetBitmapBits(iWidth*iHeight,pImageData_1);

		CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);//图像在MemDC中

		//C256Dib dib;
	 //  dib.Create256Dib(2048,2048,-1);
	 //  dib.CopyPixels(pImageData_1);

	 //  dib.DrawBmp(&MemDC,0,0,0);

	 //  pDC->SetStretchBltMode(COLORONCOLOR);
	 //  pDC->StretchBlt(0,0,512,512,&MemDC,0,0,2048,2048,SRCCOPY);


	   
		//pDC->BitBlt(0,0,2048,2048,&MemDC,0,0,SRCCOPY);

		//CBitmap  bitmap;
		//bitmap.CreateCompatibleBitmap(pDC,iWidth,iHeight);
		//bitmap.SetBitmapBits(iWidth*iHeight,pImageData_1);

		//MemBitmap.CreateCompatibleBitmap(pDC,iWidth,iHeight);
		//MemBitmap.SetBitmapBits(iWidth*iHeight,pImageData_1);
		//bool a=MemBitmap.CreateBitmap(2048,2048,1,8,NULL);
		//bool a=MemBitmap.CreateBitmap(2048,2048,1,8,NULL);
		//DWORD c=MemBitmap.SetBitmapBits(iWidth*iHeight,pImageData_1);
		//BITMAPINFO ucPicBoxInfo;

		//StretchDIBits(pDC->GetSafeHdc(),0,0,512,512,0,0,2048,2048,(void *)pImageData_1,(BITMAPINFO*)ucPicBoxInfo,DIB_RGB_COLORS,SRCCOPY);

	//    #define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
 //// TODO: Add your control notification handler code here
 //int i,j;
 //BYTE* m_bitData=new BYTE[800*600];
 //ZeroMemory((void*)m_bitData, 800*600);
 //for (i=0; i<600; i++)
 //{
 // for(j=0; j<800; j++)
 // {
 //  m_bitData[i*800+j]=255*i/600;
 // }
 //}

 LONG lWidth=2048;
 LONG lHeight=-2048;//注意此位置为负值因为BMP图像数据存储是上下倒置
 LPBITMAPINFO lpbmi;
 // BMP文件头的句柄
 HANDLE hBmpFileHead;
 //计算信息头和调色板的大小
 hBmpFileHead=::GlobalAlloc(GHND,sizeof(BITMAPINFOHEADER)
         + sizeof(RGBQUAD)
         * 256);
 if(hBmpFileHead==0)
 {
  AfxMessageBox("分配内存失败");
  return;
 }
 //填充信息头
 lpbmi=(LPBITMAPINFO)::GlobalLock((HGLOBAL)hBmpFileHead);
 lpbmi->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
 lpbmi->bmiHeader.biWidth=lWidth;
 lpbmi->bmiHeader.biHeight=lHeight;
 lpbmi->bmiHeader.biPlanes=1;
 lpbmi->bmiHeader.biBitCount=8;
 lpbmi->bmiHeader.biCompression=BI_RGB;
 lpbmi->bmiHeader.biSizeImage=(((lWidth*8) + 31) / 32 * 4)*lHeight;
 lpbmi->bmiHeader.biXPelsPerMeter=0;
 lpbmi->bmiHeader.biYPelsPerMeter=0;
 lpbmi->bmiHeader.biClrUsed=256;
 lpbmi->bmiHeader.biClrImportant=256;
 //填充256级灰度调色板
 for(int i=0;i<256;i++)
 {
  lpbmi->bmiColors[i].rgbBlue=i;
  lpbmi->bmiColors[i].rgbGreen=i;
  lpbmi->bmiColors[i].rgbRed=i;
  lpbmi->bmiColors[i].rgbReserved=0;
 }

// CreateDIBSection( MemDC.GetSafeHdc(),lpbmi,DIB_RGB_COLORS,(void **)&pImageData_1,0,0 );
  SetStretchBltMode(MemDC.GetSafeHdc(),COLORONCOLOR);//避免图像缩放失真添加模式
  StretchDIBits(MemDC.GetSafeHdc(),  
        0,0,512,512,  
        0,0,2047+1,2047+1,  
        pImageData_1,  
        lpbmi,  
        DIB_RGB_COLORS,  
        SRCCOPY);

 //StretchDIBits( pDC->GetSafeHdc(),  
 //       0,0,  
 //               2048,  
 //               2048,  
 //       0,0,2047+1,2047+1,  
 //       pImageData_1,  
 //       lpbmi,  
 //       DIB_RGB_COLORS,  
 //       SRCCOPY  );

////填充文件头
// BITMAPFILEHEADER bmfHeader;
// ZeroMemory(&bmfHeader,sizeof(bmfHeader));
// bmfHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ sizeof(RGBQUAD) * 256;
// bmfHeader.bfSize=lpbmi->bmiHeader.biSizeImage+bmfHeader.bfOffBits;
// bmfHeader.bfType='MB';
// BYTE* pBits=new BYTE[lpbmi->bmiHeader.biSizeImage];
// ZeroMemory((void*)pBits, lpbmi->bmiHeader.biSizeImage);
// for (i=0; i<lHeight; i++)
// {
//  for (j=0; j<lWidth;j++)
//  {
//   pBits[WIDTHBYTES(lWidth*8)*(lHeight-1-i)+j]=m_bitData[i*lWidth+j];
//  }
// }
// 
// CString str="c://test1.bmp";
// HANDLE hFile=CreateFile(str,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
// if(hFile!=INVALID_HANDLE_VALUE)
// {
//  DWORD dwRet=0;
//  WriteFile(hFile,&bmfHeader,sizeof(bmfHeader),&dwRet,NULL);
//  WriteFile(hFile,&lpbmi->bmiHeader,sizeof(lpbmi->bmiHeader),&dwRet,NULL);
//  WriteFile(hFile,&lpbmi->bmiColors[0],sizeof(RGBQUAD) * 256,&dwRet,NULL);
//  WriteFile(hFile,pBits,lpbmi->bmiHeader.biSizeImage,&dwRet,NULL);
//  CloseHandle(hFile); 
// }
// delete[] pBits;
// delete[] m_bitData;
// ::GlobalUnlock((HGLOBAL)hBmpFileHead);
// ::GlobalFree((HGLOBAL) hBmpFileHead);
//



//
//		unsigned char hBitMapInfo[sizeof(BITMAPINFOHEADER)+  
//                          sizeof(RGBQUAD)* 256];  
//tagBITMAPINFO *BitMapInfo=(tagBITMAPINFO *) hBitMapInfo;  
//for(int i=0;i<256;i++)  
//{  
//    BitMapInfo->bmiColors[i].rgbBlue = i;  
//    BitMapInfo->bmiColors[i].rgbGreen = i;  
//    BitMapInfo->bmiColors[i].rgbRed = i;  
//    BitMapInfo->bmiColors[i].rgbReserved = i;  
//}  
//BitMapInfo->bmiHeader.biSize=40;//sizeof(tagBITMAPINFOHEADER); 
//BitMapInfo->bmiHeader.biBitCount = 8;  
//BitMapInfo->bmiHeader.biClrImportant = 0;  
//BitMapInfo->bmiHeader.biClrUsed = 0;  
//BitMapInfo->bmiHeader.biCompression = BI_RGB;  
//BitMapInfo->bmiHeader.biPlanes = 1;  
//BitMapInfo->bmiHeader.biSizeImage =0;  
//BitMapInfo->bmiHeader.biXPelsPerMeter = 0;  
//BitMapInfo->bmiHeader.biYPelsPerMeter = 0;  
////BitMapInfo->bmiHeader.biSizeImage =0;  
////BitMapInfo->bmiHeader.biXPelsPerMeter = 0;  
////BitMapInfo->bmiHeader.biYPelsPerMeter = 0;  
////BitMapInfo->bmiHeader.biHeight = nLines+1;//  
////BitMapInfo->bmiHeader.biWidth = nPixels+1;//  
////StretchDIBits( pDC->GetSafeHdc(),  
////        0,0,  
////                m_ClientRect.right,  
////                m_ClientRect.bottom,  
////        0,0,nPixels+1,nLines+1,  
////        pImage,  
////        BitMapInfo,  
////        DIB_RGB_COLORS,  
////        SRCCOPY  );  
//
//BitMapInfo->bmiHeader.biHeight = -2048;//  
//BitMapInfo->bmiHeader.biWidth = 2048;//  
//
//		::SetDIBitsToDevice (	pDC->GetSafeHdc(),	//1
//								0,					//2
//								0,					//3
//								2048,	//4
//								2048,	//5
//								0,				//6
//								0,				//7
//								0,				//8
//								2048, //9
//								pImageData_1, //10
//								BitMapInfo,	//11
//								DIB_RGB_COLORS);	//12

//BITMAPFILEHEADER bmf;
//bmf.bfType =0x4D42;
//bmf.bfSize =sizeof(BITMAPINFOHEADER)+ sizeof(RGBQUAD)* 256+2048*2048;
//bmf.bfReserved1=0;
//bmf.bfReserved2=0;
//bmf.bfOffBits=sizeof(BITMAPINFOHEADER)+ sizeof(RGBQUAD)* 256;
//CFile fp;
//fp.Open("D:\\model.bmp",CFile::modeCreate|CFile::modeWrite);
//fp.Write((LPSTR)&bmf,sizeof(BITMAPFILEHEADER));
//fp.Write((LPSTR)BitMapInfo,sizeof(BITMAPINFOHEADER)+ sizeof(RGBQUAD)* 256);
//fp.Write(pImageData_1,2048*2048);
//fp.Close();

//StretchDIBits( pDC->GetSafeHdc(),  
//        0,0,  
//                512,  
//                512,  
//        0,0,2047+1,2047+1,  
//        pImageData_1,  
//        BitMapInfo,  
//        DIB_RGB_COLORS,  
//        SRCCOPY  );  


  //BITMAPINFO   bmi;   
  //bmi.bmiHeader.biSize=sizeof(BITMAPINFO);   
  //bmi.bmiHeader.biWidth=2048;   
  //bmi.bmiHeader.biHeight=2048;   
  //bmi.bmiHeader.biPlanes=1;   
  //bmi.bmiHeader.biBitCount=8;   
  //bmi.bmiHeader.biCompression=BI_RGB;   
  //bmi.bmiHeader.biClrUsed=0;   
  //  
  ////HDC   hdc=GetWindowDC(Panel1->Handle);   
  ////SetStretchBltMode(COLORONCOLOR);   
  //StretchDIBits(pDC->GetSafeHdc(),0,0,512,512,0,0,2048,2048,pImageData_1,&bmi,DIB_RGB_COLORS,SRCCOPY);


//BITMAPINFO *bm=(BITMAPINFO*)new byte[sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(256)];   
//FillBitmapInfo(bm,2048,-2048,8,2048);
//
//StretchDIBits( pDC->GetSafeHdc(),  
//        0,0,  
//                512,  
//                512,  
//        0,0,2048,2048,  
//        pImageData_1,  
//        bm,  
//        DIB_RGB_COLORS,  
//        SRCCOPY  );  


//pDC->StretchBlt(0,0,512,512,&MemDC,0,0,2048,2048,SRCCOPY);

		//BITMAP bm;
		//BYTE *pBits=new BYTE[2048*2048];
		////MemBitmap.GetObject(sizeof(bm), &bm);
		//bm.bmHeight=2048;
		//bm.bmWidth=2048;
		//bm.bmBitsPixel=8;
		//bm.bmType=0;
		//bm.bmBits=pBits;//pImageData_1;
		//bm.bmWidthBytes=iWidth+iWidth%2;//iWidth/2+(iWidth/2)%2;
		//bool b=MemBitmap.CreateBitmapIndirect(&bm);



		//MemBitmap.CreateBitmap(2048,2048,1,8,pImageData_1);


		//CDC   memDC;  
  // CBitmap   memBitmap;  
  // memDC.CreateCompatibleDC(pDC);  
  // memBitmap.CreateBitmap(width,height,1,24,(BYTE*)pImageData);  
  // CBitmap*   pOldBitmap=memDC.SelectObject(&memBitmap);  
  //  
  // pDC->BitBlt(0,0,width,height,&memDC,0,0,SRCCOPY);  
  //  
  // memDC.SelectObject(pOldBitmap);  

/*		hBitmap =CreateBitmap(100,100,1,32,p); 
        hBitmapDC = CreateCompatibleDC(hdc); 
        SelectObject(hBitmapDC,hBitmap);*/ 

		

		//MemBitmap.CreateBitmap( iWidth, iHeight, 1, 1, NULL ) ; 
		//MemBitmap.CreateBitmap(iWidth,iHeight,1,24,pImageData_1);
		//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上

		//SelectObject(MemDC,MemBitmap);

	//CBitmap *pOldBit=MemDC.SelectObject(&bitmap);//图像在MemDC中
		//CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);//图像在MemDC中

		//pDC->BitBlt(0,0,512,512,&MemDC,0,0,SRCCOPY);

		pDlg->m_ulSaveNumber_1++;


		//sprintf_s(ch_ImageFileName_1,1024,"%s\\%08d.jpg",pDlg->m_cSavePath_1,++pDlg->m_ulSaveNumber_1);
		CString st;
		   CString m_strLeftPath;
   m_strLeftPath="D:\\Image";
		//memcpy(m_cSavePath_1,m_strLeftPath.GetBuffer(),m_strLeftPath.GetLength());
		//st.Format("%s\\%08d.jpg",pDlg->m_cSavePath_1,++pDlg->m_ulSaveNumber_1);
		st.Format("%s\\1-%08d.jpg",m_strLeftPath,pDlg->m_ulSaveNumber_1);
		//Save_Bitmap(st,&MemBitmap);
		
		
		CImage imgTemp; // CImage是MFC中的类。
		//imgTemp.Create(iWidth,iHeight,24) ;
		//HDC hdc=imgTemp.GetDC();
		
		//StretchBlt(hdc,0,0,2048,2048,MemDC.GetSafeHdc(),0,0,512,512,SRCCOPY);
		//pDC->StretchBlt(0,0,512,512,&MemDC,0,0,512,512,SRCCOPY);
		//imgTemp.b
		//BitBlt(imgTemp.GetDC(),0,0,2048,2048,MemDC.m_hDC,0,0,SRCCOPY);
		
		//HBITMAP b1=CreateBitmap(iWidth,iHeight,1,32,pImageData_1);
		//imgTemp.Attach(b1);

		imgTemp.Attach(MemBitmap.operator HBITMAP());
		//imgTemp.Attach((HBITMAP)MemBitmap.GetSafeHandle()); 

		imgTemp.Save(st );
		////imgTemp.Save(st,Gdiplus::ImageFormatJPEG );
		

		//st.Format("%s\\4-%08d.jpg",m_strLeftPath,pDlg->m_ulSaveNumber_1);
		////Save_Bitmap(st,&MemBitmap);
		//
		//
		//CImage img;
		//img.Attach(bitmap.operator HBITMAP());
		//img.Save(st );

//Bitmap Image(HBITMAP(MemBitmap),NULL);//从CBitmap中得到HBitmap
//
// EncoderParameters encoderParameters;
//    CLSID jpgClsid; 
//	GetEncoderClsid(L"image/jpeg", &jpgClsid);
//    encoderParameters.Count = 1;
//    encoderParameters.Parameter[0].Guid = EncoderQuality;
//    encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
//    encoderParameters.Parameter[0].NumberOfValues = 1;
//    // Save the image as a JPEG with quality level 100.
//    ULONG             quality;
//    quality = 100;
//    encoderParameters.Parameter[0].Value = &quality;
//    Status status = Image.Save(pFileName, &jpgClsid, &encoderParameters);

//	Bitmap mbitmap(HBITMAP(MemBitmap),NULL);//从CBitmap中得到HBitmap
//CLSID jpegClsid;
//
//
//
//GetEncoderClsid(L"image/jpeg", &jpegClsid);//选择编码
//
//
//CStringW strWide = CT2CW(st); // 将T字符转换成宽字符
//WCHAR *pFileName = strWide.GetBuffer();  // 获取CString内部缓存，并保证缓存长
//mbitmap.Save(pFileName,&jpegClsid);



 



//mbitmap.Save("bbb.jpg",&jpegClsid);//保存

		//const unsigned short *pFileName=L"d://new.jpg";//保存路径
		//SaveFile(&MemBitmap,pFileName );


		//将内存中的图拷贝到屏幕上进行显示
		//pDC->StretchBlt(0,0,512,512,&MemDC,0,0,2048,2048,SRCCOPY);
		//pDC->BitBlt(0,0,2048,2048,&MemDC,0,0,SRCCOPY);
		int width=iWidth;
		int height=iHeight;

		//CImage image;
  //  image.Create(width, height, 32);
  //  BitBlt(image.GetDC(), 0, 0, width, height, MemDC.m_hDC, 0, 0, SRCCOPY);

  //  HRESULT hResult = image.Save("D:\\new.jpg");

		//pDC->BitBlt(0,0,iWidth,iHeight,&MemDC,0,0,SRCCOPY);
		//绘图完成后的清理
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();//清楚内存DC
		
	   if(!pDlg->m_bDirectoryExists_1)
		{
			//判断目录是否存在,如果不存在就创建目录
			pDlg->m_bDirectoryExists_1=true;
			ZLBCreateDirectory(pDlg->m_cSavePath_1);
		}
		start = clock();
		memcpy(pDlg->m_cSavePath_1,m_strLeftPath.GetBuffer(),m_strLeftPath.GetLength());
		sprintf_s(ch_ImageFileName_1,1024,"%s\\2-%08d.bmp",pDlg->m_cSavePath_1,pDlg->m_ulSaveNumber_1);
		pBuffer_1->Save(ch_ImageFileName_1,"-format bmp");


		

		//sprintf_s(ch_ImageFileName_1,1024,"%s\\%08d.bmp",pDlg->m_cSavePath_1,pDlg->m_ulSaveNumber_1);
		//pBuffer_1->Save("D:\\Image\\SS.avi","-format avi",-1,iCount);

		//sprintf_s(ch_ImageFileName_1,1024,"%s\\3-%08d.jpg",pDlg->m_cSavePath_1,pDlg->m_ulSaveNumber_1);
		//pBuffer_1->Save(ch_ImageFileName_1,"-format jpeg -quality 80");
		//pBuffer_1->Save(ch_ImageFileName_1,"-format jpeg");
		//CRect rect;
		//rect.top =0;
		//rect.left =0;
		//rect.right =100;
		//rect.bottom=100;
		//HBITMAP hBitmapSrc;  
		//hBitmapSrc = CreateCompatibleBitmap(view, rect.right, rect.bottom);  
		//SelectObject(hMemDC, hBitmapSrc);  
		//BitBlt(hMemDC, 0, 0, rect.right, rect.bottom, hdc, 0, 0, SRCCOPY);  
		//SaveBitmap(hBitmapSrc , "C:\\123.bmp");     // SaveBitmap()是自定义的一个函数，用来把传递进来的位图句柄保存成图片文件  

		end = clock();
		timeSpace =(double)(end - start);
		if(pDlg->m_pfLog_1 != NULL)
		{
			pDlg->m_ulSaveNumber_1++;
			SYSTEMTIME time;
			::GetLocalTime(&time);
			fprintf(pDlg->m_pfLog_1,"L:%d-%d-%d %d:%d:%d.%d tcount=%d acount=%d time=%f\r\n",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,pDlg->m_ulTriggerNumber_1,pDlg->m_ulSaveNumber_1,timeSpace);
		}

		pBuffer_1->ReleaseAddress(&pImageData_1);
   }

}


void CGitDemoDlg::OnBnClickedOk()
{
	BOOL bAcqNoGrab	= m_Xfer_1 && *m_Xfer_1 && !m_Xfer_1->IsGrabbing();
	BOOL bAcqGrab		= m_Xfer_1 && *m_Xfer_1 && m_Xfer_1->IsGrabbing();
	BOOL bNoGrab		= !m_Xfer_1 || !m_Xfer_1->IsGrabbing();
	if( m_Xfer_1->Grab())
	{

	// Acquisition Control
	GetDlgItem(IDCANCEL)->EnableWindow(bAcqNoGrab);
	GetDlgItem(IDOK)->EnableWindow(bAcqGrab);
	}
	//CDialogEx::OnOK();
}


void CGitDemoDlg::OnBnClickedCancel()
{
	BOOL bAcqNoGrab	= m_Xfer_1 && *m_Xfer_1 && !m_Xfer_1->IsGrabbing();
	BOOL bAcqGrab		= m_Xfer_1 && *m_Xfer_1 && m_Xfer_1->IsGrabbing();
	BOOL bNoGrab		= !m_Xfer_1 || !m_Xfer_1->IsGrabbing();
	if( m_Xfer_1->Freeze())
	{
		if (CAbortDlg(this, m_Xfer_1).DoModal() != IDOK) 
		{
			m_Xfer_1->Abort();
		}
		// Acquisition Control
		GetDlgItem(IDCANCEL)->EnableWindow(bAcqNoGrab);
		GetDlgItem(IDOK)->EnableWindow(bAcqGrab);
	}
	KillTimer(1);
	CDialogEx::OnCancel();
}
