/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OPExtent

\brief    


\date     $Date: 2006/04/20 14:29:39,70 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPExtent"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
#include  <sExtentList.hpp>
#include  <sOPBase.hpp>
#include  <sOPExtent.hpp>


/******************************************************************************/
/**
\brief  Initialize - 


\return term

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPExtent :: Initialize (int32 ini_opt )
{
  DBObjectHandle          obh(ObjectHandle());
  DBFieldDef             *fielddef;
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( !(fielddef = DictHandle()->ProvideExtendDef(opname)) )
                                                     OQLSERR(161)
              if ( SetupParameters() )               ERROR
              SetDescription(fielddef);
    case  4 : re_open = 3;
    case  3 : if ( !value.IsValid() )
              {
                if ( !ObjectHandle() )               ERROR
                if ( value.OpenAccessPath(obh,operand_bnf,oper_env,obh.GetAccess()) )
                                                     ERROR
                SetDescription(value.GetDescription());
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
\brief  OPExtent - 


\return term

\param  oper_bnf - 
\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPExtent"

                        OPExtent :: OPExtent (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (NULL,oper_bnf,parent_node,parm_bnf)
{

  op_type = NT_OPExtent;

  SetOPName(oper_bnf->StringValue());
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPExtent - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPExtent"

                        OPExtent :: ~OPExtent ( )
{



}


