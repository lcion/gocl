// GPolygO.h: interface for the GPolygO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPOLYGO_H__CA69C384_E536_11D3_8E5B_00500461226B__INCLUDED_)
#define AFX_GPOLYGO_H__CA69C384_E536_11D3_8E5B_00500461226B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"

class GPolygO : public SnglGObj  
{
public:
	LONG m_bgcolor2;
	BOOL TakeCmtS(LONG *grid, LONG *oid, LPSTR CommentStr);
	BOOL Save(ofstream *dst, LONG nID);
	int Move(HWND hWnd, POINT mhlPoint);
	void SetLimitis(RECT *pRect);
	void AdjustGmove();
	int m_nofPct;
	void Redraw(HDC memHdc);
	void Create(POINT *pointst, int nofPt);
	GPolygO(int ObjId);
	virtual ~GPolygO();

};

#endif // !defined(AFX_GPOLYGO_H__CA69C384_E536_11D3_8E5B_00500461226B__INCLUDED_)
