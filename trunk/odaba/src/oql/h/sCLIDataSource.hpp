/********************************* Class Declaration ***************************/
/**
\package  OQL - 
\class    CLIDataSource

\brief    


\date     $Date: 2006/08/28 14:24:14,57 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CLIDataSource_HPP
#define   CLIDataSource_HPP

class     CLIDataSource;

class     CLICollection;
class     CLIDataSource;
class     CLInterpreter;
class     CLInterpreterBase;
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  CLIDataSource
{
protected  :         int32                                        id;                                                        // 
protected  :         char                                         name[129];                                                 // 
protected  :         CLInterpreterBase                           *interpreter;                                               // 
protected  :         DBObjectHandle                               ds_handle;                                                 // 
protected  :         NString                                      cur_path;                                                  // 
protected  :         CLICollection                               *ph_list[100];                                              // 
protected  :         int32                                        ph_count;                                                  // 
protected  :         int32                                        ph_cur;                                                    // 
protected  :         int32                                        ph_last;                                                   // 

public     :
                     int32                                        get_id() { return(id); }
                     char                                        *get_name() { return(name); }
                     CLInterpreterBase                           *get_interpreter() { return(interpreter); }
                     DBObjectHandle                              &get_ds_handle() { return(ds_handle); }
                     NString                                     &get_cur_path() { return(cur_path); }
                     int32                                        get_ph_count() { return(ph_count); }
                     int32                                        get_ph_cur() { return(ph_cur); }
                     int32                                        get_ph_last() { return(ph_last); }
public     :                                        logical AttributeList (char **attributes, logical append );
public     :                                        logical BeginTransaction (logical ext_TA=NO, char *w_maxnumstr=NULL );
public     :                                             CLIDataSource (CLInterpreterBase *clipbase, ODABAClient &odaba_client, char *dsname, int32 ds_id );
public     :                                             CLIDataSource (CLInterpreterBase *clipbase, CLIDataSource *source_ds, int32 ds_id );
public     :                                             CLIDataSource (CLInterpreterBase *clipbase, ODABAClient &odaba_client, DBObjectHandle &dbohandle, char *dsname, int32 ds_id );
public     :                                        logical ChangeCollection (char *prop_path );
public     :                                        logical ChangeOrder (char *key_name );
public     :                                        logical CheckCollection (logical msg_opt );
public     :                                        logical CloseCollection ( );
public     :                                        logical CommitTransaction (logical all_ta );
public     :                                        logical Copy (CLIDataSource *source_ds, char *old_key, char *key_value );
public     :                                        logical CopyContext (CLIDataSource *ds_context );
public     :                                        logical Create (char *key_value );
public     :                                        DatabaseHandle &DBHandle ( );
public     :                                        logical Delete (char *mask, logical err_del );
public     :                                        logical DeleteExtent (char *ext_names );
public     :                                        logical DeleteExtentRef (char *ext_names );
public     :                                        DictionaryHandle &DictHandle ( );
public     :                                        logical DisplayCollection ( );
public     :                                        logical DisplayKey ( );
public     :                                        logical DoForAll (char *cmdline );
public     :                                        logical DoIf (char *cmdline );
public     :                                        logical DoWhile (char *cmdline );
public     :                                        logical ExecuteAction (char *act_name, char **sparm_list );
public     :                                        logical ExecuteExpression (char *expression );
public     :                                        logical ExecuteInstanceAction (char *act_name, char **sparm_list );
public     :                                        logical ExecutePropertyAction (char *act_name, char **sparm_list );
public     :                                        CLICollection *GetCollection (int32 coll_id );
public     :                                        logical IsOpened ( );
public     :                                        logical ListAttributes (char *mask );
public     :                                        logical ListCollections (char *mask, logical emp_opt );
public     :                                        logical ListKeys ( );
public     :                                        logical ListOpenColls ( );
public     :                                        logical ListOrder ( );
public     :                                        logical Locate (char *key_value );
public     :                                        logical Move (CLIDataSource *source_ds, char *old_key, char *key_value );
public     :                                        logical Output (char *fstring, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                                        logical Output (char *fstring, int32 intval, char *parm1=NULL, char *parm2=NULL );
public     :                                        logical Output (char *fstring, char *parm0, int32 intval, char *parm2=NULL );
public     :                                        logical Position (int32 count );
public     :                                        logical Print (char *fstring, char **sparm_list, int32 count );
public     :                                        logical RecreateExtent (char *ext_names );
public     :                                        logical RollBack (logical all_ta );
public     :                                        logical RunQuery (char *expression );
public     :                                        logical Select (char *expression );
public     :                                        logical SetPropertyHandle (PropertyHandle &prophdl );
public     :                                        logical SetPropertyHandle (PropertyHandle *ph_ptr );
public     :                                        logical SetValue (char *assignment );
public     :                                        logical Unselect ( );
public     :                                             ~CLIDataSource ( );
};

#pragma pack()
#endif
