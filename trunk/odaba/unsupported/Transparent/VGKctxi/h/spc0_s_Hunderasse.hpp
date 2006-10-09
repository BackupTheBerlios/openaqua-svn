/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Hunderasse

\brief    


\date     $Date: 2006/07/07 18:08:25,87 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Hunderasse_HPP
#define   pc0_s_Hunderasse_HPP

class     pc0_s_Hunderasse;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Hunderasse :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Hunderasse (PropertyHandle *prophdl );
public     :                                             pc0_s_Hunderasse (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
