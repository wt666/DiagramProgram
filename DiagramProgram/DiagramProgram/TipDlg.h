#pragma once


// CTipDlg �Ի���

class CTipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDlg)

public:
	CTipDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTipDlg();

// �Ի�������
	enum { IDD = IDD_TIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};