/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ref

\brief    


\date     $Date: 2006/03/12 19:14:58,35 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ref_HPP
#define   ref_HPP

class     ref;

class     DBHandle;
class     DBIndex;
class     LACObject;
class     LNode;
class     PCSHandle;
class     RefAccess;
class     exd;
class     inti;
class     ref;
class     refs;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <sEntryHandle.hpp>
#include  <sckh.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  ref :public sts,
public EntryHandle
{
protected  :         EB_Number                                   *refrex ATTR_ALIGN(4);                                      //
protected  :         RefAccess                                   *struct_access;                                             //
protected  :         DBIndex                                     *refsakcb;                                                  //
public     :         int32                                        refcuri;                                                   //
protected  :         int16                                        refsid;                                                    //
public     :         logical                                      refmod;                                                    //
public     :         logical                                      refglob;                                                   //
protected  :         ckh                                          new_ckh;                                                   //
protected  :         ckh                                          old_ckh;                                                   //

public     :
                     EB_Number                                   *get_refrex() { return(refrex); }
                     RefAccess                                   *get_struct_access() { return(struct_access); }
                     DBIndex                                     *get_refsakcb() { return(refsakcb); }
                     int16                                        get_refsid() { return(refsid); }
                     ckh                                         &get_new_ckh() { return(new_ckh); }
                     ckh                                         &get_old_ckh() { return(old_ckh); }
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     :                                     logical CheckDBDelInstances (NString &nresult, logical repair );
public     :                                     logical CheckDBIndex (NString &nresult, CheckOptions check_opts );
public     :                                     logical CheckDBRefIndex (NString &nresult, logical repair );
public     :                                     int16 CheckID (void *instptr, void *oldinst, EB_Number entnr );
public     : virtual                             logical CheckIndex (NString &nresult, logical repair );
public     : virtual                             char *CheckMod (void *instptr, void *oldinst, char *key_area );
public     : virtual                             logical CheckNewID (void *instptr, EB_Number entnr );
public     : virtual                             logical CheckWProtect ( );
public     : virtual                             logical DelExt (int32 lindx0 );
public     :                                     logical DelKey (char *skey, EB_Number ebsnum );
public     : virtual                             logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             logical DeleteID (EB_Number entnr );
public     : virtual                             void DeleteReference ( );
public     : virtual                             int32 GetCount ( );
public     : virtual                             char *GetGenAttribute ( );
public     : virtual                             EB_Number GetID (int32 lindx0 );
public     : virtual                             int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             int32 GetIndex (EB_Number ebsnum );
public     : virtual                             char *GetKey (int32 lindx0, char *keyptr );
public     :                                     char *GetKeyInstance (inti *intiptr );
public     :                                     int16 GetKeyLength ( );
public     :                                     char *GetKeyNum ( );
public     : virtual                             int16 GetModCount ( );
public     :                                     char *GetOldKeyInstance (inti *intiptr, void *oldinst );
public     :                                     int32 GetRefCuri ( );
public     : virtual                             refs *GetSharedRef ( );
public     :                                     logical HasWorkspace ( );
public     :                                     char *IdentityToPIF (char *skey, char *keyptr );
public     :                                     logical InitialWrite ( );
public     :                                     void Initialize (DBIndex *akcbptr );
public     :                                     logical IsIdentityOrder ( );
public     :                                     logical IsModified ( );
public     :                                     logical IsTemporary ( );
public     :                                     logical Lock ( );
public     :                                     char *PIFToIdentity (char *keyptr );
public     : virtual                             exd *ProvideEXD ( );
public     : virtual                             logical ReadIndexEntry (int32 lindx0, void *instptr );
public     : virtual                             logical Refresh ( );
public     :                                     void ReleaseReference ( );
public     : virtual                             logical Repair ( );
public     :                                     logical ReserveEXD ( );
public     :                                     void ReserveReference ( );
public     : virtual                             logical Reset ( );
public     :                                     logical ResetEXD ( );
public     :                                     void ResetRefCuri ( );
public     : virtual                             logical Save ( );
public     :                                     char SetAutoIdent (void *instptr );
public     :                                     void SetKeyErrorVariables (char *keyptr );
public     :                                     logical SetKeyNum (char *keyarea );
public     : virtual                             void SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                             logical Setup (EB_Number *extref, EB_Number clnumb, int16 w_mbnumber=0 );
public     :                                     logical Unlock (logical extlock );
public     : virtual                             logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             int32 WSAddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical WSAddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     : virtual                             logical WSCheckNewID (void *instptr, EB_Number entnr );
public     : virtual                             logical WSDelKey (char *skey, EB_Number ebsnum );
public     : virtual                             logical WSDeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             logical WSDeleteID (EB_Number entnr );
public     :                                     void WSDeleteReference ( );
public     : virtual                             int32 WSGetCount ( );
public     : virtual                             EB_Number WSGetID (int32 lindx0 );
public     : virtual                             int32 WSGetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             int32 WSGetIndex (EB_Number ebsnum );
public     : virtual                             char *WSGetKey (int32 lindx0, char *keyptr );
public     : virtual                             char WSSetAutoIdent (void *instptr );
public     : virtual                             logical WriteIndexEntry (int32 lindx0, void *instptr );
public     :                                                             ref (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind );
public     :                                                             ref ( );
public     : static                              ref *__cdecl refcrt (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind, PCSHandle *pcs_handle );
public     : virtual                                                     ~ref ( );
public     :                                     void set_refmod ( ){

  refmod = YES;

}

public     :                                     void set_refrex (EB_Number *extref ){

  refrex = extref;

}

};

#pragma pack()
#endif
