/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OPSynExceptHandling



\date     $Date: 2006/04/11 11:57:36,28 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynExceptHandling"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOPSynExceptHandling.hpp>


/******************************************************************************/
/**
\brief  Execute

\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSynExceptHandling :: Execute ( )
{
  ExecReturnCodes         exec_rc = ERC_success;
  if ( exh_type != NVH_undefined )
    Environment()->SetExceptionHandling(exh_type);
  return(exec_rc);
}

/******************************************************************************/
/**
\brief  Initialize

\return term

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPSynExceptHandling :: Initialize (int32 ini_opt )
{
  BNFData                *bdata;
  char                   *ex_string;
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( !(bdata = parm_bnf->GetSymbol("simple_op")) )
                                                     OQLERR(109)
              if ( ex_string = bdata->StringValue() );
              {
                if ( stricmp(ex_string,"accept") )
                  exh_type = NVH_accept;
                else if ( stricmp(ex_string,"ignore") )
                  exh_type = NVH_ignore;
                else if ( stricmp(ex_string,"exception") )
                  exh_type = NVH_exception; 
                else                                 OQLERR(109)
              }
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPSynExceptHandling

\return term

\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynExceptHandling"

                        OPSynExceptHandling :: OPSynExceptHandling (OPBase *parent_node, BNFData *parm_bnf )
                     : OPBase (NULL,parent_node),
  parm_bnf(parm_bnf),
  exh_type(NVH_undefined)

{

  op_type = NT_OPSynError;

  SetOPName("error");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynExceptHandling

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynExceptHandling"

                        OPSynExceptHandling :: ~OPSynExceptHandling ( )
{



}


