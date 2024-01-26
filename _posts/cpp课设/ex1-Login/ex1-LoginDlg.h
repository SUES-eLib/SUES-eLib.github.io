
// ex1-LoginDlg.h: 头文件
//

#pragma once


// Cex1LoginDlg 对话框
class Cex1LoginDlg : public CDialogEx
{
// 构造
public:
	Cex1LoginDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EX1LOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	// user name
	CString m_csName;
	// Password
	// Password
	CString m_csPwd;
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedName();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangePwd();
};
