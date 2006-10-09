/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pcBase

\brief    


\date     $Date: 2006/07/12 14:42:10,29 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pcBase_HPP
#define   pcBase_HPP

class     pcBase;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pcBase :public PropertyHandle
{

public     :
public     :                                        logical ProvideInSpecialExtent (char *extnames );
public     :                                        logical RemoveFromSpecialExtent (char *extnames );
public     :                                             pcBase (PropertyHandle *prophdl );
public     :                                             pcBase (DatabaseHandle &dbhandle, char *extnames, PIACC accopt );
};

#endif
