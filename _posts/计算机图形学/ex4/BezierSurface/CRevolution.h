#pragma once
#include "Patch.h"
#include"CBezierPatch.h"
class CRevolution
{
public:
	CRevolution(void) {};
	virtual ~CRevolution(void) {};
	void ReadCubicBezierControlPoint(CP3 P[4]);
	CP3* GetVertexArrayName(void);
	void DrawRevolutionSurface(CDC* pDC);
private:
	void ReadVertex(void);
	void ReadPatch(void);
private:
	CP3 P[4];
	CP3 V[48];
	CPatch S[4];
};