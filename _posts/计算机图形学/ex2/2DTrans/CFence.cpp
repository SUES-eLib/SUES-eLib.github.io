#include "pch.h"
#include "CFence.h"
#define ROUND(d) int(d + 0.5)
CFence::CFence(void)
{
}
CFence::~CFence(void)
{
}
void CFence::ReadPoint(void)
{
	P[0] = CP2(-1, -1);
	P[1] = CP2(1, -1);
	P[2] = CP2(1, 1);
	P[3] = CP2(-1, 1);
	P[4] = CP2(-2.5, -2.5);
	P[5] = CP2(2.5, -2.5);
	P[6] = CP2(2.5, 2.5);
	P[7] = CP2(-2.5, 2.5);
	P[8] = CP2((P[4].x + P[7].x) / 2 - 2, (P[4].y + P[7].y) / 2);
	P[9] = CP2((P[4].x + P[5].x) / 2, (P[4].y + P[5].y) / 2 - 2);
	P[10] = CP2((P[5].x + P[6].x) / 2 + 2, (P[5].y + P[6].y) / 2);
	P[11] = CP2((P[6].x + P[7].x) / 2, (P[6].y + P[7].y) / 2 + 2);
}
void CFence::Draw(CDC* pDC)
{
	CPen NewPen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&NewPen);

	pDC->MoveTo(ROUND(P[0].x), ROUND(P[0].y));
	pDC->LineTo(ROUND(P[1].x), ROUND(P[1].y));
	pDC->LineTo(ROUND(P[2].x), ROUND(P[2].y));
	pDC->LineTo(ROUND(P[3].x), ROUND(P[3].y));
	pDC->LineTo(ROUND(P[0].x), ROUND(P[0].y));

	pDC->MoveTo(ROUND(P[4].x), ROUND(P[4].y));
	pDC->LineTo(ROUND(P[5].x), ROUND(P[5].y));
	pDC->LineTo(ROUND(P[6].x), ROUND(P[6].y));
	pDC->LineTo(ROUND(P[7].x), ROUND(P[7].y));
	pDC->LineTo(ROUND(P[4].x), ROUND(P[4].y));

	pDC->MoveTo(ROUND(P[8].x), ROUND(P[8].y));
	pDC->LineTo(ROUND(P[10].x), ROUND(P[10].y));
	pDC->MoveTo(ROUND(P[9].x), ROUND(P[9].y));
	pDC->LineTo(ROUND(P[11].x), ROUND(P[11].y));
	pDC->SelectObject(pOldPen);
}
