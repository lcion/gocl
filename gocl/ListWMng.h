// ListWMng.h: interface for the ListWMng class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTWMNG_H__EE689A42_D583_11D3_ACBE_00500449492C__INCLUDED_)
#define AFX_LISTWMNG_H__EE689A42_D583_11D3_ACBE_00500449492C__INCLUDED_

#include "Lista.h"	// Added by ClassView
#include <fstream>
using namespace std;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ListWMng  
{
public:
	BOOL MoveClientW(LONG wid, LONG x, LONG y);
	BOOL TakeNextCommentStr(LONG *wid, LONG *grid, LONG *oid, LPSTR CommentStr);
	BOOL ChangeTxt(LONG wndId, LONG grpId, LONG txtoId, LPSTR szText);
	HWND m_hparentW;
	BOOL LoadAllObjects(ifstream *src, HWND hparentWnd);
	BOOL SaveAllObjects(ofstream *dst);
	LONG GobjChgColors(LONG wID, LONG grpId, LONG objID, LONG bcolor, LONG color);
	LONG AddPolyLine(LONG wID, LONG grpId, LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR szCText);
	LONG AddGroup(LONG wID, LONG gID);
	LONG AddPolygon(LONG wID, LONG grpId, LONG pgID, POINT *pointArray, int nofpct);
	LONG AddCircle(LONG wID, LONG grpId, LONG cirID, POINT *pointst);
	int AddBox(LONG wID, LONG grpId, LONG boxID, POINT *params);
	BOOL GobjMove(LONG wndId, LONG grpId, LONG txtoId, POINT point);
	BOOL GobjMoveTo(LONG wndId, LONG grpId, LONG txtoId, POINT point);
	BOOL SetTextFont(LONG wndId, LONG grpId, LONG txtoId, LPSTR fName, int fsize, int fattrib);
	HINSTANCE m_hAppInst;
	Lista SWOlist;
	void SethInst(HINSTANCE hInstance);
	BOOL SetVisible(LONG hidx, BOOL visible);
	BOOL SetBounds(LONG hidx, LONG x, LONG y, LONG width, LONG height);
	WORD SetBackgroundColor(LONG hidx, LONG color);
	BOOL Refresh(LONG hidx);
	BOOL CloseView(LONG hidx);
	LONG AddText(LONG tWndId, LONG grpId, LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
	LONG AddView(LONG wID, HWND hwndParent);
	ListWMng();
	virtual ~ListWMng();

};

#endif // !defined(AFX_LISTWMNG_H__EE689A42_D583_11D3_ACBE_00500449492C__INCLUDED_)
