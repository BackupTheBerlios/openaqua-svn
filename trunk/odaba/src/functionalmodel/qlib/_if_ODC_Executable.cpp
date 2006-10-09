/********************************* Interface Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Executable

\brief    


\date     $Date: 2006/03/13 21:30:39,12 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_ODC_Executable"

#include  <pfmodel.h>
#include  <s_if_ODC_Executable.hpp>


#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

logical __cdecl GetDocFileName                          ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  ODC_Executable   *CO      = (ODC_Executable *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
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
          case 0 : *retval = CO->GetDocFileName();
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

