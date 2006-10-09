/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_Leistung

\brief    


\date     $Date: 2006/07/21 12:08:23,29 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_Leistung_HPP
#define   pc_Leistung_HPP

class     pc_Leistung;

#include  <sPropertyHandle.hpp>
class  pc_Leistung :public PropertyHandle
{

public     :
public     :                                        PropertyHandle *GPHWert (char *typ_string, logical provide );
public     :                                             pc_Leistung (PropertyHandle *prophdl );
};

#endif
