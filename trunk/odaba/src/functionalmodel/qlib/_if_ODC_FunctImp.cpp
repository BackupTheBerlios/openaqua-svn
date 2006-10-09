/********************************* Interface Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_FunctImp



\date     $Date: 2006/05/20 19:08:53,23 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_ODC_FunctImp"

#include  <pfmodel.h>
#include  <s_if_ODC_FunctImp.hpp>


#undef     MOD_ID
#define    MOD_ID  "GetCIFunctName"

logical __cdecl GetCIFunctName( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  NString           nstring;
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
    
         *retval = "";
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->GetCIFunctName(co,nstring);
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
#define    MOD_ID  "GetCIRetValue"

logical __cdecl GetCIRetValue( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  NString           nstring;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                  ERROR
  
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
           case 0 : *retval = CO->GetCIRetValue(co,nstring);
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
#define    MOD_ID  "GetCOMParmList"

logical __cdecl GetCOMParmList( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  NString           nstring;
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
    
         *retval = "";
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 1 : *retval = CO->GetCOMParmList(co,nstring,
                                                 (*parmlist)[0]->IsTrue());
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
#define    MOD_ID  "GetParmCallList"

logical __cdecl GetParmCallList( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  NString           nstring;
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
    
         *retval = "";
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->GetParmCallList(co,nstring);
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
#define    MOD_ID  "GetParmList"

logical __cdecl GetParmList( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  NString           nstring;
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
    
         *retval = "";
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->GetParmList(co,nstring,
                                              NO);
                    break;
           case 1 : *retval = CO->GetParmList(co,nstring,
                                              (*parmlist)[0]->IsTrue());
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
#define    MOD_ID  "IsIFImplement"

logical __cdecl IsIFImplement( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                     ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->AllocDescription();
         retval->GetDescription(NO)->InitField(T_LO,NO,NO,NO);
         break;
         
    case ET_First      : 
         
         *retval = NO;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 1 : *retval = CO->IsIFImplement((*parmlist)[0]->GetString());
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
#define    MOD_ID  "SetLineCount"

logical __cdecl SetLineCount( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                  ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
    
         retval->AllocDescription();
         retval->GetDescription(NO)->InitField(T_LO,NO,NO,NO);
         break;
         
    case ET_First      : 
    
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 2 : *retval = CO->SetLineCount(co,
                                              (*parmlist)[0]->GetString(),
                                              (*parmlist)[1]->GetInt());
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
#define    MOD_ID  "UpdatePrototype"

logical __cdecl UpdatePrototype( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                    ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->AllocDescription();
         retval->GetDescription(NO)->InitField(T_LO,NO,NO,NO);
         break;
         
    case ET_First      : 
    
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->UpdatePrototype(co);
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
#define    MOD_ID  "UpdateSource"

logical __cdecl UpdateSource( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_FunctImp     *CO      = (ODC_FunctImp *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                   ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->AllocDescription();
         retval->GetDescription(NO)->InitField(T_LO,NO,NO,NO);
         break;
         
    case ET_First      : 
         
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->UpdateSource(co);
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

