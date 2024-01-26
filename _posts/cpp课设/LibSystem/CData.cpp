#include "pch.h"
#include "CBook.h"
#include "CData.h"

int CData::m_staID = 0;
CData* CData::m_sInstance = NULL;
CData::CData()
{
	if (m_staID == 0)
		m_staID++;
	m_listBook = list<CBook>();
}

CData::~CData()
{

}

CData* CData::CreateInstance()
{
	if (m_staID == 0)
		m_sInstance = new CData();
	return m_sInstance;
}

void CData::DeleteInstance()
{
	if (m_sInstance != NULL)
	{
		delete m_sInstance;
		m_staID = 0;
	}
	m_sInstance = NULL;
}

void CData::Save(CString csFullPath)
{
	ofstream out(csFullPath, ios::out);
	if (out.is_open())
	{
		out << m_listBook.size() << endl;
		for (list<CBook>::iterator it = m_listBook.begin(); it != m_listBook.end(); it++)
			it->Save(out);
		out.close();
	}
}

void CData::Load(CString csFullPath)
{
	m_listBook.clear();
	ifstream in(csFullPath, ios::in);
	if (in.is_open())
	{
		int num;
		in >> num;
		for (int i = 0; i < num; i++)
		{
			CBook book = CBook();
			book.Load(in);
			m_listBook.push_back(book);
		}
		in.close();
	}
}

void CData::AddBook(CBook& book)
{
	m_listBook.push_back(book);
}

void CData::AddBook(string sName, string sISBN, string sPublisher, int nStock,
	int nPYear, int nPMonth, string sCatalog,
	int nbYear, int nbMonth, int nbDay, int nBNo, string sBorrow)
{
	CBook Book = CBook();
	Book.SetBook(sName, sISBN, sPublisher, nStock, nPYear, nPMonth, sCatalog,
		nbYear, nbMonth, nbDay, nBNo, sBorrow);
	m_listBook.push_back(Book);
}

void CData::DeleBookByNo(string sISBN, int nBNo)
{
	bool bFound = false;
	for (list<CBook>::iterator it = m_listBook.begin(); it != m_listBook.end(); it++)
	{
		if (it->m_sISBN == sISBN && it->m_nBNo == nBNo)
		{
			m_listBook.erase(it);
			bFound = true;
			break;
		}
	}
	if (bFound == false)
	{
		AfxMessageBox(_T("看看你的书籍信息对不对呢"));
	}
}

void CData::DeleBookByISBN(string sISBN)
{
	bool bFound = false;
	for (list<CBook>::iterator it = m_listBook.begin(); it != m_listBook.end(); it++)
	{
		
		if (it->m_sISBN == sISBN)
		{
			m_listBook.erase(it);
			it = m_listBook.begin();
			bFound = true;
		}
	}
	list<CBook>::iterator it = m_listBook.begin();
	if (it->m_sISBN == sISBN)
	{
		m_listBook.erase(it);
		bFound = true;
	}
	if (bFound == false)
	{
		AfxMessageBox(_T("看看你的书籍信息对不对呢"));
	}
}

void CData::UpdateBookInfo(string sName, string sISBN, string sPublisher,
	int nStock, int nPYear, int nPMonth, string sCatalog)
{
	bool bFound = false;
	for (list<CBook>::iterator it = m_listBook.begin(); it != m_listBook.end(); it++)
	{
		if (it->m_sISBN == sISBN)
		{
			it->m_sName = sName;
			it->m_sPublisher = sPublisher;
			it->m_nPYear = nPYear;
			it->m_nPMonth = nPMonth;
			it->m_sCatalog = sCatalog;
			it->m_nStock = nStock;
			bFound = true;
		}
	}
	if (bFound == false)
	{
		AfxMessageBox(_T("看看你的书籍信息对不对呢"));
	}
}

void CData::UpdateBook(string sISBN, int nbYear, int nbMonth, int nbDay,
	int nBNo, string sBorrow)
{
	bool bFound = false;
	for (list<CBook>::iterator it = m_listBook.begin(); it != m_listBook.end(); it++)
	{

		if (it->m_sISBN == sISBN && it->m_nBNo == nBNo)
		{
			it->m_nbYear = nbYear;
			it->m_nbMonth = nbMonth;
			it->m_nbDay = nbDay;
			it->m_nBNo = nBNo;
			it->m_csBorrow = sBorrow;
			bFound = true;
		}
	}
	if (bFound == false)
	{
		AfxMessageBox(_T("看看你的书籍信息对不对呢"));
	}
}

void CData::ReturnBook(string sISBN, int nBNo, string sBorrow)
{
	bool bFound = false;
	for (list<CBook>::iterator it = m_listBook.begin(); it != m_listBook.end(); it++)
	{

		if (it->m_sISBN == sISBN && it->m_nBNo == nBNo)
		{
			it->m_nBNo = nBNo;
			it->m_csBorrow = sBorrow;
			bFound = true;
		}
	}
	if (bFound == false)
	{
		AfxMessageBox(_T("看看你的书籍信息对不对呢"));
	}
}