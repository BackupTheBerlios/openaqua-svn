/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    exdBBuffer

\brief    


\date     $Date: 2006/03/12 19:14:22,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   exdBBuffer_HPP
#define   exdBBuffer_HPP

class     exdBBuffer;

class     BinArrayObjEntry;
class     BinSArrayObjEntry;
class     LACObject;
class     exd;
#include  <sBinArray.hpp>
#include  <sBinSArray.hpp>
#include  <sEB_Number.hpp>
#include  <sStatistic.hpp>
#pragma pack(8)

class  exdBBuffer :public BinArray
{
protected  :         LACObject                                   *ob_handle ATTR_ALIGN(4);                                   
protected  :         int32                                        inst_length;                                               
protected  :         int16                                        struct_id;                                                 
protected  :         int16                                        schema_version;                                            
protected  :         Statistic                                    stats;                                                     
protected  :         int16                                        empty_count;                                               

public     :
                     LACObject                                   *get_ob_handle() { return(ob_handle); }
                     int32                                        get_inst_length() { return(inst_length); }
                     int16                                        get_struct_id() { return(struct_id); }
                     int16                                        get_schema_version() { return(schema_version); }
                     Statistic                                   &get_stats() { return(stats); }
                     int16                                        get_empty_count() { return(empty_count); }
public     :                                     logical Clear ( );
public     :                                     exd *Delete (EB_Number entnum );
public     : virtual                             void FreeObjEntry (BinSArrayObjEntry *obj_entry );
public     :                                     exd *GetExdEntry (int32 lindex );
public     : virtual                             void InitObjEntry (BinSArrayObjEntry *obj_entry, uint64 entry_index );
public     :                                     exd *Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr=CUR_VERSION );
public     :                                     exd *Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     :                                     exd *Replace (exd *exdarea );
public     :                                     logical Setup (EB_Number entnr );
public     :                                                             exdBBuffer (LACObject *lobhandle, int16 maxcount, int32 instlen, int16 sid, uint16 version, logical auto_reorg=YES );
public     :                                     void set_sid (int16 sid );
public     :                                                             ~exdBBuffer ( );
};

#pragma pack()
#endif
