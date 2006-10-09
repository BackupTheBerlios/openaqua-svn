/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACOPOutput

\brief    


\date     $Date: 2006/08/30 23:42:56,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACOPOutput"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDBQOutput.hpp>
#include  <sDBStructDef.hpp>
#include  <sOperEnvironment.hpp>
#include  <snode.hpp>
#include  <sACOPOutput.hpp>


/******************************************************************************/
/**
\brief  ACOPOutput - 



-------------------------------------------------------------------------------
\brief  i01 - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  structdef - 
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPOutput"

     ACOPOutput :: ACOPOutput (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,nodeptr,structdef,operenv)
{

  nodetype = NT_ACOPOutput;


}

/******************************************************************************/
/**
\brief  i02 - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  proppath - 
\param  operenv - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPOutput"

     ACOPOutput :: ACOPOutput (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{

BEGINSEQ
  nodetype = NT_ACOPOutput;
  set_prop_path("output");
  
  nodeacc  = accopt;
  
  if ( InitOperandBNF(proppath) )                    ERROR
  if ( InitOutput(ST_file_output) )                  ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03 - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  bnf_data - 
\param  operenv - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPOutput"

     ACOPOutput :: ACOPOutput (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{

BEGINSEQ
  nodetype = NT_ACOPOutput;
  set_prop_path("output");  
  
  nodeacc  = accopt;
  oper_bnf = bnf_data;

  if ( InitOutput(ST_file_output) )                     ERROR
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i04 - 



\param  outnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPOutput"

     ACOPOutput :: ACOPOutput (ACOPOutput &outnode_ref )
                     : ACOperation (outnode_ref)
{

  nodetype = NT_ACOPOutput;


}

/******************************************************************************/
/**
\brief  CreateCopyNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACOPOutput :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACOPOutput(*this) ) )        SDBERR(95)
                                                     SDBCERR
  if ( nodefield->get_weak_typed() || !memcmp(nodefield->fmcbname,"VOID ",5) )
    nodeptr->SetType(GetCurrentType());

RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Get - 



\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEIG - 



\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACOPOutput :: Get (int32 indx0, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( indx0 != 0 )                                  ERROR

  if ( !nodenode->IsPositioned() )                   ERROR
  
  nstring = "";
  output->Write(nstring,*nodenode->GetPH());
  instptr = (char *)nstring;
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACOPOutput :: Get (char *skey, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  SDBERR(99)
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  InitOutput - 



\return term - Termination code

\param  op_code - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOutput"

logical ACOPOutput :: InitOutput (ST_OpCodes op_code )
{
  int32                   curindx = 0;
  BNFData                *parameter;
  BNFData                *bdata;
  char                    cpath[1024];
  char                    line_sep[10];
  char                    field_sep[10];
  char                    string_sep[10];
  char                    head_line[10];
  char                    dsname[129];
  char                    extname[129];
  logical                 term = NO;
BEGINSEQ
  if ( nodenode && !nodenode->GetStructDef() )       SDBERR(99)
  
  if ( !oper_bnf->IsA("parm_list") && !(oper_bnf = oper_bnf->GetElement("parm_list")) )
                                                     SDBERR(777)
  if ( op_code == ST_file_output )
  {
    strcpy(cpath,oper_bnf->GetParameter("Path","con"));
    strcpy(field_sep,oper_bnf->GetParameter("FieldSeparator",","));
    strcpy(line_sep,oper_bnf->GetParameter("LineSeparator","\n"));
    if ( isdigit(*line_sep) )
      *line_sep = atoi(line_sep);
    strcpy(head_line,oper_bnf->GetParameter("HeadLine","YES"));
    strcpy(string_sep,oper_bnf->GetParameter("StringSeparator","\""));
    
    output = new DBQOutput(cpath,line_sep,field_sep,string_sep,
                           *head_line == 'Y' || *head_line == 'y');
  }
  if ( op_code == ST_db_output )
  {
    strcpy(dsname,oper_bnf->GetParameter("Datasource","DATABASE"));
    strcpy(extname,oper_bnf->GetParameter("Extent",NULL));
    
    output = new DBQOutput(NULL,dsname,extname);
  }
  if ( !output )                                     ERROR

  bnode::Open (object_ref,nodenode,DBFieldDef::GetStaticFieldDef(T_INT),NULL,PI_Read);

  output->Open(Bnodenode->get_nodefield()->GetDBStruct());
  if ( !GetArea() ) 
    AllocateArea();
  if ( nodeinst )
    nodeinst->set_iselarea(GetArea());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACOPOutput - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACOPOutput"

     ACOPOutput :: ~ACOPOutput ( )
{

  if ( nodeinst )
    nodeinst->set_iselarea(NULL);
  
  if ( nodeidnt == NODE_ID )
    ACOperation::Close();


}


