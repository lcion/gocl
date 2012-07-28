// GLndO.h: interface for the GLndO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLNDO_H__254810A1_FB17_11D3_ACDA_00500461226B__INCLUDED_)
#define AFX_GLNDO_H__254810A1_FB17_11D3_ACDA_00500461226B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"

class GLndO : public SnglGObj  
{
public:
	BOOL GetSelectedObjInfo(void *objInfoStruct);
	BOOL Save(ofstream *dst);
	void Redraw(HDC owindowDC);
	void Create(POINT *params, LPSTR szCText);
	GLndO(char *ObjName);
	virtual ~GLndO();
};

#endif // !defined(AFX_GLNDO_H__254810A1_FB17_11D3_ACDA_00500461226B__INCLUDED_)
