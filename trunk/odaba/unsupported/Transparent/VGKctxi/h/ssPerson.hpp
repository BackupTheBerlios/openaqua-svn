/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sPerson

\brief    


\date     $Date: 2006/06/20 11:04:16,31 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sPerson_HPP
#define   sPerson_HPP

class     sPerson;

#include  <sCTX_Structure.hpp>
#include  <ssBase_SharedData.hpp>
class  sPerson :public sBase_SharedData
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     :                                             sPerson ( );
public     : virtual                                     ~sPerson ( );
};

#endif
