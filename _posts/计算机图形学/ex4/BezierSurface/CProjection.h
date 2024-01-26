#pragma once
#include "CP3.h"
class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void SetEye(double R);
	CP3 GetEye(void);
	CP2 ObliqueProjection(CP3 WorldPoint);
	CP2 OrthogonalProjection(CP3 WorldPoint);
	CP2 PerspectiveProjection(CP3 WorldPoint);
private:
	CP3 EyePoint;
	double R, d;
};