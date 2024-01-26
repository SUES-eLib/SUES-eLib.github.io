#include "pch.h"
#include "CStudent.h"

CStudent::CStudent()
{

}

CStudent::CStudent(string sNo, string sName, BOOL bGender,
	               int nYear, int nMonth, int nDay,
	               int nGrade, string sMajor)
{
	m_sNo = sNo;
	m_sName = sName;
	m_bGender = bGender;
	m_nYear = nYear;
	m_nMonth = nMonth;
	m_nDay = nDay;
	m_nGrade =nGrade;
	m_sMajor = sMajor;
}

CStudent::~CStudent()
{

}

void CStudent::SetStudent(string sNo, string sName, BOOL bGender,
	int nYear, int nMonth, int nDay,
	int nGrade, string sMajor)
{
	m_sNo = sNo;
	m_sName = sName;
	m_bGender = bGender;
	m_nYear = nYear;
	m_nMonth = nMonth;
	m_nDay = nDay;
	m_nGrade = nGrade;
	m_sMajor = sMajor;
}

void CStudent::Save(ofstream& out)
{
	out << m_sNo << _T("\t");
	out << m_sName << _T("\t");
	out << m_bGender << _T("\t");
	out << m_nYear << _T("\t");
	out << m_nMonth << _T("\t");
	out << m_nDay << _T("\t");
	out << m_nGrade << _T("\t");
	out << m_sMajor << _T("\n");
}

void CStudent::Load(ifstream& in)
{
	in >> m_sNo;
	in >> m_sName;
	in >> m_bGender;
	in >> m_nYear >> m_nMonth >> m_nDay;
	in >> m_nGrade;
	in >> m_sMajor;
}