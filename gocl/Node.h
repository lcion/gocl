// Node.h: interface for the Node class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__03132F31_3B57_11D3_8F67_4854E82A6CCB__INCLUDED_)
#define AFX_NODE_H__03132F31_3B57_11D3_8F67_4854E82A6CCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define DATA_TYPE LPVOID
#include "windows.h"
class Node  
{
public:
	char * strnID;
	int nID;
	DATA_TYPE LpvCls;
	Node * next;
	Node();
	virtual ~Node();

};

#endif // !defined(AFX_NODE_H__03132F31_3B57_11D3_8F67_4854E82A6CCB__INCLUDED_)
