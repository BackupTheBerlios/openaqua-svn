/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    CLInterpreter

\brief    


\date     $Date: 2006/08/28 17:01:13,57 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CLInterpreter"

#include  <poql.h>
#include  <sCLInterpreter.hpp>
#include  <scfte.hpp>
#include  <sCLInterpreter.hpp>


/******************************************************************************/
/**
\brief  BEGIN - Begin of block

        The  'begin' command marks the begin of a block. In contrast to the 'do'
        command  the 'begin' command does not  save the current state, i.e. when
        returning  from  the  block  the  current state corresponds to the state
        after executing the last command in the block.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BEGIN"

logical CLInterpreter :: BEGIN ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( input_mode ) 
      ReadCommands();
    term = ExecuteCommandList(cmd->GetCMDList(),0);
  }
  else
  {
//                                 :   
    Output("Run command block      : begin\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command introduces a block of commands, which is terminated by an 'end'\n");
    Output("  command. Command lines must be entered completely before executing the block.\n");
    Output("  In contrast to 'do', commands in the begin block may change the current \n");
    Output("  collections and instance selections.\n");
    Output("  \n");
//                        -
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BEGINTRANSACTION - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BEGINTRANSACTION"

logical CLInterpreter :: BEGINTRANSACTION ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->BeginTransaction(GetOption('e') ? YES : NO,Parm(1));
  }
  else
  {
//                                 :   
    Output("Start transaction      : BeginTransaction [max_count] -e - Dn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function starts a transaction, which is opened until it is closed by \n");
    Output("  CommitTransaction or RolBack. \n");
    Output("  \n");
//                        -
    Output("  max_num     - maximal number of database entries to be stored in transaction\n");
    Output("                When this value is set the transaction is written to the \n");
    Output("                database when exceeding the maximum size.\n");
    Output("  -e          - long (external) transaction\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CALL - Call file with statements

        Syntax: call file_name
        The commands uses the commands from the file for further input.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CALL"

logical CLInterpreter :: CALL ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    SetParameters(1);
    RunBatch(Parm(0));
    ResetParameters();
  }
  else
  {
//                                 :   
    Output("Call procedure file    : call file_name[@entry_point]\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command runs commands from the file. Proc-files should not contain quit\n");
    Output("  statements (q), since this will terminate the application.\n");
    Output("  \n");
//                        -
    Output("  file_name   - complete path to the file containing the instructions\n");
    Output("  entry_point - when an entry point is appended to the file name the procedure\n");
    Output("                is not processed from the beginning but from the entry point,\n");
    Output("                which must be a defined entry point in the procedure.\n");
    Output("  \n");
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CC - Change collection

        Syntax: cc prop_path|coll_id|* -Dn  
        Change  collection  will  select  one  of  the  avaialble  extents  or 
        collections  (references) of the selected instance. It is not necessary,
        that  an instance is selected, i.e. you may change the selection without
        a selected instance.
        The  property path passed as parameter must be a valid property path for
        the  selected  property  handle  (i.e.  a  property  of  the  selected 
        structure).  When passing  a property  path beginning  with '/' (e.g. cc
        /Person)  the current property hierarchy is closed and the extent passed
        after  the /  will be  opened. When  passing one  or more dots ('.') the
        corresponding  number  of  parents  is closed before the passed property
        path  is  opened.  Each  cc  command  creates  one level in the property
        hierarchy, although, when passing a complex path.
        The  command can  be used  also to  copy a data source context including
        the  complete context  hierarchy. Passing  * instead  of a property path
        will copy the collection hierarchy into the new data source context. 
        Passing  a collection (coll_id) will  switch to the selected collection.
        Passing no parameters will display the curren hierarchy.
        The  -D  option  can  be  used  to  redirect the current location before
        changing  the  property  path.  In  this  case  the  is  changed  in the
        referenced data source context beginning with the last collection.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CC"

logical CLInterpreter :: CC ( )
{
  CLIDataSource          *ds_context;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    if ( Parm(0) )
    { 
      if ( *Parm(0) == '*' )
      {
        ds_context = current_ds;
        ChangeDataSource("*");  // current_ds neu gesetzt
        current_ds->CopyContext(ds_context);
      }
      else
        current_ds->ChangeCollection(Parm(0));
    }
    else
      current_ds->ListOpenColls();
  }
  else
  {
//                                 :   
    Output("Change collection      : cc prop_path|coll_id|*|& -Dn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows closing, opening or switching to an opened collection.\n");
    Output("  \n");
//                        -
    Output("  prop_path   - extent or reference name for the collection to be opened\n");
    Output("  *           - create a copy of the referenced collection and data source\n");
    Output("                context\n");
    Output("  &           - open the base collection for the selected property\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  -Cn         - re-direction to other collection th the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  cc Person         : Open the 'Person' collection in the current data source\n"); 
    Output("                      context\n");
    Output("  cc /Person        : Open the 'Person' collection in the current data source\n");
    Output("                      context after closing all opened collections\n");
    Output("  cc ..children     : Close the last two collections and open the collection\n");
    Output("                      'children'.\n");
    Output("  cc 2              : Switch to collection 2 in the current context'\n");
    Output("  cc * -D1          : creates a new data source context (copy) of data source 1\n");
    Output("                      and copies the collection hierarchy from data source 1'\n");
    Output("  cc                : Displays the current collection hierarchy and collection\n");
    Output("                      numbers (id).\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CD - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CD"

logical CLInterpreter :: CD ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(NO) )                             ERROR
    ChangeDataSource(Parm(0));
  }
  else
  {
//                                 :   
    Output("Change data sources    : cd [dsname|*|dsid|.] -Dn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows opening a data source or switching to another data source\n");
    Output("  context. Not passing any parameter will close the data source context.\n");
    Output("  \n");
//                        -
    Output("  dsname      - data source name as defined in the catalogue\n");
    Output("  dsid        - context identifier for opened data source\n");
    Output("  *           - create a copy of the current data source context\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  cd ProjectDB      : Open data source context for 'ProjectDB'\n");
    Output("  cd 2              : Switch to data source context 2'\n");
    Output("  cd * -D2          : Create a data source coppy from data source context 2\n");
    Output("  cd   -D3          : Close data source context 3.\n");
    Output("  cd .              : Close current data source and switch to previous.\n");
    Output("  cd                : Displays the currently opened data sources\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CLInterpreter - Konstruktor



-------------------------------------------------------------------------------
\brief  i0 - 



\param  odaba_client - ODABA Client Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLInterpreter"

     CLInterpreter :: CLInterpreter (ODABAClient &odaba_client )
                     : CLInterpreterBase(odaba_client)
{

  cmd = this;


}

/******************************************************************************/
/**
\brief  i01 - 



\param  clip - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLInterpreter"

     CLInterpreter :: CLInterpreter (CLInterpreter *clip )
                     : CLInterpreterBase(clip)
{



}

/******************************************************************************/
/**
\brief  CO - Change order

        Syntax: co index_name -Dn -Cn
        The  function will  change the  collection order  according to the index
        name  passed to  the commant.  When no  index or  key name is passed the
        order is reset to the default order for the collection.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CO"

logical CLInterpreter :: CO ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->ChangeOrder(Parm(0));
  }
  else
  {
//                                 :   
    Output("Change sort order      : co key_name -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows closing, opening or switching to an opened collection.\n");
    Output("  \n");
//                        -
    Output("  key_name    - key name for an index defined for the collection. When no key\n");
    Output("                name is passed the default order is set.\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  co sk_name        : set collection oder to key 'sk_name'\n"); 
    Output("  co                : reset default order\n"); 
    Output("  co * -D1          : set default order in current collection of data source \n");
    Output("                      context 1\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  COMMITTRANSACTION - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "COMMITTRANSACTION"

logical CLInterpreter :: COMMITTRANSACTION ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->CommitTransaction(GetOption('a') ? YES : NO);
  }
  else
  {
//                                 :   
    Output("Stop transaction       : CommitTransaction -a - Dn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function stops a transaction storing the results to the higher transaction\n");
    Output("  or database. \n");
    Output("  \n");
//                        -
    Output("  -a          - stop all transactions\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CPY - Copy instance or collection

        Syntax: cpy keyval|position|.|* [new_key] -Dn -Cn
        The  function copies the selected  instance to the referenced collection
        (-Dn,  -Cn). Copying an instance or collection to the current collection
        in  another data source  context is possible  by passing the data source
        id (-Dn). 
        When  not passing a dot '.' instead of a key value or a position number,
        the  instance  selected  in  the  referenced  or  current  collection is
        copied.  Otherwise  instances  according  to  the  key value are copied.
        Passing  * will  copy all  instance from  the current collection. When a
        selection is set, only selected instances are copied.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CPY"

logical CLInterpreter :: CPY ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->Copy(last_ds,Parm(0),Parm(1));
  }
  else
  {
//                                 :   
    Output("Copy instance          : cpy keyval|position|.|* [new_key] -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command copies a single instance or a collection of instances from the \n");
    Output("  current collection to the referenced collection. Copying an instance will \n");
    Output("  change the selections for all subsequent collections in the target hierarchy.\n");
    Output("  \n");
//                        -
    Output("  pos         - position of instance to be copied\n");
    Output("  .           - cpoy instance currently selected in the collection\n");
    Output("  key_value   - key value for the instance to be copied (ordered collection)\n");
    Output("  new_key     - copy and rename instance of an ordered collection (single\n");
    Output("                instance, only)\n");
    Output("  *           - copy all instances filtered in the current colletion (--> sfc)\n");
    Output("  -Dn         - target data source for copy. When no target is defined the \n");
    Output("                instance is copied to the current data source (with new key)\n");
    Output("  -Cn         - target collection for copy. When no target collection is defined\n");
    Output("                the instance is copied to the current collection in the\n");
    Output("                referenced data source (-Dn)\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  cpy Miller|Paul   : Copy person instance for Paul Millerto selected instance\n"); 
    Output("  cpy 0             : Copy first instance to selected instance\n");
    Output("  cpy . -D3 -C2     : Copy selected instance to collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CRT - Create instance

        Syntax: crt [[ds_id:]hier_id:][keyval]
        The  command  will  create  an  instance  in  the  referenced collection
        context.  The key  value must  be passed  according to the selected sort
        order.  When  the  collection  is  not ordered, a position can be passed
        instead  of a key value. When not passing any key value or position, the
        new  instance is inserted before the selected  instance or at the end of
        the  collection  when  no  instance  is  selected in the collection. For
        ordered collections an empty key is created in this case.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CRT"

logical CLInterpreter :: CRT ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->Create(Parm(0));
  }
  else
  {
//                                 :   
    Output("Create instance        : crt [keyval] -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command creates a new instance in the referenced collection. Creating an\n");
    Output("  instance will reset the selections for all subsequent collections in the\n");
    Output("  hierarchy.\n");
    Output("  \n");
//                        -
    Output("  key_value   - key value for the new instance when the collection is ordered\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  crt Miller|Paul   : Create an instzance for the person Paul Miller\n"); 
    Output("  crt               : Create an empty instance in the current collection\n");
    Output("  crt -D3 -c2       : Create an empty instance in collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DEL - Delete instance or collection

        Syntax: del keyval|pos|.|mask -Dn -Cn
        The  function  will  delete  one  or more an instances in the referenced
        collection.  You may delete a single instance by key or position (keyval
        or  pos), the  instance currently  selected in the referenced collection
        (.)  or all instances according to the  mask passed (e.g. a*). Passing a
        mask requires key access for the collection.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DEL"

logical CLInterpreter :: DEL ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->Delete(Parm(0),GetOption('E') ? YES : NO);
  }
  else
  {
//                                 :   
    Output("Delete instance        : del keyval|pos|.|* -Dn -Cn\n");
    Output("Delete instance        : del keyval|pos -E\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command deletes an instance in the referenced collection. Deleting an\n");
    Output("  instance will reset the selections for all subsequent collections in the\n");
    Output("  hierarchy.\n");
    Output("  \n");
//                        -
    Output("  key_value   - key value for the instance to be deleted (ordered collection)\n");
    Output("  pos         - position of instance to be deleted in the collection\n");
    Output("  .           - delete instance currently seölected in the collection\n");
    Output("  *           - delete all filtered instances in the collection (--> sfc)\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  -E          - Delete instances that cannot be read (usually by index)\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  del Miller|Paul   : delete person instance for Paul Miller\n"); 
    Output("  del 0             : delete first instance n collection\n");
    Output("  del . -D3 -c2     : delete selected instance in collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DELETEEXTENT - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DELETEEXTENT"

logical CLInterpreter :: DELETEEXTENT ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->DeleteExtent(Parm(0));
  }
  else
  {
//                                 :   
    Output("Delete extend          : DeleteExtent name -Dn \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows deleting an extent. Deleting an extent will not delete the\n");
    Output("  instances associated with the extent but is a function to delete an extent\n");
    Output("  that has some problems and cannot be deleted using DeleteSet. It allows also\n");
    Output("  deleting en empty extent or an enumeration (CodeSet).\n");
    Output("  \n");
//                        -
    Output("  name        - extent name to be deleted\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DELETEEXTENTREF - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DELETEEXTENTREF"

logical CLInterpreter :: DELETEEXTENTREF ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->DeleteExtentRef(Parm(0));
  }
  else
  {
//                                 :   
    Output("Delete extent reference: DeleteExtentRef name -Dn \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows deleting the reference to an extent. It will not delete the\n");
    Output("  instances associated with the extent but is a function to delete an extent\n");
    Output("  that has some problems and cannot be deleted using DeleteSet. It allows also\n");
    Output("  deleting en empty extent or an enumeration (CodeSet).\n");
    Output("  \n");
//                        -
    Output("  name        - extent name to be deleted\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DO - Begin of block

        The  'do' command marks the begin of a block. In contrast to the 'begin'
        command  the  'do'  command  creates  a separate environment stack, wich
        causes  the current state of selected  data sources and property handles
        to  remain unchanged.  After returning  from a  'do' block, the selected
        collections and instances are the same as befor running the do block.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DO"

logical CLInterpreter :: DO ( )
{
  CLInterpreterBase      *clip;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( input_mode ) 
      ReadCommands();
    clip = Push();
    term = clip->ExecuteCommandList(NULL,0);
    clip->Pop();
  }
  else
  {
//                                 :   
    Output("Run command block      : do\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command introduces a block of commands, which is terminated by an 'end'\n");
    Output("  command. Command lines must be entered completely before executing the block.\n");
    Output("  In contrast to 'begin' do returns to the current state of the selected \n");
    Output("  collections and instances after terminating the do block. \n");
    Output("  \n");
//                        -
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ECHO - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ECHO"

logical CLInterpreter :: ECHO ( )
{
  logical                 echo_opt = 2;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    if ( !Parm(0) )
    {
      Output("  echo: %s\n",(char *)(echo? "on" : "off"));
    }
    else if ( !strcmp(gvtsupr(Parm(0)),"ON") )
      echo_opt = YES;
    else if ( !strcmp(Parm(0),"OFF") )
      echo_opt = NO;
    else Output(" ERROR - wrong echo option. Enter 'on' or 'off'.");
    if ( echo_opt != 2 )
    {
      SetEcho(echo_opt);
      cmd->SetEcho(echo_opt);
    }

  else
  {
//                                 :   
    Output("echo command input     : echo [on|off]\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  With 'echo on' you will cause the systen to display the commands entered\n");
    Output("  directly or in a procedure. 'echo off' will switch off this feature.\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  END - End of block

        The  end  command  marks  the  end  of  a  block.  Usually it requires a
        preceeding "do" or "begin".

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "END"

logical CLInterpreter :: END ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( GetOption('h') )
  {
//                                 :   
    Output("Terminate command block: end\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command terminates a command block, which has been introduced by a 'do' or\n");
    Output("  'begin' command.\n");
    Output("  \n");
//                        -
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EXECUTEACTION - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EXECUTEACTION"

logical CLInterpreter :: EXECUTEACTION ( )
{
  char                   *parm;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(NO) )                             ERROR
    parm = Parm(1);
    current_ds->ExecuteAction(Parm(0),&parm);
  }
  else
  {
//                                 :   
    Output("Execute property action: ExecuteAction act_name [parm1 ... parmN] -Dn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function runs the database action named in action_name passing optional\n");
    Output("  parameters as defined in parm1, ..., parmN. \n");
    Output("  \n");
//                        -
    Output("  act_name    - action name for the database action as defined in the context\n");
    Output("                class\n");
    Output("  parm        - parameters passed to the action\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EXECUTEEXPRESSION - Execute expression

        Syntax: Executeexpression expression -Dn 
        The  function runs  the passed  expression. When the expression contains
        blank  characters, it must  be enclosed in  "". You may enter multi-line
        expressions  using the  line continuation  character at  the end of each
        line  but  the  last.  The  expression  must be static, i.e. it must not
        refer to object variables.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EXECUTEEXPRESSION"

logical CLInterpreter :: EXECUTEEXPRESSION ( )
{
  char                   *parm;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->ExecuteExpression(Parm(0));
  }
  else
  {
//                                 :   
    Output("Execute expression     : ExecuteExpression expression\n");
    Output("                                               -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function runs the passed expression. When the expression contains blank\n");
    Output("  characters, it must be enclosed in \"\". You may enter multi-line expressions\n");
    Output("  using the line continuation character at the end of each line but the last.\n");
    Output("  The expression must be static, i.e. it must not refer to object variables.\n");
    Output("  \n");
//                        -
    Output("  expression  - expression to be executed\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EXECUTEINSTANCEACTION - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EXECUTEINSTANCEACTION"

logical CLInterpreter :: EXECUTEINSTANCEACTION ( )
{
  char                   *parm;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    parm = Parm(1);
    current_ds->ExecuteInstanceAction(Parm(0),&parm);
  }
  else
  {
//                                 :   
    Output("Execute instance action: ExecuteInstanceAction act_name [parm1 ... parmN]\n");
    Output("                                               -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function runs the action named in action_name passing optional parameters\n");
    Output("  as defined in parm1, ..., parmN. \n");
    Output("  \n");
//                        -
    Output("  act_name    - action name for the instance action as defined in the context\n");
    Output("                class\n");
    Output("  parm        - parameters passed to the action\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EXECUTEPROPERTYACTION - Execute property action

        Syntax: ExecutePropertyAction action_name [parm1 ... parmN] -Dn -Cn
        The  function  runs  the  the  action  named  in action_name passing the
        optional parameters as defined in parm1, ..., parmN. 
        The  property  action  is  executed  in  the  context  of  the  current 
        collection  (when not using the -D or -C switch). The action called must
        be implemented in the property context class of the current collection.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EXECUTEPROPERTYACTION"

logical CLInterpreter :: EXECUTEPROPERTYACTION ( )
{
  char                   *parm;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    parm = Parm(1);
    current_ds->ExecutePropertyAction(Parm(0),&parm);
  }
  else
  {
//                                 :   
    Output("Execute property action: ExecutePropertyAction act_name [parm1 ... parmN]\n");
    Output("                                               -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function runs the action named in action_name passing optional parameters\n");
    Output("  as defined in parm1, ..., parmN. \n");
    Output("  \n");
//                        -
    Output("  act_name    - action name for the property action as defined in the context\n");
    Output("                class\n");
    Output("  parm        - parameters passed to the action\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EXIT - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EXIT"

logical CLInterpreter :: EXIT ( )
{

  return(QUIT());

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

logical CLInterpreter :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("WHILE",ALINK(this,CLInterpreter,WHILE)),
                           cfte("SFC",ALINK(this,CLInterpreter,SFC)),
                           cfte("SET",ALINK(this,CLInterpreter,SET)),
                           cfte("SAV",ALINK(this,CLInterpreter,SAV)),
                           cfte("SAL",ALINK(this,CLInterpreter,SAL)),
                           cfte("ROLLBACK",ALINK(this,CLInterpreter,ROLLBACK)),
                           cfte("RFC",ALINK(this,CLInterpreter,RFC)),
                           cfte("RETURN",ALINK(this,CLInterpreter,RETURN)),
                           cfte("REDIR",ALINK(this,CLInterpreter,REDIR)),
                           cfte("RECREATEEXTENT",ALINK(this,CLInterpreter,RECREATEEXTENT)),
                           cfte("QUIT",ALINK(this,CLInterpreter,QUIT)),
                           cfte("Q",ALINK(this,CLInterpreter,Q)),
                           cfte("PRINT",ALINK(this,CLInterpreter,PRINT)),
                           cfte("PREV",ALINK(this,CLInterpreter,PREV)),
                           cfte("PAUSE",ALINK(this,CLInterpreter,PAUSE)),
                           cfte("OQL",ALINK(this,CLInterpreter,OQL)),
                           cfte("NEXT",ALINK(this,CLInterpreter,NEXT)),
                           cfte("MOV",ALINK(this,CLInterpreter,MOV)),
                           cfte("LOC",ALINK(this,CLInterpreter,LOC)),
                           cfte("LOAD",ALINK(this,CLInterpreter,LOAD)),
                           cfte("LO",ALINK(this,CLInterpreter,LO)),
                           cfte("LK",ALINK(this,CLInterpreter,LK)),
                           cfte("LI",ALINK(this,CLInterpreter,LI)),
                           cfte("LEAVE",ALINK(this,CLInterpreter,LEAVE)),
                           cfte("LD",ALINK(this,CLInterpreter,LD)),
                           cfte("LCN",ALINK(this,CLInterpreter,LCN)),
                           cfte("LAV",ALINK(this,CLInterpreter,LAV)),
                           cfte("LAN",ALINK(this,CLInterpreter,LAN)),
                           cfte("IF",ALINK(this,CLInterpreter,IF)),
                           cfte("HELP",ALINK(this,CLInterpreter,HELP)),
                           cfte("FA",ALINK(this,CLInterpreter,FA)),
                           cfte("EXIT",ALINK(this,CLInterpreter,EXIT)),
                           cfte("EXECUTEPROPERTYACTION",ALINK(this,CLInterpreter,EXECUTEPROPERTYACTION)),
                           cfte("EXECUTEINSTANCEACTION",ALINK(this,CLInterpreter,EXECUTEINSTANCEACTION)),
                           cfte("EXECUTEEXPRESSION",ALINK(this,CLInterpreter,EXECUTEEXPRESSION)),
                           cfte("EXECUTEACTION",ALINK(this,CLInterpreter,EXECUTEACTION)),
                           cfte("END",ALINK(this,CLInterpreter,END)),
                           cfte("ECHO",ALINK(this,CLInterpreter,ECHO)),
                           cfte("DO",ALINK(this,CLInterpreter,DO)),
                           cfte("DELETEEXTENTREF",ALINK(this,CLInterpreter,DELETEEXTENTREF)),
                           cfte("DELETEEXTENT",ALINK(this,CLInterpreter,DELETEEXTENT)),
                           cfte("DEL",ALINK(this,CLInterpreter,DEL)),
                           cfte("CRT",ALINK(this,CLInterpreter,CRT)),
                           cfte("CPY",ALINK(this,CLInterpreter,CPY)),
                           cfte("COMMITTRANSACTION",ALINK(this,CLInterpreter,COMMITTRANSACTION)),
                           cfte("CO",ALINK(this,CLInterpreter,CO)),
                           cfte("CD",ALINK(this,CLInterpreter,CD)),
                           cfte("CC",ALINK(this,CLInterpreter,CC)),
                           cfte("CALL",ALINK(this,CLInterpreter,CALL)),
                           cfte("BEGINTRANSACTION",ALINK(this,CLInterpreter,BEGINTRANSACTION)),
                           cfte("BEGIN",ALINK(this,CLInterpreter,BEGIN)),
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
    term = CLInterpreterBase::ExecuteFunction(fname,chk_opt);
  

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FA - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FA"

logical CLInterpreter :: FA ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    if ( !strcmp(GetCommand(),"FA") )    
    {
      SetupSubCommand();
      if ( GetCommand() )
        gvtsupr(GetCommand());
    }
    current_ds->DoForAll(GetCommand());
  }
  else
  {
//                                 :   
    Output("do for all instances   : fa command -Dn - Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows repeating a command for all instances in a collection. The\n");
    Output("  command starts with the currently selected instance or with the first when no\n");
    Output("  instance is selected for in the collection.\n");
    Output("  \n");
//                        -
    Output("  command     - The command to be executed in each iteration of the loop. For\n");
    Output("                processing a block of statements you may use the 'call' or the \n");
    Output("                'do' command\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  -Cn         - re-direction to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  fa lav            : List attribute values for all instances in a collection\n"); 
    Output("  fa call proc1     : run procedure proc1 for all instances in the collection\n"); 
    Output("  fa do             : run the list of subsequent commands for all instances in\n"); 
    Output("                      the current collection\n");
    Output("  fa lav -D2 - C1   : show attributes for all instances in collection 1 of data\n");
    Output("                      source 2\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  HELP - List available commands

        Syntax: help [command]
        The  function  will  list  the  commands available in the given context.
        Passsing  a  specific  command  will  display the syntax for the command
        requested.
        1, ..., parmN. 
        The  property  action  is  executed  in  the  context  of  the  current 
        collection  (when not using the -D or -C switch). The action called must
        be implemented in the property context class of the current collection.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HELP"

logical CLInterpreter :: HELP ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    Help(Parm(0));
  else
  {
//                                 :   
    Output("help                   : help [command] -d -a -e\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command shows available commands or details for one command.\n");
    Output("  \n");
//                        -
    Output("  command     - name of the command to be displayed\n");
    Output("  -d          - show details for each command (default for 'command')\n");
    Output("  -a          - show all commands (ignored in connection with 'command')\n");
    Output("  -e          - show extended commands (ignored in connection with 'command')\n");
    Output("  \n");
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IF - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IF"

logical CLInterpreter :: IF ( )
{
  char                   *expression = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                              ERROR
    if ( current_ds->CheckCollection(YES) )          ERROR
    if ( !strcmp(GetCommand(),"IF") )    
    {
      if ( !Parm(1) )
      {
        Output(" Error - Missing expression or command in IF-statement\n");
        ERROR
      }
      if ( SetCondition(Parm(0)) )                    ERROR
      SetupSubCommand();
      SetupSubCommand();
      if ( GetCommand() )
        gvtsupr(GetCommand());
    }
    current_ds->DoIf(GetCommand());
  }
  else
  {
//                                 :   
    Output("do when true           : if expression command -Dn - Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows running a command or a sequence of commands under certain\n");
    Output("  conditions. The command is executed when the expression is true. You may run a\n");
    Output("  sequence of commands enclosed in a begin/do-end block.\n");
    Output("  \n");
//                        -
    Output("  expression  - The condition to be checked before running the command(s). The\n");
    Output("                expression must be a valid ODABA-OQL expression. When the\n");
    Output("                expression contains blanks it must be put into quotes.\n");
    Output("  command     - The command to be executed when the condition ist true.For\n");
    Output("                processing a block of statements you may use 'call' or a\n");
    Output("                'begin/do' block\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  -Cn         - re-direction to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  if \"age > 20\" lav name : \n"); 
    Output("                      The attribute value for 'name' is listed, when 'age' is \n"); 
    Output("                      greater than 20.\n"); 
    Output("  if \"age > 20\" do \n"); 
    Output("    lav name         \n"); 
    Output("    lav age          \n"); 
    Output("  end                \n"); 
    Output("                      The attribute values for 'name' and 'age' are listed, when\n"); 
    Output("                      'age' is greater than 20.\n"); 
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LAN - List attributes

        Syntax: lan [mask] -Dn -Cn
        The  command  will  list  the  available  attributes  for  the  selected
        structure. Passing a mask will list attributes according to the mask.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LAN"

logical CLInterpreter :: LAN ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->ListAttributes(Parm(0));
  }
  else
  {
//                                 :   
    Output("List attribute names   : lan [mask] -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command lists the attribute names available for instances of the current\n");
    Output("  or referenced collection\n");
    Output("  \n");
//                        -
    Output("  mask        - display attribute names according to the mask, only\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  la                : list all attribute names for the current collection\n"); 
    Output("  la  -D3 -c2       : list all attribute names for collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");

  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LAV - Display attributes

        Syntax: lav [prop_path|*] -Dn -Cn
        The  function displays the  values for one  or more attributes. When not
        passing  an attribute  name or  property path  pointing to an attribute,
        the  command will  list the  values for  the defined attribute list. For
        showing all attributes an * must be passed as property path. 
        The  data source condext (ds_id) and the hierarchy identifyier (hier_id)
        allow  referring  to  another  hierarchy  then the current or to another
        data  source context. Referring to the current hierarchy in another data
        source context is possible by passing 'ds_id::'.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LAV"

logical CLInterpreter :: LAV ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    DisplayAttribute(Parm(0));
  }
  else
  {
//                                 :   
    Output("List attribute values  : lav [attrname|*] -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command shows the attribute value for a single attribute or all\n");
    Output("  attributes for the instance. When an attribute ist has been defined (al) the\n");
    Output("  attributes of the list are displayed by default.\n");
    Output("  \n");
//                        -
    Output("  attrname   - property path to attribute to be displayed\n");
    Output("  *           - display all attributes\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  lav first_name    : display 'first_name' value for selected instance\n"); 
    Output("  lav               : display all attributes (no list) or the attributes defined\n");
    Output("                      in an attribute list (--> al)\n");
    Output("  lav * -D3 -c2     : display all attributes for the selected instance in \n");
    Output("                      collection 2 of data source context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LCN - List references/collections

        Syntax: lcn [mask] -E -Dn -Cn
        The  command will  list all  collections avaiable  in the given context.
        When   a   property   handle   is   opened   subsequent   references and
        relationships  are  displayed.  When  no  property  handle  is  opened 
        available  extents are listed. Passing a  mask will list the collections
        according  to the mask (e.g. all  collections with a name beginning with
        a when passing 'a*').
        The  -E  option  will  list  also empty collections which are not listed
        when not using this option.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LCN"

logical CLInterpreter :: LCN ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->ListCollections(Parm(0),GetOption('E') ? YES : NO);
  }
  else
  {
//                                 :   
    Output("List collection names  : lcn [mask] -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command lists the sub-collection or reference names available for\n");
    Output("  instances of the current or referenced collection\n");
    Output("  \n");
//                        -
    Output("  mask        - display collection names according to the mask, only\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  lc                : list all collection names for the current collection\n"); 
    Output("  lc  -D3 -c2       : list all collection names for collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LD - List data sources

        Syntax: ld [*]
        The  function  lists  all  available  data  sources.  When  passing * as
        parameter  the command  will list  all data  source contexts opened with
        the corresponding context number.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LD"

logical CLInterpreter :: LD ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    ListDataSource(Parm(0));
  else
  {
//                                 :   
    Output("list data sources      : ld \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command displays available or opened data sources.\n");
    Output("  \n");
//                        -
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LEAVE - Leave block or procedure

        Leave  causes  the  command  line  interpreter to leave a block. When no
        block  is activated the command works the  same way as return and leaves
        the procedure or the program.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LEAVE"

logical CLInterpreter :: LEAVE ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    proc_opt = 'l';
  else
  {
//                                 :   
    Output("leave block            : leave \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command will leave the current block (do-end or begin-end) and continue \n");
    Output("  with the next statement after the 'end' statement.\n");
    Output("  \n");

  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LI - Display collection

        Syntax: li -Dn -Cn
        The  display collection command will list  all keys or positions for the
        instances  of  the  current  collection.  This  might change the current
        selection  in  the  property  path.  If  no instance is selected for the
        parent  level,  the  first  instance  for  the  parent level is selected
        automatically.
        When  passing a property path, the collection referenced by the property
        path  is  displayed.  The  property  path  passed as parameter must be a
        valid  property path for  the selected property  handle (i.e. a property
        of  the  selected  structure)  and  in  instance must be selected in the
        current context or the first instance is selected automatically.
        When  passing  a  hierarchy  identifier  (-Cn)  the  collection  in  the
        referenced  hierarchy is displayed without changing the hierarchy level.
        Passing  a data source context number  (-Dn) and a hierarchy number will
        display  instances  in  the  collection  of  the  referenced data source
        context.  Passing  a  only  data  source  context  (-Dn),  will list the
        instances  for  the  current  collection  in  the referenced data source
        context.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LI"

logical CLInterpreter :: LI ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->DisplayCollection();
  }
  else
  {
//                                 :   
    Output("List instances         : li -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command shows lists all instances of the collection by kay value or\n");
    Output("   position.\n");
    Output("  \n");
//                        -
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  li                : list instances of current collection\n"); 
    Output("  li  -D3 -c2       : list all instances for collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LK - List keys

        Syntax: lk -Cn -Dn
        The  command  lists  the  keys  defined  for  the structure. This is not
        identical  with the  list of  indexes (sort  orders) for the collection,
        which can be displayed with the 'lo' command.
        e  is selected for  the parent level,  the first instance for the parent
        level is selected automatically.
        When  passing a property path, the collection referenced by the property
        path  is  displayed.  The  property  path  passed as parameter must be a
        valid  property path for  the selected property  handle (i.e. a property
        of  the  selected  structure)  and  in  instance must be selected in the
        current context or the first instance is selected automatically.
        When  passing  a  hierarchy  identifier  (-Cn)  the  collection  in  the
        referenced  hierarchy is displayed without changing the hierarchy level.
        Passing  a data source context number  (-Dn) and a hierarchy number will
        display  instances  in  the  collection  of  the  referenced data source
        context.  Passing  a  only  data  source  context  (-Dn),  will list the
        instances  for  the  current  collection  in  the referenced data source
        context.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LK"

logical CLInterpreter :: LK ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->ListKeys();
  }
  else
  {
//                                 :   
    Output("List keys              : lk  -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command lists the keys defined for the structure. This is not identical \n");
    Output("  with the list of indexes (sort orders) for the collection, which can be \n");
    Output("  displayed with the 'lo' command.\n");
    Output("  \n");
//                        -
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  lk                : list keys for the structure of the current collection\n"); 
    Output("  la  -D3 -c2       : list keys for the structure for collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LO - Liste available sort orders (indexes)

        Syntax: lo -Cn -Dn
        The  command displays the sort orders (index or key names) available for
        the selected collection.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LO"

logical CLInterpreter :: LO ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->ListOrder();
  }
  else
  {
//                                 :   
    Output("List sort orders       : lo  -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command lists the sort orders (key names) available for instances of the\n");
    Output("  current or referenced collection\n");
    Output("  \n");
//                        -
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  lo                : list sort orders for the current collection\n"); 
    Output("  lo  -D3 -c2       : list sort orders for collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LOAD - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LOAD"

logical CLInterpreter :: LOAD ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    LoadProcedure(Parm(0));
  }
  else
  {
//                                 :   
    Output("Load procedure file    : load file_name\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command loads commands from the file. A loaded procedure or entry points\n");
    Output("  in a loaded procedure can be called at any time after the procedure is .\n");
    Output("  loaded.\n");
    Output("  As long as entry point in all loaded procedures are unique you may call an \n");
    Output("  entry point without prefixing the procedure path. If entry point names are not\n");
    Output("  unique, the procedure path must be entered before the entry point name. \n");
    Output("  \n");
//                        -
    Output("  file_name   - complete path to the file containing the instructions\n");
    Output("  \n");
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LOC - Locate instance

        Syntax: loc keyval|pos -S -Dn -Cn
        The  locate  command  allows  locating  an  instance in the current or a
        previously  opened (parent)  collection. The  instance can be positioned
        by  key or position. Position  must be a number  less than the number of
        instances in the collection. Key values are passed as string keys. 
        For  locating an instance in a parent location or in another data source
        context,  you may pass the -Dn  and/or -Cn option for addressing another
        collection (in another data source context). 
        The  -S option  forces the  command to  display the key for the selected
        instance.  When  the  collection  is  unordered  the  position number is
        displayed instead.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LOC"

logical CLInterpreter :: LOC ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->Locate(Parm(0));
  }
  else
  {
//                                 :   
    Output("Locate instance        : loc [key_value|pos] -S -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command locates an instance in the referenced collection. Locating an\n");
    Output("  instance will reset the selections for all subsequent collections in the\n");
    Output("  hierarchy. After locating an instance it is selected in the collection.\n");
    Output("  \n");
//                        -
    Output("  key_value   - key value for the instance to be located (ordered collection)\n");
    Output("  pos         - position of instance to be located in the collection\n");
    Output("  -S          - show key for the instance located\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  loc Miller|Paul   : locate person instance for Paul Miller\n"); 
    Output("  loc 0             : locate first instance n collection\n");
    Output("  loc -S            : Display the currently selected key\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  MOV - Move instance or collection

        Syntax:       mov       [[ds_id:]hier_id:]keyval|position|.|*      
        [[ds_id:]hier_id:][new_key]
        The  command moves  the selected  instance to the referenced collection.
        Copying  an instance or collection from  or to the current collection in
        another data source context is possible by passing 'ds_id::'. 
        When  passing a dot '.' instead of a key value or a position number, the
        instance  selected  in  the  referenced  or current collection is moved.
        Otherwise  instances  according  to  the  key value are moved. Passing *
        will  move all instance from the  source collection. Moved instances are
        deleted in the source collection.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MOV"

logical CLInterpreter :: MOV ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->Move(last_ds,Parm(0),Parm(1));
  }
  else
  {
//                                 :   
    Output("Move instance          : mov keyval|position|.|* [new_key] -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command moves a single instance or a collection of instances from the \n");
    Output("  current collection to the referenced collection. Moving an instance will \n");
    Output("  delete the instance in the source collectin and change the selections for all\n");
    Output("  subsequent collections in the target hierarchy.\n");
    Output("  \n");
//                        -
    Output("  pos         - position of instance to be moved\n");
    Output("  .           - move instance currently selected in the collection\n");
    Output("  key_value   - key value for the instance to be moved (ordered collection)\n");
    Output("  new_key     - move and rename instance of an ordered collection (single\n");
    Output("                instance, only)\n");
    Output("  *           - move all instances filtered in the current colletion (--> sfc)\n");
    Output("  -Dn         - target data source for move. When no target is defined the \n");
    Output("                instance is copied to the current data source (with new key)\n");
    Output("  -Cn         - target collection for move. When no target collection is defined\n");
    Output("                the instance is copied to the current collection in the\n");
    Output("                referenced data source (-Dn)\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  mov Miller|Paul   : Move person instance for Paul Millerto selected instance\n"); 
    Output("  mov 0             : Move first instance to selected instance\n");
    Output("  mov . -D3 -C2     : Move selected instance to collection 2 of data source\n");
    Output("                      context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  NEXT - Locate next instance

        Syntax: next count -S -Dn -Cn
        The  next  command  allows  locating  the next instance skipping 'count'
        instances.  
        For  locating an instance in a parent location or in another data source
        context,  you may pass the -Dn  and/or -Cn option for addressing another
        collection (in another data source context).
        The  -S option  forces the  command to  display the key for the selected
        instance.  When  the  collection  is  unordered  the  position number is
        displayed instead.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NEXT"

logical CLInterpreter :: NEXT ( )
{
  int                     count = 1;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    if ( Parm(0) )
      count += atoi(Parm(0));
    current_ds->Position(count);
  }
  else
  {
//                                 :   
    Output("Position foreward      : next [count] -S -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command locates the next instance by skipping a number of count instances.\n");
    Output("  The command will reset the selections for all subsequent collections in the\n");
    Output("  hierarchy. After locating an instance it is selected in the collection.\n");
    Output("  \n");
//                        -
    Output("  count       - number of instances to be skipped (default is 0)\n");
    Output("  -S          - show key for the instance located\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  next -S           : locate naxt instance in the collection and display the key\n"); 
    Output("                      for the selected instance\n"); 
    Output("  next 7            : locate next instance after skipping the next 7 instances\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OQL - Running an oql query from the commanline

        Syntax: oql statements end
        The  command allows  entering a  number of  command lines for a complete
        OQL  query.  A  query  can  be  defined  as  SELECT statement, as an OQL
        expression  or as  an access  path. You  can run  any query using the CC
        command,  but in this case you must  enter the query in the same command
        line.  OQL allows defining queries, which are defined on several command
        lines.
        The  query  is  terminated  with  an  end line, which must be a separate
        line.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OQL"

logical CLInterpreter :: OQL ( )
{
  char                   *string;
  CLInterpreterBase      *clip = this;
  logical                 do_opt = NO;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(NO) )                               ERROR
    if ( strcmp(GetCommand(),"OQL") )                ERROR
    string = GetCommandLine();
    gvtxbts(string,string,strlen(string));  // remove trailing blanks
    if ( (do_opt = !stricmp(string,"DO")) || !stricmp(string,"BEGIN") )
    {
      string = NULL;
      if ( do_opt )
        clip = Push();
    }
    clip->get_current_ds()->RunQuery(string);
    if ( do_opt )
      clip->Pop();
  }
  else
  {
//                                 :   
    Output("run OQL query          : oql ");
    Output("                       :     query statements\n");
    Output("                       : end\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows running an OQL query on the selected collection. The statements\n");
    Output("  are defined on the successor lines and must contain an OQL expression or a OQL \n");
    Output("  query (select statement). The and of te statement is indicated with the 'end' line.\n");
    Output("  \n");
//                        -
    Output("  command     - The command to be executed in each iteration of the loop. For\n");
    Output("                processing a block of statements you may use the 'call' or the \n");
    Output("                'do' command\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  -Cn         - re-direction to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  oql \n"); 
    Output("    select (name, first_name) \n"); 
    Output("    from  (person) \n"); 
    Output("    where (name > 'H') \n"); 
    Output("  end \n"); 
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PAUSE - Pause execution

        Syntax: pause
        The command stops the execution until the enter key is pressed.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PAUSE"

logical CLInterpreter :: PAUSE ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    Output("Press any key to continue ...");
    getchar();
  }

  else
  {
//                                 :   
    Output("Pause processing       : pause\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command stops the execution until the enter key is pressed.\n");
    Output("  \n");
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PREV - Locate previous instance

        Syntax: prev count -S -Dn -Cn
        The  'prev'  command  allows  locating  the  previous  instance  in  a 
        collection skipping 'count' instances.  
        For  locating an instance in a parent location or in another data source
        context,  you may pass the -Dn  and/or -Cn option for addressing another
        collection (in another data source context).
        The  -S option  forces the  command to  display the key for the selected
        instance.  When  the  collection  is  unordered  the  position number is
        displayed instead.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PREV"

logical CLInterpreter :: PREV ( )
{
  int                     count = -1;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    if ( Parm(0) )
      count -= atoi(Parm(0));
    current_ds->Position(count);
  }
  else
  {
//                                 :   
    Output("Position backward      : prev [count] -S -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command locates the previous instance by skipping a number of count \n");
    Output("  instances. The command will reset the selections for all subsequent \n");
    Output("  collections in the hierarchy. After locating an instance it is selected in the\n");
    Output("  collection.\n");
    Output("  \n");
//                        -
    Output("  count       - number of instances to be skipped (default is 0)\n");
    Output("  -S          - show key for the instance located\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  next -S           : locate naxt instance in the collection and display the key\n"); 
    Output("                      for the selected instance\n"); 
    Output("  next 7            : locate next instance after skipping the next 7 instances\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PRINT - Print currently selected instance

        Syntax: print format_string parm1 ... parmN -Dn -Cn
        The  'print'  command  allows  displaying  the  content  of the currenly
        selected  instance in a formatted string.  When no instance is selected,
        the  result is empty. You may use the  print command in a while loop for
        displaying a collection of instances.
        The  format  string  contains  fixed  text and '%s' variables, which are
        replaced  by the values  of the parameters  passed as parm1 to parmN. As
        parameter  you  may  pass  variable  names  or expressions, which can be
        evaluated  for the selected instance.  All parameters are converted into
        strings automatically, before being passed to the format string.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PRINT"

logical CLInterpreter :: PRINT ( )
{
  int                     indx = 0;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    while ( Parm(++indx) ) ;
    current_ds->Print(Parm(0),&parm_list[1],indx-1);
  }
  else
  {
//                                 :   
    Output("display formatted data : print fstring [parm ... parm] -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows displaying the content of the currenly selected instance \n");
    Output("  in a formatted string. When no instance is selected, the result is empty.   \n");
    Output("  You may use the print command in a while loop for displaying a collection of\n");
    Output("  instances. \n");
    Output("  \n");
//                        -
    Output("  fstring     - the format string contains fixed text and '%s' variables, which\n");
    Output("                are replaced by the values of the parameters passed as parameter.\n"); 
    Output("  parm        - any variable name or expression, which can be evaluated for the \n");
    Output("                selected instance, can be passed as parameter. All parameters   \n");
    Output("                are converted into strings automatically, before being passed to\n");
    Output("                the format string. \n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  print \"hello world\" : prints a constant text\n"); 
    Output("  print \"The address of %s %s is %s\" first_name last_name address\n"); 
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Q - Terminate debugger (alias for QUIT)

        This  is  a  run  command, which immediately terminates the application.
        When  running  the  debugger  under  OShell,  it  does not terminate the
        OShell, but the debug-ger, only.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Q"

logical CLInterpreter :: Q ( )
{

  return(QUIT());

}

/******************************************************************************/
/**
\brief  QUIT - Terminate debugger (alias for QUIT)

        This  is  a  run  command, which immediately terminates the application.
        When  running  the  debugger  under  OShell,  it  does not terminate the
        OShell, but the debug-ger, only.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "QUIT"

logical CLInterpreter :: QUIT ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    proc_opt = 'x';
  else
  {
//                                 :   
    Output("quit application       : quit|q|exit|x \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command will close all collections and data sources and terminate the\n");
    Output("  console\n");
    Output("  \n");
  }
  

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RECREATEEXTENT - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RECREATEEXTENT"

logical CLInterpreter :: RECREATEEXTENT ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->RecreateExtent(Parm(0));
  }
  else
  {
//                                 :   
    Output("Recreate extend          : RecreateExtent name -Dn \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows recreating a corrupted extent. The corrupted extent will \n");
    Output("  be deleted before recreating it. The function may take a while, since the\n");
    Output("  whole database is searched for entries, which belong to the extent\n");
    Output("  \n");
//                        -
    Output("  name        - extent name to be recreated\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  REDIR - Redirect output

        Syntax: redir [path]
        The  function  allows  the  permanent  redirection  of  output  for  the
        subsequent  commands.  Only  data  output  is  redirected  to  the  file
        location  passed  to  the  command.  Error and system messages are still
        written to the standard output.
        Calling  redir  without  parameter  will  reset  the  redirection of the
        output.  Redirection  of  the  output  is  also  reset  at  the end of a
        begin/do  block, when being specified within the  block or at the end of
        a called procedure, when being activated within a procedure.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "REDIR"

logical CLInterpreter :: REDIR ( )
{
  int                     indx = 0;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  { 
    if ( parent && (output == parent->get_output()) )
      output = NULL;
    if (Parm(0)) InitOutput(Parm(0));
    else   InitOutput( "" );
  }
  else
  {
//                                 :   
    Output("redirect output        : redir [path]\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function allows the permanent redirection of output for the subsequent   \n");
    Output("  commands. Only data output is redirected to the file location passed to the  \n");
    Output("  command. Error and system messages are still written to the standard output. \n");
    Output("  Calling redir without parameter will reset the redirection of the output.    \n");
    Output("  Redirection of the output is also reset at the end of a begin/do block, when \n");
    Output("  being specified within the block or at the end of a called procedure, when   \n");
    Output("  being activated within a procedure.\n");
    Output("  \n");
//                        -
    Output("  path        - location for redirection.\n"); 
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  redir c:/out.txt  : write output to file out.txt on drive c\n"); 
    Output("  redir             : reset redirection for getting the output on standard\n"); 
    Output("                      output\n"); 
    Output("  \n");
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RETURN - Return from procedure

        A  return  statement  causes  the  command line interpreter to leave the
        current  procedure. Entered on console it will leave the current console
        input  (i.e. the  programm, when  the console  has not been activated by
        the console command).

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RETURN"

logical CLInterpreter :: RETURN ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
    proc_opt = 'r';
  else
  {
//                                 :   
    Output("Return from procedure  : return \n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command will leave the current procedure and continue with the next \n");
    Output("  statement after the procedure call.\n");
    Output("  \n");
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RFC - Reset selection

        Syntax: rfc -Dn -Cn
        The  command  resets  a  defined  filter  condition  for  the  current 
        collection.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RFC"

logical CLInterpreter :: RFC ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->Unselect();
  }
  else
  {
//                                 :   
    Output("Reset filter condition : rfc -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command resets the filter condition set for the current or referenced\n");
    Output("  collection\n");
    Output("  \n");
//                        -
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  rsl               : reset selection for the current collection\n"); 
    Output("  rsl  -D3 -c2      : reset selection for collection 2 of data source context 3\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ROLLBACK - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ROLLBACK"

logical CLInterpreter :: ROLLBACK ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->RollBack(GetOption('a') ? YES : NO);
  }
  else
  {
//                                 :   
    Output("Cancel transaction     : RollBack -a - Dn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function stops a transaction discarding all changes.\n");
    Output("  \n");
//                        -
    Output("  -a          - stop all transactions\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SAL - Define attribute list

        Syntax: sal attrname_1 ... attrname_n -A -Dn -Cn
        The  function defines an attribute display list for the attributes to be
        displayed  using the da  command. The attribute  list is defined for the
        currently selected hierarchy level. 
        The  attribute  list  can  be  deleted not passing any parameter. The -A
        option allows appending the attribute list.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SAL"

logical CLInterpreter :: SAL ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->AttributeList(parm_list,GetOption('A') ? YES : NO);
  }
  else
  {
//                                 :   
    Output("Set attribute list     : sal attrname_1 ... attrname_n -A -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  \n");
    Output("  The command allows setting an atribute list for the selected collection, that\n");
    Output("  are listed when calling the list attribute values (lav) command.\n");
    Output("  \n");
//                        -
    Output("  attr_name_n - attribute name to be displayed\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  -Cn         - re-direction to other collection th the hierarchy\n");
    Output("  -A          - append current attribute list. When this option is not set the \n");
    Output("                list is deleted and rebuilt.\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  sal name income   : creates a new attribute list with 'name' and 'income'\n"); 
    Output("  sal first_name -A : adds 'first_name' to the attribute list\n"); 
    Output("  sal name -D2 -C1  : creates a new attribute list with 'name' for collection 1\n");
    Output("                      in datasource context 2\n");
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SAV - Set value for attribute

        Syntax: sav [[ds_id:]hier_id:]attr_name=value
        The  command  will  change  the  value  for  the attribute referenced by
        attr_name.  The  data  source  must  be  opened  for update/write and an
        instance must be selected in the referenced collection context.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SAV"

logical CLInterpreter :: SAV ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->SetValue(Parm(0));
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
    Output("  sav name='Smith'  : change name value to 'Smith'\n"); 
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SET - Set system variable

        Syntax: SetSysVariable var_name value
        The  function  allows  setting  a  value  for  a  system  or environment
        variable.  System variables are usually  references as "var_name" in ini
        files  or other locations.  System variables cab  be retrieved using the
        GetSysVariable() command.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SET"

logical CLInterpreter :: SET ( )
{
  int                     indx = 0;
  char                   *pos;
  char                   *text;
  char                    variable[ID_SIZE];
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( !Parm(0) )
      while ( text = GetPosSysVariable(++indx,variable) )
        Output("  %s=%s\n",variable,text);
    else 
    {
      if ( !Parm(1) && (pos = strchr(Parm(0),'=')) )
      {
          SetParm(1,pos+1);
          *pos = 0;
      }
      if ( Parm(1) )
        ::SetSysVariable(Parm(0),Parm(1));
      else
        Output("  %s=%s\n",Parm(0),::GetSysVariable(Parm(0)));
    }
  }
  else
  {
//                                 :   
    Output("set                    : set var_name [value]\n");
    Output("                         set [var_name=value]\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The function allows setting or displaying a value for a system or environment\n");
    Output("  variable. Not passing any parameter will display all variables set.\n");
    Output("  \n");
//                        -
    Output("  var_name    - Name for the system variable (usually referenced as %var_name%)\n");
    Output("  value       - value to be set for the variable\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  set NAME=Smith    : Setting value for NAME to 'Smith'\n"); 
    Output("  set NAME          : display current settings for NAME\n"); 
    Output("  set NAME=         : reset current settings for NAME\n"); 
    Output("  set               : display current settings for all variables\n"); 
    Output("                      context 3\n");
    Output("  \n");

  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SFC - Set selection

        Syntax: sfc expression | -Fexpression_path
        The  command  defines  a  filter  for the current collection. The filter
        condition  is read from a file, when  f:expression points to a text file
        that contqains the expression.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SFC"

logical CLInterpreter :: SFC ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                             ERROR
    current_ds->Select(Parm(0));
  }
  else
  {
//                                 :   
    Output("Set Filter condition   : sfc expression -Dn -Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command restricts the number of visible instances in the current or\n");
    Output("  referenced collection by setting a filter condition (selection).\n");
    Output("  \n");
//                        -
    Output("  expression  - filter expression for the selection\n");
    Output("  -Dn         - redirect to other data source context\n");
    Output("  -Cn         - redirect to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  sfc name > 'S'    : display instances with nam greater than S, only. Note,\n"); 
    Output("                      that constant string values must be put in single quotes.\n"); 
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WHILE - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WHILE"

logical CLInterpreter :: WHILE ( )
{
  char                   *expression = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !GetOption('h') )
  {
    if ( CheckDS(YES) )                              ERROR
    if ( current_ds->CheckCollection(YES) )          ERROR
    if ( !strcmp(GetCommand(),"WHILE") )    
    {
      if ( Parm(0) )
        expression = strdup(Parm(0));
      if ( !Parm(1) )
      {
        Output(" Error - Missing expression or command in while-statement\n");
        ERROR
      }
      if ( SetCondition(expression) )                 ERROR
      SetupSubCommand();
      SetupSubCommand();
      if ( GetCommand() )
        gvtsupr(GetCommand());
    }
    current_ds->DoWhile(GetCommand());
  }
  else
  {
//                                 :   
    Output("do while true          : while expression command -Dn - Cn\n");
    if ( !GetOption('d') )                           LEAVESEQ

//                   1         2         3         4         5         6         7         8
//          12345678901234567890123456789012345678901234567890123456789012345678901234567890   
    Output("  The command allows running a command or a sequence of commands as long as the\n");
    Output("  passed condition is true. In contrast to 'fa' the function does not change\n");
    Output("  the selection for the collection. You may pass a sequence of commands\n");
    Output("  enclosed in a begin/do-end block.\n");
    Output("  \n");
//                        -
    Output("  expression  - The condition to be checked before running the command(s). The\n");
    Output("                expression must be a valid ODABA-OQL expression. When the\n");
    Output("                expression contains blanks it must be put into quotes.\n");
    Output("  command     - The command to be executed when the condition ist true.For\n");
    Output("                processing a block of statements you may use 'call' or a\n");
    Output("                'begin/do' block\n");
    Output("  -Dn         - re-direction to other data source context\n");
    Output("  -Cn         - re-direction to other collection in the hierarchy\n");
    Output("  \n");
    Output("Examples\n");
//                              :
    Output("  while \"age > 20\" sav age={age+1} : \n"); 
    Output("                      The attribute value for 'name' is listed, when 'age' is \n"); 
    Output("                      greater than 20.\n"); 
    Output("  while \"age > 20\" begin \n"); 
    Output("    lav name         \n"); 
    Output("    next          \n"); 
    Output("  end                \n"); 
    Output("                      The attribute values for 'name' and 'age' are listed, when\n"); 
    Output("                      'age' is greater than 20.\n"); 
    Output("  \n");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~CLInterpreter - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CLInterpreter"

     CLInterpreter :: ~CLInterpreter ( )
{



}


