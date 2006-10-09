/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|14:26:45,35}|(REF)
\class    OPOQLOperation

\brief    


\date     $Date: 2006/04/02 15:18:22,00 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPOQLOperation"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPOQLOperation.hpp>


/******************************************************************************/
/**
\brief  Initialize - 


\return term

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPOQLOperation :: Initialize (int32 ini_opt )
{
  BNFData                *bdata;
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
  
  switch ( re_open )
  {
    case -1 : if ( SetupParameters() )               ERROR
    case  4 : re_open = 3;
    case  3 : switch ( op_code )
              {
                case ST_set_where    : 
                {
                  SetDescription(parent->get_parent()->GetDescription());
                  if ( !CO() || !CO()->IsValid() )   ERROR
                  if ( !CO()->IsValid() )            ERROR
                  if ( bdata = parm_bnf->GetElement("parm_list") )
                    CO()->SetSelection(bdata->GetElement(0)->StringValue());
                }
                break;
                
                case ST_set_group_by :
                {
                  SetDescription(parent->get_parent()->GetDescription());
                  if ( !CO() || !CO()->IsValid() )   ERROR
                  if ( !CO()->IsValid() )            ERROR
                  if ( bdata = parm_bnf->GetElement("parm_list") )
                    if ( !CO()->SetOrder(bdata->GetElement(0)->StringValue()) )
                      break;
                }

                default : ;
                {
                  if ( !value.IsValid() )
                  {
                    if ( CO() )
                    {
                      if ( !CO()->IsValid() )        ERROR
                      if ( value.Open(*CO(),op_code,parm_bnf,oper_env) )
                                                     ERROR
                    }
                    else
                    {
                      if ( !ObjectHandle() )         ERROR
                      DBObjectHandle   obh(ObjectHandle());
                      if ( value.Open(obh,op_code,parm_bnf,oper_env) )
                                                     ERROR
                    }
                    SetDescription(value.GetDescription());
                  }
                }
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
\brief  OPOQLOperation - 



\param  op_code - 
\param  classref - 
\param  oper_bnf - 
\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPOQLOperation"

                        OPOQLOperation :: OPOQLOperation (ST_OpCodes op_code, DBStructDef *classref, BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (classref,oper_bnf,parent_node,parm_bnf),
  op_code(op_code)
{

  op_type = NT_OPOQLOperation;
  selection = NO;

  if ( oper_bnf )
    SetOPName(oper_bnf->GetStringValue(NULL,NULL));
      
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPOQLOperation - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPOQLOperation"

                        OPOQLOperation :: ~OPOQLOperation ( )
{



}


