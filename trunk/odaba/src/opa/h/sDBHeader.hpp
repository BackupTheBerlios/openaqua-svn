/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBHeader

\brief    


\date     $Date: 2006/03/12 19:12:57,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBHeader_HPP
#define   DBHeader_HPP

class     DBHeader;

#define  CUR_DBVERSION                             6
#define  CUR_SYSVERSION                            18
#include  <sEB_Number.hpp>
#pragma pack(1)

class  DBHeader
{
protected  :         char                                         ident[4];                                                  //
protected  :         uint16                                       last_str_number;                                           //
protected  :         char                                         reserved1[8];                                              
protected  :         uint16                                       recover_number;                                            //
protected  :         char                                         recover_path[65];                                          //
protected  :         uint16                                       recover_first;                                             //
protected  :         uint32                                       root_objekt;                                               //
protected  :         int16                                        version;                                                   
protected  :         int16                                        schema_version;                                            //
protected  :         logical                                      save_transaction;                                          
protected  :         int32                                        write_transact;                                            
protected  :         int32                                        recover_pos;                                               
protected  :         logical                                      recover_write;                                             
protected  :         int16                                        system_version;                                            //
protected  :         EB_Number                                    shadow_db;                                                 // Reference to definition of shadow database
protected  :         int32                                        next_ws_number;                                            // Next free workspace number
protected  :         char                                         reserved[13];                                              //

public     :
                     char                                        *get_ident() { return(ident); }
                     char                                        *get_reserved1() { return(reserved1); }
                     char                                        *get_recover_path() { return(recover_path); }
                     logical                                      get_save_transaction() { return(save_transaction); }
                     logical                                      get_recover_write() { return(recover_write); }
                     EB_Number                                   &get_shadow_db() { return(shadow_db); }
                     int32                                        get_next_ws_number() { return(next_ws_number); }
                     char                                        *get_reserved() { return(reserved); }
public     :                                                             DBHeader ( );
public     :                                     void FromPIF (logical pif );
public     :                                     void Initialize ( );
public     :                                     void ToPIF (logical pif );
public     :                                     int32 get_last_str_number ( );
public     :                                     int16 get_recover_first ( );
public     :                                     uint16 get_recover_number ( );
public     :                                     int32 get_recover_pos ( );
public     :                                     EB_Number get_root_objekt ( );
public     :                                     int16 get_schema_version ( );
public     :                                     int16 get_system_version ( );
public     :                                     int16 get_version ( );
public     :                                     int32 get_write_transact ( );
public     :                                     void inc_next_ws_number ( );
public     :                                     void set_last_str_num (uint16 maxstrnum );
public     :                                     void set_next_ws_number (int32 ws_num );
public     :                                     void set_recover_fst ( );
public     :                                     uint16 set_recover_numb (uint16 recnum=0 );
public     :                                     void set_recover_path (char *recpath );
public     :                                     void set_recover_pos (int32 rec_position );
public     :                                     void set_recover_writ (logical recover_opt );
public     :                                     EB_Number set_root_objekt (EB_Number entnr );
public     :                                     logical set_save_ta (logical save_ta );
public     :                                     void set_schema_vers (uint16 version );
public     :                                     void set_system_version (uint16 version );
public     :                                     void set_version (int16 new_version );
public     :                                     int32 set_write_ta (char write_ta );
};

#pragma pack()
#endif
