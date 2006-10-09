/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Pferderasse

\brief    


\date     $Date: 2006/07/07 17:25:50,71 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Pferderasse_HPP
#define   pc0_s_Pferderasse_HPP

class     pc0_s_Pferderasse;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Pferderasse :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Pferderasse (PropertyHandle *prophdl );
public     :                                             pc0_s_Pferderasse (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
