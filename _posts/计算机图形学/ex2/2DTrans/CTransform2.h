#pragma once
#include "CP2.h"
class CTransform2
{
public:
	CTransform2(void);
	virtual ~CTransform2(void);
	void SetMatrix(CP2* P, int ptNumber);
	void Identity(void);
	void Translate(double tx, double ty);
	void Scale(double sx, double sy);
	void Scale(double sx, double sy, CP2 p);
	void Rotate(double beta);
	void Rotate(double beta, CP2 p);
	void ReflectOrg(void);
	void ReflectX(void);
	void ReflectY(void);
	void Shear(double b, double c);
	void MultiplyMatrix(void);
private:
	double T[3][3];
	CP2* P;
	int  ptNumber;
};