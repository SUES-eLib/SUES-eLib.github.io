#include "pch.h"
#include "DDALine.h"
void DDALine::SetStart(CPoint p0)
{
    P0 = p0;
}
void  DDALine::SetEnd(CPoint p1)
{
    P1 = p1;
}
CPoint  DDALine::GetStart()
{
    return P1;
}
CPoint  DDALine::GetEnd()
{
    return P0;
}
void DDALine::CDDALine(CDC* pDC)
{
    float dx, dy, x, y, steps;
    int i;

    dx = P1.x - P0.x;
    dy = P1.y - P0.y;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    x = P0.x;
    y = P0.y;

    for (i = 0; i < steps; i++) {
        pDC->SetPixel(x, y, RGB(255, 100, 20));
        x += xIncrement;
        y += yIncrement;
    }
}
