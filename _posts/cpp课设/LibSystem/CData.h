#pragma once
#include "CBook.h"
#include "CUser.h"
class CData
{
private:
	CData();
	~CData();
public:
	static CData* CreateInstance();
	static void DeleteInstance();
	void AddBook(CBook& book);
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
	void Save(CString csFullPath);
	void Load(CString csFullPath);

	inline int GetNumOfBook() { return m_listBook.size(); }
public:
	static int m_staID;
	static CData* m_sInstance;
	list<CBook> m_listBook;
};

