/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ctxe



\date     $Date: 2006/03/12 19:22:10,31 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ctxe"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <sctxe.hpp>


/******************************************************************************/
/**
\brief  ctxe - 


-------------------------------------------------------------------------------
\brief i0


\param  class_number
\param  flnkptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ctxe"

                        ctxe :: ctxe (int32 class_number, flnk flnkptr )
                     : flnk (flnkptr),
  res_number(class_number)
{



}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ctxe"

                        ctxe :: ctxe ( )
                     : flnk (),
  res_number(0)
{



}


