/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Zahlungsweise

\brief    


\date     $Date: 2006/06/28 22:41:22,46 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_Zahlungsweise_HPP
#define   pc0_s_Zahlungsweise_HPP

class     pc0_s_Zahlungsweise;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_Zahlungsweise :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_Zahlungsweise (PropertyHandle *prophdl );
public     :                                             pc0_s_Zahlungsweise (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
