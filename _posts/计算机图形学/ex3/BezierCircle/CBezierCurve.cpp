#include "pch.h"
#include "CBezierCurve.h"
#define ROUND(d) int(d + 0.5)
CBezierCurve::CBezierCurve(void)
{
}
CBezierCurve::~CBezierCurve(void)
{
}
void CBezierCurve::ReadPoint(CP2* P)
{
	for (int i = 0; i < 4; i++)
		this->P[i] = P[i];
}
void CBezierCurve::DrawCurve(CDC* pDC)//de Casteljau 递推算法
{
	CPen NewPen, * pOldPen;
	NewPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&NewPen);
	CP2 p00 = P[0], p10 = P[1], p20 = P[2], p30 = P[3];
	CP2 p01, p11, p21, p02, p12, p03;
	double tStep = 0.1;//步长
	pDC->MoveTo(ROUND(P[0].x), ROUND(P[0].y));
	for (double t = 0.0; t < 1; t += tStep)
	{
		p01 = (1 - t) * p00 + t * p10;
		p11 = (1 - t) * p10 + t * p20;
		p21 = (1 - t) * p20 + t * p30;
		p02 = (1 - t) * p01 + t * p11;
		p12 = (1 - t) * p11 + t * p21;
		p03 = (1 - t) * p02 + t * p12;
		pDC->LineTo(ROUND(p03.x), ROUND(p03.y));
	}
	pDC->LineTo(ROUND(P[3].x), ROUND(P[3].y));
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}
void CBezierCurve::DrawPolygon(CDC* pDC)
{
	CPen pen(PS_SOLID, 3, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush brush(RGB(0, 0, 255));
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	int i = 0;
	pDC->MoveTo(ROUND(P[i].x), ROUND(P[i].y));
	pDC->Ellipse(ROUND(P[i].x) - 5, ROUND(P[i].y) - 5, ROUND(P[i].x) + 5, ROUND(P[i].y) + 5);
	for (i = 1; i < 4; i++)
	{
		pDC->LineTo(ROUND(P[i].x), ROUND(P[i].y));
		pDC->Ellipse(ROUND(P[i].x) - 5, ROUND(P[i].y) - 5, ROUND(P[i].x) + 5, ROUND(P[i].y) + 5);
	}
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}