/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Type

\brief    


\date     $Date: 2006/03/13 21:30:26,34 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_Type"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <ssSDB_Type.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  strctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_Type :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sSDB_Type();
  return(NO);

}

/******************************************************************************/
/**
\brief  DBOpened - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBOpened"

logical sSDB_Type :: DBOpened ( )
{
  PropertyHandle    *prophdl      = GetPropertyHandle();
  PropertyHandle    *checkhdl     = prophdl;
BEGINSEQ
  if ( prophdl->GetMode() == PI_Read )               LEAVESEQ
    
  while ( checkhdl->IsShareBaseHandle() )
    checkhdl = checkhdl->GetParentProperty();
  
  if ( !strcmp(checkhdl->GetPropertyPath(),"impl_ref") )
                                                     LEAVESEQ
  prophdl->GPH("impl_ref")->SetType("SDB_Structure");

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  sSDB_Type - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_Type"

                        sSDB_Type :: sSDB_Type ( )
                     : CTX_Structure ()
{



}

/******************************************************************************/
/**
\brief  ~sSDB_Type - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_Type"

                        sSDB_Type :: ~sSDB_Type ( )
{



}


