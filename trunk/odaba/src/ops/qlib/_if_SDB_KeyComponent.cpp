/********************************* Interface Class Source Code ***************************/
/**
\package  OPS
\class    SDB_KeyComponent

\brief    Key component
          A  key component defines refers to a single attribute, a key or a base
          structure. Key components can be referenced in different ways:
          -  by referring  to an  attribute of  the structure or one of its base
          structures using the attribute name
          - by referring to a near attribute property using a property path
          -  by  referring  to  a  key  name defined for a base structure, which
          provides the attributes defined for the referenced key
          -  by referring to a base  structure, which provides the attributes of
          its identifying key as key attributes
          When  a key component  refers to a  transient attribute, indexes based
          on  such keys are  not updated automatically,  i.e. the application is
          responsible  to update the index, when  the value of a transient field
          changes, which is defined as key component.

\date     $Date: 2006/05/11 13:12:31,35 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_SDB_KeyComponent"

#include  <pops7.h>
#include  <s_if_SDB_KeyComponent.hpp>


#undef     MOD_ID
#define    MOD_ID  "KeyDataDecl"

logical __cdecl KeyDataDecl( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  SDB_KeyComponent *CO      = (SDB_KeyComponent *)co->GetArea();
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
           case 1 : *retval = CO->KeyDataDecl(co,nstring,
                                              (*parmlist)[0]);
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

