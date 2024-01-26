#pragma once
class DDALine
{
private:
    CPoint P0, P1;
public:
    void SetStart(CPoint p0);
    void SetEnd(CPoint p1);
    CPoint GetStart();
    CPoint GetEnd();
    void CDDALine(CDC* pDC);
};