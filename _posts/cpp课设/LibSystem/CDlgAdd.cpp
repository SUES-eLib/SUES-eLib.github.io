// CDlgAdd.cpp: 实现文件
//

#include "pch.h"
#include "globe.h"
#include "CBook.h"
#include "CData.h"
#include "CDataAdapter.h"
#include "LibSystem.h"
#include "afxdialogex.h"
#include "CDlgAdd.h"


// CDlgAdd 对话框

IMPLEMENT_DYNAMIC(CDlgAdd, CDialogEx)

CDlgAdd::CDlgAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, m_csName(_T(""))
	, m_csISBN(_T(""))
	, m_dtBuy(COleDateTime::GetCurrentTime())
	, m_cbCatalog()
	, m_csPublisher(_T(""))
	, m_nPMonth(0)
	, m_nPYear(0)
	, m_nBNum(0)
	, m_pDA(NULL)
	, m_nStock(0)
{

}

CDlgAdd::~CDlgAdd()
{
	m_pDA = NULL;
}

void CDlgAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDX_Text(pDX, IDC_EDIT_ISBN, m_csISBN);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BUY, m_dtBuy);
	DDX_Control(pDX, IDC_COMBO_CATA, m_cbCatalog);
	DDX_Text(pDX, IDC_EDIT_PMONTH, m_nPMonth);
	DDX_Text(pDX, IDC_EDIT_PUB, m_csPublisher);
	DDX_Text(pDX, IDC_EDIT_PYEAR, m_nPYear);
	DDX_Control(pDX, IDC_SPIN_MONTH, m_spinMonth);
	DDX_Control(pDX, IDC_SPIN_YEAR, m_spinYear);
	DDX_Text(pDX, IDC_EDIT_NUM, m_nBNum);
	DDX_Control(pDX, IDC_SPIN_NUM, m_spinBNum);
}


BEGIN_MESSAGE_MAP(CDlgAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgAdd::OnBnClickedOk)
	ON_BN_CLICKED(IDABORT, &CDlgAdd::OnBnClickedAbort)
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
	m_nBNum = 1;
	m_nPYear = 2023;
	m_nPMonth = 1;
	m_csBorrow = _T("未借出");
	for (int i = 0; i < CataNum; i++)
		m_cbCatalog.AddString(g_BookCata[i]);
	m_cbCatalog.SetCurSel(0);
	UpdateData(FALSE);
	m_spinBNum.SetBuddy(GetDlgItem(IDC_EDIT_NUM));
	m_spinBNum.SetRange(1, 1000);
	m_spinYear.SetBuddy(GetDlgItem(IDC_EDIT_PYEAR));
	m_spinYear.SetRange(1950, 2050);
	m_spinMonth.SetBuddy(GetDlgItem(IDC_EDIT_PMONTH));
	m_spinMonth.SetRange(1, 12);
	GetDlgItem(IDC_EDIT_NAME)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString csCatalog;
	CBook book = CBook();

	int nNextNo = 0;
	m_pDA->FindBNumByISBN(m_csISBN.GetBuffer(), book);
	if (book.m_nBNo > 0)
	{
		nNextNo = m_pDA->m_it->m_nBNo;
		m_nStock = m_pDA->m_it->m_nStock + m_nBNum;
	}
	else
	{
		m_nStock = m_nBNum;
	}
	
	csCatalog = g_BookCata[m_cbCatalog.GetCurSel()];
	for (int i = nNextNo; i < m_nBNum + nNextNo; i++)
	{
		m_nBNo = i + 1;
		m_pDA->AddBook(m_csName.GetBuffer(), m_csISBN.GetBuffer(), m_csPublisher.GetBuffer(),
			m_nStock, m_nPYear, m_nPMonth, csCatalog.GetBuffer(),
			m_dtBuy.GetYear(), m_dtBuy.GetMonth(), m_dtBuy.GetDay(), m_nBNo, m_csBorrow.GetBuffer());
	}
	m_pDA->UpdateBookInfo(m_csName.GetBuffer(), m_csISBN.GetBuffer(), m_csPublisher.GetBuffer(),
			m_nStock, m_nPYear, m_nPMonth, g_BookCata[m_cbCatalog.GetCurSel()].GetBuffer());
	m_pDA->Save();

	AfxMessageBox(_T("添加成功！"));
	CDialogEx::OnOK();
}


void CDlgAdd::OnBnClickedAbort()
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
