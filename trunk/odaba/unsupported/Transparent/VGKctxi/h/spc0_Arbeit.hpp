/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Arbeit

\brief    


\date     $Date: 2006/07/03 10:42:03,10 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Arbeit_HPP
#define   pc0_Arbeit_HPP

class     pc0_Arbeit;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_Arbeit :public pc0Base_local
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportArbeitgeber (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportOD (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportSebststaendig (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Arbeit (PropertyHandle *prophdl );
};

#endif
