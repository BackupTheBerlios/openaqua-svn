/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    PoolTA

\brief    


\date     $Date: 2006/03/12 19:13:44,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PoolTA_HPP
#define   PoolTA_HPP

class     PoolTA;

class     ACObject;
class     LACObject;
class     acb;
class     exd;
#include  <sEB_Number.hpp>
#include  <sTABuffer.hpp>
#include  <sexdBuffer.hpp>
#pragma pack(8)

class  PoolTA :public TABuffer,
public exdBuffer
{
protected  :         int16                                        max_entries ATTR_ALIGN(4);                                 //

public     :
public     : virtual                             logical Cancel ( );
public     :                                     logical Check (TABuffer *low_ta );
public     : virtual                             uint8 CheckWProtect (exd *exdptr );
public     : virtual                             logical Delete (exd *exdptr );
public     :                                     int32 GetCount ( );
public     : virtual                             logical GetEBI (exd *exdptr );
public     : virtual                             int32 GetLength (acb *acbptr );
public     : virtual                             int32 GetUsedLength (acb *acbptr );
public     : virtual                             logical IsEmpty ( );
public     : virtual                             exd *Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr=CUR_VERSION );
public     : virtual                             exd *Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     : virtual                             logical LocateEntry (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     :                                                             PoolTA (LACObject *lobhandle, TABuffer *highTABuf, int32 tanumber, int16 w_maxnum=AUTO );
public     : virtual                             logical Read (exd *exdptr, int32 w_instlen=AUTO );
public     : virtual                             logical Save ( );
public     :                                     logical SaveRecovery ( );
public     : virtual                             logical Write (exd *exdptr );
public     : virtual                                                     ~PoolTA ( );
};

#pragma pack()
#endif
