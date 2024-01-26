
// LibSystemDlg.h: 头文件
//

#pragma once
#include "CUser.h"
#include "CDataAdapter.h"
// CLibSystemDlg 对话框
class CLibSystemDlg : public CDialogEx
{
// 构造
public:
	CLibSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CDataAdapter m_da;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// username
	CString m_csName;
	// password
	CString m_csPwd;
	list<CUser> m_listUser;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangePwd();
	void LoadUser(CString csFullPath);
	void CheckUser(CString csUName);
	list<CUser>* pList;
	list<CUser>::iterator m_it;
	bool bFound;
};
