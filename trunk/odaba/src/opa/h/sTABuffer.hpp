/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    TABuffer

\brief    


\date     $Date: 2006/03/12 19:13:54,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TABuffer_HPP
#define   TABuffer_HPP

class     TABuffer;

class     DBHandle;
class     DelInstEntry;
class     DiffListList;
class     DifferenceList;
class     Error;
class     LACObject;
class     TABuffer;
class     acb;
class     eb_RootBase;
class     exd;
#include  <sEB_Number.hpp>
#include  <sexdBBuffer.hpp>
#pragma pack(8)

class  TABuffer
{
protected  :         LACObject                                   *ob_handle;                                                 //
protected  :         TABuffer                                    *high_TA;                                                   //
protected  :         int16                                        ta_level;                                                  //
protected  :         int32                                        ta_count;                                                  //
protected  :         logical                                      ta_error;                                                  //
protected  :         DiffListList                                *dl_list;                                                   //
protected  :         DelInstEntry                                *new_global_instances;                                      //
protected  :         Error                                       *last_error;                                                //

public     :
                     LACObject                                   *get_ob_handle() { return(ob_handle); }
                     TABuffer                                    *get_high_TA() { return(high_TA); }
                     int16                                        get_ta_level() { return(ta_level); }
                     int32                                        get_ta_count() { return(ta_count); }
                     logical                                      get_ta_error() { return(ta_error); }
                     DiffListList                                *get_dl_list() { return(dl_list); }
                     DelInstEntry                                *get_new_global_instances() { return(new_global_instances); }
                     Error                                       *get_last_error() { return(last_error); }
public     :                                     void AddGlobalInstance (char *extnames, EB_Number ebsnum );
public     :                                     void AppendDIList (DelInstEntry *di_entry );
public     : virtual                             logical Cancel ( );
public     : virtual                             logical Check (TABuffer *low_ta );
public     : virtual                             logical CheckEBI (exd *exdptr );
public     :                                     logical CheckEntry (exd *exdptr, exd *ta_exd );
public     : virtual                             uint8 CheckWProtect (exd *exdptr );
public     :                                     logical ConsolidateDlists ( );
public     : virtual                             logical Delete (exd *exdptr );
public     :                                     int32 GetCount ( );
public     :                                     DifferenceList *GetDiffList (EB_Number entnr );
public     : virtual                             logical GetEBI (exd *exdptr );
public     : virtual                             int32 GetLength (acb *acbptr );
public     :                                     TABuffer *GetTop ( );
public     : virtual                             int32 GetUsedLength (acb *acbptr );
public     : virtual                             logical IsEmpty ( );
public     : virtual                             exd *Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr=CUR_VERSION );
public     : virtual                             exd *Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     :                                     TABuffer *LocateBuffer (int32 tanumber );
public     :                                     TABuffer *LocateBuffer (exd *exdptr );
public     : virtual                             logical LocateEntry (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     :                                     DifferenceList *ProvideDiffList (DifferenceList *dlist_ptr );
public     :                                     DifferenceList *ProvideDiffList (DBIndex *db_index, EB_Number entnr, logical shared_opt );
public     : virtual                             logical Read (exd *exdptr, int32 w_instlen=AUTO );
public     :                                     logical ReleaseDlists ( );
public     :                                     logical ReleaseEntry (exd *exdptr );
public     :                                     void ReleaseFields ( );
public     :                                     logical ReserveEntry (exd *exdptr );
public     :                                     logical ResetDIList (logical term );
public     :                                     logical ResetEntry (exd *exdarea );
public     :                                     void ResetError ( );
public     :                                     void RestoreError ( );
public     : virtual                             logical Save ( );
public     :                                     void SetError ( );
public     :                                     void SetLastError ( );
public     :                                     logical SetupEntry (exd *exdptr );
public     : virtual                             logical Start (TABuffer *highTABuf, int32 tanumber );
public     : virtual                             logical Stop ( );
public     :                                                             TABuffer (LACObject *lobhandle, TABuffer *highTABuf, int32 tanumber );
public     :                                     logical UpdateEntry (exd *exdptr );
public     : virtual                             logical Write (exd *exdptr );
public     : virtual                                                     ~TABuffer ( );
};

#pragma pack()
#endif
