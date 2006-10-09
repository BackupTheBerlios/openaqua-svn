/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    cftp

\brief    


\date     $Date: 2006/03/12 19:22:10,14 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cftp"

#include  <pdefault.h>
#include  <sCTX_Base.hpp>
#include  <scftp.hpp>


/******************************************************************************/
/**
\brief  HighContext - 


\return fncptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HighContext"

CTX_Base *cftp :: HighContext ( )
{


  return(cftpfnc);
}

/******************************************************************************/
/**
\brief  SetContext


\param  fncptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContext"

void cftp :: SetContext (CTX_Base *fncptr )
{

  *cftpret = fncptr;

}

/******************************************************************************/
/**
\brief  cftp


\param  fnames -
\param  resptr -
\param  highfnc -
\param  fncptr_p -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cftp"

                        cftp :: cftp (char *fnames, void *resptr, CTX_Base *highfnc, CTX_Base **fncptr_p )
                     : cftpname(fnames), cftpfnc(highfnc), 
 cftpres(resptr), cftpret(fncptr_p)

{



}


