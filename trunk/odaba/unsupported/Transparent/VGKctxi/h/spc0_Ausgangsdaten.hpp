/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Ausgangsdaten

\brief    


\date     $Date: 2006/07/07 13:49:38,31 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Ausgangsdaten_HPP
#define   pc0_Ausgangsdaten_HPP

class     pc0_Ausgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_Ausgangsdaten :public pc0Base_local
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportKinder (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportSchaeden (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportVV (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportVV_KFZ (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Ausgangsdaten (PropertyHandle *prophdl );
};

#endif
