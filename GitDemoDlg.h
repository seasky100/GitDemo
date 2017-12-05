
// GitDemoDlg.h : 头文件
//

#include "SapClassBasic.h"
#include "SapClassGui.h"
#include "ZLBCommonLib.h"
#include "ZLBImageLib.h"

#include "SerialPort.h"
#pragma once

// CGitDemoDlg 对话框
class CGitDemoDlg : public CDialogEx
{
// 构造
public:
	CGitDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GITDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//afx_msg LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
public:
	 CImageExWnd    m_ImageWnd_1;
	CString m_configFileName_1;
	SapAcqDevice	*m_AcqDevice_1;
	SapBuffer		*m_Buffers_1;
	SapTransfer		*m_Xfer_1;
	SapView        *m_View_1;
	//double m_dbVoltage_1;
	//double m_dbVoltage_2;
	//double m_dbSpeed;
	CSerialPort m_SerialPortOne;
	CSerialPort m_SerialPortTwo;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	double m_dbSpeed;
	double m_dbVoltage_1;
	double m_dbVoltage_2;
	BOOL CreateObjects_1();
	BOOL DestroyObjects_1();
	void FitToWindow(SapView *pView);
	static void XferCallback_1(SapXferCallbackInfo * pInfo);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	FILE *m_pfLog_1;
	unsigned long m_ulTriggerNumber_1;
	unsigned long m_ulSaveNumber_1;
	bool m_bDirectoryExists_1;
	char m_cSavePath_1[1024];
	long m_TriggerNumber_1;
	long m_SaveNumber_1;
};
