/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Adresse

\brief    


\date     $Date: 2006/06/29 13:39:18,75 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Adresse_HPP
#define   pc0_Adresse_HPP

class     pc0_Adresse;

class     TP_ImportGlobals;
#include  <sPropertyHandle.hpp>
class  pc0_Adresse :public PropertyHandle
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Adresse (PropertyHandle *prophdl );
};

#endif
