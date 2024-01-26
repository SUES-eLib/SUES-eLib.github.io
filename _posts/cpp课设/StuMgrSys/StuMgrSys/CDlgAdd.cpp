// CDlgAdd.cpp: 实现文件
//

#include "pch.h"
#include "globe.h"
#include "CStudent.h"
#include "CData.h"
#include "CDataAdapter.h"
#include "StuMgrSys.h"
#include "CDlgAdd.h"
#include "afxdialogex.h"


// CDlgAdd 对话框

IMPLEMENT_DYNAMIC(CDlgAdd, CDialogEx)

CDlgAdd::CDlgAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, m_csNo(_T(""))
	, m_csName(_T(""))
	, m_bGender(FALSE)
	, m_tmBirth(COleDateTime::GetCurrentTime())
	, m_nGrade(0)
{

}

CDlgAdd::~CDlgAdd()
{
}

void CDlgAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NO, m_csNo);
	DDV_MaxChars(pDX, m_csNo, 8);
	DDX_Text(pDX, IDC_NAME, m_csName);
	DDX_Radio(pDX, IDC_RADIO_GENDER, m_bGender);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIRTH, m_tmBirth);
	DDX_Text(pDX, IDC_GRADE, m_nGrade);
	DDV_MinMaxInt(pDX, m_nGrade, 1978, 2050);
	DDX_Control(pDX, IDC_COMBO_MAJOR, m_comboMajor);
	DDX_Control(pDX, IDC_SPIN1, m_spinGrade);
}


BEGIN_MESSAGE_MAP(CDlgAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgAdd 消息处理程序
void CDlgAdd::SetDA(CDataAdapter* pDA)
{
	m_pDA = pDA;
}

BOOL CDlgAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_bGender = GENDER_MALE;
	m_nGrade = 2021;
	for (int i = 0; i < MAJORS_NUM ; i++)
		m_comboMajor.AddString(g_csMajors[i]);
	m_comboMajor.SetCurSel(0);
	UpdateData(FALSE);
	m_spinGrade.SetBuddy(GetDlgItem(IDC_GRADE));
	m_spinGrade.SetRange(1978, 2050);
	GetDlgItem(IDC_NO)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString csMajor;
	csMajor = g_csMajors[m_comboMajor.GetCurSel()];
	m_pDA->AddStudent(m_csNo.GetBuffer(), m_csName.GetBuffer(), m_bGender, 
		           m_tmBirth.GetYear(), m_tmBirth.GetMonth(), m_tmBirth.GetDay(),
		           m_nGrade, csMajor.GetBuffer());

	m_pDA->Save();
	
	CDialogEx::OnOK();
}
