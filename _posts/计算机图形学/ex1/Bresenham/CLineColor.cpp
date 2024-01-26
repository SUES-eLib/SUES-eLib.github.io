#include "pch.h"
#include "CLineColor.h"
CLineColor::CLineColor()
{
}
CLineColor::CLineColor(CPoint p0, CPoint p1)
{
	P0 = p0;
	P1 = p1;
}
CLineColor::~CLineColor()
{
}
void CLineColor::SetStart(CPoint p0)
{
	P0 = p0;
}
void CLineColor::SetEnd(CPoint p1)
{
	P1 = p1;
}
CPoint CLineColor::GetEnd()
{
	return P1;
}
CPoint CLineColor::GetStart()
{
	return P0;
}
void CLineColor::BresenhamLine(CDC* pDC)//采用直线绘制算法来绘制直线
{
	int dx = abs(P1.x - P0.x);
	int dy = abs(P1.y - P0.y);
	bool bInterChange = TRUE;
	int e, signX, signY, temp;
	signX = (P1.x > P0.x) ? 1 : ((P1.x < P0.x) ? -1 : 0);
	signY = (P1.y > P0.y) ? 1 : ((P1.y < P0.y) ? -1 : 0);
	if (dy > dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = FALSE;
	}
	e = -dx;
	CPoint p = P0;
	for (int i = 1; i <= dx; i++)
	{
		pDC->SetPixelV(p.x, p.y, RGB(20, 60, 100));
		if (bInterChange)
			p.x += signX;
		else
			p.y += signY;
		e += 2 * dy;
		if (e >= 0)
		{
			if (bInterChange)
				p.y += signY;
			else
				p.x += signX;
			e -= 2 * dx;
		}
	}
}