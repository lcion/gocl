/* 
* Description:	The DLL exported function are defined here.
* File:			gocl.cpp
*	Lybrary exported functions
*	GOCL_SetBounds
*	GOCL_SetVisible
*	GOCL_GobjChgColors
*	GOCL_DeleteGObject
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
*	Add a window with wndName to the parent window
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddView(char *wName, HWND hwndParent)
{
	return listWMngi.AddView(wName, hwndParent);
}


/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Set the window dimensions and position
*	The window manager identify the window by "wndName" identifier
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_SetBounds(char *wndName, LONG x, LONG y, LONG length, LONG height)
{
	return listWMngi.SetBounds(wndName, x, y, length, height);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Set Edit working Mode for all windows
*	
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
void APIENTRY GOCL_SetEditMode(UCHAR bEditMode)
{
	listWMngi.SetEditMode(bEditMode);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Set the specified window visible (visible=true) or hide (visible=false)
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_SetVisible(char *wndName, BOOL visible)
{
	return listWMngi.SetVisible(wndName, visible);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Change colors to the specified graphilcal object
*	A graphical object is identified by tree identifiers:
*		1. Window ID
*		2. Group ID
*		3. Object ID
*	If the object do not have a group then grpName = -1
*	If we want to set colors for the entire group then we
*	call this function with objName = -1
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_GobjChgColors(char *wndName, char *grpName, char *objName, LONG bcolor, LONG color)
{
	return listWMngi.GobjChgColors(wndName, grpName, objName, bcolor, color);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Destroy window specified by wndName
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_DeleteGObject(char *objName)
{
		return listWMngi.DeleteGObject(objName);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Set the window, identified by wndName ,background color to the color
*		value.
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
WORD APIENTRY GOCL_SetBackgroundColor(char *wndName, LONG color)
{
	return listWMngi.SetBackgroundColor(wndName, color);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Refresh the specified window
*	here the window bitmap is rebuilded
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_Refresh(char *wndName)
{
	return listWMngi.Refresh(wndName);
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
LONG APIENTRY GOCL_AddGroup(char *wndName, char *gName)
{
	return listWMngi.AddGroup(wndName, gName);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Add a text object to the group specified by grpName from wind
*	The text graphical object is ientified by:
*		wndName  - window identifier
*		grpName  - group identifier
*		txtoID - graphical object identifier
*	The grpName can be -1 => a free object in the window
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddText(char *szOMName, char *txtName, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	return listWMngi.AddText(szOMName, txtName, szText, x, y, color, bcolor, szCText);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Add a Tube object to the group specified by szOMName from wind
*	The Tube graphical object is ientified by:
*		szOMName  - Tube group Name
*		tubeName - graphical object name
*	The szOMName can't be null or empty
* Revision:
* 2000-09-26 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddTube(char *szOMName, char *tubeName, POINT *data, LPSTR szCText)
{
	return listWMngi.AddTube(szOMName, tubeName, data, szCText);
}


/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Add a Press object to the group specified by szOMName from the window
*	The Press graphical object is ientified by:
*		szOMName  - Press group Name
*		pressName - graphical object name
*	The szOMName can't be null or empty
* Revision:
* 2000-09-26 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_AddPress(char *szOMName, char *presName, POINT *data, LPSTR szCText)
{
	return listWMngi.AddPress(szOMName, presName, data, szCText);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Add a Molder object to the group specified by szOMName from the window
*	The Molder graphical object is ientified by:
*		szOMName  - Molder group Name
*		molderName - graphical object name
*	The szOMName can't be null or empty
* Revision:
* 2000-10-04 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_AddMold(char *szOMName, char *moldName, POINT *data, LPSTR szCText)
{
	return listWMngi.AddMold(szOMName, moldName, data, szCText);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*   Add a LogicalAnd object to the group specified by szOMName from the window
*	The LogicalAnd graphical object is ientified by:
*		szOMName  - Press group Name
*		lndName - graphical object name
*	The szOMName can't be null or empty
* Revision:
* 2000-09-26 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_AddLogicalAnd(char *szOMName, char *lndName, POINT *params, LPSTR szCText)
{
	return listWMngi.AddLogicalAnd(szOMName, lndName, params, szCText);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Set font propertyes to the specified text graphical object
*	The text graphical object is ientified by:
*		wndName  - window identifier
*		grpName  - group identifier
*		txtoID - graphical object identifier
*	The grpName can be -1 => a free object in the window
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_SetTextFont(char *szOMName, char *txtoName, LPSTR fName, int fsize, int fattrib)
{
	return listWMngi.SetTextFont(szOMName, txtoName, fName, fsize, fattrib);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a Box object to one existing group from the window
*	The text graphical object is ientified by:
*		wndName  - window identifier
*		grpName  - group identifier
*		boxID - graphical object identifier
*	The grpName can be -1 => a free object in the window
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddBox(char *szOMName, char *boxName, POINT *params)
{
	return listWMngi.AddBox(szOMName, boxName, params);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a Circle object to one existing group from the window
*	The Circle graphical object is ientified by:
*		wndName  - window identifier
*		grpName  - group identifier
*		cirID - graphical object identifier
*	The grpName can be -1 => a free object in the window
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddCircle(char *szOMName, char *cirName, POINT *pointst)
{
	return listWMngi.AddCircle(szOMName, cirName, pointst);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a Polygon object to one existing group from the window
*	The Polygon graphical object is ientified by:
*		wndName  - window identifier
*		grpName  - group identifier
*		pgName - graphical object identifier
*	The grpName can be -1 => a free object in the window
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddPolygon(char *szOMName, char *pgName, POINT *pointArray, int nofpct)
{
	return listWMngi.AddPolygon(szOMName, pgName, pointArray, nofpct);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Add a PolyLine object to one existing group from the window
*	The PolyLine graphical object is ientified by:
*		wndName  - window identifier
*		grpName  - group identifier
*		plID - graphical object identifier
*	The grpName can be -1 => a free object in the window
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG APIENTRY GOCL_AddPolyLine(char *szOMName, char *plName, POINT *pointArray, int nofpct)
{
	return listWMngi.AddPolyLine(szOMName, plName, pointArray, nofpct);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Move an existing graphical object in one existing group from the 
*	window
*	The  graphical object is ientified by:
*		wndName  - window identifier
*		grpName  - group identifier
*		goID - graphical object identifier
*	The grpName can be -1 => a free object in the window is moved
*	The goID can be -1 => a free object in the window is moved
*	!Please do not call this function with both grpName and goID
*		set to -1. The function have no efect!
*	The graphical object is moved with mhlpoint.x to the left and
*		mhlpoint.y to the bottom
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_GobjMove(char *szOMName, char *goName, POINT mhlpoint)
{
	return listWMngi.GobjMove(szOMName, goName, mhlpoint);
}

/*********************************************************************
* Description:
*	Call the windows manager class with command:
*	Move an existing graphical object in one existing group from the
*		window to a final point "fpoint"
*	The  graphical object is ientified by:
*		wndName  - window identifier
*		grpName  - group identifier
*		goID - graphical object identifier
*	The grpName can be -1 => a free object in the window is moved
*	The goID can be -1 => a free object in the window is moved
*	!Please do not call this function with both grpName and goID
*		set to -1. The function have no efect!
*	The graphical object is moved with the upper left corner in
*		the specified position. The new position will be fpoint
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_GobjMoveTo(char *wndName, char *grpName, char *goName, POINT fpoint)
{
	return listWMngi.GobjMoveTo(wndName, grpName, goName, fpoint);
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
BOOL APIENTRY GOCL_ChangeTxt(char *wndName, char *grpName, char *txtoName, LPSTR szText)
{
	return listWMngi.ChangeTxt(wndName, grpName, txtoName, szText);
}

/*********************************************************************
* Description:
*   Call the windows manager class with command:
*	Take the next graphical object comment string.
*	to obtain the current graphical object ids we can call this 
*		function with: wndName = grid = oid = -1
*	the buffer CommentStr shoud have MAX_PATH bytes of memory
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_TakeNextCommentStr(char *wndName, char *grName, char *oName, LPSTR CommentStr)
{
	return listWMngi.TakeNextCommentStr(wndName, grName, oName, CommentStr);
}

BOOL APIENTRY GOCL_MoveClientW(char *wndName, LONG offsetX, LONG offsetY)
{
	return listWMngi.MoveClientW(wndName, offsetX, offsetY);
}

/*********************************************************************
* Description:
*   Test if the objectName exist as an object in the library
*	or it is free to use for another object
*
* Revision:
* 2000-09-20 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_IsObject(char *objName)
{
	return listWMngi.IsObject(objName);
}

/*********************************************************************
* Description:
*   Test if the objectName exist as an object in the library
*	or it is free to use for another object
*
* Revision:
* 2000-09-20 luci 1.0 New
**********************************************************************/
BOOL APIENTRY GOCL_GetSelectedObjInfo(void *objInfoStruct){
	return listWMngi.GetSelectedObjInfo(objInfoStruct);
}
