/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    rvre

\brief    


\date     $Date: 2006/03/12 19:19:33,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "rvre"

#include  <popa7.h>
#include  <srvre.hpp>


/******************************************************************************/
/**
\brief  rvre - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvre"

                        rvre :: rvre ( )
{

  memset(this,0,RVRE);
  memcpy(rvreidnt,"RVRE",4);


}


