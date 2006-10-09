/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPProperty

\brief    


\date     $Date: 2006/08/25 14:57:35,25 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPProperty"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sDictionary.hpp>
#include  <sExtentList.hpp>
#include  <sOPBase.hpp>
#include  <snode.hpp>
#include  <sOPProperty.hpp>


/******************************************************************************/
/**
\brief  InitDescription - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDescription"

logical OPProperty :: InitDescription ( )
{
  DBStructDef            *classref = NULL;
  fmcb                   *fmcbptr  = NULL;
  BNFData                *bdata;
  char                   *names;
  int32                   offset = 0;
  logical                 term   = NO;
BEGINSEQ
  if ( !(bdata = operand_bnf->GetSymbol("pname")) )
  {
    bdata = operand_bnf;
    if ( bdata->IsSymbol("access_path") )    
      bdata = operand_bnf->GetElement("path_element");
    if ( !bdata->IsSymbol("path_element") )         OQLERR(99)
    bdata = bdata->GetElement("path_operand");
    if ( !bdata->IsSymbol("path_name") )  // cannot pre-define type for expression or elementary view
                                                    LEAVESEQ
    bdata = bdata->GetSymbol("pname");
  }
  
  names = bdata->StringValue();
   
  if ( !(classref = class_ref) )
    if ( !(classref = LocalScope()) )
      classref = Scope();

  if ( classref )
    if ( !(fmcbptr = classref->SearchField(names,&offset)) )
      fmcbptr = DBStructDef::GetMetaAttribute(names);

  if ( fmcbptr )
    is_static = NO;

  if ( !fmcbptr )
    if ( !DictHandle()->CheckExtendDef(names) )
      if ( fmcbptr = DictHandle()->ProvideExtendDef(names) )
        is_static = YES;

  if ( !fmcbptr )                                   ERROR
  SetDescription((DBFieldDef *)fmcbptr);             
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical OPProperty :: Initialize (int32 ini_opt )
{
  DBStructDef            *classref;
  node                   *nodeptr;
  fmcb                   *fmcbptr;
  int32                   offset;
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  if ( !(classref = class_ref) )
    classref = Scope();
    
  switch ( re_open )
  {
    case -1 : if ( SetupSetOperation() )             ERROR
    case  4 : InitDescription();
              re_open = 3;
    case  3 : if ( !is_static )
                value.Close();
    case  2 : if ( !value.IsValid() ) 
                if ( OpenValue() )                   ERROR
                else re_open = 0;
              break;        
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPProperty - 



\return term - 

\param  classref - 
\param  oper_bnf - 
\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPProperty"

     OPProperty :: OPProperty (DBStructDef *classref, BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (classref,oper_bnf,parent_node,parm_bnf),
  is_static(AUTO)
{

  op_type = NT_OPProperty;

  SetOPName(oper_bnf->StringValue());
  
  Initialize(0);

}

/******************************************************************************/
/**
\brief  OpenValue - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenValue"

logical OPProperty :: OpenValue ( )
{
  DBObjectHandle          obh(ObjectHandle());
  node                   *nodeptr;
  FunctionTypes           path_type    = FT_undefined;
  int8                    path_opt_ref = 0;
  logical                 term = NO;
BEGINSEQ
  if ( is_static )
  {    
    if ( !ObjectHandle() )
    {
      if ( !((BNFExpData *)operand_bnf)->IsPropertyPath(Scope(),DictHandle(),oper_env,path_type,path_opt_ref) ) 
      {
        parent->ShowError(109,OBJ_ID,MOD_ID,operand_bnf);  
                                                    ERROR
      }
      LEAVESEQ
    }
    if ( !value.OpenAccessPath(obh,operand_bnf,oper_env,MIN(obh.GetAccess(),PI_Update)) )
    {
      value.get_nodeptr()->SetPIRef(&value);
      is_static = YES;
    }
  }
  else if ( is_static != YES )  // might be AUTO
  {
    if ( (nodeptr = CO()->GetNode()) && nodeptr->get_nodetype() != NT_Node )
    {
      if ( value.OpenAccessPath(CO()->GetNode(),operand_bnf,oper_env,NO) ) 
                                                    ERROR
      value.get_nodeptr()->SetPIRef(&value);
      is_static = NO;
      last_co.CopyHandle(CO());
    }
    else
    {
      value.Open(GetDescription(),NULL);            ERROR
    }
  }  
  else                                              ERROR
  
  if ( !value.IsCollection() ) 
    is_set_operand = AUTO;

  SetDescription(value.GetDescription(NO));     

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupSetOperation - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSetOperation"

logical OPProperty :: SetupSetOperation ( )
{
  BNFData    *bdata = NULL;
  logical     term = NO;
  if ( operand_bnf->IsSymbol("path_element") )
  {
    if ( operand_bnf->GetElement("operand_list") )
    {
      is_set_operand = YES;
      if ( (bdata = operand_bnf->GetElement("parm_list")) )
        is_set_operand = NO;    
    }
  }
  else if ( operand_bnf->IsSymbol("access_path")  || 
            operand_bnf->IsSymbol("coll_operand") || 
            operand_bnf->IsSymbol("expr_code")      ) 
  {
    if ( parm_bnf && parm_bnf->IsSymbol("operand_list") )
      if ( !(bdata = parm_bnf->GetElement("parm_list")) )   // empty parmlist
        is_set_operand = YES;   

    parm_bnf = bdata;       
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ~OPProperty - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPProperty"

     OPProperty :: ~OPProperty ( )
{



}


