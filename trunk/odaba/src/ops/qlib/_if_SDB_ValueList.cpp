/********************************* Interface Class Source Code ***************************/
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

\date     $Date: 2006/07/12 19:11:50,98 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_SDB_ValueList"

#include  <pops7.h>
#include  <s_if_SDB_ValueList.hpp>


#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

logical __cdecl GetDocFileName( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_ValueList    *CO      = (SDB_ValueList *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  NString           nstring;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                   ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->AllocDescription();
         retval->GetDescription(NO)->InitField(T_STRING,NO,NO,NO);
         break;
         
    case ET_First      : 
    
         *retval = "";
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->GetDocFileName(co,nstring);
                    break;
           default: ERROR
         }
         break;
         
    case ET_Next       :
    default            : 
         
         ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

