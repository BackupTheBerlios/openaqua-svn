/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Stammdaten

\brief    


\date     $Date: 2006/06/28 15:04:19,28 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Stammdaten_HPP
#define   pc0_Stammdaten_HPP

class     pc0_Stammdaten;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc0_Stammdaten :public PropertyHandle
{

public     :
public     :                                        logical CheckValidExistance (int32 id );
public     :                                             pc0_Stammdaten (PropertyHandle *prophdl );
public     :                                             pc0_Stammdaten (DatabaseHandle &dbhandle, char *extnames, PIACC accopt );
};

#endif
