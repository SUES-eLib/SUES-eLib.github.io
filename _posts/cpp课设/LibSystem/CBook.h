#pragma once

class CBook
{
public:
	CBook();
	CBook(string sName, string sISBN, string sPublisher, int nStock,
		int nPYear, int nPMonth, string sCatalog,
		int nbYear, int nbMonth, int nbDay, int nBNo, string sBorrow);
	~CBook();
	void SetBook(string sName, string sISBN, string sPublisher, int nStock,
		int nPYear, int nPMonth, string sCatalog,
		int nbYear, int nbMonth, int nbDay, int nBNo, string sBorrow);

	void Save(ofstream &out);
	void Load(ifstream& in);
public:
	string m_sName;
	string m_sISBN;
	string m_sPublisher;
	int m_nBNum;
	int m_nPYear;
	int m_nPMonth;
	string m_sCatalog;
	COleDateTime m_dtBuy;
	int m_nbYear;
	int m_nbMonth;
	int m_nbDay;
	int m_nBNo;
	string m_csBorrow;
	int m_nStock;
};
