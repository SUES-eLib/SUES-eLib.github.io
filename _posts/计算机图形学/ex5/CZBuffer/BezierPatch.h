#pragma once
#include"Mesh.h"
#include"Projection.h"
#include"ZBuffer.h"

class CBezierPatch
{
public:
	CBezierPatch(void);
	virtual ~CBezierPatch(void);
	void ReadControlPoint(CP3 CtrPt[4][4], int ReNumber);//读入16个控制点和递归深度
	void SetScene(CLighting* pLight, CMaterial* pMaterial);//设置场景
	void DrawCurvedPatch(CDC* pDC, CZBuffer* pZBuffer);//绘制曲面
	void DrawControlGrid(CDC* pDC);//绘制控制网格
private:
	void Recursion(CDC* pDC, CZBuffer* pZBuffer, int ReNumber, CMesh Mesh);//递归函数
	void Tessellation(CMesh Mesh);//细分函数
	void DrawFacet(CDC* pDC, CZBuffer* pZBuffer);//绘制四边形网格
	void LeftMultiplyMatrix(double M[4][4], CP3 P[4][4]);//左乘顶点矩阵
	void RightMultiplyMatrix(CP3 P[4][4], double M[4][4]);//右乘顶点矩阵
	void TransposeMatrix(double M[4][4]);//转置矩阵
private:
	int ReNumber;//递归深度
	CP3 CtrPt[4][4];//曲面的16个控制点
	CP3 quadrP[4];//四边形的顶点
	CVector3 quadrN[4];//四边形的顶点法向量
	CProjection projection;//投影
	CLighting* pLight;//光照
	CMaterial* pMaterial;//材质
};

