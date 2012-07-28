/* Node.cpp *******************************************************
*	 Description: implementation of the Node class.
*
*	Functions:
*		Node::Node
*		Node::~Node
*		
*		
*		
*	Revision:
*
**********************************************************************/

#include "Node.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/*********************************************************************
* Description:Construction
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
Node::Node(){
	next = NULL;
	LpvCls = NULL;
	strnID = NULL;
}

/*********************************************************************
* Description:Destruction
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
Node::~Node(){
}
