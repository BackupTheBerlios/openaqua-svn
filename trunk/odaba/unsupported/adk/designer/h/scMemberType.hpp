/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cMemberType

\brief    


\date     $Date: 2006/04/24 13:39:00,21 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cMemberType_HPP
#define   cMemberType_HPP

class     cMemberType;

class  cMemberType :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterStoreData ( );
public     :                                                             cMemberType ( );
public     : virtual                                                     ~cMemberType ( );
};

#endif
