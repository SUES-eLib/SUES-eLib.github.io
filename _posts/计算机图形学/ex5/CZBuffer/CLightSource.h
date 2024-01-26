#pragma once
#include"CRGB.h"
#include"P3.h"
class CLightSource
{
public:
	CLightSource(void);
	virtual ~CLightSource(void);
	void SetDiffuse(CRGB diffuse);
	void SetSpecular(CRGB specular);	
	void SetPosition(double x, double y, double z);	
	void SetAttenuationFactor(double c0, double c1, double c2);
	void SetOnOff(BOOL onoff);public:
	CRGB L_Diffuse;	CRGB L_Specular;	
	CP3 L_Position;	
	double L_C0;	
	double L_C1;	
	double L_C2;
	BOOL L_OnOff;
};