#pragma once
#include "CRGB.h"
class CMaterial
{
public:
	CMaterial(void);
	virtual~CMaterial(void);
	void SetAmbient(CRGB c);	
	void SetDiffuse(CRGB c);	
	void SetSpecular(CRGB c);	
	void SetEmission(CRGB c);
	void SetExponent(double n);
public:
	CRGB M_Ambient;
	CRGB M_Diffuse;	
	CRGB M_Specular;	
	CRGB M_Emission;	
	double M_n;
};
