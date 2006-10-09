/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Partner

\brief    


\date     $Date: 2006/06/28 18:01:35,39 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Partner_HPP
#define   pc0_s_Partner_HPP

class     pc0_s_Partner;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Partner :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Partner (PropertyHandle *prophdl );
public     :                                             pc0_s_Partner (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
