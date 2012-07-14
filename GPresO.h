// GPresO.h: interface for the GPresO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPRESO_H__439DC301_F355_11D3_ACCC_00500461226B__INCLUDED_)
#define AFX_GPRESO_H__439DC301_F355_11D3_ACCC_00500461226B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"
#include "math.h"

class GPresO : public SnglGObj  
{
public:
	BOOL Save(ofstream *dst, LONG nID);
	void Redraw(HDC memHdc);
	void Create(POINT *data, LPSTR szCText);
	GPresO(int ObjId);
	virtual ~GPresO();

};

#endif // !defined(AFX_GPRESO_H__439DC301_F355_11D3_ACCC_00500461226B__INCLUDED_)
