// GCircleO.h: interface for the GCircleO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GCIRCLEO_H__AFBA20D1_DFB0_11D3_ACB4_00500449492C__INCLUDED_)
#define AFX_GCIRCLEO_H__AFBA20D1_DFB0_11D3_ACB4_00500449492C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"

class GCircleO : public SnglGObj  
{
public:
	LONG m_bgcolor2;
	BOOL Save(ofstream *dst, LONG nID);
	void Redraw(HDC memHdc);
//	void Create(LONG radius, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
	void Create(POINT *pointst);
	GCircleO(int ObjId);
	virtual ~GCircleO();
	BOOL TakeCmtS(LONG *grid, LONG *oid, LPSTR CommentStr);
};


#endif // !defined(AFX_GCIRCLEO_H__AFBA20D1_DFB0_11D3_ACB4_00500449492C__INCLUDED_)
