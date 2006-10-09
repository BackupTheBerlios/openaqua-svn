/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    DLInterpreter

\brief    Interpreter for OSICommandline Debugger
          Inherits  CLInterpreter and implements all  commands that are used for
          debugging  OQL Scripts. 
          Where it was possible the commands are named like in GDB
          naming convention ist UPPERCASE some commands get shortcuts 
          the  commands  can  get  called  with GetOpition('h')==true. then they
          should display a brief message. (?? why not dsc_topic?)
          // changes to get more gdb compatible
          go->c

          stepin->step
          dsi->s->step

          stepover->next
          dso->n->next

          stepout->until
          dsx->u->until

          listcallstack->backtrace
          dcs->bt->backtrace

 
          dle ->l

\date     $Date: 2006/03/12 19:19:51,79 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DLInterpreter_HPP
#define   DLInterpreter_HPP

class     DLInterpreter;

class     DLInterpreter;
class     OPBase;
class     OPDecl;
#include  <cDebugModi.h>
#include  <cExecReturnCodes.h>
#include  <sCLInterpreter.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  DLInterpreter :public CLInterpreter
{
protected  :         DebugModi                                    mode ATTR_ALIGN(4);                                        //
protected  :         OPBase                                      *current_node;                                              //
protected  :         OPDecl                                      *expression;                                                //
protected  :         logical                                      run_option;                                                //

public     :
                     DebugModi                                    get_mode() { return(mode); }
                     OPBase                                      *get_current_node() { return(current_node); }
                     logical                                      get_run_option() { return(run_option); }
public     :                                     logical BACKTRACE ( );
public     :                                     logical BREAKALWAYS ( );
public     :                                     logical BT ( );
public     :                                     logical C ( );
public     :                                     logical CD ( );
public     :                                     logical CONTINUE ( );
public     :                                     logical DBA ( );
public     :                                     logical DJO ( );
public     :                                     logical DLC ( );
public     :                                                             DLInterpreter (ODABAClient &odaba_client );
public     :                                                             DLInterpreter (DLInterpreter *dlip );
public     :                                     logical DRB ( );
public     :                                     logical DSB ( );
public     :                                     ExecReturnCodes Debug (OPBase *op_node );
public     :                                     logical EXIT ( );
public     :                                     logical ExecuteCommands ( );
public     :                                     logical ExecuteCommands (OPBase *op_node );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                     PropertyHandle GetPropertyHandle (char *prop_path, logical copy_opt=YES );
public     :                                     logical JUMPOVER ( );
public     :                                     logical L ( );
public     :                                     logical LAV ( );
public     :                                     logical LISTCURRENTLINE ( );
public     :                                     logical LISTEXPRESSION ( );
public     :                                     logical N ( );
public     :                                     logical NEXT ( );
public     :                                     logical NotSupported ( );
public     :                                     logical O ( );
public     :                                     logical Q ( );
public     :                                     logical QUIT ( );
public     :                                     logical RESETBREAK ( );
public     :                                     logical RUN ( );
public     :                                     logical S ( );
public     :                                     logical SAV ( );
public     :                                     logical SETBREAK ( );
public     :                                     logical STEP ( );
public     :                                     logical STEPOUT ( );
public     :                                     void SetBreakPoint (logical bp_opt );
public     :                                     void SetBreakPoint (char *name );
public     :                                     void SetMode (DebugModi debug_mode );
public     :                                     logical SetPreviousExpression (OPBase *op_node );
public     :                                     logical SetValue (char *prop_path );
public     :                                     logical ShowCurrentLine ( );
public     :                                     logical ShowExpression ( );
public     :                                     logical UpdateDatasource ( );
public     : virtual                                                     ~DLInterpreter ( );
};

#pragma pack()
#endif
