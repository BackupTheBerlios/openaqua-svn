/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0Base_local

\brief    


\date     $Date: 2006/06/29 11:03:32,71 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0Base_local_HPP
#define   pc0Base_local_HPP

class     pc0Base_local;

class     TP_ImportGlobals;
#include  <sPropertyHandle.hpp>
class  pc0Base_local :public PropertyHandle
{

public     :
public     :                                        logical Add (Key key, TP_ImportGlobals *imp_globals );
public     : virtual                                logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportAlle (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical Message (char *typ_string, char *text, TP_ImportGlobals *imp_globals, logical check_opt );
public     :                                        logical Provide (int32 indx0, TP_ImportGlobals *imp_globals );
public     :                                        logical Provide (char *typ_string, TP_ImportGlobals *imp_globals );
public     :                                        logical Save (char *typ_string, TP_ImportGlobals *imp_globals );
public     :                                             pc0Base_local (PropertyHandle *prophdl );
};

#endif
