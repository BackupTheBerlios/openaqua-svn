/******************************** Class Declaration *****************************************************/
/**
\class pcBase_NotizHaving

\brief 

\date $Date: 2006/07/12 17:19:19,64 $
\dbsource q:\transparent\transparent.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#ifndef   pcBase_NotizHaving_HPP
#define   pcBase_NotizHaving_HPP

class     pcBase_NotizHaving;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spcBase.hpp>
class  pcBase_NotizHaving :public pcBase
{

public     :
public     :                                        PropertyHandle *CreateNotiz (char *typ_string, char *betreff_text, char *von_an );
public     :                                        PropertyHandle *CreateWiedervorlageNotiz (char *betreff_text, char *von_an );
public     :                                        PropertyHandle *ResetWV ( );
public     :                                             pcBase_NotizHaving (PropertyHandle *prophdl );
public     :                                             pcBase_NotizHaving (DatabaseHandle &dbhandle, char *extnames, PIACC accopt );
};

#endif
