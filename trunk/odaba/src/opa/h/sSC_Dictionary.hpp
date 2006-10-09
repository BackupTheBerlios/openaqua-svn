/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_Dictionary

\brief    


\date     $Date: 2006/03/12 19:13:49,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_Dictionary_HPP
#define   SC_Dictionary_HPP

class     SC_Dictionary;

#include  <sDLL.h>
class     SC_Database;
class     CS_Connection;
#include  <cPIACC.h>
#include  <sCS_Handle.hpp>
#include  <sSC_Database.hpp>
#include  <sSC_Handle.hpp>
#pragma pack(8)

class  SC_Dictionary :public SC_Database,
public DictionaryHandle
{
protected  :         DLL(SC_Database)                            *databases ATTR_ALIGN(4);                                   //

public     :
                     DLL(SC_Database)                            *get_databases() { return(databases); }
public     :                                     void ForceClose (logical cache_opt );
public     : virtual                             char *GetName ( );
public     : virtual                             char *GetTypeName ( );
public     :                                     SC_Handle *IsUsingDB (char *cpath, int8 database_opt );
public     :         opa7ImpExp                  SC_Database *ProvideDatabase (int64 client_handle, char *cpath, PIACC accopt, logical online_version=NO, uint16 version_nr=CUR_VERSION, char sysenv=NO );
public     :         opa7ImpExp                  logical ReleaseDatabase (SC_Database *sc_database );
public     :         opa7ImpExp                                          SC_Dictionary (CS_Connection *cs_connection, SC_Handle *parent_handle, int64 client_handle );
public     :         opa7ImpExp                  void SetDictHdl (DictionaryHandle *dicthdl_ptr );
public     : virtual                                                     ~SC_Dictionary ( );
};

#pragma pack()
#endif
