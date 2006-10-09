/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Beruf

\brief    


\date     $Date: 2006/06/29 13:22:38,56 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Beruf_HPP
#define   pc0_s_Beruf_HPP

class     pc0_s_Beruf;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Beruf :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Beruf (PropertyHandle *prophdl );
public     :                                             pc0_s_Beruf (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
