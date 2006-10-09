/********************************* Interface Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_Project



\date     $Date: 2006/05/20 19:08:33,31 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_ODC_Project"

#include  <pfmodel.h>
#include  <s_if_ODC_Project.hpp>


#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

logical __cdecl GetDocFileName( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_Project      *CO      = (ODC_Project *)co->GetArea();
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
           case 1 : *retval = CO->GetDocFileName(co,nstring,
                                                 (*parmlist)[0]->GetString());
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
#define    MOD_ID  "GetProjectPath"

logical __cdecl GetProjectPath( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_Project      *CO      = (ODC_Project *)co->GetArea();
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
           case 1 : *retval = CO->GetProjectPath(co,nstring,
                                                 (*parmlist)[0]->GetString());
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

