/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    refs

\brief    


\date     $Date: 2006/03/12 19:15:05,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   refs_HPP
#define   refs_HPP

class     refs;

class     DBHandle;
class     DBIndex;
class     DifferenceList;
class     LACObject;
class     exd;
class     inti;
class     refs;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <sref.hpp>
#pragma pack(8)

class  refs :public ref
{
protected  :         int16                                        refsotyp ATTR_ALIGN(4);                                    //
protected  :         logical                                      shared_ref;                                                //
protected  :         EB_Number                                    temp_rex;                                                  //
protected  :         DifferenceList                              *diff_list;                                                 //
protected  :         DifferenceList                              *sum_list;                                                  //
protected  :         int32                                        ws_curri;                                                  //
protected  :         EB_Number                                    ws_entnr;                                                  //
protected  :         ref                                         *shadow_ref;                                                //

public     :
                     int16                                        get_refsotyp() { return(refsotyp); }
                     logical                                      get_shared_ref() { return(shared_ref); }
                     EB_Number                                   &get_temp_rex() { return(temp_rex); }
                     DifferenceList                              *get_diff_list() { return(diff_list); }
                     DifferenceList                              *get_sum_list() { return(sum_list); }
                     int32                                        get_ws_curri() { return(ws_curri); }
                     EB_Number                                   &get_ws_entnr() { return(ws_entnr); }
                     ref                                         *get_shadow_ref() { return(shadow_ref); }
public     :                                     int32 DLGetIndex (DifferenceList *dlist_ptr, char *skey, EB_Number ebsnum, logical exact=YES );
public     :                                     int32 DLGetIndex (EB_Number ebsnum );
public     :                                     char *DLGetKey (int32 lindx0, char *keyptr );
public     :                                     logical DeleteDiffListReference ( );
public     :                                     EB_Number GetIdent (char *skey, EB_Number ebsnum );
public     : virtual                             int16 GetModCount ( );
public     :                                     logical InitKeyValue (inti *intiptr, void *oldinst, char *keyarea, EB_Number entnr );
public     :                                     logical InitSumList ( );
public     :                                     logical RefreshDiffList (logical refresh_all );
public     : virtual                             logical Reset ( );
public     :                                     int32 SRAddExt (EB_Number entnr, char *skey, int32 lindx0 );
public     :                                     logical SRAddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     :                                     logical SRCheckNewID (void *instptr, EB_Number entnr );
public     :                                     logical SRDelKey (char *skey, EB_Number entnr );
public     :                                     logical SRDeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                     int32 SRGetCount ( );
public     :                                     EB_Number SRGetID (int32 lindx0 );
public     :                                     int32 SRGetIndex (EB_Number ebsnum );
public     :                                     int32 SRGetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     :                                     char *SRGetKey (int32 lindx0, char *keyptr );
public     :                                     char SRSetAutoIdent (void *instptr );
public     :                                     logical SRUpdateDiff (char *skey, EB_Number entnr, char op_char );
public     :                                     logical SetupShadowRef ( );
public     :                                     logical SetupSumList (char *w_skey1=NULL, char *w_skey2=NULL );
public     :                                     logical SharedCollInTA ( );
public     : virtual                             int32 WSAddExt (EB_Number entnr, char *skey, int32 lindx0 );
public     : virtual                             logical WSAddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     : virtual                             logical WSCheckNewID (void *instptr, EB_Number entnr );
public     : virtual                             logical WSDelKey (char *skey, EB_Number entnr );
public     : virtual                             logical WSDeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             int32 WSGetCount ( );
public     : virtual                             EB_Number WSGetID (int32 lindx0 );
public     : virtual                             int32 WSGetIndex (EB_Number ebsnum );
public     : virtual                             int32 WSGetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             char *WSGetKey (int32 lindx0, char *keyptr );
public     : virtual                             char WSSetAutoIdent (void *instptr );
public     :                                                             refs (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, char otyp, DBIndex *akcbptr, logical globind );
public     :                                     logical refsdel ( );
public     :                                     logical refskck (char *newkey );
public     :                                     logical refsren (char *oldkey, char *newkey );
public     :                                     void reset_ws_curri ( );
public     :                                     void set_shared_ref (logical shared_opt );
public     : virtual                                                     ~refs ( );
public     : virtual                             refs *GetSharedRef ( ){

 return (this);

}

public     : virtual                             logical Refresh ( ){

 return (NO);

}

};

#pragma pack()
#endif
