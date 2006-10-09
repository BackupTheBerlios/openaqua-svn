/********************************* Interface Class Source Code ***************************/
/**
\package  OPI - 
\class    PropertyHandle

\brief    Property Handle
          Property  handle are used  to handle persistent  or transient {\b data
          source}.  A  data  source  is  a  collection,  object  instance  or an
          elementary  database  field.  A  data  source  contains the data for a
          property of a specific object.
          A  property handle  usually handles  a collection of subsequent object
          instance.  In  special  cases  the  collection  is  singular (e.g. the
          'direction'  for a  persion is  exactly one 'Adress' object instance).
          In  other cases the instance is elementary (as eg the given names of a
          person). 
          A  property handle has a cursor function  that allows to select one of
          the  instances in the collection as  the "current" instance. Only from
          the  selected instance  you can  retrieve data  by means of subsequent
          property  handles or  Get-functions (GetString(),  GetTime(), ...) for
          elementary datasources. 

          {\b Generic Property handles}

          You  can  define  generic  property handles using the generic property
          handle  contructor (PH(type)()). This requires that you have created a
          C++  header file for the referenced type.  In this case you can access
          elementary  data  field  in  the  instance  directly  referring to the
          generated  class  members.  For  references  the  instance  contains 
          corresponding  generic  property  handles  that  you  can reference by
          class  member name  as well.  In this  case you need not to create the
          property  handle  you  want  to access. This makes programming simpler
          but  in this case you must recompile the application when changing the
          database  structure. This is not  necessary when referring to property
          handles hierarchies created in the appplication.  

          {\b Property handle hierarchies}

          Property  handles  form  a  tree  that  defines  a specific view in an
          application.  When defining  this view  once the property handles cann
          be  used  as  long  as  the application follows the defined view. When
          defining  a property  handle for  "AllPersons", which  is an extent in
          the  database,  you  can  define  sub-ordinated  property  handles for
          'name',  'children', and  'company', which  refer to the persons name,
          its  children  and  the  company  the  person  is  working  for.  When
          selecting  another  person  in  the  AllPerson  property  handle  the 
          datasources  for 'name',  'children' and  'company' will change. This,
          however,  is  maintained  automatically  by  the  systen,  i.e.  when 
          changing  the selection in  an upper property  handle the data sources
          for  all subordinated  property handles  are updated automatically and
          you can access them directly. 

          {\b Filter and temporaty datasources}

          Usually  a property handle shows all the elements that have been added
          to  the data source. You can  restrict the number of visible instances
          by  setting  a  filter  (SetSelection())  using an expression or a C++
          function.  You can  also create  a new  data source using the Select()
          function which creates a temporary data source. 

          {\b Operations with Property handles}

          Property  handes  provide  all  algebraic  and set operations. You can
          apply  most of algebraic  operations  (as +,  -, * etc.) on elementary
          {\u  and} collection  data sources.  In this  case eg the '-' operator
          corresponds  to  the  relational  Minus()  operation.  In  most cases,
          however,  the types  of operands  must be  comparable. You can compare
          string  data  with  numeric  data  but  you  cannot  compare  a person
          collection with a date field. 
          Set  operations  are  defined  on the operations defined in relational
          algebra  (Intersection, Union, Minus, Select) rather that by using SQL
          like Select statements.

\date     $Date: 2006/08/29 20:25:15,37 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_PropertyHandle"

#include  <pdefault.h>
#include  <s_if_PropertyHandle.hpp>


#undef     MOD_ID
#define    MOD_ID  "Add"

logical __cdecl Add( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open();
                         if ( co->GetDescription() )
                         {
                           retval->CopyDescription(co->GetDescription());
                           retval->GetDescription()->set_set_operation(AUTO);
                         }
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1 : co->Add(*(*parmlist)[0]);
                                    break;
                           default: ERROR;
                         }
                         retval->CopyHandle(co);
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
#define    MOD_ID  "AppendString"

logical __cdecl AppendString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt  = parmlist ? parmlist->GetSize() : 0;
  char     *string   = NULL;
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : switch ( parmcnt )
                         {
                           case 1  : string   = (*parmlist)[0]->GetString(); 
                                     break;
                           case 0  : 
                           default : ERROR
                         }
                         retval->CopyHandle(NULL);
                         *retval = co->AppendString(string);
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
#define    MOD_ID  "CanUpdate"

logical __cdecl CanUpdate( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = !co->NoWrite();
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
#define    MOD_ID  "ChangeMode"

logical __cdecl ChangeMode( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int          parmcnt = parmlist ? parmlist->GetSize() : 0;
  int          mode    = UNDEF;
  logical      term = NO;
  Instance     instance;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( parmcnt != 1 )         ERROR
                         if ( !(mode = (*parmlist)[0]->GetInt()) )
                         {
                           if ( *(*parmlist)[0] == "PI_Read" )
                             mode = PI_Read;
                           else if ( *(*parmlist)[0] == "PI_Write" )
                             mode = PI_Write;
                           else if ( *(*parmlist)[0] == "PI_Update" )
                             mode = PI_Update;
                         }
                         if ( !mode )                ERROR
                         *retval = co->ChangeMode((PIACC)mode);
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
#define    MOD_ID  "CheckWProtect"

logical __cdecl CheckWProtect( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = co->CheckWProtect();
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
#define    MOD_ID  "Close"

logical __cdecl Close( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open(); // es fehlt Angabe fuer set_operation
                         break;
    case ET_First      : co->Close();
                         retval->CopyHandle(co);
                         break;
    case ET_Next       :
    default            : ERROR;
  }

RECOVER
  return(YES);
ENDSEQ
  return(NO);
}


#undef     MOD_ID
#define    MOD_ID  "Contains"

logical __cdecl Contains( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt   = parmlist ? parmlist->GetSize() : 0;
  char     *string;
  char     *prop_path;
  logical   case_opt = YES;
  logical   term     = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : switch ( parmcnt )   
                         {
                           case 3 : string = (char *)(*parmlist)[0]->GetArea();
                                    prop_path = (char *)(*parmlist)[1]->GetArea();
                                    case_opt = (*parmlist)[2]->IsTrue();
                                    *retval = co->Contains(string,prop_path,case_opt,YES);
                                    break;
                           case 2 : case_opt = (*parmlist)[2]->IsTrue();
                           case 1 : string = (char *)(*parmlist)[0]->GetArea();
                                    *retval = co->Contains(string,case_opt);
                                    break;
                           default: ERROR
                         }
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
#define    MOD_ID  "Copy"

logical __cdecl Copy( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open();
                         if ( co->GetDescription() )
                         {
                           retval->CopyDescription(co->GetDescription());
                           retval->GetDescription()->set_set_operation(AUTO);
                         }
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1 : co->Copy(*(*parmlist)[0]);
                                    break;
                           default: ERROR;
                         }
                         retval->CopyHandle(co);
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
#define    MOD_ID  "CopyData"

logical __cdecl CopyData( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  PIREPL    repl_opt= REPL_none;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = YES;
                         if ( !co->IsPositioned() )    LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 2 : repl_opt = (PIREPL)(*parmlist)[1]->GetInt();
                           case 1 : *retval = co->CopyData(*(*parmlist)[0],repl_opt);
                                    break;
                           default: ERROR;
                         }
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
#define    MOD_ID  "CopySet"

logical __cdecl CopySet( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(YES);
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1 : *retval = co->CopySet(*(*parmlist)[0]);
                                    break;
                           default: ERROR;
                         }
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
#define    MOD_ID  "Day"

logical __cdecl Day( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetDate().GetDay();
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
#define    MOD_ID  "Delete"

logical __cdecl Delete( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int          parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical      term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = NO;
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1: *retval = co->Delete(*(*parmlist)[0]);
                                   break;
                           case 0: *retval = co->Delete(AUTO);
                         }
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
#define    MOD_ID  "DeleteIndexEntry"

logical __cdecl DeleteIndexEntry( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  int32     set_pos0 = AUTO;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = NO;
                         if ( !co->IsCollection() )  LEAVESEQ
                         if ( parmcnt )
                           set_pos0 = (*parmlist)[0]->GetInt();
                         *retval = co->DeleteIndexEntry(set_pos0);
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
#define    MOD_ID  "DeleteSet"

logical __cdecl DeleteSet( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int          parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical      term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(YES);
                         break;
    case ET_First      : *retval = NO;
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1: *retval = co->Delete((*parmlist)[0]->IsTrue());
                                   break;
                           case 0: *retval = co->DeleteSet(YES);
                         }
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
#define    MOD_ID  "Distinct"

logical __cdecl Distinct( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int         parmcnt = parmlist ? parmlist->GetSize() : 0;
  char     *key     = NULL;
  int       i       = 0;
  logical   term    = NO;
BEGINSEQ
  if ( !co && parmcnt )
  {
    co = (*parmlist)[0];
    i = 1;
  }
  
  if ( !co->IsCollection() )  LEAVESEQ
  if ( parmcnt > i )
    key = (*parmlist)[i]->GetString();
  co->ToTop();
  retval->Distinct(*co,key,exectype);
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "Exist"

logical __cdecl Exist( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = NO;
                         if ( !co->IsCollection() )  LEAVESEQ
                         if ( parmcnt )
                           co->Get(*(*parmlist)[0]);
                         *retval = co->Exist();
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
#define    MOD_ID  "FindKey"

logical __cdecl FindKey( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   exact= YES;
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = NO;
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 2: exact = (*parmlist)[1]->IsTrue();
                           case 1: *retval = !co->LocateKey(*(*parmlist)[0],exact);
                                   break;
                           case 0: ERROR
                         }    
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
#define    MOD_ID  "First"

logical __cdecl First( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical                 term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = co->Get(FIRST_INSTANCE) ? YES : NO;
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
#define    MOD_ID  "Format"

logical __cdecl Format( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  int16     count   = 0;
  char     *parms[64];
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open((char *)NULL);
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = "";
                         if ( !co->IsCollection() )  LEAVESEQ
                         if ( !parmcnt )             ERROR
                         while ( ++count < parmcnt )
                         {
                           parms[count-1] = (*parmlist)[count]->GetString();
                         }
                         *retval = co->Format((*parmlist)[0]->GetString(),parms,count);
                         break;
    case ET_Next       :
    default            : ERROR;
  }
  
  

RECOVER
  term = NO;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "Get"

logical __cdecl Get( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open();
                         if ( co->GetDescription() )
                         {
                           retval->CopyDescription(co->GetDescription());
                           retval->GetDescription()->set_set_operation(AUTO);
                         }
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1: co->Get(*(*parmlist)[0]);
                                   break;
                           case 0: co->Get(AUTO);
                         }
                         if ( co->IsSelected() )
                           retval->CopyHandle(co);
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
#define    MOD_ID  "GetCount"

logical __cdecl GetCount( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(YES);
                         break;
    case ET_First      : *retval = co->GetCount();
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
#define    MOD_ID  "GetCurrentIndex"

logical __cdecl GetCurrentIndex( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         break;
    case ET_First      : *retval = co->GetCurrentIndex();
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
#define    MOD_ID  "GetDay"

logical __cdecl GetDay( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetDay();
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
#define    MOD_ID  "GetGUID"

logical __cdecl GetGUID( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_STRING));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : switch ( parmcnt )   
                         {
                           case 0 : *retval = co->GetGUID();
                                    break;
                           default: ERROR
                         }
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
#define    MOD_ID  "GetHours"

logical __cdecl GetHours( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical     term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetHours();
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
#define    MOD_ID  "GetKey"

logical __cdecl GetKey( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  char      string[1024];
  int32     lindx0;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_STRING));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : switch ( parmcnt )   
                         {
                           case 1 : lindx0 = (*parmlist)[0]->GetInt();
                           case 0 : *retval = co->KeyToString(string,co->GetKey(lindx0));
                                    break;
                           default: ERROR
                         }
    case ET_Next       :
    default            : ERROR;
  }
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "GetLOID"

logical __cdecl GetLOID( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : switch ( parmcnt )   
                         {
                           case 0 : *retval = co->GetLOID();
                                    break;
                           default: ERROR
                         }
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
#define    MOD_ID  "GetMinutes"

logical __cdecl GetMinutes( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical     term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetMinutes();
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
#define    MOD_ID  "GetMonth"

logical __cdecl GetMonth( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetMonth();
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
#define    MOD_ID  "GetParentProperty"

logical __cdecl GetParentProperty( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype ) 
  {
    case ET_Initialize : retval->Open();
                         if ( co->GetDescription() )
                         {
                           retval->CopyDescription(co->GetDescription());
                           retval->GetDescription()->set_set_operation(AUTO);
                         }
                         break;
    case ET_First      : retval->CopyHandle(co->GetParentProperty());
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
#define    MOD_ID  "GetPropertyHandle"

logical __cdecl GetPropertyHandle( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open();
                         if ( co->GetDescription() )
                         {
                           retval->CopyDescription(co->GetDescription());
                           retval->GetDescription()->set_set_operation(AUTO);
                         }
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1 : retval->CopyHandle(co->GetPropertyHandle((*parmlist)[0]->GetString()));
                                    break;
                           default: ERROR;
                         }
                         
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
#define    MOD_ID  "GetRelative"

logical __cdecl GetRelative( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open((char *)NULL);
                         if ( co->GetDescription() )
                           retval->CopyDescription(co->GetDescription());
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1: co->GetRelative((*parmlist)[0]->GetInt());
                                   break;
                           case 0: co->GetRelative(AUTO);
                         }
                         retval->CopyHandle(co);
    case ET_Next       :
    default            : ERROR;
  }
  
  

RECOVER
  term = NO;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "GetRelativeCount"

logical __cdecl GetRelativeCount( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(YES);
                         break;
    case ET_First      : *retval = co->GetRelativeCount();
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
#define    MOD_ID  "GetRelativeIndex"

logical __cdecl GetRelativeIndex( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   last_opt = NO;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( parmcnt > 0 )
                           last_opt = (*parmlist)[0]->IsTrue();
                         *retval = co->GetRelativeIndex(last_opt);
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
#define    MOD_ID  "GetSeconds"

logical __cdecl GetSeconds( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical     term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetSeconds();
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
#define    MOD_ID  "GetSubString"

logical __cdecl GetSubString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt   = parmlist ? parmlist->GetSize() : 0;
  int32     length    = AUTO;
  int32     start_pos = 0;
  logical   term      = NO;
BEGINSEQ
  switch ( exectype ) 
  {
    case ET_Initialize : retval->Open((char *)NULL);
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = "";
                         switch ( parmcnt )
                         {
                           case 2  : length = (*parmlist)[1]->GetInt();
                           case 1  : start_pos = (*parmlist)[0]->GetInt();
                           case 0  : *retval = co->GetSubString(start_pos,length);
                                     break;
                           default : ERROR
                         }
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
#define    MOD_ID  "GetText"

logical __cdecl GetText( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  int16     count   = 0;
  char     *parms[64];
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open((char *)NULL);
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = "";
                         if ( parmcnt > 1 )
                           *retval = co->GetText((*parmlist)[0]->GetString());
                         else
                           *retval = co->GetText();
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
#define    MOD_ID  "GetYear"

logical __cdecl GetYear( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetYear();
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
#define    MOD_ID  "GoTop"

logical __cdecl GoTop( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = !co->ToTop();
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
#define    MOD_ID  "HasData"

logical __cdecl HasData( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = co->HasData();
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
#define    MOD_ID  "HasDescription"

logical __cdecl HasDescription( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical                 cond = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = co->HasDescription();
                         break;
    case ET_Next       :
    default            : ERROR;
  }  
  


RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}


#undef     MOD_ID
#define    MOD_ID  "Inherits"

logical __cdecl Inherits( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : switch ( parmcnt )
                         {
                           case 1: *retval = co->Inherits((*parmlist)[0]->GetString());
                                   break;
                           case 0: ERROR
                         }    
                         break;
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
#define    MOD_ID  "InsertString"

logical __cdecl InsertString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt  = parmlist ? parmlist->GetSize() : 0;
  char     *string   = NULL;
  int32     position = 0;
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : switch ( parmcnt )
                         {
                           case 2  : position = (*parmlist)[1]->GetInt(); 
                           case 1  : string   = (*parmlist)[0]->GetString(); 
                                     break;
                           case 0  : 
                           default : ERROR
                         }
                         retval->CopyHandle(NULL);
                         *retval = co->InsertString(string,position);
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
#define    MOD_ID  "InstanceToString"

logical __cdecl InstanceToString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  char     *empty_string = NULL;
  char     *string_sep = NULL;
  char     *field_sep = NULL;
  char     *block_sep = NULL;
  logical   skip_trans = NO;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_STRING));
                         break;
    case ET_First      : switch ( parmcnt )   
                         {
                           case 5 : skip_trans = (*parmlist)[4]->IsTrue();
                           case 4 : empty_string = (char *)(*parmlist)[3]->GetArea();
                           case 3 : block_sep = (char *)(*parmlist)[2]->GetArea();
                           case 2 : field_sep = (char *)(*parmlist)[1]->GetArea();
                           case 1 : string_sep = (char *)(*parmlist)[0]->GetArea();
                           case 0 : *retval = co->InstanceToString(string_sep,field_sep,block_sep,empty_string,skip_trans);
                                    break;
                           default: ERROR
                         }
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
#define    MOD_ID  "IsA"

logical __cdecl IsA( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : switch ( parmcnt )
                         {
                           case 1: *retval = co->IsA((*parmlist)[0]->GetString());
                                   break;
                           case 0: ERROR
                         }    
                         break;
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
#define    MOD_ID  "IsEmpty"

logical __cdecl IsEmpty( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = co->IsEmpty();
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
#define    MOD_ID  "IsTrue"

logical __cdecl IsTrue( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = co->IsTrue();
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
#define    MOD_ID  "IsWriteProtected"

logical __cdecl IsWriteProtected( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = co->CheckWProtect();
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
#define    MOD_ID  "Last"

logical __cdecl Last( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical                 term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = co->Get(LAST_INSTANCE) ? YES : NO;
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
#define    MOD_ID  "LocateIndex"

logical __cdecl LocateIndex( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   exact= YES;
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = NO;
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 2: exact = (*parmlist)[1]->IsTrue();
                           case 1: *retval = co->LocateKey(*(*parmlist)[0],exact);
                                   break;
                           case 0: ERROR
                         }    
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
#define    MOD_ID  "LocateKey"

logical __cdecl LocateKey( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   exact= YES;
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = NO;
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 2: exact = (*parmlist)[1]->IsTrue();
                           case 1: *retval = co->LocateKey(*(*parmlist)[0],exact);
                                   break;
                           case 0: ERROR
                         }    
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
#define    MOD_ID  "Month"

logical __cdecl Month( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetDate().GetMonth();
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
#define    MOD_ID  "Next"

logical __cdecl Next( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  int32             count   = 1;
  logical           term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( !co->IsCollection() )  LEAVESEQ
                         if ( parmcnt )
                           count = MAX(1,(*parmlist)[0]->GetInt());
                         *retval = !co->Position(count);
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
#define    MOD_ID  "Open"

logical __cdecl Open( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int              parmcnt = parmlist ? parmlist->GetSize() : 0;
  PropertyHandle   ph; 
  void            *db_inst;
  logical          netopt = NO;
  PIACC            accopt = PI_Read;
  char            *prop_path;
  logical          term    = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : switch ( parmcnt )
                         {
                           case 3 : accopt    = (PIACC)GetSystemDictionary().StringToEnum("PIACC",*(*parmlist)[2]);
                           case 2 : prop_path = (*parmlist)[1]->GetString();
                                    db_inst   = (*parmlist)[0]->GetArea();
                                    break;
                           default: ERROR;
                         }
                         *retval = ph.Open(*(DatabaseHandle *)db_inst,prop_path,accopt);
                         if ( co->GetDescription() && !co->Inherits(ph) )
                           *retval = NO;
                         else
                           if ( co->SetTransientProperty(ph) )
                             co->CopyHandle(&ph);              // if not transient co
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
#define    MOD_ID  "Position"

logical __cdecl Position( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term = NO;
  Instance  instance;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         if ( parmcnt )
                           *retval = co->Position((*parmlist)[0]->GetInt());
                         else
                           *retval = co->Position(1);
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
#define    MOD_ID  "Previous"

logical __cdecl Previous( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  int32             count = 1;
  logical           term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( !co->IsCollection() )  LEAVESEQ
                         if ( parmcnt )
                           count = MAX(1,(*parmlist)[0]->GetInt());
                         *retval = !co->Position(-count);
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
#define    MOD_ID  "Provide"

logical __cdecl Provide( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  char     *key;
  logical   term = NO;
  Instance  instance;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open((char *)NULL);
                         if ( co->GetDescription() )
                           retval->CopyDescription(co->GetDescription());
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1: co->Provide(*(*parmlist)[0]);
                                   break;
                           case 0: co->Provide(FIRST_INSTANCE);
                         }
                         if ( co->IsSelected() )
                           retval->CopyHandle(co);
                         break;
    case ET_Next       :
    default            : ERROR;
  }
RECOVER
  term = NO;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "ProvideGlobal"

logical __cdecl ProvideGlobal( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  char     *key;
  logical   term = NO;
  Instance  instance;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->Open((char *)NULL);
                         if ( co->GetDescription() )
                           retval->CopyDescription(co->GetDescription());
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 1: co->ProvideGlobal(*(*parmlist)[0]);
                                   break;
                           case 0: co->ProvideGlobal(FIRST_INSTANCE);
                         }
                         retval->CopyHandle(co);
                         break;
    case ET_Next       :
    default            : ERROR;
  }  

RECOVER
  term = NO;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "RemoveFromCollection"

logical __cdecl RemoveFromCollection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = co->RemoveFromCollection();
                         break;
    case ET_Next       :
    default            : ERROR;
  }  

RECOVER

ENDSEQ
  return(NO);
}


#undef     MOD_ID
#define    MOD_ID  "RemoveInstance"

logical __cdecl RemoveInstance( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = !co->RemoveFromCollection();
                         break;
    case ET_Next       :
    default            : ERROR;
  }  

RECOVER

ENDSEQ
  return(NO);
}


#undef     MOD_ID
#define    MOD_ID  "RemoveString"

logical __cdecl RemoveString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt  = parmlist ? parmlist->GetSize() : 0;
  char     *string   = NULL;
  int32     position = 0;
  int32     len      = AUTO;
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : switch ( parmcnt )
                         {
                           case 3  : len = (*parmlist)[1]->GetInt(); 
                           case 2  : position = (*parmlist)[1]->GetInt(); 
                           case 1  : string   = (*parmlist)[0]->GetString(); 
                                     break;
                           case 0  : 
                           default : ERROR
                         }
                         retval->CopyHandle(NULL);
                         *retval = co->RemoveString(string,position,len);
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
#define    MOD_ID  "RepairIndex"

logical __cdecl RepairIndex( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  char     *key_name = NULL;
  char     *attrstr = NULL;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(YES);
                         break;
    case ET_First      : retval->CopyHandle(NULL);
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                           case 2: attrstr  = (*parmlist)[1]->GetString();
                           case 1: key_name = (*parmlist)[0]->GetString();
                         }
                         *retval = co->RepairIndex(key_name,attrstr);
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
#define    MOD_ID  "ReplaceString"

logical __cdecl ReplaceString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  char     *oldstr  = NULL;
  char     *newstr  = "";
  char     *parms[64];
  logical   term = NO;

BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : switch ( parmcnt )
                         {
                           case 2  : newstr = (*parmlist)[1]->GetString(); 
                           case 1  : oldstr = (*parmlist)[0]->GetString(); 
                                     break;
                           case 0  : 
                           default : ERROR
                         }
                         retval->CopyHandle(NULL);
                         *retval = co->ReplaceString(oldstr,newstr);
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
#define    MOD_ID  "ResetFilter"

logical __cdecl ResetFilter( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = !co->ResetSelection();
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
#define    MOD_ID  "ResetSelection"

logical __cdecl ResetSelection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = co->ResetSelection();
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
#define    MOD_ID  "ResetWProtect"

logical __cdecl ResetWProtect( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = co->ResetWProtect();
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
#define    MOD_ID  "ResetWriteProtection"

logical __cdecl ResetWriteProtection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = !co->ResetWProtect();
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
#define    MOD_ID  "Save"

logical __cdecl Save( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   save_opt   = NO;
  logical   switch_opt = NO;
  logical   term       = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = NO;
                         if ( !co->IsCollection() )  LEAVESEQ
                         switch ( parmcnt )
                         {
                            case 2 : switch_opt = (*parmlist)[0]->IsTrue();
                            case 1 : save_opt   = (*parmlist)[1]->IsTrue();
                            default: ;
                          }
                         *retval = co->Save(save_opt,switch_opt);
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
#define    MOD_ID  "SetFilter"

logical __cdecl SetFilter( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( parmcnt != 1 )         ERROR
                         *retval = !co->SetSelection((char *)(*parmlist)[0]->GetArea());
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
#define    MOD_ID  "SetSelection"

logical __cdecl SetSelection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int       parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : if ( parmcnt != 1 )         ERROR
                         *retval = co->SetSelection((char *)(*parmlist)[0]->GetArea());
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
#define    MOD_ID  "SetWProtect"

logical __cdecl SetWProtect( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = !co->SetWProtect();
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
#define    MOD_ID  "SetWriteProtection"

logical __cdecl SetWriteProtection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         break;
    case ET_First      : *retval = !co->SetWProtect();
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
#define    MOD_ID  "ToTop"

logical __cdecl ToTop( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                         retval->GetDescription()->set_set_operation(AUTO);
                         break;
    case ET_First      : *retval = co->ToTop();
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
#define    MOD_ID  "Year"

logical __cdecl Year( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  logical   term = NO;
BEGINSEQ
  switch ( exectype )
  {
    case ET_Initialize : retval->CopyDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                         retval->GetDescription()->set_set_operation(NO);
                         break;
    case ET_First      : *retval = co->GetDate().GetYear();
                         break;
    case ET_Next       :
    default            : ERROR;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

