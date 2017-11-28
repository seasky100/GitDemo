
// GitDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GitDemo.h"
#include "GitDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGitDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_dbSpeed);
	DDX_Text(pDX, IDC_EDIT1, m_dbVoltage_1);
	DDX_Text(pDX, IDC_EDIT2, m_dbVoltage_2);
}

BEGIN_MESSAGE_MAP(CGitDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveData)
	//ON_MESSAGE(WM_COMM_RXCHAR, &CGitDemoDlg::OnReceiveData)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGitDemoDlg 消息处理程序

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
	//if(m_SerialPortOne.InitPort(this,1,9600,'N',8,1,EV_RXCHAR|EV_CTS,512))
	//{
	//	m_SerialPortOne.StartMonitoring();
	//}
	
	if(m_SerialPortTwo.InitPort(this,3,9600,'N',8,1,EV_RXCHAR|EV_CTS,512))
	{
		m_SerialPortTwo.StartMonitoring();
		SetTimer(1,500,NULL);
	}
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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
	byte sendvoltage[] = {0x01,0x03,0x02,0x58,0x00,0x04,0xC4,0x62};
	byte sendfrequency[]={0x01,0x03,0x00,0x00,0x00,0x08,0x44,0x0C};
	//m_SerialPortOne.WriteToPort((char*)sendvoltage,8);
	m_SerialPortTwo.WriteToPort((char*)sendfrequency,8);
	KillTimer(1);
	CDialogEx::OnTimer(nIDEvent);
}


void CGitDemoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//KillTimer(1);
}
