/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Kind

\brief    


\date     $Date: 2006/07/07 12:23:13,23 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Kind_HPP
#define   pc0_Kind_HPP

class     pc0_Kind;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0Base_local.hpp>
class  pc0_Kind :public pc0Base_local
{

public     :
public     : virtual                                logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_Kind (PropertyHandle *prophdl );
};

#endif
