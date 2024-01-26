#include "pch.h"
#include "CHistory.h"

CHistory::CHistory()
{

}

CHistory::CHistory(string sISBN, int nNo, string sBorrow,
	int nLYear, int nLMonth, int nLDay)
{
	m_sISBN = sISBN;
	m_nNo= nNo;
	m_sBorrow = sBorrow;
	m_nLYear = nLYear;
	m_nLMonth = nLMonth;
	m_nLDay = nLDay;
}

CHistory::~CHistory()
{

}

void CHistory::SetHistory(string sISBN, int nNo, string sBorrow,
	int nLYear, int nLMonth, int nLDay)
{
	m_sISBN = sISBN;
	m_nNo = nNo;
	m_sBorrow = sBorrow;
	m_nLYear = nLYear;
	m_nLMonth = nLMonth;
	m_nLDay = nLDay;
}

void CHistory::Save(ofstream& out)
{
	out << m_sISBN << _T("\t");
	out << m_nNo << _T("\t");
	out << m_sBorrow << _T("\t");
	out << m_nLYear << _T("\t");
	out << m_nLMonth << _T("\t");
	out << m_nLDay << _T("\n");
}

void CHistory::Load(ifstream& in)
{
	in >> m_sISBN;
	in >> m_nNo;
	in >> m_sBorrow;
	in >> m_nLYear >> m_nLMonth >> m_nLDay;
}
