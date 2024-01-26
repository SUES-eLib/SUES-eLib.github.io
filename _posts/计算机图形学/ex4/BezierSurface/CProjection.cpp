#include "pch.h"
#include "CProjection.h"
CProjection::CProjection(void)
{
	R = 1200, d = 800;
	EyePoint.x = 0, EyePoint.y = 0, EyePoint.z = R;
}
CProjection::~CProjection(void)
{
}
void CProjection::SetEye(double R)
{
	EyePoint.z = R;
}
CP3 CProjection::GetEye(void)
{
	return EyePoint;
}
CP2 CProjection::ObliqueProjection(CP3 WorldPoint)
{
	CP2 ScreenPoint;
	ScreenPoint.x = WorldPoint.x - 0.3536 * WorldPoint.z;
	ScreenPoint.y = WorldPoint.y - 0.3536 * WorldPoint.z;
	return ScreenPoint;
}
CP2 CProjection::OrthogonalProjection(CP3 WorldPoint)
{
	CP2 ScreenPoint;	
	ScreenPoint.x = WorldPoint.x;
	ScreenPoint.y = WorldPoint.y;
	return ScreenPoint;
}
CP2 CProjection::PerspectiveProjection(CP3 WorldPoint)
{
	CP3 ViewPoint;	
	ViewPoint.x = WorldPoint.x;
	ViewPoint.y = WorldPoint.y;
	ViewPoint.z = EyePoint.z - WorldPoint.z;
	CP2 ScreenPoint;	
	ScreenPoint.x = d * ViewPoint.x / ViewPoint.z;
	ScreenPoint.y = d * ViewPoint.y / ViewPoint.z;
	return ScreenPoint;
}