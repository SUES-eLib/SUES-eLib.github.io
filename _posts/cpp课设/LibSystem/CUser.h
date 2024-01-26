#pragma once
class CUser
{
public:
	CUser();
	CUser(string sUName, string sUPwd, int nAuthority);
	~CUser();
	void SetUser(string sUName, string sUPwd, int nAuthority);

	void Save(ofstream& out);
	void Load(ifstream& in);
public:
	string m_sUName;
	string m_sPwd;
	int m_nAuthority;
};
