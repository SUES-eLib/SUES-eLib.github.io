#pragma once
#include"CP3.h"
class CVector3
{
public:
	CVector3(void);
	virtual ~CVector3(void);
	CVector3(double x, double y, double z);	
	CVector3(const CP3& p);
	CVector3(const CP3& p0, const CP3& p1);	
	double Magnitude(void);	CVector3 Normalize(void);	
	friend CVector3 operator + (const CVector3& v0, const CVector3& v1);	
	friend CVector3 operator - (const CVector3& v0, const CVector3& v1);
	friend CVector3 operator * (const CVector3& v, double scalar);
	friend CVector3 operator * (double scalar, const CVector3& v);
	friend CVector3 operator / (const CVector3& v, double scalar);
	friend double DotProduct(const CVector3& v0, const CVector3& v1);	
	friend CVector3 CrossProduct(const CVector3& v0, const CVector3& v1);
private:
	double x, y, z;
};

