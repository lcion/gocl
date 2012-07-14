// GBoxO.h: interface for the GBoxO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GBOXO_H__FCB13DD4_DF91_11D3_ACB3_00500449492C__INCLUDED_)
#define AFX_GBOXO_H__FCB13DD4_DF91_11D3_ACB3_00500449492C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"

class GBoxO : public SnglGObj  
{
public:
	LONG m_bgcolor2;
	BOOL TakeCmtS(LONG *grid, LONG *oid, LPSTR CommentStr);
	BOOL Save(ofstream *dst, LONG nID);
	void Redraw(HDC owindowDC);
	void Create(POINT *params);
	GBoxO(int ObjId);
	virtual ~GBoxO();
};

#endif // !defined(AFX_GBOXO_H__FCB13DD4_DF91_11D3_ACB3_00500449492C__INCLUDED_)
