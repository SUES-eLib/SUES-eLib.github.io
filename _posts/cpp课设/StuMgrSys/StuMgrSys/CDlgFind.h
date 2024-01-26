#pragma once


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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedFind();
	CString m_csNo;
	CString m_csName;
	CComboBox m_comboMajor;
	COleDateTime m_tmBirth;
	int m_nGrade;
	BOOL m_bGender;
	CSpinButtonCtrl m_spinGrade;
	
public:
	CString m_csMajor;
	CDataAdapter* m_pDA;
	void SetDA(CDataAdapter* pDA);
};
