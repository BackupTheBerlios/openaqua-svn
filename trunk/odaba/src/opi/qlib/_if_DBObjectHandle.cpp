/********************************* Interface Class Source Code ***************************/
/**
\package  OPI - 
\class    DBObjectHandle

\brief    Database Object handle
          Database  object  handles  are  necessary  for  accessing  data  in an
          database  object. A  database object  can be  considered as a database
          within  a database. Each  database has a  root database object on top.
          Below  each  database  object  any  number  of  subordinated  database
          objects can be created. 
          Database  objects  in  a  database  are  logically  separated  but not
          physically.  Thus,  it  becomes  possible  to  establish links between
          structure  instances  in  different  database  objects.  Each database
          object  has, however, its own  extents containing the global instances
          of the database object. 
          The  database object  handle for  the root  database object is part of
          the  database  handle  (->  DatabaseHandle)  and need not to be opened
          explicitly. 
          A  database  object  handle  is  required  for opening extent property
          handles for accessing structure instances stored in extents.
          The  database  object  handle administrates transactions. Transactions
          can  be  started  and  stopped  for  each  object handle. The database
          object  handle is not thread save,  i.e. a database object handle must
          not be used simultaneously in different threads. 
          The  database  object  supports  version  slices,  i.e.  each database
          object may have its own current version.

\date     $Date: 2006/08/27 20:20:45,10 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_DBObjectHandle"

#include  <pdefault.h>
#include  <s_if_DBObjectHandle.hpp>


#undef     MOD_ID
#define    MOD_ID  "BeginTransaction"

logical __cdecl BeginTransaction( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  int32     max_num = AUTO;
  logical   ext_ta  = NO;
  void     *instarea;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( !(instarea = co->Get(0).GetArea()) )
                                                     ERROR
                         switch ( parmcnt )
                         {
                            case 2 : max_num = (*parmlist)[1]->GetInt();
                            case 1 : ext_ta  = (*parmlist)[0]->IsTrue();
                            default: ;
                          }
                         *retval = ((DBObjectHandle *)instarea)->BeginTransaction(ext_ta,max_num);
                         break;
    case ET_Next       :
    default            : ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "CommitTransaction"

logical __cdecl CommitTransaction( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  int16     ta_level = AUTO;
  void     *instarea;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( !(instarea = co->Get(0).GetArea()) )
                                                     ERROR
                         if ( parmcnt )
                           ta_level = (*parmlist)[0]->GetInt();
                         *retval = ((DBObjectHandle *)instarea)->CommitTransaction(ta_level);
                         break;
    case ET_Next       :
    default            : ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "RollBack"

logical __cdecl RollBack( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  void     *instarea;
  int16     ta_level = AUTO;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( !(instarea = co->Get(0).GetArea()) )
                                                     ERROR
                         if ( parmcnt )
                           ta_level = (*parmlist)[0]->GetInt();
                         *retval = ((DBObjectHandle *)instarea)->RollBack(ta_level);
                         break;
    case ET_Next       :
    default            : ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

