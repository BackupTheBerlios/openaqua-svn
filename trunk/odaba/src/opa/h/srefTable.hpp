/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    refTable

\brief    


\date     $Date: 2006/03/12 19:15:02,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   refTable_HPP
#define   refTable_HPP

class     refTable;

#ifndef   GSRT_refEntry_HPP
#define   GSRT_refEntry_HPP
#include  <srefEntry.hpp>
#include  <sGSRT.h>
#endif
class     CSHandleList;
class     DBFieldDef;
class     DBHandle;
class     LACObject;
class     LNode;
class     PCSHandle;
class     binti;
class     inti;
class     kmvl;
class     ref;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  refTable :public GSRT(refEntry)
{
protected  :         kmvl                                        *keymvl ATTR_ALIGN(4);                                      //
protected  :         ref                                         *topref;                                                    //
protected  :         logical                                      oldinst_opt;                                               //
protected  :         logical                                      generic;                                                   //
protected  :         logical                                      autoid_key;                                                //
protected  :         uint16                                       schema_version;                                            //
protected  :         exd                                         *lock_exd;                                                  //

public     :
                     kmvl                                        *get_keymvl() { return(keymvl); }
                     ref                                         *get_topref() { return(topref); }
                     logical                                      get_oldinst_opt() { return(oldinst_opt); }
                     logical                                      get_generic() { return(generic); }
                     logical                                      get_autoid_key() { return(autoid_key); }
                     uint16                                       get_schema_version() { return(schema_version); }
public     :                                     logical AddGenericRef (char *fldname, inti *intiptr, EB_Number entnr );
public     :                                     logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     :                                     logical CheckMod (void *instptr, void *oldinst );
public     :                                     logical CheckNew ( );
public     :                                     logical CheckNewID (void *instptr, EB_Number entnr );
public     :                                     logical CheckWProtect ( );
public     :                                     logical Create ( );
public     :                                     logical DelGenericRef (char *fldname, binti *bintiptr, EB_Number entnr );
public     :                                     logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                     logical DeleteID (EB_Number entnr );
public     :                                     logical DeleteReference ( );
public     :                                     EB_Number GetID ( );
public     :                                     ref *GetReference (char *keynames=NULL );
public     :                                     ref *GetReference (int16 indx );
public     :                                     logical HasKeyLocks ( );
public     :                                     logical Lock ( );
public     :                                     logical OldinstRequested (ref *curref );
public     :                                     logical Refresh ( );
public     :                                     logical RemoveReference ( );
public     :                                     logical Reset ( );
public     :                                     void ResetEBNumber ( );
public     :                                     logical ResetNew ( );
public     :                                     logical Save ( );
public     :                                     ref *SelectSourceRef ( );
public     :                                     char SetAutoIdent (void *instptr );
public     :                                     logical SetInWork (logical workopt );
public     :                                     void SetVersion (uint16 version_nr=CUR_VERSION );
public     :                                     logical Setup (EB_Number *extref, EB_Number clnumb, int16 mbnumber, PIACC accopt, logical tempmain=NO );
public     :                                     logical Unlock (logical extlock );
public     :                                     logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr, logical temp_only=NO );
public     :                                     logical UpdateNew (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     :                                                             refTable (LACObject *lobhandle, DBFieldDef *fielddef, PCSHandle *pcs_handle );
public     :                                                             refTable (ref *refptr );
public     :                                     logical OldinstRequested ( ){

  return ( this ? oldinst_opt : NO );

}

};

#pragma pack()
#endif
