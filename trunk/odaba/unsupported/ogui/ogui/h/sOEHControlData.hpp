/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHControlData

\brief    
          can anybody please document? please

\date     $Date: 2006/03/13 21:34:10,51 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHControlData_HPP
#define   OEHControlData_HPP

class     OEHControlData;

#include  <sDLL.h>
class     CellData;
class     CellData;
class     ODS;
class     ODataWidget;
class     OEHSlotRouter;
class     OStringList;
#include  <sOEHDataWidget.hpp>
#pragma pack(4)

class  OEHControlData :public OEHDataWidget
{
protected  :         OStringList                                 *string_list;                                               //
protected  :         DLL(CellData)                               *cells;                                                     //
protected  :         logical                                      ignore;                                                    //
protected  :         OEHSlotRouter                               *router;                                                    //

public     :
                     OStringList                                 *get_string_list() { return(string_list); }
                     logical                                      get_ignore() { return(ignore); }
                     OEHSlotRouter                               *get_router() { return(router); }
public     : virtual                             logical Activate ( );
public     :                                     void AddCell (CellData *pCellData );
public     :                                     logical BeginOnce ( );
public     : virtual                             void ClearData ( );
public     : virtual                             void ClearList ( );
public     :                                     void Connect (char *ods_signal, char *oeh_slot );
public     :                                     OStringList *CreateStringList ( );
public     : virtual                             logical Deactivate (logical data_only=NO );
public     :                                     void Disconnect (char *ods_signal, char *oeh_slot );
public     :                                     void EndOnce (logical started );
public     : virtual                             void FillData ( );
public     : virtual                             void FillList ( );
public     :                                     OStringList *GetStringList ( );
public     : virtual                             void HandleActivated ( );
public     : virtual                             void HandleClosed ( );
public     : virtual                             void HandleOpened (logical chk_visible );
public     : virtual                             void ListChanged (logical chk_visible );
public     : virtual                             void ListReset ( );
public     : virtual                             void ListUpdated ( );
public     :         OGUI7ImpExp                                         OEHControlData (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL );
public     :         OGUI7ImpExp                                         OEHControlData (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                                     void Reconnect (char *ods_signal, char *oeh_slot, char *oeh_prev_slot );
public     :                                     void RemoveCell (CellData *pCellData );
public     :                                     void RemoveStringList ( );
public     : virtual                             void SetReadOnly (logical fReadOnly );
public     :                                     void StoreToValue (QString qsValue );
public     :                                     void StoreToValue (char *string );
public     :                                     void StoreToValue (int32 number );
public     :                                     void StoreToValue (logical cond );
public     :                                     void StoreToValue (dbdt date );
public     :                                     void StoreToValue (dbtm time );
public     : virtual                             logical SyncColState ( );
public     : virtual                             logical SyncInstState ( );
public     : virtual                             void UnsyncColState ( );
public     : virtual                             void UnsyncState ( );
public     : virtual                             void UpdateControl ( );
public     : virtual                             void UpdateList ( );
public     : virtual                             void UpdateReadOnly (logical fReadOnly );
public     :                                     OStringList *UpdateStringList ( );
public     : virtual                             void ValueInserted ( );
public     : virtual                             void ValueRemoved ( );
public     : virtual                             void ValueReset ( );
public     : virtual                             logical ValueSelected ( );
public     : virtual                             void ValueUpdated ( );
protected  :                                     logical getEnabled ( );
public     :                                                             ~OEHControlData ( );
};

#pragma pack()
#endif
