#include "pch.h"
#include "CLighting.h"
CLighting::CLighting(void)
{
	nLightNumber = 1;
	LightSource = new CLightSource[nLightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);
}
CLighting::CLighting(int nLightNumber)
{
	this->nLightNumber = nLightNumber;
	LightSource = new CLightSource[nLightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);
}
CLighting::~CLighting(void)
{
	if (LightSource)
	{
		delete[]LightSource;
		LightSource = NULL;
	}
}
void CLighting::SetLightNumber(int nLightNumber)
{
	if (LightSource)
		delete[]LightSource;
	this->nLightNumber = nLightNumber;
	LightSource = new CLightSource[nLightNumber];
}
CRGB CLighting::Illuminate(CP3 ViewPoint, CP3 Point, CVector3 ptNormal, CMaterial* pMaterial)
{
	CRGB ResultI = pMaterial->M_Emission;
	for (int loop = 0; loop < nLightNumber; loop++)	
	{
		if (LightSource[loop].L_OnOff)		
		{
			CRGB I = CRGB(0.0, 0.0, 0.0);	
			CVector3 L(Point, LightSource[loop].L_Position);
			double d = L.Magnitude();	
			L = L.Normalize();		
			CVector3 N = ptNormal;
			N = N.Normalize();			
			double NdotL = max(DotProduct(N, L), 0);
			I += LightSource[loop].L_Diffuse * pMaterial->M_Diffuse * NdotL;
			CVector3 V(Point, ViewPoint);		
			V = V.Normalize();		
			CVector3 H = (L + V) / (L + V).Magnitude();	
			double NdotH = max(DotProduct(N, H), 0);
			double Rs = pow(NdotH, pMaterial->M_n);
			I += LightSource[loop].L_Specular * pMaterial->M_Specular * Rs;
			double c0 = LightSource[loop].L_C0;	
			double c1 = LightSource[loop].L_C1;		
			double c2 = LightSource[loop].L_C2;		
			double f = (1.0 / (c0 + c1 * d + c2 * d * d));
			f = min(1.0, f);
			ResultI += I * f;
		}
		else
			ResultI += Point.c;
	}
		ResultI += Ambient * pMaterial->M_Ambient;
		ResultI.Normalize();
		return ResultI;
}