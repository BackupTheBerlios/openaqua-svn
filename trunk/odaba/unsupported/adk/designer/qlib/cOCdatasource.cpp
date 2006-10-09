/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cOCdatasource

\brief    


\date     $Date: 2006/04/24 13:39:27,68 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cOCdatasource"

#include  <pdesign.h>
#include  <scOCdatasource.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cOCdatasource :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cOCdatasource();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterSelect - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cOCdatasource :: DoAfterSelect ( )
{
/*
  pc_DataSource    *ds_ph = (pc_DataSource *)GetPropertyHandle();
  CTX_Control      *hctx = GetHighContext();
  PropertyHandle   *parent_ph = hctx->GetPropertyHandle();
  DataSourceHandle *dsh = (DataSourceHandle *)parent_ph->Get(AUTO).GetData();
  DataSource       *ds  = NULL;
*/
BEGINSEQ
//  if ( !dsh )                                       P_ERR(99)
     
//  if ( ds_ph->Setup(dsh,GetData()->GetString()) )   ERROR


RECOVER

ENDSEQ
  return(NO);
}


