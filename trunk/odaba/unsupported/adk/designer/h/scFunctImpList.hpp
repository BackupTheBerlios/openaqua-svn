/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cFunctImpList



\date     $Date: 2006/04/24 13:36:21,60 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cFunctImpList_HPP
#define   cFunctImpList_HPP

class     cFunctImpList;

#include  <scSDBResource_Base.hpp>
class  cFunctImpList :public cSDBResource_Base
{
protected  :         PropertyHandle                               implementation_descr;                                      

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual DesignerImpExp              int8 DoAfterDeleteData ( );
public     : virtual DesignerImpExp              int8 DoAfterInsertData ( );
public     : virtual DesignerImpExp              int8 DoBeforeClose ( );
public     : virtual DesignerImpExp              int8 DoBeforeDeleteData ( );
public     : virtual DesignerImpExp              int8 DoBeforeInsertData ( );
public     :                                                             cFunctImpList ( );
public     : virtual                                                     ~cFunctImpList ( );
};

#endif
