/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|14:26:45,35}|(REF)
\class    OPGlobalVariable

\brief    


\date     $Date: 2006/04/06 18:15:37,90 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPGlobalVariable"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
#include  <snode.hpp>
#include  <sOPGlobalVariable.hpp>


/******************************************************************************/
/**
\brief  Initialize - 


\return term

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPGlobalVariable :: Initialize (int32 ini_opt )
{
  PropertyHandle         *ph = NULL;
  ParmList               *global_vars;
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( !(global_vars = (ParmList *)GetOPAProcessVariable(PVN_GlobalVariables)) )
                                                     OQLSERR(99)
              value.RegisterNode(*global_vars->Get(opname));             
              SetDescription(value.GetDescription(NO));
              if ( SetupParameters() )               ERROR
    default : re_open = 0;
  }  


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPGlobalVariable - 


\return term

\param  oper_bnf - 
\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPGlobalVariable"

                        OPGlobalVariable :: OPGlobalVariable (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (NULL,oper_bnf,parent_node,parm_bnf)

{

  op_type = NT_OPGlobalVariable;
  
  SetOPName(oper_bnf->StringValue());
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPGlobalVariable - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPGlobalVariable"

                        OPGlobalVariable :: ~OPGlobalVariable ( )
{



}


