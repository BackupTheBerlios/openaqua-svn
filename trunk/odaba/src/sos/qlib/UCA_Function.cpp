/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UCA_Function

\brief    


\date     $Date: 2006/03/12 19:22:02,95 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UCA_Function"

#include  <pdefault.h>
#include  <sCTX_Base.hpp>
#include  <sUCA_Function.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical UCA_Function :: Execute ( )
{
  logical   term = NO;

BEGINSEQ
  if ( !context )                                   SOSERR(99)
  if ( !context->CheckPermission(this) )            ERROR
  term = context->ExecuteFunction(name);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  UCA_Function


\param  fname - Function name
\param  fncptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UCA_Function"

                        UCA_Function :: UCA_Function (char *fname, CTX_Base *fncptr )
                     : UCA_Action(fname,fncptr)
{



}

/******************************************************************************/
/**
\brief  ~UCA_Function


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~UCA_Function"

                        UCA_Function :: ~UCA_Function ( )
{



}


