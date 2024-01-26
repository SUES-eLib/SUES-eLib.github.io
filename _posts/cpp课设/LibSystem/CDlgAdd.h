#pragma once
#include "afxdialogex.h"

// CDlgAdd 对话框

class CDlgAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAdd)

public:
	CDlgAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csName;
	CString m_csISBN;
	CString m_csPublisher;
	int m_nBNum;
	CSpinButtonCtrl m_spinBNum;
	// PublishYear
	int m_nPYear;
	// PublishMonth
	int m_nPMonth;
	int m_nBNo;
	CSpinButtonCtrl m_spinYear;
	CSpinButtonCtrl m_spinMonth;
	CComboBox m_cbCatalog;
	COleDateTime m_dtBuy;
	CString m_csBorrow;
	int m_nStock;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
public:
	CDataAdapter* m_pDA;
	void SetDA(CDataAdapter* pDA);
	afx_msg void OnBnClickedAbort();
};