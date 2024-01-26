#pragma once


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
	CString m_csNo;
	CString m_csName;
	BOOL m_bGender;
	COleDateTime m_tmBirth;
	int m_nGrade;
	CComboBox m_comboMajor;
	virtual BOOL OnInitDialog();
	CSpinButtonCtrl m_spinGrade;
	afx_msg void OnBnClickedOk();
public:
	CDataAdapter* m_pDA;
	void SetDA(CDataAdapter* pDA);
};
