/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Branche

\brief    


\date     $Date: 2006/06/29 13:24:09,01 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Branche_HPP
#define   pc0_s_Branche_HPP

class     pc0_s_Branche;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Branche :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Branche (PropertyHandle *prophdl );
public     :                                             pc0_s_Branche (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
