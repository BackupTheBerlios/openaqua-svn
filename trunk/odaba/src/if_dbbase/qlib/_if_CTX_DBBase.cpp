/********************************* Interface Class Source Code ***************************/
/**
\package  OPA
\class    CTX_DBBase

\brief    Base class for data base contexts
          The   base   class   for   database   contexts   provides   some basic
          functionality  for data base context  classes. In particular the class
          provides  most of the default event handlers that can be overloaded in
          specific  context  classes.  Overloaded  handlers need not to call the
          default  handlers  since  nothing  is  done  in  the default handlers.
          Handlers  for  database  events  are  usually  called  within internal
          transactions.  Thus, all  modifications made  by the event handler are
          reset when the transaction fails.
          For  a number of database operations Not-events are generated that are
          called   in   case   of   an   error.   An   error could be a database
          (consistency)  error but  the process  event (before event) could have
          denied the operation as well.

\date     $Date: 2006/05/01 16:10:46,56 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_CTX_DBBase"

#include  <popa7.h>
#include  <s_if_CTX_DBBase.hpp>


#undef     MOD_ID
#define    MOD_ID  "HighDBContext"

logical __cdecl HighDBContext( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  CTX_DBBase  *CO     = (CTX_DBBase *)co->GetArea();
  int          parmcnt  = parmlist ? parmlist->GetSize() : 0;
  char        *parm0_str;
  CTX_DBBase  *ctx_ptr  = NULL;
  logical      term;
BEGINSEQ
  if ( !CO || !retval )                            ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
      
      if ( retval->InitResult(CO->GetSysDict(),"CTX_DBBase",UNDEF,0) )
                                                     ERROR
      break;
    
    case ET_First      : // pruefung der retval-descr. waere sicherer (nd)
      
      if ( (impname      && impname[1] == '1') ||
           (parmcnt >= 1 && *(parm0_str = (*parmlist)[0]->GetString())) )
        ctx_ptr = CO->HighDBContext(parm0_str,(CTX_Types)(parmcnt >= 2 ? (*parmlist)[1]->GetInt() : CTXT_undefined));
      else 
        ctx_ptr = CO->HighDBContext((CTX_Types)(parmcnt >= 1 ? (*parmlist)[0]->GetInt() : CTXT_undefined));
      
    case ET_Next       :
      
      retval->SetArea((char *)ctx_ptr);
      if ( !ctx_ptr )                                ERROR
      break;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

