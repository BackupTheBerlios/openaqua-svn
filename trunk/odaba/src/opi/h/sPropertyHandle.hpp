/********************************* Class Declaration ***************************/
/**
\package  OPI - 
\class    PropertyHandle

\brief    Property Handle
          Property  handle are used  to handle persistent  or transient {\b data
          source}.  A  data  source  is  a  collection,  object  instance  or an
          elementary  database  field.  A  data  source  contains the data for a
          property of a specific object.
          A  property handle  usually handles  a collection of subsequent object
          instance.  In  special  cases  the  collection  is  singular (e.g. the
          'direction'  for a  persion is  exactly one 'Adress' object instance).
          In  other cases the instance is elementary (as eg the given names of a
          person). 
          A  property handle has a cursor function  that allows to select one of
          the  instances in the collection as  the "current" instance. Only from
          the  selected instance  you can  retrieve data  by means of subsequent
          property  handles or  Get-functions (GetString(),  GetTime(), ...) for
          elementary datasources. 

          {\b Generic Property handles}

          You  can  define  generic  property handles using the generic property
          handle  contructor (PH(type)()). This requires that you have created a
          C++  header file for the referenced type.  In this case you can access
          elementary  data  field  in  the  instance  directly  referring to the
          generated  class  members.  For  references  the  instance  contains 
          corresponding  generic  property  handles  that  you  can reference by
          class  member name  as well.  In this  case you need not to create the
          property  handle  you  want  to access. This makes programming simpler
          but  in this case you must recompile the application when changing the
          database  structure. This is not  necessary when referring to property
          handles hierarchies created in the appplication.  

          {\b Property handle hierarchies}

          Property  handles  form  a  tree  that  defines  a specific view in an
          application.  When defining  this view  once the property handles cann
          be  used  as  long  as  the application follows the defined view. When
          defining  a property  handle for  "AllPersons", which  is an extent in
          the  database,  you  can  define  sub-ordinated  property  handles for
          'name',  'children', and  'company', which  refer to the persons name,
          its  children  and  the  company  the  person  is  working  for.  When
          selecting  another  person  in  the  AllPerson  property  handle  the 
          datasources  for 'name',  'children' and  'company' will change. This,
          however,  is  maintained  automatically  by  the  systen,  i.e.  when 
          changing  the selection in  an upper property  handle the data sources
          for  all subordinated  property handles  are updated automatically and
          you can access them directly. 

          {\b Filter and temporaty datasources}

          Usually  a property handle shows all the elements that have been added
          to  the data source. You can  restrict the number of visible instances
          by  setting  a  filter  (SetSelection())  using an expression or a C++
          function.  You can  also create  a new  data source using the Select()
          function which creates a temporary data source. 

          {\b Operations with Property handles}

          Property  handes  provide  all  algebraic  and set operations. You can
          apply  most of algebraic  operations  (as +,  -, * etc.) on elementary
          {\u  and} collection  data sources.  In this  case eg the '-' operator
          corresponds  to  the  relational  Minus()  operation.  In  most cases,
          however,  the types  of operands  must be  comparable. You can compare
          string  data  with  numeric  data  but  you  cannot  compare  a person
          collection with a date field. 
          Set  operations  are  defined  on the operations defined in relational
          algebra  (Intersection, Union, Minus, Select) rather that by using SQL
          like Select statements.

\date     $Date: 2006/08/29 20:24:05,12 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PropertyHandle_HPP
#define   PropertyHandle_HPP

class     PropertyHandle;
#include "copadll.h"

#define  GetHighProperty                           GetParentProperty
#define  ReplaceSysVar                             ReplaceSysVariables
#define  Tnodeptr                                  nodeptr->GetNode(YES)
class     ACObject;
class     BNFData;
class     CSA_Handle;
class     CTX_Property;
class     CTX_Structure;
class     DBFieldDef;
class     OPBase;
class     OperEnvironment;
class     OperationHandle;
class     ParmList;
class     PropertyHandle;
class     SDB_Member;
class     SimpleAction;
class     fmcb;
class     node;
class     smcb;
#include  <cOperationTypes.h>
#include  <cPIACC.h>
#include  <cPIADEF.h>
#include  <cPIREPL.h>
#include  <cSDB_RLEV.h>
#include  <cST_OpCodes.h>
#include  <sDBObjectHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sEventLink.hpp>
#include  <sInstance.hpp>
#include  <sKeyClass.hpp>
#pragma pack(8)

class  PropertyHandle
{
protected  :         node                                        *nodeptr;                                                   // 

public     :
public     :                  OPIImpExp             Instance Add (int32 set_pos0, Key sortkey, Key identkey_w=Key() );
public     :                  OPIImpExp             Instance Add (Key sortkey, Key identkey_w=Key() );
public     :                  OPIImpExp             Instance Add (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             Instance Add (int32 set_pos0_w=AUTO, logical init_inst=YES );
public     :                  OPIImpExp             Instance Add (Instance newinst, int32 set_pos0_w=AUTO );
public     :                  OPIImpExp             Instance Add (Key sortkey, Key ident_key, Instance instance, logical init_inst=YES );
public     :                  OPIImpExp             Instance Add (int32 set_pos0, Key sortkey, Key ident_key, Instance instance, logical init_inst=YES );
public     :                  OPIImpExp             Instance AddGlobal (int32 set_pos0, Key sortkey, Key identkey_w=Key(), logical init_inst=YES );
public     :                  OPIImpExp             Instance AddGlobal (Key sortkey, Key identkey_w=Key(), logical init_inst=YES );
public     :                  OPIImpExp             Instance AddGlobal (int32 set_pos0_w=AUTO, logical init_inst=YES );
public     :                  OPIImpExp             Instance AddGlobal (Instance newinst, int32 set_pos0_w=AUTO );
public     :                  OPIImpExp             Instance AddGlobal (Key sortkey, Key ident_key, Instance instance, logical init_inst=YES );
public     :                  OPIImpExp             Instance AddGlobal (int32 set_pos0, Key sortkey, Key identkey_w=Key(), Instance newitp_w=Instance(), logical init_inst=YES );
public     :                  OPIImpExp             logical AddReference (PropertyHandle &source_handle, int32 set_pos0_w=AUTO );
public     :                                        Instance Add_intern (int32 indx0, Key sort_key, Key ident_key, Instance newinst, logical init_inst=YES, logical global_add=NO );
public     :                  OPIImpExp             logical AllocDescription ( );
public     :                  OPIImpExp             logical AllocDescription (DatabaseHandle &dbhandle, char *fldnames, char *fldtypes, SDB_RLEV ref_level, uint32 size, uint16 precision, uint32 dimension );
public     :                  OPIImpExp             logical AllocateArea ( );
public     :                  OPIImpExp             logical AppendString (char *string );
public     :                  OPIImpExp             logical AutoLocate (char chkopt=AUTO );
public     :                  OPIImpExp             logical Cancel ( );
public     :                  OPIImpExp             logical CancelBuffer ( );
public     :                  OPIImpExp             int16 ChangeBuffer (int16 buffnum=AUTO );
public     :                  OPIImpExp             logical ChangeCache (int16 buffnum=AUTO );
public     :                  OPIImpExp             PIACC ChangeMode (PIACC newmode );
public     :                  OPIImpExp             logical Check (logical ini_opt=NO );
public     :                                        logical CheckPosition ( );
public     :                                        logical CheckUpdate (logical check_update=YES );
public     :                  OPIImpExp             logical CheckWProtect ( );
public     :                  OPIImpExp             logical Close ( );
public     :                                        int16 Compare (const PropertyHandle &cprop_hdl );
public     :                                        int16 Compare (dbdt date_val );
public     :                                        int16 Compare (double double_val );
public     :                                        int16 Compare (int32 long_val );
public     :                                        int16 Compare (char *string );
public     :                                        int16 Compare (dbtm time_val );
public     :                  OPIImpExp             int8 CompareKey (Key ident_key1, Key ident_key2 );
public     :                  OPIImpExp             int8 CompareSortKey (Key sort_key1, Key sort_key2 );
public     :                  OPIImpExp             logical CompareType (PropertyHandle &prop_hdl, logical convert );
public     :                  OPIImpExp             logical Contains (char *reg_string, logical case_opt=YES, logical conv_opt=NO );
public     :                  OPIImpExp             logical Contains (char *reg_string, char *prop_path, logical case_opt=YES, logical conv_opt=NO );
public     :                  OPIImpExp             logical ConvertToWinChar ( );
public     :                  OPIImpExp             Instance Copy (PropertyHandle &source_handle, PIREPL replopt=REPL_none, PIREPL copy_type=REPL_all );
public     :                  OPIImpExp             Instance Copy (PropertyHandle &source_handle, Key new_key, PIREPL replopt=REPL_none, PIREPL copy_type=REPL_all );
public     :                  OPIImpExp             Instance Copy (PropertyHandle &source_handle, int32 set_pos0, PIREPL replopt=REPL_none, PIREPL copy_type=REPL_all );
public     :                  OPIImpExp             Instance Copy (PropertyHandle &source_handle, Key new_key, int32 set_pos0, PIREPL replopt=REPL_none, PIREPL copy_type=REPL_all );
public     :                  OPIImpExp             logical CopyData (Instance instance, logical switchopt=NO );
public     :                  OPIImpExp             logical CopyData (PropertyHandle &source_handle, PIREPL replopt=REPL_none );
public     :                  OPIImpExp             logical CopyDescription (DBFieldDef *prop_def );
public     :                  OPIImpExp             logical CopyHandle (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical CopyHandle (PropertyHandle *property_handle );
public     :                  OPIImpExp             Instance CopyInst (Instance srceinst, smcb *srcesmcb, PIREPL replopt=REPL_none, PIREPL copy_type=REPL_all );
public     :                  OPIImpExp             logical CopyInstance (Instance instance );
public     :                                        logical CopyInstanceArea (PropertyHandle &prophdl );
public     :                  OPIImpExp             int32 CopySet (const PropertyHandle &csource_handle, PIREPL replopt=REPL_none, PIREPL copy_type=REPL_all, logical inverse_check=NO );
public     :                                        logical CreatePIHandle (PropertyHandle **pi_liste, int32 count, int16 operation, char sk_opt=YES, logical transient_w=NO, char *key_name_w=NULL );
public     :                                        logical CreatePIHandle (DBObjectHandle &obhandle, DBFieldDef *dbfielddef );
public     :                                        logical CreatePIHandle (PropertyHandle &pibref );
public     :                                        logical CreatePIHandle (PropertyHandle &pibref, char *grouping_rule );
public     :                  OPIImpExp             logical CreateTempExtent (DBObjectHandle &obhandle );
public     :                  OPIImpExp             logical CreateTempExtent (PropertyHandle &prophdl_ref, char *extnames_w=NULL );
public     :                  OPIImpExp             logical Delete (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical Delete (Key sort_key );
public     :                  OPIImpExp             logical Delete (int32 set_pos0_w=AUTO, logical del_dep=YES, logical del_inst=NO );
public     :                  OPIImpExp             logical DeleteIndexEntry (int32 set_pos0 );
public     :                  OPIImpExp             logical DeleteSet (logical del_dep=YES );
public     :                  OPIImpExp             PropertyHandle *Dereference ( );
public     :                                        logical DisableKeyCheck ( );
public     :                  OPIImpExp             PropertyHandle &Distinct (PropertyHandle &prophdl_ref, char *key_name_w=NULL );
public     :                  OPIImpExp             PropertyHandle &Distinct (char *key_name_w=NULL );
public     :                  OPIImpExp             PropertyHandle &Distinct (PropertyHandle &prophdl_ref, char *key_name, ExecutionTypes exectype );
public     :                  OPIImpExp             Instance Duplicate (int32 set_pos0, PIREPL replopt=REPL_none );
public     :                  OPIImpExp             Instance Duplicate (Key ident_key, PIREPL replopt=REPL_none );
public     :                                        logical EnableKeyCheck ( );
public     :                  OPIImpExp             logical Execute (ParmList *parmlist );
public     :                  OPIImpExp             logical Execute ( );
public     :                  OPIImpExp             PropertyHandle ExecuteExpression (DBObjectHandle &res_obhandle, char *expression );
public     :                  OPIImpExp             PropertyHandle ExecuteExpression (DBObjectHandle &res_obhandle, DBObjectHandle &obhandle, char *expression );
public     :                  OPIImpExp             logical ExecuteInstanceAction (char *action_name, char *parm_string );
public     :                  OPIImpExp             logical ExecutePropertyAction (char *action_name, char *parm_string );
public     :                  OPIImpExp             logical Exist ( ) const;
public     :                  OPIImpExp             Key ExtractKey (Key ident_key_w=Key(), Instance instance_w=Instance() );
public     :                  OPIImpExp             Key ExtractKey (char *key_name, Key key, Instance instance_w=Instance() );
public     :                  OPIImpExp             Key ExtractKey (char *key_name );
public     :                  OPIImpExp             Key ExtractSortKey (Key sort_key, Instance instance );
public     :                  OPIImpExp             Key ExtractSortKey (Key sort_key_w=Key() );
public     :                  OPIImpExp             logical Fill (Instance instance );
public     :                  OPIImpExp             logical FillData (Instance instance );
public     :                  OPIImpExp             Key FirstKey ( );
public     :                  OPIImpExp             char *Format (char *fstring, char **parm_list, int16 parm_count );
public     :                  OPIImpExp             Instance Get (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             Instance Get (int32 set_pos0_w=AUTO );
public     :                  OPIImpExp             Instance Get (Key sort_key );
public     :                  OPIImpExp             char *GetActionResult ( );
public     :                  OPIImpExp             char *GetArea (char chkopt=AUTO ) const;
public     :                  OPIImpExp             char *GetArea (char *prop_path, char chkopt=AUTO ) const;
public     :                  OPIImpExp             char *GetAttribute (int32 indx0, logical full_path=YES, logical generic=YES );
public     :                  OPIImpExp             PropertyHandle *GetBaseProperty ( );
public     :                                        Instance GetBufferInstance (int32 indx0 );
public     :                  OPIImpExp             int32 GetCollectionID ( );
public     :                  OPIImpExp             PropertyHandle *GetCollectionProperty ( );
public     :                  OPIImpExp             int32 GetCount ( );
public     :                  OPIImpExp             int32 GetCurrentIndex ( );
public     :                  OPIImpExp             uint32 GetCurrentSize ( );
public     :                  OPIImpExp             char *GetCurrentType ( );
public     :                  OPIImpExp             DBStructDef *GetCurrentTypeDef ( );
public     :                  OPIImpExp             PropertyHandle GetDBField (char *prop_path );
public     :                  OPIImpExp             DatabaseHandle &GetDBHandle ( );
public     :                  OPIImpExp             dbdt GetDate ( );
public     :                  OPIImpExp             dbdt GetDate (char *prop_path );
public     :                  OPIImpExp             dttm GetDateTime ( );
public     :                  OPIImpExp             dttm GetDateTime (char *prop_path );
public     :                  OPIImpExp             int32 GetDay ( );
public     :                  OPIImpExp             int32 GetDay (char *prop_path );
public     :                  OPIImpExp             DBFieldDef *GetDescription (char chkopt=AUTO ) const;
public     :                  OPIImpExp             DictionaryHandle &GetDictionary ( );
public     :                  OPIImpExp             int32 GetDimension ( ) const;
public     :                  OPIImpExp             double GetDouble ( );
public     :                  OPIImpExp             double GetDouble (char *prop_path );
public     :                  OPIImpExp             int16 GetExtInstModCount (int32 objid );
public     :                  OPIImpExp             int16 GetExtInstModCount ( );
public     :                  OPIImpExp             char *GetExtentName ( );
public     :                  OPIImpExp             fld *GetField ( );
public     :                  OPIImpExp             DBFieldDef *GetFieldDef ( );
public     :                  OPIImpExp             char *GetGUID ( );
public     :                  OPIImpExp             int32 GetGenAttrType (char *w_propnames=NULL );
public     :                  OPIImpExp             int32 GetGenOrderType ( );
public     :                  OPIImpExp             int64 GetGlobalID ( );
public     :                  OPIImpExp             int64 GetGlobalID (Key skey );
public     :                  OPIImpExp             char *GetHierarchyPath ( );
public     :                  OPIImpExp             int32 GetHours ( );
public     :                  OPIImpExp             int32 GetHours (char *prop_path );
public     :                  OPIImpExp             uint64 GetID (int32 set_pos0_w=AUTO );
public     :                  OPIImpExp             uint64 GetID (Key sort_key );
public     :                  OPIImpExp             char *GetIdentity (char *id_string );
public     :                  OPIImpExp             char *GetIndexName (int32 indx0 );
public     :                  OPIImpExp             Instance GetInitArea ( );
public     :                  OPIImpExp             Instance GetInitInstance ( );
public     :                                        Instance GetInst (char *extinst );
public     :                  OPIImpExp             int16 GetInstModCount ( );
public     :                  OPIImpExp             Instance GetInstance ( ) const;
public     :                  OPIImpExp             CTX_Structure *GetInstanceContext ( );
public     :                  OPIImpExp             int32 GetInt ( );
public     :                  OPIImpExp             int32 GetInt (char *prop_path );
public     :                  OPIImpExp             int32 GetIntValue ( );
public     :                  OPIImpExp             int32 GetIntValue (char *prop_path );
public     :                  OPIImpExp             Key GetKey (int32 set_pos0_w=AUTO );
public     :                                        Key GetKeyFromParm (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             int16 GetKeyLength ( );
public     :                  OPIImpExp             smcb *GetKeySMCB (char *key_name_w=NULL );
public     :                  OPIImpExp             int64 GetLOID (int32 set_pos0_w=AUTO );
public     :                  OPIImpExp             int64 GetLOID (Key sort_key );
public     :                  OPIImpExp             int32 GetMinutes ( );
public     :                  OPIImpExp             int32 GetMinutes (char *prop_path );
public     :                  OPIImpExp             PIACC GetMode ( );
public     :                  OPIImpExp             int32 GetMonth ( );
public     :                  OPIImpExp             int32 GetMonth (char *prop_path );
public     :                                        node *GetNode ( );
public     :                  OPIImpExp             int32 GetNormalized ( );
public     :                                        OPBase *GetOPNode ( );
public     :                  OPIImpExp             DBObjectHandle &GetObjectHandle ( );
public     :                  OPIImpExp             int64 GetOrigin ( );
public     :                  OPIImpExp             PropertyHandle *GetParentProperty ( );
public     :                  OPIImpExp             PropertyHandle *GetPathElement (char *path_element );
public     :                  OPIImpExp             PIADEF GetPrivilege ( );
public     :                  OPIImpExp             CTX_Property *GetPropertyContext ( );
public     :                  OPIImpExp             PropertyHandle *GetPropertyHandle (char *prop_path, logical *is_transient );
public     :                  OPIImpExp             PropertyHandle *GetPropertyHandle (char *prop_path );
public     :                  OPIImpExp             char *GetPropertyPath ( );
public     :                  OPIImpExp             int16 GetRefModCount ( );
public     :                  OPIImpExp             char *GetReference (int32 indx0, logical full_path=YES, logical generic=YES );
public     :                  OPIImpExp             Instance GetRelative (int32 set_pos0_w=AUTO );
public     :                  OPIImpExp             int32 GetRelativeCount ( );
public     :                  OPIImpExp             int32 GetRelativeIndex (logical last_opt );
public     :                  OPIImpExp             int32 GetSeconds ( );
public     :                  OPIImpExp             int32 GetSeconds (char *prop_path );
public     :                  OPIImpExp             Key GetSelectedKey ( );
public     :                  OPIImpExp             int32 GetSize ( );
public     :                  OPIImpExp             int32 GetSizeOf ( );
public     :                  OPIImpExp             char *GetSortKey ( );
public     :                  OPIImpExp             int16 GetSortKeyLength ( );
public     :                  OPIImpExp             smcb *GetSortKeySMCB ( );
public     :                  OPIImpExp             char *GetString ( );
public     :                  OPIImpExp             char *GetString (char *prop_path );
public     :                  OPIImpExp             uint32 GetStringLength ( );
public     :                  OPIImpExp             char *GetStringValue ( );
public     :                  OPIImpExp             char *GetStringValue (char *prop_path );
public     :                  OPIImpExp             DBStructDef *GetStructDef ( ) const;
public     :                  OPIImpExp             char *GetSubString (int32 start_pos, int32 length=AUTO );
public     :                                        node *GetTNode ( );
public     :                  OPIImpExp             char *GetText ( );
public     :                  OPIImpExp             char *GetText (char *prop_path );
public     :                  OPIImpExp             dbtm GetTime ( );
public     :                  OPIImpExp             dbtm GetTime (char *prop_path );
public     :                  OPIImpExp             char *GetType ( );
public     :                                        logical GetValid ( );
public     :                  OPIImpExp             Instance GetValue (int32 lindx0 );
public     :                  OPIImpExp             uint16 GetVersion ( );
public     :                  OPIImpExp             int32 GetYear ( );
public     :                  OPIImpExp             int32 GetYear (char *prop_path );
public     :                                        PropertyHandle &Group (PropertyHandle &prophdl_ref, char *grouping_rule, logical distinct=NO );
public     :                  OPIImpExp             logical HasData ( );
public     :                  OPIImpExp             logical HasDescription ( );
public     :                  OPIImpExp             logical HasGenericAttributes ( );
public     :                  OPIImpExp             logical HasIndex ( );
public     :                  OPIImpExp             logical Inherits (char *strnames );
public     :                  OPIImpExp             logical Inherits (PropertyHandle &prophdl );
public     :                  OPIImpExp             PropertyHandle *InitPropertyHandle (char *prop_path, PropertyHandle *property_handle );
public     :                  OPIImpExp             logical InitResult (PropertyHandle &operand1, PropertyHandle &operand2 );
public     :                  OPIImpExp             logical InitResult (DictionaryHandle &dictptr, char *type, uint32 size, uint16 precision );
public     :                                        logical InitValue (DictionaryHandle &dicthdl, PropertyHandle *co, ParmList *variables, ParmList *parameters );
public     :                  OPIImpExp             logical Initialize (Instance instance_w=Instance() );
public     :                  OPIImpExp             logical InsertString (char *string, int32 position );
public     :                  OPIImpExp             logical InsertTerminator (char *string );
public     :                  OPIImpExp             logical InstanceInserted ( ) const;
public     :                  OPIImpExp             char *InstanceToString (char *string_sep, char *field_sep, char *block_sep, char *empty_string, logical skip_trans=NO );
public     :                  OPIImpExp             PropertyHandle &Intersect (PropertyHandle &prop_hdl1, PropertyHandle &prop_hdl2, char sk_opt=YES );
public     :                  OPIImpExp             PropertyHandle &Intersect (PropertyHandle **ph_list, int32 count, char sk_opt=YES );
public     :                  OPIImpExp             PropertyHandle &Intersect (PropertyHandle &prophdl_ref, char sk_opt=YES );
public     :                  OPIImpExp             logical Is (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical IsA (char *strnames );
public     :                  OPIImpExp             logical IsActive ( ) const;
public     :                  OPIImpExp             logical IsAttribute ( ) const;
public     :                  OPIImpExp             logical IsAutoSelection ( ) const;
public     :                  OPIImpExp             logical IsBasedOn (char *strnames ) const;
public     :                  OPIImpExp             logical IsBasetypeProperty ( ) const;
public     :                  OPIImpExp             logical IsBasicType ( ) const;
public     :                  OPIImpExp             logical IsClient ( ) const;
public     :                  OPIImpExp             logical IsCollection (char chkopt=AUTO ) const;
public     :                  OPIImpExp             logical IsCollectionUpdate ( ) const;
public     :                  OPIImpExp             logical IsCopyHandle ( ) const;
public     :                  OPIImpExp             logical IsDirty ( );
public     :                  OPIImpExp             logical IsEmpty ( ) const;
public     :                  OPIImpExp             logical IsEnumeration ( ) const;
public     :                  OPIImpExp             logical IsGenericAttribute ( );
public     :                  OPIImpExp             logical IsInitInstance ( ) const;
public     :                  OPIImpExp             logical IsMemo (char chkopt=AUTO ) const;
public     :                  OPIImpExp             logical IsModified ( );
public     :                  OPIImpExp             logical IsNewInstance ( ) const;
public     :                  OPIImpExp             logical IsNumeric ( ) const;
public     :                  OPIImpExp             logical IsOldInstance ( ) const;
public     :                  OPIImpExp             logical IsOwner ( );
public     :                  OPIImpExp             logical IsPathExpression ( );
public     :                  OPIImpExp             logical IsPositioned (char chkopt=AUTO ) const;
public     :                  OPIImpExp             logical IsReadOnly ( ) const;
public     :                  OPIImpExp             logical IsSelected (char chkopt=AUTO ) const;
public     :                  OPIImpExp             logical IsSensitive ( ) const;
public     :                  OPIImpExp             logical IsSensitive (char *prop_path ) const;
public     :                  OPIImpExp             logical IsServer ( ) const;
public     :                  OPIImpExp             logical IsShareBaseHandle (char chkopt=AUTO ) const;
public     :                  OPIImpExp             logical IsStructure ( ) const;
public     :                  OPIImpExp             logical IsText (char chkopt=AUTO ) const;
public     :                  OPIImpExp             logical IsTransient ( ) const;
public     :                  OPIImpExp             logical IsTrue ( ) const;
public     :                  OPIImpExp             logical IsTrue (char *prop_path ) const;
public     :                  OPIImpExp             logical IsTyped ( ) const;
public     :                  OPIImpExp             logical IsUserHandle ( ) const;
public     :                  OPIImpExp             logical IsValid (logical topt=YES ) const;
public     :                  OPIImpExp             logical IsValidText (char *string ) const;
public     :                  OPIImpExp             logical IsVariableType ( );
public     :                  OPIImpExp             logical IsWeakTyped ( ) const;
public     :                  OPIImpExp             logical IsWrite ( ) const;
public     :                  OPIImpExp             char *KeyToString (Key key_string, Key key_val, char *key_name_w=NULL );
public     :                  OPIImpExp             logical Locate (int64 obident, logical read_opt=YES );
public     :                  OPIImpExp             logical LocateIndex (int32 set_pos0 );
public     :                  OPIImpExp             logical LocateIndex (PropertyHandle &prop_hdl, logical exact_w=YES );
public     :                  OPIImpExp             logical LocateKey (Key sort_key, logical exact_w=YES );
public     :                  OPIImpExp             logical LocateKey (PropertyHandle &prop_hdl, logical exact_w=YES );
public     :                  OPIImpExp             logical LocatePath ( );
public     :                  OPIImpExp             logical Lock ( );
public     :                  OPIImpExp             logical LockSet ( );
public     :                  OPIImpExp             void MarkUnused ( );
public     :                  OPIImpExp             void MarkUsed ( );
public     :                  OPIImpExp             PropertyHandle &Minus (PropertyHandle &prop_hdl1, PropertyHandle &prop_hdl2, char sk_opt=YES );
public     :                  OPIImpExp             PropertyHandle &Minus (PropertyHandle &prophdl_ref, char sk_opt=YES );
public     :                  OPIImpExp             logical Modify ( );
public     :                  OPIImpExp             Instance Move (PropertyHandle &source_handle, PIREPL replopt=REPL_none );
public     :                  OPIImpExp             Instance Move (PropertyHandle &source_handle, Key new_key, PIREPL replopt=REPL_none );
public     :                  OPIImpExp             logical MoveDown ( );
public     :                  OPIImpExp             logical MoveUp ( );
public     :                  OPIImpExp             Key NextKey (Key sort_key_w=Key(), int16 switch_level=AUTO );
public     :                  OPIImpExp             logical NoWrite ( );
public     :                  OPIImpExp             logical Open ( );
public     :                  OPIImpExp             logical Open (int64 int64_val );
public     :                  OPIImpExp             logical Open (logical logval );
public     :                  OPIImpExp             logical Open (PropertyHandle &prop_hdl, char *prop_path );
public     :                  OPIImpExp             logical Open (PropertyHandle *property_handle, char *prop_path );
public     :                  OPIImpExp             logical Open (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             logical Open (dbdt date_val );
public     :                  OPIImpExp             logical Open (DBObjectHandle &object_handle, char *extnames, PIACC accopt, logical transient_w=NO, char *key_name_w=NULL );
public     :                  OPIImpExp             logical Open (double dbl_value );
public     :                  OPIImpExp             logical Open (int32 int_val );
public     :                  OPIImpExp             logical Open (PropertyHandle *property_handle );
public     :                  OPIImpExp             logical Open (char *string, int32 string_len );
public     :                  OPIImpExp             logical Open (char *string, logical conv_opt=NO );
public     :                  OPIImpExp             logical Open (dbtm time_val );
public     :                  OPIImpExp             logical Open (dttm datetime_val );
public     :                  OPIImpExp             logical Open (PropertyHandle &prop_hdl, BNFData *parm_data, logical open_opt );
public     :                  OPIImpExp             logical Open (DBObjectHandle &object_handle, char *strnames, char *keyname, char *baseexts_w=NULL, logical weak_opt_w=NO, logical own_opt_w=NO );
public     :                  OPIImpExp             logical Open (DBObjectHandle &object_handle, BNFData *parm_data, PIACC accopt );
public     :                  OPIImpExp             logical Open (PropertyHandle &prop_hdl, ST_OpCodes op_code, char *rule=NULL, OperEnvironment *operenv_w=NULL, PIACC access_mode=PI_Read );
public     :                  OPIImpExp             logical Open (DBObjectHandle &object_handle, ST_OpCodes op_code, char *rule=NULL, OperEnvironment *operenv_w=NULL, PIACC access_mode=PI_Read );
public     :                  OPIImpExp             logical Open (PropertyHandle &prop_hdl, ST_OpCodes op_code, BNFData *parm_data, OperEnvironment *operenv_w=NULL, PIACC access_mode=PI_Read );
public     :                  OPIImpExp             logical Open (DBObjectHandle &object_handle, ST_OpCodes op_code, BNFData *parm_data, OperEnvironment *operenv_w=NULL, PIACC access_mode=PI_Read );
public     :                  OPIImpExp             logical Open (DBStructDef *struct_def, char *prop_names, Instance instance );
public     :                  OPIImpExp             logical Open (DictionaryHandle &dictptr, DBFieldDef *field_def, char *init_string, logical init_opt, logical const_opt );
public     :                  OPIImpExp             logical Open (DictionaryHandle &dictptr, char *prop_names, char *typenames, SDB_RLEV ref_level, uint32 size, uint16 precision, uint32 dimension, char *init_string );
public     :                  OPIImpExp             logical Open (DictionaryHandle &dictptr, char *typenames );
public     :                  OPIImpExp             logical Open (DBStructDef *strdef, Instance instance );
public     :                  OPIImpExp             logical Open (DBFieldDef *field_def, Instance initinst );
public     :                                        logical OpenAccessPath (PropertyHandle &prop_hdl, char *path_prop, OperEnvironment *operenv, logical open_opt );
public     :                                        logical OpenAccessPath (PropertyHandle &prop_hdl, BNFData *parm_data, OperEnvironment *operenv, logical open_opt );
public     :                                        logical OpenAccessPath (node *nodptr, BNFData *parm_data, OperEnvironment *operenv, logical open_opt );
public     :                                        logical OpenAccessPath (DBObjectHandle &object_handle, char *path_prop, OperEnvironment *operenv, PIACC accopt );
public     :                                        logical OpenAccessPath (DBObjectHandle &object_handle, BNFData *parm_data, OperEnvironment *operenv, PIACC accopt );
public     :                  OPIImpExp             logical OpenHierarchy (PropertyHandle *bottom_ph, PropertyHandle *top_ph=NULL, logical path_opt=NO, PIACC accmode=PI_undefined, logical copy_selection=YES );
public     :                  OPIImpExp             logical OwnsData ( );
public     :                  OPIImpExp             logical Position (int32 count );
public     :                  OPIImpExp             logical PositionTop ( );
public     :                  OPIImpExp             PropertyHandle Power (PropertyHandle &prop_hdl );
public     :                  OPIImpExp                  PropertyHandle (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp                  PropertyHandle (PropertyHandle *property_handle );
public     :                  OPIImpExp                  PropertyHandle (node *nodptr );
public     :                  OPIImpExp                  PropertyHandle (PropertyHandle &prophdl_ref, char *prop_names );
public     :                  OPIImpExp                  PropertyHandle (PropertyHandle *property_handle, char *prop_path );
public     :                  OPIImpExp                  PropertyHandle (DBObjectHandle &object_handle, char *extnames, PIACC accopt );
public     :                  OPIImpExp                  PropertyHandle (DBObjectHandle &object_handle, char *extnames, char *keynames, PIACC accopt, logical transient_w=NO );
public     :                  OPIImpExp                  PropertyHandle (DBObjectHandle &object_handle, char *strnames, char *keyname, char *baseexts_w=NULL, logical weak_opt_w=NO, logical own_opt_w=NO );
public     :                  OPIImpExp                  PropertyHandle (PropertyHandle &prop_hdl, ST_OpCodes op_code, char *rule=NULL );
public     :                  OPIImpExp                  PropertyHandle (DBObjectHandle &object_handle, ST_OpCodes op_code, char *rule=NULL );
public     :                  OPIImpExp                  PropertyHandle (PropertyHandle &prop_hdl, ST_OpCodes op_code, BNFData *parm_data );
public     :                  OPIImpExp                  PropertyHandle (DBObjectHandle &object_handle, ST_OpCodes op_code, BNFData *parm_data );
public     :                  OPIImpExp                  PropertyHandle (DBStructDef *strdef, char *prop_names, Instance instance_w=Instance() );
public     :                  OPIImpExp                  PropertyHandle (DictionaryHandle &dictptr, DBFieldDef *field_def, char *init_string, logical init_opt, logical const_opt );
public     :                  OPIImpExp                  PropertyHandle (DictionaryHandle &dictptr, char *prop_names, char *typenames, SDB_RLEV ref_level, uint32 size, uint16 precision, uint32 dimension, char *init_string );
public     :                  OPIImpExp                  PropertyHandle (DictionaryHandle &dictptr, char *typenames );
public     :                  OPIImpExp                  PropertyHandle (DBStructDef *strdef, Instance instance_w=Instance() );
public     :                  OPIImpExp                  PropertyHandle (DBFieldDef *field_def, Instance initinst );
public     :                  OPIImpExp                  PropertyHandle (int32 int_val );
public     :                  OPIImpExp                  PropertyHandle (char *string );
public     :                  OPIImpExp                  PropertyHandle (char *string, int32 string_len );
public     :                  OPIImpExp                  PropertyHandle (double dbl_value );
public     :                  OPIImpExp                  PropertyHandle (dbdt date_val );
public     :                  OPIImpExp                  PropertyHandle (dbtm time_val );
public     :                  OPIImpExp                  PropertyHandle (dttm datetime_val );
public     :                  OPIImpExp                  PropertyHandle (logical logval );
public     :                  OPIImpExp                  PropertyHandle ( );
public     :                  OPIImpExp             logical ProvGenAttribute ( );
public     :                  OPIImpExp             Instance Provide (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             Instance Provide (int32 set_pos0_w=AUTO );
public     :                  OPIImpExp             Instance Provide (Key sort_key );
public     :                  OPIImpExp             Instance Provide (char *charkey );
public     :                  OPIImpExp             Instance Provide (Instance initinst );
public     :                  OPIImpExp             Instance ProvideArea ( ) const;
public     :                  OPIImpExp             char *ProvideGUID ( );
public     :                  OPIImpExp             Instance ProvideGlobal (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             Instance ProvideGlobal (int32 set_pos0_w=AUTO );
public     :                  OPIImpExp             Instance ProvideGlobal (Key sort_key );
public     :                  OPIImpExp             Instance ProvideGlobal (char *charkey );
public     :                  OPIImpExp             Instance ProvideGlobal (Instance initinst );
public     :                                        node *ProvideNode ( );
public     :                  OPIImpExp             OperationHandle *ProvideOperation (char *expression );
public     :                  OPIImpExp             int16 ReadBuffer (int32 set_pos0, int16 direction=1 );
public     :                  OPIImpExp             logical Refresh ( );
public     :                  OPIImpExp             logical RegisterHandle ( );
public     :                                        logical RegisterNode (node *nodptr );
public     :                                        logical RegisterNode (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical ReleaseBuffer ( );
public     :                  OPIImpExp             logical RemoveFromCollection ( );
public     :                  OPIImpExp             logical RemoveString (char *string, int32 position, int32 len );
public     :                  OPIImpExp             logical RemoveTerminator (char *string );
public     :                  OPIImpExp             logical Rename (Key new_key );
public     :                  OPIImpExp             logical RepairIndex (char *key_name_w=NULL, char *attrstr_w=NULL );
public     :                  OPIImpExp             logical ReplaceString (char *old_str, char *new_str );
public     :                  OPIImpExp             logical ReplaceSysVariables ( );
public     :                  OPIImpExp             logical Reset ( );
public     :                  OPIImpExp             void ResetDirty ( );
public     :                  OPIImpExp             void ResetInstanceEventHandler (EventLink *event_link );
public     :                  OPIImpExp             void ResetInstanceProcessHandler (EventLink *event_link );
public     :                  OPIImpExp             void ResetPropertyEventHandler (EventLink *event_link );
public     :                  OPIImpExp             void ResetPropertyProcessHandler (EventLink *event_link );
public     :                  OPIImpExp             logical ResetSelection ( );
public     :                  OPIImpExp             logical ResetTransientProperty ( );
public     :                  OPIImpExp             logical ResetWProtect ( );
public     :                  OPIImpExp             node *ReturnHandle ( );
public     :                  OPIImpExp             logical Save (char savopt=NO, logical switchopt=NO );
public     :                  OPIImpExp             int32 SearchText (char *string, int32 curpos=0, logical case_opt=YES );
public     :                  OPIImpExp             PropertyHandle &Select (PropertyHandle &prophdl_ref, char *expression );
public     :                  OPIImpExp             void SetActionResult (char *result_string );
public     :                  OPIImpExp             Instance SetArea (void *datarea );
public     :                  OPIImpExp             logical SetContextVariables (char *context_string );
public     :                  OPIImpExp             void SetDescription (DBFieldDef *prop_def );
public     :                  OPIImpExp             void SetDescription (fmcb *fmcbptr );
public     :                  OPIImpExp             void SetDirty ( );
public     :                  OPIImpExp             logical SetDynLength ( );
public     :                  OPIImpExp             logical SetGenAttribute (char *attrstr );
public     :                  OPIImpExp             logical SetGenAttribute (int attrtype );
public     :                  OPIImpExp             logical SetGenAttribute (char *attrstr, char *prop_path );
public     :                  OPIImpExp             logical SetGenAttribute (int attrtype, char *prop_path );
public     :                                        logical SetGenAttribute_intern (char *prop_path, int attrtype, char *attrstr );
public     :                  OPIImpExp             Instance SetInstance (Instance instance );
public     :                  OPIImpExp             logical SetInstanceAction (SimpleAction *action );
public     :                  OPIImpExp             void SetInstanceEventHandler (EventLink *event_link );
public     :                  OPIImpExp             void SetInstanceProcessHandler (EventLink *event_link );
public     :                  OPIImpExp             logical SetKey (Key ident_key, Instance instance );
public     :                  OPIImpExp             logical SetKey (Key ident_key );
public     :                                        void SetModified ( );
public     :                  OPIImpExp             logical SetNormalized (int32 long_val );
public     :                  OPIImpExp             logical SetOrder (char *key_name_w=NULL );
public     :                  OPIImpExp             logical SetOrder (char *key_name, int attrtype );
public     :                  OPIImpExp             logical SetOrder (char *key_name, char *attrstr );
public     :                  OPIImpExp             logical SetOrder (char *key_name, int attrtype, char *attrstr );
public     :                                        logical SetOrder_intern (char *key_name, int attrtype, char *attrstr );
public     :                  OPIImpExp             logical SetPropertyAction (SimpleAction *action );
public     :                  OPIImpExp             void SetPropertyEventHandler (EventLink *event_link );
public     :                  OPIImpExp             void SetPropertyProcessHandler (EventLink *event_link );
public     :                  OPIImpExp             logical SetSelection (char *expression );
public     :                  OPIImpExp             logical SetSelection (BNFData *bdata );
public     :                  OPIImpExp             logical SetSortKey (Key sort_key, Instance instance );
public     :                  OPIImpExp             logical SetSortKey (Key sort_key );
public     :                  OPIImpExp             logical SetTransientProperty (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical SetType (char *strnames );
public     :                                        logical SetUpdate (logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (const PropertyHandle &cprop_hdl, logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (int64 int64_val, logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (logical logval, logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (dbdt date_val, logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (double dbl_value, logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (int32 long_val, logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (char *string, logical check_update=YES, logical conv_opt=NO );
public     :                  OPIImpExp             PropertyHandle &SetValue (dbtm time_val, logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (dttm datetime_val, logical check_update=YES );
public     :                  OPIImpExp             PropertyHandle &SetValue (int16 short_val, logical check_update=YES );
public     :                  OPIImpExp             logical SetVersion (uint16 version_nr=CUR_VERSION );
public     :                  OPIImpExp             logical SetWProtect ( );
public     :                  OPIImpExp             ACObject *StartRTA ( ) const;
public     :                  OPIImpExp             logical StopRTA (logical ta_started ) const;
public     :                                        logical StoreData (Instance instance );
public     :                  OPIImpExp             Key StringToKey (Key key_string, char *key_name_w=NULL );
public     :                  OPIImpExp             logical ToTop ( );
public     :                  OPIImpExp             PropertyHandle &Union (PropertyHandle &prop_hdl1, PropertyHandle &prop_hdl2, char sk_opt=YES, logical distinct=NO );
public     :                  OPIImpExp             PropertyHandle &Union (PropertyHandle **ph_list, int32 count, char sk_opt=YES, logical distinct=NO );
public     :                  OPIImpExp             PropertyHandle &Union (PropertyHandle &prophdl_ref, char sk_opt=YES, logical distinct=NO );
public     :                  OPIImpExp             logical Unlock ( );
public     :                  OPIImpExp             logical UnlockSet ( );
public     :                  OPIImpExp             logical UnregisterHandle ( );
public     :                  OPIImpExp             logical ValidateNode (logical provide_inst ) const;
public     :                  OPIImpExp             node *get_nodeptr ( ) const;
public     :                  OPIImpExp             logical operator! ( );
public     :                  OPIImpExp             logical operator!= (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             logical operator!= (char *string );
public     :                  OPIImpExp             logical operator!= (int32 long_val );
public     :                  OPIImpExp             logical operator!= (double double_val );
public     :                  OPIImpExp             logical operator!= (dbdt date_val );
public     :                  OPIImpExp             logical operator!= (dbtm time_val );
public     :                  OPIImpExp             logical operator!= (PropertyHandle *property_handle );
public     :                  OPIImpExp             PropertyHandle operator% (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             PropertyHandle operator& (PropertyHandle &prophdl_ref );
public     :                  OPIImpExp             logical operator&& (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle &operator&= (PropertyHandle &prophdl_ref );
public     :                  OPIImpExp             Instance operator() (int32 set_pos0 );
public     :                  OPIImpExp             Instance operator() (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             Instance operator() (Key sort_key );
public     :                  OPIImpExp             PropertyHandle operator* (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle &operator*= (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle operator+ (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle &operator++ (int  );
public     :                  OPIImpExp             PropertyHandle &operator++ ( );
public     :                  OPIImpExp             PropertyHandle &operator+= (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle operator- (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle operator- ( );
public     :                  OPIImpExp             PropertyHandle &operator-- ( );
public     :                  OPIImpExp             PropertyHandle &operator-- (int  );
public     :                  OPIImpExp             PropertyHandle &operator-= (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle operator/ (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle &operator/= (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             logical operator< (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical operator< (char *string );
public     :                  OPIImpExp             logical operator< (int32 long_val );
public     :                  OPIImpExp             logical operator< (double double_val );
public     :                  OPIImpExp             logical operator< (dbdt date_val );
public     :                  OPIImpExp             logical operator< (dbtm time_val );
public     :                  OPIImpExp             PropertyHandle operator<< (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             logical operator<= (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical operator<= (char *string );
public     :                  OPIImpExp             logical operator<= (int32 long_val );
public     :                  OPIImpExp             logical operator<= (dbtm time_val );
public     :                  OPIImpExp             logical operator<= (dbdt date_val );
public     :                  OPIImpExp             logical operator<= (double double_val );
public     :                  OPIImpExp             PropertyHandle &operator= (int64 int64_val );
public     :                  OPIImpExp             PropertyHandle &operator= (logical logval );
public     :                  OPIImpExp             PropertyHandle &operator= (dbdt date_val );
public     :                  OPIImpExp             PropertyHandle &operator= (double dbl_value );
public     :                  OPIImpExp             PropertyHandle &operator= (int32 long_val );
public     :                  OPIImpExp             PropertyHandle &operator= (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle &operator= (int16 short_val );
public     :                  OPIImpExp             PropertyHandle &operator= (char *string );
public     :                  OPIImpExp             PropertyHandle &operator= (dbtm time_val );
public     :                  OPIImpExp             PropertyHandle &operator= (dttm datetime_val );
public     :                  OPIImpExp             logical operator== (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             logical operator== (char *string );
public     :                  OPIImpExp             logical operator== (int32 long_val );
public     :                  OPIImpExp             logical operator== (double double_val );
public     :                  OPIImpExp             logical operator== (dbdt date_val );
public     :                  OPIImpExp             logical operator== (dbtm time_val );
public     :                  OPIImpExp             logical operator== (PropertyHandle *property_handle );
public     :                  OPIImpExp             logical operator> (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical operator> (char *string );
public     :                  OPIImpExp             logical operator> (int32 long_val );
public     :                  OPIImpExp             logical operator> (double double_val );
public     :                  OPIImpExp             logical operator> (dbdt date_val );
public     :                  OPIImpExp             logical operator> (dbtm time_val );
public     :                  OPIImpExp             logical operator>= (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             logical operator>= (char *string );
public     :                  OPIImpExp             logical operator>= (int32 long_val );
public     :                  OPIImpExp             logical operator>= (double double_val );
public     :                  OPIImpExp             logical operator>= (dbtm time_val );
public     :                  OPIImpExp             logical operator>= (dbdt date_val );
public     :                  OPIImpExp             PropertyHandle operator>> (const PropertyHandle &cprop_hdl );
public     :                  OPIImpExp             PropertyHandle &operator[] (int32 set_pos0 );
public     :                  OPIImpExp             PropertyHandle &operator[] (PropertyHandle &prop_hdl );
public     :                  OPIImpExp             PropertyHandle &operator[] (Key skey );
public     :                  OPIImpExp             logical operator^ (const PropertyHandle &cprop_hdl ) const;
public     :                  OPIImpExp             PropertyHandle operator| (PropertyHandle &prophdl_ref );
public     :                  OPIImpExp             PropertyHandle &operator|= (PropertyHandle &prophdl_ref );
public     :                  OPIImpExp             logical operator|| (const PropertyHandle &cprop_hdl );
public     :                                        void set_nodeptr (node *nodptr );
public     :                  OPIImpExp                  ~PropertyHandle ( );
};

#pragma pack()
#endif
