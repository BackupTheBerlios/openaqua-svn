/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_KFZVS

\brief    


\date     $Date: 2006/07/03 19:15:44,53 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_KFZVS_HPP
#define   pc0_KFZVS_HPP

class     pc0_KFZVS;

class     TP_ImportGlobals;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0Base_VS.hpp>
class  pc0_KFZVS :public pc0Base_VS
{

public     :
public     : virtual                                logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_KFZVS (PropertyHandle *prophdl );
public     :                                             pc0_KFZVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
