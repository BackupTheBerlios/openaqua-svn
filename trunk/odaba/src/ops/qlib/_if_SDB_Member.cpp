/********************************* Interface Class Source Code ***************************/
/**
\package  OPS - 
\class    SDB_Member

\brief    Structure member
          Structure  or  class  member  are  details  the  structure  definition
          consists   of.   Structure   member   may   appear  in ODABA structure
          definitions  as attributes, reference, relationship or base structure.
          In  ODABA  class  definition  members  appear  also  as  functions  or
          function,  windows  or  documents.  Members  are also used to describe
          function  parameters. In the scope of  a structure or class definition
          member names must be unique.

\date     $Date: 2006/07/12 19:11:41,96 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_SDB_Member"

#include  <pops7.h>
#include  <s_if_SDB_Member.hpp>


#undef     MOD_ID
#define    MOD_ID  "BitSize"

logical __cdecl BitSize( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_Member       *CO      = (SDB_Member *)co->GetArea();
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
           case 0 : *retval = CO->BitSize(co,nstring);
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


#undef     MOD_ID
#define    MOD_ID  "CharSize"

logical __cdecl CharSize( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_Member       *CO      = (SDB_Member *)co->GetArea();
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
           case 0 : *retval = CO->CharSize(co,nstring);
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


#undef     MOD_ID
#define    MOD_ID  "DataTypeCString"

logical __cdecl DataTypeCString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_Member       *CO      = (SDB_Member *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
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
           case 1 : *retval = CO->DataTypeCString((*parmlist)[0]->GetInt());
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


#undef     MOD_ID
#define    MOD_ID  "GetCOMType"

logical __cdecl GetCOMType( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_Member       *CO      = (SDB_Member *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static char       typestring[41];
  char             *typstr  = NULL;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                     ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->AllocDescription();
         retval->GetDescription(NO)->InitField(T_STRING,NO,NO,NO);
         break;
         
    case ET_First      : 
    
         if ( !CO )                                  ERROR
         *retval = "";
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : typstr = gvtxbts(typestring,CO->get_ddetype(),ID_SIZE);
                    break; 
           case 1 : typstr = (*parmlist)[0]->GetString();
                    break;
           default: ERROR
         }
         *retval = CO->GetCOMType(typstr,typestring);
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


#undef     MOD_ID
#define    MOD_ID  "GetPLType"

logical __cdecl GetPLType( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_Member       *CO      = (SDB_Member *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
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
           case 0 : *retval = CO->GetPLType((*parmlist)[0]->GetString());
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


#undef     MOD_ID
#define    MOD_ID  "IsAttrToBeAligned"

logical __cdecl IsAttrToBeAligned( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_Member       *CO      = (SDB_Member *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                    ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->AllocDescription();
         retval->GetDescription(NO)->InitField(T_INT,NO,NO,NO);
         break;
         
    case ET_First      : 
    
         *retval = 0;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->IsAttrToBeAligned();
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


#undef     MOD_ID
#define    MOD_ID  "KeyTypeCString"

logical __cdecl KeyTypeCString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_Member       *CO      = (SDB_Member *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
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
           case 0 : *retval = CO->KeyTypeCString();
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


#undef     MOD_ID
#define    MOD_ID  "ParmTypeCString"

logical __cdecl ParmTypeCString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_Member       *CO      = (SDB_Member *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
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
           case 0 : *retval = CO->ParmTypeCString();
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

