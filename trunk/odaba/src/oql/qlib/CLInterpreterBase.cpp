/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    CLInterpreterBase

\brief    


\date     $Date: 2006/08/28 17:00:53,90 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CLInterpreterBase"

#include  <poql.h>
#include  <ioshell.h>
#ifndef   DLL_CommandLine_HPP
#define   DLL_CommandLine_HPP
#include  <sCommandLine.hpp>
#include  <sDLL.h>
#endif
#include  <sBNFData.hpp>
#include  <sCLICollection.hpp>
#include  <sCLIDataSource.hpp>
#include  <sCLInterpreter.hpp>
#include  <sCLInterpreterBase.hpp>
#include  <sCommandLine.hpp>
#include  <sFunctLink.hpp>
#include  <sPropertyHandle.hpp>
#include  <scfte.hpp>
#include  <sCLInterpreterBase.hpp>


/******************************************************************************/
/**
\brief  CLInterpreterBase - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  odaba_client - ODABA Client Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLInterpreterBase"

     CLInterpreterBase :: CLInterpreterBase (ODABAClient &odaba_client )
                     : CommandLine(NULL,YES,this),
  cmd(NULL),
  client(odaba_client),
  cli_list(),
  current_ds(NULL),
  last_ds(NULL),
  last_id(0),
  count(0),
  from_console(YES),
  child(NULL),
  parent(NULL),
  input_mode(YES),
  proc_opt(' '),
  procedures(NULL)

{
  int       i = 0;
  cmd = this;
  
  for ( i = 0; i < PARM_COUNT; i++ )
    parameters[i] = NULL;


}

/******************************************************************************/
/**
\brief  i01 - 



\param  clipbase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLInterpreterBase"

     CLInterpreterBase :: CLInterpreterBase (CLInterpreterBase *clipbase )
                     : CommandLine(NULL,clipbase->get_echo(),
            clipbase->get_top_cmdline()),
  cmd(NULL),
  client(clipbase->get_client()),
  cli_list(),
  current_ds(NULL),
  last_ds(NULL),
  last_id(clipbase->get_last_id()),
  count(clipbase->get_count()),
  from_console(clipbase->get_from_console()),
  child(NULL),
  parent(clipbase),
  input_mode(clipbase->get_input_mode()),
  proc_opt(clipbase->get_proc_opt()),
  procedures(NULL)
{
  int                i;
  CLIDataSource     *ds;
  cmd = clipbase->get_cmd();
  
  clipbase->get_cli_list().GoTop();
  while ( ds = clipbase->get_cli_list().GetNext() )
  {
    cli_list.AddTail(new CLIDataSource(this,ds,ds->get_id()));
    if ( ds == clipbase->get_current_ds() )
      current_ds = cli_list.GetTail();
    if ( ds == clipbase->get_last_ds() )
      last_ds = cli_list.GetTail();
  }
  
  for (i=0; i < PARM_COUNT; i++ )
    parameters[i] = strdup(clipbase->parameters[i]);

  if ( output = clipbase->get_output() )
    permanent_redirection = clipbase->get_permanent_redirection();

}

/******************************************************************************/
/**
\brief  ChangeDataSource - 



\return term - 

\param  dsname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeDataSource"

logical CLInterpreterBase :: ChangeDataSource (char *dsname )
{
  int              id;
  CLIDataSource   *ds_context;
  CLIDataSource   *ds;
  logical          term = NO;
BEGINSEQ
  last_id = 0;
  cli_list.GoTop();
  while ( ds = cli_list.GetNext() )
    if ( last_id < ds->get_id() )
      last_id = ds->get_id();
      
  if ( !dsname || !*dsname )
  {
    if ( !current_ds )
    {
      Output("missing data source name\n");
      Help("cd");
    }
    else
    {
      cli_list.GoTop();
      while ( ds_context = cli_list.GetNext() )
        Output("%i: %s\n",ds_context->get_id(),ds_context->get_name());
    }
  }
  else if ( *dsname >= '0' && *dsname <= '9' )
  {
    id =  atoi(dsname);
    if ( !(ds_context = LocateDataSource(id)) )
    {
      Output("data source '%i' not opened\n",id);    ERROR
    }
    current_ds = ds_context;
    last_ds    = current_ds;
  }
  else if ( *dsname == '*' )
  {
    if ( (ds_context = new CLIDataSource(this,current_ds,++last_id)) && ds_context->IsOpened() )
    {
      cli_list.AddTail(ds_context);
      current_ds = ds_context;
      last_ds    = current_ds;
    }
    else
    {
      delete ds_context;
      last_id--;
    }
  }
  else if ( *dsname == '.' )
  {
    Close(current_ds);
  }
  else
  {
    if ( (ds_context = new CLIDataSource(this,client,dsname,++last_id)) && ds_context->IsOpened() )
    {
      cli_list.AddTail(ds_context);
      current_ds = ds_context;
      last_ds    = current_ds;
    }
    else
    {
      delete ds_context;
      last_id--;
    }
  }



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckCondition - 



\return cond - 

\param  expression - OQL expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckCondition"

logical CLInterpreterBase :: CheckCondition (char *expression )
{
  logical                 cond = YES;
  OperationHandle        *oph;

BEGINSEQ
  if ( !cmd->get_condition() )                       LEAVESEQ

  oph = (OperationHandle *)cmd->get_condition();
  if ( oph->Execute(NULL) )                          ERROR
  if ( !oph->GetResult().IsTrue() )                  ERROR


RECOVER
  cond = NO;
ENDSEQ
  return(cond);;
}

/******************************************************************************/
/**
\brief  CheckDS - 



\return term - 

\param  msg_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDS"

logical CLInterpreterBase :: CheckDS (logical msg_opt )
{
  char             *cid;
  int               id;
  CLIDataSource    *ds_context = NULL;
  logical           term = NO;
BEGINSEQ
  current_ds = last_ds;
  if ( cid = GetOption('D') )
  {
    id =  atoi(cid);
    if ( !(ds_context = LocateDataSource(id)) )
    {
      Output("data source '%i' not opened\n",id);    ERROR
    }
    current_ds = ds_context;
  }
  if ( !current_ds )
    current_ds = cli_list.GetHead();
  if ( !current_ds && msg_opt )
  {
    Output("Error - no data collection opened\n",id);
                                                     ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ClearCMDList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearCMDList"

void CLInterpreterBase :: ClearCMDList ( )
{

  cmd_list = NULL;

}

/******************************************************************************/
/**
\brief  Close - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical CLInterpreterBase :: Close ( )
{
  CLIDataSource    *ds;
  cmd = NULL;
  RemoveCondition();
      
  while ( ds = cli_list.GetTail() )
  {
    cli_list.RemoveAt();
    delete ds;
  }
  last_ds = current_ds = NULL;
  return(NO);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ds_context - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical CLInterpreterBase :: Close (CLIDataSource *ds_context )
{
  CLIDataSource    *ds = NULL;
  CLIDataSource    *tds = NULL;
  if ( current_ds == ds_context )
    current_ds = NULL;
  if ( last_ds == ds_context )
    last_ds = NULL;
  
  cli_list.GoTop();
  while ( ds = cli_list.GetNext() )
    if ( ds == ds_context )
      cli_list.RemoveAt();
    else
      tds = ds;

  delete ds_context;
  if ( !current_ds )
    current_ds = tds;

  if ( !current_ds )
    current_ds = cli_list.GetHead();

  if ( !last_ds )
    last_ds = current_ds;
  return(NO);
}

/******************************************************************************/
/**
\brief  CommandLoop - 



\return term - 

\param  command_file - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CommandLoop"

logical CLInterpreterBase :: CommandLoop (char *command_file )
{

  if ( command_file )
    RunBatch(command_file);
  
  input_mode = YES;
  echo = NO;  
  while ( GetConsoleCommand() )
    if ( *GetCommand() )
      if ( ExecuteCommand() )
        break;
  return(NO);
}

/******************************************************************************/
/**
\brief  CreatePropertyHandle - 



\return ph - 

\param  ph - 
\param  prop_path - Property path
\param  copy_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePropertyHandle"

PropertyHandle CLInterpreterBase :: CreatePropertyHandle (PropertyHandle &ph, char *prop_path, logical copy_opt )
{
  PropertyHandle      prophdl;
  if ( prop_path && &ph )
  {
    if ( copy_opt )
      prophdl.Open(ph,prop_path);           // avoid 109 for misspellings, Check-function
    else
      prophdl.Open(&ph,prop_path);          // avoid 109 for misspellings, Check-function
  }
  else
  {
    if ( copy_opt )
      prophdl.CopyHandle(ph);
    else
      prophdl.CopyHandle(&ph);
  }

  return(&prophdl);
}

/******************************************************************************/
/**
\brief  DisplayAttribute - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  ph - 
\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayAttribute"

logical CLInterpreterBase :: DisplayAttribute (PropertyHandle &ph, char *name )
{
  int32                   indx0 = 0;
  PropertyHandle          prophdl;
  char                   *prop_path;
  logical                 term = NO;
BEGINSEQ
  if ( !ph.IsValid() )                                 ERROR
  ph.Execute(NULL);
  if ( ph.IsBasicType() || ph.IsEnumeration() ) 
    DisplayAttribute(name,ph);
  else
    while ( (prop_path = ph.GetAttribute(indx0++,NO,NO)) && *prop_path )
    {
      prophdl.Open(ph,prop_path);
      DisplayAttribute(prop_path,prophdl);
    }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayAttribute"

logical CLInterpreterBase :: DisplayAttribute (char *prop_path )
{
  PropertyHandle          ph;
  logical                 term = NO;
BEGINSEQ
  if ( !(ph = GetPropertyHandle(prop_path)).IsValid() )  ERROR

  if ( !ph.IsSelected() )
    Output("Error- no instance selected\n");
  
  CLInterpreterBase::DisplayAttribute(ph,prop_path);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  name - 
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayAttribute"

logical CLInterpreterBase :: DisplayAttribute (char *name, PropertyHandle &ph )
{
  DBFieldDef             *fielddef;
  int32                   indx0 = 0;
  int32                   dim = 1;
  char                    string[17];
  logical                 term = NO;
BEGINSEQ
  if ( !(fielddef = ph.GetDescription()) )                ERROR

  if ( !(dim = fielddef->fmcbdim) || ph.IsAutoSelection() )
    dim = 1;

  while ( indx0 < dim ) 
  {
    Output("  %s",name);
    if ( dim > 1 )
    {
      Output("[%s]",gvtxitoa(indx0,string,10));
      ph.Get(indx0);
    }
    Output("=%s\n",ph.GetString());
    indx0++;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 



\return term - 

\param  command_file - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical CLInterpreterBase :: Execute (char *command_file )
{
  logical                 term = NO;
  CommandLoop(command_file);
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteCommand - 



\return process_opt - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteCommand"

char CLInterpreterBase :: ExecuteCommand ( )
{
  char          *cmdname;
  logical        rc = NO;
  logical        term = NO;
  if ( cmd != this )
    Copy(cmd);
  
  ReplaceSysVariables();
  if ( parameters )
    ReplaceParameters(parameters);
  
  if ( output && !permanent_redirection )
    ResetOutput();
  ParseCommand();
  if ( output_file )
  {
    if ( parent && (output == parent->get_output()) )
      output = NULL;
    InitOutput();
  }
  cmdname = GetCommand();
    
  if ( type == CLT_function )
    ExecutePHFunction(GetCollection(),cmdname,NO);
  else if ( type != CLT_redirection )
    if ( ExecuteFunction(cmdname,NO) && from_console )
    {
      Output("Error - command '%s' not supported\n",cmdname);
      Help(NULL);
    }

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  cmdline - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteCommand"

char CLInterpreterBase :: ExecuteCommand (char *cmdline )
{
  char   process_opt = NO;
BEGINSEQ
  ResetCommand();
  SetCommand(cmdline);
  Initialize(NULL);
  
  if ( type == CLT_undefined )                       ERROR
  
  if ( ExecuteCommand() )                            ERROR
RECOVER
  process_opt = YES;
ENDSEQ
  return(process_opt);
}

/******************************************************************************/
/**
\brief  ExecuteCommandList - 



\return term - 

\param  cmdlist - 
\param  pos - position relativly 1
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteCommandList"

logical CLInterpreterBase :: ExecuteCommandList (DLL(CommandLine) *cmdlist, uint16 pos )
{
  CommandLine            *old_cmd = cmd;
  logical                 term = NO;
BEGINSEQ
  if ( !cmdlist && !cmd->get_cmd_list() )            LEAVESEQ
    
  DLL(CommandLine) cursor(cmdlist ? *cmdlist : *cmd->get_cmd_list());
  
  cursor.GoTop();
  while ( (cmd = cursor.GetNext()) && pos )
    pos--;
    
  while ( cmd )
  {
    input_mode = NO;
    if ( term = ExecuteListCommand() )
    {
      if ( term == YES )                            ERROR
      LEAVESEQ
    }
    switch ( proc_opt )
    {
      case 'l' : proc_opt = 'c';
      case 'x' :
      case 'r' : LEAVESEQ
    }
    cmd = cursor.GetNext();
  }
  cmd = old_cmd;

  input_mode = YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 



\return term - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical CLInterpreterBase :: ExecuteFunction (char *fname, logical chk_opt )
{
  logical                 term = NO;
BEGINSEQ
  if ( chk_opt )                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteListCommand - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteListCommand"

logical CLInterpreterBase :: ExecuteListCommand ( )
{
  CLInterpreterBase      *clip;
  logical                 term = NO;
  if ( !strcmp(cmd->GetCommand(),"DO") )
  {
    clip = Push();
    term = clip->ExecuteCommandList(cmd->GetCMDList(),0);
    clip->Pop();
  }
  else if ( !strcmp(cmd->GetCommand(),"BEGIN") )
    term = ExecuteCommandList(cmd->GetCMDList(),0);
  else
    term = ExecuteCommand();

  return(term);
}

/******************************************************************************/
/**
\brief  ExecutePHFunction - 



\return term - 

\param  co - 
\param  fname - 
\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecutePHFunction"

logical CLInterpreterBase :: ExecutePHFunction (PropertyHandle *co, char *fname, char chkopt )
{
  PropertyHandle    retval;
  FunctLink         flink;
  int               i = 0;
  logical           term = NO;
BEGINSEQ
  if ( !chkopt )
  {
    if ( CheckDS(YES) )                              ERROR
    if ( current_ds->CheckCollection(YES) )          ERROR
      
    if ( !(co = GetCollection()) )
    {
      Output(" Error - No collection selected for property handle function\n");
      ERROR
    }
    
    if ( flink.SetFunctionPtr(co->GetDictionary(),"PropertyHandle",fname) )
    {
      Output(" Error - Property handle function '%s' not supported\n",fname);
      ERROR
    }
    
    ParmList  pl(*co,parm_list);
    if ( !retval.GetDescription() )
      flink.Execute(co,&retval,&pl,NULL,ET_Initialize);
    if ( flink.Execute(co,&retval,&pl,NULL,ET_First) )
    {
      Output(" Error - Executing property handle function\n");
      ERROR
    }
    if ( retval.IsBasicType() )
    {
      if ( strcmp(retval.GetCurrentType(),"LOGICAL") )
        Output("  %s\n",retval.GetString());
      else
        Output("  %s\n",(char *)(retval.IsTrue() ? "yes" : "no") );
    }
    if ( retval.IsCollection() )
    {
      if ( retval.IsPositioned() )
        Output("  instance %l of %l selected\n",retval.GetCurrentIndex(),retval.GetCount());
      else
        Output("  no instance selected\n");
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCollection - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollection"

CLICollection *CLInterpreterBase :: GetCollection ( )
{

  return ( this && current_ds ? current_ds->GetCollection(AUTO)
                              : NULL );


}

/******************************************************************************/
/**
\brief  GetCommandLine - 



\return string - String area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCommandLine"

char *CLInterpreterBase :: GetCommandLine ( )
{
  int                i = 0;
  static   NString   nstring;
  char              *string = NULL;
  nstring = "";
  
  while ( parm_list[i] )
  {
    nstring += parm_list[i++];
    nstring += ' ';
  }

  string = nstring;
  return(string);
}

/******************************************************************************/
/**
\brief  GetCommandType - 



\return cmdtype - 

\param  cmd_line - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCommandType"

CommandTypes CLInterpreterBase :: GetCommandType (CommandLine *cmd_line )
{
  char                   *cmdstr;
  char                   *pos;
  char                   *cmdname;
  CommandTypes            cltype;
  int                     i = 0;
BEGINSEQ
  if ( !cmd_line )
    cmd_line = cmd;
  if ( !cmd_line )                                   ERROR
    
  cltype = CLT_command;
  if ( !(cmdname = cmd_line->GetCommand()) )         ERROR
  gvtsupr(cmdname);
  
  if ( *cmdname == '\'' )      // comment
    cltype = CLT_comment;
  else if ( !strcmp(cmdname,"DO") || !strcmp(cmdname,"BEGIN") )  
    cltype = CLT_begin;                           // begin
  else if ( !strcmp(cmdname,"END") )              // terminate
    cltype = CLT_end;
  else if ( *cmdname == '@' )                     // entry point
    cltype = CLT_entrypoint;
  else if ( ExecuteFunction(cmdname,YES) )
  {
    cmd_line->GetCommandName();
    cltype = CLT_function;
  }
  if ( cltype == CLT_command )
    if ( !strcmp(cmdname,"FA") || !strcmp(cmdname,"OQL") || !strcmp(cmdname,"WHILE") || !strcmp(cmdname,"IF") ) // do-commands
    {
      cmdstr = cmd_line->get_command();
      if ( ( ((pos = strstr(cmdstr,"do")) || (pos = strstr(cmdstr,"DO")) || 
              (pos = strstr(cmdstr,"Do"))) && (pos[2] == 0 || pos[2] == ' ') )      ||
           ( ((pos = strstr(cmdstr,"begin")) || (pos = strstr(cmdstr,"BEGIN")) || 
              (pos = strstr(cmdstr,"Begin"))) && (pos[5] == 0 || pos[5] == ' ') )         )
          cltype = CLT_begin;                     // begin
    }
  
  cmd_line->SetType(cltype);
RECOVER
  cltype = CLT_undefined;
ENDSEQ
  return(cltype);
}

/******************************************************************************/
/**
\brief  GetCondition - 



\return oper_hdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCondition"

OperationHandle *CLInterpreterBase :: GetCondition ( )
{
  OperationHandle        *oph = NULL;
  if ( !cmd )
    cmd = this;
  oph = (OperationHandle *)cmd->get_condition();
  return(oph);
}

/******************************************************************************/
/**
\brief  GetConsoleCommand - 



\return command - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConsoleCommand"

char *CLInterpreterBase :: GetConsoleCommand ( )
{

  if ( proc_opt == 'x' )
    return(NULL);
    
  cmd = this;
  cmd->InputCommand(GetPrompt());

  return(cmd->GetCommand());
}

/******************************************************************************/
/**
\brief  GetEntryPoint - 



\return cmdlist - 

\param  ep_name - 
\param  posptr - 
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryPoint"

DLL(CommandLine) *CLInterpreterBase :: GetEntryPoint (char *ep_name, uint16 *posptr, logical recursive )
{
  extern  CLInterpreterBase *OShell;
  DLL(CommandLine) *cmdlist = NULL;
  if ( parent )
    cmdlist = parent->GetEntryPoint(ep_name,posptr,recursive);
  else if ( procedures )
    cmdlist = procedures->GetEntryPoint(ep_name,posptr,recursive);
  else if ( OShell && OShell != this )
    cmdlist = OShell->GetEntryPoint(ep_name,posptr,recursive);
  return(cmdlist);
}

/******************************************************************************/
/**
\brief  GetOQLCommand - 



\return string - String area

\param  cmdlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOQLCommand"

char *CLInterpreterBase :: GetOQLCommand (DLL(CommandLine) *cmdlist )
{
  CommandLine            *old_cmd = cmd;
  static  NString         nstring(255);
  char                   *string = NULL;
BEGINSEQ
  if ( !cmdlist && !cmd->get_cmd_list() )            LEAVESEQ
    
  DLL(CommandLine) cursor(cmdlist ? *cmdlist : *cmd->get_cmd_list());
  
  nstring = "";
  cursor.GoTop();
  while ( cmd = cursor.GetNext() )
  {
    nstring += cmd->get_command();
    nstring += '\n';
  }
  
  cmd = old_cmd;
  string = nstring;

ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetPrompt - 



\return command - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrompt"

char *CLInterpreterBase :: GetPrompt ( )
{
  static   char      prompt[256];
  int       num;
  strcpy(prompt,"ODABA");
  if ( last_ds )
  {
    if ( (num = last_ds->get_ph_last()) < 0 )
      strcpy(prompt,last_ds->get_name());
    else
    {
      strcpy(prompt,last_ds->get_name());
      strcat(prompt,"/");
      while ( num-- )
        strcat(prompt,".");
      if ( last_ds->get_ph_last() > 0 )
        strcat(prompt,"/");
      strcat(prompt,last_ds->GetCollection(last_ds->get_ph_last())->GetName());
    }
  }
  strcat(prompt,">");

  return(prompt);
}

/******************************************************************************/
/**
\brief  GetPropertyHandle - 



\return ph - 

\param  prop_path - Property path
\param  copy_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle CLInterpreterBase :: GetPropertyHandle (char *prop_path, logical copy_opt )
{
  PropertyHandle     *ph = current_ds->GetCollection(AUTO);
  PropertyHandle      prophdl;
  prophdl = CreatePropertyHandle(*ph,prop_path,copy_opt);
  return(&prophdl);
}

/******************************************************************************/
/**
\brief  Help - 



\return term - 

\param  cmdstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Help"

logical CLInterpreterBase :: Help (char *cmdstring )
{
  logical      all = NO;
  logical      extended = NO;
BEGINSEQ
  SetOption("h");
  if ( cmdstring && *cmdstring )
  {
    SetOption("d");
    gvtsupr(cmdstring);
    ExecuteFunction(cmdstring,NO);
  }
  else
  {
    if ( GetOption('a') )
      all = YES;
    if ( GetOption('f') )
    {
//                                     :   
      Output("Function call            : fname [parm_1 ... parm_N] -Dn -Cn\n");

//                     1         2         3         4         5         6         7         8
//            12345678901234567890123456789012345678901234567890123456789012345678901234567890   
      Output("  Functions can only be called when a collection is opened. The parameters\n");
      Output("  passed to a function depend on the function called and are listed below. You \n");
      Output("  may redirect function calls to another collection or to a collection for \n");
      Output("  another data source context. When redirecting the function call to another  \n");
      Output("  data source a collection must be opened for the target data source.\n");
      Output("  More details about functions you can find at:\n");
      Output("    www.run-software.com/ODABADocu/index.php (IF_AccessClass/PropertyHandle)\n");
      Output("  \n");
//                          -
      Output("  fname       - function name to be executed\n");
      Output("                class\n");
      Output("  parm_n      - function specific parameters\n");
      Output("  -Dn         - redirect function to other data source context\n");
      Output("  -Cn         - redirect function to other collection context\n");
      Output("  \n");
      Output("  Following functions are supported by OShel:\n");
      Output("  \n");
      Output("  Execute instance action : ExecuteInstanceAction act_name [parm1 ... parmN]\n");
      Output("  Execute property action : ExecutePropertyAction act_name [parm1 ... parmN]\n");
      Output("  Get instance count      : GetCount\n");
      Output("  Has data                : HasData\n");
      LEAVESEQ
    }
    
    ExecuteFunction("NEXT",NO);
    ExecuteFunction("STEP",NO);
    ExecuteFunction("STEPOUT",NO);
    ExecuteFunction("CONTINUE",NO);
    ExecuteFunction("RUN",NO);
    ExecuteFunction("LISTEXPRESSION",NO);
    ExecuteFunction("LISTCURRENTLINE",NO);
    ExecuteFunction("BACKTRACE",NO);
    ExecuteFunction("SETBREAK",NO);
    ExecuteFunction("RESETBREAK",NO);
    ExecuteFunction("BREAKALWAYS",NO);
    
    ExecuteFunction("HELP",NO);
    ExecuteFunction("ECHO",NO);
    ExecuteFunction("CALL",NO);
    ExecuteFunction("LOAD",NO);
    ExecuteFunction("FA",NO);
    ExecuteFunction("IF",NO);
    ExecuteFunction("WHILE",NO);
    ExecuteFunction("DO",NO);
    ExecuteFunction("BEGIN",NO);
    ExecuteFunction("END",NO);
    ExecuteFunction("LD",NO);
    ExecuteFunction("CD",NO);
    ExecuteFunction("SET",NO);
    ExecuteFunction("REDIR",NO);
    ExecuteFunction("Q",NO);
    
    if ( all || current_ds )
    {
      ExecuteFunction("CC",NO);
      ExecuteFunction("LCN",NO);
      
      ExecuteFunction("BEGINTRANSACTION",NO);
      ExecuteFunction("COMMITTRANSACTION",NO);
      ExecuteFunction("ROLLBACK",NO);
      
      ExecuteFunction("DELETEEXTENT",NO);
      ExecuteFunction("DELETEEXTENTREF",NO);
      
      ExecuteFunction("OQL",NO);
      ExecuteFunction("PRINT",NO);
      
      if ( all || current_ds->GetCollection(AUTO) )    
      {
        ExecuteFunction("LI",NO);
        ExecuteFunction("LOC",NO);
        ExecuteFunction("NEXT",NO);
        ExecuteFunction("PREV",NO);
        ExecuteFunction("LO",NO);
        ExecuteFunction("LK",NO);
        ExecuteFunction("CO",NO);
        ExecuteFunction("CRT",NO);
        ExecuteFunction("CPY",NO);
        ExecuteFunction("MOV",NO);
        ExecuteFunction("DEL",NO);
        ExecuteFunction("LAN",NO);
        ExecuteFunction("SAL",NO);
        ExecuteFunction("SAV",NO);
        ExecuteFunction("LAV",NO);
        ExecuteFunction("SFC",NO);
        ExecuteFunction("RFC",NO);
      }
    }
  }
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  ListDataSource - 



\return term - 

\param  display_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListDataSource"

logical CLInterpreterBase :: ListDataSource (char *display_opt )
{
  char             *dsname;
  int32              indx0 = 0;
  logical           term = NO;
  while ( dsname = client.GetDataSource(indx0++) )
    Output("%s\n",dsname);

  return(term);
}

/******************************************************************************/
/**
\brief  LoadProcedure - 



\return term - 

\param  file_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadProcedure"

logical CLInterpreterBase :: LoadProcedure (char *file_name )
{
  CommandLine            *cmdline;
  logical                 term = NO;
BEGINSEQ
  if ( parent )
    parent->LoadProcedure(file_name);
    
  if ( !procedures )
    procedures = new CommandLine(NULL,echo,top_cmdline);
  if ( CommandLine::LoadProcedure(file_name,NULL) )
  {
    Output(" ERROR - procedure '%s' not found or not a valid file\n",file_name);
    ERROR
  }

  SetCommand("BEGIN");
  cmdline = new CommandLine(*cmd);
  cmd_list = NULL;
  entry_points = NULL;
  procedures->AddEntryPoint(file_name,AUTO);
  procedures->AddCommand(cmdline);
  ResetCommand();
  SetCommand("RETURN");
  cmdline = new CommandLine(*cmd);
  procedures->AddCommand(cmdline);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateDataSource - 



\return ds - 

\param  ds_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateDataSource"

CLIDataSource *CLInterpreterBase :: LocateDataSource (int32 ds_id )
{
  CLIDataSource    *ds = NULL;
  cli_list.GoTop();
  while ( ds = cli_list.GetNext() )
    if ( ds_id == ds->get_id() )
      break;

  return(ds);
}

/******************************************************************************/
/**
\brief  Pop - 



\return clip - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pop"

CLInterpreterBase *CLInterpreterBase :: Pop ( )
{
  CLInterpreterBase  *clip = NULL;
  if ( clip = parent )
  {
    clip->child = NULL;
    if ( parent && (output == parent->get_output()) )
      output = NULL;
    parent = NULL;
    delete this;
  }


  return(clip);
}

/******************************************************************************/
/**
\brief  Push - 



\return clip - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Push"

CLInterpreterBase *CLInterpreterBase :: Push ( )
{
  CLInterpreter   *clip = (CLInterpreter *)this;
  child = new CLInterpreter(clip);

  return(child);
}

/******************************************************************************/
/**
\brief  ReadCommands - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadCommands"

logical CLInterpreterBase :: ReadCommands ( )
{

  return( input_mode ? cmd->ReadCommands(GetPrompt()) : NO );

}

/******************************************************************************/
/**
\brief  RemoveCondition - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveCondition"

void CLInterpreterBase :: RemoveCondition ( )
{
  OperationHandle        *oph;
BEGINSEQ
  if ( !cmd )                                        LEAVESEQ
    
  if ( oph = (OperationHandle *)cmd->get_condition() )
    delete oph;
  
  cmd->SetCondition(NULL);
ENDSEQ

}

/******************************************************************************/
/**
\brief  ResetParameters - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetParameters"

void CLInterpreterBase :: ResetParameters ( )
{
  int              i;
  for (i=0; i < PARM_COUNT && parameters[i]; i++ )
  {
    free(parameters[i]);
    parameters[i] = NULL;
  }



}

/******************************************************************************/
/**
\brief  RunBatch - 



\return term - 

\param  file_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RunBatch"

logical CLInterpreterBase :: RunBatch (char *file_name )
{
  char                   *ep;
  uint16                  pos = 0;
  char                   *fname = NULL;
  DLL(CommandLine)       *cmdlist;
  logical                 term = NO;
BEGINSEQ
  if ( !file_name )                                  SDBERR(99)
  fname = strdup(file_name);
  
  if ( ep = strchr(fname,'@') )
  {
    *ep = 0;
    ep++;
  }
    
  if ( *fname && !(cmdlist = GetEntryPoint(fname,&pos,YES)) )
    if ( LoadProcedure(fname) )                  ERROR
    
  if ( !(cmdlist = GetEntryPoint(ep ? ep : fname,&pos,YES)) )
                                                     SDBERR(99)
  if ( ExecuteCommandList(cmdlist,pos) )             ERROR

  switch ( proc_opt )
  {
    case 'l' : 
    case 'r' : proc_opt = 'c';
    case 'x' : LEAVESEQ
  }

RECOVER
  term = YES;
ENDSEQ
  if ( fname )
    free(fname);
  return(term);
}

/******************************************************************************/
/**
\brief  SetCondition - 



\return term - 

\param  expression - OQL expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCondition"

logical CLInterpreterBase :: SetCondition (char *expression )
{
  OperationHandle        *oph;
  char                   *expr = NULL;
  logical                 term = NO;
BEGINSEQ
  RemoveCondition();
  
  if ( !cmd )
    cmd = this;
  
  if ( *expression == '{' )
  {
    expr = (char *)malloc(strlen(expression)+2);
    expression = strcpy(expr,expression);
    strcat(expr,";");
  }
  oph = new OperationHandle(*current_ds->GetCollection(AUTO));
  if ( oph->ProvideExpression(current_ds->get_ds_handle().GetDictionary(),
                              current_ds->get_ds_handle().GetDictionary(),
                              current_ds->get_ds_handle(),expression) )   ERROR  
  cmd->SetCondition(oph);
RECOVER
  term = YES;
ENDSEQ
  if ( expr )
    free(expr);
  return(term);
}

/******************************************************************************/
/**
\brief  SetDataCollection - 



\return term - 

\param  ph_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataCollection"

logical CLInterpreterBase :: SetDataCollection (PropertyHandle *ph_ptr )
{
  ODABAClient      odaba;
  CLIDataSource   *ds;
  logical          term = NO;
BEGINSEQ
  last_ds = current_ds = NULL;
  
  cli_list.GoTop();
  while ( ds = cli_list.RemoveHead() )
    delete ds;
  
  if ( !ph_ptr )                                     LEAVESEQ

  ds = new CLIDataSource(this,odaba,ph_ptr->GetObjectHandle(),"OC-Intern",1);
  cli_list.AddTail(ds);
  last_ds = current_ds = ds;
  
  ds->SetPropertyHandle(ph_ptr);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetOShell - 




\param  clip_base - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOShell"

void __cdecl CLInterpreterBase :: SetOShell (CLInterpreterBase *clip_base )
{
  extern  CLInterpreterBase *OShell;

  OShell = clip_base;

}

/******************************************************************************/
/**
\brief  SetOption - 



\return option - 

\param  optstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOption"

char *CLInterpreterBase :: SetOption (char *optstring )
{
  int         i = 0;
  char       *option = NULL;
BEGINSEQ
  while ( i < OPT_COUNT && (option = options[i++]) )
    if ( *option == *optstring )  
      break;
  
  if ( i >= OPT_COUNT )                              SDBERR(99)
  
  options[i-1] = optstring;
RECOVER
  option = NULL;
ENDSEQ
  return(option);
}

/******************************************************************************/
/**
\brief  SetParameters - 




\param  parmno - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParameters"

void CLInterpreterBase :: SetParameters (uint16 parmno )
{
  int           i;
  ResetParameters();
  for ( i = 0; i+parmno < PARM_COUNT && parm_list[i+parmno]; i++ )
    parameters[i] = strdup(parm_list[i+parmno]);
    


}

/******************************************************************************/
/**
\brief  SetValue - 



\return term - 

\param  ph - 
\param  prop_path - Property path
\param  value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical CLInterpreterBase :: SetValue (PropertyHandle &ph, char *prop_path, char *value )
{
  DictionaryHandle       &dictionary = current_ds->DictHandle();
  BNFData                *bdata;
  logical                 term = NO;
BEGINSEQ
  if ( !ph.IsWrite() )
  {
    Output("Error- cannot update instance or no instance selected\n");         
                                                     ERROR
  }
  
  if ( !(bdata = dictionary.ParseExpression(value,"operand")) )
  {
    Output("Error - assignment value is not a valid operand\n");   
                                                     ERROR
  }
  
  if ( bdata->IsSymbol("std_constant") )
  {
    if ( bdata->IsSymbol("std_string") )
      ph = bdata->GetStringConstant();
    else
      ph = bdata->GetStringValue(NULL,NULL);
  }
  else if ( bdata->IsSymbol("OQLSelect") || bdata->IsSymbol("access_path") )
  {
    PropertyHandle       tph = GetPropertyHandle(value,NO);
    if ( !tph.IsValid() )
    {
      Output("Error - cannot open query or access path '%s'\n",value);   
                                                     ERROR
    }
    ph = tph;
  }
  else 
  {
    PropertyHandle phVoid = GetPropertyHandle(NULL);
    OperationHandle      oh(phVoid);
    if ( oh.ProvideExpression(dictionary,dictionary,current_ds->DBHandle(),bdata) )
    {
      Output("Error - invalid expression '%s'\n",value);   
                                                     ERROR
    }
    if ( !oh.Execute(NULL) )
      ph = oh.GetResult();
  }

  if ( !ph.IsCollection() )
    DisplayAttribute(ph,prop_path);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~CLInterpreterBase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CLInterpreterBase"

     CLInterpreterBase :: ~CLInterpreterBase ( )
{

  delete procedures;
  
  ResetParameters();  
  Close();


}


