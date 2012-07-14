// Lista.cpp: implementation of the Lista class.
//
//////////////////////////////////////////////////////////////////////

#include "Lista.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
Lista::Lista(){
	head = NULL;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
Lista::~Lista(){
	InitLst();
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void Lista::InitLst(){
	if(head)
		DelList(head);
	head = NULL;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void Lista::AddNode(int cds, LPVOID lpvCls){
	Node *pnNod;
	Node *tmp;
	pnNod = new Node;
	pnNod->LpvCls = lpvCls;
	pnNod->nID = cds;
	if(head == NULL){
		head = pnNod;
		return;
	}
	for(tmp = head; tmp->next != NULL; tmp = tmp->next);
	tmp->next = pnNod;
}
//Lista::AddNode

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void Lista::DelList(Node *sblist){
	if(sblist->next) DelList(sblist->next);
	delete sblist;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int  Lista::Count(){
	Node *tmp;
	int index;
	for(tmp = head, index = 0; tmp->next != NULL; tmp = tmp->next, index++);
	return index;
}


/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG Lista::GetNewID()
{
	Node *tmp;
	if(head)
		for(int i=0; i < 65535; i++)
		{
			for(tmp = head; tmp->next != NULL && tmp->nID != i; tmp = tmp->next);
			if(tmp->nID != i)
				return i;
		}
	return 0;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void * Lista::GetHandle(LONG Id)
{
	Node *tmp;
	if(head){
		for(tmp = head; tmp->next != NULL && tmp->nID != Id; tmp = tmp->next);
		return tmp->LpvCls;
	}
	return NULL;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-03 luci 1.0 New
**********************************************************************/
void * Lista::GetHandle(char *strId)
{
	Node *tmp;
	if(head){
		for(tmp = head; tmp->next != NULL && strcmp(tmp->strnID, strId) != 0; tmp = tmp->next);
		return tmp->LpvCls;
	}
	return NULL;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int Lista::DelItem(LONG hidx)
{
	Node *tmp, *tmp1;

	for(tmp1 = tmp = head; tmp->next != NULL && tmp->nID != hidx; tmp = tmp->next)tmp1 = tmp;
	if(tmp->nID == hidx)
	{
		if(tmp == head)
		{
			head = head->next;
			delete tmp;
		}
		else
		{
			tmp1->next = tmp->next;
			delete tmp;
		}
	return 1;
	}
	return 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
Node * Lista::GetFirstItem()
{
	if(head)
		return head;
	return NULL;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
Node * Lista::GetNextItem(Node *lastItem)
{
	if(lastItem && lastItem->next)
		return lastItem->next;
	return NULL;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
LONG Lista::CheckNewID(LONG wID)
{
	if(!head)
		return wID;
	Node *tmp;
	for(tmp = head; tmp->next != NULL && tmp->nID != wID; tmp = tmp->next);
	if(tmp->nID != wID)
		return wID;
	else
		return -1;
}

void * Lista::GetNextClsPtr(LONG *nID)
{
	if(head==NULL)
		return NULL;
	if(*nID == -1)
	{
		*nID = head->nID;
		return head->LpvCls;
	}
	Node *tmp;
	for(tmp = head; tmp->next != NULL && tmp->nID != *nID; tmp = tmp->next);
	if(tmp->nID == *nID && tmp->next)
	{
		*nID = tmp->next->nID;
		return tmp->next->LpvCls;
	}
	else
	{
		*nID = -1;
		return NULL;
	}
}
