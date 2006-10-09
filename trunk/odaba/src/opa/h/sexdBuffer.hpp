/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    exdBuffer

\brief    


\date     $Date: 2006/03/12 19:14:23,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   exdBuffer_HPP
#define   exdBuffer_HPP

class     exdBuffer;

#ifndef   DLL_exd_HPP
#define   DLL_exd_HPP
#include  <sexd.hpp>
#include  <sDLL.h>
#endif
#ifndef   GSRT_exdEntry_HPP
#define   GSRT_exdEntry_HPP
#include  <sexdEntry.hpp>
#include  <sGSRT.h>
#endif
class     BinTree;
class     LACObject;
class     exd;
#include  <sBTIterator.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  exdBuffer :public BTIterator
{
protected  :         LACObject                                   *ob_handle;                                                 //
protected  :         int32                                        inst_length;                                               //
protected  :         int16                                        struct_id;                                                 //
protected  :         int16                                        schema_version;                                            //
protected  :         int32                                        loc_count;                                                 //
protected  :         int32                                        ins_count;                                                 //
protected  :         int32                                        del_count;                                                 //
protected  :         int16                                        empty_count;                                               //
protected  :         int16                                        del_proz;                                                  //
protected  :         logical                                      shadow_base;                                               //
protected  :         logical                                      write_shadow;                                              //
protected  :         logical                                      locate_exact;                                              //
protected  :         BinTree                                     *exd_tree;                                                  //
protected  :         DLL(exd)                                     free_exds;                                                 

public     :
                     LACObject                                   *get_ob_handle() { return(ob_handle); }
                     int32                                        get_inst_length() { return(inst_length); }
                     int16                                        get_struct_id() { return(struct_id); }
                     int16                                        get_schema_version() { return(schema_version); }
                     int32                                        get_loc_count() { return(loc_count); }
                     int32                                        get_ins_count() { return(ins_count); }
                     int32                                        get_del_count() { return(del_count); }
                     int16                                        get_empty_count() { return(empty_count); }
                     int16                                        get_del_proz() { return(del_proz); }
                     logical                                      get_shadow_base() { return(shadow_base); }
                     logical                                      get_write_shadow() { return(write_shadow); }
                     logical                                      get_locate_exact() { return(locate_exact); }
                     BinTree                                     *get_exd_tree() { return(exd_tree); }
                     DLL(exd)                                    &get_free_exds() { return(free_exds); }
public     :                                     logical Add (EB_Number entnr, exd *exdarea );
public     :                                     logical Clear ( );
public     :                                     logical Delete (exd *exdarea );
public     :                                     exd *Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr=CUR_VERSION );
public     :                                     exd *Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     :                                     void Optimize ( );
public     :                                     void Release (exd *exdarea );
public     :                                     exd *Replace (exd *exdarea );
public     :                                     logical Setup (EB_Number oldent, EB_Number entnr );
public     :                                                             exdBuffer (LACObject *lobhandle, int16 maxcount, int32 instlen, int16 sid, uint16 version, logical shadow_read=NO, logical shadow_write=NO );
public     :                                     void set_sid (int16 sid );
public     :                                                             ~exdBuffer ( );
};

#pragma pack()
#endif
