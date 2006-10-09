/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Hund

\brief    


\date     $Date: 2006/06/29 19:05:08,75 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Hund_HPP
#define   pc0_Hund_HPP

class     pc0_Hund;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_Hund :public pc0Base_local
{

public     :
public     : virtual                                logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Hund (PropertyHandle *prophdl );
};

#endif
