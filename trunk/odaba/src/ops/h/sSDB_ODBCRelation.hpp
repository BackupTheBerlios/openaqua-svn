/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ODBCRelation

\brief    ODBC relation
          Extent  definitions  for  external  ODBC  relations  can  be  used for
          accessing  data  via  ODBC  interface. The interface provides read and
          write access, but is mainly intended for read access. 
          ODBC  extents can be  accessed as other  database collections by means
          of property handles, which allow keyed access or access by position.

\date     $Date: 2006/03/13 21:30:10,78 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ODBCRelation_HPP
#define   SDB_ODBCRelation_HPP

class     SDB_ODBCRelation;

#include  <sSDB_Reference.hpp>
#pragma pack(8)

class  SDB_ODBCRelation :public SDB_Reference
{
protected  :         char                                         data_source[81] ATTR_ALIGN(4);                             // Data source reference
protected  :         char                                         user_id[16];                                               // User identification
protected  :         char                                         password[16];                                              // Password
protected  :         PI(mem)                                      SQL_Statement;                                             // SQL statement

public     :
                     char                                        *get_data_source() { return(data_source); }
                     char                                        *get_user_id() { return(user_id); }
                     char                                        *get_password() { return(password); }
                     PI(mem)                                     &get_SQL_Statement() { return(SQL_Statement); }
};

#pragma pack()
#endif
