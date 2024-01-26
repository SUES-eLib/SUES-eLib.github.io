#pragma once
#include "CData.h"
class CDataAdapter
{
public:
	CDataAdapter();
	~CDataAdapter();
	void AddStudent(string sNo, string sName, BOOL bGender,
		int nYear, int nMonth, int nDay,
		int nGrade, string sMajor);
	
	bool FindStudentByNo(string& sNo, string& sName, BOOL& bGender,
		int& nYear, int& nMonth, int& nDay,
		int& nGrade, string& sMajor);
	void DeleStudentByNo(string sNo);
	void UpdateStudent(string sNo, string sName, BOOL bGender,
		int nYear, int nMonth, int nDay,
		int nGrade, string sMajor);
	
	void Save();
	void Load();

	inline int GetNumOfStudent() { return m_pData->GetNumOfStudent(); }
	inline list<CStudent>* GetListOfStudent() { return &m_pData->m_listStudent; }
	bool GetFirstStudent(CStudent& stu);
	bool GetNextStudent(CStudent& stu);
	bool GetPrevStudent(CStudent& stu);
	bool GetLastStudent(CStudent& stu);
	bool FindStudentByNo(string sNo, CStudent& stu);

	void FillWithStudent(CStudent& stu, CString& csNo, CString& sName, BOOL& bGender,
		COleDateTime& tmBirth, int& nGrade, CString& csMajor);
public:
	CData* m_pData;
	list<CStudent>::iterator m_it;
};

