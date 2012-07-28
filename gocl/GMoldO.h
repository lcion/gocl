// GMoldO.h: interface for the GMoldO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMOLDO_H__9F678541_0179_11D4_ACE1_00500461226B__INCLUDED_)
#define AFX_GMOLDO_H__9F678541_0179_11D4_ACE1_00500461226B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"

class GMoldO : public SnglGObj  
{
public:
	BOOL GetSelectedObjInfo(void *objInfoStruct);
	BOOL Save(ofstream *dst);
	void Redraw(HDC owindowDC);
	void Create(POINT *params, LPSTR szCText);
	GMoldO(char *ObjName);
	virtual ~GMoldO();

};

#endif // !defined(AFX_GMOLDO_H__9F678541_0179_11D4_ACE1_00500461226B__INCLUDED_)
