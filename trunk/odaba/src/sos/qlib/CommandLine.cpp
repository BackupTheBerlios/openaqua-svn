/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    CommandLine

\brief    Command line
          The  class  provides  services  for evaluating command line parameters
          and  options.  A  command  line  may contain a command, parameters and
          options.  The command is passed at  the beginning of the command line.
          Parameters  and options can appear  in any sequence. Parameters, which
          contain spaces (or separators must be passed in quotes (""). 
          Obptions  are preceeded  by '/'  or '-'  and an option character (e.g.
          -F).  Options may appear  at any place  in the parameter string except
          within  parameters  enclosed  in  quotes.  The  optionvalue  follows 
          immediately  the  option  character  (e.g. -Fc:	emp	empfile). Option
          values containining spaces or separators must be put in quotes.
          The  commandline allows processing  predefined procedures. Independent
          on  the  detailled  command  syntax  the  commandline processor allows
          defining  entry  points  at  the  beginning  of  a  command  line  as 
          ':ep_name".  You  may  also  define  block  separators  (e.g. "do" and
          "end")  that  define  a  subordinated  block  of  command  lines.  The
          ReadCommands()  function supports  reading command  lines for a block,
          the  LoadProcedure() function supports  reading a procedure containing
          a number of statements as block, which can be executed repeativly.
          The  command line can be initialized by using the Initialize() command
          or by getting the command from a command line inpit (InputCommand()):
          A  command  may  have  a  list  ob sub-commands (typically for command
          blocks).  Sub-commands are administrated by  a command list, which you
          can create, iterate or clear. 
          Moreover,  a  command  may  define  a  number  of  entry  points  in 
          sub-ordinated  command lists. An  entry point is  a unique name on the
          command  level,  that  refers  to  a  command in a command list. Entry
          points  can be located by GetEntryPoint on the command line level in a
          list of sub-commands or recursively.

\date     $Date: 2006/08/28 21:25:14,06 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CommandLine"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <cCommandTypes.h>
#include  <sCLEntryPoint.hpp>
#include  <sCommandLine.hpp>
#include  <sNString.hpp>
#include  <sCommandLine.hpp>


