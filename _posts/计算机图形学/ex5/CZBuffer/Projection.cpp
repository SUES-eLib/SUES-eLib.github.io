#include "pch.h"
#include "Projection.h"

CProjection::CProjection(void)
{
	R = 1200, d = 800;
	EyePoint.x = 0, EyePoint.y = 0, EyePoint.z = R;//视点位于屏幕正前方
}

CProjection::~CProjection(void)
{
}

void CProjection::SetEye(double R)//设置视径
{
	this->R = R;
}

CP3 CProjection::GetEye(void)//读取视点
{
	return EyePoint;
}


CP2 CProjection::ObliqueProjection(CP3 WorldPoint)//斜二测投影
{
	CP2 ScreenPoint;//屏幕坐标系二维点
    ScreenPoint.x = WorldPoint.x - 0.3536 * WorldPoint.z;
	ScreenPoint.y = WorldPoint.y - 0.3536 * WorldPoint.z;
	return ScreenPoint;
}

CP2 CProjection::OrthogonalProjection(CP3 WorldPoint)//正交投影
{
	CP2 ScreenPoint;//屏幕坐标系二维点
	ScreenPoint.x = WorldPoint.x;
	ScreenPoint.y = WorldPoint.y;
	return ScreenPoint;
}

CP2 CProjection::PerspectiveProjection2(CP3 WorldPoint)
{
	CP3 ViewPoint;//观察坐标系三维点
	ViewPoint.x = WorldPoint.x;
	ViewPoint.y = WorldPoint.y;
	ViewPoint.z = EyePoint.z - WorldPoint.z;
	ViewPoint.c = WorldPoint.c;
	CP2 ScreenPoint;//屏幕坐标系二维点
	ScreenPoint.x = d * ViewPoint.x / ViewPoint.z;
	ScreenPoint.y = d * ViewPoint.y / ViewPoint.z;
	ScreenPoint.c = ViewPoint.c;
	return ScreenPoint;
}
   
CP3 CProjection::PerspectiveProjection3(CP3 WorldPoint)
{
	CP3 ViewPoint;
	ViewPoint.x = WorldPoint.x; 
	ViewPoint.y = WorldPoint.y;
	ViewPoint.z = EyePoint.z - WorldPoint.z;
	ViewPoint.c = WorldPoint.c;
	CP3 ScreenPoint;
	ScreenPoint.x = d * ViewPoint.x / ViewPoint.z;
	ScreenPoint.y = d * ViewPoint.y / ViewPoint.z;
	ScreenPoint.z = (ViewPoint.z - d) * d / ViewPoint.z;
	ScreenPoint.c = ViewPoint.c;
	return ScreenPoint;
}
