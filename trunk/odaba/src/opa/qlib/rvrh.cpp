/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    rvrh

\brief    


\date     $Date: 2006/03/12 19:19:33,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "rvrh"

#include  <popa7.h>
#include  <srvrh.hpp>


/******************************************************************************/
/**
\brief  rvrh - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrh"

                        rvrh :: rvrh ( )
                     : rvrhstim(0), rvrhttim(0)

{

  memset(this,0,sizeof(rvrh));
  memcpy(rvrhidnt,"RVRH",4);  


}


