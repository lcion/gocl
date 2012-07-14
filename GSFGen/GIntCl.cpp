/* 
* Description:	Graphical interface Class to DLL
* File:			GIntCl.cpp
* Autor:		Luci
* Date:			17.01.2000
*/

#include "stdafx.h"
#include "GIntCl.h"



GIntCl::GIntCl()
{
	hInstGrL = LoadLibrary("ChartV.dll");
	(FARPROC &)lpAddView = GetProcAddress(hInstGrL , "WOBJ_AddView");
	(FARPROC &)lpSetBounds = GetProcAddress(hInstGrL , "WOBJ_SetBounds");
	(FARPROC &)lpSetVisible = GetProcAddress(hInstGrL , "WOBJ_SetVisible");
	(FARPROC &)lpCloseView = GetProcAddress(hInstGrL , "WOBJ_CloseView");
	(FARPROC &)lpSetBackgroundColor = GetProcAddress(hInstGrL , "WOBJ_SetBackgroundColor");
	(FARPROC &)lpRefresh = GetProcAddress(hInstGrL , "WOBJ_Refresh");
	(FARPROC &)lpAddText = GetProcAddress(hInstGrL , "WOBJ_AddText");
	(FARPROC &)lpComputeBmp  = GetProcAddress(hInstGrL , "WOBJ_ComputeBmp");
	(FARPROC &)lpSetTextFont = GetProcAddress(hInstGrL , "WOBJ_SetTextFont");
	(FARPROC &)lpGobjMove = GetProcAddress(hInstGrL , "WOBJ_GobjMove");
	(FARPROC &)lpGobjMoveTo = GetProcAddress(hInstGrL , "WOBJ_GobjMoveTo");
	(FARPROC &)lpAddBox = GetProcAddress(hInstGrL , "WOBJ_AddBox");
	(FARPROC &)lpAddCircle = GetProcAddress(hInstGrL , "WOBJ_AddCircle");
}

GIntCl::~GIntCl()
{
	FreeLibrary(hInstGrL);
	lpAddView = NULL;
}

long GIntCl::AddView(HWND HWnd)
{
	if(lpAddView != NULL)
		return lpAddView(HWnd);
	else
		return 0;
}

WORD GIntCl::SetBackgroundColor(long whnd, long color)
{
	return lpSetBackgroundColor(whnd, color);
}

BOOL GIntCl::SetBounds(LONG hidx, LONG x, LONG y, LONG width, LONG height)
{
	return lpSetBounds(hidx, x, y, width, height);
}

BOOL GIntCl::SetVisible(LONG handle, BOOL visible)
{
	return lpSetVisible(handle, visible);
}

BOOL GIntCl::CloseView(LONG winID)
{
	return lpCloseView(winID);
}

BOOL GIntCl::Refresh(LONG winID)
{
	return lpRefresh(winID);
}

LONG GIntCl::AddText(LONG hwndParent, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor)
{
	return lpAddText(hwndParent, szText, x, y, color, bcolor);
}

LONG GIntCl::ComputeBmp(LONG hidx)
{
	return lpComputeBmp(hidx);
}

BOOL GIntCl::SetTextFont(LONG wndId, LONG txtoId, LPSTR fName, int fsize, int fattrib)
{
	return lpSetTextFont(wndId, txtoId, fName, fsize, fattrib);
}

int GIntCl::GobjMove(LONG wndId, LONG txtoId, POINT mhlpoint)
{
	return lpGobjMove(wndId, txtoId, mhlpoint);
}

BOOL GIntCl::GobjMoveTo(LONG wndId, LONG txtoId, POINT fpoint)
{
	return lpGobjMoveTo(wndId, txtoId, fpoint);
}

LONG GIntCl::AddBox(LONG wId, LONG length, LONG posx, LONG posy, LONG color, LONG bcolor)
{
	return lpAddBox(wId, length, posx, posy, color, bcolor);
}

LONG GIntCl::AddCircle(LONG wId, LONG radius, LONG posx, LONG posy, LONG color, LONG bcolor)
{
	return lpAddCircle(wId, radius, posx, posy, color, bcolor);
}
