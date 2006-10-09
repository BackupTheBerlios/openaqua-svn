/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DifferenceList

\brief    


\date     $Date: 2006/03/12 19:13:12,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DifferenceList_HPP
#define   DifferenceList_HPP

class     DifferenceList;

#define  SYS_NSID                                  0
class     DBFieldDef;
class     DBIndex;
class     DBStructDef;
class     DiffListEntry;
class     LACObject;
class     acb;
class     exd;
class     ref;
#include  <sDifferenceList.hpp>
#include  <sEB_Number.hpp>
#include  <smvl.hpp>
#pragma pack(8)

class  DifferenceList :public mvl
{
protected  :         DifferenceList                              *prev_list ATTR_ALIGN(4);                                   //
protected  :         DifferenceList                              *ws0_list;                                                  //
protected  :         int8                                         ws_level;                                                  //
protected  :         int32                                        ws_number;                                                 //
protected  :         ref                                         *reference;                                                 //
protected  :         DiffListEntry                               *work_entry;                                                //
protected  :         logical                                      local_exd;                                                 //
protected  :         logical                                      local_index_def;                                           //
protected  :         int8                                         ref_orgtype;                                               //
protected  :         DBFieldDef                                  *field_def;                                                 //

public     :
                     DifferenceList                              *get_prev_list() { return(prev_list); }
                     DifferenceList                              *get_ws0_list() { return(ws0_list); }
                     int8                                         get_ws_level() { return(ws_level); }
                     int32                                        get_ws_number() { return(ws_number); }
                     ref                                         *get_reference() { return(reference); }
                     DiffListEntry                               *get_work_entry() { return(work_entry); }
                     logical                                      get_local_exd() { return(local_exd); }
                     logical                                      get_local_index_def() { return(local_index_def); }
                     int8                                         get_ref_orgtype() { return(ref_orgtype); }
                     DBFieldDef                                  *get_field_def() { return(field_def); }
public     :                                     logical Add (DifferenceList *dlist_ptr );
public     :                                     logical Add (DifferenceList *dlist_ptr, char *skey1, char *skey2 );
public     :                                     DiffListEntry *AddEntry (char *skey );
public     :                                     DiffListEntry *AddEntry (DiffListEntry *dl_entry, int32 wsnumber );
public     :                                     logical AddIndexOperation (char *skey, EB_Number entnr, int16 operation );
public     :                                     logical CheckOperation (char *skey, EB_Number entnr );
public     :                                     logical Consolidate ( );
public     :                                     logical Consolidate (DifferenceList *dlist_ptr );
public     :                                     void Deinitialize ( );
public     :                                     logical DeleteEntry ( );
public     :                                     int32 Difference (char *skey, logical recursiv=NO );
public     :                                                             DifferenceList (ref *refptr, uint8 wslevel );
public     :                                                             DifferenceList (DifferenceList *dlist_ptr );
public     :                                                             DifferenceList (LACObject *lobhandle, uint8 wslevel );
public     :                                                             DifferenceList (LACObject *lobhandle, exd *exdptr );
public     :                                                             DifferenceList (DifferenceList *dlist_ptr, LACObject *lobhandle, DBIndex *db_index, EB_Number entnr );
public     : virtual                             logical FromPIF (exd *exdarea );
public     :                                     EB_Number GetEBINumber ( );
public     :                                     DiffListEntry *GetEntry (char *skey, logical recursiv=NO );
public     :                                     DiffListEntry *GetEntry (int32 lindx0 );
public     : virtual                             char *GetKey (int32 lindx0, char *keyptr );
public     :                                     DiffListEntry *GetPlusDiffEntry (char *skey, int32 difference );
public     :                                     DBStructDef *GetStructDef (EB_Number entnr );
public     :                                     logical Initialize ( );
public     :                                     logical ListSetup (DifferenceList *dlist_ptr );
public     :                                     logical LockEntry (char *keyptr );
public     :                                     logical ProvidePrevList (logical recursiv=NO );
public     :                                     logical ProvideTable (EB_Number ebsnum );
public     :                                     logical ProvideWS0List ( );
public     : virtual                             logical Refresh ( );
public     :                                     logical RefreshAll ( );
public     : virtual                             logical Reset ( );
public     :                                     logical SetupMVL (DBIndex *akcbptr );
public     :                                     logical Store (DifferenceList *dlist_ptr );
public     :                                     DiffListEntry *StoreEntry (DiffListEntry *dl_entry );
public     :                                     logical SumList (DifferenceList *dlist_ptr, char *w_skey1=NULL, char *w_skey2=NULL );
public     : virtual                             logical ToPIF (exd *exdarea );
public     :                                     logical UnlockEntries ( );
public     :                                     logical UnlockEntry (char *keyptr );
public     :                                     logical UpdateEntry (DiffListEntry *dl_entry, int32 wsnumber );
public     :                                     logical UpdateWSNumber (DiffListEntry *dl_entry, int32 wsnumber );
public     :                                     void set_ws_number (int32 wsnumber );
public     :                                                             ~DifferenceList ( );
};

#pragma pack()
#endif
