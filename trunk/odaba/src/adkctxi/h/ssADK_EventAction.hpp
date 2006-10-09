/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    sADK_EventAction

\brief    


\date     $Date: 2006/03/30 21:11:52,51 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sADK_EventAction_HPP
#define   sADK_EventAction_HPP

class     sADK_EventAction;

#include  <ssLanguageDependendBase.hpp>
class  sADK_EventAction :public sLanguageDependendBase
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     :                                     logical DBCreated ( );
public     :                                     logical DBRead ( );
public     :                                     logical DBStored ( );
public     :                                     logical SetKeyString ( );
public     :                                                             sADK_EventAction ( );
public     :                                                             ~sADK_EventAction ( );
};

#endif
