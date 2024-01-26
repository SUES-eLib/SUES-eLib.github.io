#pragma once
#include "Point3.h"
#include "CLighting.h"
class CZBuffer
{
public:
	CZBuffer(void);
	virtual ~CZBuffer(void);
	void InitialDepthBuffer(int nWidth, int nHeight, double zDepth);
	void SetPoint(CP3 P0, CP3 P1, CP3 P2, CVector3 N0, CVector3 N1, CVector3 N2);
	void PhongShader(CDC* pDC, CP3 ViewPoint, CLighting* pLight, CMaterial* pMaterial);
private:
	void SortVertex(void);
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);
	CVector3 LinearInterp(double t, double coorStart, double coorEnd, CVector3 normalStart, CVector3 normalEnd);
protected:
	CP3 P0, P1, P2;	
	CPoint3 point0, point1, point2;
	CPoint2* SpanLeft;
	CPoint2* SpanRight;	
	int nIndex;
	double** zBuffer;	
	int nWidth, nHeight;
};