#include "pch.h"
#include "CLightSource.h"
CLightSource::CLightSource(void)
{
	L_Diffuse = CRGB(0.0, 0.0, 0.0);	
	L_Specular = CRGB(1.0, 1.0, 1.0);	
	L_Position.x = 0.0, L_Position.y = 0.0, L_Position.z = 1000.0;	
	L_C0 = 1.0;	L_C1 = 0.0;	L_C2 = 0.0;	L_OnOff = TRUE;
}
CLightSource::~CLightSource(void)
{
}
void CLightSource::SetDiffuse(CRGB difuse)
{
	L_Diffuse = difuse;
}
void CLightSource::SetSpecular(CRGB specular)
{
	L_Specular = specular;
}
void CLightSource::SetPosition(double x, double y, double z)
{
	L_Position.x = x;
	L_Position.y = y;
	L_Position.z = z;
}
void CLightSource::SetOnOff(BOOL onoff)
{
	L_OnOff = onoff;
}
void CLightSource::SetAttenuationFactor(double c0, double c1, double c2)
{
	L_C0 = c0;
	L_C1 = c1;
	L_C2 = c2;
}