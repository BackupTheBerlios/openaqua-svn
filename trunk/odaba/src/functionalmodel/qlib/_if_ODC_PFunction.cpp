/********************************* Interface Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_PFunction



\date     $Date: 2006/05/20 19:08:42,65 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_ODC_PFunction"

#include  <pfmodel.h>
#include  <s_if_ODC_PFunction.hpp>


#undef     MOD_ID
#define    MOD_ID  "SetLineCount"

logical __cdecl SetLineCount( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  ODC_PFunction    *CO      = (ODC_PFunction *)co->GetArea();
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
           case 1 : *retval = CO->SetLineCount(co,(*parmlist)[0]->GetInt());
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

