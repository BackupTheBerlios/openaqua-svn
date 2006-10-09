/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Gesellschaft

\brief    


\date     $Date: 2006/06/28 15:05:07,31 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Gesellschaft_HPP
#define   pc0_s_Gesellschaft_HPP

class     pc0_s_Gesellschaft;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Gesellschaft :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Gesellschaft (PropertyHandle *prophdl );
public     :                                             pc0_s_Gesellschaft (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
