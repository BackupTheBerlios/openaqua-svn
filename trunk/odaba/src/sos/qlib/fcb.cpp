/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    fcb

\brief    


\date     $Date: 2006/03/12 19:22:20,35 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "fcb"

#include  <pdefault.h>
#include  <sfmcb.hpp>
#include  <sfcb.hpp>


/******************************************************************************/
/**
\brief  GetName - 


\return fldname -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *fcb :: GetName ( )
{

  return(fcbfmcb->fmcbname);

}

/******************************************************************************/
/**
\brief  fcb

-------------------------------------------------------------------------------
\brief FCB_


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fcb"

                        fcb :: fcb ( )
                     :   fcbfmcb(NULL)

{

  SOSRESET


}

/******************************************************************************/
/**
\brief FCB_N


\param  fmcbptr - Field definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fcb"

                        fcb :: fcb (fmcb *fmcbptr )
                     :   fcbfmcb(fmcbptr)

{

  SOSRESET


}

/******************************************************************************/
/**
\brief  fcbfmcbs


\param  fmcbptr - Field definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fcbfmcbs"

void fcb :: fcbfmcbs (fmcb *fmcbptr )
{

  fcbfmcb = fmcbptr;

}


