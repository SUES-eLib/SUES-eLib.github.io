#pragma once
#include "CFacet.h"
#include "CP3.h"
class CCube
{
public:
	CCube(void);
	virtual ~CCube(void);
	void ReadPoint(void);
	void ReadFacet(void);
	CP3* GetVertexArrayName(void);
	void Draw(CDC* pDC);
	CP3 P[8];
	CFacet F[6];
};

