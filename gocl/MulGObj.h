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
#include "GRezO.h"
#include "GPresO.h"
#include "GLndO.h"
#include "GMoldO.h"
class MulGObj : public SnglGObj
{
public:
	LONG AddMold(LONG boxID, POINT *params, LPSTR szCText);
	BOOL TakeCmtS(LONG *grid, LONG *oid, LPSTR CommentStr);
	int AddLogicalAnd(LONG boxID, POINT *params, LPSTR szCText);
	void ChangeTxt(LONG txtoId, LPSTR szText);
	LONG AddPress(LONG presID, POINT *data, LPSTR szCText);
	LONG AddRez(LONG rezID, POINT *data, LPSTR szCText);
	BOOL Save(ofstream *dst, LONG nID);
	LONG GobjChgColors(LONG objID, LONG bcolor, LONG color);
	LONG AddPolyLine(LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR szCText);
	void Redraw(HDC memHdc);
	MulGObj( int ObjId, HWND hclsWnd );
	virtual ~MulGObj();
	LONG	AddPolygon(LONG pgID, POINT *pointArray, int nofpct); //, LONG color, LONG bcolor, LPSTR szCText
	LONG	AddCircle(LONG cirID, POINT *pointst);
	int		AddBox(LONG boxID, POINT *params);
	int		Move(LONG txtoId, POINT point);
	int		MoveTo(LONG txtoId, POINT point);
	BOOL	SetTextFont(LONG txtoId, LPSTR fName, int fsize, int fattrib);
	int		AddText(LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);

	HBITMAP m_bkgndBmp;
	HWND m_clsWnd;

private:
	Lista grpOList;
};


#endif // !defined(AFX_MULGOBJ_H__CA69C380_E536_11D3_8E5B_00500461226B__INCLUDED_)
