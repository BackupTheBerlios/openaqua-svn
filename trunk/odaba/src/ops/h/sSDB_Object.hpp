/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_Object

\brief    Not used


\date     $Date: 2006/03/13 21:30:10,82 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Object_HPP
#define   SDB_Object_HPP

class     SDB_Object;

#include  <sEB_Number.hpp>
#pragma pack(8)

class  SDB_Object
{
protected  :         int16                                        type_id;                                                   //
protected  :         EB_Number                                    address;                                                   //

public     :
                     int16                                        get_type_id() { return(type_id); }
                     EB_Number                                   &get_address() { return(address); }
};

#pragma pack()
#endif
