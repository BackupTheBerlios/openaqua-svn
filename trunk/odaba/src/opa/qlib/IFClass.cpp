/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    IFClass



\date     $Date: 2006/05/09 15:20:47,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "IFClass"

#include  <popa7.h>
#include  <csfctp.h>
#include  <ljump.h>
#include  <sCSInstanceList.hpp>
#include  <sCS_Connection.hpp>
#include  <sIFFunction.hpp>
#include  <sSC_Handle.hpp>
#include  <sThreadEntry.hpp>
#include  <sIFClass.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return term - Termination code

\param  dwServiceClass
\param  dwServiceFunc
\param  connection
\param  cso_ptr
\param  cparms
\param  result
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical IFClass :: Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Connection *connection, void *cso_ptr, CSInstanceList *cparms, CSInstanceList *result )
{
  SC_Handle  *sc_handle = (SC_Handle *)cso_ptr;
  char        string[33];
  logical     term = NO;
BEGINSEQ
SOSTRY 
{
  if ( cso_ptr )
  {
    if ( sc_handle->Start() )
    {
      if ( sc_handle->IsClosing(dwServiceClass,dwServiceFunc) || !SDBERROR )
                                                     ERROR
      else                                           SDBERR(9)
    }
  }
  else
    if ( sc_handle->CheckHandle(dwServiceClass,dwServiceFunc) )
                                                     ERROR
        
  if ( dwServiceFunc >= function_count )             SDBERR(509)
  term = function_table[dwServiceFunc].Execute(connection,cso_ptr,cparms,result);

  if ( cso_ptr )
    sc_handle->Stop(dwServiceClass,dwServiceFunc);
}
SOSCATCH
{
  SDBEV1(gvtxltoa(dwServiceClass,string,10),UNDEF)
  SDBEV2(gvtxltoa(dwServiceFunc,string,10),UNDEF)
  SDBERR(518)
}

RECOVER
  term = YES;
ENDSEQ
  ThreadEntry::ReleaseLocks();
  return(term);
}

/******************************************************************************/
/**
\brief  IFClass


\param  if_fct_table - 
\param  if_fct_count
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IFClass"

     IFClass :: IFClass (IFFunction *if_fct_table, int16 if_fct_count )
                     :   function_table(if_fct_table),
  function_count(if_fct_count)
{


}


