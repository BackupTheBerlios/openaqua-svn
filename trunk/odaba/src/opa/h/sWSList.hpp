/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    WSList

\brief    


\date     $Date: 2006/03/12 19:13:56,89 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   WSList_HPP
#define   WSList_HPP

class     WSList;

class     DBHandle;
class     eb_RootBase;
#include  <sSDB_Workspace.hpp>
#include  <sWorkspaceEntry.hpp>
#include  <smvld.hpp>
#pragma pack(8)

class  WSList :public mvld
{

public     :
public     :                                     logical Add (SDB_Workspace &wsentry );
public     :                                     logical Delete (int32 lindx0 );
public     :                                     logical Delete (char *wsname );
public     :                                     logical Exist (SDB_Workspace &wsentry );
public     :                                     SDB_Workspace *Get (SDB_Workspace &wsentry );
public     :                                     SDB_Workspace *Get (char *wsname );
public     :                                     SDB_Workspace *Get (int32 lindx0 );
public     : virtual                             logical Refresh ( );
public     :                                                             WSList (DBHandle *dbhandle );
public     :                                                             WSList (db_RootBase *rootbase, DBHandle *dbhandle );
public     :                                                             ~WSList ( );
};

#pragma pack()
#endif
