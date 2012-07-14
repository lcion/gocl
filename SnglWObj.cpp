/* SnglWObj.cpp *******************************************************
*	 Description: implementation of the SnglWObj class.
*
*	Functions:
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
*		
**********************************************************************/

#include "SnglWObj.h"


/*********************************************************************
* Description:
*   Construction
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
SnglWObj::SnglWObj(HWND parentHWnd)
{
	m_parentHWnd = parentHWnd;
	m_bkgndBmp = NULL;
	m_bckgndColor = 0;
}

/*********************************************************************
* Description:
*   Destruction
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
SnglWObj::~SnglWObj()
{
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
		wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
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
			return TRUE;

    case WM_PALETTECHANGED:
			if ((HWND)wParam == hWnd)
			break;
		case WM_PAINT:
			pThis->RefreshW();
			break;
		case WM_SIZE:
			pThis->ComputeBkgnd();
			break;
    case WM_KEYDOWN:
			switch( wParam )
			{
			case VK_ESCAPE:
			case VK_F12:
				PostMessage(hWnd,WM_CLOSE,0,0);
				break;
			}
		break;

    case WM_DESTROY:
//			PostQuitMessage( 0 );
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
int SnglWObj::AddText(LONG grpId, LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	if(grpId == NO_GROUP)
	{
		if(gobjsList.CheckNewID(txtID) == -1)
			return -1;
		GTxtO *pGobj = new GTxtO(txtID);
		pGobj->Create(m_clsWnd, szText, x, y, color, bcolor, szCText);
		gobjsList.AddNode(txtID, pGobj);
		return txtID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->AddText(txtID, szText, x, y, color, bcolor, szCText);
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
	SetCursor(LoadCursor(NULL, IDC_ARROW));
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
BOOL SnglWObj::SetTextFont(LONG grpId, LONG txtoId, LPSTR fName, int fsize, int fattrib)
{
	if(grpId == NO_GROUP)
	{
		GTxtO *gtxtO = (GTxtO*) gobjsList.GetHandle(txtoId);
		gtxtO->SetFont(fName, fsize, fattrib);
		return true;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->SetTextFont(txtoId, fName, fsize, fattrib);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::MoveTo(LONG grpId, LONG txtoId, POINT point)
{
	if(grpId == NO_GROUP)
	{
		GTxtO *gtxtO = (GTxtO*) gobjsList.GetHandle(txtoId);
		
		return gtxtO->MoveTo(m_clsWnd, point);
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->MoveTo(txtoId, point);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::Move(LONG grpId, LONG txtoId, POINT point)
{
	if(grpId == NO_GROUP)
	{
		SnglGObj *gtxtO = (SnglGObj*) gobjsList.GetHandle(txtoId);
		return gtxtO->Move(m_clsWnd, point);
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->Move(txtoId, point);
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::AddBox(LONG grpId, LONG boxID, POINT *params)
{
	if(grpId == NO_GROUP)
	{
		if(gobjsList.CheckNewID(boxID) == -1)
			return -1;
		GBoxO *pGobj = new GBoxO(boxID);
		pGobj->Create(params);
		gobjsList.AddNode(boxID, pGobj);
		return boxID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->AddBox( boxID, params);
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglWObj::AddMold(LONG grpId, LONG moldID, POINT *params, LPSTR szCText)
{
	if(grpId == NO_GROUP)
	{
		if(gobjsList.CheckNewID(moldID) == -1)
			return -1;
		GMoldO *pGobj = new GMoldO(moldID);
		pGobj->Create(params, szCText);
		gobjsList.AddNode(moldID, pGobj);
		return moldID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->AddMold( moldID, params, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddCircle(LONG grpId, LONG cirID, POINT *pointst)
{
	if(grpId == NO_GROUP)
	{
		if(gobjsList.CheckNewID(cirID) == -1)
			return -1;
		GCircleO *pGobj = new GCircleO(cirID);
		pGobj->Create(pointst);
		gobjsList.AddNode(cirID, pGobj);
		return cirID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->AddCircle(cirID, pointst);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddPolygon(LONG grpId, LONG pgID, POINT *pointArray, int nofpct )//LONG color, LONG bcolor, LPSTR szCText
{
	if(grpId == NO_GROUP)
	{
		if(gobjsList.CheckNewID(pgID) == -1)
			return -1;
		GPolygO *pGobj = new GPolygO(grpId);
		pGobj->Create(pointArray, nofpct);//, color, bcolor, szCText
//		LONG theID = gobjsList.GetNewID();
		gobjsList.AddNode(pgID, pGobj);
		return pgID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->AddPolygon(pgID, pointArray, nofpct);//, color, bcolor, szCText
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddGroup(LONG gID)
{
	if(gobjsList.CheckNewID(gID) == -1)
		return -1;
	MulGObj *pGobj = new MulGObj(gID, m_clsWnd);
//	LONG theID = gobjsList.GetNewID();
	gobjsList.AddNode(gID, pGobj);
	return gID;
}


/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddPolyLine(LONG grpId, LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR szCText)
{
	if(grpId == NO_GROUP)
	{
		if(gobjsList.CheckNewID(plID) == -1)
			return -1;
		GPolyLO *pGobj = new GPolyLO(grpId);
		pGobj->Create(pointArray, nofpct, color, szCText);
//		LONG theID = gobjsList.GetNewID();
		gobjsList.AddNode(plID, pGobj);
		return plID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->AddPolyLine(plID, pointArray, nofpct, color, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddRez(LONG grpID, LONG rezID, POINT *data, LPSTR szCText)
{
	if(grpID == NO_GROUP)
	{
		if(gobjsList.CheckNewID(rezID) == -1)
			return -1;
		GRezO *pGobj = new GRezO(rezID);
		pGobj->Create(data, szCText);
		gobjsList.AddNode(rezID, pGobj);
		return rezID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpID);
	return grpObj->AddRez(rezID, data, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
LONG SnglWObj::AddPress(LONG grpID, LONG presID, POINT *data, LPSTR szCText)
{
	if(grpID == NO_GROUP)
	{
		if(gobjsList.CheckNewID(presID) == -1)
			return -1;
		GPresO *pGobj = new GPresO(presID);
		pGobj->Create(data, szCText);
		gobjsList.AddNode(presID, pGobj);
		return presID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpID);
	return grpObj->AddPress(presID, data, szCText);
}


/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
LONG SnglWObj::GobjChgColors(LONG grpId, LONG objID, LONG bcolor, LONG color)
{
	if(grpId == NO_GROUP)
	{
		SnglGObj *gtxtO = (SnglGObj*) gobjsList.GetHandle(objID);
		return gtxtO->GobjChgColors(bcolor, color);
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->GobjChgColors(objID, bcolor, color);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::SaveWindowObjects(ofstream *dst, LONG nID)
{
	RECT tmpr;
	LONG ret=GetWindowRect(  m_clsWnd, &tmpr );
	POINT cpoint;
	cpoint.x = tmpr.left;
	cpoint.y = tmpr.top;
	ScreenToClient(m_parentHWnd, &cpoint);
	*dst << "BWND " <<nID<<" "<< " " << cpoint.x << " " << cpoint.y << " " << tmpr.right-tmpr.left 
		<< " " << tmpr.bottom-tmpr.top << " " << m_bckgndColor << endl;
	Node *pListItem = gobjsList.GetFirstItem();
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		pGObj->Save(dst, pListItem->nID);
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
			LoadText(-1, src);
		}
		else if(strcmp(readBuf, "BOX") == 0)
		{
			LoadBox(-1, src);
		}
		else if(strcmp(readBuf, "POG") == 0)
		{
			LoadPolyG(-1, src);
		}
		else if(strcmp(readBuf, "POL") == 0)
		{
			LoadPolyL(-1, src);
		}
		else if(strcmp(readBuf, "CIR") == 0)
		{
			LoadCircle(-1, src);
		}
		else if(strcmp(readBuf, "PRS") == 0)
		{
			LoadPress(-1, src);
		}
		else if(strcmp(readBuf, "TUB") == 0)
		{
			LoadRez(-1, src);
		}
		else if(strcmp(readBuf, "LND") == 0)
		{
			LoadLogicalAnd(-1, src);//LoadLogicalAnd(LONG grp, ifstream *src)
		}
		else if(strcmp(readBuf, "MLD") == 0)
		{
			LoadMold(-1, src);
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
BOOL SnglWObj::LoadText(LONG grp, ifstream *src)
{
	int txtLen;
	char readBuf[MAX_PATH], szCText[MAX_PATH], fontName[MAX_PATH];
	LONG x, y, color, bcolor, txtID, fsize, fprop;
	*src >> txtID;
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
	LONG ntxtID = AddText(grp, txtID, readBuf, x, y, color, bcolor, szCText);
	if(txtLen > 0)
		SetTextFont(grp, txtID, fontName, fsize, fprop);
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
BOOL SnglWObj::LoadBox(LONG grp, ifstream *src)
{
	char szCText[MAX_PATH];
	LONG boxID;
	POINT params[4];
	*src >> boxID;
	*src >> params[0].x; //first point x;
	*src >> params[0].y; //first point y;
	*src >> params[1].x;//second point x;
	*src >> params[1].y;//second point y;
	*src >> params[2].x;//col;
	*src >> params[2].y;//bcol1;
	*src >> params[3].x;//bcol2;
	src->getline(szCText, MAX_PATH);
	params[3].y = (long) &szCText[0];
	AddBox(grp, boxID, &params[0]);
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
BOOL SnglWObj::LoadMold(LONG grp, ifstream *src)
{
	char szCText[MAX_PATH];
	LONG boxID;
	POINT params[4];
	*src >> boxID;
	*src >> params[0].x; //first point x;
	*src >> params[0].y; //first point y;
	*src >> params[1].x;//second point x;
	*src >> params[1].y;//second point y;
	*src >> params[2].x;//depth of the internal elipse;
	*src >> params[2].y;//offset to eches of the internal elipse;
	*src >> params[3].x;//col;
	*src >> params[3].y;//bcol;
	src->getline(szCText, MAX_PATH);
	AddMold(grp, boxID, &params[0], szCText);
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadPolyG(LONG grp, ifstream *src)
{
	LONG npcts, pgID;
	POINT *ptab;
	char szCText[MAX_PATH];
	*src >> pgID;
	*src >> npcts;
	ptab = (POINT*)malloc(sizeof(POINT)*(npcts+2));
	int i;
	for(i = 0; i < npcts+1; i++)
	{
		*src >> ptab[i].x;
		*src >> ptab[i].y;
	}
	*src >> ptab[i].x;
//	*src >> bcol;
	src->getline(szCText, MAX_PATH);
	ptab[i].y = (long) &szCText[0];
	AddPolygon(grp, pgID, ptab, npcts);
	free(ptab);
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadPolyL(LONG grp, ifstream *src)
{
	LONG npcts, col, plID;
	POINT *ptab;
	char szCText[MAX_PATH];
	*src >> plID;
	*src >> npcts;
	ptab = (POINT*)malloc(sizeof(POINT)*npcts);
	for(int i = 0; i < npcts; i++)
	{
		*src >> ptab[i].x;
		*src >> ptab[i].y;
	}
	*src >> col;
	src->getline(szCText, MAX_PATH);
	AddPolyLine(grp, plID, ptab, npcts, col, szCText);
	free(ptab);
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
BOOL SnglWObj::LoadCircle(LONG grp, ifstream *src)
{
	LONG cirID; //radius, x, y, color, bcolor, 
	POINT pointst[4];
	char szCText[MAX_PATH];
	*src >> cirID;
	*src >> pointst[0].x;
	*src >> pointst[0].y;
	*src >> pointst[1].x;
	*src >> pointst[1].y;
	*src >> pointst[2].x;
	*src >> pointst[2].y;
	src->getline(szCText, MAX_PATH);
	pointst[3].x = (long) &szCText[0];
	AddCircle(grp, cirID, pointst);
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-07 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadPress(LONG grp, ifstream *src)
{
	LONG presID;
	POINT data[4];
	char szCText[MAX_PATH];
	*src >> presID;
	*src >> data[0].x; //thick;
	*src >> data[1].x; //left
	*src >> data[1].y; //top
	*src >> data[2].x; //right
	*src >> data[2].y; //bottom
	*src >> data[3].x;//color;
	*src >> data[3].y;//bcolor;
	src->getline(szCText, MAX_PATH);

	AddPress(grp, presID, &data[0], szCText);
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-07 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::LoadRez(LONG grp, ifstream *src)
{
	LONG rezID;
	POINT data[3];
	char szCText[MAX_PATH];
	*src >> rezID;
	*src >> data[0].x; //number of crosses;
	*src >> data[1].x; //left
	*src >> data[1].y; //top
	*src >> data[2].x; //right
	*src >> data[2].y; //bottom
	*src >> data[0].y; //color;
	src->getline(szCText, MAX_PATH);

	AddRez(grp, rezID, &data[0], szCText);
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
	LONG gId;
	*src >> gId;
	AddGroup(gId);
	*src >> readBuf;

	while( strcmp(readBuf, "TXT") == 0 || strcmp(readBuf, "BOX") == 0 || strcmp(readBuf, "POG") == 0 || strcmp(readBuf, "POL") == 0 || strcmp(readBuf, "CIR") == 0 || strcmp(readBuf, "PRS") == 0 || strcmp(readBuf, "TUB") == 0 || strcmp(readBuf, "LND") == 0 || strcmp(readBuf, "MLD") == 0)
	{
		if(strcmp(readBuf, "TXT") == 0)
		{
			LoadText(gId, src);
		}
		else if(strcmp(readBuf, "BOX") == 0)
		{
			LoadBox(gId, src);
		}
		else if(strcmp(readBuf, "POG") == 0)
		{
			LoadPolyG(gId, src);
		}
		else if(strcmp(readBuf, "POL") == 0)
		{
			LoadPolyL(gId, src);
		}
		else if(strcmp(readBuf, "CIR") == 0)
		{
			LoadCircle(gId, src);
		}
		else if(strcmp(readBuf, "PRS") == 0)
		{
			LoadPress(gId, src);
		}
		else if(strcmp(readBuf, "TUB") == 0)
		{
			LoadRez(gId, src);
		}
		else if(strcmp(readBuf, "LND") == 0)
		{
			LoadLogicalAnd(gId, src);
		}
		else if(strcmp(readBuf, "MLD") == 0)
		{
			LoadMold(gId, src);
		}
		*src >> readBuf;
	}
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
void SnglWObj::ChangeTxt(LONG grpId, LONG txtoId, LPSTR szText)
{
	if(grpId == NO_GROUP)
	{
		GTxtO *gtxtO = (GTxtO*) gobjsList.GetHandle(txtoId);
		gtxtO->ChangeTxt(m_clsWnd,szText);
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	grpObj->ChangeTxt(txtoId, szText);
}

BOOL SnglWObj::LoadLogicalAnd(LONG grp, ifstream *src)
{
	LONG lndID;
	POINT params[3];
	char szCText[MAX_PATH];
	*src >> lndID;
	*src >> params[0].x; //first point x;
	*src >> params[0].y; //first point y;
	*src >> params[1].x;//second point x;
	*src >> params[1].y;//second point y;
	*src >> params[2].x;//col;
	*src >> params[2].y;//bcol;
	src->getline(szCText, MAX_PATH);

	AddLogicalAnd(grp, lndID, &params[0], szCText);//AddLogicalAnd(LONG grpId, LONG boxID, POINT *params)
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
int SnglWObj::AddLogicalAnd(LONG grpId, LONG lndID, POINT *params, LPSTR szCText)
{
	if(grpId == NO_GROUP)
	{
		if(gobjsList.CheckNewID(lndID) == -1)
			return -1;
		GLndO *pGobj = new GLndO(lndID);
		pGobj->Create(params, szCText);
		gobjsList.AddNode(lndID, pGobj);
		return lndID;
	}
	MulGObj *grpObj = (MulGObj *)gobjsList.GetHandle(grpId);
	return grpObj->AddLogicalAnd( lndID, params, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL SnglWObj::TakeNextCmtS(LONG *gid, LONG *oid, LPSTR CommentStr)
{
	SnglGObj *pGObj;
	if(*oid == -1)
		pGObj = (SnglGObj *)gobjsList.GetNextClsPtr(gid);
	else
		pGObj = (SnglGObj *)gobjsList.GetHandle(*gid);
	return pGObj->TakeCmtS(gid, oid, CommentStr);
}

void SnglWObj::MoveW(LONG offsetX, LONG offsetY)
{
//	WINDOWINFO wi;

//	GetWindowInfo(m_clsWnd, &wi);

//	SetWindowPos(m_clsWnd, NULL, wi.rcWindow.left + offsetX, wi.rcWindow.top+offsetY, wi.rcWindow.right-wi.rcWindow.left, wi.rcWindow.bottom-wi.rcWindow.top, SWP_NOZORDER);
}
