#pragma once
#include"CMesh.h"
#include"CP3.h"
class CBezierPatch
{
public:
	CBezierPatch(void);
	virtual ~CBezierPatch(void);
	void ReadControlPoint(CP3 CtrPt[4][4], int ReNumber);//����16 �����Ƶ�͵ݹ����
	void DrawCurvedPatch(CDC* pDC);//��������
	void DrawControlGrid(CDC* pDC);//���ƿ�������
private:
	void Recursion(CDC* pDC, int ReNumber, CMesh Mesh);//�ݹ麯��
	void Tessellation(CMesh Mesh);//ϸ�ֺ���
	void DrawFacet(CDC* pDC);//�����ı�������
	void LeftMultiplyMatrix(double M[4][4], CP3 P[4][4]);//��˶������
	void RightMultiplyMatrix(CP3 P[4][4], double M[4][4]);//�ҳ˶������
	void TransposeMatrix(double M[4][4]);
private:
	int ReNumber;//�ݹ����
	CP3 quadrP[4];//�ı��������
	CP3 CtrPt[4][4];//�����16 �����Ƶ�
};
