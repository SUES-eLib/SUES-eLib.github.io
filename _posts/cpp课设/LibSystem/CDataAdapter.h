#pragma once
#include "CData.h"
class CDataAdapter
{
public:
	CDataAdapter();
	~CDataAdapter();
	void AddBook(string sName, string sISBN, string sPublisher, int nStock,
		int nPYear, int nPMonth, string sCatalog,
		int nbYear, int nbMonth, int nbDay, int nBNo, string sBorrow);
	void DeleBookByNo(string sISBN, int nBNo);
	void DeleBookByISBN(string sISBN);
	void UpdateBookInfo(string sName, string sISBN, string sPublisher,
		int nStock, int nPYear, int nPMonth, string sCatalog);
	void UpdateBook(string sISBN, int nbYear, int nbMonth, int nbDay,
		int nBNo, string sBorrow);
	void ReturnBook(string sISBN, int nBNo, string sBorrow);

	void Save();
	void Load();

	inline int GetNumOfBook() { return m_pData->GetNumOfBook(); }
	inline list<CBook>* GetListOfBook() { return &m_pData->m_listBook; }
	bool GetFirstBook(CBook& book);
	bool GetNextBook(CBook& book);
	bool GetPrevBook(CBook& book);
	bool GetLastBook(CBook& book);
	bool FindBookByNo(string sISBN, int nBNo, CBook& book);
	bool FindBNumByISBN(string sISBN, CBook& book);
	void FillWithBook(CBook& book,CString& sName, CString& sISBN, CString& sPublisher,
		int& nStock, int& nPYear, int& nPMonth, CString& sCatalog,
		COleDateTime& dtBuy, int& nBNo, CString& sBorrow);
	int ReturnNum(string sISBN);
public:
	CData* m_pData;
	list<CBook>::iterator m_it;
};

