#pragma once
#include "CStudent.h"
class CData
{
private:
	CData();
	~CData();
public:
	static CData* CreateInstance();
	static void DeleteInstance();
	void AddStudent(CStudent& stu);
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
	void Save(CString csFullPath);
	void Load(CString csFullPath);
	inline int GetNumOfStudent() { return m_listStudent.size(); }
public:
	static int m_sID;
	static CData* m_sInstance;
	list<CStudent> m_listStudent;
};

