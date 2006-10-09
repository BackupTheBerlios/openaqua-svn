/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    RootBaseTA

\brief    


\date     $Date: 2006/03/12 19:13:47,31 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   RootBaseTA_HPP
#define   RootBaseTA_HPP

class     RootBaseTA;

class     DBHandle;
class     LACObject;
class     acb;
class     exd;
#include  <sEB_Number.hpp>
#include  <sTABuffer.hpp>
#include  <seb_RootBase.hpp>
#pragma pack(8)

class  RootBaseTA :public TABuffer,
public eb_RootBase
{

public     :
public     : virtual                             logical Cancel ( );
public     : virtual                             logical CheckEBI (exd *exdptr );
public     : virtual                             uint8 CheckWProtect (exd *exdptr );
public     : virtual                             logical Delete (exd *exdptr );
public     : virtual                             logical GetEBI (exd *exdptr );
public     : virtual                             int32 GetLength (acb *acbptr );
public     : virtual                             int32 GetUsedLength (acb *acbptr );
public     : virtual                             logical IsEmpty ( );
public     : virtual                             logical LocateEntry (EB_Number entnr, uint16 version_nr=CUR_VERSION );
public     : virtual                             logical Read (exd *exdptr, int32 w_instlen=AUTO );
public     :                                                             RootBaseTA (LACObject *lobhandle, TABuffer *highTABuf, int32 tanumber );
public     : virtual                             logical Save ( );
public     : virtual                             logical Write (exd *exdptr );
public     : virtual                                                     ~RootBaseTA ( );
};

#pragma pack()
#endif
