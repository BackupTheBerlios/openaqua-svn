/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    DBIndexList



\date     $Date: 2006/04/26 19:32:38,48 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBIndexList_HPP
#define   DBIndexList_HPP

class     DBIndexList;

#ifndef   DLO_DBIndex_HPP
#define   DLO_DBIndex_HPP
#include  <sDBIndex.hpp>
#include  <sDLO.h>
#endif
#include  <sReferenceObject.hpp>
#pragma pack(8)

class  DBIndexList :public DLO(DBIndex),
public ReferenceObject
{

public     :
public     :                                                             DBIndexList ( );
public     :                                     char *GetIndexName (int32 indx0 );
public     : virtual                                                     ~DBIndexList ( );
};

#pragma pack()
#endif
