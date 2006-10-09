/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cImpParmList

\brief    


\date     $Date: 2006/04/24 13:37:58,15 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cImpParmList"

#include  <pdesign.h>
#include  <scImpParmList.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cImpParmList :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cImpParmList();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterDeleteData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDeleteData"

int8 cImpParmList :: DoAfterDeleteData ( )
{

  return ( Changed() );

}

/******************************************************************************/
/**
\brief  DoAfterInsertData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterInsertData"

int8 cImpParmList :: DoAfterInsertData ( )
{
  PropertyHandle    *prophdl   = GetCurrentPropertyHandle();
  PropertyHandle    *type      = prophdl->GPH("ddetype");
BEGINSEQ
  if ( type->IsTrue() )                             LEAVESEQ

  prophdl->ExecuteInstanceAction("SetDefaults",NULL);

ENDSEQ
  return ( Changed() );
}

/******************************************************************************/
/**
\brief  DoAfterSaveData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSaveData"

int8 cImpParmList :: DoAfterSaveData ( )
{

  return ( Changed() );

}

/******************************************************************************/
/**
\brief  DoAfterSelect - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cImpParmList :: DoAfterSelect ( )
{

  return ( cSDBResourceNotifyHigh::DoAfterSelect() );

}

/******************************************************************************/
/**
\brief  SetupHeadline - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupHeadline"

logical cImpParmList :: SetupHeadline ( )
{
  PropertyHandle *prophdl  = GetPropertyHandle();
  prophdl->GetParentProperty()->ExecuteInstanceAction("FillHeadLine",NULL);

  Changed();
  return(NO);
}

/******************************************************************************/
/**
\brief  cImpParmList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cImpParmList"

                        cImpParmList :: cImpParmList ( )
                     : cSDBResourceNotifyHigh ()
{



}

/******************************************************************************/
/**
\brief  ~cImpParmList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cImpParmList"

                        cImpParmList :: ~cImpParmList ( )
{



}


