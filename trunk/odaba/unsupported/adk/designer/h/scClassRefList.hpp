/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassRefList

\brief    


\date     $Date: 2006/04/24 13:33:04,59 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassRefList_HPP
#define   cClassRefList_HPP

class     cClassRefList;

class  cClassRefList :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoBeforeInsertData ( );
public     :                                                             cClassRefList ( );
public     : virtual                                                     ~cClassRefList ( );
};

#endif
