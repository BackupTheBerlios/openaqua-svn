/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_HausratVS

\brief    


\date     $Date: 2006/06/29 14:22:19,39 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_HausratVS_HPP
#define   pc0_HausratVS_HPP

class     pc0_HausratVS;

class     TP_ImportGlobals;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0Base_VS.hpp>
class  pc0_HausratVS :public pc0Base_VS
{

public     :
public     : virtual                                logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_HausratVS (PropertyHandle *prophdl );
public     :                                             pc0_HausratVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
