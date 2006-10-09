/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    RefAccess

\brief    


\date     $Date: 2006/03/12 19:13:46,65 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   RefAccess_HPP
#define   RefAccess_HPP

class     RefAccess;

class     DBHandle;
class     DBStructDef;
class     LACObject;
class     RefAccess;
class     exd;
class     exdBuffer;
class     isel;
#include  <sEB_Number.hpp>
#include  <sStructAccess.hpp>
#pragma pack(8)

class  RefAccess :public StructAccess
{
protected  :         LACObject                                   *ob_handle ATTR_ALIGN(4);                                   
protected  :         exdBuffer                                   *ref_buffer;                                                
protected  :         int64                                        temp_entnr;                                                

public     :
                     LACObject                                   *get_ob_handle() { return(ob_handle); }
                     exdBuffer                                   *get_ref_buffer() { return(ref_buffer); }
                     int64                                        get_temp_entnr() { return(temp_entnr); }
public     :                                     int32 ChangeEXDSize (exd *exdarea, int32 longlen );
public     :                                     EB_Number CreateEBI (int16 mbnumber, EB_Number clnumb, uint16 sbnumber, uint16 version_nr=CUR_VERSION );
public     :                                     int32 GetDBEntryLength (EB_Number ebsnum, uint8 wslevel, uint16 version_nr=CUR_VERSION );
public     :                                     int32 GetDBUsedLength (EB_Number ebsnum, uint8 wslevel, uint16 version_nr=CUR_VERSION );
public     : virtual                             exd *GetEXD (exd *exdarea );
public     : virtual                             exd *GetEXD (EB_Number entnr, uint16 version_nr=CUR_VERSION );
public     :                                     RefAccess *GetRefAccess ( );
public     :                                     int64 GetTempEBNr ( );
public     :                                     logical IsNet ( );
public     :                                     logical Lock (EB_Number ebsnum );
public     :                                     exd *ProvideEXD (EB_Number ebsnum, EB_Number clnumb, int32 longlen, char otyp, logical bwrite_opt, logical support_diff_list, uint16 version_nr=CUR_VERSION, logical w_trans_opt=NO );
public     :                                                             RefAccess (LACObject *lobhandle, DBStructDef *strdefptr, int16 maxcount, logical shadow_read=NO );
public     :                                                             RefAccess ( );
public     :                                     logical Unlock (EB_Number ebsnum );
public     :                                     EB_Number WriteEXD (exd *exdarea, int32 l_size, int16 mbnumber, uint16 sbnumber, int32 offset );
public     : virtual                                                     ~RefAccess ( );
};

#pragma pack()
#endif
