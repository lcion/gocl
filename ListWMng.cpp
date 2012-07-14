/* ListWMng.cpp *******************************************************
*	 Description: implementation of the ListWMng class.
*
*	Functions:
*		ListWMng::LoadAllObjects
*		ListWMng::SaveAllObjects
*		ListWMng::GobjChgColors
*		ListWMng::AddPolyLine
*		ListWMng::AddGroup
*		ListWMng::AddPolygon
*		ListWMng::AddCircle
*		ListWMng::AddBox
*		ListWMng::GobjMove
*		ListWMng::GobjMoveTo
*		ListWMng::SetTextFont
*		ListWMng::ComputeBmp
*		ListWMng::SethInst
*		ListWMng::SetVisible
*		ListWMng::SetBounds
*		ListWMng::SetBackgroundColor
*		ListWMng::Refresh
*		ListWMng::CloseView
*		ListWMng::AddText
*		ListWMng::AddView
*		ListWMng::ListWMng
*		ListWMng::~ListWMng
*
*	Revision:
*		2000-02-23 luci 1.0 New
**********************************************************************/

#include "ListWMng.h"
#include "SnglWObj.h"


/*********************************************************************
* Description:
*   Constructor
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
ListWMng::ListWMng()
{

}

/*********************************************************************
* Description:
*   Destructor
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
ListWMng::~ListWMng()
{

}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG ListWMng::AddView(LONG wID, HWND hwndParent)
{
	m_hparentW = hwndParent;

	if(SWOlist.CheckNewID(wID) == -1)
		return -1;
	SnglWObj *newWobj = new SnglWObj(hwndParent);
	newWobj->Create(m_hAppInst, 0, 0x00ffffff);
	SWOlist.AddNode(wID, newWobj);
	return wID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG ListWMng::AddText(LONG tWndId, LONG grpId, LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( tWndId );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddText(grpId, txtID, szText, x, y, color, bcolor, szCText);
	}
	else
		return -1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL ListWMng::CloseView(LONG hidx)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( hidx );
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		SWOlist.DelItem( hidx );
		delete pSnglWObj;
		return 1;
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL ListWMng::Refresh(LONG hidx)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( hidx );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->ComputeBkgnd();
		return 1;
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
WORD ListWMng::SetBackgroundColor(LONG hidx, LONG color)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( hidx );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->SetBackgroundColor(color);
		return 1;
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL ListWMng::SetBounds(LONG hidx, LONG x, LONG y, LONG width, LONG height)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( hidx );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->SetBounds(x,  y,  width,  height);
		return 1;
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL ListWMng::SetVisible(LONG hidx, BOOL visible)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( hidx );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->SetVisible( visible );
		return 1;
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void ListWMng::SethInst(HINSTANCE hInstance)
{
	m_hAppInst = hInstance;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL ListWMng::SetTextFont(LONG wndId, LONG grpId, LONG txtoId, LPSTR fName, int fsize, int fattrib)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndId );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->SetTextFont(grpId, txtoId, fName, fsize, fattrib);
		return 1;
	}
	else
		return 0;

}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL ListWMng::GobjMoveTo(LONG wndId, LONG grpId, LONG txtoId, POINT point)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndId );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->MoveTo(grpId, txtoId, point);
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL ListWMng::GobjMove(LONG wndId, LONG grpId, LONG txtoId, POINT point)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndId );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->Move(grpId, txtoId, point);
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int ListWMng::AddBox(LONG wID, LONG grpId, LONG boxID, POINT *params)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wID );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddBox(grpId, boxID, params);
	}
	else
		return -1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG ListWMng::AddCircle(LONG wID, LONG grpId, LONG cirID, POINT *pointst)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wID );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddCircle(grpId, cirID, pointst);
	}
	else
		return -1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG ListWMng::AddPolygon(LONG wID, LONG grpId, LONG pgID, POINT *pointArray, int nofpct) //, LONG color, LONG bcolor, LPSTR szCText
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wID );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddPolygon(grpId, pgID, pointArray, nofpct); //, color, bcolor, szCText
	}
	else
		return -1;

}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG ListWMng::AddGroup(LONG wID, LONG gID)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wID );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddGroup(gID);
	}
	else
		return -1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG ListWMng::AddPolyLine(LONG wID, LONG grpId, LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR szCText)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wID );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddPolyLine(grpId, plID, pointArray, nofpct, color, szCText);
	}
	else
		return -1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
LONG ListWMng::GobjChgColors(LONG wID, LONG grpId, LONG objID, LONG bcolor, LONG color)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wID );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->GobjChgColors(grpId, objID, bcolor, color);
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL ListWMng::SaveAllObjects(ofstream *dst)
{
	Node *pListItem = SWOlist.GetFirstItem();
	int retval=1;
	while(pListItem != NULL)
	{
		SnglWObj *pGObj = (SnglWObj *)pListItem->LpvCls;
		pGObj->SaveWindowObjects(dst, pListItem->nID);
		pListItem = pListItem->next;
	}
	return retval;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
BOOL ListWMng::LoadAllObjects(ifstream *src, HWND hparentWnd)
{
	char readBuf[264] = "NULL_IMPUT_FILE";
	m_hparentW = hparentWnd;
	*src >> readBuf;
	while(strcmp(readBuf, "BWND") == 0)
	{
		LONG x, y, width, hight, bkcolor, wID;
		*src >> wID;//x
		*src >> x;//x
		*src >> y;//y
		*src >> width;//long
		*src >> hight;//hight
		*src >> bkcolor;//color
		if(AddView(wID, m_hparentW) == -1) // the ID is not free
			return false;
		SetBounds(wID , x , y, width, hight);
		SetBackgroundColor(wID, bkcolor);
		SetVisible(wID, 1);
		SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wID );
		pSnglWObj->LoadWindowObjects(src, readBuf);
		Refresh(wID);
		*src >> readBuf;
	}
	if(strcmp(readBuf, "NULL_IMPUT_FILE"))
	return TRUE;
	return FALSE;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL ListWMng::ChangeTxt(LONG wndId, LONG grpId, LONG txtoId, LPSTR szText)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndId );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->ChangeTxt(grpId, txtoId, szText);
		return 1;
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL ListWMng::TakeNextCommentStr(LONG *wid, LONG *grid, LONG *oid, LPSTR CommentStr)
{
	SnglWObj *pGObj;
	if(*oid == -1)
		pGObj = (SnglWObj *)SWOlist.GetNextClsPtr(wid);
	else
		pGObj = (SnglWObj *)SWOlist.GetHandle(*wid);
	return pGObj->TakeNextCmtS(grid, oid, CommentStr);
}

BOOL ListWMng::MoveClientW(LONG wid, LONG x, LONG y)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wid );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->MoveW(x, y);
		return 1;
	}
	else
		return 0;
}
