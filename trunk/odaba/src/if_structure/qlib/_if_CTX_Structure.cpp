/********************************* Interface Class Source Code ***************************/
/**
\package  OPA - 
\class    CTX_Structure

\brief    Structure Context
          A  structure context  is created  for each  structure type. It defines
          the  connection  between  the  instance  and the instance description.
          Moreover,  it allows determining the active con-text hierarchy for the
          structure  instance,  i.e.  the  parent property/extent, the structure
          the  parent property  is defined  in, the  parent parent property etc.
          Thus,  the structure context  defines the context  in which the object
          instance has been provided.
          The  parent  context  for  a  structure  context  is always a property
          context.  This  can  be  the  property  context  for  an extent or for
          another property within a structure instance.
          The  structure  context  allows  handling  read and updating events as
          well as creating or deleting events.

\date     $Date: 2006/06/13 22:40:36,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_CTX_Structure"

#include  <popa7.h>
#include  <s_if_CTX_Structure.hpp>


#undef     MOD_ID
#define    MOD_ID  "GetCollection"

logical __cdecl GetCollection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  CTX_Structure  *CO     = (CTX_Structure *)co->GetArea();
  PropertyHandle *prop_hdl = CO ? CO->HighDBContext()->GetPropertyHandle() : NULL;
  logical         term = NO;

BEGINSEQ
  if ( !CO || !retval )                            ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : break;
    case ET_First      : if ( prop_hdl->IsCollection() )
                           break;
    case ET_Next       : prop_hdl = NULL;
  }
      
  retval->CopyHandle(prop_hdl);
  if ( !prop_hdl )                                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "GetInstance"

logical __cdecl GetInstance( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  CTX_Structure  *CO     = (CTX_Structure *)co->GetArea();
  PropertyHandle *prop_hdl = CO ? CO->GetPropertyHandle() : NULL;
  logical   term = NO;
BEGINSEQ
  if ( !CO || !retval )                            ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
    case ET_First      : break;
    case ET_Next       : prop_hdl = NULL;
  }
      
  retval->CopyHandle(prop_hdl);
  if ( !prop_hdl )                                   ERROR
RECOVER
   term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "GetOldInstance"

logical __cdecl GetOldInstance( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  CTX_Structure   *CO = (CTX_Structure *)co->GetArea();
  PropertyHandle   ph_old;
  logical          term = NO;
BEGINSEQ
  if ( !CO || !retval )                            ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : break;                      // oder wie First ?
    case ET_First      : if ( CO->GetOldInstance() )
                           ph_old = CO->GetOldField();
                         break;
    case ET_Next       : ;
  }
      
  retval->Copy(ph_old);
  if ( !ph_old.IsValid() )                           ERROR
RECOVER
   term = YES;
ENDSEQ
  return(term);
}

