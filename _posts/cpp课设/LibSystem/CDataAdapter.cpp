#include "pch.h"
#include "CDataAdapter.h"

CDataAdapter::CDataAdapter()
{
	m_pData = CData::CreateInstance();
}
CDataAdapter::~CDataAdapter()
{
	if (m_pData)
		CData::DeleteInstance();
	m_pData = NULL;
}

void CDataAdapter::AddBook(string sName, string sISBN, string sPublisher, int nStock,
	int nPYear, int nPMonth, string sCatalog,
	int nbYear, int nbMonth, int nbDay, int nBNo, string sBorrow)
{
	m_pData->AddBook(sName, sISBN, sPublisher, nStock,
		nPYear, nPMonth, sCatalog, nbYear, nbMonth, nbDay, nBNo, sBorrow);
}

void CDataAdapter::DeleBookByNo(string sISBN, int nBNo)
{
	m_pData->DeleBookByNo(sISBN, nBNo);
	AfxMessageBox(_T("书本删除成功！"));
}

void CDataAdapter::DeleBookByISBN(string sISBN)
{
	m_pData->DeleBookByISBN(sISBN);
	AfxMessageBox(_T("书籍删除成功！"));
}

void CDataAdapter::UpdateBookInfo(string sName, string sISBN, string sPublisher,
	int nStock, int nPYear, int nPMonth, string sCatalog)
{
	m_pData->UpdateBookInfo(sName, sISBN, sPublisher,nStock, nPYear, nPMonth, sCatalog);
}

void CDataAdapter::UpdateBook(string sISBN,	int nbYear, int nbMonth, int nbDay,
	int nBNo, string sBorrow)
{
	m_pData->UpdateBook(sISBN, nbYear, nbMonth, nbDay, nBNo, sBorrow);
	AfxMessageBox(_T("书本信息更改成功！"));
}

void CDataAdapter::ReturnBook(string sISBN,	int nBNo, string sBorrow)
{
	m_pData->ReturnBook(sISBN, nBNo, sBorrow);
	AfxMessageBox(_T("借阅状态更新成功！"));
}

void CDataAdapter::Save()
{
	m_pData->Save(_T(".\\data.txt"));
}

void CDataAdapter::Load()
{
	m_pData->Load(_T(".\\data.txt"));
}

bool CDataAdapter::GetFirstBook(CBook& book)
{
	list<CBook>* pList = GetListOfBook();
	if (pList->size() == 0)
		return false;

	m_it = pList->begin();
	book = *m_it;
	return true;
}

bool CDataAdapter::GetPrevBook(CBook& book)
{
	list<CBook>* pList = GetListOfBook();
	bool bRes = false;

	if (pList->size() != 0)
	{
		if (m_it != pList->begin())
			m_it--;

		book = *m_it;
		bRes = true;
	}
	return bRes;
}

bool CDataAdapter::GetNextBook(CBook& book)
{
	list<CBook>* pList = GetListOfBook();
	bool bRes = false;
	if (pList->size() != 0)
	{
		m_it++;
		if (m_it == pList->end())
			m_it--;
		book= *m_it;
		bRes = true;
	}
	return bRes;
}

bool CDataAdapter::GetLastBook(CBook& book)
{
	list<CBook>* pList = GetListOfBook();
	if (pList->size() == 0)
		return false;

	m_it = pList->end();
	m_it--;
	book = *m_it;
	return true;
}

bool CDataAdapter::FindBookByNo(string sISBN, int nBNo, CBook& book)
{
	list<CBook>* pList = GetListOfBook();
	if (pList->size() == 0)
		return false;

	bool bFound = false;
	for (list<CBook>::iterator it = pList->begin(); it != pList->end(); it++)
	{
		if (it->m_sISBN == sISBN && it->m_nBNo == nBNo)
		{
			m_it = it;
			book = *it;
			bFound = true;
			break;
		}
	}
	if (bFound == false)
	{
		AfxMessageBox(_T("看看你的书籍信息对不对呢"));
		m_it = pList->begin();
		book = *m_it;
	}
	return bFound;
}

bool CDataAdapter::FindBNumByISBN(string sISBN, CBook& book)
{
	list<CBook>* pList = GetListOfBook();
	if (pList->size() == 0)
		return false;

	bool bFound = false;
	int nNextNo = 1;
	for (list<CBook>::iterator it = pList->begin(); it != pList->end(); it++)
	{
		if (it->m_sISBN == sISBN)
		{
			if (it->m_nBNo >= nNextNo)
			{
				nNextNo = it->m_nBNo;
				m_it = it;
				book = *it;
				bFound = true;
			}
		}
	}
	return bFound;
}

void CDataAdapter::FillWithBook(CBook& book, CString& sName, CString& sISBN, CString& sPublisher,
	int& nStock, int& nPYear, int& nPMonth, CString& sCatalog,
	COleDateTime& dtBuy, int& nBNo, CString& sBorrow)
{
	sName = book.m_sName.c_str();
	sISBN = book.m_sISBN.c_str();
	sPublisher = book.m_sPublisher.c_str();
	nStock = book.m_nStock;
	nPYear = book.m_nPYear;
	nPMonth = book.m_nPMonth;
	dtBuy = COleDateTime(book.m_nbYear, book.m_nbMonth, book.m_nbDay, 0, 0, 0);
	nBNo = book.m_nBNo;
	sBorrow = book.m_csBorrow.c_str();
}

int CDataAdapter::ReturnNum(string sISBN)
{
	list<CBook>* pList = GetListOfBook();
	if (pList->size() == 0)
		return 0;
	int nReturn = 0;
	for (list<CBook>::iterator it = pList->begin(); it != pList->end(); it++)
	{
		if (it->m_sISBN == sISBN && it->m_csBorrow == _T("未借出"))
		{
			nReturn++;
		}
	}
	return nReturn;
}