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
	BOOL GetSelectedObjInfo(void *objInfoStruct);
	void SetEditMode(UCHAR bEditMode);
	BOOL AddMold(char *szOMName, char *moldName, POINT *data, LPSTR szCText);
	BOOL AddLogicalAnd(char *grpName, char *lndName, POINT *params, LPSTR szCText);
	BOOL AddPress(char *grpName, char *presName, POINT *data, LPSTR szCText);
	BOOL AddTube(char *grpName, char *tubName, POINT *data, LPSTR szCText);
	BOOL IsObject(char *objName);
	BOOL MoveClientW(char *wndName, LONG x, LONG y);
	BOOL TakeNextCommentStr(char *wndName, char *grName, char *oName, LPSTR CommentStr);
	BOOL ChangeTxt(char *wndName, char *grpName, char *txtoName, LPSTR szText);
	HWND m_hparentW;
	BOOL LoadAllObjects(ifstream *src, HWND hparentWnd);
	BOOL SaveAllObjects(ofstream *dst);
	LONG GobjChgColors(char *wndName, char *grpName, char *objName, LONG bcolor, LONG color);
	LONG AddPolyLine(char *szOMName, char *plName, POINT *pointArray, int nofpct);
	LONG AddGroup(char *wName, char *gName);
	LONG AddPolygon(char *szOMName, char *pgName, POINT *pointArray, int nofpct);
	LONG AddCircle(char *szOMName, char *cirName, POINT *pointst);
	int AddBox(char *szOMName, char *boxName, POINT *params);
	BOOL GobjMove(char *szOMName, char *goName, POINT point);
	BOOL GobjMoveTo(char *wndName, char *grpName, char *txtoName, POINT point);
	BOOL SetTextFont(char *szOMName, char *txtoName, LPSTR fName, int fsize, int fattrib);
	HINSTANCE m_hAppInst;
	Lista SWOlist;
	void SethInst(HINSTANCE hInstance);
	BOOL SetVisible(char *wndName, BOOL visible);
	BOOL SetBounds(char *wndName, LONG x, LONG y, LONG width, LONG height);
	WORD SetBackgroundColor(char *wndName, LONG color);
	BOOL Refresh(char *wndName);
	BOOL DeleteGObject(char *objName);
	LONG AddText(char *szOMName, char *txtName, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
	LONG AddView(char *wName, HWND hwndParent);
	ListWMng();
	virtual ~ListWMng();

private:
	void *GetWObjByOMName(char *szOMName);
};

#endif // !defined(AFX_LISTWMNG_H__EE689A42_D583_11D3_ACBE_00500449492C__INCLUDED_)
