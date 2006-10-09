/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EventParms

\brief    


\date     $Date: 2006/03/12 19:13:21,85 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EventParms_HPP
#define   EventParms_HPP

class     EventParms;

#include  <sEB_Number.hpp>
#pragma pack(8)

class  EventParms
{
protected  :         char                                         is_instance;                                               
protected  :         char                                         identity[10];                                              
protected  :         char                                         term;                                                      

public     :
                     char                                         get_is_instance() { return(is_instance); }
                     char                                        *get_identity() { return(identity); }
public     :                                                             EventParms (logical is_inst, EB_Number entnr );
public     :                                     uint64 GetID ( );
public     :                                     logical IsInstance ( );
public     :                                                             ~EventParms ( );
};

#pragma pack()
#endif
