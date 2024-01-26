#pragma once
#include"CMesh.h"
#include"CP3.h"
#include"CProjection.h"
class CBezierPatch
{
public:
	CBezierPatch(void);
	virtual ~CBezierPatch(void);
	void ReadControlPoint(CP3 CtrPt[4][4], int ReNumber);
	void DrawCurvedPatch(CDC* pDC);
	void DrawControlGrid(CDC* pDC);
private:
	void Recursion(CDC* pDC, int ReNumber, CMesh Mesh);
	void Tessellation(CMesh Mesh);
	void DrawFacet(CDC* pDC);
	void LeftMultiplyMatrix(double M[4][4], CP3 P[4][4]);
	void RightMultiplyMatrix(CP3 P[4][4], double M[4][4]);
	void TransposeMatrix(double M[4][4]);
private:
	int ReNumber;
	CP3 quadrP[4];
	CP3 CtrPt[4][4];
	CProjection projection;
};
