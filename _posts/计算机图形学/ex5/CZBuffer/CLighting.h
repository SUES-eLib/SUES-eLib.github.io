#pragma once
#include"CMaterial.h"
#include"Vector3.h"
#include"CLightSource.h"
class CLighting
{
public:
	CLighting(void);
	CLighting(int nLightNumber);
	virtual ~CLighting(void);
	void SetLightNumber(int nLightNumber);
	CRGB Illuminate(CP3 ViewPoint, CP3 Point, CVector3 ptNormal, CMaterial* pMaterial);

public:
	int nLightNumber;
	CLightSource* LightSource;
	CRGB Ambient;
};
