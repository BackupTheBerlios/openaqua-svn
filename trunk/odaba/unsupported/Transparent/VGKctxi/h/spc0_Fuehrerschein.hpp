/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Fuehrerschein

\brief    


\date     $Date: 2006/07/03 17:08:30,06 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Fuehrerschein_HPP
#define   pc0_Fuehrerschein_HPP

class     pc0_Fuehrerschein;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_Fuehrerschein :public pc0Base_local
{

public     :
public     : virtual                                logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Fuehrerschein (PropertyHandle *prophdl );
};

#endif
