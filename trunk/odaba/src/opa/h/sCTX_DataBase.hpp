/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CTX_DataBase

\brief    Database Context
          The  database context  allows defining  functionality that is executed
          when  opening  or  closing  a  database. The database context does not
          have a parent context.
          The  default  database  context  can  be  overloaded  by a application
          specific database context class.

\date     $Date: 2006/03/12 19:12:42,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_DataBase_HPP
#define   CTX_DataBase_HPP

class     CTX_DataBase;

class     ACObject;
class     CTX_Base;
class     DBHandle;
class     PropertyHandle;
#include  <sCTX_DBBase.hpp>
#pragma pack(8)

class  CTX_DataBase :public CTX_DBBase
{
protected  :         ACObject                                    *object_handle ATTR_ALIGN(4);                               //

public     :
                     ACObject                                    *get_object_handle() { return(object_handle); }
public     :         opa7ImpExp                                          CTX_DataBase ( );
public     : virtual opa7ImpExp                  logical ExecLogin (PropertyHandle *prophdl );
public     :         opa7ImpExp                  ODABAClient &GetConnectionClient ( );
public     : virtual opa7ImpExp                  CTX_Types GetContextType ( );
public     :         opa7ImpExp                  DatabaseHandle &GetDBHandle ( );
public     :                                     void Initialize (DBHandle *dbhandle, CTX_Base *highctx );
public     :         opa7ImpExp                  int8 Login (PropertyHandle *prophdl );
public     : virtual opa7ImpExp                                          ~CTX_DataBase ( );
};

#pragma pack()
#endif
