#pragma once
#include "CP2.h"
class CFence
{
public:
	CFence(void);
	virtual ~CFence(void);
	void ReadPoint(void);
	void Draw(CDC* pDC);
public:
	CP2 P[12];
};

