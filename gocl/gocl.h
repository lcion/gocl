//chartv.h
#if !defined(AFX_chartv_H__31194821_CE79_11D3_ACB5_00500449492C__INCLUDED_)
#define AFX_chartv_H__31194821_CE79_11D3_ACB5_00500449492C__INCLUDED_

#include "windows.h"
#include "stdio.h"
#include "ListWMng.h"
#include <fstream>
using namespace std;
typedef unsigned char uc;
//Global variables

// exported functionS

#define ID_FIRSTCHILD	100
#define ID_SECONDCHILD	101
#define ID_THIRDCHILD	102
#define MAXWNDH			50

ListWMng	listWMngi;

LONG APIENTRY GOCL_AddView(HWND handle);
BOOL APIENTRY GOCL_SetBounds(LONG hidx, LONG x, LONG y, LONG width, LONG height);
BOOL APIENTRY GOCL_SetVisible(LONG hidx, BOOL visible);
LONG APIENTRY GOCL_GobjChgColors(LONG wID, LONG grpId, LONG objID, LONG bcolor, LONG color);
BOOL APIENTRY GOCL_CloseView(LONG hidx);
WORD APIENTRY GOCL_SetBackgroundColor(LONG hidx, LONG color);
BOOL APIENTRY GOCL_Refresh(LONG hidx);
LONG APIENTRY GOCL_AddGroup(LONG wndId, LONG gID);
LONG APIENTRY GOCL_AddText(LONG wndId, LONG grpId, LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
LONG APIENTRY GOCL_AddBox(LONG wndId, LONG grpId, LONG boxID, POINT *params, LPSTR szCText);
LONG APIENTRY GOCL_AddCircle(LONG wndId, LONG grpId, LONG cirID, LONG radius, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
LONG APIENTRY GOCL_AddPolygon(LONG wID, LONG grpId, LONG pgID, POINT *pointArray, int nofpct, LONG color, LONG bcolor, LPSTR szCText);
LONG APIENTRY GOCL_AddPolyLine(LONG wID, LONG grpId, LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR szCText);
BOOL APIENTRY GOCL_SetTextFont(LONG wndId, LONG grpId, LONG txtoId, LPSTR fName, int fsize, int fattrib);
BOOL APIENTRY GOCL_GobjMove(LONG wndId, LONG grpId, LONG txtoId, POINT mhlpoint);
BOOL APIENTRY GOCL_GobjMoveTo(LONG wndId, LONG grpId, LONG txtoId, POINT fpoint);
BOOL APIENTRY GOCL_SaveAllObjects(LPSTR lpstrFile);
BOOL APIENTRY GOCL_LoadAllObjects(ifstream *src, HWND hparentWnd);
BOOL APIENTRY GOCL_ChangeTxt(LONG wndId, LONG grpId, LONG txtoId, LPSTR szText);
BOOL APIENTRY GOCL_TakeNextCommentStr(LONG *wid, LONG *grid, LONG *oid, LPSTR CommentStr);
#endif