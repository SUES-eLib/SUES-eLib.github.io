#include "pch.h"
#include "CBook.h"

CBook::CBook()
{
	
}

CBook::CBook(string sName, string sISBN, string sPublisher, int nStock,
	int nPYear, int nPMonth, string sCatalog,
	int nbYear, int nbMonth, int nbDay, int nBNo, string sBorrow)
{
	m_sName = sName;
	m_sISBN = sISBN;
	m_sPublisher = sPublisher;
	m_nStock = nStock;
	m_nPYear = nPYear;
	m_nPMonth = nPMonth;
	m_sCatalog = sCatalog;
	m_nbYear = nbYear;
	m_nbMonth = nbMonth;
	m_nbDay = nbDay;
	m_nBNo = nBNo;
	m_csBorrow = sBorrow;
}

CBook::~CBook()
{

}

void CBook::SetBook(string sName, string sISBN, string sPublisher, int nStock,
	int nPYear, int nPMonth, string sCatalog,
	int nbYear, int nbMonth, int nbDay, int nBNo, string sBorrow)
{
	m_sName = sName;
	m_sISBN = sISBN;
	m_sPublisher = sPublisher;
	m_nStock = nStock;
	m_nPYear = nPYear;
	m_nPMonth = nPMonth;
	m_sCatalog = sCatalog;
	m_nbYear = nbYear;
	m_nbMonth = nbMonth;
	m_nbDay = nbDay;
	m_nBNo = nBNo;
	m_csBorrow = sBorrow;
}

void CBook::Save(ofstream& out)
{
	out << m_sName << _T("\t");
	out << m_sISBN << _T("\t");
	out << m_sPublisher << _T("\t");
	out << m_nStock << _T("\t");
	out << m_nPYear << _T("\t");
	out << m_nPMonth << _T("\t");
	out << m_sCatalog << _T("\t");
	out << m_nbYear << _T("\t");
	out << m_nbMonth << _T("\t");
	out << m_nbDay << _T("\t");
	out << m_nBNo << _T("\t");
	out << m_csBorrow << _T("\n");
}

void CBook::Load(ifstream& in)
{
	in >> m_sName;
	in >> m_sISBN;
	in >> m_sPublisher;
	in >> m_nStock;
	in >> m_nPYear;
	in >> m_nPMonth;
	in >> m_sCatalog;
	in >> m_nbYear >> m_nbMonth >> m_nbDay;
	in >> m_nBNo;
	in >> m_csBorrow;
}
