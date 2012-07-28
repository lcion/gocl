// ObjTentry.h: interface for the ObjTentry class.
//
//////////////////////////////////////////////////////////////////////
#include <fstream>
#include "windows.h"

#if !defined(AFX_OBJTENTRY_H__4B2F5E91_4E80_11D4_9D43_00C0DF042790__INCLUDED_)
#define AFX_OBJTENTRY_H__4B2F5E91_4E80_11D4_9D43_00C0DF042790__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ObjTentry  
{
public:
	char* m_objName;
	int m_objId;
	ObjTentry(int id, char* name);
	virtual ~ObjTentry();

};

#endif // !defined(AFX_OBJTENTRY_H__4B2F5E91_4E80_11D4_9D43_00C0DF042790__INCLUDED_)
