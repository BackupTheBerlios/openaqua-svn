/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    PoolTA_old



\date     $Date: 2006/03/12 19:13:45,57 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PoolTA_old_HPP
#define   PoolTA_old_HPP

class     PoolTA_old;

class     LACObject;
class     acb;
class     exd;
#include  <sEB_Number.hpp>
#include  <sTABuffer.hpp>
#include  <sexdBuffer.hpp>
#pragma pack(8)

class  PoolTA_old :public TABuffer,
public exdBuffer
{
protected  :         int16                                        max_entries ATTR_ALIGN(4);                                 

public     :
public     : virtual                             logical Cancel ( );
public     :                                     logical Check (exdBBuffer *exd_buffer );
public     : virtual                             UCHAR CheckWProtect (exd *exdptr );
public     : virtual                             logical Delete (exd *exdptr );
public     : virtual                             logical GetEBI (exd *exdptr );
public     : virtual                             int32 GetLength (acb *acbptr );
public     : virtual                             int32 GetUsedLength (acb *acbptr );
public     : virtual                             logical LocateEntry (EB_Number entnr, uint16 version_nr=CUR_VERSION );
public     :                                     void PoolTA (LACObject *lobhandle, TABuffer *highTABuf, int32 tanumber, int16 w_maxnum=AUTO );
public     : virtual                             logical Read (exd *exdptr, int32 w_instlen=AUTO );
public     : virtual                             logical Save ( );
public     :                                     logical SaveRecovery ( );
public     : virtual                             logical Write (exd *exdptr );
public     : virtual                             void ~PoolTA ( );
};

#pragma pack()
#endif
