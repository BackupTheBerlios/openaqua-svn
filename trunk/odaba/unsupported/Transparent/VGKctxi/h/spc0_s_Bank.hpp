/******************************** Class Declaration *****************************************************/
/**
\class pc0_s_Bank

\brief 

\date $Date: 2006/06/28 20:17:56,35 $
\dbsource q:\transparent\transparent.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#ifndef   pc0_s_Bank_HPP
#define   pc0_s_Bank_HPP

class     pc0_s_Bank;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc0_s_Bank :public PropertyHandle
{

public     :
public     :                                        logical CheckValidExistance (char *string );
public     :                                             pc0_s_Bank (PropertyHandle *prophdl );
public     :                                             pc0_s_Bank (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
