#pragma once

class CStudent
{
public:
	CStudent();
	CStudent(string sNo,string sName,BOOL bGender,
		     int nYear, int nMonth, int nDay,
		     int nGrade,string sMajor);
	~CStudent();

	void SetStudent(string sNo, string sName, BOOL bGender,
		            int nYear, int nMonth, int nDay,
		            int nGrade, string sMajor);

	void Save(ofstream &out);
	void Load(ifstream& in);
public:
	string m_sNo;
	string m_sName;
	BOOL m_bGender;
	int m_nYear;
	int m_nMonth;
	int m_nDay;
	int m_nGrade;
	string m_sMajor;
};

