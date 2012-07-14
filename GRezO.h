// GRezO.h: interface for the GRezO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GREZO_H__439DC302_F355_11D3_ACCC_00500461226B__INCLUDED_)
#define AFX_GREZO_H__439DC302_F355_11D3_ACCC_00500461226B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"
#include "math.h"
class GRezO : public SnglGObj  
{
public:
	BOOL Save(ofstream *dst, LONG nID);
	void Redraw(HDC memHdc);
	void Create(POINT *pointst, LPSTR szCText);
	GRezO(int ObjId);
	virtual ~GRezO();

};

#endif // !defined(AFX_GREZO_H__439DC302_F355_11D3_ACCC_00500461226B__INCLUDED_)
