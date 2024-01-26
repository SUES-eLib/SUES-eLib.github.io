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

void CDataAdapter::AddStudent(string sNo, string sName, BOOL bGender,
	int nYear, int nMonth, int nDay,
	int nGrade, string sMajor)
{
	m_pData->AddStudent(sNo, sName, bGender, nYear, nMonth, nDay,
		nGrade, sMajor);

}

bool CDataAdapter::FindStudentByNo(string& sNo, string& sName, BOOL& bGender,
	int& nYear, int& nMonth, int& nDay,
	int& nGrade, string& sMajor)
{
	return m_pData->FindStudentByNo(sNo, sName, bGender, nYear, nMonth, nDay,
		nGrade, sMajor);
}

void CDataAdapter::DeleStudentByNo(string sNo)
{
	m_pData->DeleStudentByNo(sNo);
}

void CDataAdapter::UpdateStudent(string sNo, string sName, BOOL bGender,
	int nYear, int nMonth, int nDay,
	int nGrade, string sMajor)
{
	m_pData->UpdateStudent(sNo, sName, bGender, nYear, nMonth, nDay,
		nGrade, sMajor);
}

void CDataAdapter::Save()
{
	m_pData->Save(_T("D:\\data.txt"));
}

void CDataAdapter::Load()
{
	m_pData->Load(_T("D:\\data.txt"));
}

bool CDataAdapter::GetFirstStudent(CStudent& stu)
{
	list<CStudent>* pList = GetListOfStudent();
	if (pList->size() == 0)
		return false;
	
	m_it = pList->begin();
	stu = *m_it;
	return true;
}
bool CDataAdapter::GetNextStudent(CStudent& stu)
{
	list<CStudent>* pList = GetListOfStudent();
	bool bRes = false;
	if (pList->size() != 0)
	{
		m_it++;
		if (m_it == pList->end())
			m_it--;
		stu = *m_it;
		bRes = true;
	}
	return bRes;
}

bool CDataAdapter::GetPrevStudent(CStudent& stu)
{
	list<CStudent>* pList = GetListOfStudent();
	bool bRes = false;
	
	if (pList->size() != 0)
	{
		if (m_it != pList->begin())
			m_it--;

		stu = *m_it;
		bRes = true;
	}
	return bRes;
}
bool CDataAdapter::GetLastStudent(CStudent& stu)
{
	list<CStudent>* pList = GetListOfStudent();
	if (pList->size() == 0)
		return false;
	
	m_it = pList->end();
	m_it--;
	stu = *m_it;
	return true;
}

bool CDataAdapter::FindStudentByNo(string sNo, CStudent& stu)
{
	list<CStudent>* pList = GetListOfStudent();
	if (pList->size() == 0)
		return false;

	bool bFound = false;
	for (list<CStudent>::iterator it = pList->begin(); it != pList->end(); it++)
	{
		if (it->m_sNo == sNo)
		{
			m_it = it;
			stu = *it;
			bFound = true;
			break;
		}
	}
	if (bFound == false)
		stu = *m_it;
	return bFound;
}


void CDataAdapter::FillWithStudent(CStudent& stu, CString& csNo, CString& csName, 
	BOOL& bGender, COleDateTime& tmBirth, int& nGrade, CString& csMajor)
{
	csNo = stu.m_sNo.c_str();
	csName = stu.m_sName.c_str();
	bGender = stu.m_bGender;
	tmBirth = COleDateTime(stu.m_nYear, stu.m_nMonth, stu.m_nDay, 0, 0, 0);
	nGrade = stu.m_nGrade;
	csMajor = stu.m_sMajor.c_str();
}