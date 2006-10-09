/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cCreatePH

\brief    


\date     $Date: 2006/04/24 13:34:01,40 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cCreatePH"

#include  <pdesign.h>
#include  <scCreatePH.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cCreatePH :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cCreatePH();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterOpen - 


\return excuted

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 cCreatePH :: DoAfterOpen ( )
{

  SetPropertyHandle(&datasource);
  return(NO);
}

/******************************************************************************/
/**
\brief  cCreatePH - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cCreatePH"

                        cCreatePH :: cCreatePH ( )
                     : CTX_Control (),
  datasource("")
{



}

/******************************************************************************/
/**
\brief  ~cCreatePH - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cCreatePH"

                        cCreatePH :: ~cCreatePH ( )
{



}


