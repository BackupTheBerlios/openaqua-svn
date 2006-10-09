/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    Workspace

\brief    Workspace
          A  workspace is implemented  as overlay rootbase  on top of a database
          or another workspace.

\date     $Date: 2006/03/12 19:13:57,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Workspace_HPP
#define   Workspace_HPP

class     Workspace;

class     DBHandle;
class     EBI;
class     acb;
class     srt;
#include  <sEB_Number.hpp>
#include  <sRootBaseTA.hpp>
#include  <sTABuffer.hpp>
#include  <seb_RootBase.hpp>
#pragma pack(8)

class  Workspace :public TABuffer,
public eb_RootBase
{
protected  :         db_RootBase                                 *root_base ATTR_ALIGN(4);                                   
protected  :         char                                        *ws_name;                                                   
protected  :         logical                                      is_empty;                                                  
protected  :         int32                                        ws_number;                                                 

public     :
                     db_RootBase                                 *get_root_base() { return(root_base); }
                     char                                        *get_ws_name() { return(ws_name); }
                     logical                                      get_is_empty() { return(is_empty); }
                     int32                                        get_ws_number() { return(ws_number); }
public     : virtual                             logical CheckEBI (acb *acbptr );
public     : virtual                             uint8 Check_WProtect (acb *acbptr );
public     : virtual                             db_RootBase *Close ( );
public     : virtual                             logical CloseRecursive ( );
public     : virtual                             logical Consolidate ( );
public     :                                     logical ConsolidateDiffList (exd *exdptr );
public     :                                     logical ConsolidateWSEntry (exd *exdptr );
public     :                                     EB_Number Create (acb *acbptr );
public     :                                     EB_Number Create (EB_Number clnumb, int16 mbnumber, uint16 sbnumber, uint16 version_nr=CUR_VERSION );
public     : virtual                             logical Delete (acb *acbptr );
public     :                                     logical DeleteWSEntry (acb *acbptr );
public     : virtual                             logical Discard ( );
public     : virtual                             logical ExistEBI (acb *acbptr );
public     : virtual                             logical Flush ( );
public     : virtual                             EBI *GetEBI (acb *acbptr );
public     : virtual                             int16 GetMBNumber (EB_Number entnr );
public     : virtual                             db_RootBase *GetRootBase (uint8 wslevel );
public     : virtual                             int32 Get_Length (acb *acbptr );
public     :                                     uint8 Get_Mod (acb *acbptr );
public     :                                     logical IsEmpty ( );
public     : virtual                             logical IsWorkspace ( );
public     : virtual                             void *Locate (acb *acbptr, int32 entlen );
public     : virtual                             logical Lock (acb *acbptr, logical wait );
public     : virtual                             logical LockInternal (acb *acbptr, logical wait );
public     : virtual                             logical ProvideWSEntry (acb *acbptr, logical del_opt );
public     : virtual                             logical ReleaseEntry (acb *acbptr );
public     : virtual                             logical ReleaseWSEntry (acb *acbptr );
public     :                                     logical Remove ( );
public     : virtual                             logical Reserve (acb *acbptr, logical wait );
public     : virtual                             logical ReserveEntry (acb *acbptr );
public     : virtual                             logical ReserveWSEntry (acb *acbptr );
public     : virtual                             logical SaveBuffer ( );
public     : virtual                             logical Unlock (acb *acbptr );
public     : virtual                             logical UnlockInternal (acb *acbptr );
public     : virtual                             logical Update (acb *acbptr, int32 entlen, int32 offset );
public     :                                                             Workspace (DBHandle *dbhandle, char *ws_names, char *cpath, logical exclusive, uint8 ws_level );
public     : virtual                                                     ~Workspace ( );
};

#pragma pack()
#endif
