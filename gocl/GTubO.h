// GTubO.h: interface for the GTubO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GTUBO_H__439DC302_F355_11D3_ACCC_00500461226B__INCLUDED_)
#define AFX_GTUBO_H__439DC302_F355_11D3_ACCC_00500461226B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnglGObj.h"
#include "math.h"
class GTubO : public SnglGObj  
{
public:
	BOOL GetSelectedObjInfo(void *objInfoStruct);
	BOOL Save(ofstream *dst);
	void Redraw(HDC memHdc);
	void Create(POINT *pointst, LPSTR szCText);
	GTubO(char *ObjName);
	virtual ~GTubO();

};

#endif // !defined(AFX_GTUBO_H__439DC302_F355_11D3_ACCC_00500461226B__INCLUDED_)
