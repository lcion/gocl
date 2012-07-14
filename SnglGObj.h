// SnglGObj.h: interface for the SnglGObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNGLGOBJ_H__EE689A43_D583_11D3_ACBE_00500449492C__INCLUDED_)
#define AFX_SNGLGOBJ_H__EE689A43_D583_11D3_ACBE_00500449492C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
using namespace std;

#define ALL_OBJS		-1
#define NO_GROUP		-1
#define TXTID			0
#define BOXID			1
#define CIRCLEID		2
#define POLYGID			3
#define POLYLID			4
#define GROUPID			5
#define TUBID			6
#define PRESID			7
#define MOLDID			8

#include "windows.h"

class SnglGObj
{
public:
	virtual BOOL TakeCmtS(LONG *grid, LONG *oid, LPSTR CommentStr);
	BOOL isInfo(LPSTR str);
	virtual BOOL Save(ofstream *dst, LONG nID);
	LONG GobjChgColors(LONG bcolor, LONG color);
	virtual int MoveTo(HWND hWnd, POINT fPoint);
	virtual int Move(HWND hWnd, POINT mhlpoint);
	LONG m_lGOColor;
	LONG m_lGOBkndCol;
	char * m_vpobjData;
	char * m_strComment;
	RECT m_objRect;
	virtual void Redraw(HDC memHdc);
	int Create(LONG left, LONG top, LONG right, LONG bottom, LONG color, LONG bcolor, LPSTR szText);
	int m_objId;
	SnglGObj(int ObjId);
	virtual ~SnglGObj();

};

#endif // !defined(AFX_SNGLGOBJ_H__EE689A43_D583_11D3_ACBE_00500449492C__INCLUDED_)
