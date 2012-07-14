/* 
* Description:	Graphical interface Class to DLL
* File:			GIntCl.h
* Autor:		Luci
* Date:			17.01.2000
*/
#include <iostream.h>
#include <windows.h>
#include <conio.h>
#include "resource.h"

#define	MAXW	10
#define MAXO	10

class GIntCl
{
public:
	LONG AddCircle(LONG wId, LONG radius, LONG posx, LONG posy, LONG color, LONG bcolor);
	LONG AddBox(LONG wId, LONG length, LONG posx, LONG posy, LONG color, LONG bcolor);
	BOOL GobjMoveTo(LONG wndId, LONG txtoId, POINT fpoint);
	int GobjMove(LONG wndId, LONG txtoId, POINT mhlpoint);
	BOOL SetTextFont(LONG wndId, LONG txtoId, LPSTR fName, int fsize, int fattrib);
	LONG ComputeBmp(LONG hidx);
	LONG AddText(LONG hwndParent, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor);
	BOOL Refresh(LONG);
	BOOL CloseView(LONG winID);
	BOOL SetVisible(LONG handle, BOOL visible);
	BOOL SetBounds(LONG hidx, LONG x, LONG y, LONG width, LONG height);
	GIntCl();
	~GIntCl();
	long AddView(HWND HWnd);
	WORD SetBackgroundColor(long whnd, long color);
private:
	HINSTANCE hInstGrL;
	long (FAR STDAPICALLTYPE * lpAddView)(HWND handle);
	long (FAR STDAPICALLTYPE * lpSetBounds)(LONG hidx, LONG x, LONG y, LONG width, LONG height);
	BOOL (FAR STDAPICALLTYPE * lpSetVisible)(LONG , BOOL);
	BOOL (FAR STDAPICALLTYPE * lpCloseView)(LONG );
	BOOL (FAR STDAPICALLTYPE * lpSetBackgroundColor)(LONG , LONG);
	BOOL (FAR STDAPICALLTYPE * lpRefresh)(LONG);
	LONG (FAR STDAPICALLTYPE * lpAddText)(LONG hwndParent, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor);
	LONG (FAR STDAPICALLTYPE * lpComputeBmp)(LONG hidx);
	LONG (FAR STDAPICALLTYPE * lpSetTextFont)(LONG , LONG , LPSTR , int , int );
	LONG (FAR STDAPICALLTYPE * lpGobjMove)(LONG wndId, LONG txtoId, POINT mhlpoint);
	LONG (FAR STDAPICALLTYPE * lpGobjMoveTo)(LONG wndId, LONG txtoId, POINT mhlpoint);
	LONG (FAR STDAPICALLTYPE * lpAddBox)(LONG wId, LONG length, LONG posx, LONG posy, LONG color, LONG bcolor);
	LONG (FAR STDAPICALLTYPE * lpAddCircle)(LONG wId, LONG radius, LONG posx, LONG posy, LONG color, LONG bcolor);
};
