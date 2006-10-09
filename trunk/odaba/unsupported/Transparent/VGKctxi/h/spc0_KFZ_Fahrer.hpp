/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_KFZ_Fahrer

\brief    


\date     $Date: 2006/07/03 17:35:44,20 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_KFZ_Fahrer_HPP
#define   pc0_KFZ_Fahrer_HPP

class     pc0_KFZ_Fahrer;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_KFZ_Fahrer :public pc0Base_local
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_KFZ_Fahrer (PropertyHandle *prophdl );
};

#endif
