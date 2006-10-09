/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    SDB_ValueList

\brief    Value list
          A  value  list  defines  a  list of enumerated values. Value lists are
          used  for  defining  value  domains,  which  describe the extension of
          permisible  values  in  terms  of  value domain items. A value list my
          define a hierarchical structure of values (classification).
          A  value list can be defined as  database resource, but also as ad hoc
          value list e.g. in a grouping clause.
          A  value  list  can  be  used  as  global  value  list  or  as list of
          sub-categories  for  another  value.  A  value list may act as list of
          sub-categories for any number of values.

\date     $Date: 2006/07/12 19:11:50,67 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_ValueList"

#include  <pops7.h>
#include  <spc_SDB_ValueList.hpp>
#include  <sSDB_ValueList.hpp>


/******************************************************************************/
/**
\brief  GetDocFileName - 


\return filnames - 
/******************************************************************************/
/**
\brief  i00 - 


\param  prophdl - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

char *SDB_ValueList :: GetDocFileName (PropertyHandle *prophdl, NString &nstring )
{

  return ( pc_SDB_ValueList(prophdl).GetDocFileName(nstring) );


}


