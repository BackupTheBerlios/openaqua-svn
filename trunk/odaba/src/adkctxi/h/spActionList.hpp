/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pActionList



\date     $Date: 2006/05/23 13:18:38,62 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pActionList_HPP
#define   pActionList_HPP

class     pActionList;

class  pActionList :public CTX_Property
{

public     :
public     :                                        int32 Create (CTX_Property **propctx_ptrp );
public     :                                        logical DBInserted ( );
public     :                                             pActionList ( );
public     :                                             ~pActionList ( );
};

#endif
