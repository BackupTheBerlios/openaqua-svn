/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_VorSchaden

\brief    


\date     $Date: 2006/06/28 23:54:01,70 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_VorSchaden_HPP
#define   pc0_VorSchaden_HPP

class     pc0_VorSchaden;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_VorSchaden :public pc0Base_local
{

public     :
public     : virtual                                logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_VorSchaden (PropertyHandle *prophdl );
};

#endif
