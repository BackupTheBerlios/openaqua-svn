/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ProcessVariable

\brief    Process variable


\date     $Date: 2006/03/12 19:21:52,48 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ProcessVariable"

#include  <pdefault.h>
#include  <sProcessVariable.hpp>


/******************************************************************************/
/**
\brief  Remove - 


\return var_ptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *ProcessVariable :: Remove ( )
{
  void *variable = variable_ptr;
  *(sts *)this = sts();
  variable_ptr = NULL;
  return(variable);
}


