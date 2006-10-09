/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Leistung

\brief    


\date     $Date: 2006/07/03 13:12:35,76 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Leistung_HPP
#define   pc0_Leistung_HPP

class     pc0_Leistung;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_Leistung :public pc0Base_local
{

public     :
public     :                                        logical Import (char *typ_string, PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportGliedertaxen (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Leistung (PropertyHandle *prophdl );
};

#endif
