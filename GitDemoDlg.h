
// GitDemoDlg.h : ͷ�ļ�
//
#include "SerialPort.h"
#pragma once

// CGitDemoDlg �Ի���
class CGitDemoDlg : public CDialogEx
{
// ����
public:
	CGitDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GITDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
