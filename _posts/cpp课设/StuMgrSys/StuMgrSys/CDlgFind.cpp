// CDlgFind.cpp: 实现文件
//

#include "pch.h"
#include "globe.h"
#include "CStudent.h"
#include "CData.h"
#include "CDataAdapter.h"
#include "StuMgrSys.h"
#include "CDlgFind.h"
#include "afxdialogex.h"


// CDlgFind 对话框

IMPLEMENT_DYNAMIC(CDlgFind, CDialogEx)

CDlgFind::CDlgFind(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FIND, pParent)
	, m_csNo(_T(""))
	, m_csName(_T(""))
	, m_tmBirth(COleDateTime::GetCurrentTime())
	, m_nGrade(0)
	, m_bGender(FALSE)
{

}

CDlgFind::~CDlgFind()
{
}

void CDlgFind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NO, m_csNo);
	DDV_MaxChars(pDX, m_csNo, 8);
	DDX_Text(pDX, IDC_NAME, m_csName);
	DDX_Control(pDX, IDC_COMBO_MAJOR, m_comboMajor);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIRTH, m_tmBirth);
	DDX_Text(pDX, IDC_GRADE, m_nGrade);
	DDV_MinMaxInt(pDX, m_nGrade, 1978, 2050);
	DDX_Radio(pDX, IDC_RADIO_GENDER, m_bGender);
	DDX_Control(pDX, IDC_SPIN1, m_spinGrade);
}


BEGIN_MESSAGE_MAP(CDlgFind, CDialogEx)
	ON_BN_CLICKED(IDC_PREV, &CDlgFind::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_NEXT, &CDlgFind::OnBnClickedNext)
	ON_BN_CLICKED(IDC_FIND, &CDlgFind::OnBnClickedFind)
END_MESSAGE_MAP()


// CDlgFind 消息处理程序

void CDlgFind::SetDA(CDataAdapter* pDA)
{
	m_pDA = pDA;
}

BOOL CDlgFind::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_pDA && m_pDA->GetNumOfStudent()>0)
	{
		CStudent stu;
		int index=0;
		m_pDA->GetFirstStudent(stu);
		m_pDA->FillWithStudent(stu, m_csNo, m_csName, m_bGender, m_tmBirth, m_nGrade, m_csMajor);
		for (int i = 0; i < MAJORS_NUM; i++)
		{
			m_comboMajor.AddString(g_csMajors[i]);
			if (m_csMajor == g_csMajors[i])
				index = i;
		}
		m_comboMajor.SetCurSel(index);
	}
	UpdateData(FALSE);
	m_spinGrade.SetBuddy(GetDlgItem(IDC_GRADE));
	m_spinGrade.SetRange(1978, 2050);
	GetDlgItem(IDC_NO)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgFind::OnBnClickedPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	CStudent stu;
	int index = 0;
	m_pDA->GetPrevStudent(stu);
	m_pDA->FillWithStudent(stu, m_csNo, m_csName, m_bGender, m_tmBirth, m_nGrade, m_csMajor);
	UpdateData(FALSE);

	for (int i = 0; i < MAJORS_NUM; i++)
		if (m_csMajor == g_csMajors[i])
			index = i;
	m_comboMajor.SetCurSel(index);
}


void CDlgFind::OnBnClickedNext()
{
	// TODO: 在此添加控件通知处理程序代码
	CStudent stu;
	int index = 0;
	m_pDA->GetNextStudent(stu);
	m_pDA->FillWithStudent(stu, m_csNo, m_csName, m_bGender, m_tmBirth, m_nGrade, m_csMajor);
	UpdateData(FALSE);

	for (int i = 0; i < MAJORS_NUM; i++)
		if (m_csMajor == g_csMajors[i])
			index = i;
	m_comboMajor.SetCurSel(index);

}


void CDlgFind::OnBnClickedFind()
{
	// TODO: 在此添加控件通知处理程序代码
	CStudent stu;
	int index = 0;
	UpdateData(TRUE);
	string sNo = m_csNo.GetBuffer();
	m_pDA->FindStudentByNo(sNo,stu);
	m_pDA->FillWithStudent(stu, m_csNo, m_csName, m_bGender, m_tmBirth, m_nGrade, m_csMajor);
	UpdateData(FALSE);

	for (int i = 0; i < MAJORS_NUM; i++)
		if (m_csMajor == g_csMajors[i])
			index = i;
	m_comboMajor.SetCurSel(index);
}
