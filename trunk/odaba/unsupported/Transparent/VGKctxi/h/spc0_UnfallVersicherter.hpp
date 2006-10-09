/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_UnfallVersicherter

\brief    


\date     $Date: 2006/07/03 12:04:37,09 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_UnfallVersicherter_HPP
#define   pc0_UnfallVersicherter_HPP

class     pc0_UnfallVersicherter;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_UnfallVersicherter :public pc0Base_local
{

public     :
public     :                                        logical ImportDaten (PropertyHandle *source_ph, logical partner_opt, logical kinder_opt, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportResult (PropertyHandle *source_ph, logical partner_opt, logical kinder_opt, TP_ImportGlobals *imp_globals );
public     :                                             pc0_UnfallVersicherter (PropertyHandle *prophdl );
};

#endif
