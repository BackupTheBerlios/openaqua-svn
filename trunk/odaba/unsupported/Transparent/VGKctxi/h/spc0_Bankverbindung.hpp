/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Bankverbindung

\brief    


\date     $Date: 2006/06/28 21:27:08,14 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Bankverbindung_HPP
#define   pc0_Bankverbindung_HPP

class     pc0_Bankverbindung;

class     TP_ImportGlobals;
#include  <sPropertyHandle.hpp>
#include  <spc0Base_local.hpp>
class  pc0_Bankverbindung :public pc0Base_local
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Bankverbindung (PropertyHandle *prophdl );
};

#endif
