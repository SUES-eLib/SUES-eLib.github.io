#include "pch.h"
#include "CCircle.h"
CCircle::CCircle(void)
{
}
CCircle::~CCircle(void)
{
}
CP2* CCircle::GetVertexArrayName(void)
{
	return P;
}
void CCircle::ReadPoint(void)
{
	double m = 0.5523;
	P[0].x = 1, P[0].y = 0;
	P[1].x = 1, P[1].y = m;
	P[2].x = m, P[2].y = 1;
	P[3].x = 0, P[3].y = 1;
	P[4].x = -m, P[4].y = 1;
	P[5].x = -1, P[5].y = m;
	P[6].x = -1, P[6].y = 0;
	P[7].x = -1, P[7].y = -m;
	P[8].x = -m, P[8].y = -1;
	P[9].x = 0, P[9].y = -1;
	P[10].x = m, P[10].y = -1;
	P[11].x = 1, P[11].y = -m;
}
void CCircle::Draw(CDC* pDC)
{
	CP2 CtrP[4];
	//第一段
	CtrP[0] = P[0], CtrP[1] = P[1], CtrP[2] = P[2], CtrP[3] = P[3];
	bezier[0].ReadPoint(CtrP);
	bezier[0].DrawCurve(pDC);
	bezier[0].DrawPolygon(pDC);
	//第二段
	CtrP[0] = P[3], CtrP[1] = P[4], CtrP[2] = P[5], CtrP[3] = P[6];
	bezier[1].ReadPoint(CtrP);
	bezier[1].DrawCurve(pDC);
	bezier[1].DrawPolygon(pDC);
	//第三段
	CtrP[0] = P[6], CtrP[1] = P[7], CtrP[2] = P[8], CtrP[3] = P[9];
	bezier[2].ReadPoint(CtrP);
	bezier[2].DrawCurve(pDC);
	bezier[2].DrawPolygon(pDC);
	//第四段
	CtrP[0] = P[9], CtrP[1] = P[10], CtrP[2] = P[11], CtrP[3] = P[0];
	bezier[3].ReadPoint(CtrP);
	bezier[3].DrawCurve(pDC);
	bezier[3].DrawPolygon(pDC);
}