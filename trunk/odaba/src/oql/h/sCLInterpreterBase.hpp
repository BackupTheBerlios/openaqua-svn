/********************************* Class Declaration ***************************/
/**
\package  OQL - 
\class    CLInterpreterBase

\brief    


\date     $Date: 2006/08/28 14:30:02,93 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CLInterpreterBase_HPP
#define   CLInterpreterBase_HPP

class     CLInterpreterBase;

#include  <sDLL.h>
class     CommandLine;
#ifndef   DLL_CLIDataSource_HPP
#define   DLL_CLIDataSource_HPP
#include  <sCLIDataSource.hpp>
#include  <sDLL.h>
#endif
class     CLICollection;
class     CLIDataSource;
class     CLInterpreterBase;
class     PropertyHandle;
#include  <cCommandTypes.h>
#include  <sCommandLine.hpp>
#pragma pack(8)

class  CLInterpreterBase :public CommandLine
{
protected  :         CommandLine                                 *cmd;                                                       // 
protected  :         ODABAClient                                  client;                                                    // 
protected  :         DLL(CLIDataSource)                           cli_list;                                                  // 
protected  :         CLIDataSource                               *current_ds;                                                // 
protected  :         CLIDataSource                               *last_ds;                                                   // 
protected  :         int32                                        last_id;                                                   // 
protected  :         int32                                        count;                                                     // 
protected  :         logical                                      from_console;                                              // 
protected  :         CLInterpreterBase                           *child;                                                     // 
protected  :         CLInterpreterBase                           *parent;                                                    // 
protected  :         logical                                      input_mode;                                                // 
protected  :         char                                         proc_opt;                                                  // 
protected  :         CommandLine                                 *procedures;                                                // 
public     :         char                                        *parameters[32];                                            // 

public     :
                     CommandLine                                 *get_cmd() { return(cmd); }
                     ODABAClient                                 &get_client() { return(client); }
                     DLL(CLIDataSource)                          &get_cli_list() { return(cli_list); }
                     CLIDataSource                               *get_current_ds() { return(current_ds); }
                     CLIDataSource                               *get_last_ds() { return(last_ds); }
                     int32                                        get_last_id() { return(last_id); }
                     int32                                        get_count() { return(count); }
                     logical                                      get_from_console() { return(from_console); }
                     CLInterpreterBase                           *get_child() { return(child); }
                     CLInterpreterBase                           *get_parent() { return(parent); }
                     logical                                      get_input_mode() { return(input_mode); }
                     char                                         get_proc_opt() { return(proc_opt); }
                     CommandLine                                 *get_procedures() { return(procedures); }
public     :                  OQLImpExp                  CLInterpreterBase (ODABAClient &odaba_client );
public     :                  OQLImpExp                  CLInterpreterBase (CLInterpreterBase *clipbase );
public     :                                        logical ChangeDataSource (char *dsname );
public     :                                        logical CheckCondition (char *expression );
public     :                                        logical CheckDS (logical msg_opt );
public     :                                        void ClearCMDList ( );
public     :                                        logical Close ( );
public     :                                        logical Close (CLIDataSource *ds_context );
public     :                                        logical CommandLoop (char *command_file );
public     :                                        PropertyHandle CreatePropertyHandle (PropertyHandle &ph, char *prop_path, logical copy_opt=YES );
public     :                                        logical DisplayAttribute (PropertyHandle &ph, char *name );
public     :                                        logical DisplayAttribute (char *prop_path );
public     :                                        logical DisplayAttribute (char *name, PropertyHandle &ph );
public     :                  OQLImpExp             logical Execute (char *command_file );
public     :                  OQLImpExp             char ExecuteCommand ( );
public     :                  OQLImpExp             char ExecuteCommand (char *cmdline );
public     :                                        logical ExecuteCommandList (DLL(CommandLine) *cmdlist, uint16 pos );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical ExecuteListCommand ( );
public     :                                        logical ExecutePHFunction (PropertyHandle *co, char *fname, char chkopt=AUTO );
public     :                                        CLICollection *GetCollection ( );
public     :                                        char *GetCommandLine ( );
public     : virtual                                CommandTypes GetCommandType (CommandLine *cmd_line );
public     :                                        OperationHandle *GetCondition ( );
public     :                                        char *GetConsoleCommand ( );
public     :                  OQLImpExp             DLL(CommandLine) *GetEntryPoint (char *ep_name, uint16 *posptr, logical recursive );
public     :                                        char *GetOQLCommand (DLL(CommandLine) *cmdlist );
public     :                                        char *GetPrompt ( );
public     : virtual                                PropertyHandle GetPropertyHandle (char *prop_path, logical copy_opt=YES );
public     :                                        logical Help (char *cmdstring );
public     :                                        logical ListDataSource (char *display_opt );
public     :                                        logical LoadProcedure (char *file_name );
public     :                                        CLIDataSource *LocateDataSource (int32 ds_id );
public     :                                        CLInterpreterBase *Pop ( );
public     :                                        CLInterpreterBase *Push ( );
public     :                                        logical ReadCommands ( );
public     :                                        void RemoveCondition ( );
public     : virtual                                void ResetParameters ( );
public     :                                        logical RunBatch (char *file_name );
public     :                                        logical SetCondition (char *expression );
public     :                  OQLImpExp             logical SetDataCollection (PropertyHandle *ph_ptr );
public     : static           OQLImpExp             void __cdecl SetOShell (CLInterpreterBase *clip_base );
public     :                                        char *SetOption (char *optstring );
public     :                                        void SetParameters (uint16 parmno );
public     :                                        logical SetValue (PropertyHandle &ph, char *prop_path, char *value );
public     : virtual          OQLImpExp                  ~CLInterpreterBase ( );
};

#pragma pack()
#endif
