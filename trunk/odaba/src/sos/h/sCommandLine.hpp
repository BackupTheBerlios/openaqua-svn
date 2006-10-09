/********************************* Class Declaration ***************************/
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
          immediately  the  option  character  (e.g. -Fc:       emp     empfile). Option
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

\date     $Date: 2006/08/28 21:24:55,09 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CommandLine_HPP
#define   CommandLine_HPP

class     CommandLine;
#include "csosdll.h"

#define  OPT_COUNT                                 sizeof(options)/sizeof(options[0])
#define  PARM_COUNT                                sizeof(parm_list)/sizeof(parm_list[0])
class     CLEntryPoint;
#include  <cCommandTypes.h>
#include  <sCommandLine.hpp>
#include  <svcls.hpp>
#pragma pack(8)

class  CommandLine :public vcls
{
protected  :         char                                        *command;                                                   // 
protected  :         char                                        *options[32];                                               // 
protected  :         char                                        *parm_list[32];                                             // 
protected  :         FILE                                        *file_handle;                                               // 
protected  :         char                                        *cmd_name;                                                  // 
protected  :         DLL(CommandLine)                            *cmd_list;                                                  // 
protected  :         GSRT(CLEntryPoint)                          *entry_points;                                              // 
protected  :         logical                                      echo;                                                      // 
protected  :         logical                                      owns_file_handle;                                          // 
protected  :         CommandLine                                 *top_cmdline;                                               // 
protected  :         CommandTypes                                 type;                                                      // 
protected  :         void                                        *condition;                                                 // 
protected  :         int16                                        size;                                                      // 
protected  :         FILE                                        *output;                                                    // 
protected  :         char                                        *output_file;                                               // 
protected  :         logical                                      permanent_redirection;                                     // 

public     :
                     char                                        *get_command() { return(command); }
                     FILE                                        *get_file_handle() { return(file_handle); }
                     char                                        *get_cmd_name() { return(cmd_name); }
                     DLL(CommandLine)                            *get_cmd_list() { return(cmd_list); }
                     GSRT(CLEntryPoint)                          *get_entry_points() { return(entry_points); }
                     logical                                      get_echo() { return(echo); }
                     logical                                      get_owns_file_handle() { return(owns_file_handle); }
                     CommandLine                                 *get_top_cmdline() { return(top_cmdline); }
                     CommandTypes                                 get_type() { return(type); }
                     void                                        *get_condition() { return(condition); }
                     int16                                        get_size() { return(size); }
                     FILE                                        *get_output() { return(output); }
                     char                                        *get_output_file() { return(output_file); }
                     logical                                      get_permanent_redirection() { return(permanent_redirection); }
public     :                  SOSImpExp             logical AddCommand (CommandLine *cmd_line );
public     :                  SOSImpExp             logical AddEntryPoint (char *names, uint16 pos_w=AUTO );
public     :                  SOSImpExp             void ClearCMDList ( );
public     :                  SOSImpExp             void ClearOutput ( );
public     :                                        void CloseFile ( );
public     :                  SOSImpExp                  CommandLine (char *cmdstr, char cmd_separatot=' ' );
public     :                  SOSImpExp                  CommandLine (CommandLine &cmd_line_ref );
public     :                  SOSImpExp                  CommandLine (FILE *filehandle, logical echo_opt, CommandLine *topcmd );
public     :                  SOSImpExp             logical Copy (CommandLine *cmd_line );
public     :                  SOSImpExp             void FlushOutput ( );
public     :                  SOSImpExp             DLL(CommandLine) *GetCMDList ( );
public     :                  SOSImpExp             char *GetCommand ( );
public     :                  SOSImpExp             char *GetCommandName ( );
public     : virtual          SOSImpExp             CommandTypes GetCommandType (CommandLine *cmd_line );
public     :                  SOSImpExp             DLL(CommandLine) *GetEntryPoint (char *names, uint16 *posptr, logical recursive=YES );
public     :                  SOSImpExp             char *GetMLCommand (char *prompt );
public     :                  SOSImpExp             char *GetOption (char opt_id );
public     :                  SOSImpExp             logical InitOutput (char *w_path=NULL );
public     :                  SOSImpExp             void Initialize (char *cmdstr );
public     :                  SOSImpExp             char *InputCommand (char *prompt );
public     :                  SOSImpExp             logical InputCommandLine ( );
public     :                  SOSImpExp             char *InputFromArguments (int argc, char *argv[] );
public     :                                        char *InputFromCommand (CommandLine *cmd_line );
public     :                  SOSImpExp             char *InputFromFile (char *file_name );
public     :                  SOSImpExp             logical LoadProcedure (char *file_name, char *ep_name );
public     :                  SOSImpExp             char *Option (int32 parmno );
public     :                  SOSImpExp             logical Output (char *fstring, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                  SOSImpExp             logical Output (char *fstring, int32 intval, char *parm1=NULL, char *parm2=NULL );
public     :                  SOSImpExp             logical Output (char *fstring, char *parm0, int32 intval, char *parm2=NULL );
public     :                  SOSImpExp             logical Output (char *fstring, int32 intval, int32 intval2, char *parm1=NULL, char *parm2=NULL );
public     :                  SOSImpExp             char *Parm (int32 parmno );
public     :                  SOSImpExp             char *ParseCommand ( );
public     :                  SOSImpExp             logical ReadCommands (char *prompt );
public     :                  SOSImpExp             logical ReplaceParameters (char **plist );
public     :                  SOSImpExp             logical ReplaceSysVariables ( );
public     :                  SOSImpExp             void ResetCommand ( );
public     :                  SOSImpExp             logical ResetOutput ( );
public     :                                        logical ResizeCommand (logical chkopt=YES );
public     :                  SOSImpExp             void SetCommand (char *cmdstring );
public     :                  SOSImpExp             void SetCondition (void *cond_expr );
public     :                  SOSImpExp             void SetEcho (logical echo_opt );
public     :                  SOSImpExp             void SetParm (int32 parmno, char *parmval );
public     :                  SOSImpExp             void SetType (CommandTypes cmdtype );
public     :                  SOSImpExp             logical SetupSubCommand ( );
public     :                  SOSImpExp                  ~CommandLine ( );
};

#pragma pack()
#endif
