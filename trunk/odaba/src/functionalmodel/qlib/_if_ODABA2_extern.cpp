/********************************* Interface Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODABA2_extern

\brief    


\date     $Date: 2006/03/13 21:30:38,89 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_ODABA2_extern"

#include  <pfmodel.h>
#include  <s_if_ODABA2_extern.hpp>


#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

logical __cdecl GetProjectPath                          ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  ODABA2_extern    *CO      = (ODABA2_extern *)co->GetArea();
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
           case 1 : *retval = CO->GetProjectPath((*parmlist)[0]->GetString());
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

