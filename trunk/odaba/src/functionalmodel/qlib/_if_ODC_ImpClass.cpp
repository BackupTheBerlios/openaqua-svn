/********************************* Interface Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_ImpClass



\date     $Date: 2006/05/20 19:07:57,20 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_ODC_ImpClass"

#include  <pfmodel.h>
#include  <s_if_ODC_ImpClass.hpp>


#undef     MOD_ID
#define    MOD_ID  "ExpressionsOnly"

logical __cdecl ExpressionsOnly( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_ImpClass     *CO      = (ODC_ImpClass *)co->GetArea();
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
         
         *retval = NO;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->ExpressionsOnly(co);
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
#define    MOD_ID  "GetDocFileName"

logical __cdecl GetDocFileName( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_ImpClass     *CO      = (ODC_ImpClass *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  DBFieldDef        flddef;
  NString           nstring;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                      ERROR
  
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
           case 1 : 
           case 2 : *retval = CO->GetDocFileName(co,nstring,
                                                 (*parmlist)[0]->GetString(),
                                                 parmcnt > 1 ? (*parmlist)[1]->IsTrue() : NO);
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
#define    MOD_ID  "IsExprClass"

logical __cdecl IsExprClass( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_ImpClass     *CO      = (ODC_ImpClass *)co->GetArea();
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
         
         *retval = NO;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->IsExprClass(co);
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
#define    MOD_ID  "IsIFClass"

logical __cdecl IsIFClass( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_ImpClass     *CO      = (ODC_ImpClass *)co->GetArea();
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
         
         *retval = NO;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->IsIFClass(co,NULL);
                    break;
           case 1 : *retval = CO->IsIFClass(co,(*parmlist)[0]->GetString());
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

