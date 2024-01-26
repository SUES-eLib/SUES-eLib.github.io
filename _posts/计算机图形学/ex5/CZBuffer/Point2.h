#pragma once
#include"CRGB.h"
#include"Vector3.h"

class CPoint2
{
public:
	CPoint2(void);
	CPoint2(int x, int y);
	CPoint2(int x, int y, CRGB c);
	CPoint2(int x, int y, CVector3 n);
	virtual ~CPoint2(void);
	friend CPoint2 operator + (const CPoint2 &pt0, const CPoint2 &pt1);
	friend CPoint2 operator - (const CPoint2 &pt0, const CPoint2 &pt1);
	friend CPoint2 operator * (int scalar, const CPoint2 &pt);
public:
	int x, y;
	CRGB c;
	CVector3 n;
};

