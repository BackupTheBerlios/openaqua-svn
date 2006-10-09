/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cka

\brief    


\date     $Date: 2006/03/12 19:18:30,07 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cka"

#include  <popa7.h>
#include  <skfc.hpp>
#include  <scka.hpp>


/******************************************************************************/
/**
\brief  CloseCKE - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseCKE"

logical cka :: CloseCKE ( )
{

  return(NO);


}

/******************************************************************************/
/**
\brief  GetKey - 


\return keyptr -

\param  keyptr -
\param  instptr -
\param  indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *cka :: GetKey (char *keyptr, void *instptr, int16 indx )
{

  ckekfc->kfckgt((char *)instptr,keyptr,indx);
  return(keyptr);


}

/******************************************************************************/
/**
\brief  OpenCKE - 


\return count -

\param  instptr -
\param  refopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenCKE"

int16 cka :: OpenCKE (void *instptr, logical refopt )
{

  return(ckekfc->kfcfmcbg()->fmcbdim);


}

/******************************************************************************/
/**
\brief  cka - 



\param  kfcptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cka"

                        cka :: cka (kfc *kfcptr )
                     : cke(kfcptr)

{



}

/******************************************************************************/
/**
\brief  ~cka - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cka"

                        cka :: ~cka ( )
{



}


