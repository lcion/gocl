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


class Lista  
{
public:
	void * GetNextClsPtr(LONG *nID);
	LONG CheckNewID(LONG wID);
	Node * GetNextItem(Node *lastItem);
	Node * GetFirstItem();
	int DelItem( LONG hidx );
	void * GetHandle( LONG Id );
	void * GetHandle( char *strId );
	LONG GetNewID();
	Node * head;
	int Count();
	void DelList(Node *sbtree);
	void InitLst();
	void AddNode(int cds, LPVOID id_geo);
	Lista();
	virtual ~Lista();

};

#endif // !defined(AFX_LISTA_H__03132F34_3B57_11D3_8F67_4854E82A6CCB__INCLUDED_)
