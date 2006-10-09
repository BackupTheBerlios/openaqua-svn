/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cFieldTable

\brief    


\date     $Date: 2006/03/12 19:37:13,70 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cFieldTable"

#include  <pdesign.h>
#include  <scFieldTable.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc -

\param  ctx_ctl_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cFieldTable :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cFieldTable();
  return(NO);

}

/******************************************************************************/
/**
\brief  SetDataSource

\return term -

\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical cFieldTable :: SetDataSource (PropertyHandle *prophdl )
{
  CTX_Control            *ctx_ptr;
  logical                 term = NO;
BEGINSEQ
  SetPropertyHandle(prophdl);
  if ( !(ctx_ptr = GetControlContext("properties")) )
                                                     ERROR
  ctx_ptr->SetPropertyHandle(prophdl);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cFieldTable


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cFieldTable"

                        cFieldTable :: cFieldTable ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cFieldTable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cFieldTable"

                        cFieldTable :: ~cFieldTable ( )
{



}


