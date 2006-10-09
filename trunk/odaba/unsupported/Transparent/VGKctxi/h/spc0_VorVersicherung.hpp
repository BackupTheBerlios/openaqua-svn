/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_VorVersicherung

\brief    


\date     $Date: 2006/07/03 15:10:41,21 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_VorVersicherung_HPP
#define   pc0_VorVersicherung_HPP

class     pc0_VorVersicherung;

class     TP_ImportGlobals;
#include  <sPropertyHandle.hpp>
#include  <spc0Base_local.hpp>
class  pc0_VorVersicherung :public pc0Base_local
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportKFZ (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_VorVersicherung (PropertyHandle *prophdl );
};

#endif
