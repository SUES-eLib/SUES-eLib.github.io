#pragma once
#include "afxdialogex.h"
#include "CDataAdapter.h"

// CDlgUserIndex 对话框

class CDlgUserIndex : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUserIndex)

public:
	CDlgUserIndex(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgUserIndex();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_USER_INDEX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDataAdapter* m_da;
	afx_msg void OnBnClickedButtonInput();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
};
