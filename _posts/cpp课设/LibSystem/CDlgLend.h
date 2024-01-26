#pragma once
#include "afxdialogex.h"
#include "CHistory.h"

// CDlgLend 对话框

class CDlgLend : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLend)

public:
	CDlgLend(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgLend();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csCatalog;
	CDataAdapter* m_pDA;
	void SetDA(CDataAdapter* pDA);
	virtual BOOL OnInitDialog();
	CComboBox m_cbCatalog;
	int m_nBNo;
	CString m_csBorrow;
	CString m_csISBN;
	CString m_csName;
	CString m_csPublisher;
	int m_nReturn;
	int m_nStock;
	int m_nPMonth;
	int m_nPYear;
	COleDateTime m_dtBuy;
	COleDateTime m_dtLTime;
	CSpinButtonCtrl m_spinBNum;

	afx_msg void OnBnClickedAbort();
	afx_msg void OnBnClickedLend();
	afx_msg void OnBnClickedReturn();

	void AddHistory(string sISBN, int nNo, string sBorrow,
		int nLYear, int nLMonth, int nLDay);
	void LoadHistory(CString csFullPath);
	void SaveHistory(CString csFullPath);

	list<CHistory> m_listHistory;
	list<CHistory>* pList;
	list<CHistory>::iterator m_it;
};
