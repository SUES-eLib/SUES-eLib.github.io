#pragma once
#include "afxdialogex.h"


// CDlgFind 对话框

class CDlgFind : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFind)

public:
	CDlgFind(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgFind();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedFind();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedNext();
public:
	CString m_csCatalog;
	CDataAdapter* m_pDA;
	void SetDA(CDataAdapter* pDA);
	afx_msg void OnBnClickedUpdateinfo();
	afx_msg void OnBnClickedUpdatebook();
};
