/* SnglWObj.cpp *******************************************************
*	 Description: implementation of the SnglWObj class.
*
*	Functions:
*		SnglWObj::GetSelectedObjInfo
*		SnglWObj::SelectWObj
*		SnglWObj::SetEditMode
*		SnglWObj::DeleteGObject
*		SnglWObj::IsObject
*		SnglWObj::MoveW
*		SnglWObj::TakeNextCmtS
*		SnglWObj::AddLogicalAnd
*		SnglWObj::LoadLogicalAnd
*		SnglWObj::ChangeTxt
*		SnglWObj::LoadGroup
*		SnglWObj::LoadCircle
*		SnglWObj::LoadPolyL
*		SnglWObj::LoadPolyG
*		SnglWObj::LoadBox
*		SnglWObj::LoadText
*		SnglWObj::LoadWindowObjects
*		SnglWObj::SaveWindowObjects
*		SnglWObj::GobjChgColors
*		SnglWObj::AddPolyLine
*		SnglWObj::AddGroup
*		SnglWObj::AddPolygon
*		SnglWObj::AddCircle
*		SnglWObj::AddBox
*		SnglWObj::Move
*		SnglWObj::MoveTo
*		SnglWObj::SetTextFont
*		SnglWObj::RefreshW
*		SnglWObj::ComputeBkgnd
*		SnglWObj::SetBackgroundColor
*		SnglWObj::SetVisible
*		SnglWObj::SetBounds
*		SnglWObj::AddText
*		SnglWObj::DrawAllGObj
*		SnglWObj::Create
*		SnglWObj::SnglWObj
*		SnglWObj::~SnglWObj
*
*		SnglWObj::WndProc
*
*	Revision:
*		2000-10-05 luci 1.0 New
**********************************************************************/

#include "SnglWObj.h"


