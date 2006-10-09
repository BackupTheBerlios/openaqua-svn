/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cStructMemberList

\brief    


\date     $Date: 2006/06/03 15:05:24,70 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cStructMemberList_HPP
#define   cStructMemberList_HPP

class     cStructMemberList;

class     PropertyHandle;
#include  <scSDBResource_Base.hpp>
class  cStructMemberList :public cSDBResource_Base
{

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterInsertData ( );
public     : virtual                                int8 DoBeforeInsertData ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical SetDefaults ( );
public     :                                        logical SetDefaults (PropertyHandle *prophdl, char *typenames );
public     :                                             cStructMemberList ( );
public     :                                             ~cStructMemberList ( );
};

#endif
