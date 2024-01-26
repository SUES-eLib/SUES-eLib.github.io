#pragma once
#include"CBezierCurve.h"
class CCircle
{
public:
	CCircle(void);
	virtual ~CCircle(void);
	void ReadPoint(void);
	CP2* GetVertexArrayName(void);
	void Draw(CDC* pDC);
private:
	CP2 P[12];
	CBezierCurve bezier[4];
};