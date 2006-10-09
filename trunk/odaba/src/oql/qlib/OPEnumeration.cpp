/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OPEnumeration

\brief    


\date     $Date: 2006/04/19 12:27:00,46 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPEnumeration"

#include  <poql.h>
#include  <sDictionary.hpp>
#include  <sOPParmList.hpp>
#include  <sOPEnumeration.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPEnumeration :: Execute ( )
{
  OPBase                 *op_node;
  ExecReturnCodes         rc = ERC_success;
BEGINSEQ
  if ( op_node = Parmlist()->GetAt(0) )
  {
    SaveCO();
    rc = op_node->Execute();
    RestoreCO();
    if ( rc == ERC_terminate )                       ERROR
    DBObjectHandle     dbo(ObjectHandle());
    if ( value.Open(dbo,op_node->GetValue()->GetString(),dbo.GetAccess()) )
                                                     ERROR
  }
  

RECOVER
  rc = ERC_terminate;
ENDSEQ
  return(rc);
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

logical OPEnumeration :: Initialize (int32 ini_opt )
{
  DBFieldDef             *fielddef;
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( SetupParameters() )               ERROR
    case  4 : re_open = 3;
    case  3 : 
              fldfmcb = fielddef = new DBFieldDef("Enumeration","SDB_CSEntry",SYS_NSID,RL_reference,UNDEF,UNDEF,
                                                  UNDEF,NULL,NULL,NO,NULL,NULL,NULL);
              fielddef->GetDBStruct(DictHandle());
              fldfaloc = YES;
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
\brief  OPEnumeration - 



\param  oper_bnf - 
\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPEnumeration"

                        OPEnumeration :: OPEnumeration (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (NULL,oper_bnf,parent_node,parm_bnf)
{

  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPEnumeration - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPEnumeration"

                        OPEnumeration :: ~OPEnumeration ( )
{



}


