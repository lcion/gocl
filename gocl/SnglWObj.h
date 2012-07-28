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
#include "GTubO.h"
#include "GPresO.h"
#include "GLndO.h"

class SnglWObj  
{
public:
	BOOL DeleteSelectedObj();
	BOOL GetSelectedObjInfo(void *objInfoStruct);
	void SetEditMode(UCHAR bEditMode);
	BOOL DeleteGObject(char *objName);
	BOOL IsObject(char *objName);
	void MoveW(LONG x, LONG y);
	BOOL TakeNextCmtS(char *gName, char *oName, LPSTR CommentStr);
	int AddLogicalAnd(char *grpName, char *lndName, POINT *params, LPSTR szCText);
	BOOL LoadLogicalAnd(char *grpName, ifstream *src);
	void ChangeTxt(char *grpName, char *txtoName, LPSTR szText);
	BOOL LoadGroup(ifstream *src, char *readBuf);
	BOOL LoadCircle(char *grpName, ifstream *src);
	BOOL LoadPolyL(char *grpName, ifstream *src);
	BOOL LoadPolyG(char* grpName, ifstream *src);
	BOOL LoadBox(char *grpName, ifstream *src);
	BOOL LoadMold(char *grpName, ifstream *src);
	BOOL LoadText(char *grpName, ifstream *src);
	BOOL LoadPress(char *grpName, ifstream *src);
	BOOL LoadTub(char *grpName, ifstream *src);
	BOOL LoadWindowObjects(ifstream *src, char *readBuf);
	BOOL SaveWindowObjects(ofstream *dst);
	LONG GobjChgColors(char *grpName, char *objName, LONG bcolor, LONG color);
	LONG AddPolyLine(char *grpName, char *plName, POINT *pointArray, int nofpct);
	LONG AddGroup(char *grpName, char *GroupObjName);
	LONG AddPolygon(char *szOMName, char *pgName, POINT *pointArray, int nofpct);
	LONG AddCircle(char *grpName, char *cirName, POINT *pointst);
	int AddBox(char *grpName, char *boxName, POINT *params);
	int AddMold(char *grpName, char *moldName, POINT *params, LPSTR szCText);
	LONG AddPress(char *grpName, char *presName, POINT *data, LPSTR szCText);
	LONG AddTub(char *grpName, char *tubName, POINT *data, LPSTR szCText);
	int Move(char *grpName, char *txtoName, POINT point);
	int MoveTo(char *grpName, char *txtOName, POINT point);
	BOOL SetTextFont(char *grpName, char *txtName, LPSTR fName, int fsize, int fattrib);
	void RefreshW();
	void ComputeBkgnd();
	int SetBackgroundColor(LONG color);
	BOOL SetVisible( BOOL visible );
	int SetBounds(LONG x, LONG y, LONG width, LONG height);
	int AddText(char *szOMName, char *txtName, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
	void DrawAllGObj(HDC memHdc);
	LONG Create(HINSTANCE appInst, LONG color, LONG bkcolor);
	SnglWObj(HWND parentHWnd, char *pWndName);
	virtual ~SnglWObj();

	char *m_WndName;
	Lista gobjsList;
//	Lista *m_pNameIdLst;
	HWND m_parentHWnd;
	HBITMAP m_bkgndBmp;
	HWND m_clsWnd;
	LONG m_bckgndColor;
private:
	BOOL SelectWObj(UINT x, UINT y);
	void CheckLoadResult(bool bFail, char* objName, char* szCText);
	UCHAR m_bEditMode;
	static	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};
/*
typedef struct tagWINDOWINFO {
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
} WINDOWINFO, *PWINDOWINFO, *LPWINDOWINFO;

BOOL WINAPI
GetWindowInfo(
    HWND hwnd,
    PWINDOWINFO pwi
);
*/

#endif // !defined(AFX_SNGLWOBJ_H__EE689A41_D583_11D3_ACBE_00500449492C__INCLUDED_)
