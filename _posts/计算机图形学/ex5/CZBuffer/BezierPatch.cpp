#include "pch.h"
#include "BezierPatch.h"
#define ROUND(d) int(d + 0.5)

CBezierPatch::CBezierPatch(void)
{
	ReNumber = 0;
}

CBezierPatch::~CBezierPatch(void)
{
}

void CBezierPatch::ReadControlPoint(CP3 CtrPt[4][4], int ReNumber)
{
	for (int i = 0; i< 4; i++)
		for (int j = 0; j < 4; j++)
			this->CtrPt[i][j] = CtrPt[i][j];
	this->ReNumber = ReNumber;
}

void CBezierPatch::SetScene(CLighting* pLight, CMaterial* pMaterial)//���ó���
{
	this->pLight = pLight;
	this->pMaterial = pMaterial;
}

void CBezierPatch::DrawCurvedPatch(CDC* pDC, CZBuffer* pZBuffer)
{
	CMesh Mesh;
	Mesh.BL = CT2(0, 0), Mesh.BR = CT2(1, 0);//��ʼ��uv
	Mesh.TR = CT2(1, 1), Mesh.TL = CT2(0, 1);
	Recursion(pDC, pZBuffer, ReNumber, Mesh);//�ݹ麯��
}

void CBezierPatch::Recursion(CDC* pDC, CZBuffer* pZBuffer, int ReNumber, CMesh Mesh)//�ݹ麯��
{
	if (0 == ReNumber)
	{
		Tessellation(Mesh);//ϸ�����棬����u��v����ת��Ϊ��x��y����
		DrawFacet(pDC, pZBuffer);//����Сƽ��
		return;
	}
	else
	{
		CT2 Mid = (Mesh.BL + Mesh.TR) / 2.0;
		CMesh SubMesh[4];//һ��Ϊ�ĸ�
		//�����ӳ�����
		SubMesh[0].BL = Mesh.BL;
		SubMesh[0].BR = CT2(Mid.u, Mesh.BL.v);
		SubMesh[0].TR = CT2(Mid.u, Mid.v);
		SubMesh[0].TL = CT2(Mesh.BL.u, Mid.v);
		//�����ӳ�����
		SubMesh[1].BL = SubMesh[0].BR;
		SubMesh[1].BR = Mesh.BR;
		SubMesh[1].TR = CT2(Mesh.BR.u, Mid.v);
		SubMesh[1].TL = SubMesh[0].TR;
		//�����ӳ�����
		SubMesh[2].BL = SubMesh[1].TL;
		SubMesh[2].BR = SubMesh[1].TR;
		SubMesh[2].TR = Mesh.TR;
		SubMesh[2].TL = CT2(Mid.u, Mesh.TR.v);
		//�����ӳ�����
		SubMesh[3].BL = SubMesh[0].TL;
		SubMesh[3].BR = SubMesh[2].BL;
		SubMesh[3].TR = SubMesh[2].TL;
		SubMesh[3].TL = Mesh.TL;
		Recursion(pDC, pZBuffer, ReNumber - 1, SubMesh[0]);//�ݹ����4��������
		Recursion(pDC, pZBuffer, ReNumber - 1, SubMesh[1]);
		Recursion(pDC, pZBuffer, ReNumber - 1, SubMesh[2]);
		Recursion(pDC, pZBuffer, ReNumber - 1, SubMesh[3]);
	}
}

