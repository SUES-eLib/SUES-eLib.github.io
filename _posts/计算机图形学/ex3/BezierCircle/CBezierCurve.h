#pragma once
#include"CP2.h"
class CBezierCurve
{
public:
	CBezierCurve();
	virtual ~CBezierCurve();
	void ReadPoint(CP2* P);
	void DrawCurve(CDC* pDC);
	void DrawPolygon(CDC* pDC);
private:
	CP2 P[4];
};
