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
#define LNDID			9

#include "windows.h"
#include "lista.h"

typedef struct {
	UCHAR objType;
	char *strGOName;
	char *strComment;
	char *strOMName;
	char *fntName;
	RECT *objRect;
	long GOColor;
	long GOBColor;
	long GOBColor1;
	UCHAR dNoOfPoints;
	void *vpObjData;
}OBJINFO;

class SnglGObj
{
public:
	virtual BOOL GetSelectedObjInfo(void *objInfoStruct);
	virtual BOOL SelectGObject(UINT x, UINT y);
	virtual BOOL DeleteGObject(char *objName);
	BOOL IsObject(char *objName);
	char * m_GOName;
	virtual BOOL TakeCmtS(char *grid, char *oid, LPSTR CommentStr);
	BOOL isInfo(LPSTR str);
	virtual BOOL Save(ofstream *dst);
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
//	int m_objId;
	SnglGObj(char *ObjName);
	virtual ~SnglGObj();

private:
	UCHAR m_bSelected;
};

#endif // !defined(AFX_SNGLGOBJ_H__EE689A43_D583_11D3_ACBE_00500449492C__INCLUDED_)
