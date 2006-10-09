/********************************* Class Source Code ***************************/
/**
\package  OQL - 
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

\date     $Date: 2006/08/27 20:02:54,32 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DLInterpreter"

#include  <poql.h>
#include  <dlincl.h>
#include  <sDLInterpreter.hpp>
#include  <sOPBase.hpp>
#include  <sOPDecl.hpp>
#include  <sPropertyHandle.hpp>
#include  <scfte.hpp>
#include  <sDLInterpreter.hpp>


/******************************************************************************/
/**
\brief  BACKTRACE - List Call Stack

        The command will list the calling sequence until the cur-rent position.

        (gdb) help backtrace
        Print backtrace of all stack frames, or innermost COUNT frames.
        With a negative argument, print outermost -COUNT frames.
        Use  of  the  'full'  qualifier  also  prints  the  values  of the local
        variables.

        step-in command.
        (gdb) help step
        Step program until it reaches a different source line.
        Argument  N  means  do  this  N times (or till program stops for another
        reason).
        ell command. 
        When  a  breakpoint  procedure  has  already  been set, the command will
        deactivate  the current breakpoint  procedure and replace  it by the new
        one.  When  not  passing  a  procedure  name,  the  current  breakpoint 
        procedure will be reset.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BACKTRACE"

logical DLInterpreter :: BACKTRACE ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    current_node->ListCallStack(Parm(0) ? atoi(Parm(0)) : AUTO);
  else
  {
//                                 :   
    Output("list call stack        : backtrace|bt [count] \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command displays the current call stack beginning with the last called\n");
    Output("  expression.\n");
    Output("  Print backtrace of all stack frames, or innermost COUNT frames.\n");
    Output("  !!With a negative argument, print outermost -COUNT frames.\n");
    Output("  !!Use of the 'full' qualifier also prints the values of the local variables.\n");
    Output("  \n");

//                        -
    Output("  count       - maximum stack level to be displayed\n");
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BREAKALWAYS - Break at each statement

        The  break-always command causes the debugger to stop at each statement,
        also  when choosing  'continue' as  next run command. Thus, break-always
        is similar to the step-in command. 
        The  break-always command can be reset by using the run commands StepIn,
        StepOver, StepOut or JumpOver.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BREAKALWAYS"

logical DLInterpreter :: BREAKALWAYS ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    mode = DM_always;      // break at each statement
    run_option = YES;
  }
  else
  {
//                                 :   
    Output("stop at each statement : BreakAlways|dba \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  This is a run command, which causes the debugger to stop at each statement.\n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BT - alias for BACKTRACE



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BT"

logical DLInterpreter :: BT ( )
{

  return(BACKTRACE());

}

/******************************************************************************/
/**
\brief  C - alias for Continue



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "C"

logical DLInterpreter :: C ( )
{

  // was GO
  return(CONTINUE());

}

/******************************************************************************/
/**
\brief  CD - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CD"

logical DLInterpreter :: CD ( )
{

  return(NotSupported());

}

/******************************************************************************/
/**
\brief  CONTINUE - Continue execution until next break point

        The  continue command executes the expression(s) until reaching the next
        breakpoint.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CONTINUE"

logical DLInterpreter :: CONTINUE ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    run_option = YES;
  else
  {
//                                 :   
    Output("continue application   : continue|c \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  This is a run command, which causes the debugger to run the application \n");
    Output("  until the next break point.\n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBA - Break at each statement

        The  break-always command causes the debugger to stop at each statement,
        also  when choosing  'continue' as  next run command. Thus, break-always
        is similar to the step-in command. 
        The  break-always command can be reset by using the run commands StepIn,
        StepOver, StepOut or JumpOver.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBA"

logical DLInterpreter :: DBA ( )
{

  return(BREAKALWAYS());

}

/******************************************************************************/
/**
\brief  DJO - Skip statement

        The  jump-over command  will skip  the execution  of the next statement.
        Depending  on the breakpoint  setting for block  statements it will skip
        the  whole block, when the breakpoint reached is at the beginning of the
        block  (e.g.  before  the  WHILE  keyword)  or just a block statement or
        operand, when the current breakpoint is within the block statement.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DJO"

logical DLInterpreter :: DJO ( )
{

  return(JUMPOVER());

}

/******************************************************************************/
/**
\brief  DLC - List current expression line

        The  command  will  list  the  current statement as being displayed when
        entering the debug prompt.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLC"

logical DLInterpreter :: DLC ( )
{

  return(LISTCURRENTLINE());

}

/******************************************************************************/
/**
\brief  DLInterpreter - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  odaba_client - ODABA Client Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLInterpreter"

     DLInterpreter :: DLInterpreter (ODABAClient &odaba_client )
                     : CLInterpreter (odaba_client),
  mode(DM_first_statement),
  current_node(NULL),
  expression(NULL),
  run_option(NO)
{

  cmd = this;
  SetEcho(NO);


}

/******************************************************************************/
/**
\brief  i01 - 



\param  dlip - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLInterpreter"

     DLInterpreter :: DLInterpreter (DLInterpreter *dlip )
                     : CLInterpreter(dlip),
  mode(dlip->get_mode()),
  current_node(NULL),
  expression(NULL),
  run_option(NO)
{

  mode = dlip->get_mode();

}

/******************************************************************************/
/**
\brief  DRB - Reset break point at current position

        The  reset-break command will reset the  breakpoint at the current line.
        At  debug time, you cannot reset  break-point at other positions then at
        the current one.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DRB"

logical DLInterpreter :: DRB ( )
{

  return(RESETBREAK());

}

/******************************************************************************/
/**
\brief  DSB - Set break point at current position

        The  set-break  command  allows  setting  a  breakpoint  at  the current
        position.  At debug time,  you cannot set  breakpoint at other positions
        then at the current one.
        The  command  allows  defining  a  procedure entry point for the current
        breakpoint  by passing an entry point name to the command. The procedure
        with  the entry-point is called, when the breakpoint is reached the next
        time.  When not yet being loaded, the procedure can be loaded explicitly
        by calling the "Load" OShell command. 
        When  a  breakpoint  procedure  has  already  been set, the command will
        deactivate  the current breakpoint  procedure and replace  it by the new
        one.  When  not  passing  a  procedure  name,  the  current  breakpoint 
        procedure will be reset.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DSB"

logical DLInterpreter :: DSB ( )
{

  return(SETBREAK());

}

/******************************************************************************/
/**
\brief  Debug - 



\return exec_rc - 

\param  op_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Debug"

ExecReturnCodes DLInterpreter :: Debug (OPBase *op_node )
{
  OPBase                   *last_node;
  logical                   debug = YES;
  ExecReturnCodes           rc = ERC_success;
BEGINSEQ
  switch ( mode )
  {
    case DM_terminate       : rc = ERC_terminate;
    case DM_undefined       : debug = NO;
                              break;
    case DM_step_over       : if ( expression == op_node->GetExpressionDecl() )
                              {
                                mode = DM_break_point;
                                break;
                              }
    case DM_break_point     : if ( !op_node->IsDebug() )
                                debug = NO;
                              break;
    case DM_jump_over       : 
    case DM_first_statement : 
    case DM_step_in         : mode = DM_break_point;
    case DM_always          : break;
  }

  if ( debug )
    if ( ExecuteCommands(op_node) )                    ERROR
    
  last_node = current_node;
  if ( mode == DM_jump_over )
    rc = ERC_success;
  else if ( mode == DM_terminate )
  {
    rc = ERC_terminate;
    mode = DM_step_in;
  }
  else
    rc = op_node->Execute();
  current_node = last_node;
  

RECOVER
  rc = ERC_terminate;
ENDSEQ
  return(rc);
}

/******************************************************************************/
/**
\brief  EXIT - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EXIT"

logical DLInterpreter :: EXIT ( )
{

  return(NotSupported());

}

/******************************************************************************/
/**
\brief  ExecuteCommands - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteCommands"

logical DLInterpreter :: ExecuteCommands ( )
{
  char                    procname[ID_SIZE+2];
  char                   *name;
  logical                 term = NO;
//  if ( echo )
  ShowCurrentLine();

  if ( name = current_node->GetAutoRun() )
  {
    memset(procname,0,sizeof(procname));
    procname[0] = '@';
    strncpy(procname+1,name,ID_SIZE);
    RunBatch(procname);
    top_cmdline = this;
  }
  
  run_option = NO;
  while ( GetConsoleCommand() )
    if ( *GetCommand() )
      if ( ExecuteCommand() || run_option )
        break;

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  op_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteCommands"

logical DLInterpreter :: ExecuteCommands (OPBase *op_node )
{
  logical                 term = NO;
BEGINSEQ
  current_node = op_node;
  UpdateDatasource();
  if ( ExecuteCommands() )                           ERROR

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

logical DLInterpreter :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("STEPOUT",ALINK(this,DLInterpreter,STEPOUT)),
                           cfte("STEP",ALINK(this,DLInterpreter,STEP)),
                           cfte("SETBREAK",ALINK(this,DLInterpreter,SETBREAK)),
                           cfte("SAV",ALINK(this,DLInterpreter,SAV)),
                           cfte("S",ALINK(this,DLInterpreter,S)),
                           cfte("RUN",ALINK(this,DLInterpreter,RUN)),
                           cfte("RESETBREAK",ALINK(this,DLInterpreter,RESETBREAK)),
                           cfte("QUIT",ALINK(this,DLInterpreter,QUIT)),
                           cfte("Q",ALINK(this,DLInterpreter,Q)),
                           cfte("O",ALINK(this,DLInterpreter,O)),
                           cfte("NEXT",ALINK(this,DLInterpreter,NEXT)),
                           cfte("N",ALINK(this,DLInterpreter,N)),
                           cfte("LISTEXPRESSION",ALINK(this,DLInterpreter,LISTEXPRESSION)),
                           cfte("LISTCURRENTLINE",ALINK(this,DLInterpreter,LISTCURRENTLINE)),
                           cfte("LAV",ALINK(this,DLInterpreter,LAV)),
                           cfte("L",ALINK(this,DLInterpreter,L)),
                           cfte("JUMPOVER",ALINK(this,DLInterpreter,JUMPOVER)),
                           cfte("EXIT",ALINK(this,DLInterpreter,EXIT)),
                           cfte("DSB",ALINK(this,DLInterpreter,DSB)),
                           cfte("DRB",ALINK(this,DLInterpreter,DRB)),
                           cfte("DLC",ALINK(this,DLInterpreter,DLC)),
                           cfte("DJO",ALINK(this,DLInterpreter,DJO)),
                           cfte("DBA",ALINK(this,DLInterpreter,DBA)),
                           cfte("CONTINUE",ALINK(this,DLInterpreter,CONTINUE)),
                           cfte("CD",ALINK(this,DLInterpreter,CD)),
                           cfte("C",ALINK(this,DLInterpreter,C)),
                           cfte("BT",ALINK(this,DLInterpreter,BT)),
                           cfte("BREAKALWAYS",ALINK(this,DLInterpreter,BREAKALWAYS)),
                           cfte("BACKTRACE",ALINK(this,DLInterpreter,BACKTRACE)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    cfteptr->LINKINST(this);
    term = cfteptr->ActionCall();
  }
  else
    term = CLInterpreter::ExecuteFunction(fname,chk_opt);

ENDSEQ
  return(term);
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

PropertyHandle DLInterpreter :: GetPropertyHandle (char *prop_path, logical copy_opt )
{
  PropertyHandle                ph;
  PropertyHandle                prophdl;
  if ( prop_path )
    ph.CopyHandle(&current_node->GetPropertyHandle(prop_path));
  else
    ph.CopyHandle((PropertyHandle *)current_ds->GetCollection(AUTO));
  
  if ( copy_opt )  
    prophdl.CopyHandle(ph);
  else
    prophdl.CopyHandle(&ph);
    
  if ( !prophdl.IsValid() ) 
    Output("'%s' not found\n",prop_path);

  return(prophdl);
}

/******************************************************************************/
/**
\brief  JUMPOVER - Skip statement

        The  jump-over command  will skip  the execution  of the next statement.
        Depending  on the breakpoint  setting for block  statements it will skip
        the  whole block, when the breakpoint reached is at the beginning of the
        block  (e.g.  before  the  WHILE  keyword)  or just a block statement or
        operand, when the current breakpoint is within the block statement.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "JUMPOVER"

logical DLInterpreter :: JUMPOVER ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    mode = DM_jump_over;      // skip current statement
    run_option = YES;
  }
  else
  {
//                                 :   
    Output("do not execute         : JumpOver|djo \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  This is a run command, which causes the debugger to ignore the current \n");
    Output("  and continue with the next statement. This might be a statement in the current \n");
    Output("  expression or in the calling expression.\n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  L - alias for listexpression



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "L"

logical DLInterpreter :: L ( )
{

  // was DLE
  return(LISTEXPRESSION());

}

/******************************************************************************/
/**
\brief  LAV - List attribute values

        The  command displays the  attribute value for  a variable or object. In
        extension  to OShell, you  may display not  only object variables in the
        current  context,  but  also  pa-rameter  values  and  global  or  local
        variables defined in the expression.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LAV"

logical DLInterpreter :: LAV ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    DisplayAttribute(Parm(0));
  }
  else
  {
//                                 :   
    Output("List attribute values  : lav [varname|*] -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command shows the attribute value(s) for a property, parameter or local\n");
    Output("  or global variable. When an variable is complex, all attribute values for the\n");
    Output("  complex data type are displayed.\n");
    Output("  \n");
//                        -
    Output("  varname     - property path to be displayed\n");
    Output("  *           - display all attributes\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  lav first_name    : display 'first_name' value for selected instance\n"); 
    Output("  lav parm1.name    : display the name attribute of parameter parm1\n");
    Output("  \n");
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LISTCURRENTLINE - List current expression line

        The  command  will  list  the  current statement as being displayed when
        entering the debug prompt.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LISTCURRENTLINE"

logical DLInterpreter :: LISTCURRENTLINE ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    ShowCurrentLine();
  else
  {
//                                 :   
    Output("list current line      : ListCurrentLine|dlc \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command lists the line with the current statement.\n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LISTEXPRESSION - List expression

        The command will list the currently running expression.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LISTEXPRESSION"

logical DLInterpreter :: LISTEXPRESSION ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    ShowExpression();
  else
  {
//                                 :   
    Output("list current expression: ListExpression|l \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command lists the current expression \n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  N - alias for NEXT



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "N"

logical DLInterpreter :: N ( )
{
  logical                 term = NO;
  // was DLI
  return(NEXT());
  return(term);
}

/******************************************************************************/
/**
\brief  NEXT - Halt at next statement in current expression

        The  stepover  command  breaks  at  the  next  statement  in the current
        expression  or at the  next break point.  Since some statements may have
        different  breakpoints, the step-over command may break several times at
        the same line, when going through with the step-over command.


        (gdb) help next
        Step program, proceeding through subroutine calls.
        Like the "step" command as long as subroutine calls do not happen;
        when they do, the call is treated as one instruction.
        Argument  N  means  do  this  N times (or till program stops for another
        reason).

        will  deactivate the current breakpoint procedure  and replace it by the
        new  one.  When  not  passing  a  procedure name, the current breakpoint
        procedure will be reset.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NEXT"

logical DLInterpreter :: NEXT ( )
{
  logical                 term = NO;
BEGINSEQ
//next -- Step program
//was STEPOVER
  if ( !GetOption('h') )
  {
    mode = DM_step_over;      // stop at next statement in the current expression
    expression = current_node->GetExpressionDecl();
    run_option = YES;
  }
  else
  {
//                                 :   
    Output("go to next statement   : next|n \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    //Output("  This is a run command, which causes the debugger to stop at next statement in \n");
    //Output("  the current expression or at the next break point.\n");
    
    Output("  Step program, proceeding through subroutine calls.\n");
    Output("  Like the step command as long as subroutine calls do not happen;\n");
    Output("  when they do, the call is treated as one instruction.\n");
    Output("  this function is also called 'step over' in some environments");

    Output("  Argument N means do this N times (or till program stops for another reason).");
    Output("    not implemented!");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  NotSupported - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotSupported"

logical DLInterpreter :: NotSupported ( )
{

  if ( !GetOption('h') || GetOption('d') )
    Output("  The command is not supported in debug environment.\n");

  return(YES);
}

/******************************************************************************/
/**
\brief  O - Run to next line in calling function



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "O"

logical DLInterpreter :: O ( )
{

  return STEPOUT();

}

/******************************************************************************/
/**
\brief  Q - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Q"

logical DLInterpreter :: Q ( )
{

  return(QUIT());

}

/******************************************************************************/
/**
\brief  QUIT - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "QUIT"

logical DLInterpreter :: QUIT ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    mode = DM_terminate;      // stop at next statement
    run_option = YES;
  }
  else
  {
//                                 :   
    Output("terminate debugging    : Quit|q \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  This is a run command, which immediately terminates the application. When \n");
    Output("  running the debugger under OShell, it does not terminate the OShell, but the\n");
    Output("  debugger, only.\n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RESETBREAK - Reset break point at current position

        The  reset-break command will reset the  breakpoint at the current line.
        At  debug time, you cannot reset  break-point at other positions then at
        the current one.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RESETBREAK"

logical DLInterpreter :: RESETBREAK ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    SetBreakPoint(NO);      
  else
  {
//                                 :   
    Output("reset break point      : ResetBreak|drb \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command sets a break point at the current position.\n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RUN - Run without break

        The  run command will continue execution without stop-ping at breakpoint
        anymore.  The  debugger  will  still  break execution, when an error has
        been detected while exe-cuting.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RUN"

logical DLInterpreter :: RUN ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    mode = DM_undefined;      // don't stop at brak points
    run_option = YES;
  }
  else
  {
//                                 :   
    Output("run application        : run \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  This is a run command, which causes the debugger to run the application \n");
    Output("  whithout stopping at break points any more. The debugger will still stop in \n");
    Output("  case of errors.\n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  S - alias for STEP



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "S"

logical DLInterpreter :: S ( )
{

  // was dsi
  return(STEP());

}

/******************************************************************************/
/**
\brief  SAV - Modify attribute value

        The  command  allows  changing  the  attribute  value for a variable. In
        extension  to OShell,  you may  modify not  only object variables in the
        current  context,  but  also  parame-ter  values  and  global  or  local
        variables defined in the ex-pression.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SAV"

logical DLInterpreter :: SAV ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    SetValue(Parm(0));
  }
  else
  {
//                                 :   
    Output("Set attribute value    : sav attrname=value -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command assigns a new value to the attribute of the instance selected in\n");
    Output("  the current or referenced collection\n");
    Output("  \n");
//                        -
    Output("  attrname    - name of the attribute for assignment\n");
    Output("  value       - value to be assigned to the attribute. The valu is a constant,\n");
    Output("                a variable valid in the current environment or an expression.\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  sav name='Smith:  : change name value to 'Smith'\n"); 
    Output("  \n");
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SETBREAK - Set break point at current position

        The  set-break  command  allows  setting  a  breakpoint  at  the current
        position.  At debug time,  you cannot set  breakpoint at other positions
        then at the current one.
        The  command  allows  defining  a  procedure entry point for the current
        breakpoint  by passing an entry point name to the command. The procedure
        with  the entry-point is called, when the breakpoint is reached the next
        time.  When not yet being loaded, the procedure can be loaded explicitly
        by calling the "Load" OShell command. 
        When  a  breakpoint  procedure  has  already  been set, the command will
        deactivate  the current breakpoint  procedure and replace  it by the new
        one.  When  not  passing  a  procedure  name,  the  current  breakpoint 
        procedure will be reset.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SETBREAK"

logical DLInterpreter :: SETBREAK ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    if ( Parm(0) )
      SetBreakPoint(Parm(0));   
    else   
      SetBreakPoint(YES);   
  else
  {
//                                 :   
    Output("set break point        : SetBreak|dsb [proc_name]\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command sets a break point at the current position.\n");
    Output("  \n");
//                        -
    Output("  proc_name   - A procedure name containing a list of commands to be executed\n");
    Output("                when reaching the breakpoint. The Commandlist must be loaded \n");
    Output("                from the calling environment, e.g. the calling OShell.\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  dsb bp10          : set breakpont at current line and call procedure bp10 \n"); 
    Output("                      always when reaching the breakpoint.\n"); 
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  STEP - Go to next statement or operand

        The  step-in  command  breaks  in  the  first  statement  of  the called
        expression  or at the next statement, when the cur-rent statement is not
        an   expression   call.   Since   some   statements   may have different
        breakpoints,  the step-in  command may  break several  times at the same
        line, when going through with the step-in command.
        (gdb) help step
        Step program until it reaches a different source line.
        Argument  N  means  do  this  N times (or till program stops for another
        reason).
        ell command. 
        When  a  breakpoint  procedure  has  already  been set, the command will
        deactivate  the current breakpoint  procedure and replace  it by the new
        one.  When  not  passing  a  procedure  name,  the  current  breakpoint 
        procedure will be reset.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STEP"

logical DLInterpreter :: STEP ( )
{
  logical                 term = NO;
BEGINSEQ
  //step -- Step program until it reaches a different source line
  // was: STEPIN
  if ( !GetOption('h') )
  {
    mode = DM_step_in;      // stop at next statement
    run_option = YES;
  }
  else
  {
//                                 :   
    Output("go to next statement   : Step|s \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
//    Output("  This is a run command, which causes the debugger to stop at next statement \n");
//    Output("  executed. This might be a statement in a called expression, in the current \n");
//    Output("  expression or in the calling expression.\n");
    Output("  Step program until it reaches a different source line.\n");
    Output("  Argument N means do this N times (or till program stops for another reason).\n");
    Output("  this function is also called 'step into' in some environments");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  STEPOUT - Return to calling expression

        The  step-out  command  breaks  at  the  next  statement  in the calling
        expression or at the next break point.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STEPOUT"

logical DLInterpreter :: STEPOUT ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    mode = DM_step_over;      // stop at next statement in the calling expression
    expression = current_node->GetPreviousOPDecl();
    run_option = YES;
  }
  else
  {
//                                 :   
    Output("leave expression       : stepout|o \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  This is a run command, which causes the debugger to stop at next statement in \n");
    Output("  the calling expression or at the next break point.\n");
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetBreakPoint - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  bp_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBreakPoint"

void DLInterpreter :: SetBreakPoint (logical bp_opt )
{

  current_node->SetBreakPoint(bp_opt);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBreakPoint"

void DLInterpreter :: SetBreakPoint (char *name )
{

  current_node->SetBreakPoint(name);

}

/******************************************************************************/
/**
\brief  SetMode - 




\param  debug_mode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMode"

void DLInterpreter :: SetMode (DebugModi debug_mode )
{

  mode = debug_mode;

}

/******************************************************************************/
/**
\brief  SetPreviousExpression - 



\return term - 

\param  op_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPreviousExpression"

logical DLInterpreter :: SetPreviousExpression (OPBase *op_node )
{
  logical                 term = NO;
  if ( expression == op_node->GetExpressionDecl() )
    expression = op_node->GetPreviousOPDecl();
  return(term);
}

/******************************************************************************/
/**
\brief  SetValue - 



\return term - 

\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical DLInterpreter :: SetValue (char *prop_path )
{
  PropertyHandle          ph;
  char                   *value;
  logical                 term = NO;
BEGINSEQ
  if ( !prop_path || !*prop_path )                   ERROR

  if ( !(value = strchr(prop_path,'=')) )
  {
    Output("Error - Sytax error in statement\n");    ERROR
  }
  *value = 0;
  value++;
  
  if ( !(ph = GetPropertyHandle(prop_path)).IsValid() )   
                                                     ERROR
  CLInterpreterBase::SetValue(ph,prop_path,value);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ShowCurrentLine - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowCurrentLine"

logical DLInterpreter :: ShowCurrentLine ( )
{
  logical            term = NO;
  Output("%s%s\n",GetPrompt(),current_node->GetCurrentLine());

  return(term);
}

/******************************************************************************/
/**
\brief  ShowExpression - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowExpression"

logical DLInterpreter :: ShowExpression ( )
{
  logical                 term = NO;
  Output("\n%s\n",current_node->GetExpressionDecl()->GetExpression());
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateDatasource - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateDatasource"

logical DLInterpreter :: UpdateDatasource ( )
{
  CLIDataSource   *ds_context;
  logical                 term = NO;
// current_node->CO()

  if ( !current_ds && current_node->ResOBHandle() )
  {
    DBObjectHandle   dbo(current_node->ResOBHandle());
    if ( (ds_context = new CLIDataSource(this,client,dbo,"DEBUG",++last_id)) && ds_context->IsOpened() )
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

  if ( current_ds )
    current_ds->SetPropertyHandle(*current_node->CO());
  return(term);
}

/******************************************************************************/
/**
\brief  ~DLInterpreter - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DLInterpreter"

     DLInterpreter :: ~DLInterpreter ( )
{



}


