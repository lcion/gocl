// GPolyLO.h: interface for the GPolyLO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPolyLO_H__A7CE5C44_E8FC_11D3_ACBF_00500461226B__INCLUDED_)
#define AFX_GPolyLO_H__A7CE5C44_E8FC_11D3_ACBF_00500461226B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"

class GPolyLO : public SnglGObj
{
public:
	BOOL Save(ofstream *dst, LONG nID);
	int Move(HWND hWnd, POINT mhlPoint);
	void SetLimitis(RECT *pRect);
	void Redraw(HDC memHdc);
	void Create(POINT *pointst, int nofPt, LONG color, LPSTR szCText);
	int m_nofPct;
	GPolyLO(int ObjId);
	virtual ~GPolyLO();

};

#endif // !defined(AFX_GPolyLO_H__A7CE5C44_E8FC_11D3_ACBF_00500461226B__INCLUDED_)
