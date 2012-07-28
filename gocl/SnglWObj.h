// SnglWObj.h: interface for the SnglWObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNGLWOBJ_H__EE689A41_D583_11D3_ACBE_00500449492C__INCLUDED_)
#define AFX_SNGLWOBJ_H__EE689A41_D583_11D3_ACBE_00500449492C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STR_CLASSNAME "SingleWindowObject"

//#include "windows.h"
//#include "winuser.h"


#include "Lista.h"	// Added by ClassView
#include "SnglGObj.h"
#include "GTxtO.h"
#include "GBoxO.h"
#include "GCircleO.h"
#include "GPolygO.h"
#include "MulGObj.h"
#include "GRezO.h"
#include "GPresO.h"
#include "GLndO.h"
class SnglWObj  
{
public:
	void MoveW(LONG x, LONG y);
	BOOL TakeNextCmtS(LONG *gid, LONG *oid, LPSTR CommentStr);
	int AddLogicalAnd(LONG grpId, LONG boxID, POINT *params, LPSTR szCText);
	BOOL LoadLogicalAnd(LONG grp, ifstream *src);
	void ChangeTxt(LONG grpId, LONG txtoId, LPSTR szText);
	BOOL LoadGroup(ifstream *src, char *readBuf);
	BOOL LoadCircle(LONG grp, ifstream *src);
	BOOL LoadPolyL(LONG grp, ifstream *src);
	BOOL LoadPolyG(LONG grp, ifstream *src);
	BOOL LoadBox(LONG grp, ifstream *src);
	BOOL LoadMold(LONG grp, ifstream *src);
	BOOL LoadText(LONG grp, ifstream *src);
	BOOL LoadPress(LONG grp, ifstream *src);
	BOOL LoadRez(LONG grp, ifstream *src);
	BOOL LoadWindowObjects(ifstream *src, char *readBuf);
	BOOL SaveWindowObjects(ofstream *dst, LONG nID);
	LONG GobjChgColors(LONG grpId, LONG objID, LONG bcolor, LONG color);
	LONG AddPolyLine(LONG grpId, LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR szCText);
	LONG AddGroup(LONG gID);
	LONG AddPolygon(LONG grpId, LONG pgID, POINT *pointArray, int nofpct);
	LONG AddCircle(LONG grpId, LONG cirID, POINT *pointst);
	int AddBox(LONG grpId, LONG boxID, POINT *params);
	int AddMold(LONG grpId, LONG boxID, POINT *params, LPSTR szCText);
	LONG AddPress(LONG grpID, LONG presID, POINT *data, LPSTR szCText);
	LONG AddRez(LONG grpID, LONG rezID, POINT *data, LPSTR szCText);
	int Move(LONG grpId, LONG txtoId, POINT point);
	int MoveTo(LONG grpId, LONG txtoId, POINT point);
	BOOL SetTextFont(LONG grpId, LONG txtoId, LPSTR fName, int fsize, int fattrib);
	void RefreshW();
	void ComputeBkgnd();
	int SetBackgroundColor(LONG color);
	BOOL SetVisible( BOOL visible );
	int SetBounds(LONG x, LONG y, LONG width, LONG height);
	int AddText(LONG grpId, LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
	Lista gobjsList;
	void DrawAllGObj(HDC memHdc);
	LONG Create(HINSTANCE appInst, LONG color, LONG bkcolor);
	SnglWObj(HWND hwndParent);
	virtual ~SnglWObj();

	HWND m_parentHWnd;
	HBITMAP m_bkgndBmp;
	HWND m_clsWnd;
	LONG m_bckgndColor;
private:
	static	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// check read result
	void CheckLoadResult(bool bFail, char*objName, int index);
};

/*typedef struct tagWINDOWINFO {
    DWORD cbSize;
    RECT  rcWindow;
    RECT  rcClient;
    DWORD dwStyle;
    DWORD dwExStyle;
    DWORD dwWindowStatus;
    UINT  cxWindowBorders;
    UINT  cyWindowBorders;
    ATOM  atomWindowType;
    WORD  wCreatorVersion;
} WINDOWINFO, *PWINDOWINFO, *LPWINDOWINFO;*/

/*BOOL WINAPI
GetWindowInfo(
    HWND hwnd,
    PWINDOWINFO pwi
);*/

#endif // !defined(AFX_SNGLWOBJ_H__EE689A41_D583_11D3_ACBE_00500449492C__INCLUDED_)
