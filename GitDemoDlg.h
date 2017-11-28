
// GitDemoDlg.h : 头文件
//
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
};
