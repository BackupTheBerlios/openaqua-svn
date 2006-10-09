/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPBaseCollection

\brief    


\date     $Date: 2006/03/12 19:20:52,98 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPBaseCollection"

#include  <poql.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sParmList.hpp>
#include  <sOPBaseCollection.hpp>


/******************************************************************************/
/**
\brief  Initialize - 


\return term

\param  ini_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPBaseCollection :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( SetupParameters() )               ERROR
    case  4 : re_open = 3;
    case  3 : if ( !CO() )                           ERROR
              value.Open(CO()->GetBaseProperty());
              SetDescription(value.GetDescription(NO));             
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPBaseCollection - 


\return term

\param  oper_bnf -
\param  parent_node -
\param  parm_bnf -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPBaseCollection"

                        OPBaseCollection :: OPBaseCollection (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (NULL,oper_bnf,parent_node,parm_bnf)
{

  op_type = NT_OPBaseCollection;

  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPBaseCollection - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPBaseCollection"

                        OPBaseCollection :: ~OPBaseCollection ( )
{



}


