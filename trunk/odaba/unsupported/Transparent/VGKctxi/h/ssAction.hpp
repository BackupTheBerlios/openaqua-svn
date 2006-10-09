/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sAction

\brief    


\date     $Date: 2006/07/07 12:27:41,25 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sAction_HPP
#define   sAction_HPP

class     sAction;

#include  <sCTX_Structure.hpp>
#include  <ssBase_SharedData.hpp>
class  sAction :public sBase_SharedData
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBInitialize ( );
public     : virtual                                logical DBOpened ( );
public     :                                             sAction ( );
public     : virtual                                     ~sAction ( );
};

#endif
