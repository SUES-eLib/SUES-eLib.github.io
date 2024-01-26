// CDlgFind.cpp: 实现文件
//

#include "pch.h"
#include "globe.h"
#include "CBook.h"
#include "CData.h"
#include "CDataAdapter.h"
#include "LibSystem.h"
#include "afxdialogex.h"
#include "CDlgFind.h"


// CDlgFind 对话框

IMPLEMENT_DYNAMIC(CDlgFind, CDialogEx)

CDlgFind::CDlgFind(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FIND, pParent)
	, m_dtBuy(COleDateTime::GetCurrentTime())
	, m_csISBN(_T(""))
	, m_csName(_T(""))
	, m_nPMonth(0)
	, m_csPublisher(_T(""))
	, m_nPYear(0)
	, m_csBorrow(_T(""))
	, m_cbCatalog()
	, m_nStock(0)
{

}

CDlgFind::~CDlgFind()
{
}

void CDlgFind::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CDlgFind, CDialogEx)
	ON_BN_CLICKED(IDC_FIND, &CDlgFind::OnBnClickedFind)
	ON_BN_CLICKED(IDC_PREV, &CDlgFind::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_NEXT, &CDlgFind::OnBnClickedNext)
	ON_BN_CLICKED(IDC_UPDATEINFO, &CDlgFind::OnBnClickedUpdateinfo)
	ON_BN_CLICKED(IDC_UPDATEBOOK, &CDlgFind::OnBnClickedUpdatebook)
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
	if (m_pDA && m_pDA->GetNumOfBook() > 0)
	{
		int index = 0;
		for (int i = 0; i < CataNum; i++)
		{
			m_cbCatalog.AddString(g_BookCata[i]);
			if (m_csCatalog = g_BookCata[i])
				index = i;
		}
		
		CBook book = CBook();
		m_pDA->GetFirstBook(book);
		m_pDA->FillWithBook(book, m_csName, m_csISBN, m_csPublisher,
			m_nStock, m_nPYear, m_nPMonth, m_csCatalog, m_dtBuy, m_nBNo, m_csBorrow);

		for (int i = 0; i < CataNum; i++)
			if (m_pDA->m_it->m_sCatalog == g_BookCata[i].GetBuffer())
				index = i;
		m_cbCatalog.SetCurSel(index);
	}
	UpdateData(FALSE);
	m_spinBNum.SetBuddy(GetDlgItem(IDC_EDIT_BNO));
	m_spinBNum.SetRange(1, 100);
	m_spinBNum.SetBuddy(GetDlgItem(IDC_EDIT_NUM));
	m_spinBNum.SetRange(1, 1000);
	m_spinYear.SetBuddy(GetDlgItem(IDC_EDIT_PYEAR));
	m_spinYear.SetRange(1950, 2050);
	m_spinMonth.SetBuddy(GetDlgItem(IDC_EDIT_PMONTH));
	m_spinMonth.SetRange(1, 12);
	GetDlgItem(IDC_EDIT_ISBN)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgFind::OnBnClickedFind()
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


void CDlgFind::OnBnClickedPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	CBook book = CBook();
	int index = 0;
	m_pDA->GetPrevBook(book);
	m_pDA->FillWithBook(book, m_csName, m_csISBN, m_csPublisher,
		m_nStock, m_nPYear, m_nPMonth, m_csCatalog, m_dtBuy, m_nBNo, m_csBorrow);
	UpdateData(FALSE);

	for (int i = 0; i < CataNum; i++)
		if (m_pDA->m_it->m_sCatalog == g_BookCata[i].GetBuffer())
			index = i;
	m_cbCatalog.SetCurSel(index);
}


void CDlgFind::OnBnClickedNext()
{
	// TODO: 在此添加控件通知处理程序代码
	CBook book = CBook();
	int index = 0;
	m_pDA->GetNextBook(book);
	m_pDA->FillWithBook(book, m_csName, m_csISBN, m_csPublisher,
		m_nStock, m_nPYear, m_nPMonth, m_csCatalog, m_dtBuy, m_nBNo, m_csBorrow);
	UpdateData(FALSE);

	for (int i = 0; i < CataNum; i++)
		if (m_pDA->m_it->m_sCatalog == g_BookCata[i].GetBuffer())
			index = i;
	m_cbCatalog.SetCurSel(index);
}


void CDlgFind::OnBnClickedUpdateinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CBook book = CBook();
	int index = 0;
	UpdateData(TRUE);
	for (int i = 0; i < CataNum; i++)
	{
		if (m_cbCatalog.GetCurSel() == i)
		{
			index = i;
			break;
		}
	}
	m_cbCatalog.SetCurSel(index);

	m_pDA->UpdateBookInfo(m_csName.GetBuffer(), m_csISBN.GetBuffer(), m_csPublisher.GetBuffer(),
		m_nStock, m_nPYear, m_nPMonth, g_BookCata[m_cbCatalog.GetCurSel()].GetBuffer());
	AfxMessageBox(_T("书籍信息更改成功！"));
	m_pDA->Save();
}


void CDlgFind::OnBnClickedUpdatebook()
{
	// TODO: 在此添加控件通知处理程序代码
	CBook book = CBook();
	int index = 0;
	UpdateData(TRUE);

	m_pDA->UpdateBook(m_csISBN.GetBuffer(), m_dtBuy.GetYear(), m_dtBuy.GetMonth(),
		m_dtBuy.GetDay(), m_nBNo, m_csBorrow.GetBuffer());

	m_pDA->Save();
}
