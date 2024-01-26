#pragma once
#include "afxdialogex.h"


// CDlgDelete 对话框

class CDlgDelete : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDelete)

public:
	CDlgDelete(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgDelete();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cbCatalog;
	COleDateTime m_dtBuy;
	CString m_csISBN;
	CString m_csName;
	int m_nPMonth;
	CString m_csPublisher;
	int m_nPYear;
	CSpinButtonCtrl m_spinMonth;
	CSpinButtonCtrl m_spinBNum;
	CSpinButtonCtrl m_spinYear;
	int m_nBNo;
	CString m_csBorrow;
	//int m_nBNum;
	int m_nStock;
public:
	CString m_csCatalog;
	CDataAdapter* m_pDA;
	void SetDA(CDataAdapter* pDA);
	afx_msg void OnBnClickedAbortIsbn();
	afx_msg void OnBnClickedAbortNo();
	afx_msg void OnBnClickedDeletebook();
	afx_msg void OnBnClickedDeleteall();
};
