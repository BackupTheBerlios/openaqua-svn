/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    PCSHandle

\brief    


\date     $Date: 2006/03/12 19:18:01,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "PCSHandle"

#include  <popa7.h>
#include  <sCSA_Handle.hpp>
#include  <sPCSHandle.hpp>


/******************************************************************************/
/**
\brief  Get - 


\return acthdl -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

CSA_Handle *PCSHandle :: Get ( )
{

  return( this ? active_handle : NULL);

}

/******************************************************************************/
/**
\brief  PCSHandle - 



\param  acthdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PCSHandle"

                        PCSHandle :: PCSHandle (CSA_Handle *acthdl )
                     : active_handle(acthdl)
{



}

/******************************************************************************/
/**
\brief  operator-> - 


\return acthdl -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator->"

CSA_Handle *PCSHandle :: operator-> ( )
{

  return( this ? active_handle : NULL);


}

/******************************************************************************/
/**
\brief  operator= - 


\return acthdl -

\param  act_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

CSA_Handle *PCSHandle :: operator= (CSA_Handle *act_handle )
{

  return(active_handle = act_handle);

}

/******************************************************************************/
/**
\brief  ~PCSHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~PCSHandle"

                        PCSHandle :: ~PCSHandle ( )
{



}


