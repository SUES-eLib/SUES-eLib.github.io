// CDlgDelete.cpp: 实现文件
//

#include "pch.h"
#include "globe.h"
#include "CBook.h"
#include "CData.h"
#include "CDataAdapter.h"
#include "LibSystem.h"
#include "afxdialogex.h"
#include "CDlgDelete.h"


// CDlgDelete 对话框

IMPLEMENT_DYNAMIC(CDlgDelete, CDialogEx)

CDlgDelete::CDlgDelete(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELETE, pParent)
	, m_csName(_T(""))
	, m_csISBN(_T(""))
	, m_dtBuy(COleDateTime::GetCurrentTime())
	, m_cbCatalog()
	, m_csPublisher(_T(""))
	, m_nPMonth(0)
	, m_nPYear(0)
{

}

CDlgDelete::~CDlgDelete()
{
}

void CDlgDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CATA, m_cbCatalog);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BUY, m_dtBuy);
	DDX_Text(pDX, IDC_EDIT_ISBN, m_csISBN);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDX_Text(pDX, IDC_EDIT_BNO, m_nBNo);
	DDX_Text(pDX, IDC_EDIT_PMONTH, m_nPMonth);
	DDX_Text(pDX, IDC_EDIT_PUB, m_csPublisher);
	DDX_Text(pDX, IDC_EDIT_PYEAR, m_nPYear);
	DDX_Control(pDX, IDC_SPIN_MONTH, m_spinMonth);
	DDX_Control(pDX, IDC_SPIN_NUM, m_spinBNum);
	DDX_Control(pDX, IDC_SPIN_YEAR, m_spinYear);
	DDX_Text(pDX, IDC_EDIT_BNO, m_nBNo);
	DDX_Text(pDX, IDC_EDIT_BORROW, m_csBorrow);
	DDX_Text(pDX, IDC_EDIT_STOCK, m_nStock);
}


BEGIN_MESSAGE_MAP(CDlgDelete, CDialogEx)
	ON_BN_CLICKED(ID_ABORT_ISBN, &CDlgDelete::OnBnClickedAbortIsbn)
	ON_BN_CLICKED(ID_ABORT_NO, &CDlgDelete::OnBnClickedAbortNo)
	ON_BN_CLICKED(IDC_DELETEBOOK, &CDlgDelete::OnBnClickedDeletebook)
	ON_BN_CLICKED(IDC_DELETEALL, &CDlgDelete::OnBnClickedDeleteall)
END_MESSAGE_MAP()


// CDlgDelete 消息处理程序

void CDlgDelete::SetDA(CDataAdapter* pDA)
{
	m_pDA = pDA;
}

void CDlgDelete::OnBnClickedAbortIsbn()
{
	// TODO: 在此添加控件通知处理程序代码
	CBook book = CBook();
	int index = 0;
	UpdateData(TRUE);
	string sISBN = m_csISBN.GetBuffer();

	if (m_pDA->FindBNumByISBN(sISBN, book))
	{
		for (int i = 0; i < CataNum; i++)
			if (m_pDA->m_it->m_sCatalog == g_BookCata[i].GetBuffer())
				index = i;
		m_cbCatalog.SetCurSel(index);
		m_csName = m_pDA->m_it->m_sName.c_str();
		m_csPublisher = m_pDA->m_it->m_sPublisher.c_str();
		m_nPYear = m_pDA->m_it->m_nPYear;
		m_nPMonth = m_pDA->m_it->m_nPMonth;
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("数据库中无该ISBN号，请先录入数据！"));
	}
}


BOOL CDlgDelete::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_nPYear = 2023;
	m_nPMonth = 1;
	m_csBorrow = _T("未借出");
	for (int i = 0; i < CataNum; i++)
		m_cbCatalog.AddString(g_BookCata[i]);
	m_cbCatalog.SetCurSel(0);
	UpdateData(FALSE);
	m_spinBNum.SetBuddy(GetDlgItem(IDC_EDIT_BNO));
	m_spinBNum.SetRange(1, 100);
	m_spinBNum.SetBuddy(GetDlgItem(IDC_EDIT_NUM));
	m_spinBNum.SetRange(1, 1000);
	m_spinYear.SetBuddy(GetDlgItem(IDC_EDIT_PYEAR));
	m_spinYear.SetRange(1950, 2050);
	m_spinMonth.SetBuddy(GetDlgItem(IDC_EDIT_PMONTH));
	m_spinMonth.SetRange(1, 12);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDlgDelete::OnBnClickedAbortNo()
{
	// TODO: 在此添加控件通知处理程序代码
	CBook book = CBook();
	int index = 0;
	UpdateData(TRUE);
	int nBNo = m_nBNo;
	string sISBN = m_csISBN.GetBuffer();

	m_pDA->FindBookByNo(sISBN, nBNo, book);
	m_pDA->FillWithBook(book, m_csName, m_csISBN, m_csPublisher,
		m_nStock, m_nPYear, m_nPMonth, m_csCatalog, m_dtBuy, m_nBNo, m_csBorrow);
	UpdateData(FALSE);

	for (int i = 0; i < CataNum; i++)
		if (m_pDA->m_it->m_sCatalog == g_BookCata[i].GetBuffer())
			index = i;
	m_cbCatalog.SetCurSel(index);
}


void CDlgDelete::OnBnClickedDeletebook()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int nBNo = m_nBNo;
	CBook book = CBook();
	string sISBN = m_csISBN.GetBuffer();
	m_pDA->DeleBookByNo(sISBN, nBNo);
	m_pDA->UpdateBookInfo(m_csName.GetBuffer(), m_csISBN.GetBuffer(), m_csPublisher.GetBuffer(),
		m_nStock - 1 , m_nPYear, m_nPMonth, g_BookCata[m_cbCatalog.GetCurSel()].GetBuffer());
	m_pDA->GetFirstBook(book);
	m_pDA->FillWithBook(book, m_csName, m_csISBN, m_csPublisher,
		m_nStock, m_nPYear, m_nPMonth, m_csCatalog, m_dtBuy, m_nBNo, m_csBorrow);
	UpdateData(FALSE);
	m_pDA->Save();
}


void CDlgDelete::OnBnClickedDeleteall()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int nBNo = m_nBNo;
	string sISBN = m_csISBN.GetBuffer();
	CBook book = CBook();
	m_pDA->DeleBookByISBN(sISBN);
	m_pDA->GetFirstBook(book);
	m_pDA->FillWithBook(book, m_csName, m_csISBN, m_csPublisher,
		m_nStock, m_nPYear, m_nPMonth, m_csCatalog, m_dtBuy, m_nBNo, m_csBorrow);
	UpdateData(FALSE);
	m_pDA->Save();
}
