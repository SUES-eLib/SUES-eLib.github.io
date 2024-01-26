#pragma once
class CHistory
{
public:
	CHistory();
	CHistory(string sISBN, int nNo, string sBorrow,
		int nLYear, int nLMonth, int nLDay);
	~CHistory();
	void SetHistory(string sISBN, int nNo, string sBorrow,
		int nLYear, int nLMonth, int nLDay);

	void Save(ofstream& out);
	void Load(ifstream& in);
public:
	string m_sISBN;
	int m_nNo;
	string m_sBorrow;
	int m_nLYear;
	int m_nLMonth;
	int m_nLDay;
};

