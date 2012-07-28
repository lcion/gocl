/* 
* Description:	The DLL exported function are defined here.
* File:			gocl.cpp
*	Lybrary exported functions
*	GOCL_SetBounds
*	GOCL_SetVisible
*	GOCL_GobjChgColors
*	GOCL_CloseView
*	GOCL_SetBackgroundColor
*	GOCL_Refresh
*	GOCL_AddGroup
*	GOCL_AddText
*	GOCL_AddBox
*	GOCL_AddCircle
*	GOCL_AddPolygon
*	GOCL_AddPolyLine
*	GOCL_SetTextFont
*	GOCL_GobjMove
*	GOCL_GobjMoveTo
*	GOCL_SaveAllObjects
*	GOCL_LoadAllObjects
*	GOCL_ChangeTxt
*	GOCL_TakeNextCommentStr
*
* Autor:		Luci
* Date:			20/01/2000
*/

#include "gocl.h"


/*********************************************************************
* Description:
*   Library entrance funcion
*	Here I initialize window manager class
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		listWMngi.SethInst(hInstance);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
    return 1;
        UNREFERENCED_PARAMETER(lpReserved);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a window with wID to the parent window
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddView(LONG wID, HWND hwndParent)
{
	return listWMngi.AddView(wID, hwndParent);
}


/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Set the window dimensions and position
*	The window manager identify the window by "hidx" identifier
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_SetBounds(LONG hidx, LONG x, LONG y, LONG width, LONG height)
{
	return listWMngi.SetBounds(hidx, x, y, width, height);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Set the specified window visible (visible=true) or hide (visible=false)
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_SetVisible(LONG hidx, BOOL visible)
{
	return listWMngi.SetVisible(hidx, visible);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Change colors to the specified graphilcal object
*	A graphical object is identified by tree identifiers:
*		1. Window ID
*		2. Group ID
*		3. Object ID
*	If the object do not have a group then grpid = -1
*	If we want to set colors for the entire group then we
*	call this function with objID = -1
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_GobjChgColors(LONG wID, LONG grpId, LONG objID, LONG bcolor, LONG color)
{
	return listWMngi.GobjChgColors(wID, grpId, objID, bcolor, color);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Destroy window specified by hidx
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_CloseView(LONG hidx)
{
		return listWMngi.CloseView(hidx);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Set the window, identified by hidx ,background color to the color
*		value.
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
WORD APIENTRY GOCL_SetBackgroundColor(LONG hidx, LONG color)
{
	return listWMngi.SetBackgroundColor(hidx, color);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Refresh the specified window
*	here the window bitmap is rebuilded
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_Refresh(LONG hidx)
{
	return listWMngi.Refresh(hidx);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a new group of objects to the specified window
*	the group does not contain objects but you can add now objects
*	using as group ID the returned value
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddGroup(LONG wndId, LONG gID)
{
	return listWMngi.AddGroup(wndId, gID);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Add a text object to the group specified by grpId from wind
*	The text graphical object is ientified by:
*		wndid  - window identifier
*		grpId  - group identifier
*		txtoID - graphical object identifier
*	The grpId can be -1 => a free object in the window
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddText(LONG wndId, LONG grpId, LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	return listWMngi.AddText(wndId, grpId, txtID, szText, x, y, color, bcolor, szCText);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Set font propertyes to the specified text graphical object
*	The text graphical object is ientified by:
*		wndid  - window identifier
*		grpId  - group identifier
*		txtoID - graphical object identifier
*	The grpId can be -1 => a free object in the window
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_SetTextFont(LONG wndId, LONG grpId, LONG txtoId, LPSTR fName, int fsize, int fattrib)
{
	return listWMngi.SetTextFont(wndId, grpId, txtoId, fName, fsize, fattrib);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a Box object to one existing group from the window
*	The text graphical object is ientified by:
*		wndid  - window identifier
*		grpId  - group identifier
*		boxID - graphical object identifier
*	The grpId can be -1 => a free object in the window
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddBox(LONG wndId, LONG grpId, LONG boxID, POINT *params)
{
	return listWMngi.AddBox(wndId, grpId, boxID, params);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a Circle object to one existing group from the window
*	The Circle graphical object is ientified by:
*		wndid  - window identifier
*		grpId  - group identifier
*		cirID - graphical object identifier
*	The grpId can be -1 => a free object in the window
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddCircle(LONG wndId, LONG grpId, LONG cirID, LONG radius, POINT *pointst)
{
	return listWMngi.AddCircle(wndId, grpId, cirID, pointst);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a Polygon object to one existing group from the window
*	The Polygon graphical object is ientified by:
*		wndid  - window identifier
*		grpId  - group identifier
*		pgID - graphical object identifier
*	The grpId can be -1 => a free object in the window
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddPolygon(LONG wID, LONG grpId, LONG pgID, POINT *pointArray, int nofpct, LONG color, LONG bcolor, LPSTR szCText)
{
	return listWMngi.AddPolygon(wID, grpId, pgID, pointArray, nofpct);//
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a PolyLine object to one existing group from the window
*	The PolyLine graphical object is ientified by:
*		wndid  - window identifier
*		grpId  - group identifier
*		plID - graphical object identifier
*	The grpId can be -1 => a free object in the window
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddPolyLine(LONG wID, LONG grpId, LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR szCText)
{
	return listWMngi.AddPolyLine(wID, grpId, plID, pointArray, nofpct, color, szCText);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Move an existing graphical object in one existing group from the 
*	window
*	The  graphical object is ientified by:
*		wndid  - window identifier
*		grpId  - group identifier
*		goID - graphical object identifier
*	The grpId can be -1 => a free object in the window is moved
*	The goID can be -1 => a free object in the window is moved
*	!Please do not call this function with both grpID and goID
*		set to -1. The function have no efect!
*	The graphical object is moved with mhlpoint.x to the left and
*		mhlpoint.y to the bottom
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_GobjMove(LONG wndId, LONG grpId, LONG goId, POINT mhlpoint)
{
	return listWMngi.GobjMove(wndId, grpId, goId, mhlpoint);
}

/*********************************************************************
* Description:
*	Call the windows manager class with command:
*	Move an existing graphical object in one existing group from the
*		window to a final point "fpoint"
*	The  graphical object is ientified by:
*		wndid  - window identifier
*		grpId  - group identifier
*		goID - graphical object identifier
*	The grpId can be -1 => a free object in the window is moved
*	The goID can be -1 => a free object in the window is moved
*	!Please do not call this function with both grpID and goID
*		set to -1. The function have no efect!
*	The graphical object is moved with the upper left corner in
*		the specified position. The new position will be fpoint
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_GobjMoveTo(LONG wndId, LONG grpId, LONG goID, POINT fpoint)
{
	return listWMngi.GobjMoveTo(wndId, grpId, goID, fpoint);
}

/*********************************************************************
* Description:
*	Call the windows manager class with command:
*	Save all the existing objects from the library to a file
*	specified by lpstrFile.
*	in the lpstrFile parameter we shoud specified the filename
*	with complete path
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_SaveAllObjects(LPSTR lpstrFile)
{
	ofstream dst;
	BOOL rvalue = false;
	dst.open(lpstrFile);
	if(dst.is_open())
		rvalue = listWMngi.SaveAllObjects(&dst);
	dst.close();
	return rvalue;
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Load a script file and create the graphical objects.
*	In the lpstrFile parameter we shoud specified the filename
*	with complete path of the script file.
*
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_LoadAllObjects(LPSTR lpstrFile, HWND hparentWnd)
{
	BOOL rvalue = false;
	ifstream src;
	src.open(lpstrFile);
	if(src.is_open() == FALSE)
		return FALSE;
	rvalue = listWMngi.LoadAllObjects(&src, hparentWnd);
	src.close();
		return rvalue;
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Change the text in a text object.
*	by changing text from a text graphical object, all properties of 
*	the text object are keep.
*
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_ChangeTxt(LONG wndId, LONG grpId, LONG txtoId, LPSTR szText)
{
	return listWMngi.ChangeTxt(wndId, grpId, txtoId, szText);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Take the next graphical object comment string.
*	to obtain the current graphical object ids we can call this 
*		function with: wid = grid = oid = -1
*	the buffer CommentStr shoud have MAX_PATH bytes of memory
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_TakeNextCommentStr(LONG *wid, LONG *grid, LONG *oid, LPSTR CommentStr)
{
	return listWMngi.TakeNextCommentStr(wid, grid, oid, CommentStr);
}

BOOL APIENTRY GOCL_MoveClientW(LONG wid, LONG offsetX, LONG offsetY)
{
	return listWMngi.MoveClientW(wid, offsetX, offsetY);
}