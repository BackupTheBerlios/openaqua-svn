/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Staat

\brief    


\date     $Date: 2006/06/29 13:04:40,98 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Staat_HPP
#define   pc0_s_Staat_HPP

class     pc0_s_Staat;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Staat :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Staat (PropertyHandle *prophdl );
public     :                                             pc0_s_Staat (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
