/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Pferd

\brief    


\date     $Date: 2006/06/29 21:09:07,81 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Pferd_HPP
#define   pc0_Pferd_HPP

class     pc0_Pferd;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_Pferd :public pc0Base_local
{

public     :
public     : virtual                                logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Pferd (PropertyHandle *prophdl );
};

#endif
