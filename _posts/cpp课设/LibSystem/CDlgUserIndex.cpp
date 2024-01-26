// CDlgUserIndex.cpp: 实现文件
//

#include "pch.h"
#include "CDlgUserIndex.h"
#include "CDlgLend.h"
#include "LibSystemDlg.h"
#include "LibSystem.h"
#include "afxdialogex.h"


// CDlgUserIndex 对话框

IMPLEMENT_DYNAMIC(CDlgUserIndex, CDialogEx)

CDlgUserIndex::CDlgUserIndex(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_USER_INDEX, pParent)
{

}

CDlgUserIndex::~CDlgUserIndex()
{
}

void CDlgUserIndex::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgUserIndex, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CDlgUserIndex::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDCANCEL, &CDlgUserIndex::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgUserIndex 消息处理程序


void CDlgUserIndex::OnBnClickedButtonInput()
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


BOOL CDlgUserIndex::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_da = new CDataAdapter();
	m_da->Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgUserIndex::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	CLibSystemDlg dlg;
	dlg.DoModal();
}
