/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Tarif

\brief    


\date     $Date: 2006/06/28 17:59:48,03 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Tarif_HPP
#define   pc0_s_Tarif_HPP

class     pc0_s_Tarif;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Tarif :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Tarif (PropertyHandle *prophdl );
public     :                                             pc0_s_Tarif (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
