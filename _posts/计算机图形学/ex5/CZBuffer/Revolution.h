#pragma once
#include "Patch.h"
#include "BezierPatch.h"

class CRevolution  //��ת��
{
public:
	CRevolution(void);
	virtual ~CRevolution(void);
	void ReadCubicBezierControlPoint(CP3 P[4]);//���߶����ʼ��
	CP3*  GetVertexArrayName(void);//�õ�����������
	void DrawRevolutionSurface(CDC* pDC, CZBuffer* pZbuffer);//���ƻ�ת��
private:
	void ReadVertex(void);//�����ת����ƶ���ζ���
	void ReadPatch(void);//�����ת��˫��������Ƭ	
private:
	CP3 P[4];//�������ߵ�4����ά���Ƶ�
	CP3 V[48];//��ת���ܶ�������(4����,��48����)
	CPatch S[4];//��ת�����������飨һȦ4���棩
public:
	CBezierPatch patch;//Bezier����Ƭ
};