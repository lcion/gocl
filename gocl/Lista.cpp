/* Lista.cpp *******************************************************
*	 Description: implementation of the Lista class
*
*	Functions:
*		Lista::Lista
*		Lista::~Lista
*		Lista::InitLst
*		Lista::AddNode
*		Lista::DelList
*		Lista::Count
*		Lista::GetNewID
*		Lista::GetHandle
*		Lista::DelItem
*		Lista::GetFirstItem
*		Lista::GetNextItem
*		Lista::CheckNewID
*		Lista::GetNextClsPtr
*		Lista::GetNextClsPtr
*		Lista::GetPreviousItem
*		
*		
*	Revision:
*		2000-10-05 luci 1.0 New
**********************************************************************/

#include "Lista.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

/*********************************************************************
* Description: Construction
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
Lista::Lista(){
	head = NULL;
}

/*********************************************************************
* Description:Destruction
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
void Lista::AddNode(char *cds, LPVOID lpvCls){
	Node *pnNod;
	Node *tmp;
	pnNod = new Node;
	pnNod->LpvCls = lpvCls;
//	pnNod->nID = cds;
	pnNod->strnID = new char[strlen(cds)+1];
	strcpy_s(pnNod->strnID, strlen(cds)+1, cds);
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
	delete sblist->strnID;
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
int Lista::DelItem(char *itemName)
{
	Node *tmp, *tmp1;

	for(tmp1 = tmp = head; tmp->next != NULL && strcmp(tmp->strnID, itemName) != 0; tmp = tmp->next)tmp1 = tmp;
	if(strcmp(tmp->strnID, itemName) == 0)
	{
		if(tmp == head)
		{
			head = head->next;
			delete tmp->strnID;
			delete tmp;
		}
		else
		{
			tmp1->next = tmp->next;
			delete tmp->strnID;
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

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
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

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
void * Lista::GetNextClsPtr(char *nName)
{
	if(head==NULL)
		return NULL;
	if(nName[0] == '\0')
	{
		strcpy_s(nName, CMNT_BUFF, head->strnID);
		return head->LpvCls;
	}
	Node *tmp;
	for(tmp = head; tmp->next != NULL && strcmp(tmp->strnID, nName) !=0 ; tmp = tmp->next);
	if(strcmp(tmp->strnID, nName) ==0  && tmp->next)
	{
		strcpy_s(nName, CMNT_BUFF, tmp->next->strnID);
		return tmp->next->LpvCls;
	}
	else
	{
		return NULL;
	}
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
Node *Lista::GetLastItem()
{
	if(head==NULL)
		return NULL;
	Node *tmp;
	for(tmp = head; tmp->next != NULL ; tmp = tmp->next);
	return tmp;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
Node * Lista::GetPreviousItem(Node *crtItem)
{
	if(head == crtItem || head == NULL)
		return NULL;
	Node *tmp;
	for(tmp = head; tmp->next != NULL && tmp->next != crtItem; tmp = tmp->next);
	return tmp;
}
