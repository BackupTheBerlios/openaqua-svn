/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPAccessPath

\brief    


\date     $Date: 2006/06/26 18:39:34,42 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPAccessPath"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
#include  <sOPAccessPath.hpp>
#include  <sOPBase.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sOPParmList.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <snode.hpp>
#include  <sOPAccessPath.hpp>


/******************************************************************************/
/**
\brief  Call - 


\return term - 

\param  co - 
\param  call_parms - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPAccessPath :: Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation )
{
  ExecReturnCodes         rc = ERC_null;  
  DBStructDef            *classref = NULL;
  PropertyHandle          result;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  local_co = co;
  
  if ( set_operation == YES )
  {
    parent->ToTop(NO);
    while ( !parent->Next() )  // verstellt CO
      if ( (rc = Execute()) != ERC_success )
        break;
  }
  else
    rc = Execute();  
  
  if ( rc == ERC_terminate )                         ERROR
  if ( rc == ERC_null )
  {
    ResetValue();                                    LEAVESEQ
  }
  rc = ERC_success;
RECOVER
  ResetValue();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPAccessPath :: Execute ( )
{
  ExecReturnCodes         rc   = ERC_success;
  logical                 term = NO;
BEGINSEQ
  source_stack.Push(source ? source->GetValue() : NULL);
  if ( (rc = InitSource()) != ERC_success )          ERROR
    
  if ( path_ext )
  {    
    term = path_ext->Call(GetValue(),(OPParmList *)NULL,is_set_operand);
    if ( term )                                      ERROR
    value.RegisterNode(path_ext->Value());
    if ( !Value() )
    {
      rc = ERC_null;                                 ERROR
    }
  }
  
  if ( !fldfmcb )
    SetDescription(Value()->GetFieldDef());


RECOVER
  ResetValue();
  if ( rc == ERC_success )
    rc = ERC_terminate;
ENDSEQ
  SetupSourceHandle();
  source_stack.Pop();
  return(rc);
}

/******************************************************************************/
/**
\brief  Get - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical OPAccessPath :: Get ( )
{

  return ( source->Get() );

}

/******************************************************************************/
/**
\brief  GetAccessNode - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccessNode"

node *OPAccessPath :: GetAccessNode ( )
{
  node                   *nodeptr = NULL;

  return(nodeptr);
}

/******************************************************************************/
/**
\brief  GetLastNode - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastNode"

node *OPAccessPath :: GetLastNode ( )
{

  return ( path_ext ? path_ext->GetLastNode()
                    : source ? source->Value()
                             : NULL              );

}

/******************************************************************************/
/**
\brief  InitSource - 


\return rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSource"

ExecReturnCodes OPAccessPath :: InitSource ( )
{
  DBStructDef            *classref = NULL;
  PropertyHandle         *co       = NULL;
  ExecReturnCodes         rc       = ERC_success;
BEGINSEQ
  if ( parent && LocalScope() )
    local_co = parent->Source()->GetValue();
  
  if ( local_co )
    PushCO(local_co);                  // parent local CO
  if ( !CO() )
    SetUpperCO();
  if ( CO() && (classref = CO()->GetCurrentTypeDef()) )
    class_ref = classref;
  
  if ( intern_expr )
  {
    if ( source->Call(CO(),(OPParmList *)NULL,NO) )
      rc = ERC_terminate;
    if ( rc != ERC_success )                         ERROR
  }
  else  
  {
    rc = source ? source->Execute() : ERC_terminate;    
    if ( rc != ERC_success )                         ERROR
  }
  
  value.RegisterNode(source->Value());

RECOVER
  ResetValue();
ENDSEQ
  if ( local_co )
    PopCO();
  return(rc);
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

logical OPAccessPath :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  GetReopen();
    
  switch ( re_open )
  {
    case -1 : if ( operand_bnf->IsSymbol("OQLSelect") )
              {
                if ( SetupOQLElements() )           OQLERR(145)
              }
              else if ( ext_index >= 0 )
                if ( SetupPathElement() )           OQLERR(145)
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocalScope - 


\return structdef - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocalScope"

DBStructDef *OPAccessPath :: LocalScope ( )
{

  return(local_scope ? class_ref : NULL);

}

/******************************************************************************/
/**
\brief  Next - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Next"

logical OPAccessPath :: Next ( )
{

  return ( source->Next() );

}

/******************************************************************************/
/**
\brief  OPAccessPath - 


\return term - 

\param  classref - 
\param  oper_bnf - 
\param  parent_node - 
\param  pext_bnf - 
\param  indx0 - 
\param  lscope - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPAccessPath"

     OPAccessPath :: OPAccessPath (DBStructDef *classref, BNFData *oper_bnf, OPBase *parent_node, BNFData *pext_bnf, int32 indx0, logical lscope )
                     : OPVariable (classref,oper_bnf,parent_node,pext_bnf),
  path_ext(NULL),
  ext_index(indx0),
  is_coll_operand(NO),
  intern_expr(NO),
  local_co(NULL),
  source_stack(NULL)
{

  op_type = NT_OPAccessPath;

  if ( lscope )
    local_scope = YES;
  
  if ( indx0 >= 0 )
    Initialize(0);

}

/******************************************************************************/
/**
\brief  Position - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  count_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical OPAccessPath :: Position (int32 &count_ref )
{
  logical                 backward = count_ref < 0;
  logical                 term = NO;
BEGINSEQ
  if ( !count_ref )                                  LEAVESEQ
  
  if ( path_ext )
  {
    if ( on_top )
      Position(backward);
    while ( count_ref )
    {
      if ( path_ext->Position(count_ref) )           ERROR
      if ( Position(backward) )                      LEAVESEQ
    }
  }
  else
  {
    while ( count_ref ) 
    {
      if ( Position(backward) )                      LEAVESEQ
      count_ref -= backward ? -1 : 1;
    }
  }

  value.RegisterNode(path_ext ? path_ext->Value() : source->Value());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  backward - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical OPAccessPath :: Position (logical backward )
{
  logical                 term = NO;
BEGINSEQ
  if ( on_top )
    if ( InitSource() != ERC_success )               ERROR
      
  if ( backward ? Previous() : Next() )              ERROR

  if ( path_ext )
    path_ext->ToTop(NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Previous - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Previous"

logical OPAccessPath :: Previous ( )
{

  return ( source->Previous() );

}

/******************************************************************************/
/**
\brief  ResetValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetValue"

void OPAccessPath :: ResetValue ( )
{

  value.Close();          // ist vielleicht zu stark, dann Cancel()

}

/******************************************************************************/
/**
\brief  Setup - 


\return cur_element - 

\param  classref - 
\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

OPAccessPath *OPAccessPath :: Setup (DBStructDef *classref, OPBase *parent_node )
{
  OPAccessPath       *cur_element = this;
BEGINSEQ
  if ( !this )
  {
    cur_element = (OPAccessPath *)parent_node;       LEAVESEQ
  }
  
  if ( classref )
    class_ref = classref;
  else
    class_ref = parent_node->Source()->GetDescription()->GetDBStruct(DictHandle());
    
  if ( SetupSourceOperation() )                      ERROR
  is_set_operand = source->IsSetOperand();

  if ( parent_node )
  {
    ((OPAccessPath *)parent_node)->path_ext = this;
    parent_node->SetDescription(GetDescription());
  }

RECOVER
  cur_element = NULL;
ENDSEQ
  return(cur_element);
}

/******************************************************************************/
/**
\brief  SetupOQLElements - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupOQLElements"

logical OPAccessPath :: SetupOQLElements ( )
{
  OPAccessPath           *select   = NULL;
  OPAccessPath           *where    = NULL;
  OPAccessPath           *having   = NULL;
  OPAccessPath           *group    = NULL;
  OPAccessPath           *order    = NULL;
  OPAccessPath           *output   = NULL;
  OPAccessPath           *cur_element = NULL;
  BNFData                *pext_bnf = operand_bnf;
  BNFData                *bdata;
  int32                   indx0    = 0;
  logical                 term     = NO;
BEGINSEQ
// OQLSelect      := sel_spec from_spec [sel_extensions(*)] [output_spec]
// sel_spec       := _select operand_list
// sel_extensions := where_spec | having_spec | group_spec | order_spec

  operand_bnf = NULL;
  while ( bdata = pext_bnf->GetElement(++indx0) )
  {
    switch ( bdata->GetSymbolCode("sel_spec", "from_spec", "where_spec", "having_spec", 
                                  "group_spec", "order_spec", "output_spec")            )
    {
      case  1 : select = new OPAccessPath(NULL,bdata,NULL,NULL,AUTO,YES); 
                break;
      case  2 : operand_bnf = bdata; 
                break;
      case  3 : where  = new OPAccessPath(NULL,bdata,NULL,NULL,AUTO,YES); 
                break;
      case  4 : having = new OPAccessPath(NULL,bdata,NULL,NULL,AUTO,YES); 
                break;
      case  5 : group  = new OPAccessPath(NULL,bdata,NULL,NULL,AUTO,YES); 
                break;
      case  6 : order  = new OPAccessPath(NULL,bdata,NULL,NULL,AUTO,YES); 
                break;
      case  7 : output = new OPAccessPath(NULL,bdata,NULL,NULL,AUTO,YES); 
                break;
      default : ;
    }
  }
  
  if ( !operand_bnf )                                OQLERR(777)
  cur_element = Setup(class_ref,NULL);               OQLCERR
      
  cur_element = where->Setup(NULL,cur_element);      OQLCERR
  cur_element = select->Setup(NULL,cur_element);     OQLCERR
  cur_element = group->Setup(NULL,cur_element);      OQLCERR
  cur_element = having->Setup(NULL,cur_element);     OQLCERR
  cur_element = order->Setup(NULL,cur_element);      OQLCERR
  cur_element = output->Setup(NULL,cur_element);     OQLCERR

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupPathElement - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupPathElement"

logical OPAccessPath :: SetupPathElement ( )
{
  BNFData                *pext_bnf = NULL;
  BNFData                *oper_bnf = NULL;
  OPBase                 *parm_node = NULL;
  DBStructDef            *classref = NULL;
  logical                 lscope;
  logical                 term = NO;
BEGINSEQ
// access_path    := path_element [ path_extension(*) ]
// path_extension := ext_op path_element 

  if ( !ext_index ) // first element
  {
    pext_bnf = operand_bnf->GetSymbol("access_path");
    operand_bnf = pext_bnf->GetElement(0);
  }
  else
    pext_bnf = parm_bnf;

  if ( SetupSource() )                               ERROR
  is_set_operand = source->IsSetOperand();
    
  if ( oper_bnf = pext_bnf->GetElement(ext_index+1) )  // next path_extension 
  {
    lscope = oper_bnf->GetElement(0)->IsValue(".");    // use expression scope for parameters
    oper_bnf = oper_bnf->GetElement(1);                // next path_element
    if ( !source->GetDescription() )                 ERROR
    if ( !(classref = value.GetCurrentTypeDef()) )
      classref = DictHandle()->GetStructDef(source->GetDescription()->fmcbtype);
    // wir müssen noch sagen, dass wir für alle path_extensions keine static operands zulassen wollen
    path_ext = new OPAccessPath(classref,oper_bnf,this,pext_bnf,
                                ext_index+1,lscope); 
    SetDescription(path_ext->GetDescription());
    value.RegisterNode(path_ext->Value());
    OQLCERR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupSource - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSource"

logical OPAccessPath :: SetupSource ( )
{
  DBFieldDef             *fielddef = parent->GetDescription();
  BNFData                *oper_bnf = NULL;
  OPBase                 *parm_node = NULL;
  logical                 term = NO;
BEGINSEQ
// path_element := path_operand [ operand_list ]
// path_operand := path_name | coll_operand | expr_code
// coll_operand := '[' access_path ']'

  if ( parent && LocalScope() )
    local_co = parent->Source()->GetValue();
  if ( local_co )
    PushCO(local_co);                  // parent local CO
  
  oper_bnf = operand_bnf->GetElement(0)->GetElement(0);
  switch ( oper_bnf->GetSymbolCode("path_name","coll_operand","expr_code") )
  {
    case 1 : source = CreateOperandNode(this,operand_bnf);  
             break;
    case 2 : if ( source = CreateOperandNode(this,oper_bnf->GetElement(1)) )
             {
               is_coll_operand = YES;
               if ( SetupParameters() )              ERROR
             }
             break;
    case 3 : source = new OPExpressionDecl(oper_env,parent->GetValue(),oper_bnf);
             OQLCERR
             if ( SetupParameters() )                ERROR
             intern_expr = YES;
             break;
  }
  
  if ( !source )
  {
    if ( !fielddef->get_weak_typed() )               ERROR
    // fuer alle Ableitungen von fmcbtype/class_ref->smcbname 
    // class_ref neu setzen und probieren (rekursiv) 
    // dazu ware liste der Ableitungen an DBStructDef hilfreich
    // -> oder allg. Behandlung in Initialize
    ERROR
  }
  SetDescription();
  if ( source->Value() )
    value.RegisterNode(source->Value());

RECOVER
  term = YES;
ENDSEQ
  if ( local_co )
    PopCO();
  return(term);
}

/******************************************************************************/
/**
\brief  SetupSourceHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSourceHandle"

void OPAccessPath :: SetupSourceHandle ( )
{

  if ( source && source_stack.Count() > 1 )
  {
    source->GetValue()->CopyHandle(NULL);
    re_open = 3;
  }

}

/******************************************************************************/
/**
\brief  SetupSourceOperation - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSourceOperation"

logical OPAccessPath :: SetupSourceOperation ( )
{
  FunctionTypes           ftype = FT_undefined;
  BNFData                *oper_bnf = operand_bnf;
  BNFData                *prm_bnf  = NULL;
  logical                 term = NO;
BEGINSEQ
// sel_spec    := _select operand_list
// from_spec   := _from operand_list 
// where_spec  := _where condition 
// having_spec := _having condition 
// order_spec  := _order_by '(' scoped_names ')'
// group_spec  := _group_by '(' categories ')'  // automatically generates 'value' and 'partition' property in the structure
// output_spec := to_file | to_database
// to_file     := _tofile operand_list   // ToFile( Path=Console, FieldSeparator=',', StringSeparator='"', LineSeparator=10,, HeadLine=YES )
// to_database := _todb operand_list     // ToDatabase ( Datasource='Output',  Extent=SelectedPersons )

  switch ( operand_bnf->GetSymbolCode("sel_spec", "from_spec", "where_spec", "having_spec", 
                                      "group_spec", "order_spec", "output_spec")            )
  {
    case  1 : ftype = FT_OQLSelect; 
              prm_bnf = oper_bnf->GetElement(1);   // parameters
              break;
    case  2 : ftype = FT_OQLFrom; 
              prm_bnf = oper_bnf->GetElement(1);   // parameters
              break;
    case  3 : 
    case  4 : ftype = FT_OQLWhere; 
              prm_bnf = oper_bnf->GetElement(1);   // parameters
              break;
    case  5 : ftype = FT_OQLGroupBy; 
              prm_bnf = oper_bnf->GetElement(2);   // categories
              break;
    case  6 : ftype = FT_OQLOrderBy; 
              prm_bnf = oper_bnf->GetElement(2);   // scoped names
              break;
    case  7 : oper_bnf = operand_bnf->GetElement(0);
              ftype = oper_bnf->IsA("to_file") 
                        ? FT_OQLToFile : FT_OQLToDB; 
              prm_bnf = oper_bnf->GetElement(1);   // parameters
              break;
    default : ;
  }
  
  if ( !(source = CreateOperationNode(ftype,this,class_ref,oper_bnf->GetElement(0),prm_bnf)) )
                                                     ERROR
  SetDescription();
  if ( source->Value() )
    value.RegisterNode(source->Value());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ToTop - 


\return term - 

\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToTop"

logical OPAccessPath :: ToTop (logical recursive )
{

  if ( recursive && path_ext )
    path_ext->ToTop(recursive);
    
  return ( source->ToTop(recursive) );

}

/******************************************************************************/
/**
\brief  ~OPAccessPath - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPAccessPath"

     OPAccessPath :: ~OPAccessPath ( )
{



}


