/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    isel

\brief    


\date     $Date: 2006/06/29 13:07:00,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   isel_HPP
#define   isel_HPP

class     isel;

#define  Lnodeptr                                  ((LNode *)nodeptr)
class     ACObject;
class     DBStructDef;
class     StructAccess;
class     guid;
class     inti;
class     node;
#include  <sEB_Number.hpp>
#include  <sEntryHandle.hpp>
#include  <sbinti.hpp>
#pragma pack(8)

class  isel :public binti,
public EntryHandle
{

public     :
public     : virtual                                logical Add (logical global_add=NO );
public     : virtual                                logical AddGenericRef (char *fldname );
public     : virtual                                logical Cancel ( );
public     :                                        logical CheckDBInstance (NString &nresult, CheckOptions check_opts );
public     : virtual                                uint8 CheckWProtect ( );
public     : virtual                                logical Close ( );
public     : virtual          OPAImpExp             logical CopyBufferInstance (inti *intiptr );
public     : virtual                                logical CreateGUID (guid *_guid );
public     : virtual                                logical DelGenericRef (char *fldname );
public     : virtual                                logical Delete (char *extnames, logical is_root, int16 delopt=AUTO );
public     : virtual                                logical DeleteInstance ( );
public     : virtual                                logical Get (EB_Number entnr );
public     : virtual                                logical Get (char *extinst );
public     : virtual          OPAImpExp             EB_Number GetClusterNumber ( );
public     :                                        logical GetData (node *nodeptr );
public     : virtual          OPAImpExp             char *GetExtInst ( );
public     : virtual                                EB_Number GetID (int32 w_indx0=-1 );
public     : virtual          OPAImpExp             int16 GetMBNumber ( );
public     : virtual                                int16 GetModCount ( );
public     :                                        ACObject *GetOBHandle ( );
public     : virtual                                char *GetOldInst (void *oldinst );
public     : virtual                                int16 GetSID (EB_Number entnr );
public     : virtual          OPAImpExp             StructAccess *GetStructAccess ( );
public     : virtual                                uint16 GetVersion ( );
public     :                                        logical IsInWork ( );
public     : virtual                                logical IsNewInstance ( );
public     : virtual                                logical IsPositioned ( );
public     :                                        int8 IsReserved ( );
public     : virtual                                logical Lock ( );
public     : virtual          OPAImpExp             logical MoveInstance (inti *intiptr );
public     : virtual                                logical RemoveGUID ( );
public     : virtual                                logical Reserve ( );
public     : virtual                                void Reset ( );
public     :                                        logical ResetReferences ( );
public     :                                        logical ResetWProtect ( );
public     : virtual                                logical Save (logical switchopt, logical overwrite=NO, logical refresh_opt=NO );
public     : virtual          OPAImpExp             void SetClusterNumber (EB_Number clnumb );
public     :                                        void SetExtInstType (int8 iactyp );
public     : virtual                                logical SetInWork (logical workopt );
public     :                                        void SetMBNumber (int16 mbnumber );
public     : virtual                                void SetStructAccess (StructAccess *structacc );
public     : virtual                                void SetTimeStamp ( );
public     : virtual          OPAImpExp             void SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                                logical SetWProtect ( );
public     :                                        void Setup ( );
public     :                                        void Setup (EB_Number clnumb, int16 mbnumber );
public     :                                        logical SetupInst (logical update );
public     : virtual                                logical Unlock ( );
public     :                                             isel (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical crt_opt );
public     :                                             isel ( );
public     :                                             isel (DBStructDef *strdefptr, void *instptr );
public     : virtual                                     ~isel ( );
};

#pragma pack()
#endif
