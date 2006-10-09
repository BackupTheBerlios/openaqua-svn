/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    sSDB_ValueList



\date     $Date: 2006/05/03 17:35:16,56 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_ValueList_HPP
#define   sSDB_ValueList_HPP

class     sSDB_ValueList;

class  sSDB_ValueList :protected CTX_Structure
{

public     :
public     :                                        int32 Create (CTX_Structure **CTX_Structure_ptrp );
public     : virtual                                logical DBCreated ( );
public     :                                             sSDB_ValueList ( );
public     : virtual                                     ~sSDB_ValueList ( );
};

#endif
