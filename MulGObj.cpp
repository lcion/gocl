// MulGObj.cpp: implementation of the MulGObj class.
//
//////////////////////////////////////////////////////////////////////

#include "MulGObj.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
MulGObj::MulGObj( int ObjId, HWND hclsWnd):SnglGObj(ObjId)
{
	m_clsWnd = hclsWnd;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
MulGObj::~MulGObj()
{
	Node *pListItem = grpOList.GetFirstItem();
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		delete(pGObj);
		pListItem = pListItem->next;
	}
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int MulGObj::AddText(LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	if(grpOList.CheckNewID(txtID) == -1)
		return -1;
	GTxtO *pGobj = new GTxtO(txtID);
	pGobj->Create(m_clsWnd, szText, x, y, color, bcolor, szCText);
//	LONG theID = grpOList.GetNewID();	void Create(HWND m_clsWnd, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
	grpOList.AddNode(txtID, pGobj);
	return txtID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL MulGObj::SetTextFont(LONG txtoId, LPSTR fName, int fsize, int fattrib)
{
	GTxtO *gtxtO = (GTxtO*) grpOList.GetHandle(txtoId);
	gtxtO->SetFont(fName, fsize, fattrib);
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int MulGObj::MoveTo(LONG txtoId, POINT point)
{
	if(txtoId != ALL_OBJS)
	{
		SnglGObj *gtxtO = (SnglGObj*) grpOList.GetHandle(txtoId);
		return gtxtO->MoveTo(m_clsWnd, point);
	}
	Node *pListItem = grpOList.GetFirstItem();
	int retval=1;
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		if(pGObj->MoveTo(m_clsWnd, point) == -1) retval = -1;
		pListItem = pListItem->next;
	}
	return retval;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int MulGObj::Move(LONG txtoId, POINT point)
{
	if(txtoId != ALL_OBJS)
	{
		SnglGObj *gtxtO = (SnglGObj*) grpOList.GetHandle(txtoId);
		return gtxtO->Move(m_clsWnd, point);
	}
	Node *pListItem = grpOList.GetFirstItem();
	int retval=1;
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		if(pGObj->Move(m_clsWnd, point) == -1) retval = -1;
		pListItem = pListItem->next;
	}
	return retval;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int MulGObj::AddBox(LONG boxID, POINT *params)
{
	if(grpOList.CheckNewID(boxID) == -1)
		return -1;
	GBoxO *pGobj = new GBoxO(boxID);
	pGobj->Create(params);
	grpOList.AddNode(boxID, pGobj);
	return boxID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddCircle(LONG cirID, POINT *pointst)
{
	if(grpOList.CheckNewID(cirID) == -1)
		return -1;
	GCircleO *pGobj = new GCircleO(cirID);
	pGobj->Create(pointst);
	grpOList.AddNode(cirID, pGobj);
	return cirID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddPolygon(LONG pgID, POINT *pointArray, int nofpct) //, LONG color, LONG bcolor, LPSTR szCText
{
	if(grpOList.CheckNewID(pgID) == -1)
		return -1;
	GPolygO *pGobj = new GPolygO(pgID);
	pGobj->Create(pointArray, nofpct);//, color, bcolor, szCText
	grpOList.AddNode(pgID, pGobj);
	return pgID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void MulGObj::Redraw(HDC memHdc)
{
	Node *pListItem = grpOList.GetFirstItem();
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
LONG MulGObj::AddPolyLine(LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR szCText)
{
	if(grpOList.CheckNewID(plID) == -1)
		return -1;
	GPolyLO *pGobj = new GPolyLO(plID);
	pGobj->Create(pointArray, nofpct, color, szCText);
	grpOList.AddNode(plID, pGobj);
	return plID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
LONG MulGObj::GobjChgColors(LONG objID, LONG bcolor, LONG color)
{
	if(objID != ALL_OBJS)
	{
		SnglGObj *gobj = (SnglGObj*) grpOList.GetHandle(objID);
		return gobj->GobjChgColors(bcolor, color);
	}
	Node *pListItem = grpOList.GetFirstItem();
	int retval=1;
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
//		if(pGObj->GobjChgColors(bcolor, color) == -1) retval = -1;
		pGObj->GobjChgColors(bcolor, color);
		pListItem = pListItem->next;
	}
	return retval;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL MulGObj::Save(ofstream *dst, LONG nID)
{
	Node *pListItem = grpOList.GetFirstItem();
	int retval = 1;
	*dst << "BGRP " << nID << endl;
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		pGObj->Save(dst, pListItem->nID);
		pListItem = pListItem->next;
	}
	*dst << "EGRP" << endl;
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddRez(LONG rezID, POINT *data, LPSTR szCText)
{
	if(grpOList.CheckNewID(rezID) == -1)
		return -1;
	GRezO *pGobj = new GRezO(rezID);
	pGobj->Create(data, szCText);
	grpOList.AddNode(rezID, pGobj);
	return rezID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddPress(LONG presID, POINT *data, LPSTR szCText)
{
	if(grpOList.CheckNewID(presID) == -1)
		return -1;
	GPresO *pGobj = new GPresO(presID);
	pGobj->Create(data, szCText);
	grpOList.AddNode(presID, pGobj);
	return presID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
void MulGObj::ChangeTxt(LONG txtoId, LPSTR szText)
{
	GTxtO *gtxtO = (GTxtO*) grpOList.GetHandle(txtoId);
	gtxtO->ChangeTxt(m_clsWnd,szText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
int MulGObj::AddLogicalAnd(LONG landID, POINT *params, LPSTR szCText)
{
	if(grpOList.CheckNewID(landID) == -1)
		return -1;
	GLndO *pGobj = new GLndO(landID);
	pGobj->Create(params, szCText);
	grpOList.AddNode(landID, pGobj);
	return landID;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL MulGObj::TakeCmtS(LONG *gid, LONG *oid, LPSTR CommentStr)
{
	SnglGObj *pGObj;
	pGObj = (SnglGObj *)grpOList.GetNextClsPtr(oid);
	while(pGObj && false == pGObj->TakeCmtS(gid, oid, CommentStr))
		pGObj = (SnglGObj *)grpOList.GetNextClsPtr(oid);
	if(pGObj)
		return true;
	else
		return false;
}
/*	if(*oid == -1)
		pGObj = (SnglGObj *)grpOList.GetNextClsPtr(oid);
	else
		pGObj = (SnglGObj *)grpOList.GetHandle(*oid);
*/

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-27 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddMold(LONG moldID, POINT *params, LPSTR szCText)
{
	if(grpOList.CheckNewID(moldID) == -1)
		return -1;
	GMoldO *pGobj = new GMoldO(moldID);
	pGobj->Create(params, szCText);
	grpOList.AddNode(moldID, pGobj);
	return moldID;
}
