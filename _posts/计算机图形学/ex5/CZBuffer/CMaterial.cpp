#include "pch.h"
#include "CMaterial.h"
CMaterial::CMaterial(void)
{
	M_Ambient = CRGB(0.2, 0.2, 0.2);
	M_Diffuse = CRGB(0.8, 0.8, 0.8);
	M_Specular = CRGB(0.0, 0.0, 0.0);
	M_Emission = CRGB(0.0, 0.0, 0.0, 1.0);
	M_n = 1.0;
}
CMaterial::~CMaterial(void)
{
}
void CMaterial::SetAmbient(CRGB c)
{
	M_Ambient = c;
}
void CMaterial::SetDiffuse(CRGB c)
{
	M_Diffuse = c;
}
void CMaterial::SetSpecular(CRGB c)
{
	M_Specular = c;
}
void CMaterial::SetEmission(CRGB c)
{
	M_Emission = c;
}
void CMaterial::SetExponent(double n)
{
	M_n = n;
}