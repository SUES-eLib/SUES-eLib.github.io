#include "pch.h"
#include "CStudent.h"
#include "CData.h"

int CData::m_sID = 0;
CData* CData::m_sInstance = NULL;
CData::CData()
{
	if (m_sID == 0)
		m_sID++;
}

CData::~CData()
{

}

CData* CData::CreateInstance()
{
	if (m_sID == 0)
		m_sInstance = new CData();
	return m_sInstance;
}

void CData::DeleteInstance()
{
	if (m_sInstance != NULL)
	{
		delete m_sInstance;
		m_sID = 0;
	}
	m_sInstance = NULL;
}

void CData::Save(CString csFullPath)
{
	ofstream out(csFullPath, ios::out);
	if (out.is_open())
	{
		out << m_listStudent.size() << endl;
		for (list<CStudent>::iterator it = m_listStudent.begin(); it != m_listStudent.end(); it++)
			it->Save(out);
		out.close();
	}
}

void CData::Load(CString csFullPath)
{
	m_listStudent.clear();
	ifstream in(csFullPath, ios::in);
	if (in.is_open())
	{
		int num;
		in >> num;
		for (int i = 0; i < num; i++)
		{
			CStudent stu;
			stu.Load(in);
			m_listStudent.push_back(stu);
		}
		in.close();
	}
}

void CData::AddStudent(CStudent& stu)
{
	m_listStudent.push_back(stu);
}

void CData::AddStudent(string sNo, string sName, BOOL bGender,
	int nYear, int nMonth, int nDay,
	int nGrade, string sMajor)
{
	CStudent stu;
	stu.SetStudent(sNo, sName, bGender, nYear, nMonth, nDay, nGrade, sMajor);
	m_listStudent.push_back(stu);
}

bool SortByNoAscent(CStudent &stu1, CStudent&stu2)
{ 
	return (stu1.m_sNo < stu2.m_sNo); 
}

bool CData::FindStudentByNo(string& sNo, string& sName, BOOL& bGender,
	int& nYear, int& nMonth, int& nDay,
	int& nGrade, string& sMajor)
{
	bool bFound = false;
	for (list<CStudent>::iterator it = m_listStudent.begin(); it != m_listStudent.end(); it++)
	{
		if (it->m_sNo == sNo)
		{
			sName = it->m_sName;
			bGender = it->m_bGender;
			nYear = it->m_nYear;
			nMonth = it->m_nMonth;
			nDay = it->m_nDay;
			nGrade = it->m_nGrade;
			sMajor = it->m_sMajor;

			bFound = true;
			break;
		}
	}
	return bFound;
}
void CData::DeleStudentByNo(string sNo)
{
	for (list<CStudent>::iterator it = m_listStudent.begin(); it != m_listStudent.end(); it++)
	{
		if (it->m_sNo == sNo)
		{
			m_listStudent.erase(it);
			break;
		}
	}
}
void CData::UpdateStudent(string sNo, string sName, BOOL bGender,
	int nYear, int nMonth, int nDay,
	int nGrade, string sMajor)
{
	for (list<CStudent>::iterator it = m_listStudent.begin(); it != m_listStudent.end(); it++)
	{
		if (it->m_sNo == sNo)
		{
			it->SetStudent(sNo, sName, bGender, nYear, nMonth, nDay, nGrade, sMajor);
			break;
		}
	}
}