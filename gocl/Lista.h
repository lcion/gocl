// Lista.h: interface for the Lista class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTA_H__03132F34_3B57_11D3_8F67_4854E82A6CCB__INCLUDED_)
#define AFX_LISTA_H__03132F34_3B57_11D3_8F67_4854E82A6CCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Node.h"

#define TXTID  0
#define GRAPHID 1
#define ANNYID 2

#define SMALL_BUFF 20
#define CMNT_BUFF 100

class Lista  
{
public:
//first node in the list
	Node * head;
//Get Previous Node Item
	Node * GetPreviousItem(Node *crtItem);
//Get Last node Item from the list
	Node *GetLastItem();
//Get Next Class Pointer using the current node name
	void * GetNextClsPtr(char *nName);
//Get Next Class Pointer using the current node Identifier
	void * GetNextClsPtr(LONG *nID);
//Check New IDentifier for unic in list
	LONG CheckNewID(LONG wID);
//Get Next Node Item
	Node * GetNextItem(Node *lastItem);
//Get First Node Item in list
	Node * GetFirstItem();
//Delete Item specified by Identifier
	int DelItem( LONG hidx );
//Get Handle to the stored information using Node Identifier
	void * GetHandle( LONG Id );
//Get Handle to the stored information using Node name
	void * GetHandle( char *strId );
//Return next free identifier
	LONG GetNewID();
//Return the number of items from the list
	int Count();
//delete the list starting with the specified node
	void DelList(Node *sbtree);
//Delete the specified node using the node name
	int DelItem(char *itemName);
//Initialise the list
	void InitLst();
//Add a node to the list with name as node identifier
	void AddNode(char *cds, LPVOID lpvCls);
//Add a node to the list with ID as node identifier
	void AddNode(int cds, LPVOID id_geo);
//constructor
	Lista();
//destructor
	virtual ~Lista();

};

#endif // !defined(AFX_LISTA_H__03132F34_3B57_11D3_8F67_4854E82A6CCB__INCLUDED_)
