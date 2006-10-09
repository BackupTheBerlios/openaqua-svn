/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cFunctImpList



\date     $Date: 2006/05/23 14:09:41,29 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cFunctImpList"

#include  <pdesign.h>
#include  <spc1_ODC_FunctImp.hpp>
#include  <scFunctImpList.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cFunctImpList :: Create (CTX_Control **ctx_ctl_ptrp )
{
  *ctx_ctl_ptrp = new cFunctImpList();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterDeleteData

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDeleteData"

int8 cFunctImpList :: DoAfterDeleteData ( )
{

  if ( UserState1() )
  {
    SetUserState1(NO);
    if ( !implementation_descr.NoWrite() )
      implementation_descr.Delete();
  }

  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterInsertData

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterInsertData"

int8 cFunctImpList :: DoAfterInsertData ( )
{
  PropertyHandle   *prophdl   = GetCurrentPropertyHandle();
  char              executed  = NO;
BEGINSEQ
  if ( UserState2() )
  {
    SetUserState2(NO);
    if ( !GetDecisionYes(17,prophdl->GPH("sys_ident")->GetString()) )
                                                    LEAVESEQ
  }

  pc1_ODC_FunctImp   impl_pc(prophdl);
  impl_pc.SetupCodeBlocks(this);

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  DoBeforeClose

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeClose"

int8 cFunctImpList :: DoBeforeClose ( )
{

  implementation_descr.Close();
  return(NO);
}

/******************************************************************************/
/**
\brief  DoBeforeDeleteData

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDeleteData"

int8 cFunctImpList :: DoBeforeDeleteData ( )
{
  PropertyHandle  *prophdl  = GetCurrentPropertyHandle();
  PropertyHandle  *parent   = prophdl->GetParentProperty();
  char             executed = NO;
  SetUserState1(NO);

  switch ( *ODEOption(this,"DeleteDescriptionWithImplementation") )
  {
    case 'Y' : SetUserState1(YES);                  break;
    case 'N' : SetUserState1(NO);                   break; 
    case 'A' :
    default  : if ( GetDecisionYes(12,prophdl->GPH("sys_ident")->GetString()) )
               {
                 implementation_descr.Open(*parent->GPH("implementation_descr"));
                 if ( implementation_descr.Get(prophdl->ExtractKey()) )   
                   SetUserState1(YES);
               }
  }

  return(executed);
}

/******************************************************************************/
/**
\brief  DoBeforeInsertData

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeInsertData"

int8 cFunctImpList :: DoBeforeInsertData ( )
{
  PropertyHandle   *prophdl   = GetCurrentPropertyHandle();
  PropertyHandle   *init_ph   = GetInitPropertyHandle();
  PropertyHandle   *new_ident = init_ph->GPH("sys_ident");
  char              executed  = NO;
  pc1_ODC_FunctImp   impl_pc(prophdl);
  SetUserState2(impl_pc.ExistDescription(new_ident->GetString()));
  return(executed);
}

/******************************************************************************/
/**
\brief  cFunctImpList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cFunctImpList"

     cFunctImpList :: cFunctImpList ( )
                     : cSDBResource_Base(),
  implementation_descr()
{
}

/******************************************************************************/
/**
\brief  ~cFunctImpList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cFunctImpList"

     cFunctImpList :: ~cFunctImpList ( )
{
}


