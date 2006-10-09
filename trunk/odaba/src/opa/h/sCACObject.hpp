/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    CACObject

\brief    Database Object handle
          Database  Object  handle  (Object  handle) are necessary for accessing
          data  in an Database Object. It  allows accessing extents that contain
          the  main instances  in a  Database Object.  The object handle for the
          root  Database Object it the database  handle ({\b {.r DBHandle}}) and
          need not to be opened explicitly. 
          An  object handle is necessary for opening collection handles (PI) for
          accessing object instances stored in extents.  
          Moreover;  the object handle  administrates transactions. Transactions
          can be started and stopped for each object handle. 
          The  object handle  allows also  defining Database Object versions for
          creating and accessing version slices for a Database Object.

\date     $Date: 2006/08/26 12:07:26,56 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CACObject_HPP
#define   CACObject_HPP

class     CACObject;

#include  <sDLL.h>
class     CNode;
#ifndef   INTERVAL_dttm_HPP
#define   INTERVAL_dttm_HPP
#include  <sdttm.hpp>
#include  <sINTERVAL.h>
#endif
class     BNFData;
class     BNFExpData;
class     CACObject;
class     CClient;
class     CDBHandle;
class     CS_Connection;
class     ClientConnection;
class     DBExtend;
class     DBFieldDef;
class     DBHandle;
class     DBStructDef;
class     OperEnvironment;
class     node;
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <cResourceTypes.h>
#include  <sACObject.hpp>
#include  <sCSHandle.hpp>
#include  <sCSInstanceList.hpp>
#include  <sCS_Handle.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sEB_Number.hpp>
#include  <sODABAClient.hpp>
#include  <sdttm.hpp>
#pragma pack(8)

class  CACObject :public CSHandle,
public virtual ACObject
{
protected  :         CDBHandle                                   *cdbhandle;                                                 // Parent database object handle
protected  :         DLL(CNode)                                  *topnode_list;                                              // Database Handle

public     :
                     CDBHandle                                   *get_cdbhandle() { return(cdbhandle); }
                     DLL(CNode)                                  *get_topnode_list() { return(topnode_list); }
public     :                                             CACObject (DBHandle *dbhandle, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                                             CACObject (ACObject *obhandle, int32 objid, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                                             CACObject (ACObject *obhandle, char *objname, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                                             CACObject (CS_Connection *cs_connection );
public     :                                             CACObject ( );
public     : virtual                                logical ChangeTimeStamp (uint16 version_nr=CUR_VERSION, dttm timestamp=dttm() );
public     : virtual                                logical CloseObject ( );
public     : virtual                                node *CreateNode (DBExtend *dbextdef, PIACC accopt );
public     : virtual                                node *CreateNode (char *extnames, PIACC accopt );
public     : virtual                                node *CreatePathNode (char *prop_path, OperEnvironment *operenv, PIACC accopt );
public     : virtual                                node *CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv, PIACC accopt );
public     : virtual                                node *CreateTempNode (DBFieldDef *dbfield_def );
public     : virtual                                node *CreateTempNode (node *basenode );
public     : virtual                                node *CreateTempNode (node *basenode, char *grouping_rule );
public     : virtual                                logical DeleteExtent (char *extnames );
public     : virtual                                logical DeleteExtentRef (char *extnames );
public     : virtual                                logical ExecObjCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual                                logical ExtentExist (char *extnames );
public     : virtual                                PIACC GetAccess ( );
public     : virtual                                CACObject *GetClientACObject ( );
public     :                                        ClientConnection *GetClientConnect ( );
public     :                                        ODABAClient &GetConnectionClient ( );
public     : virtual                                char *GetExtent (int32 indx0 );
public     : virtual          OPAImpExp             GSRT(ExtentListEntry) *GetExtentList ( );
public     : virtual                                int16 GetModCount (EB_Number entnr );
public     : virtual                                int16 GetTALevel ( );
public     : virtual                                dttm GetTimeStamp (uint16 version_nr=CUR_VERSION );
public     : virtual                                uint16 GetVersion (dttm timestamp=dttm() );
public     :                                        void InitHandle (logical alloc_buffer=YES );
public     : virtual                                logical NewVersion (dttm timestamp=dttm(), uint16 version_nr=CUR_VERSION );
public     :                                        logical PopResult ( );
public     :                                        logical PushResult ( );
public     : virtual                                logical SetOverload (logical overload_opt );
public     : virtual                                logical SetUserDefinedIdentity (logical identity_opt );
public     : virtual                                logical SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                                logical SetVersion (dttm timestamp=dttm() );
public     : virtual                                logical SetVersion (dbdt date );
public     : virtual                                int16 StartTA (logical ext_TA, int16 w_maxnum=AUTO );
public     : virtual                                logical StopTA (int16 talevel=AUTO, logical error_case_w=NO );
public     :                                        void UninitHandle ( );
public     : virtual                                logical UpdateTimestamp (logical timestamp_enabled );
public     : virtual                                int32 VersionCount ( );
public     : virtual                                INTERVAL(dttm) VersionIntervall (uint16 version_nr=CUR_VERSION );
public     : virtual                                     ~CACObject ( );
};

#pragma pack()
#endif
