#pragma once
#include "afxdialogex.h"
#include "CDataAdapter.h"

// CDlgIndex 对话框

class CDlgIndex : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIndex)

public:
	CDlgIndex(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgIndex();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INDEX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonInput();
	virtual BOOL OnInitDialog();
public:
	CDataAdapter* m_da;
	afx_msg void OnBnClickedCancel();
};
