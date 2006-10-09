/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InternalTA

\brief    


\date     $Date: 2006/03/12 19:13:26,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   InternalTA_HPP
#define   InternalTA_HPP

class     InternalTA;

class     DBHandle;
class     LACObject;
class     acb;
class     exd;
#include  <sEB_Number.hpp>
#include  <sModBuffer.hpp>
#include  <sTABuffer.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  InternalTA :public TABuffer,
public ModBuffer
{
protected  :         int16                                        use_count ATTR_ALIGN(4);                                   

public     :
                     int16                                        get_use_count() { return(use_count); }
public     : virtual                             logical Cancel ( );
public     : virtual                             uint8 CheckWProtect (exd *exdptr );
public     : virtual                             logical Delete (exd *exdptr );
public     :                                     int32 GetCount ( );
public     : virtual                             logical GetEBI (exd *exdptr );
public     : virtual                             int32 GetLength (acb *acbptr );
public     : virtual                             int32 GetUsedLength (acb *acbptr );
public     :                                                             InternalTA (LACObject *lobhandle );
public     : virtual                             logical IsEmpty ( );
public     : virtual                             exd *Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr=CUR_VERSION );
public     : virtual                             exd *Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     : virtual                             logical LocateEntry (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     : virtual                             logical Read (exd *exdptr, int32 w_instlen=AUTO );
public     : virtual                             logical Save ( );
public     :                                     logical SaveRecovery ( );
public     : virtual                             logical Start (TABuffer *highTABuf, int32 tanumber );
public     : virtual                             logical Stop ( );
public     : virtual                             logical Write (exd *exdptr );
public     : virtual                                                     ~InternalTA ( );
public     :                                     void set_use_count (int16 usecount ){

  use_count = usecount;

}

};

#pragma pack()
#endif
