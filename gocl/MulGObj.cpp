/* MulGObj.cpp *******************************************************
*	 Description: implementation of the MulGObj class.
*
*	Functions:
*		MulGObj::MulGObj
*		MulGObj::~MulGObj
*		MulGObj::AddText
*		MulGObj::SetTextFont
*		MulGObj::MoveTo
*		MulGObj::Move
*		MulGObj::AddBox
*		MulGObj::AddCircle
*		MulGObj::AddPolygon
*		MulGObj::Redraw
*		MulGObj::AddPolyLine
*		MulGObj::GobjChgColors
*		MulGObj::Save
*		MulGObj::AddTub
*		MulGObj::AddPress
*		MulGObj::ChangeTxt
*		MulGObj::AddLogicalAnd
*		MulGObj::TakeCmtS
*		MulGObj::AddMold
*		MulGObj::IsObject
*		MulGObj::DeleteGObject
*		MulGObj::SelectGObject
*		
*	Revision:
*		2000-10-05 luci 1.0 New
**********************************************************************/

#include "MulGObj.h"


/*********************************************************************
* Description:Construction
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
MulGObj::MulGObj( char *ObjName, HWND hclsWnd):SnglGObj(ObjName)
{
	m_clsWnd = hclsWnd;
}

/*********************************************************************
* Description:Destruction
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
int MulGObj::AddText(char* txtName, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	GTxtO *pGobj = new GTxtO(txtName);
	pGobj->Create(m_clsWnd, szText, x, y, color, bcolor, szCText);
	grpOList.AddNode(txtName, pGobj);
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL MulGObj::SetTextFont(char *txtOName, LPSTR fName, int fsize, int fattrib)
{
	GTxtO *gtxtO = (GTxtO*) grpOList.GetHandle(txtOName);
	gtxtO->SetFont(fName, fsize, fattrib);
	return true;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int MulGObj::MoveTo(char *txtoName, POINT point)
{
	if(txtoName[0] != '\0')
	{
		SnglGObj *gtxtO = (SnglGObj*) grpOList.GetHandle(txtoName);
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
int MulGObj::Move(char *txtoName, POINT point)
{
	if(txtoName[0] != '\0')
	{
		SnglGObj *gtxtO = (SnglGObj*) grpOList.GetHandle(txtoName);
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
int MulGObj::AddBox(char *boxName, POINT *params)
{
/*	if(grpOList.CheckNewID(boxID) == -1)
		return -1;*/
	GBoxO *pGobj = new GBoxO(boxName);
	pGobj->Create(params);
	grpOList.AddNode(boxName, pGobj);