void CBezierPatch::Tessellation(CMesh Mesh)//ϸ�����溯��
{
	double M[4][4];//ϵ������M
	M[0][0] = -1, M[0][1] = 3, M[0][2] = -3, M[0][3] = 1;
	M[1][0] = 3, M[1][1] = -6, M[1][2] = 3, M[1][3] = 0;
	M[2][0] = -3, M[2][1] = 3, M[2][2] = 0, M[2][3] = 0;
	M[3][0] = 1, M[3][1] = 0, M[3][2] = 0, M[3][3] = 0;
	CP3 P3[4][4];//���߼����ÿ��Ƶ�����
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			P3[i][j] = CtrPt[i][j];
	LeftMultiplyMatrix(M, P3);//ϵ�����������ά�����
	TransposeMatrix(M);//����ת�þ���
	RightMultiplyMatrix(P3, M);//ϵ�������ҳ���ά�����
	double u0, u1, u2, u3, v0, v1, v2, v3;//u��v��������
	double u[4] = { Mesh.BL.u,Mesh.BR.u ,Mesh.TR.u ,Mesh.TL.u };
	double v[4] = { Mesh.BL.v,Mesh.BR.v ,Mesh.TR.v ,Mesh.TL.v };
	for (int i = 0; i < 4; i++)
	{
		u3 = pow(u[i], 3.0), u2 = pow(u[i], 2.0), u1 = u[i], u0 = 1;
		v3 = pow(v[i], 3.0), v2 = pow(v[i], 2.0), v1 = v[i], v0 = 1;
		quadrP[i] = (u3 * P3[0][0] + u2 * P3[1][0] + u1 * P3[2][0] + u0 * P3[3][0]) * v3
			+ (u3 * P3[0][1] + u2 * P3[1][1] + u1 * P3[2][1] + u0 * P3[3][1]) * v2
			+ (u3 * P3[0][2] + u2 * P3[1][2] + u1 * P3[2][2] + u0 * P3[3][2]) * v1
			+ (u3 * P3[0][3] + u2 * P3[1][3] + u1 * P3[2][3] + u0 * P3[3][3]) * v0;
		//���㶥�㷨����
		CP3 uTagent, vTagent;
		double du3, du2, du1, du0;//u�����ƫ����
		du3 = 3.0 * pow(u[i], 2.0), du2 = 2.0 * u[i], du1 = 1, du0 = 0.0;
		v3 = pow(v[i], 3.0), v2 = pow(v[i], 2.0), v1 = v[i], v0 = 1.0;
		uTagent = (du3 * P3[0][0] + du2 * P3[1][0] + du1 * P3[2][0] + du0 * P3[3][0]) * v3
			    + (du3 * P3[0][1] + du2 * P3[1][1] + du1 * P3[2][1] + du0 * P3[3][1]) * v2
			    + (du3 * P3[0][2] + du2 * P3[1][2] + du1 * P3[2][2] + du0 * P3[3][2]) * v1
			    + (du3 * P3[0][3] + du2 * P3[1][3] + du1 * P3[2][3] + du0 * P3[3][3]) * v0;
		double dv3, dv2, dv1, dv0;//v�����ƫ����
		u3 = pow(u[i], 3.0), u2 = pow(u[i], 2.0), u1 = u[i], u0 = 1.0;
		dv3 = 3.0 * pow(v[i], 2.0), dv2 = 2.0 * v[i], dv1 = 1.0, dv0 = 0.0;
		vTagent = (u3 * P3[0][0] + u2 * P3[1][0] + u1 * P3[2][0] + u0 * P3[3][0]) * dv3
			    + (u3 * P3[0][1] + u2 * P3[1][1] + u1 * P3[2][1] + u0 * P3[3][1]) * dv2
			    + (u3 * P3[0][2] + u2 * P3[1][2] + u1 * P3[2][2] + u0 * P3[3][2]) * dv1
			    + (u3 * P3[0][3] + u2 * P3[1][3] + u1 * P3[2][3] + u0 * P3[3][3]) * dv0;
		CVector3 Pu = CVector3(uTagent), Pv = CVector3(vTagent);
		quadrN[i] = CrossProduct(Pu, Pv).Normalize();//��һ�����㷨����
		if(Pv.Magnitude() < 1e-4)//�ϱ������v��ƫ����Ϊ��
			quadrN[i] = CVector3(quadrP[i]).Normalize();
		
	}
}

void CBezierPatch::DrawFacet(CDC* pDC, CZBuffer* pZBuffer)
{
	CP3 ScreenPoint[4];
	CP3 ViewPoint = projection.GetEye();
	CVector3 NewVector[4], PerturbationVector;
	for (int nPoint = 0; nPoint < 4; nPoint++)
	{
		ScreenPoint[nPoint] = projection.PerspectiveProjection3(quadrP[nPoint]);
		double Frequency = 50;
		double bump = sin((quadrP[nPoint].x + quadrP[nPoint].y + quadrP[nPoint].z) / Frequency);
		PerturbationVector = CVector3(bump, bump, bump);
		NewVector[nPoint] = quadrN[nPoint] + PerturbationVector;
	}
	pZBuffer->SetPoint(ScreenPoint[0], ScreenPoint[2], ScreenPoint[3], NewVector[0], NewVector[2], NewVector[3]);
	pZBuffer->PhongShader(pDC, ViewPoint, pLight, pMaterial);
	pZBuffer->SetPoint(ScreenPoint[0], ScreenPoint[1], ScreenPoint[2], NewVector[0], NewVector[1], NewVector[2]);
	pZBuffer->PhongShader(pDC, ViewPoint, pLight, pMaterial);
}

void CBezierPatch::LeftMultiplyMatrix(double M[4][4], CP3 P[4][4])//��˾���M*P
{
	CP3 PTemp[4][4];//��ʱ����
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			PTemp[i][j] = M[i][0] * P[0][j] + M[i][1] * P[1][j] + M[i][2] * P[2][j] + M[i][3] * P[3][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			P[i][j] = PTemp[i][j];
}

void CBezierPatch::RightMultiplyMatrix(CP3 P[4][4], double M[4][4])//�ҳ˾���P*M
{
	CP3 PTemp[4][4];//��ʱ����
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			PTemp[i][j] = P[i][0] * M[0][j] + P[i][1] * M[1][j] + P[i][2] * M[2][j] + P[i][3] * M[3][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			P[i][j] = PTemp[i][j];
}

void CBezierPatch::TransposeMatrix(double M[4][4])//ת�þ���
{
	double PTemp[4][4];//��ʱ����
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			PTemp[j][i] = M[i][j];
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			M[i][j] = PTemp[i][j];
}

void CBezierPatch::DrawControlGrid(CDC* pDC)//���ƿ�������
{
	CP2 P2[4][4];//��ά���Ƶ�
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			P2[i][j] = projection.PerspectiveProjection2(CtrPt[i][j]);//͸��ͶӰ
	CPen NewPen, *pOldPen;
	NewPen.CreatePen(PS_SOLID, 3, RGB(0, 128, 0));
	pOldPen = pDC->SelectObject(&NewPen);
	for(int i = 0; i < 4; i++)
	{
		pDC->MoveTo(ROUND(P2[i][0].x), ROUND(P2[i][0].y));
		for(int j = 1; j < 4; j++)
			pDC->LineTo(ROUND(P2[i][j].x),ROUND(P2[i][j].y));
	}
	for(int j = 0; j < 4; j++)
	{
		pDC->MoveTo(ROUND(P2[0][j].x), ROUND(P2[0][j].y));
		for(int i = 1; i < 4; i++)
			pDC->LineTo(ROUND(P2[i][j].x), ROUND(P2[i][j].y));
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}