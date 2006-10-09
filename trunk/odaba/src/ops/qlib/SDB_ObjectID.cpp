/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ObjectID

\brief    Database object instance (internal)
          When  accessing  a  database  object  in  the  database,  the external
          database  object  is  provided  in  an internal form, which transforms
          database addresses into access handles (property handle). 
          This  structure  is  equivalent  to  SDB_ObjectExt,  but  defines  the
          internal presentation of a database object instance.

\date     $Date: 2006/03/13 21:30:21,29 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_ObjectID"

#include  <pops7.h>
#include  <sSDB_ObjectID.hpp>