/******************************************************************************/
/**
\brief  AddCommand - 



\return term - Success

\param  cmd_line - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddCommand"

logical CommandLine :: AddCommand (CommandLine *cmd_line )
{
  logical                 term = NO;
  if ( !cmd_list )
    cmd_list = new DLL(CommandLine)();

  cmd_list->AddTail(cmd_line);

  return(term);
}

/******************************************************************************/
/**
\brief  AddEntryPoint - 



\return term - Success

\param  names - Name
\param  pos_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEntryPoint"

logical CommandLine :: AddEntryPoint (char *names, uint16 pos_w )
{
  logical                 term = NO;
  if ( !cmd_list )
    cmd_list = new DLL(CommandLine)();
  
  if ( !entry_points )
    entry_points = new GSRT(CLEntryPoint)(5,sizeof(CLEntryPoint),64,1,'C',YES);
  if ( pos_w == USHORTMAX )
    pos_w = cmd_list->GetCount();
  
  CLEntryPoint  clep(names,cmd_list,pos_w);

  entry_points->AddEntry(&clep);
  return(term);
}

/******************************************************************************/
/**
\brief  ClearCMDList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearCMDList"

void CommandLine :: ClearCMDList ( )
{
  CommandLine       *cmd_line;
  if ( cmd_list )
    while ( cmd_line = cmd_list->RemoveTail() )
      delete cmd_line;



}

/******************************************************************************/
/**
\brief  ClearOutput - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearOutput"

void CommandLine :: ClearOutput ( )
{

  SystemOutput("",YES,YES);


}

/******************************************************************************/
/**
\brief  CloseFile - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseFile"

void CommandLine :: CloseFile ( )
{

  if ( file_handle && owns_file_handle )
    fclose(file_handle);
  file_handle = NULL;


}

/******************************************************************************/
/**
\brief  CommandLine - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  cmdstr - Command line string
\param  cmd_separatot - Parameter separator
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CommandLine"

     CommandLine :: CommandLine (char *cmdstr, char cmd_separatot )
                     : vcls (),
  command(NULL),
  file_handle(NULL),
  cmd_name(NULL),
  cmd_list(NULL),
  entry_points(NULL),
  echo(NO),
  owns_file_handle(NO),
  type(CLT_undefined),
  top_cmdline(NULL),
  condition(NULL),
  size(0),
  output(NULL),
  output_file(NULL),
  permanent_redirection(NO)
{
  int32        i = 0;
  int32        j = 0;
  Initialize(cmdstr);
  top_cmdline = this;

}

/******************************************************************************/
/**
\brief  i01 - 



\param  cmd_line_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CommandLine"

     CommandLine :: CommandLine (CommandLine &cmd_line_ref )
                     : vcls (),
  command(NULL),
  file_handle(NULL),
  cmd_name(NULL),
  cmd_list(cmd_line_ref.get_cmd_list()),
  entry_points(cmd_line_ref.get_entry_points()),
  echo(cmd_line_ref.get_echo()),
  owns_file_handle(NO),
  top_cmdline(cmd_line_ref.get_top_cmdline()),
  type(cmd_line_ref.get_type()),
  condition(NULL),
  size(0),
  output(NULL),
  output_file(cmd_line_ref.get_output_file()),
permanent_redirection(cmd_line_ref.get_permanent_redirection())
{

  SetCommand(cmd_line_ref.GetCommand());


}

/******************************************************************************/
/**
\brief  i02 - 



\param  filehandle - 
\param  echo_opt - 
\param  topcmd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CommandLine"

     CommandLine :: CommandLine (FILE *filehandle, logical echo_opt, CommandLine *topcmd )
                     : vcls (),
  command(NULL),
  file_handle(filehandle),
  cmd_name(NULL),
  cmd_list(NULL),
  entry_points(NULL),
  echo(echo_opt),
  owns_file_handle(NO),
  top_cmdline(topcmd),
  type(CLT_undefined),
  condition(NULL),
  size(0),
  output(NULL),
  output_file(NULL),
  permanent_redirection(NO)
{

  Initialize(NULL);
//  type_function.SetInstance(this);

}

/******************************************************************************/
/**
\brief  Copy - Copy command line

        The  function copies an  unparsed command line.  Since the function does
        not  copy  parameter  and  option  lists,  copying a parsed command line
        results in copying the command without parameters.

\return term - Success

\param  cmd_line - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical CommandLine :: Copy (CommandLine *cmd_line )
{
  int32                   i    = 0;
  logical                 term = NO;
  ResetCommand();
  
  while ( parm_list[i] )
    parm_list[i++] = NULL;
  
  file_handle           = NULL;
  cmd_name              = NULL;
  cmd_list              = NULL;
  entry_points          = NULL;
  echo                  = NO;
  top_cmdline           = cmd_line->get_top_cmdline();
  condition             = NULL;
  type                  = cmd_line->get_type();
  
  if ( cmd_line->get_cmd_name() )
    cmd_name = strdup(cmd_line->get_cmd_name());
    
  SetCommand(cmd_line->get_command());
//  type_function.SetInstance(this);
  return(term);
}

/******************************************************************************/
/**
\brief  FlushOutput - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushOutput"

void CommandLine :: FlushOutput ( )
{

  SystemOutput("",NO,YES);


}

/******************************************************************************/
/**
\brief  GetCMDList - 



\return cmd_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCMDList"

DLL(CommandLine) *CommandLine :: GetCMDList ( )
{


  return(cmd_list);
}

/******************************************************************************/
/**
\brief  GetCommand - 



\return command - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCommand"

char *CommandLine :: GetCommand ( )
{

  if ( !cmd_name )
    GetCommandName();
    
  return( cmd_name && *cmd_name ? cmd_name : NULL);

}

/******************************************************************************/
/**
\brief  GetCommandName - 



\return cmdname - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCommandName"

char *CommandLine :: GetCommandName ( )
{
  int            i = 0;
  char           cmdname[129];
  char          *pos = command;
BEGINSEQ
  if ( cmd_name )
    free(cmd_name);
  cmd_name = NULL;
    
  if ( !pos )                                        ERROR
  
  while ( *pos && (*pos == ' ' || *pos == '\t') )
    pos++;
  
  while ( i < 64 && pos[i] && pos[i] != ' ' && pos[i] != '\t' )
  {
    cmdname[i] = pos[i];
    i++;
  }
  cmdname[i] = 0;
  
  cmd_name = strdup(cmdname);

RECOVER
  cmd_name = NULL;
ENDSEQ
  return(cmd_name);
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

CommandTypes CommandLine :: GetCommandType (CommandLine *cmd_line )
{
  char          *cmd;
BEGINSEQ
  type = CLT_command;
  if ( !(cmd = cmd_line->GetCommandName()) )       ERROR
  
  if ( *cmd == '\'' )                         // comment
    type = CLT_comment;
  else if ( !strcmp(cmd,"do") )               // begin
    type = CLT_begin;
  else if ( !strcmp(cmd,"end") )              // terminate
    type = CLT_end;
  else if ( *cmd == '@' )                     // entry point
    type = CLT_entrypoint;

RECOVER
  type = CLT_undefined;
ENDSEQ
  return(type);
}

/******************************************************************************/
/**
\brief  GetEntryPoint - 



\return cmdlist - 

\param  names - Name
\param  posptr - 
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryPoint"

DLL(CommandLine) *CommandLine :: GetEntryPoint (char *names, uint16 *posptr, logical recursive )
{
  char                 name[64];
  CommandLine         *cmdline;
  CLEntryPoint        *clep;
  DLL(CommandLine)    *cmdlist;
BEGINSEQ
  if ( !entry_points )                               ERROR
  gvtxstb(name,names,sizeof(name));
  *posptr = USHORTMAX;

  if ( clep = entry_points->GetEntry(name) )
  {
    *posptr = clep->get_cmd_pos();
    cmdlist = clep->get_cmd_list();
  }
  else if ( recursive )
  {
    DLL(CommandLine) cursor(*cmd_list);
    cursor.GoTop();
    while ( cmdline = cursor.GetNext() )
      if ( cmdlist = cmdline->GetEntryPoint(names,posptr,recursive) )
        break;
  }
RECOVER
  cmdlist = NULL;
ENDSEQ
  return(cmdlist);
}

/******************************************************************************/
/**
\brief  GetMLCommand - 



\return cmdstring - 

\param  prompt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMLCommand"

char *CommandLine :: GetMLCommand (char *prompt )
{
  static  NString   nstring(4000);
  nstring = "";
  CommandLine  cmdline(file_handle,echo,top_cmdline);
  while ( cmdline.InputCommand(prompt) )
  {
    if ( cmdline.GetCommandType(this) == CLT_end ) 
      break;
    nstring += command;
    nstring += ' ';
  }



  return(nstring);
}

/******************************************************************************/
/**
\brief  GetOption - 



\return option - 

\param  opt_id - Option-ID
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOption"

char *CommandLine :: GetOption (char opt_id )
{
  int         i = 0;
  char       *option = NULL;
BEGINSEQ
  while ( i < OPT_COUNT && (option = options[i++]) )
    if ( *option == opt_id )  
    {
      option++;                       
      LEAVESEQ
    }
ENDSEQ
  return(option);
}

/******************************************************************************/
/**
\brief  InitOutput - 



\return term - Success

\param  w_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOutput"

logical CommandLine :: InitOutput (char *w_path )
{
  logical                 term = NO;
  ResetOutput();
  
  if ( w_path )
  {
    if ( output_file )
      free(output_file);
    output_file = strdup(w_path);
    permanent_redirection = YES;
  }
  
  if ( output_file && *output_file && *output_file != '*' )
    if ( !(output = fopen(output_file,"a")) )
      term = YES;
 
  if ( output_file )
    free(output_file);
  output_file = NULL;
  
  if ( !output )
    permanent_redirection = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - Initialize command line area

        The  function initializes the command line area with the command passed.
        After  initializing the command it will  be parsed when a command string
        has  been passed, which is nesecary  for being able returning parameters
        and options.


\param  cmdstr - Command line string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CommandLine :: Initialize (char *cmdstr )
{
  int32        i = 0;
  int32        j = 0;
  free(cmd_name);
  cmd_name = NULL;

  if ( cmdstr )
  {
    if ( command )
      free(command);
    command = strdup(cmdstr);
  }
  while ( i < PARM_COUNT )
    parm_list[i++] = NULL;
  while ( j < OPT_COUNT )
    options[j++] = NULL;

  type = CLT_undefined;
  if ( cmdstr && *cmdstr ) 
    ParseCommand();

//  type = (CommandTypes)type_function.Call(this);  
  type = (CommandTypes)top_cmdline->GetCommandType(this);


}

/******************************************************************************/
/**
\brief  InputCommand - 



\return command - 

\param  prompt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputCommand"

char *CommandLine :: InputCommand (char *prompt )
{

BEGINSEQ
  if ( file_handle )
    return(InputFromFile(NULL));
    
  if ( prompt )
    Output(prompt);
  
  if ( InputCommandLine() )                          ERROR
RECOVER
  if ( cmd_name ) 
    *cmd_name = 0;
ENDSEQ
  return( command && *command ? command : NULL );
}

/******************************************************************************/
/**
\brief  InputCommandLine - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputCommandLine"

logical CommandLine :: InputCommandLine ( )
{
  char        line[1025];
  char        cline[4097];
  logical     next = YES;
  char       *pos  = NULL;
  logical     term = NO;
BEGINSEQ
  line[0] = 0;
  ResetCommand();
    
  while ( next )
  {
    *cline = 0;
    while ( next )
    {  
      if ( !file_handle )
      {
        if ( !SystemInput(line) )                    ERROR
      }
      else
        if ( !fgets(line,sizeof(line)-1,file_handle) )
          break;
          
      if ( (pos = strchr(line,10)) || (pos = strchr(line,12)) )
        *pos = 0;
      if ( line[strlen(line)-1] == '\\' )
        line[strlen(line)-1] = 0;
      else
        next = NO;
      if ( strlen(cline) +strlen(line) >= sizeof(cline) )
                                                     ERROR
      strcat(cline,line);
    }
    
    SetCommand(cline);
    if ( echo )
      Output(" >%s\n",command);
      
    if ( next )
      next = NO;
    else
    {
      pos = cline;
      while ( *pos == ' ' || *pos == '\t' )
        pos++;
      if ( !*pos || *pos == '\'' )
        next = YES;             // empty line or comment
    }
  }
  
  Initialize(NULL);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InputFromArguments - 



\return command - 

\param  argc - 
\param  argv[] - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputFromArguments"

char *CommandLine :: InputFromArguments (int argc, char *argv[] )
{
  char     cline[4097];
  int      count = 0;
  logical  quotes = NO;
  ResetCommand();
  
  *cline = 0;
  while ( count < argc )
  {
    if ( (quotes = *argv[count] != '-' && *argv[count] != '/')  )
      strcat(cline,"\"");
    strcat(cline,argv[count]);
    if ( quotes )
      strcat(cline,"\"");
    strcat(cline," ");
    count++;
    SetCommand(cline);
  }
  Initialize(NULL);
  return( *command ? command : NULL );
}

/******************************************************************************/
/**
\brief  InputFromCommand - 



\return command - 

\param  cmd_line - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputFromCommand"

char *CommandLine :: InputFromCommand (CommandLine *cmd_line )
{
  char     cline[4097];
  int      count = 0;
  logical  quotes = NO;
BEGINSEQ
  ResetCommand();
  
  *cline = 0;
  if ( !cmd_line->GetCommand() )                     ERROR
  strcpy(cline,cmd_line->GetCommand());
  while ( cmd_line->Parm(count) )
  {
    strcat(cline," ");
    strcat(cline,cmd_line->Parm(count));
    count++;
  }
  
  count = 0;
  while ( cmd_line->Option(count) )
  {
    strcat(cline," -");
    strcat(cline,cmd_line->Option(count));
    count++;
  }

  SetCommand(cline);
  Initialize(NULL);
RECOVER
  *cmd_name = 0;
ENDSEQ
  return( *command ? command : NULL );
}

/******************************************************************************/
/**
\brief  InputFromFile - 



\return command - 

\param  file_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputFromFile"

char *CommandLine :: InputFromFile (char *file_name )
{

BEGINSEQ
  if ( file_name )
  {
    CloseFile();
    if ( (file_handle = fopen(file_name,"r")) == 0 ) ERROR
    owns_file_handle = YES;
  }

  if ( InputCommandLine() )                          ERROR

RECOVER
  *cmd_name = 0;
ENDSEQ
  return( *command ? command : NULL );
}

/******************************************************************************/
/**
\brief  LoadProcedure - 



\return term - Success

\param  file_name - 
\param  ep_name - Entry point name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadProcedure"

logical CommandLine :: LoadProcedure (char *file_name, char *ep_name )
{
  logical                 term = NO;
BEGINSEQ
  if ( file_name )
  {
    CloseFile();
    if ( (file_handle = fopen(file_name,"r")) == 0 ) ERROR
  }

  if ( ReadCommands(NULL) )                          ERROR
    
  if ( command )
    free(command);
  command = NULL;
  Initialize(NULL);
  if ( ep_name && *ep_name )
    AddEntryPoint(ep_name,0);
RECOVER
  term = YES;
ENDSEQ
  CloseFile();
  return(term);
}

/******************************************************************************/
/**
\brief  Option - 



\return parm_string - 

\param  parmno - Parameter position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Option"

char *CommandLine :: Option (int32 parmno )
{

  return ( parmno < 32 ? options[parmno] : NULL);

}

/******************************************************************************/
/**
\brief  Output - 



\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 



\param  fstring - 
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CommandLine :: Output (char *fstring, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{
  char                    string[4096];
  logical                 term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  if ( output )
    fprintf(output,fstring,parm1,parm2,parm3,parm4,parm5);
  else
  {
    sprintf(string,fstring,parm1,parm2,parm3,parm4,parm5);
    SystemOutput(string,NO,NO);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fstring - 
\param  intval - 
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CommandLine :: Output (char *fstring, int32 intval, char *parm1, char *parm2 )
{
  char                    string[4096];
  logical                 term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  if ( output )
    fprintf(output,fstring,intval,parm1,parm2);
  else
  {
    sprintf(string,fstring,intval,parm1,parm2);
    SystemOutput(string,NO,NO);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  fstring - 
\param  parm0 - 
\param  intval - 
\param  parm2 - Second message variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CommandLine :: Output (char *fstring, char *parm0, int32 intval, char *parm2 )
{
  char                    string[4096];
  logical                 term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  if ( output )
    fprintf(output,fstring,parm0,intval,parm2);
  else
  {
    sprintf(string,fstring,parm0,intval,parm2);
    SystemOutput(string,NO,NO);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  fstring - 
\param  intval - 
\param  intval2 - 
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CommandLine :: Output (char *fstring, int32 intval, int32 intval2, char *parm1, char *parm2 )
{
  char                    string[4096];
  logical                 term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  if ( output )
    fprintf(output,fstring,intval,intval2,parm1,parm2);
  else
  {
    sprintf(string,fstring,intval,intval2,parm1,parm2);
    SystemOutput(string,NO,NO);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Parm - Get parameter

        The function returns the value for the n-th parameter.

\return parm_string - 

\param  parmno - Parameter position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parm"

char *CommandLine :: Parm (int32 parmno )
{

  return ( parmno < 32 ? parm_list[parmno] : NULL);

}

/******************************************************************************/
/**
\brief  ParseCommand - 



\return command - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParseCommand"

char *CommandLine :: ParseCommand ( )
{
  int         i = 0;
  int         j = 0;
  logical     quotes = NO;
  logical     next = NO;
  char       *pos = NULL;
BEGINSEQ
  if ( *command == '\'' || *command == '/')
    return(NULL);       // comment
  
  if ( !cmd_name )
    if ( !GetCommandName() )                         ERROR
    
  pos = command;
    
  while ( *pos == ' ' || *pos == '\t' )
    pos++;
    
  if ( !*command )
    return(NULL);       // empty line
  
  while ( *pos++ )  
    if ( *(pos-1) == ' ' )
    {
      *(pos-1) = 0;
      next = YES;
      break;
    }
  while ( *pos == ' ' )
    pos++;
  
  if ( next ) 
  {    
    while ( *pos )
    {
      if ( *pos == ' ' )
      {
        *pos = 0;
        next = YES;
      }
      else if ( next )
      {
        if ( *pos == '-' )
          options[j++] = pos+1;
        else if ( !memcmp(pos,">>",2) )
        {
          if ( output_file )
            free(output_file);
          output_file = strdup(pos+2);
          *pos = 0;
          pos = pos+strlen(pos);
          permanent_redirection = NO;
        }
        else
        {
          if ( *pos == '"' )
          {
            quotes = YES;
            pos++;
          }
          parm_list[i++] = pos;
          if ( quotes )
          {
            while ( *pos && *pos != '"' )
              pos++;
            if ( *pos == '"' )
              *pos = ' ';
            pos--;
            quotes = NO;
          }
        }
        next = NO;
      }
      pos++;
    }
  }
  while ( i < PARM_COUNT )
    parm_list[i++] = NULL;
  while ( j < OPT_COUNT )
    options[j++] = NULL;
RECOVER

ENDSEQ
  return(cmd_name);
}

/******************************************************************************/
/**
\brief  ReadCommands - 



\return term - Success

\param  prompt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadCommands"

logical CommandLine :: ReadCommands (char *prompt )
{
  CommandLine            *cmdline = NULL;
  CommandTypes            cmdtype = CLT_undefined;
  logical                 term = NO;
BEGINSEQ
  ClearCMDList();
  cmdline = new CommandLine(file_handle,echo,top_cmdline);
  while ( cmdline->InputCommand(prompt) )
  {
    switch ( cmdline->get_type() )
    {
      case CLT_comment    : break;
      case CLT_entrypoint : AddEntryPoint(cmdline->get_command()+1);
                            break;
      case CLT_begin      : cmdline->ReadCommands(prompt);
      case CLT_function   :
      case CLT_command    : AddCommand(cmdline);
                            cmdline = new CommandLine(file_handle,echo,top_cmdline);
                            break;
      case CLT_end        : LEAVESEQ
      case CLT_undefined  : Output(" ERROR - undefined command '%s'\n",cmd_name);
                            ERROR
    }
  }

RECOVER
  term = YES;
ENDSEQ
  if ( cmdline )
    delete cmdline;
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceParameters - 



\return term - Success

\param  plist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceParameters"

logical CommandLine :: ReplaceParameters (char **plist )
{
  char                    pst[3];
  char                   *parmstr;
  int                     i = 0;
  logical                 term = NO;
  strcpy(pst,"%0");
  while ( i < 9 && (parmstr = plist[i++]) )
  {
    pst[1]++;
    while ( size-1 - strlen(command) < strlen(parmstr) )
      ResizeCommand(NO);
    STRExchange(command,pst,parmstr,size);
  }


  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceSysVariables - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSysVariables"

logical CommandLine :: ReplaceSysVariables ( )
{
  logical                 term = NO;
  ResizeCommand();
  ReplaceSysVariable(command,size);
  return(term);
}

/******************************************************************************/
/**
\brief  ResetCommand - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCommand"

void CommandLine :: ResetCommand ( )
{

  if ( command )
    free(command);
  command = NULL;
  
  if ( cmd_name )
    free(cmd_name);
  cmd_name = NULL;

  if ( !permanent_redirection )
  {
    if ( output_file )
      free(output_file);
    output_file = NULL;
  
    ResetOutput();
  }

}

/******************************************************************************/
/**
\brief  ResetOutput - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetOutput"

logical CommandLine :: ResetOutput ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !output )                                     LEAVESEQ

  fclose(output);
  output = NULL;

  permanent_redirection = NO;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResizeCommand - 



\return term - Success

\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResizeCommand"

logical CommandLine :: ResizeCommand (logical chkopt )
{
  char                   *oldcmd;
  int                     len;
  logical                 term = NO;
  if ( !chkopt || (len = strlen(command)) > size-512 )
  {
    oldcmd = command;
    command = (char *)malloc(size=size+512);
    strcpy(command,oldcmd);
    free(oldcmd);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetCommand - 




\param  cmdstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCommand"

void CommandLine :: SetCommand (char *cmdstring )
{

  if ( command )
    free(command);
  command = strdup(cmdstring);
  size = strlen(command);

  if ( !cmd_name )
    GetCommandName();

}

/******************************************************************************/
/**
\brief  SetCondition - 




\param  cond_expr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCondition"

void CommandLine :: SetCondition (void *cond_expr )
{

  condition = cond_expr;

}

/******************************************************************************/
/**
\brief  SetEcho - 




\param  echo_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetEcho"

void CommandLine :: SetEcho (logical echo_opt )
{

  echo = echo_opt;

}

/******************************************************************************/
/**
\brief  SetParm - Set parameter value

        The function allows changing the parameter value for a parsed command.


\param  parmno - Parameter position
\param  parmval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParm"

void CommandLine :: SetParm (int32 parmno, char *parmval )
{

  if ( parmno < 32 )
    parm_list[parmno] = parmval;

}

/******************************************************************************/
/**
\brief  SetType - 




\param  cmdtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

void CommandLine :: SetType (CommandTypes cmdtype )
{

  type = cmdtype;

}

/******************************************************************************/
/**
\brief  SetupSubCommand - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSubCommand"

logical CommandLine :: SetupSubCommand ( )
{
  int                     i = 0;
  logical                 term = NO;
  if ( cmd_name )
    free(cmd_name);
  cmd_name = NULL;
  
  if ( parm_list[0] )
    cmd_name = strdup(parm_list[0]);
  else
    cmd_name = strdup("");
    
  while ( parm_list[i++] )
    parm_list[i-1] = parm_list[i];

  return(term);
}

/******************************************************************************/
/**
\brief  ~CommandLine - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CommandLine"

     CommandLine :: ~CommandLine ( )
{
  CommandLine       *cmd_line;
  ClearCMDList();  
  delete cmd_list;
  cmd_list = NULL;
  
  delete entry_points;
  entry_points = NULL;
  
  CloseFile();

  permanent_redirection = NO;
  ResetCommand();

}


