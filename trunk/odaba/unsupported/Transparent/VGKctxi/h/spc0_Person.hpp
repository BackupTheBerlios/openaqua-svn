/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_Person

\brief    


\date     $Date: 2006/07/03 13:31:24,70 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_Person_HPP
#define   pc0_Person_HPP

class     pc0_Person;

class     TP_ImportGlobals;
#include  <sPropertyHandle.hpp>
class  pc0_Person :public PropertyHandle
{

public     :
public     :                                        logical CreatePerson (char kenner, int32 id, TP_ImportGlobals *imp_globals );
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals, logical vn_opt );
public     :                                        logical ImportKind (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportKinder (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportKontakt (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical SavePerson (TP_ImportGlobals *imp_globals );
public     :                                             pc0_Person (PropertyHandle *prophdl );
};

#endif
