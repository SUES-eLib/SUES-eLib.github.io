#pragma once
#include "CP3.h"
class CTrans3
{
public:
	CTrans3(void) {};
	virtual ~CTrans3(void) {};
	void Identity(void);
	void SetMatrix(CP3* P, int ptNumber);
	void Translate(double tx, double ty, double tz);
	void Scale(double sx, double sy, double sz);
	void Scale(double sx, double sy, double sz, CP3 p);
	void RotateX(double beta);
	void RotateY(double beta);
	void RotateZ(double beta);
	void RotateX(double beta, CP3 p);
	void RotateY(double beta, CP3 p);
	void RotateZ(double beta, CP3 p);
	void ReflectX(void);
	void ReflectY(void);
	void ReflectZ(void);
	void ReflectXOY(void);
	void ReflectYOZ(void);
	void ReflectZOX(void);
	void ShearX(double b, double c);
	void ShearY(double d, double f);
	void ShearZ(double g, double h);
	void MultiplyMatrix(void);
private:
	double	M[4][4];
	CP3* P;
	int	ptNumber;
};

