/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    CLIDataSource

\brief    


\date     $Date: 2006/08/28 14:29:04,40 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CLIDataSource"

#include  <poql.h>
#include  <sCLICollection.hpp>
#include  <sCLIDataSource.hpp>
#include  <sCLInterpreter.hpp>
#include  <sCLInterpreterBase.hpp>
#include  <sPropertyHandle.hpp>
#include  <sCLIDataSource.hpp>


/******************************************************************************/
/**
\brief  AttributeList - 



\return term - 

\param  attributes - 
\param  append - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AttributeList"

logical CLIDataSource :: AttributeList (char **attributes, logical append )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->SetAttributes(attributes,append);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BeginTransaction - 



\return term - 

\param  ext_TA - External transaction
\param  w_maxnumstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BeginTransaction"

logical CLIDataSource :: BeginTransaction (logical ext_TA, char *w_maxnumstr )
{
  int16                   maxnum = AUTO;
  int16                   ta_level = 0;
  logical                 term = NO;
BEGINSEQ
  if ( w_maxnumstr && *w_maxnumstr )
    if ( maxnum = atoi(w_maxnumstr) <= 0 )
      maxnum = AUTO;
      
  if ( (ta_level = ds_handle.BeginTransaction(ext_TA,maxnum)) <= 0 )
                                                     ERROR
  Output("  Current transaction level: %i\n",ta_level);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CLIDataSource - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  clipbase - 
\param  odaba_client - ODABA Client Handle
\param  dsname - 
\param  ds_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLIDataSource"

     CLIDataSource :: CLIDataSource (CLInterpreterBase *clipbase, ODABAClient &odaba_client, char *dsname, int32 ds_id )
                     : id(ds_id),
  ds_handle(),
  interpreter(clipbase),
  ph_count(0),
  ph_cur(AUTO),
  ph_last(AUTO)

{
  int         i = 0;
BEGINSEQ
  if ( ds_handle.Open(odaba_client,dsname,PI_Write) )  
  {
    Output("  Error - Data source '%s' could not be opened\n",dsname);
    ERROR
  }
  strcpy(name,dsname);
RECOVER
  id = 0;

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  clipbase - 
\param  source_ds - 
\param  ds_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLIDataSource"

     CLIDataSource :: CLIDataSource (CLInterpreterBase *clipbase, CLIDataSource *source_ds, int32 ds_id )
                     : id(ds_id),
  ds_handle(),
  interpreter(clipbase),
  ph_count(0),
  ph_cur(AUTO),
  ph_last(AUTO)

{
  int          count = source_ds->get_ph_count();
  ds_handle = source_ds->get_ds_handle();
  strcpy(name,source_ds->get_name());

  if ( ds_handle.IsOpened() )
  {
    for ( int i = 0; i < count; i++ )
      ph_list[i] = new CLICollection(this,*source_ds->GetCollection(i));
    ph_count = count;
    ph_cur = source_ds->get_ph_cur();
    ph_last = source_ds->get_ph_last();
  }


}

/******************************************************************************/
/**
\brief  i02 - 



\param  clipbase - 
\param  odaba_client - ODABA Client Handle
\param  dbohandle - 
\param  dsname - 
\param  ds_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLIDataSource"

     CLIDataSource :: CLIDataSource (CLInterpreterBase *clipbase, ODABAClient &odaba_client, DBObjectHandle &dbohandle, char *dsname, int32 ds_id )
                     : id(ds_id),
  ds_handle(),
  interpreter(clipbase),
  ph_count(0),
  ph_cur(AUTO),
  ph_last(AUTO)

{

  ds_handle = dbohandle;
  strcpy(name,dsname);


}

/******************************************************************************/
/**
\brief  ChangeCollection - 



\return term - 

\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeCollection"

logical CLIDataSource :: ChangeCollection (char *prop_path )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(NO) || !*prop_path )          LEAVESEQ
  
  ph_cur = ph_count-1;
  if ( *prop_path >= '0' && *prop_path <= '9' )    // change collection
  {
    id = atoi(prop_path);
    if ( id >= ph_count )
    {
      Output("Error - invalid collection id '%i'\n",id);
                                                     ERROR
    }
    ph_cur = ph_last = id;
    LEAVESEQ
  }
  
  if ( *prop_path == '/' )    // change root
  {
    while ( ph_count > 0 )
      CloseCollection();
    prop_path++;
  }
  while ( *prop_path == '.' )
  {
    CloseCollection();
    prop_path++;
  }
  if ( !*prop_path )                                 LEAVESEQ
    
  if ( !ds_handle.IsOpened() )
    Output("No data source opened. Open data source with cd-command\n");
  else
  {
    if ( ph_count )
      ph_list[ph_count] = new CLICollection(this,*ph_list[ph_count-1],prop_path);
    else
      ph_list[ph_count] = new CLICollection(this,ds_handle,prop_path,ds_handle.GetAccess() == PI_Read ? PI_Read : PI_Update);
    if ( !*ph_list[ph_count]->GetName() )
    {
      Output("Error - Invalid collection name '%s'\n",prop_path);
      delete ph_list[ph_count];
      ph_list[ph_count] = NULL;
    }
    else
      ph_cur = ph_last = ph_count++;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeOrder - 



\return term - 

\param  key_name - Key name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeOrder"

logical CLIDataSource :: ChangeOrder (char *key_name )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  if ( ph_list[ph_cur]->SetOrder(key_name) )
  {
    Output("Error - invalid sort key\n");            ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckCollection - 



\return term - 

\param  msg_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckCollection"

logical CLIDataSource :: CheckCollection (logical msg_opt )
{
  int32                    id;
  char                   *cid;
  logical                 term = NO;
BEGINSEQ
  ph_cur = ph_last;
  if ( cid = interpreter->GetOption('C') )
  {
    id =  atoi(cid);
    if ( id >= ph_count )
    {
      Output("Error - invalid collection id '%i'\n",id);
                                                     ERROR
    }
    else
      ph_cur = id;
    LEAVESEQ
  }
  if ( ph_cur < 0 )
    ph_cur = ph_count-1;

  if ( msg_opt && ph_cur < 0 )
  {
    Output("Error - no collection opened\n");        ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CloseCollection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseCollection"

logical CLIDataSource :: CloseCollection ( )
{
  logical                 term = NO;
  if ( ph_count )
  {
    ph_count--;
    delete ph_list[ph_count];
    ph_list[ph_count] = NULL;
    if ( ph_last >= ph_count )
      ph_last = ph_count-1;
    if ( ph_cur >= ph_count )
      ph_cur = ph_last;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  CommitTransaction - 



\return term - 

\param  all_ta - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CommitTransaction"

logical CLIDataSource :: CommitTransaction (logical all_ta )
{
  logical                 term = NO;
BEGINSEQ
  if ( ds_handle.CommitTransaction(all_ta ? 1 : AUTO) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy - 



\return term - 

\param  source_ds - 
\param  old_key - 
\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical CLIDataSource :: Copy (CLIDataSource *source_ds, char *old_key, char *key_value )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  if ( source_ds->CheckCollection(YES) )             ERROR
  
  ph_list[ph_cur]->Copy(source_ds->GetCollection(AUTO),old_key,key_value);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyContext - 



\return term - 

\param  ds_context - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyContext"

logical CLIDataSource :: CopyContext (CLIDataSource *ds_context )
{
  int32                    i = 0;
  CLICollection          *clic;
  logical                 term = NO;
BEGINSEQ
  while ( clic = ds_context->GetCollection(i++) )
    if ( ChangeCollection(clic->GetName()) )           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create - 



\return term - 

\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical CLIDataSource :: Create (char *key_value )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->Create(key_value);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBHandle - 



\return dbhandle - Pointer to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBHandle"

DatabaseHandle &CLIDataSource :: DBHandle ( )
{

  return ( ds_handle.GetDBHandle() );

}

/******************************************************************************/
/**
\brief  Delete - 



\return term - 

\param  mask - 
\param  err_del - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical CLIDataSource :: Delete (char *mask, logical err_del )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->Delete(mask,err_del);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteExtent - 



\return term - 

\param  ext_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtent"

logical CLIDataSource :: DeleteExtent (char *ext_names )
{
  logical                 term = NO;
  if ( ds_handle.DeleteExtent(ext_names) )
    Output("  Could not delete extent '%s'\n",ext_names);
  else
    Output("  Extent '%s' deleted\n",ext_names);

  return(term);
}

/******************************************************************************/
/**
\brief  DeleteExtentRef - 



\return term - 

\param  ext_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtentRef"

logical CLIDataSource :: DeleteExtentRef (char *ext_names )
{
  logical                 term = NO;
  if ( ds_handle.DeleteExtentRef(ext_names) )
    Output("  Could not delete extent '%s'\n",ext_names);
  else
    Output("  Extent '%s' deleted\n",ext_names);

  return(term);
}

/******************************************************************************/
/**
\brief  DictHandle - 



\return dicthdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictHandle"

DictionaryHandle &CLIDataSource :: DictHandle ( )
{

  return ( ds_handle.GetDictionary() );

}

/******************************************************************************/
/**
\brief  DisplayCollection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayCollection"

logical CLIDataSource :: DisplayCollection ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->List();
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DisplayKey - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayKey"

logical CLIDataSource :: DisplayKey ( )
{
  char                    string[1024];
  char                   *keyptr;
  logical                 term = NO;
BEGINSEQ
  if ( !ph_list[ph_cur]->IsPositioned() ||
       !interpreter->GetOption('S') )                LEAVESEQ

  if ( keyptr = ph_list[ph_cur]->ExtractSortKey() )
  {
    ph_list[ph_cur]->KeyToString(string,keyptr);
    Output("  %s\n",string);
  }
  else
    Output("  %s\n",gvtxitoa(ph_list[ph_cur]->GetCurrentIndex(),string,10));



ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoForAll - 



\return term - 

\param  cmdline - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoForAll"

logical CLIDataSource :: DoForAll (char *cmdline )
{
  CLInterpreterBase      *clip;
  CLICollection          *col;
  
  logical                 do_opt = NO;
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  if ( !ph_list[ph_cur]->IsPositioned() )
    if ( !ph_list[ph_cur]->GetRelative(0L) )         ERROR
  
  clip = interpreter;
  
  if ( (do_opt = !strcmp(cmdline,"DO")) || !strcmp(cmdline,"BEGIN") )
  {
    interpreter->ReadCommands();
    if ( do_opt )
      clip = interpreter->Push();
    col = clip->GetCollection();
    while ( col->IsPositioned() )
    {
      clip->ExecuteCommandList(NULL,0);
      col->Position(1);
    }
    if ( do_opt )
      clip->Pop();
  }
  else
    while ( ph_list[ph_cur]->IsPositioned() )
    {
      clip->ExecuteFunction(cmdline,NO);
//      clip->ExecuteListCommand();
      ph_list[ph_cur]->Position(1);
    }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoIf - 



\return term - 

\param  cmdline - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoIf"

logical CLIDataSource :: DoIf (char *cmdline )
{
  CLInterpreterBase      *clip;
  OperationHandle        *oph;
  CLICollection          *col;
  
  logical                 do_opt = NO;
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  if ( !ph_list[ph_cur]->IsPositioned() )
    if ( !ph_list[ph_cur]->Get(0L) )                 ERROR
  
  clip = interpreter;
  
  if ( (do_opt = !strcmp(cmdline,"DO")) || !strcmp(cmdline,"BEGIN") )
  {
    interpreter->ReadCommands();
    if ( do_opt )
      clip = interpreter->Push();
    col = clip->GetCollection();
    if ( !(oph = clip->GetCondition()) || oph->Execute(*col,NULL) || oph->GetResult().IsTrue() )             
      clip->ExecuteCommandList(NULL,0);
    if ( do_opt )
      clip->Pop();
  }
  else
  {
    col = clip->GetCollection();
    if ( !(oph = clip->GetCondition()) || oph->Execute(*col,NULL) || oph->GetResult().IsTrue() )             
      clip->ExecuteFunction(cmdline,NO);
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoWhile - 



\return term - 

\param  cmdline - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoWhile"

logical CLIDataSource :: DoWhile (char *cmdline )
{
  CLInterpreterBase      *clip;
  OperationHandle        *oph;
  CLICollection          *col;
  
  logical                 do_opt = NO;
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  if ( !ph_list[ph_cur]->IsPositioned() )
    if ( !ph_list[ph_cur]->Get(0L) )                 ERROR
  
  clip = interpreter;
  
  if ( (do_opt = !strcmp(cmdline,"DO")) || !strcmp(cmdline,"BEGIN") )
  {
    interpreter->ReadCommands();
    if ( do_opt )
      clip = interpreter->Push();
    col = clip->GetCollection();
    while ( col->IsPositioned() )
    {
      if ( !(oph = clip->GetCondition()) || oph->Execute(*col,NULL) || oph->GetResult().IsTrue() )             
        clip->ExecuteCommandList(NULL,0);
      else
        break;
    }
    if ( do_opt )
      clip->Pop();
  }
  else
  {
    col = clip->GetCollection();
    while ( col->IsPositioned() )
    {
      if ( !(oph = clip->GetCondition()) || oph->Execute(*col,NULL) || oph->GetResult().IsTrue() )             
        clip->ExecuteFunction(cmdline,NO);
      else
        break;
    }
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteAction - 



\return term - 

\param  act_name - 
\param  sparm_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

logical CLIDataSource :: ExecuteAction (char *act_name, char **sparm_list )
{
  char                    parms[1025];
  int                     i = 0;
  logical                 first = YES;
  logical                 term = NO;
  *parms = 0;
  while ( sparm_list[i] )
  {
    if ( !first )
      strcat(parms," ");
    strcat(parms,sparm_list[i++]);
    first = NO;
  }

  ds_handle.ExecuteDBObjectAction(act_name,parms);
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteExpression - 



\return term - 

\param  expression - OQL expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteExpression"

logical CLIDataSource :: ExecuteExpression (char *expression )
{
  DataSourceHandle       *ds_hdl;
  DBObjectHandle         *res_db = &ds_handle.GetDictionary();
  PropertyHandle          ph;
  logical                 term = NO;
  if ( (ds_hdl = ds_handle.GetDataSource()) &&
       ds_hdl->reshandle.IsOpened()            )
    res_db = &ds_hdl->reshandle;
    
  ph = ds_handle.ExecuteExpression(*res_db,expression);

  if ( ph.IsValid() )
  {
    ph_list[ph_count] = new CLICollection(this,"ExprResult",ph);
    if ( !*ph_list[ph_count]->GetName() )
    {
      Output("Error - Invalid expression result\n");
      delete ph_list[ph_count];
      ph_list[ph_count] = NULL;
    }
    else
      ph_cur = ph_last = ph_count++;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteInstanceAction - 



\return term - 

\param  act_name - 
\param  sparm_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteInstanceAction"

logical CLIDataSource :: ExecuteInstanceAction (char *act_name, char **sparm_list )
{
  char                    parms[1025];
  int                     i = 0;
  logical                 first = YES;
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR 
  
  *parms = 0;
  while ( sparm_list[i] )
  {
    if ( !first )
      strcat(parms," ");
    strcat(parms,sparm_list[i++]);
    first = NO;
  }

  ph_list[ph_cur]->ExecuteInstanceAction(act_name,parms);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecutePropertyAction - 



\return term - 

\param  act_name - 
\param  sparm_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecutePropertyAction"

logical CLIDataSource :: ExecutePropertyAction (char *act_name, char **sparm_list )
{
  char                    parms[1025];
  int                     i = 0;
  logical                 first = YES;
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR 
  
  *parms = 0;
  while ( sparm_list[i] )
  {
    if ( !first )
      strcat(parms," ");
    strcat(parms,sparm_list[i++]);
    first = NO;
  }

  ph_list[ph_cur]->ExecutePropertyAction(act_name,parms);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCollection - 



\return ph - 

\param  coll_id - Unique collection identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollection"

CLICollection *CLIDataSource :: GetCollection (int32 coll_id )
{
  CLICollection         *ph = NULL;
BEGINSEQ
  if ( !ph_count || coll_id >= ph_count )          ERROR
  
  if ( coll_id == AUTO )
    coll_id = ph_cur;
    
  if ( coll_id < 0 )
    coll_id = ph_count-1;

  if ( !ph_list[coll_id]->IsValid() )                ERROR

  ph = ph_list[coll_id];
RECOVER
  ph = NULL;
ENDSEQ
  return(ph);
}

/******************************************************************************/
/**
\brief  IsOpened - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOpened"

logical CLIDataSource :: IsOpened ( )
{

  return( id > 0 ? YES : NO);

}

/******************************************************************************/
/**
\brief  ListAttributes - 



\return term - 

\param  mask - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListAttributes"

logical CLIDataSource :: ListAttributes (char *mask )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->ListAttributes(mask);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ListCollections - 



\return term - 

\param  mask - 
\param  emp_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListCollections"

logical CLIDataSource :: ListCollections (char *mask, logical emp_opt )
{
  char                   *cname;
  int32                    indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(NO) )                        ERROR
  
  
  if ( ph_cur < 0 )
    while ( cname = ds_handle.GetExtent(indx0++) )
    {
      Output("  %s\n",cname);
    }
  else
    ph_list[ph_cur]->ListCollections(mask);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ListKeys - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListKeys"

logical CLIDataSource :: ListKeys ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->ListKeys();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ListOpenColls - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListOpenColls"

logical CLIDataSource :: ListOpenColls ( )
{
  char                   *prefix;
  int                     i = 0;
  logical                 term = NO;
  Output("List of opened collections for data source %s(%i)\n",name,id);
  
  for ( i = 0; i < ph_count; i++ )
  {
    prefix =  "-";
    if (ph_list[i]->IsPositioned()) prefix = "+";
    if ( i == ph_last ) prefix = "*";
    Output(" %s%i - %s\n",prefix,i,ph_list[i]->GetName());
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ListOrder - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListOrder"

logical CLIDataSource :: ListOrder ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->ListOrder();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Locate - 



\return term - 

\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical CLIDataSource :: Locate (char *key_value )
{
  int                     ph_num = ph_count-1;
  int32                    position = AUTO;
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  if ( key_value && *key_value )
    ph_list[ph_cur]->Locate(key_value);
  DisplayKey();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Move - 



\return term - 

\param  source_ds - 
\param  old_key - 
\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

logical CLIDataSource :: Move (CLIDataSource *source_ds, char *old_key, char *key_value )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  if ( source_ds->CheckCollection(YES) )             ERROR
  
  ph_list[ph_cur]->Move(source_ds->GetCollection(AUTO),old_key,key_value);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Output - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  fstring - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CLIDataSource :: Output (char *fstring, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{

  return(interpreter->Output(fstring,parm1,parm2,parm3,parm4,parm5));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  fstring - 
\param  intval - 
\param  parm1 - 
\param  parm2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CLIDataSource :: Output (char *fstring, int32 intval, char *parm1, char *parm2 )
{

  return(interpreter->Output(fstring,intval,parm1,parm2));

}

/******************************************************************************/
/**
\brief  i02 - 



\param  fstring - 
\param  parm0 - 
\param  intval - 
\param  parm2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CLIDataSource :: Output (char *fstring, char *parm0, int32 intval, char *parm2 )
{

  return(interpreter->Output(fstring,parm0,intval,parm2));

}

/******************************************************************************/
/**
\brief  Position - 



\return term - 

\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical CLIDataSource :: Position (int32 count )
{
  int                     ph_num = ph_count-1;
  int32                    position = AUTO;
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  if ( ph_list[ph_cur]->Position(count) )
    Output("Error - Could not locate instance at requested position\n");
  else 
    DisplayKey();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Print - 



\return term - 

\param  fstring - 
\param  sparm_list - 
\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical CLIDataSource :: Print (char *fstring, char **sparm_list, int32 count )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  if ( !fstring )
    Output("Error - missing format string for print command\n");
  else
  {
    STRExchange(fstring,"\\n","\n",UNDEF); 
    STRExchange(fstring,"\\r","\r",UNDEF); 
    STRExchange(fstring,"\\t","\t",UNDEF); 
    Output(ph_list[ph_cur]->Format(fstring,sparm_list,count));
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RecreateExtent - 



\return term - 

\param  ext_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecreateExtent"

logical CLIDataSource :: RecreateExtent (char *ext_names )
{
  logical                 term = NO;
  if ( ds_handle.GetDBHandle().RecreateExtent(ext_names) )
    Output("  Could not recreate extent '%s'\n",ext_names);
  else
    Output("  Extent '%s' recreated successfully\n",ext_names);

  return(term);
}

/******************************************************************************/
/**
\brief  RollBack - 



\return term - 

\param  all_ta - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RollBack"

logical CLIDataSource :: RollBack (logical all_ta )
{
  logical                 term = NO;
BEGINSEQ
  if ( ds_handle.RollBack(all_ta ? 1 : AUTO) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RunQuery - 



\return term - 

\param  expression - OQL expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RunQuery"

logical CLIDataSource :: RunQuery (char *expression )
{
  DataSourceHandle       *ds_hdl;
  DBObjectHandle         *res_db = &ds_handle.GetDictionary();
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(NO) )                       LEAVESEQ
  
  if ( !expression )
  {
    interpreter->ReadCommands();
    expression = interpreter->GetOQLCommand(NULL);
  }
    
  if ( !expression || !*expression )                LEAVESEQ
    
  ph_cur = ph_count-1;
    
  if ( !ds_handle.IsOpened() )
    Output("No data source opened. Open data source with cd-command\n");
  else
  {
    PropertyHandle      ph;
    
    if ( (ds_hdl = ds_handle.GetDataSource()) &&
         ds_hdl->reshandle.IsOpened()            )
      res_db = &ds_hdl->reshandle;
    ph = ph_count   
         ? ph_list[ph_count-1]->ExecuteExpression(*res_db,expression)
         : ds_handle.ExecuteExpression(*res_db,expression);
    
    if ( ph.IsValid() )
    {  
      ph_list[ph_count] = new CLICollection(this,"oql",ph);
      ph_cur = ph_last = ph_count++;
    }    
//    else
//    {
//      printf("Error - Invalid query '%s'\n",expression);
//      delete ph_list[ph_count];
//      ph_list[ph_count] = NULL;
//    }
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Select - 



\return term - 

\param  expression - OQL expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Select"

logical CLIDataSource :: Select (char *expression )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->SetSelection(expression);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPropertyHandle - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyHandle"

logical CLIDataSource :: SetPropertyHandle (PropertyHandle &prophdl )
{
  logical                 term = NO;
  while ( ph_count > 1 )
    CloseCollection();
  
  if ( !ph_count || !ph_list[0] )
    ph_list[0] = new CLICollection(this,prophdl,NULL);
  else
    ph_list[0]->SetPropertyHandle(prophdl);
  
  ph_cur = ph_last = 0;
  ph_count = 1;

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyHandle"

logical CLIDataSource :: SetPropertyHandle (PropertyHandle *ph_ptr )
{
  PropertyHandle         *ph;
  logical                 term = NO;
// geht nur für neue DataSources (ohne PHs)
  if ( ph = ph_ptr->GetParentProperty() )
    SetPropertyHandle(ph);
    
  ph_list[ph_count] = new CLICollection(this,ph_ptr);
  
  ph_cur = ph_last = ph_count;
  ph_count++;

  return(term);
}

/******************************************************************************/
/**
\brief  SetValue - 



\return term - 

\param  assignment - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical CLIDataSource :: SetValue (char *assignment )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  
  ph_list[ph_cur]->SetValue(assignment);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Unselect - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unselect"

logical CLIDataSource :: Unselect ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckCollection(YES) )                        ERROR
  ph_list[ph_cur]->ResetSelection();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~CLIDataSource - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CLIDataSource"

     CLIDataSource :: ~CLIDataSource ( )
{

  while ( ph_count-- )
  {
    delete ph_list[ph_count];
    ph_list[ph_count] = NULL;
  }

}


