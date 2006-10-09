/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecExchange

\brief    Data Exchange


\date     $Date: 2006/03/12 19:09:58,96 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExecExchange_HPP
#define   ExecExchange_HPP

class     ExecExchange;

#ifndef   P_ODS_Description_HPP
#define   P_ODS_Description_HPP
#include  <sPI.hpp>
class       ODS_Description;
PI_dcl     (ODS_Description)
#endif
#ifndef   DPA_ExecAlloc_HPP
#define   DPA_ExecAlloc_HPP
#include  <sExecAlloc.hpp>
#include  <sDPA.h>
#endif
#include  <sDBObjectHandle.hpp>
#include  <sDatabaseHandle.hpp>
#pragma pack(8)

class  ExecExchange
{
protected  :         DatabaseHandle                               res_db;                                                    
protected  :         DBObjectHandle                               ob_handle;                                                 
protected  :         DatabaseHandle                               ext_dbhandle;                                              
protected  :         DPA(ExecAlloc)                               allocations;                                               
protected  :         logical                                      exp_opt;                                                   
protected  :         logical                                      owns_object;                                               
protected  :         PI(ODS_Description)                          description;                                               //

public     :
                     DatabaseHandle                              &get_res_db() { return(res_db); }
                     DBObjectHandle                              &get_ob_handle() { return(ob_handle); }
                     DatabaseHandle                              &get_ext_dbhandle() { return(ext_dbhandle); }
                     DPA(ExecAlloc)                              &get_allocations() { return(allocations); }
                     logical                                      get_exp_opt() { return(exp_opt); }
                     logical                                      get_owns_object() { return(owns_object); }
                     PI(ODS_Description)                         &get_description() { return(description); }
public     :         OPI7ImpExp                                          ExecExchange (char *excnames, logical exp_opt, const DBObjectHandle &w_obhandle_c=DBObjectHandle(), const DatabaseHandle &w_resdb_c=DatabaseHandle() );
public     :         OPI7ImpExp                                          ExecExchange (char *excnames, logical exp_opt, PropertyHandle &pi_handle, const DatabaseHandle &w_resdb_c=DatabaseHandle() );
public     :         OPI7ImpExp                  logical Execute ( );
public     :         OPI7ImpExp                  char *GetExtExtentName (int32 indx0 );
public     :         OPI7ImpExp                  char *GetIntExtentName (int32 indx0 );
public     :         OPI7ImpExp                                          ~ExecExchange ( );
};

#pragma pack()
#endif
