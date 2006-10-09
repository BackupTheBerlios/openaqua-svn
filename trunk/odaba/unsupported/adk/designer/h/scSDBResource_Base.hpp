/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/21|16:26:03,43}|(REF) - Context that communicates with the output area
\class    cSDBResource_Base

\brief    


\date     $Date: 2006/04/24 12:52:58,48 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cSDBResource_Base_HPP
#define   cSDBResource_Base_HPP

class     cSDBResource_Base;

class  cSDBResource_Base :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterEnter ( );
public     : virtual                             int8 DoAfterSelect ( );
public     :                                     logical SetDocumentPH ( );
public     :                                                             cSDBResource_Base ( );
public     : virtual                                                     ~cSDBResource_Base ( );
};

#endif
