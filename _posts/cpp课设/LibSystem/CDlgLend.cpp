// CDlgLend.cpp: 实现文件
//

#include "pch.h"
#include "globe.h"
#include "CBook.h"
#include "CData.h"
#include "CDataAdapter.h"
#include "LibSystem.h"
#include "afxdialogex.h"
#include "CDlgLend.h"


// CDlgLend 对话框

IMPLEMENT_DYNAMIC(CDlgLend, CDialogEx)

CDlgLend::CDlgLend(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LEND, pParent)
	, m_nBNo(1)
	, m_csBorrow(_T(""))
	, m_csISBN(_T(""))
	, m_csName(_T(""))
	, m_csPublisher(_T(""))
	, m_nReturn(0)
{

}

CDlgLend::~CDlgLend()
{
}

void CDlgLend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CATA, m_cbCatalog);
	DDX_Text(pDX, IDC_EDIT_BNO, m_nBNo);
	DDX_Text(pDX, IDC_EDIT_BORROW, m_csBorrow);
	DDX_Text(pDX, IDC_EDIT_ISBN, m_csISBN);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDX_Text(pDX, IDC_EDIT_PUB, m_csPublisher);
	DDX_Text(pDX, IDC_EDIT_RETRUN, m_nReturn);
	DDX_Control(pDX, IDC_SPIN_NUM, m_spinBNum);
}


BEGIN_MESSAGE_MAP(CDlgLend, CDialogEx)
	ON_BN_CLICKED(ID_ABORT, &CDlgLend::OnBnClickedAbort)
	ON_BN_CLICKED(IDC_LEND, &CDlgLend::OnBnClickedLend)
	ON_BN_CLICKED(IDC_RETURN, &CDlgLend::OnBnClickedReturn)
END_MESSAGE_MAP()


// CDlgLend 消息处理程序

void CDlgLend::SetDA(CDataAdapter* pDA)
{
	m_pDA = pDA;
}

BOOL CDlgLend::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_nPYear = 2023;
	m_nPMonth = 1;
	m_csBorrow = _T("");
	for (int i = 0; i < CataNum; i++)
		m_cbCatalog.AddString(g_BookCata[i]);
	m_cbCatalog.SetCurSel(0);
	UpdateData(FALSE);
	m_spinBNum.SetBuddy(GetDlgItem(IDC_EDIT_BNO));
	m_spinBNum.SetRange(1, 100);
	LoadHistory(_T(".//history.txt"));
	m_dtLTime = COleDateTime::GetCurrentTime();
	pList = &m_listHistory;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgLend::OnBnClickedAbort()
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
	m_nReturn = m_pDA->ReturnNum(sISBN);
	UpdateData(FALSE);

	for (int i = 0; i < CataNum; i++)
		if (m_pDA->m_it->m_sCatalog == g_BookCata[i].GetBuffer())
			index = i;
	m_cbCatalog.SetCurSel(index);
}


void CDlgLend::OnBnClickedLend()
{
	// TODO: 在此添加控件通知处理程序代码
	CBook book = CBook();
	int index = 0;
	UpdateData(TRUE);

	m_pDA->ReturnBook(m_csISBN.GetBuffer(), m_nBNo, m_csBorrow.GetBuffer());
	m_pDA->Save();
	m_nReturn = m_pDA->ReturnNum(m_csISBN.GetBuffer());
	AddHistory(m_csISBN.GetBuffer(), m_nBNo, m_csBorrow.GetBuffer(),
		m_dtLTime.GetYear(), m_dtLTime.GetMonth(), m_dtLTime.GetDay());
	SaveHistory(_T(".//history.txt"));
	UpdateData(FALSE);
}


void CDlgLend::OnBnClickedReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	CBook book = CBook();
	int index = 0;
	m_csBorrow = _T("未借出");

	m_pDA->ReturnBook(m_csISBN.GetBuffer(), m_nBNo, m_csBorrow.GetBuffer());
	m_pDA->Save();
	m_nReturn = m_pDA->ReturnNum(m_csISBN.GetBuffer());
	AddHistory(m_csISBN.GetBuffer(), m_nBNo, _T("归还"),
		m_dtLTime.GetYear(), m_dtLTime.GetMonth(), m_dtLTime.GetDay());
	SaveHistory(_T(".//history.txt"));
	UpdateData(FALSE);
}

void CDlgLend::AddHistory(string sISBN, int nNo, string sBorrow,
	int nLYear, int nLMonth, int nLDay)
{
	CHistory hist = CHistory();
	hist.SetHistory(sISBN, nNo, sBorrow, nLYear, nLMonth, nLDay);
	m_listHistory.push_back(hist);
}

void CDlgLend::LoadHistory(CString csFullPath)
{
	m_listHistory.clear();
	ifstream in(csFullPath, ios::in);
	if (in.is_open())
	{
		int num;
		in >> num;
		for (int i = 0; i < num; i++)
		{
			CHistory hist = CHistory();
			hist.Load(in);
			m_listHistory.push_back(hist);
		}
		in.close();
	}
}

void CDlgLend::SaveHistory(CString csFullPath)
{
	ofstream out(csFullPath, ios::out);
	if (out.is_open())
	{
		out << m_listHistory.size() << endl;
		for (list<CHistory>::iterator it = m_listHistory.begin(); it != m_listHistory.end(); it++)
			it->Save(out);
		out.close();
	}
}