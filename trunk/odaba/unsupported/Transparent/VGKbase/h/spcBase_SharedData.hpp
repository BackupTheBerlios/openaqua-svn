/******************************** Class Declaration *****************************************************/
/**
\class pcBase_SharedData

\brief 

\date $Date: 2006/07/12 14:40:12,75 $
\dbsource q:\transparent\transparent.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#ifndef   pcBase_SharedData_HPP
#define   pcBase_SharedData_HPP

class     pcBase_SharedData;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spcBase_NotizHaving.hpp>
class  pcBase_SharedData :public pcBase_NotizHaving
{

public     :
public     : static                                 logical __cdecl CalculateIdentKey (char *keyarea, int32 size, char kenner, int32 id );
public     :                                        logical CreateSharedData ( );
public     :                                        logical LocateID (char *string );
public     :                                             pcBase_SharedData (PropertyHandle *prophdl );
public     :                                             pcBase_SharedData (DatabaseHandle &dbhandle, char *extnames, PIACC accopt );
};

#endif