/*********************************************************************
* Description:
*   Construction
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
SnglWObj::SnglWObj(HWND parentHWnd, char *pWndName)
{
	m_WndName = new char[strlen(pWndName)+1];
	strcpy_s(m_WndName, strlen(pWndName)+1, pWndName);

	m_parentHWnd = parentHWnd;
	m_bkgndBmp = NULL;
	m_bckgndColor = 0;
	m_bEditMode = 0;
}

/*********************************************************************
* Description:
*   Destruction
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
SnglWObj::~SnglWObj()
{
	delete m_WndName;
	m_WndName = NULL;
	Node *pListItem = gobjsList.GetFirstItem();
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		delete pGObj;
		pListItem = pListItem->next;
	}

	if(m_bkgndBmp)
		DeleteObject( m_bkgndBmp );
	m_bkgndBmp = NULL;

	DestroyWindow(m_clsWnd);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::Create(HINSTANCE appInst, LONG color, LONG bkcolor)
{
	//if our window class has not been registered, then do so

	WNDCLASS wc;
	if(!GetClassInfo(appInst, STR_CLASSNAME, &wc))
	{
		ZeroMemory(&wc, sizeof(wc));
		wc.style          = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc    = (WNDPROC)WndProc;
		wc.cbClsExtra     = 0;
		wc.cbWndExtra     = 0;
		wc.hInstance      = appInst;
		wc.hIcon          = NULL;
		wc.hCursor        = NULL;
		wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName   = NULL;
		wc.lpszClassName  = STR_CLASSNAME;
		if(!RegisterClass(&wc))
		{
			//if this fails, CreateWindow will fail, so don't sweat it
			return 0;
		}
	}

	m_clsWnd = CreateWindowEx( WS_EX_CLIENTEDGE,
		STR_CLASSNAME,
		NULL,
		WS_CHILD,
		0,
		0,
		0,
		0,
		m_parentHWnd,
		0,
		appInst,
		(LPVOID) this);
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LRESULT CALLBACK SnglWObj::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	LPCREATESTRUCT lpcs;
	SnglWObj* pThis = (SnglWObj* )GetWindowLong(hWnd, GWL_USERDATA);

	switch( message )
    {

    case WM_NCCREATE:
      // Since this is the first time that we can get ahold of
      // a pointer to the window class object, all messages that might
      // have been sent before this are never seen by the Windows object
      // and only get passed on to the DefWindowProc
      lpcs = (LPCREATESTRUCT)lParam;
      pThis = (SnglWObj*)(lpcs->lpCreateParams);
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
      break;

    case WM_SETCURSOR:
         SetCursor(LoadCursor( NULL, MAKEINTRESOURCE(IDC_ARROW) ) );
         return (LRESULT)TRUE;

    case WM_PALETTECHANGED:
			if ((HWND)wParam == hWnd)
		break;
	case WM_PAINT:
		pThis->RefreshW();
		break;
	case WM_SIZE:
		pThis->ComputeBkgnd();
		break;
	case WM_LBUTTONUP:
		if(pThis->m_bEditMode){
			pThis->SelectWObj(LOWORD(lParam), HIWORD(lParam));
			pThis->ComputeBkgnd();
		}
		break;

    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void SnglWObj::DrawAllGObj(HDC memHdc)
{
	Node *pListItem = gobjsList.GetFirstItem();
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		pGObj->Redraw(memHdc);
		pListItem = pListItem->next;
	}
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::AddText(char *grpName, char *txtName, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GTxtO *pGobj = new GTxtO(txtName);
		pGobj->Create(m_clsWnd, szText, x, y, color, bcolor, szCText);
		gobjsList.AddNode(txtName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddText(txtName, szText, x, y, color, bcolor, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::SetBounds(LONG x, LONG y, LONG width, LONG height)
{
	SetWindowPos(m_clsWnd, NULL, x,	y, width, height, SWP_NOZORDER);
	//Create the background bitmap
	HDC hdcCldW = GetDC( m_clsWnd );   // Obtain handle to the device context
	if(m_bkgndBmp)
		DeleteObject( m_bkgndBmp );
	m_bkgndBmp = CreateCompatibleBitmap(  hdcCldW,        // handle to device context 
		width,     // width of bitmap, in pixels
		height     // height of bitmap, in pixels  
		);
	ReleaseDC(  m_clsWnd, hdcCldW );
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::SetVisible(BOOL visible)
{
	if(visible == 1)
		return ShowWindow(m_clsWnd, SW_SHOW);
	return ShowWindow(m_clsWnd, SW_HIDE);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::SetBackgroundColor(LONG color)
{
	m_bckgndColor = color;
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void SnglWObj::ComputeBkgnd()
{
	POINT	stPoint;
	RECT tmpr;
	PAINTSTRUCT ps;

	if(m_bkgndBmp)
	{
		GetWindowRect( m_clsWnd, &tmpr );
		HDC hdcCldW = BeginPaint(m_clsWnd, &ps);

		HDC SourceDC = CreateCompatibleDC( hdcCldW );

		HBITMAP OldObj = (HBITMAP)SelectObject(SourceDC, m_bkgndBmp);
		SetBkColor(SourceDC, m_bckgndColor);
		HPEN crtPen = CreatePen( PS_SOLID ,	1, m_bckgndColor );
		HPEN oldPen = (HPEN)SelectObject(SourceDC, crtPen);
		HBRUSH bkgBrush = CreateSolidBrush( m_bckgndColor );
		HBRUSH oldBrush = (HBRUSH)SelectObject(SourceDC, bkgBrush);

		stPoint.x = tmpr.right - tmpr.left;
		stPoint.y = tmpr.bottom - tmpr.top;
		tmpr.right = tmpr.right - tmpr.left;
		tmpr.bottom = tmpr.bottom - tmpr.top;
		tmpr.left = tmpr.top = 0;

		Rectangle(SourceDC, 0, 0, stPoint.x, stPoint.y);
		DrawAllGObj(SourceDC);
		DPtoLP(hdcCldW, &stPoint, 1);

		EndPaint(m_clsWnd, &ps);
		SelectObject(SourceDC, oldBrush);
		SelectObject(SourceDC, OldObj);
		SelectObject(hdcCldW, oldPen);

		DeleteDC(SourceDC);
		DeleteObject(bkgBrush);
		DeleteObject(crtPen);
		InvalidateRect(m_clsWnd, &tmpr, FALSE);
	}
}


/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void SnglWObj::RefreshW()
{
	POINT	stPoint;
	RECT tmpr;
	if(m_bkgndBmp)
	{
		PAINTSTRUCT ps;
		HDC hdcCldW= BeginPaint(m_clsWnd, &ps);

		HDC SourceDC = CreateCompatibleDC( hdcCldW );

		HBITMAP OldObj = (HBITMAP)SelectObject(SourceDC, m_bkgndBmp);

		GetWindowRect(  m_clsWnd,      // handle to window
			&tmpr   // address of structure for window coordinates
			); 
		stPoint.x = tmpr.right - tmpr.left;
		stPoint.y = tmpr.bottom - tmpr.top;
		DPtoLP(hdcCldW, &stPoint, 1);

		int result = BitBlt(hdcCldW, 0, 0, stPoint.x, stPoint.y, SourceDC, 0, 0, SRCCOPY);

		SelectObject(SourceDC, OldObj);
		DeleteDC(SourceDC);
		EndPaint(m_clsWnd, &ps);
	}
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::SetTextFont(char *grpName, char *txtName, LPSTR fName, int fsize, int fattrib)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GTxtO *gtxtO = (GTxtO*) gobjsList.GetHandle(txtName);
		gtxtO->SetFont(fName, fsize, fattrib);
		return true;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->SetTextFont(txtName, fName, fsize, fattrib);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::MoveTo(char *grpName, char *txtOName, POINT point)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GTxtO *gtxtO = (GTxtO*) gobjsList.GetHandle(txtOName);
		
		return gtxtO->MoveTo(m_clsWnd, point);
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->MoveTo(txtOName, point);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::Move(char *grpName, char *oName, POINT point)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		SnglGObj *gtxtO = (SnglGObj*) gobjsList.GetHandle(oName);
		return gtxtO->Move(m_clsWnd, point);
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->Move(oName, point);
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::AddBox(char *grpName, char *boxName, POINT *params)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GBoxO *pGobj = new GBoxO(boxName);
		pGobj->Create(params);
		gobjsList.AddNode(boxName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddBox( boxName, params);
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::AddMold(char *grpName, char *moldName, POINT *params, LPSTR szCText)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GMoldO *pGobj = new GMoldO(moldName);
		pGobj->Create(params, szCText);
		gobjsList.AddNode(moldName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddMold( moldName, params, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddCircle(char *grpName, char *cirName, POINT *pointst)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GCircleO *pGobj = new GCircleO(cirName);
		pGobj->Create(pointst);
		gobjsList.AddNode(cirName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddCircle(cirName, pointst);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddPolygon(char *grpName, char *pgName, POINT *pointArray, int nofpct )
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GPolygO *pGobj = new GPolygO(pgName);
		pGobj->Create(pointArray, nofpct);//, color, bcolor, szCText
		gobjsList.AddNode(pgName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddPolygon(pgName, pointArray, nofpct);//, color, bcolor, szCText
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddGroup(char *grpName, char *GroupObjName)
{
/*	if(strcmp(m_WndName, grpName) == 0)
	{*/
		MulGObj *pGobj = new MulGObj(GroupObjName, m_clsWnd);
		gobjsList.AddNode(GroupObjName, pGobj);
		return 1;
	}/*
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddGroup("",GroupObjName);//, color, bcolor, szCText
}
*/

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddPolyLine(char *grpName, char *plName, POINT *pointArray, int nofpct)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GPolyLO *pGobj = new GPolyLO(plName);
		pGobj->Create(pointArray, nofpct);
		gobjsList.AddNode(plName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddPolyLine(plName, pointArray, nofpct);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddTub(char *grpName, char *tubName, POINT *data, LPSTR szCText)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GTubO *pGobj = new GTubO(tubName);
		pGobj->Create(data, szCText);
		gobjsList.AddNode(tubName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddTub(tubName, data, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddPress(char *grpName, char *presName, POINT *data, LPSTR szCText)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GPresO *pGobj = new GPresO(presName);
		pGobj->Create(data, szCText);
		gobjsList.AddNode(presName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddPress(presName, data, szCText);
}


/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
LONG SnglWObj::GobjChgColors(char *grpName, char *objName, LONG bcolor, LONG color)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		SnglGObj *gtxtO = (SnglGObj*) gobjsList.GetHandle(objName);
		return gtxtO->GobjChgColors(bcolor, color);
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->GobjChgColors(objName, bcolor, color);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::SaveWindowObjects(ofstream *dst)
{
	RECT tmpr;
	LONG ret=GetWindowRect(  m_clsWnd, &tmpr );
	POINT cpoint;
	cpoint.x = tmpr.left;
	cpoint.y = tmpr.top;
	ScreenToClient(m_parentHWnd, &cpoint);
	*dst << "BWND " << m_WndName <<" "<< " " << cpoint.x << " " << cpoint.y << " " << tmpr.right-tmpr.left 
		<< " " << tmpr.bottom-tmpr.top << " " << m_bckgndColor << endl;
	Node *pListItem = gobjsList.GetFirstItem();
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		pGObj->Save(dst);
		pListItem = pListItem->next;
	}
	*dst << "EWND" << endl;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadWindowObjects(ifstream *src, char *readBuf)
{
	*src >> readBuf;
	while( strcmp(readBuf, "TXT") == 0 || strcmp(readBuf, "BOX") == 0 || strcmp(readBuf, "POG") == 0 || strcmp(readBuf, "POL") == 0 || strcmp(readBuf, "CIR") == 0 || strcmp(readBuf, "BGRP") == 0 || strcmp(readBuf, "EGRP") == 0 || strcmp(readBuf, "PRS") == 0 || strcmp(readBuf, "TUB") == 0 || strcmp(readBuf, "LND") == 0 || strcmp(readBuf, "MLD") == 0)
	{
		if(strcmp(readBuf, "TXT") == 0)
		{
			LoadText(m_WndName, src);
		}
		else if(strcmp(readBuf, "BOX") == 0)
		{
			LoadBox(m_WndName, src);
		}
		else if(strcmp(readBuf, "POG") == 0)
		{
			LoadPolyG(m_WndName, src);
		}
		else if(strcmp(readBuf, "POL") == 0)
		{
			LoadPolyL(m_WndName, src);
		}
		else if(strcmp(readBuf, "CIR") == 0)
		{
			LoadCircle(m_WndName, src);
		}
		else if(strcmp(readBuf, "PRS") == 0)
		{
			LoadPress(m_WndName, src);
		}
		else if(strcmp(readBuf, "TUB") == 0)
		{
			LoadTub(m_WndName, src);
		}
		else if(strcmp(readBuf, "LND") == 0)
		{
			LoadLogicalAnd(m_WndName, src);//LoadLogicalAnd(LONG grp, ifstream *src)
		}
		else if(strcmp(readBuf, "MLD") == 0)
		{
			LoadMold(m_WndName, src);
		}
		else if(strcmp(readBuf, "BGRP") == 0)
		{
			LoadGroup(src, readBuf);
		}
		*src >> readBuf;
	}
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadText(char *grpName, ifstream *src)
{
	int txtLen;
	char readBuf[MAX_PATH], szCText[MAX_PATH], fontName[MAX_PATH];
	LONG x, y, color, bcolor, fsize, fprop;
	*src >> szCText;	//text object name

	char *pTxtName = new char[strlen(szCText)+1];
	strcpy_s( pTxtName, strlen(szCText)+1, szCText);

	*src >> txtLen;
	src->get();
	src->get(readBuf, txtLen+1);
	*src >> x;
	*src >> y;
	*src >> color;
	*src >> bcolor;
	*src >> txtLen;
	if(txtLen > 0)
	{
		src->get();
		src->get(fontName, txtLen+1);//font name
		*src >> fsize; // font size
		*src >> fprop; // font properties
	}
	src->getline(szCText, MAX_PATH);
	CheckLoadResult(src->fail(), "Txt", pTxtName);

	LONG ntxtID = AddText(grpName, pTxtName, readBuf, x, y, color, bcolor, szCText);
	if(txtLen > 0)
		SetTextFont(grpName, pTxtName, fontName, fsize, fprop);
	delete pTxtName;
	return true;
}

/*********************************************************************
* Description:
*   params[0] = first point
*   params[1] = second point
*   params[2] = colors:color, bcolor1
*   params[3] = bcolor2, LPSTRcomment
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadBox(char *grpName, ifstream *src)
{
	char szCText[MAX_PATH];
	POINT params[4];
	*src >> szCText;	//box object Name

	char *pBoxName = new char[strlen(szCText)+1];
	strcpy_s( pBoxName, strlen(szCText)+1, szCText);

	*src >> params[0].x; //first point x;
	*src >> params[0].y; //first point y;
	*src >> params[1].x;//second point x;
	*src >> params[1].y;//second point y;
	*src >> params[2].x;//col;
	*src >> params[2].y;//bcol1;
	*src >> params[3].x;//bcol2;
	src->getline(szCText, MAX_PATH);
	CheckLoadResult(src->fail(), "Box", pBoxName);

	params[3].y = (long) &szCText[0];
	AddBox(grpName, pBoxName, &params[0]);

	delete pBoxName;
	return true;
}

/*********************************************************************
* Description:
*   params[0] = first point
*   params[1] = second point
*   params[2] = colors:color, bcolor
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadMold(char *grpName, ifstream *src)
{
	char szCText[MAX_PATH];
	POINT params[4];
	*src >> szCText;
	char *pMldName = new char[strlen(szCText)+1];
	strcpy_s( pMldName, strlen(szCText)+1, szCText);

	*src >> params[0].x; //first point x;
	*src >> params[0].y; //first point y;
	*src >> params[1].x;//second point x;
	*src >> params[1].y;//second point y;
	*src >> params[2].x;//depth of the internal elipse;
	*src >> params[2].y;//offset to eches of the internal elipse;
	*src >> params[3].x;//col;
	*src >> params[3].y;//bcol;
	src->getline(szCText, MAX_PATH);
	CheckLoadResult(src->fail(), "Mold", pMldName);

	AddMold(grpName, pMldName, &params[0], szCText);

	delete pMldName;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadPolyG(char* grpName, ifstream *src)
{
	LONG npcts;
	POINT *ptab;
	char szCText[MAX_PATH];
	*src >> szCText;	//Polygon object Name
	char *pPogName = new char[strlen(szCText)+1];
	strcpy_s( pPogName, strlen(szCText)+1, szCText);

	*src >> npcts;
	ptab = new POINT[npcts+2];
	int i;
	for(i = 0; i < npcts+1; i++)
	{
		*src >> ptab[i].x;
		*src >> ptab[i].y;
	}
	*src >> ptab[i].x;//bcolor 2
	src->getline(szCText, MAX_PATH);
	CheckLoadResult(src->fail(), "PolyG", pPogName);

	ptab[i].y = (long) &szCText[0];
	AddPolygon(grpName, pPogName, ptab, npcts);

	delete ptab;
	delete pPogName;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadPolyL(char *grpName, ifstream *src)
{
	LONG npcts;
	POINT *ptab;
	char szCText[MAX_PATH];

	*src >> szCText;	//PolyLine object Name
	char *pPolName = new char[strlen(szCText)+1];
	strcpy_s( pPolName, strlen(szCText)+1, szCText);

	*src >> npcts;
	ptab = new POINT[npcts+1];
	int i;
	for(i = 0; i < npcts; i++)
	{
		*src >> ptab[i].x;
		*src >> ptab[i].y;
	}
	*src >> ptab[i].x;	//color
	src->getline(szCText, MAX_PATH);
	CheckLoadResult(src->fail(), "PolyL", pPolName);
	ptab[i].y = (LONG)szCText;
	AddPolyLine(grpName, pPolName, ptab, npcts);

	delete pPolName;
	delete ptab;
	return true;
}

/*********************************************************************
* Description:
*   pointst[0].x = the radius
*   pointst[0].y = the posx
*	pointst[1].x = the posy
*	pointst[1].y = the color
*	pointst[2].x = the bcolor1
*	pointst[2].y = the bcolor2
*	pointst[3].x = the the pointer to the text comment
*	pointst[3].y = not used
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadCircle(char *grpName, ifstream *src)
{
	POINT pointst[4];
	char szCText[MAX_PATH];

	*src >> szCText;	//Circle object Name
	char *pCirName = new char[strlen(szCText)+1];
	strcpy_s( pCirName, strlen(szCText)+1, szCText);

	*src >> pointst[0].x;
	*src >> pointst[0].y;
	*src >> pointst[1].x;
	*src >> pointst[1].y;
	*src >> pointst[2].x;
	*src >> pointst[2].y;
	src->getline(szCText, MAX_PATH);
	pointst[3].x = (long) &szCText[0];
	CheckLoadResult(src->fail(), "Circle", pCirName);

	AddCircle(grpName, pCirName, pointst);
	delete pCirName;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-07 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadPress(char *grpName, ifstream *src)
{
	POINT data[4];
	char szCText[MAX_PATH];
	*src >> szCText;	//Circle object Name
	char *pPrsName = new char[strlen(szCText)+1];
	strcpy_s( pPrsName, strlen(szCText)+1, szCText);

	*src >> data[0].x; //thick;
	*src >> data[1].x; //left
	*src >> data[1].y; //top
	*src >> data[2].x; //right
	*src >> data[2].y; //bottom
	*src >> data[3].x;//color;
	*src >> data[3].y;//bcolor;
	src->getline(szCText, MAX_PATH);
	CheckLoadResult(src->fail(), "Press", szCText);

	AddPress(grpName, pPrsName, &data[0], szCText);
	delete pPrsName;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-07 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadTub(char *grpName, ifstream *src)
{
	POINT data[3];
	char szCText[MAX_PATH];
	*src >> szCText;	//Tube object Name
	char *pTubName = new char[strlen(szCText)+1];
	strcpy_s( pTubName, strlen(szCText)+1, szCText);

	*src >> data[0].x; //number of crosses;
	*src >> data[1].x; //left
	*src >> data[1].y; //top
	*src >> data[2].x; //right
	*src >> data[2].y; //bottom
	*src >> data[0].y; //color;
	src->getline(szCText, MAX_PATH);
	CheckLoadResult(src->fail(), "Tub", szCText);

	AddTub(grpName, pTubName, &data[0], szCText);
	delete pTubName;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadGroup(ifstream *src, char *readBuf)
{
	char szCText[MAX_PATH];
//	*src >> gId;
	*src >> szCText;	//Group object Name
	char *pGrpName = new char[strlen(szCText)+1];
	strcpy_s( pGrpName, strlen(szCText)+1, szCText);

	AddGroup(pGrpName, pGrpName);
	*src >> readBuf;

	while( strcmp(readBuf, "TXT") == 0 || strcmp(readBuf, "BOX") == 0 || strcmp(readBuf, "POG") == 0 || strcmp(readBuf, "POL") == 0 || strcmp(readBuf, "CIR") == 0 || strcmp(readBuf, "PRS") == 0 || strcmp(readBuf, "TUB") == 0 || strcmp(readBuf, "LND") == 0 || strcmp(readBuf, "MLD") == 0 || strcmp(readBuf, "BGRP") == 0)
	{
		if(strcmp(readBuf, "TXT") == 0)
		{
			LoadText(pGrpName, src);
		}
		else if(strcmp(readBuf, "BOX") == 0)
		{
			LoadBox(pGrpName, src);
		}
		else if(strcmp(readBuf, "POG") == 0)
		{
			LoadPolyG(pGrpName, src);
		}
		else if(strcmp(readBuf, "POL") == 0)
		{
			LoadPolyL(pGrpName, src);
		}
		else if(strcmp(readBuf, "CIR") == 0)
		{
			LoadCircle(pGrpName, src);
		}
		else if(strcmp(readBuf, "PRS") == 0)
		{
			LoadPress(pGrpName, src);
		}
		else if(strcmp(readBuf, "TUB") == 0)
		{
			LoadTub(pGrpName, src);
		}
		else if(strcmp(readBuf, "LND") == 0)
		{
			LoadLogicalAnd(pGrpName, src);
		}
		else if(strcmp(readBuf, "MLD") == 0)
		{
			LoadMold(pGrpName, src);
		}
		else if(strcmp(readBuf, "BGRP") == 0)
		{
			LoadGroup(src, readBuf);
		}
		*src >> readBuf;
	}

	delete pGrpName;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
void SnglWObj::ChangeTxt(char *grpName, char *txtoName, LPSTR szText)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GTxtO *gtxtO = (GTxtO*) gobjsList.GetHandle(txtoName);
		gtxtO->ChangeTxt(m_clsWnd,szText);
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	grpObj->ChangeTxt(txtoName, szText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadLogicalAnd(char *grpName, ifstream *src)
{
	POINT params[3];
	char szCText[MAX_PATH];
	*src >> szCText;	//LogicalAnd object Name
	char *pLndName = new char[strlen(szCText)+1];
	strcpy_s( pLndName, strlen(szCText)+1, szCText);

	*src >> params[0].x; //first point x;
	*src >> params[0].y; //first point y;
	*src >> params[1].x;//second point x;
	*src >> params[1].y;//second point y;
	*src >> params[2].x;//col;
	*src >> params[2].y;//bcol;
	src->getline(szCText, MAX_PATH);
	CheckLoadResult(src->fail(), "LAnd", szCText);

	AddLogicalAnd(grpName, pLndName, &params[0], szCText);//AddLogicalAnd(char *grpName, LONG boxID, POINT *params)
	delete pLndName;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
int SnglWObj::AddLogicalAnd(char *grpName, char *lndName, POINT *params, LPSTR szCText)
{
	if(strcmp(m_WndName, grpName) == 0)
	{
		GLndO *pGobj = new GLndO(lndName);
		pGobj->Create(params, szCText);
		gobjsList.AddNode(lndName, pGobj);
		return 1;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpName);
	return grpObj->AddLogicalAnd( lndName, params, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::TakeNextCmtS(char *gName, char *oName, LPSTR CommentStr)
{
	SnglGObj *pGObj;
	if(oName[0] == '\0')
		pGObj = (SnglGObj *)gobjsList.GetNextClsPtr(gName);
	else
		pGObj = (SnglGObj *)gobjsList.GetHandle(*gName);
	return pGObj->TakeCmtS(gName, oName, CommentStr);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-06 luci 1.0 New
**********************************************************************/
void SnglWObj::MoveW(LONG offsetX, LONG offsetY)
{
	RECT vRect;
	GetWindowRect( m_clsWnd, &vRect);
	MapWindowPoints(NULL, m_clsWnd, (POINT *)&vRect, 2);
	MoveWindow(m_clsWnd, vRect.left+offsetX, vRect.top+offsetY,	vRect.right - vRect.left, vRect.bottom - vRect.top,	TRUE);
}
/*	POINT	stPoint;
	RECT tmpr;
		GetWindowRect(  m_clsWnd,      // handle to window
			&tmpr   // address of structure for window coordinates
			); 

		stPoint.x = tmpr.right - tmpr.left;
		stPoint.y = tmpr.bottom - tmpr.top;
		DPtoLP(hdcCldW, &stPoint, 1);

*/
/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-15 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::IsObject(char *objName)
{
	if(strcmp(m_WndName, objName) == 0)
		return TRUE;
	SnglGObj *pGObj;
	Node *gNode = gobjsList.GetFirstItem();
	while(gNode){
		if( strcmp(gNode->strnID, objName) == 0)
			return TRUE;
		pGObj = (SnglGObj *) gNode->LpvCls;
		if(pGObj->IsObject(objName))
			return TRUE;
		gNode = gobjsList.GetNextItem(gNode);
	}
	return FALSE;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-28 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::DeleteGObject(char *objName)
{
	SnglGObj *pGObj;
	Node *gNode = gobjsList.GetFirstItem();
	while(gNode){
		pGObj = (SnglGObj *) gNode->LpvCls;
		if( strcmp(gNode->strnID, objName) == 0){
			gobjsList.DelItem( objName );
			delete pGObj;
			return TRUE;
		}
		if(pGObj->DeleteGObject(objName))
			return TRUE;
		gNode = gobjsList.GetNextItem(gNode);
	}
	return FALSE;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-04 luci 1.0 New
**********************************************************************/
void SnglWObj::SetEditMode(UCHAR bEditMode)
{
	m_bEditMode = bEditMode;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::SelectWObj(UINT x, UINT y)
{
	SnglGObj *pGObj;
	Node *gNode = gobjsList.GetLastItem();
	while(gNode){
		pGObj = (SnglGObj *) gNode->LpvCls;
		if(pGObj->SelectGObject( x, y))
			return TRUE;
		gNode = gobjsList.GetPreviousItem(gNode);
	}
	return FALSE;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::GetSelectedObjInfo(void *objInfoStruct)
{
	SnglGObj *pGObj;
	OBJINFO * pObjInf =(OBJINFO *)objInfoStruct;
	Node *gNode = gobjsList.GetFirstItem();
	while(gNode){
		pGObj = (SnglGObj *) gNode->LpvCls;
		if(pGObj->GetSelectedObjInfo(objInfoStruct))
		{
			if(!pObjInf->strOMName)
				pObjInf->strOMName = m_WndName;
			return TRUE;
		}
		gNode = gobjsList.GetNextItem(gNode);
	}
	return FALSE;
}

/*********************************************************************
* Description: check read result
*
* Revision:
* 2000-10-06 luci 1.0 New
**********************************************************************/
void SnglWObj::CheckLoadResult(bool bFail, char* objName, char* szCText)
{
	if(bFail){
		char buff[100];
		sprintf_s(buff, 100, "bad object %s %s\n", objName, szCText);
		OutputDebugString(buff);
	}
}
