/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    COperation

\brief    Opreartion Handle
          Operation  handles can be used for executing operations as expressions
          or  function  calls.  Usually,  an  operation  is  associated  with  a
          property  handle defining the instance that is passed to the operation
          as calling object.

\date     $Date: 2006/07/24 14:32:41,21 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "COperation"

#include  <popa7.h>
#include  <sofifct.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sCNode.hpp>
#include  <sClientConnection.hpp>
#include  <sDictionary.hpp>
#include  <sOperation.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sCOperation.hpp>


/******************************************************************************/
/**
\brief  COperation - Constructor




\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "COperation"

     COperation :: COperation (PropertyHandle &prophdl_ref )
                     : CSHandle (((CNode *)prophdl_ref.get_nodeptr())->get_csconnection()),
Operation ()
{

  Open(prophdl_ref); 


}

/******************************************************************************/
/**
\brief  CheckResultDef - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckResultDef"

logical COperation :: CheckResultDef ( )
{
  CS_Handle   *cshandle;
  DBFieldDef  *fielddef;
  logical      conversion = csconnection->get_conversion();
  logical      cond       = YES;
BEGINSEQ
  if ( Get_rec_result()[1].GetLong(conversion) == NT_undefined )
  {
    PropertyHandle::Close();
    LEAVESEQ
  }
  if ( !get_nodeptr() )                                    ERROR

  if ( cshandle = Get_rec_result()[2].GetHandle() )
  {
    if ( cshandle->GetClientPointer() != get_nodeptr() )   ERROR
  }
  else
  {
    if ( !(fielddef = get_nodeptr()->GetInstFieldDef()) ||
         fielddef->fmcbrlev != R_DIRECT )            ERROR
    
    if ( strcmp(get_nodeptr()->GetCurrentType(),Get_rec_result()[5].GetString())  ||
         fielddef->fmcbsize != Get_rec_result()[6].GetLong(conversion)      ||
         fielddef->fmcbprec != Get_rec_result()[7].GetLong(conversion)      ||
         fielddef->fmcbdim  != Get_rec_result()[8].GetLong(conversion)         )
                                                     ERROR
  }
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Execute - Execute operation

        The  function executes  a predefined  opoeration. The result is returned
        as property handle. 
        It  is  possible  to  pass  a  property  handle as calling object. If no
        property  handle  is  passed  the  one  that  was  used for creating the
        operation  is used as calling object. When using amother property handle
        than the originating one the type of the properties must be identical.

\return term - Termination code

\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical COperation :: Execute (ParmList *parameters )
{
  logical        term = YES;
#ifndef IF_Class  // client version

  if ( !get_nodeptr() || IsValid(NO) )
  {
    LockSendParms();
    if ( !csconnection )
      SDBSET(517)
    else  
    {
      Get_send_parms().Fill((CS_Handle *)(CNode *)calling_object->get_nodeptr(),
                            parameters);
   
      if ( !CConnection()->SendCSMessage(this,S_COperation,SF_COperation_Execute_ci) )
        term = Get_rec_result()[0].GetUChar();
    }
    SetupResult_intern(term);
    SetupInstance(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  ParmList      *parmlist;
  SC_Operation *sc_oper = ((SC_Operation *)cso_ptr);
  
// hier müssen wir ggf. noch den Client-Pointer setzen, wenn das ServerHandle noch keinen Client hat und
// mit dem übergebenen Serverhandle identisch ist. Wenn anderes Serverhandle->Katastrophe  
  parmlist = (*parms)[1].GetParmList(connection->get_conversion());
  term = sc_oper->Execute(parmlist);
  delete parmlist;
   
  sc_oper->FillResult(result,term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Open - Open operation handle

        To  execute operations the opration handle must be opened. After opening
        the  operation handle an expression or a function can be associated with
        the operation handle for being executed.

\return term - Termination code

\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical COperation :: Open (PropertyHandle &prophdl_ref )
{
  logical       term = YES;

#ifndef IF_Class  // client version
  
  if ( !Operation::Open(prophdl_ref) )
  {
    if ( calling_object->get_nodeptr()->IsLocalNode() )
      SDBSET(526)
    else
      if ( !csconnection )
        SDBSET(517)
      else      
      {
        LockSendParms().Fill((CS_Handle *)(CNode *)calling_object->get_nodeptr());
        InitHandle();
    
        if ( !CConnection()->SendCSMessage(this,S_COperation,SF_COperation_Open_ci) )
          if ( !(term = Get_rec_result()[0].GetUChar()) )
            SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        UnlockSendParms();
      }
  }

  return(term);
  
#else             // server version
  
  SC_Operation *sc_oper;
  CS_Handle    *handle = parms->GetHandle();
  
  if ( sc_oper = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideOperation(
                     handle->GetClientObject()
                 ) )
  {
    handle->SetServerPointer(sc_oper);
    *result->GetHandle() = *handle;
    term = NO;
  }
  result->Fill(term);
  return(NO);


#endif


}

/******************************************************************************/
/**
\brief  ProvExpression - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci1 - 



\param  dictionary - 
\param  resobj - 
\param  obhandle - Database Object handle
\param  expr_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvExpression"

logical COperation :: ProvExpression (Dictionary *dictionary, ACObject *resobj, ACObject *obhandle, char *expr_string )
{
  logical        term = YES;
#ifndef IF_Class  // client version

  if ( !get_nodeptr() || IsValid(NO) )
  {
    LockSendParms();
    if ( !csconnection )
      SDBSET(517)
    else  
    {    
      Get_send_parms().Fill(expr_string);
    
      if ( !CConnection()->SendCSMessage(this,S_COperation,SF_COperation_ProvExpression_ci1) )
        term = Get_rec_result()[0].GetUChar();
    }
    SetupResult_intern(term);
    UnlockSendParms();
    set_expression(expr_string);
  }
  return(term);
  
#else             // server version
  
  SC_Operation *sc_oper = ((SC_Operation *)cso_ptr);
  
  ParmList *parmlist = (*parms)[1].GetParmList(connection->get_conversion());
  term =  sc_oper->ProvideExpression((*parms)[0].GetString()
          );
  delete parmlist;
   
  sc_oper->FillResult(result,term);

  return(NO);

#endif


}

/******************************************************************************/
/**
\brief  ci2 - 



\param  dictionary - 
\param  resobj - 
\param  obhandle - Database Object handle
\param  clsnames - 
\param  exprnames - 
\param  parmlist - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvExpression"

logical COperation :: ProvExpression (Dictionary *dictionary, ACObject *resobj, ACObject *obhandle, char *clsnames, char *exprnames, ParmList *parmlist, logical refresh_opt )
{
  logical        term = YES;
#ifndef IF_Class  // client version
  
  SDBSET(999)  // kommt später
  return(term);
  
#else             // server version
  
  return(NO);

#endif



}

/******************************************************************************/
/**
\brief  SetupInstance - 



\return ph_inst - Pointer to Property Handle

\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInstance"

Instance COperation :: SetupInstance (logical error_case )
{
  void          *inst = NULL;
  DBFieldDef    *field_def;
  logical        term = NO;
BEGINSEQ
  if ( !(field_def = GetDescription()) )             SDBERR(99)
  
  if ( IsCollection() )                              LEAVESEQ
  
  ProvideArea();
  Get_rec_result()[9].GetInstance(field_def,
                                  (void *)GetArea(),
                                  csconnection->get_conversion());
  inst  = GetArea();

      

RECOVER


ENDSEQ
  return(inst);
}

/******************************************************************************/
/**
\brief  SetupResult_intern - 



\return term - Termination code

\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupResult_intern"

logical COperation :: SetupResult_intern (logical error_case )
{
  logical        conversion;
  CS_Handle      cshandle;
  CS_Handle     *csh;
  char           property_path[512];
  char           strnames[ID_SIZE+1];
  char           sknames[ID_SIZE+1];
  char           ctx_struct[ID_SIZE+1];
  char          *sknames_ptr    = NULL;
  char          *ctx_struct_ptr = NULL;
  char          *str;
  logical        term           = NO;
BEGINSEQ
  if ( error_case )                                  ERROR
  if ( CheckResultDef() )                            LEAVESEQ
    
  conversion      = csconnection->get_conversion();
  
  if ( csh = Get_rec_result()[2].GetHandle() )
    cshandle = *csh;
  
  strcpy(property_path,(str = Get_rec_result()[4].GetString()) ? str : "__RESULT");
  
  if ( !(str = Get_rec_result()[5].GetString()) )    ERROR  // strnames
  strcpy(strnames,str);
    
  PropertyHandle::Close();
  
  if ( Get_rec_result()[3].GetUChar() )                     // is collection
  {
    if ( str = Get_rec_result()[6].GetString() )
      ctx_struct_ptr = strcpy(ctx_struct,str);
    if ( str = Get_rec_result()[7].GetString() )
      sknames_ptr = strcpy(sknames,str);  
      
    set_nodeptr(new CNode(calling_object->get_nodeptr(),
                          &cshandle,                          // Client property handle
                          ctx_struct_ptr,                     // context structure
                          property_path, strnames, 
                          sknames,                            // sort key
                          Get_rec_result()[8].GetUChar(),     // temporary extent
                          Get_rec_result()[9].GetUChar(),     // weak_typed (temporary extent)
                          Get_rec_result()[10].GetUChar()) ); // own_opt (temporary extent)
  }
  else
  {
    set_nodeptr(new CNode(calling_object->get_nodeptr(),
                          &cshandle,
                          property_path, strnames, SYS_NSID, RL_direct,
                          Get_rec_result()[6].GetLong(conversion),     // size
                          Get_rec_result()[7].GetUShort(conversion),   // precision
                          Get_rec_result()[8].GetULong(conversion)) );// dimension
  }

RECOVER
  PropertyHandle::Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~COperation - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~COperation"

     COperation :: ~COperation ( )
{

  Close();

}


