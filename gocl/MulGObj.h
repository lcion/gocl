// MulGObj.h: interface for the MulGObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULGOBJ_H__CA69C380_E536_11D3_8E5B_00500461226B__INCLUDED_)
#define AFX_MULGOBJ_H__CA69C380_E536_11D3_8E5B_00500461226B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"
#include "Lista.h"	// Added by ClassView
#include "SnglGObj.h"
#include "GTxtO.h"
#include "GBoxO.h"
#include "GCircleO.h"
#include "GPolygO.h"
#include "GPolyLO.h"
#include "GTubO.h"
#include "GPresO.h"
#include "GLndO.h"
#include "GMoldO.h"
class MulGObj : public SnglGObj
{
public:
	BOOL GetSelectedObjInfo(void *objInfoStruct);
	BOOL SelectGObject(UINT x, UINT y);
	BOOL DeleteGObject(char *objName);
	BOOL IsObject(char *objName);
	LONG AddMold(char *moldName, POINT *params, LPSTR szCText);
	BOOL TakeCmtS(char *gid, char *oid, LPSTR CommentStr);
	int AddLogicalAnd(char *landName, POINT *params, LPSTR szCText);
	void ChangeTxt(char *txtoName, LPSTR szText);
	LONG AddPress(char *presName, POINT *data, LPSTR szCText);
	LONG AddTub(char *tubName, POINT *data, LPSTR szCText);
	BOOL Save(ofstream *dst);
	LONG GobjChgColors(char *objName, LONG bcolor, LONG color);
	LONG AddPolyLine(char *plName, POINT *pointArray, int nofpct);
	void Redraw(HDC memHdc);
	MulGObj( char *ObjName, HWND hclsWnd );
	virtual ~MulGObj();
	LONG	AddPolygon(char *pgName, POINT *pointArray, int nofpct);
	LONG	AddCircle(char *cirName, POINT *pointst);
	int		AddBox(char *boxName, POINT *params);
	int		Move(char *txtoName, POINT point);
	int		MoveTo(char *txtoName, POINT point);
	BOOL	SetTextFont(char *txtOName, LPSTR fName, int fsize, int fattrib);
	int		AddText(char* txtName, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);

	HBITMAP m_bkgndBmp;
	HWND m_clsWnd;

private:
	Lista grpOList;
};


#endif // !defined(AFX_MULGOBJ_H__CA69C380_E536_11D3_8E5B_00500461226B__INCLUDED_)
