/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPFunctionDecl

\brief    


\date     $Date: 2006/03/12 19:20:57,64 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPFunctionDecl"

#include  <poql.h>
#include  <sACObject.hpp>
#include  <sDictionary.hpp>
#include  <sNodeStack.hpp>
#include  <sOPParmList.hpp>
#include  <sOPVariableSpec.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <snode.hpp>
#include  <sOPFunctionDecl.hpp>


/******************************************************************************/
/**
\brief  Call - 


\return term
-------------------------------------------------------------------------------
\brief i0


\param  co -
\param  call_parms -
\param  set_operation -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPFunctionDecl :: Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation )
{
  logical             term  = NO;
  InitParameters(call_parms);
  
  term = CallIntern(co,set_operation);

  DeInitParameters();
  

  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  co -
\param  parm_list -
\param  set_operation -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPFunctionDecl :: Call (PropertyHandle *co, ParmList *parm_list, int8 set_operation )
{
  logical             term  = NO;
  InitParameters(parm_list);
  
  term = CallIntern(co,set_operation);

  DeInitParameters();
  

  return(term);
}

/******************************************************************************/
/**
\brief  Check - 


\return term

\param  retval -
\param  co -
\param  parm_list -
\param  convopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical OPFunctionDecl :: Check (PropertyHandle *retval, PropertyHandle *co, ParmList *parm_list, logical convopt )
{

  return(FunctLink::Check(retval,co,parm_list,convopt));

}

/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPFunctionDecl :: Execute ( )
{
  ExecReturnCodes         exec_rc = ERC_success;
BEGINSEQ
  if ( Init(CO(),pi_parms) )                         ERROR
  
  if ( FunctLink::Execute(CO(),&value,pi_parms,*impl_name > ' ' ? impl_name : (char*)NULL,ET_First) )
                                                     ERROR

RECOVER
  exec_rc = ERC_terminate;
ENDSEQ
  return(exec_rc);
}

/******************************************************************************/
/**
\brief  Init - 


\return term

\param  co -
\param  parm_list -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

logical OPFunctionDecl :: Init (PropertyHandle *co, ParmList *parm_list )
{
  logical                 term = NO;
BEGINSEQ
  if ( fldfmcb )                                     LEAVESEQ
    
// pruefung zwischen fldfmcb und value.GetDescription() waere gut
//  if ( value.GetDescription() )                      LEAVESEQ
    
  if ( FunctLink::Execute(co,&value,parm_list,*impl_name > ' ' ? impl_name : (char*)NULL,ET_Initialize) )
                                                     ERROR
  InitDescription(value.GetDescription());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitParameters - 


\return parm_count -
-------------------------------------------------------------------------------
\brief i0


\param  call_parms -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitParameters"

int32 OPFunctionDecl :: InitParameters (OPParmList *call_parms )
{
  logical         term  = NO;
BEGINSEQ
  if ( !no_decl )
  {
    OPDecl::InitParameters(call_parms);
    call_parms = Parameters();                                                     ERROR
  }                                                   
  
  if ( !(pi_parms = call_parms->SetupParmlist(pi_parms)) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  parm_list -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitParameters"

int32 OPFunctionDecl :: InitParameters (ParmList *parm_list )
{
  logical         term  = NO;
BEGINSEQ
  if ( no_decl )
    PIParmList()->Copy(parm_list);
  else
  {
    OPDecl::InitParameters(parm_list);
    if ( !(pi_parms = Parmlist()->SetupParmlist(pi_parms)) )
                                                     ERROR
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitResult

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical OPFunctionDecl :: InitResult ( )
{

  return(Init(CO(),pi_parms));


}

/******************************************************************************/
/**
\brief  IsValid

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical OPFunctionDecl :: IsValid ( )
{

  return ( this && (flnkfct || flnkcfct) );

}

/******************************************************************************/
/**
\brief  OPFunctionDecl - 


\return term
-------------------------------------------------------------------------------
\brief


\param  dictptr
\param  strnames
\param  obhandle -
\param  co -
\param  fnames
\param  check_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPFunctionDecl"

                        OPFunctionDecl :: OPFunctionDecl (Dictionary *dictptr, char *strnames, ACObject *obhandle, PropertyHandle *co, char *fnames, logical check_opt )
                     : OPDecl (NULL),
FunctLink ((OCTP)NULL),
  pi_parms(NULL),
  no_decl(YES)
{
// this is called for functions, which do not have a declaration
BEGINSEQ
  op_type = NT_OPFunctionDecl;
  no_decl = YES;

  OQLRESET
  if ( CreateEnvironment(dictptr,NULL,NULL,NULL,obhandle,co,this) )
                                                     ERROR
  if ( strnames )
    gvtxstb(type_name,strnames,ID_SIZE);
  SetOPName(fnames);
  
  if ( !SetFunctionPtr(dictptr,strnames,fnames,check_opt) )
    FunctLink::Execute(CO(),&value,NULL,(char*)NULL,ET_Initialize);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i01


\param  dictptr
\param  strnames
\param  obhandle -
\param  co -
\param  impl_ph -
\param  check_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPFunctionDecl"

                        OPFunctionDecl :: OPFunctionDecl (Dictionary *dictptr, char *strnames, ACObject *obhandle, PropertyHandle *co, PropertyHandle *impl_ph, logical check_opt )
                     : OPDecl(NULL),
FunctLink ((OCTP)NULL),
  pi_parms(NULL),
  no_decl(NO)
{
  PropertyHandle  *fct_ph = impl_ph->GetParentProperty();
BEGINSEQ
  op_type = NT_OPFunctionDecl;

  OQLRESET
  if ( CreateEnvironment(dictptr,impl_ph->GetObjectHandle().get_obhandle(),
                         NULL,NULL,obhandle,co,this) )
                                                     ERROR
  if ( strnames )
    gvtxstb(type_name,strnames,ID_SIZE);
  
  if ( CreateDecl(impl_ph) )                         ERROR
                                                     
  SetFunctionPtr(dictptr,strnames,opname,check_opt);
  if ( !value.IsValid() )
    FunctLink::Execute(CO(),&value,NULL,(char*)NULL,ET_Initialize);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  PIParmList - 


\return parm_list -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PIParmList"

ParmList *OPFunctionDecl :: PIParmList ( )
{

  if ( !pi_parms )
    pi_parms = new ParmList(NO);

  return(pi_parms);

}

/******************************************************************************/
/**
\brief  SetParmlist - 



\param  plist
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParmlist"

void OPFunctionDecl :: SetParmlist (ParmList *plist )
{



}

/******************************************************************************/
/**
\brief  ~OPFunctionDecl - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPFunctionDecl"

                        OPFunctionDecl :: ~OPFunctionDecl ( )
{

  delete pi_parms;
  pi_parms = NULL;

}


