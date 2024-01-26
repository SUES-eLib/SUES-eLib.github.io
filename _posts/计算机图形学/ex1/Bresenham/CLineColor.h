#pragma once
class CLineColor
{
private:
	CPoint P0, P1;
public:
	CLineColor();
	CLineColor(CPoint p0, CPoint p1);
	void SetStart(CPoint p0);
	void SetEnd(CPoint p1);
	CPoint GetStart();
	CPoint GetEnd();
	~CLineColor();
	void BresenhamLine(CDC* pDC);
};

