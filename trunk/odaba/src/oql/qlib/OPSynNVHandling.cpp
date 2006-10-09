/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynNVHandling

\brief    


\date     $Date: 2006/03/12 19:21:04,26 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynNVHandling"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOPSynNVHandling.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSynNVHandling :: Execute ( )
{
  ExecReturnCodes         exec_rc = ERC_success;
  if ( nvh_type != NVH_undefined )
    Environment()->SetNVHType(nvh_type);
  return(exec_rc);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term

\param  ini_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPSynNVHandling :: Initialize (int32 ini_opt )
{
  BNFData                *bdata;
  char                   *nv_string;
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( !(bdata = parm_bnf->GetSymbol("simple_op")) )
                                                     OQLERR(109)
              if ( nv_string = bdata->StringValue() );
              {
                if ( stricmp(nv_string,"accept") )
                  nvh_type = NVH_accept;
                else if ( stricmp(nv_string,"ignore") )
                  nvh_type = NVH_ignore;
                else if ( stricmp(nv_string,"exception") )
                  nvh_type = NVH_exception; 
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
\brief  OPSynNVHandling - 


\return term

\param  parent_node -
\param  parm_bnf -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynNVHandling"

                        OPSynNVHandling :: OPSynNVHandling (OPBase *parent_node, BNFData *parm_bnf )
                     : OPBase (NULL,parent_node),
  parm_bnf(parm_bnf),
  nvh_type(NVH_undefined)

{

  op_type = NT_OPSynError;

  SetOPName("error");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynNVHandling - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynNVHandling"

                        OPSynNVHandling :: ~OPSynNVHandling ( )
{



}


