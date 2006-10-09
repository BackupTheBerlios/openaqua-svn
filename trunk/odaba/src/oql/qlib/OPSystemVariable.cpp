/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPSystemVariable

\brief    


\date     $Date: 2006/08/25 14:57:52,18 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSystemVariable"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <snode.hpp>
#include  <sOPSystemVariable.hpp>


/******************************************************************************/
/**
\brief  Execute - 



\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSystemVariable :: Execute ( )
{
  ExecReturnCodes         exec_rc = ERC_success;
  value = GetSysVariable(opname);

  return(exec_rc);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPSystemVariable :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : AllocDescription("STRING",T_STRING,513);  // sollte variable Länge sein
              value.Open(GetDescription(),NULL);
    default : re_open = 0;
  }  

  return(term);
}

/******************************************************************************/
/**
\brief  OPSystemVariable - 



\return term - 

\param  oper_bnf - 
\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSystemVariable"

     OPSystemVariable :: OPSystemVariable (BNFData *oper_bnf, OPBase *parent_node )
                     : OPBase (oper_bnf,parent_node)
{

  op_type = NT_OPSystemVariable;

  SetOPName(oper_bnf->StringValue()+1); // skip '%'
  opname[strlen(opname)-1] = 0;
  Initialize(0);

}

/******************************************************************************/
/**
\brief  SetValue - 



\return term - 

\param  source_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical OPSystemVariable :: SetValue (node *source_node )
{
  logical                 term = NO;
BEGINSEQ
  if ( OPBase::SetValue(source_node) )           ERROR

  SetSysVariable(opname,value.GetString());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Store - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical OPSystemVariable :: Store ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ~OPSystemVariable - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSystemVariable"

     OPSystemVariable :: ~OPSystemVariable ( )
{



}