//	return boxID;
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddCircle(char *cirName, POINT *pointst)
{
/*	if(grpOList.CheckNewID(cirID) == -1)
		return -1;*/
	GCircleO *pGobj = new GCircleO(cirName);
	pGobj->Create(pointst);
	grpOList.AddNode(cirName, pGobj);
//	return cirID;
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddPolygon(char *pgName, POINT *pointArray, int nofpct) //, LONG color, LONG bcolor, LPSTR szCText
{
	GPolygO *pGobj = new GPolygO(pgName);
	pGobj->Create(pointArray, nofpct);//, color, bcolor, szCText
	grpOList.AddNode(pgName, pGobj);
	return 1;
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
LONG MulGObj::AddPolyLine(char *plName, POINT *pointArray, int nofpct)
{
	GPolyLO *pGobj = new GPolyLO(plName);
	pGobj->Create(pointArray, nofpct);
	grpOList.AddNode(plName, pGobj);
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
LONG MulGObj::GobjChgColors(char *objName, LONG bcolor, LONG color)
{
	if(objName != '\0')
	{
		SnglGObj *gobj = (SnglGObj*) grpOList.GetHandle(objName);
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
BOOL MulGObj::Save(ofstream *dst)
{
	Node *pListItem = grpOList.GetFirstItem();
	int retval = 1;
	*dst << "BGRP " << m_GOName << endl;
	while(pListItem != NULL)
	{
		SnglGObj *pGObj = (SnglGObj *)pListItem->LpvCls;
		pGObj->Save(dst);
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
LONG MulGObj::AddTub(char *tubName, POINT *data, LPSTR szCText)
{
	GTubO *pGobj = new GTubO(tubName);
	pGobj->Create(data, szCText);
	grpOList.AddNode(tubName, pGobj);
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddPress(char *presName, POINT *data, LPSTR szCText)
{
	GPresO *pGobj = new GPresO(presName);
	pGobj->Create(data, szCText);
	grpOList.AddNode(presName, pGobj);
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
void MulGObj::ChangeTxt(char *txtoName, LPSTR szText)
{
	GTxtO *gtxtO = (GTxtO*) grpOList.GetHandle(txtoName);
	gtxtO->ChangeTxt(m_clsWnd,szText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
int MulGObj::AddLogicalAnd(char *landName, POINT *params, LPSTR szCText)
{
	GLndO *pGobj = new GLndO(landName);
	pGobj->Create(params, szCText);
	grpOList.AddNode(landName, pGobj);
	return 1;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL MulGObj::TakeCmtS(char *gName, char *oName, LPSTR CommentStr)
{
	SnglGObj *pGObj;
	pGObj = (SnglGObj *)grpOList.GetNextClsPtr(oName);
	while(pGObj && false == pGObj->TakeCmtS(gName, oName, CommentStr))
		pGObj = (SnglGObj *)grpOList.GetNextClsPtr(oName);
	if(pGObj)
		return true;
	else
		return false;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-27 luci 1.0 New
**********************************************************************/
LONG MulGObj::AddMold(char *moldName, POINT *params, LPSTR szCText)
{
	GMoldO *pGobj = new GMoldO(moldName);
	pGobj->Create(params, szCText);
	grpOList.AddNode(moldName, pGobj);
	return 1;
}

/*********************************************************************
* Description: IsObject
*   
* Revision:
* 2000-03-27 luci 1.0 New
**********************************************************************/
BOOL MulGObj::IsObject(char *objName)
{
	if(SnglGObj::IsObject(objName))
		return TRUE;
	SnglGObj *pGObj;
	Node *gNode = grpOList.GetFirstItem();
	while(gNode){
		if( strcmp(gNode->strnID, objName) == 0)
			return TRUE;
		pGObj = (SnglGObj *) gNode->LpvCls;
		if(pGObj->IsObject(objName))
			return TRUE;
		gNode = grpOList.GetNextItem(gNode);
	}
	return FALSE;
}

/*********************************************************************
* Description: DeleteGObject
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
BOOL MulGObj::DeleteGObject(char *objName)
{
	SnglGObj *pGObj;
	Node *gNode = grpOList.GetFirstItem();
	while(gNode){
		pGObj = (SnglGObj *) gNode->LpvCls;
		if( strcmp(gNode->strnID, objName) == 0){
			grpOList.DelItem( objName );
			delete pGObj;
			return TRUE;
		}
		if(pGObj->DeleteGObject(objName))
			return TRUE;
		gNode = grpOList.GetNextItem(gNode);
	}
	return FALSE;
}

/*********************************************************************
* Description: SelectGObject
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
BOOL MulGObj::SelectGObject(UINT x, UINT y)
{
	SnglGObj *pGObj;
	Node *gNode = grpOList.GetLastItem();
	while(gNode){
		pGObj = (SnglGObj *) gNode->LpvCls;
		if(pGObj->SelectGObject(x, y))
			return TRUE;
		gNode = grpOList.GetPreviousItem(gNode);
	}
	return FALSE;
}

BOOL MulGObj::GetSelectedObjInfo(void *objInfoStruct)
{
	SnglGObj *pGObj;
	OBJINFO * pObjInf =(OBJINFO *)objInfoStruct;
	Node *gNode = grpOList.GetFirstItem();
	while(gNode){
		pGObj = (SnglGObj *) gNode->LpvCls;
		if(pGObj->GetSelectedObjInfo(objInfoStruct))
		{
			if(!pObjInf->strOMName)
				pObjInf->strOMName = m_GOName;
			return TRUE;
		}
		gNode = grpOList.GetNextItem(gNode);
	}
	return FALSE;
}
