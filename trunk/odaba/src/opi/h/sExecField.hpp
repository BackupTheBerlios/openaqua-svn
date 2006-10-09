/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecField

\brief    


\date     $Date: 2006/03/12 19:09:59,26 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExecField_HPP
#define   ExecField_HPP

class     ExecField;

#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  ExecField
{
protected  :         PropertyHandle                              *db_field;                                                  
protected  :         int32                                        index;                                                     
protected  :         char                                         attr_type[33];                                             

public     :
                     PropertyHandle                              *get_db_field() { return(db_field); }
                     int32                                        get_index() { return(index); }
                     char                                        *get_attr_type() { return(attr_type); }
public     :                                                             ExecField (PropertyHandle *dat_field, PropertyHandle &prop_dbf );
public     :                                                             ExecField ( );
public     :                                     logical LocateInstance (void *inst_ptr );
public     :                                                             ~ExecField ( );
};

#pragma pack()
#endif
