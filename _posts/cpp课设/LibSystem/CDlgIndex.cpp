// CDlgIndex.cpp: 实现文件
//

#include "pch.h"
#include "CDlgIndex.h"
#include "CDlgAdd.h"
#include "CDlgFind.h"
#include "CDlgDelete.h"
#include "CDlgLend.h"
#include "LibSystemDlg.h"
#include "LibSystem.h"
#include "afxdialogex.h"


// CDlgIndex 对话框

IMPLEMENT_DYNAMIC(CDlgIndex, CDialogEx)

CDlgIndex::CDlgIndex(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INDEX, pParent)
{

}

CDlgIndex::~CDlgIndex()
{
}

void CDlgIndex::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgIndex, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgIndex::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CDlgIndex::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgIndex::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CDlgIndex::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDCANCEL, &CDlgIndex::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgIndex 消息处理程序


void CDlgIndex::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDlgAdd dlg;
	//dlg.SetDA(m_da);
	//dlg.DoModal();
	CDlgAdd* dlg = new CDlgAdd(this);
	CDataAdapter* cd = m_da;
	dlg->SetDA(cd);
	dlg->DoModal();
	delete dlg;
}


void CDlgIndex::OnBnClickedButtonFind()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_da->GetNumOfBook() == 0)
	{
		AfxMessageBox(_T("请先录入数据！"));
		return;
	}

	CDlgFind dlg;
	dlg.SetDA(m_da);
	dlg.DoModal();
}


void CDlgIndex::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_da->GetNumOfBook() == 0)
	{
		AfxMessageBox(_T("请先录入数据！"));
		return;
	}

	CDlgDelete dlg;
	dlg.SetDA(m_da);
	dlg.DoModal();
}


void CDlgIndex::OnBnClickedButtonInput()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_da->GetNumOfBook() == 0)
	{
		AfxMessageBox(_T("请先录入数据！"));
		return;
	}
	
	CDlgLend dlg;
	dlg.SetDA(m_da);
	dlg.DoModal();
}


BOOL CDlgIndex::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_da = new CDataAdapter();
	m_da->Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDlgIndex::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	CLibSystemDlg dlg;
	dlg.DoModal();
}
