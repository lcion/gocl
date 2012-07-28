/* ListWMng.cpp *******************************************************
*	 Description: implementation of the ListWMng class.
*
*	Functions:
*		ListWMng::GetSelectedObjInfo
*		ListWMng::IsObject
*		ListWMng::MoveClientW
*		ListWMng::TakeNextCommentStr
*		ListWMng::ChangeTxt
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
*		ListWMng::DeleteGObject
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
LONG ListWMng::AddView(char *wName, HWND hwndParent)
{
	m_hparentW = hwndParent;

	SnglWObj *newWobj = new SnglWObj(hwndParent, wName);
	newWobj->Create(m_hAppInst, 0, 0x00ffffff);
	SWOlist.AddNode(wName, newWobj);
	return TRUE;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
*********************************************************************/
LONG ListWMng::AddText(char *szOMName, char *txtName, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	SnglWObj *pSnglWObj = (SnglWObj *)GetWObjByOMName(szOMName);//(SnglWObj *) SWOlist.GetHandle( twndName );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddText(szOMName, txtName, szText, x, y, color, bcolor, szCText);
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
BOOL ListWMng::DeleteGObject(char *objName)
{
/*	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( objName );
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		if(SWOlist.DelItem( objName )){
			delete pSnglWObj;
			return 1;
		}
	}*/
	SnglWObj *pSnglWObj;
	Node *wNode = SWOlist.GetFirstItem();
	while(wNode){
		pSnglWObj = (SnglWObj *) wNode->LpvCls;
		if( strcmp(wNode->strnID, objName) == 0){//window
			SWOlist.DelItem( objName );
			delete pSnglWObj;
			return TRUE;
		}
		if(pSnglWObj->DeleteGObject(objName))
			return TRUE;
		wNode = SWOlist.GetNextItem(wNode);
	}
	return FALSE;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL ListWMng::Refresh(char *wndName)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndName );
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
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
WORD ListWMng::SetBackgroundColor(char *wndName, LONG color)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndName );
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
BOOL ListWMng::SetBounds(char *wndName, LONG x, LONG y, LONG width, LONG height)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndName );
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
BOOL ListWMng::SetVisible(char *wndName, BOOL visible)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndName );
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
BOOL ListWMng::SetTextFont(char *szOMName, char *txtoName, LPSTR fName, int fsize, int fattrib)
{
	SnglWObj *pSnglWObj = (SnglWObj *) GetWObjByOMName(szOMName);
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->SetTextFont(szOMName, txtoName, fName, fsize, fattrib);
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
BOOL ListWMng::GobjMoveTo(char *wndName, char *grpName, char *txtoName, POINT point)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndName );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->MoveTo(grpName, txtoName, point);
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
BOOL ListWMng::GobjMove(char *szOMName, char *goName, POINT point)
{
	SnglWObj *pSnglWObj = (SnglWObj *) GetWObjByOMName( szOMName );
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->Move(szOMName, goName, point);
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
int ListWMng::AddBox(char *szOMName, char *boxName, POINT *params)
{
	SnglWObj *pSnglWObj = (SnglWObj *) GetWObjByOMName(szOMName);
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddBox(szOMName, boxName, params);
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
LONG ListWMng::AddCircle(char *szOMName, char *cirName, POINT *pointst)
{
	SnglWObj *pSnglWObj = (SnglWObj *) GetWObjByOMName(szOMName);
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddCircle(szOMName, cirName, pointst);
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
LONG ListWMng::AddPolygon(char *szOMName, char *pgName, POINT *pointArray, int nofpct)
{
	SnglWObj *pSnglWObj = (SnglWObj *) GetWObjByOMName(szOMName);
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddPolygon(szOMName, pgName, pointArray, nofpct); //, color, bcolor, szCText
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
LONG ListWMng::AddGroup(char *wName, char *gName)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wName );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddGroup("", gName);
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
LONG ListWMng::AddPolyLine(char *szOMName, char *plName, POINT *pointArray, int nofpct)
{
	SnglWObj *pSnglWObj = (SnglWObj *) GetWObjByOMName(szOMName);
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddPolyLine(szOMName, plName, pointArray, nofpct);
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
LONG ListWMng::GobjChgColors(char* wndName, char *grpName, char *objName, LONG bcolor, LONG color)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndName );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->GobjChgColors(grpName, objName, bcolor, color);
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
	int retval = 1;
	while(pListItem != NULL)
	{
		SnglWObj *pGObj = (SnglWObj *)pListItem->LpvCls;
		pGObj->SaveWindowObjects(dst);
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
		LONG x, y, width, hight, bkcolor;
		char szWName[30];//, *pWName;
		*src >> szWName;//windows Name
		*src >> x;//x
		*src >> y;//y
		*src >> width;//long
		*src >> hight;//hight
		*src >> bkcolor;//color
		LONG objID = AddView(szWName, m_hparentW);
		if( objID == -1) // the ID is not deleted
			return false;
		SetBounds(szWName , x , y, width, hight);
		SetBackgroundColor(szWName, bkcolor);
		SetVisible(szWName, 1);
		SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( objID );
		pSnglWObj->LoadWindowObjects(src, readBuf);
		Refresh(szWName);
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
BOOL ListWMng::ChangeTxt(char *wndName, char *grpName, char *txtoName, LPSTR szText)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndName );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->ChangeTxt(grpName, txtoName, szText);
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
BOOL ListWMng::TakeNextCommentStr(char *wndName, char *grName, char *oName, LPSTR CommentStr)
{
	SnglWObj *pGObj;
	if(oName[0] == '\0')
		pGObj = (SnglWObj *)SWOlist.GetNextClsPtr(wndName);
	else
		pGObj = (SnglWObj *)SWOlist.GetHandle(*wndName);
	return pGObj->TakeNextCmtS(grName, oName, CommentStr);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-14 luci 1.0 New
**********************************************************************/
BOOL ListWMng::MoveClientW(char *wndName, LONG x, LONG y)
{
	SnglWObj *pSnglWObj = (SnglWObj *) SWOlist.GetHandle( wndName );
	if(IsWindow(pSnglWObj->m_clsWnd))
	{
		pSnglWObj->MoveW(x, y);
		return 1;
	}
	else
		return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-14 luci 1.0 New
**********************************************************************/
BOOL ListWMng::IsObject(char *objName){
	SnglWObj *pGObj;
	Node *wNode = SWOlist.GetFirstItem();
	while(wNode){
		if( strcmp(wNode->strnID, objName) == 0)
			return TRUE;
		pGObj = (SnglWObj *) wNode->LpvCls;
		if(pGObj->IsObject(objName))
			return TRUE;
		wNode = SWOlist.GetNextItem(wNode);
	}
	return FALSE;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-26 luci 1.0 New
**********************************************************************/
void * ListWMng::GetWObjByOMName(char *szOMName)
{
	SnglWObj *pGObj;
	Node *wNode = SWOlist.GetFirstItem();
	while(wNode){
		if( strcmp(wNode->strnID, szOMName) == 0)
			return wNode->LpvCls;
		pGObj = (SnglWObj *) wNode->LpvCls;
		if(pGObj->IsObject(szOMName))
			return wNode->LpvCls;
		wNode = SWOlist.GetNextItem(wNode);
	}
	return NULL;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-26 luci 1.0 New
**********************************************************************/
BOOL ListWMng::AddTube(char *szOMName, char *tubName, POINT *data, LPSTR szCText)
{
	SnglWObj *pSnglWObj = (SnglWObj *)GetWObjByOMName(szOMName);//(SnglWObj *) SWOlist.GetHandle( twndName );
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddTub(szOMName, tubName, data, szCText);
	}
	else
		return -1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-26 luci 1.0 New
**********************************************************************/
BOOL ListWMng::AddPress(char *szOMName, char *presName, POINT *data, LPSTR szCText)
{
	SnglWObj *pSnglWObj = (SnglWObj *)GetWObjByOMName(szOMName);//(SnglWObj *) SWOlist.GetHandle( twndName );
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddPress(szOMName, presName, data, szCText);
	}
	else
		return -1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-09-26 luci 1.0 New
**********************************************************************/
BOOL ListWMng::AddLogicalAnd(char *szOMName, char *lndName, POINT *params, LPSTR szCText)
{
	SnglWObj *pSnglWObj = (SnglWObj *)GetWObjByOMName(szOMName);//(SnglWObj *) SWOlist.GetHandle( twndName );
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddLogicalAnd(szOMName, lndName, params, szCText);
	}
	else
		return -1;

}


/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-04 luci 1.0 New
**********************************************************************/
BOOL ListWMng::AddMold(char *szOMName, char *moldName, POINT *data, LPSTR szCText)
{
	SnglWObj *pSnglWObj = (SnglWObj *)GetWObjByOMName(szOMName);//(SnglWObj *) SWOlist.GetHandle( twndName );
	if(pSnglWObj && IsWindow(pSnglWObj->m_clsWnd))
	{
		return pSnglWObj->AddMold(szOMName, moldName, data, szCText);
	}
	else
		return -1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
void ListWMng::SetEditMode(UCHAR bEditMode)
{
	SnglWObj *pGObj;
	Node *wNode = SWOlist.GetFirstItem();
	while(wNode){
		pGObj = (SnglWObj *) wNode->LpvCls;
		pGObj->SetEditMode(bEditMode);
		wNode = SWOlist.GetNextItem(wNode);
	}
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-06 luci 1.0 New
**********************************************************************/
BOOL ListWMng::GetSelectedObjInfo(void *objInfoStruct)
{
	SnglWObj *pGObj;
	Node *wNode = SWOlist.GetFirstItem();
	while(wNode){
		pGObj = (SnglWObj *) wNode->LpvCls;
		if(pGObj->GetSelectedObjInfo(objInfoStruct))
			return TRUE;
		wNode = SWOlist.GetNextItem(wNode);
	}
	return FALSE;
}
