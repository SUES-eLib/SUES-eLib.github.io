#pragma once
#include "P3.h"

class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void SetEye(double R);//设置视径
	CP3 GetEye(void);//读取视点
	CP2 ObliqueProjection(CP3 WorldPoint);//斜投影
	CP2 OrthogonalProjection(CP3 WorldPoint);//正交投影
	CP2 PerspectiveProjection2(CP3 WorldPoint);//二维透视投影
	CP3 PerspectiveProjection3(CP3 WorldPoint);//三维透视投影
private:
	CP3 EyePoint;//视点
	double R, d;//视径和视距
};

