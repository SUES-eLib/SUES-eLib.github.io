#include "pch.h"
#include "CUser.h"

CUser::CUser()
{

}

CUser::CUser(string sUName, string sPwd, int nAuthority)
{
	m_sUName = sUName;
	m_sPwd = sPwd;
	m_nAuthority = nAuthority;
}

CUser::~CUser()
{

}

void CUser::SetUser(string sUName, string sPwd, int nAuthority)
{
	m_sUName = sUName;
	m_sPwd = sPwd;
	m_nAuthority = nAuthority;
}

void CUser::Save(ofstream& out)
{
	out << m_sUName << _T("\t");
	out << m_sPwd << _T("\t");
	out << m_nAuthority << _T("\n");
}

void CUser::Load(ifstream& in)
{
	in >> m_sUName;
	in >> m_sPwd;
	in >> m_nAuthority;
}
