/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/08/29 20:24:45,73 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "PropertyHandle"

#include  <pdefault.h>
#include  <cevtp.h>
#include  <cutimac.h>
#include  <dbfdefs.h>
class     PropertyHandle;
#include  <cST_OpCodes.h>
#include  <sACOPSelect.hpp>
#include  <sACObject.hpp>
#include  <sACPath.hpp>
#include  <sACTransient.hpp>
#include  <sACTransientReference.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCNode.hpp>
#include  <sCSA_Handle.hpp>
#include  <sCSNode.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBField_CHAR.hpp>
#include  <sDBField_DATE.hpp>
#include  <sDBField_DATETIME.hpp>
#include  <sDBField_INT.hpp>
#include  <sDBField_REAL.hpp>
#include  <sDBField_TIME.hpp>
#include  <sDBHandle.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionary.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sEB_Number.hpp>
#include  <sEventLink.hpp>
#include  <sExpressionReference.hpp>
#include  <sInstance.hpp>
#include  <sOPBase.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOperation.hpp>
#include  <sOperationHandle.hpp>
#include  <sParmList.hpp>
#include  <sSDB_Member.hpp>
#include  <sSimpleAction.hpp>
#include  <sXMLString.hpp>
#include  <sfmcb.hpp>
#include  <sguid.hpp>
#include  <snode.hpp>
#include  <ssmcb.hpp>
#include  <sPropertyHandle.hpp>


/******************************************************************************/
/**
\brief  Add - Add instance to collection

        You  can  add  instances  to  any  type of collection or reference. When
        adding  an instance to  a collection the  cardinality for the collection
        is  checked as well  as unique key  reuirements. When adding an instance
        to  an owning  collection or  reference a  new database instance will be
        created.  Adding an instance to a collection or reference is possible by
        position,  key (when sort orders are defined for the collection) or with
        an  initialising  instance.  When  terminating successfully the instance
        added to the collection is selected in the property handle.
        The  position passed (set_pos0) when adding  an instance to a collection
        has  an  effect  only,  when  the collection is unordered. Otherwise the
        position  is determined by the key value. For ordered instances you must
        always  pass a  sort or  ident key  value. When  passing a sort key this
        must  correspond  to  the  active  order  (index)  set  for the property
        handle.  When  an  __AUTOIDENT  key  has  been defined the next instance
        number  is  determined  in  the  collection or in its most top super set
        (based collections).
        {b Collection based references}
        When  adding an instance  to a collection  based reference or collection
        (ie  a  subset  of  another  collection)  the function checks whether an
        instance  with the same key (ident key of the instance to be added) does
        already  exist in the  base collection (super  set). In this case no new
        instance  is  created  but  the  instnce found in the base collection is
        added  to the current  collection or reference.  The instance values are
        updated  from the values  of the instance  found in the base collection.
        When  no instance has been found the  new instance (key) is added to the
        base  collection  and  than  to  the current collection. In any case the
        instance  is shared  between the  base and  the current collection, i.e.
        both refer to the same instance.
        For  base collections you must always provide an ident key. The function
        will  store the  passed keys  in an  initial instance (which can also be
        passed  by  the  application).  From  this initial instance the function
        extracts  the  ident  key  for  searching  the  instance  in  the  basic
        collections,  i.e. the ident key is  the minimum information an instance
        should have.
        {b Using shared base structure instances}
        When  the collection refers to an instance  which has one or more shared
        base  instances  the  instance  must  contain  ident  key values for all
        shared  base instances. Add by  key you can use  in this case only, when
        the key provides information for all base instance ident keys.

\return instance - Instance area
-------------------------------------------------------------------------------
\brief  A00 - 



\param  set_pos0 - Position in collection
\param  sortkey - Sort key value
\param  identkey_w - Ident key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

Instance PropertyHandle :: Add (int32 set_pos0, Key sortkey, Key identkey_w )
{

  return ( Add_intern(set_pos0,sortkey,identkey_w,NULL,YES,NO) );

}

/******************************************************************************/
/**
\brief  ByKey - 



\param  sortkey - Sort key value
\param  identkey_w - Ident key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

Instance PropertyHandle :: Add (Key sortkey, Key identkey_w )
{

  return ( Add_intern(AUTO,sortkey,identkey_w,NULL,YES,NO) );

}

/******************************************************************************/
/**
\brief  Instance - Add instance by property value

        The  function  checks  whether  the  property  handle passes a numerical
        value  or not.  When passing  a numerical  value the function creates an
        instance  at the position according to the number passed in the property
        handle  (-> "Create instance  at position"). Otherwise  the value in the
        property  handle is interpreted  as string key,  which will be converted
        into  key and adds an  instance by key value  to the collection (-> "Add
        instance by key value")..

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

Instance PropertyHandle :: Add (PropertyHandle &prop_hdl )
{

  return ( prop_hdl.IsText()
           ? Add(StringToKey(prop_hdl.GetString()))
           : Add(prop_hdl.GetInt())  );


}

/******************************************************************************/
/**
\brief  OnPosition - Create instance at position

        This  function is used to create an instance at a certain position in an
        unordered  collection. The  function creates  the instance at the passed
        position  (set_pos_w).  When  AUTO  is  passed  the  instance is created
        infront  of the selected instance. When  no instance is selected the new
        instance  is appended to the end of  the collection. The instance in the
        property  handle  can  be  initialized  before  calling the Add function
        calling  GetInitInstance() and setting initial  property values. In this
        case  the init_inst option must be set  to YES when calling the function
        (otherwuise  the initialized instance will  be ignored) and the function
        operates  similar  to  the  "Add  instance  at  position"  function. The
        instance  can be also initialized before  adding to the collection using
        the DBInitialized event in the structure context.
        When  the collection is ordered the  position passed will be ignored and
        the  instance will  be inserted  in the  collection according to the key
        passed  within  the  initialized  instance.  When  the  instance  is not
        initialized,  the instance is created with the default values defined in
        the data model (structure definition).

\param  set_pos0_w - Position in collection
\param  init_inst - Add initialized instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

Instance PropertyHandle :: Add (int32 set_pos0_w, logical init_inst )
{

  return ( Add_intern(set_pos0_w,NULL,NULL,Instance(),init_inst,NO) );

}

/******************************************************************************/
/**
\brief  i0 - Add instance

        This  function is used to insert an instance at a certain position in an
        unordered  collection. The  function inserts  the instance passed at the
        passed  position  (set_pos_w).  When  no  position  or AUTO is passed as
        position  the  instance  is  inserted  infront of the selected instance.
        When  no instance is selected the new instance is appended to the end of
        the collection.
        When  the collection is ordered the  position passed will be ignored and
        the  instance will  be inserted  in the  collection according to the key
        passed within the instance.

\param  newinst - New instance
\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

Instance PropertyHandle :: Add (Instance newinst, int32 set_pos0_w )
{

  return ( Add_intern(set_pos0_w,NULL,NULL,newinst,NO,NO) );

}

/******************************************************************************/
/**
\brief  i2 - Add instance by key

        The  function adds an instance by  key (sortkey). When the collection is
        unordered  the sort key will be interpreted  as ident key (when no extra
        ident  key  is  passed).  When  a  sort  order has been selected for the
        collection  that  is  not  the  ident  key and that does not contain the
        ident key, both, sortkey and identkey must be passed to the function. 
        Instead  of the  key you  may pass  an instance that contains the values
        for  the keys.  This can  solve problems  when having several unique key
        indexes  for  a  collection.  You  can  also  use  the GetInitInstance()
        function  to set the initial values in the instance area of the property
        handle. In this case init_inst must be set to YES.

\param  sortkey - Sort key value
\param  ident_key - Ident key value
\param  instance - Instance area
\param  init_inst - Add initialized instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

Instance PropertyHandle :: Add (Key sortkey, Key ident_key, Instance instance, logical init_inst )
{

  return ( Add_intern(AUTO,sortkey,ident_key,instance,init_inst,NO) );

}

/******************************************************************************/
/**
\brief  i3 - Add instance by index and key

        This  function can be used to  add an instance to different collections.
        The  collection  referenced  in  the property handle might be unordered,
        which  requires  adding  an  instance  by  pposition.  A base collection
        defined  for  the  collection,  however,  requires  a  key for adding an
        instance.  In this case,  the position, a  sortkey and an identkey might
        be  necessary. Instead of the key  values an instance (newinst_w) can be
        passed  or the  velues can  be set  in the instance area of the property
        handle  (GetInitInstance()).  You  may  also use the DBInitialized event
        handler for settinig initial values for the instance to be created.

\param  set_pos0 - Position in collection
\param  sortkey - Sort key value
\param  ident_key - Ident key value
\param  instance - Instance area
\param  init_inst - Add initialized instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

Instance PropertyHandle :: Add (int32 set_pos0, Key sortkey, Key ident_key, Instance instance, logical init_inst )
{

  return ( Add_intern(set_pos0,sortkey,ident_key,instance,init_inst,NO) );

}

/******************************************************************************/
/**
\brief  AddGlobal - Add instance globally to collection

        The  function  works  the  same  way  as the Add() function, except that
        global  instances are created outside  the transaction. When not running
        in a transactions the function works the same way as Add(). 
        Creating  global  instances  in  a  transaction prevents all other users
        from   creating   global   instances   for   the   same extent until the
        transaction  is  closed,  since  the  index for the global collection is
        locked  until  terminating  the  transaction.  Especially  when creating
        instances  via local  collections that  are based on global collectioons
        (extents)  uncomfortable locks  may block  the system.  In this case Add
        global should be used instead of add. 
        Using  AddGlobal() for creating a new  instance the instance will resist
        in the global collection also when rolling back the transaction.

\return ph_inst - Instance Handle
-------------------------------------------------------------------------------
\brief  A00 - 



\param  set_pos0 - Position in collection
\param  sortkey - Sort key value
\param  identkey_w - Ident key value
\param  init_inst - Add initialized instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGlobal"

Instance PropertyHandle :: AddGlobal (int32 set_pos0, Key sortkey, Key identkey_w, logical init_inst )
{

  return ( Add_intern(set_pos0,sortkey,identkey_w,NULL,init_inst,YES) );

}

/******************************************************************************/
/**
\brief  ByKey - 



\param  sortkey - Sort key value
\param  identkey_w - Ident key value
\param  init_inst - Add initialized instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGlobal"

Instance PropertyHandle :: AddGlobal (Key sortkey, Key identkey_w, logical init_inst )
{
  Instance        newinst;
  return ( Add_intern(AUTO,sortkey,identkey_w,newinst,init_inst,YES) );

}

/******************************************************************************/
/**
\brief  OnPosition - 



\param  set_pos0_w - Position in collection
\param  init_inst - Add initialized instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGlobal"

Instance PropertyHandle :: AddGlobal (int32 set_pos0_w, logical init_inst )
{

  return ( Add_intern(set_pos0_w,NULL,NULL,Instance(),init_inst,YES) );

}

/******************************************************************************/
/**
\brief  i0 - 



\param  newinst - New instance
\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGlobal"

Instance PropertyHandle :: AddGlobal (Instance newinst, int32 set_pos0_w )
{

  return ( Add_intern(set_pos0_w,NULL,NULL,newinst,NO,YES) );

}

/******************************************************************************/
/**
\brief  i2 - 



\param  sortkey - Sort key value
\param  ident_key - Ident key value
\param  instance - Instance area
\param  init_inst - Add initialized instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGlobal"

Instance PropertyHandle :: AddGlobal (Key sortkey, Key ident_key, Instance instance, logical init_inst )
{

  return ( Add_intern(AUTO,sortkey,ident_key,instance,init_inst,YES) );

}

/******************************************************************************/
/**
\brief  i3 - 



\param  set_pos0 - Position in collection
\param  sortkey - Sort key value
\param  identkey_w - Ident key value
\param  newitp_w - New instance
\param  init_inst - Add initialized instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGlobal"

Instance PropertyHandle :: AddGlobal (int32 set_pos0, Key sortkey, Key identkey_w, Instance newitp_w, logical init_inst )
{

  return ( Add_intern(set_pos0,sortkey,identkey_w,newitp_w,init_inst,YES) );

}

/******************************************************************************/
/**
\brief  AddReference - Add persistent instance

        The  function adds  an instance  selected in  another property handle to
        the  collection/reference of the current  property handle. Both property
        handles  must have the same type or the  same base type if they are weak
        typed.  You  can  use  AddReference()  only  for not owning collections.
        Usually  the function is used to  fill temporary extents with instances,
        which have been selected for special purposes. 
        You  can only add instances that are defined in the same database as the
        instances  of the  target propüerty  handle. It  is also not possible to
        add  an instance by reference from a server database to a local database
        or vize versa.

        After  addin the instance  to the property  handle the added instance is
        the currently selected one.

        {\b Events }

        When  adding  an  instance  to  a  collection  the function fires an {\i
        Insert}-event.  You can use the insert  event for checking the operation
        and  deny it. After the instance  has been added an  {\i Inserted}-Event
        is generated. 
        When  the  post  event  handler  has  been  modifying  the  instance  an
        additional  {\i  Stored}-event  might  be  created.  When  selecting the
        instance in the property handle a final {\i Read}-event is generated..

        collection)  the function checks  whether an instance  with the same key
        (ident  key of the instance to be  added) does already exist in the base
        collection  (super set). In this case no new instance is created but the
        instnce  found in the base collection is added to the current collection
        or  reference. The  instance values  are updated  from the values of the
        instance  found in the base collection.  When no instance has been found
        the  new instance (key) is added to  the base collection and than to the
        current  collection. In any case the instance is shared between the base
        and the current collection, i.e. both refer to the same instance.
        For  base collections you must always provide an ident key. The function
        will  store the  passed keys  in an  initial instance (which can also be
        passed  by  the  application).  From  this initial instance the function
        extracts  the  ident  key  for  searching  the  instance  in  the  basic
        collections,  i.e. the ident key is  the minimum information an instance
        should have.
        {b Using shared base structure instances}
        When  the collection refers to an instance  which has one or more shared
        base  instances  the  instance  must  contain  ident  key values for all
        shared  base instances. Add by  key you can use  in this case only, when
        the key provides information for all base instance ident keys.

\return term - Termination code

\param  source_handle - Source property handle
\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddReference"

logical PropertyHandle :: AddReference (PropertyHandle &source_handle, int32 set_pos0_w )
{
  ACObject    *obh = StartRTA();
  logical      term  = NO;
  if ( !ValidateNode(YES) && source_handle.IsValid() )
    term = Tnodeptr->AddReference(source_handle.Tnodeptr,set_pos0_w);

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Add_intern - Add instance internally



\return instance - Instance area

\param  indx0 - Position in collection
\param  sort_key - Sort key value
\param  ident_key - Ident key value
\param  newinst - New instance
\param  init_inst - Add initialized instance
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add_intern"

Instance PropertyHandle :: Add_intern (int32 indx0, Key sort_key, Key ident_key, Instance newinst, logical init_inst, logical global_add )
{
  Instance     instance;
  ACObject    *obh = StartRTA();
  logical      term = NO;
BEGINSEQ
  if ( ValidateNode(YES) )                           ERROR
  
  if ( !init_inst && !newinst )
    newinst = GetArea();
  if ( Check(YES) || !Tnodeptr->Add(indx0,sort_key.GetData(),
                                   ident_key.GetData(),
                                   (char *)newinst.GetData(),
                                   global_add) )     ERROR
  instance = Tnodeptr->GetArea();

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  AllocDescription - Allocate property description

        The  function creates an empty description for the property handle. When
        the  property handle is already associated  with a description this will
        be removed from the property handle.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocDescription"

logical PropertyHandle :: AllocDescription ( )
{

  return( GetValid() 
          ? Tnodeptr->AllocDescription() 
          : YES );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbhandle - Pointer to database handle
\param  fldnames - 
\param  fldtypes - 
\param  ref_level - Reference level
\param  size - Size
\param  precision - Precision
\param  dimension - Dimension
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocDescription"

logical PropertyHandle :: AllocDescription (DatabaseHandle &dbhandle, char *fldnames, char *fldtypes, SDB_RLEV ref_level, uint32 size, uint16 precision, uint32 dimension )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetValid() )                                  ERROR
    
  TypeKey   tkey(dbhandle.get_dbhandle()->GetDictionary(),fldtypes);
  term = nodeptr->dbffmcbc(dbhandle.get_dbhandle(),fldnames,
                           tkey.Name(),tkey.GetID(),
                           ref_level,size,precision,dimension);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AllocateArea - Allocate instance area

        The  function allocates  a data  area for  a property handle if this has
        not  yet been done. If the property handle is linked to the data area of
        another  property handle this link is deleted  an a private data area is
        allocated.
        You  can use this function when  you create dummy property handles which
        are controlled by the application.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocateArea"

logical PropertyHandle :: AllocateArea ( )
{

  return( GetValid() 
          ? Tnodeptr->AllocateArea() 
          : YES );

}

/******************************************************************************/
/**
\brief  AppendString - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AppendString"

logical PropertyHandle :: AppendString (char *string )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ProvideArea();
  
  if ( IsValid() )
    term = Tnodeptr->AppendString(string);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  AutoLocate - 



\return term - Termination code

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoLocate"

logical PropertyHandle :: AutoLocate (char chkopt )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
BEGINSEQ
  if ( chkopt && ValidateNode(YES) )                 ERROR
    
  term = Tnodeptr->AutoLocate(NO);

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Cancel - Cancel selection

        The  function  resets  modifications  made  on the internal instance and
        cancels  the selection. After cancelling an instance the property handle
        has  no  current  selection.  All  subordinated  property  handles  are 
        cancelled as well.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical PropertyHandle :: Cancel ( )
{
  ACObject    *obh = StartRTA();
  logical      term;
  term = IsValid() ? Tnodeptr->Cancel() : YES;
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  CancelBuffer - Cancel all buffered instances

        The  function  will  release  all  instances in a buffer. The next Get()
        access will fill the buffer again.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CancelBuffer"

logical PropertyHandle :: CancelBuffer ( )
{
  ACObject    *obh = StartRTA();
  logical      term;
  term = IsValid() ? Tnodeptr->CancelBuffer() : YES;
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeBuffer - Change collection buffer count

        Instances  for a PropertyHandle can be  read in block mode. The function
        allocates  a  buffer  size  to  the  property handle, i.e. the number of
        instances  that  will  be  read  at once. When a buffer has already been
        allocated  you can use the function to change the buffer size. Passing 0
        or  1  will  change  from  buffered  read  to unbuffered access (same as
        ReleaseBuffer()). 
        Buffered  access can  be used  for reading  collections with fixed type,
        only.  Trying  to  enable  buffered  access  for  untyped  or weak typed
        collections will fail without writing an error to the error log file. 
        When  passing AUTO as buffer size the  number of instances stored in the
        collection  is  reserved.  Thus,  you  will read the complete collection
        into the buffer. 
        When  a filter has  been defined for  the property handle only instances
        are read into the buffer that fulfill the filter condition. 
        Usually  the  buffer  is  filled  automatically when reading an instance
        that  is not contained in  the buffer. The system  tries to read as many
        instances  as  defined  in  buffer  size  from  the  current  position. 
        Subsequent  Get() request will read from the buffer as long as possible.
        Cancel()  will cansel the current selection but not the instances in the
        buffer. 
        To  position  the  buffer  on  a  certain  instance  you  can  use  the 
        ReadBuffer()  function.  For  resetting  the  buffer  you  can  use  the
        CancelBuffer() function.
        You  cannot use blockmode for views  containing references. In this case
        the  function will ignore  the request and  buffer size remains 1. There
        are  also problems in client/server  mode when referring to sub-property
        handles  for  references  in  instances  that  heve  been  reading  in 
        blockmode. Moreover, blockmode cannot be used for updating instances.

\return buffnum - 

\param  buffnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeBuffer"

int16 PropertyHandle :: ChangeBuffer (int16 buffnum )
{
  ACObject    *obh = StartRTA();
  int16        bufnum;

  ValidateNode(NO);
  
  bufnum = IsValid() ? Tnodeptr->ChangeBuffer(buffnum) : AUTO;
  obh->StopReadTA(NO);
  return(bufnum);
}

/******************************************************************************/
/**
\brief  ChangeCache - Change cache size

        For  optimizing  access  by  key  a  property  handle cache can be used.
        Usually  the  property  handle  cache  is deactivated. Passsing a buffer
        number  greater than 0 will enable a cache with buffnum entries. Passing
        0 will disable the cache.
        When  the cache is active instances are  saved in the cache and are read
        from  the cache when accessing instances  by key value. Reading by index
        will  not  access  the  cache.  Hence  the cache should be activated for
        random key access, only.
        Using  the cache in  Write mode will  lock all instances buffered in the
        cache.  Updateing an instance that is stored  in the chach can be stored
        immediately  using  the  save  function.  Changing  the selection in the
        buffer will store the instance to the cache, only.

\return term - Termination code

\param  buffnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeCache"

logical PropertyHandle :: ChangeCache (int16 buffnum )
{
  ACObject    *obh = StartRTA();
  logical      term;
  ValidateNode(NO);
  
  term = IsValid() ? Tnodeptr->CacheSize(buffnum) : YES;
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeMode - Change access mode

        The  function allows changing the access mode for a PropertyHandle. This
        requires  that the batabase object access mode is higher or equal to the
        mode that is going to be activated. 
        You  can always change from higher  modes (PI_Write, PI_Update) to lower
        modes  (PI_Read).  Changing  from  read  to  update  or  write mode has,
        however,  some limitations.  You may  change the  mode in any directions
        for  extent  property  handles  and  for  property  handles referring to
        updateable   relationships.   Changing   the   mode   for non updateable
        relationschips  or references,  however, is  possible only to PI_Read or
        PI_Write.  Changing  to  PI_Write  is  possible  only,  when  the parent
        PropertyHandle is opened with or set to PI_Write.
        Changing  the access mode will cancel all subsequent PropertyHandles and
        change the mode to the mode requested for teh current PropertyHandle.
        Property  handle  running  in  block  mode can be accessed in read mode,
        only.  Change mode will fail when attemtimg to change the mode to update
        or write in this case.

\return oldmode - Old access mode
/******************************************************************************/
/**
\brief  i0 - 



\param  newmode - New access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC PropertyHandle :: ChangeMode (PIACC newmode )
{
  ACObject    *obh = StartRTA();
  PIACC        oldmode = PI_undefined;
  int32        lindx0  = AUTO;
  int32        entnr;
BEGINSEQ
  if ( ValidateNode(NO) )                            ERROR
  
  if ( (lindx0 = GetCurrentIndex()) != AUTO )
    entnr = Tnodeptr->GetID(lindx0,YES,YES).get_ebsnum();
          
  oldmode = Tnodeptr->ChangeMode(newmode);
  
  if ( lindx0 != AUTO )
  {
    Tnodeptr->Get(lindx0);
    // (wenn entnr nicht mehr die gleiche ist, muessen wir hier noch etwas tun.)
    if ( entnr != GetID() )
      oldmode = Tnodeptr->ChangeMode(oldmode);
  }
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(oldmode);
}

/******************************************************************************/
/**
\brief  Check - Check property handle

        The function checks whether a property handle is valid and opened. 
        Usually  property handles are opened on  demand, i.e. when access to any
        database  source  is  required.  After  opening  a  property  handle  a 
        structure definition is available and access is possible in principle. 
        If  the property  handle is  invalid or  not opened the function returns
        YES, otherwise NO.

\return term - Termination code

\param  ini_opt - Initialize option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical PropertyHandle :: Check (logical ini_opt )
{

  return( !IsValid() || Tnodeptr->Check(ini_opt,NO) );

}

/******************************************************************************/
/**
\brief  CheckPosition - Check position



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPosition"

logical PropertyHandle :: CheckPosition ( )
{
  ACObject    *obh = StartRTA();
  node        *high_node;
  logical      term = NO;
BEGINSEQ
  if ( ValidateNode(NO) )                            ERROR
    
  if ( !(high_node = Tnodeptr->get_nodenode()) ||
       high_node->IsPositioned() )                   LEAVESEQ

  if ( Tnodeptr->PositionTop() )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckUpdate - 



\return term - Termination code

\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckUpdate"

logical PropertyHandle :: CheckUpdate (logical check_update )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
BEGINSEQ
  if ( ValidateNode(YES) )                           ERROR
    
  if ( check_update )  
    if ( Tnodeptr->CheckUpdate() )                   ERROR
RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 



\return wpt - Write protection state
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical PropertyHandle :: CheckWProtect ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  term = IsPositioned() ? Tnodeptr->CheckWProtect() : YES;
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Close - Close Property Handle

        The  function will close the property  handle without destroying it. The
        handle can be re-opend later again.
        When  closing  or  destroying  the property handle unsaved modifications
        will  be  saved  atomatically.  This  might cause a number of activities
        including event handlers. 
        Since  the close  fonction or  the destructor  are called implicitely in
        many  cases, the  function will  push the  error and restore it, when no
        error  has detected while closing  the property handle. When terminating
        normally,  the  error  set  is  the  same  as  before  calling the close
        function.  Otherwise the error  returned in SDBError  or CTXError is the
        error from the close function.

\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical PropertyHandle :: Close ( )
{
  int          saverrctx = 0;
  ACObject    *obh       = NULL;
  int          saverr    = 0;
  node        *tnodeptr  = NULL;
  logical      term      = NO;
BEGINSEQ
  if ( !this || !nodeptr )                           ERROR
  saverrctx = CTXERROR;
  if ( obh = StartRTA() ) 
    saverr = obh->GetErrorCode();   
  
  if ( !nodeptr->IsValid() )
  {
    if ( SDBERROR == 9 )                             ERROR
    nodeptr->stsrerr();  // sonst wird node nicht geschlossen!!
  }  
    
  if ( tnodeptr = nodeptr->GetNode(NO) )
    tnodeptr->RemoveOperations(this);
  
  nodeptr->Release((ObjectReferenceHandle *)this);

  nodeptr = NULL;
  SDBISET(saverr)
  if ( saverrctx )
    CTXISET(saverrctx);   // unzureichend, da text futsch ist, wenn anderer Fehler gesetzt worden ist

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Compare - Compare the values for two property handles

        The  function  compares  the  values  of  the  two property handles. The
        function cannot compare collections. 
        The  function retuns  -1 when  the the  value for the property handle is
        lower  than  the  value  for  the  passed  property handle. The function
        retuns  1 when the the value for  the property handle is higher than the
        value  for  the  passed  property  handle. The function returns 0 if the
        values are equal.
        The  function returns ERIC (-99) if  the values are not compareble, i.e.
        no instance selected for the property or invalid property handle.

\return comp_result - Compare result
-------------------------------------------------------------------------------
\brief  A00 - Compare with other property handle

        This  implementation compares the value in  the property handle with the
        value  in the passed property handle. Data conversion  is performed when
        required.

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int16 PropertyHandle :: Compare (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh = StartRTA();
  int16        comp_result = ERIC;

  comp_result = !ValidateNode(YES) && !cprop_hdl.ValidateNode(YES) 
                ? Tnodeptr->Compare(cprop_hdl.Tnodeptr) 
                : ERIC;
  obh->StopReadTA(NO);
  return(comp_result);
}

/******************************************************************************/
/**
\brief  Date - Compare with date value

        This  implementation compares the value in  the property handle with the
        passed  date value.  Data conversion  is performed  for the passed value
        when  required. Converting  date values  to string  values may result in
        different  string  values  for  the  same  date  value  depending on the
        national  setting. Hence, string values should not be compared with date
        values.  In this case it is more  appropriate to compare the date values
        directly ( ph.GetDate() == date_val).

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int16 PropertyHandle :: Compare (dbdt date_val )
{
  ACObject    *obh = StartRTA();
  int32        result;
  int16        comp_result = ERIC;
BEGINSEQ
  if ( !IsPositioned() || !IsValid() || Tnodeptr->IsCollection() ) 
                                                     ERROR

  result = GetDate().GetLongInt() - date_val.GetLongInt();

  if ( !result )
    comp_result = 0;
  else if ( result < 0 )
    comp_result = -1;
  else if ( result > 0 )
    comp_result = 1;

RECOVER
  comp_result = ERIC;
ENDSEQ
  obh->StopReadTA(NO);
  return(comp_result);
}

/******************************************************************************/
/**
\brief  Float - Compare with double value

        This  implementation compares the value in  the property handle with the
        passed  double float value. Data conversion  is performed for the passed
        value when required.

\param  double_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int16 PropertyHandle :: Compare (double double_val )
{
  ACObject    *obh = StartRTA();
  double       result;
  int16        comp_result = ERIC;
BEGINSEQ
  if ( !IsPositioned() || !IsValid() || Tnodeptr->IsCollection() ) 
                                                     ERROR

  result = GetDouble() - double_val;

  if ( !result )
    comp_result = 0;
  else if ( result < 0 )
    comp_result = -1;
  else if ( result > 0 )
    comp_result = 1;

RECOVER
  comp_result = ERIC;
ENDSEQ
  obh->StopReadTA(NO);
  return(comp_result);
}

/******************************************************************************/
/**
\brief  Integer - Compare with 32-bit integer value

        This  implementation compares the value in  the property handle with the
        passed  integer value. Data conversion is performed for the passed value
        when required.

\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int16 PropertyHandle :: Compare (int32 long_val )
{
  ACObject    *obh = StartRTA();
  int32        result;
  int16        comp_result = ERIC;
BEGINSEQ
  if ( !IsPositioned() || !IsValid() || Tnodeptr->IsCollection() ) 
                                                     ERROR

  result = GetInt() - long_val;

  if ( !result )
    comp_result = 0;
  else if ( result < 0 )
    comp_result = -1;
  else if ( result > 0 )
    comp_result = 1;

RECOVER
  comp_result = ERIC;
ENDSEQ
  obh->StopReadTA(NO);
  return(comp_result);
}

/******************************************************************************/
/**
\brief  String - Compare with string value

        This  implementation compares the value in  the property handle with the
        value  in the passed string. Data conversion is performed for the string
        when required.

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int16 PropertyHandle :: Compare (char *string )
{
  ACObject    *obh = StartRTA();
  char        *str = NULL;
  int16        comp_result = ERIC;
BEGINSEQ
  if ( !IsPositioned() || !IsValid() || Tnodeptr->IsCollection() ) 
                                                     ERROR
  if ( str = ReplaceControlSequences(string,UNDEF,YES) )
    string = str;
    
  comp_result = strcmp(GetString(),string);

  if ( comp_result > 0 )
    comp_result = 1;
  else if ( comp_result < 0 )
    comp_result = -1;

RECOVER
  comp_result = ERIC;
ENDSEQ
  if ( str )
    free(str);
  obh->StopReadTA(NO);
  return(comp_result);
}

/******************************************************************************/
/**
\brief  Time - Compare with time value

        This  implementation compares the value in  the property handle with the
        passed  time value.  Data conversion  is performed  for the passed value
        when  required. Converting  time values  to string  values may result in
        different  string  values  for  the  same  time  value  depending on the
        national  setting. Hence, string values should not be compared with time
        values.  In this case it is more  appropriate to compare the time values
        directly ( ph.GetTime() == time_val).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int16 PropertyHandle :: Compare (dbtm time_val )
{
  ACObject    *obh = StartRTA();
  int32        result;
  int16                   comp_result = ERIC;
BEGINSEQ
  if ( !IsPositioned() || !IsValid() || Tnodeptr->IsCollection() ) 
                                                     ERROR

  result = GetTime().GetLongInt() - time_val.GetLongInt();

  if ( !result )
    comp_result = 0;
  else if ( result < 0 )
    comp_result = -1;
  else if ( result > 0 )
    comp_result = 1;

RECOVER
  comp_result = ERIC;
ENDSEQ
  obh->StopReadTA(NO);
  return(comp_result);
}

/******************************************************************************/
/**
\brief  CompareKey - Compare two ident key values

        The  function  compares  two  ident  key  values.  The keys are compared
        according to the data types of it's components.
        The  function  retuns  -1  when  the  the  value  for  the  first  key 
        (ident_key1)  is lower than  the value for  the second key (ident_key2).
        The  function  retuns  1  when  the  the  first value is higher than the
        second one. The function returns 0 when the keys are are equal.
        The  function returns ERIC (-99) if  the values are not compareble, i.e.
        when  no  ident  key  has  been  defined  or when the property handle is
        invalid.

\return cmpval - Compare result

\param  ident_key1 - 
\param  ident_key2 - Second key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareKey"

int8 PropertyHandle :: CompareKey (Key ident_key1, Key ident_key2 )
{
  ACObject    *obh = StartRTA();
  int8         comp_result = ERIC;
  ValidateNode(NO);
  
  comp_result = IsValid() 
                ? Tnodeptr->CompareKey(ident_key1.GetData(),
                                       ident_key2.GetData())
                : ERIC;

  obh->StopReadTA(NO);
  return(comp_result);
}

/******************************************************************************/
/**
\brief  CompareSortKey - Compare keys accroding to current sort order

        The  function  compares  two  key  values  for  the  selected  sort  key
        (SetOrder()).  The keys are compared according to the data types of it's
        components.
        The  function retuns -1 when the the value for the first key (sort_key1)
        is  lower than  the value  for the  second key (sort_key2). The function
        retuns  1 when  the the  first value  is higher than the second one. The
        function returns 0 when the keys are are equal.
        The  function returns ERIC (-99) if  the values are not compareble, i.e.
        when  the  collection  is  unordered  or  when  the  property  handle is
        invalid.

\return cmpval - Compare result

\param  sort_key1 - 
\param  sort_key2 - Second key
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareSortKey"

int8 PropertyHandle :: CompareSortKey (Key sort_key1, Key sort_key2 )
{
  ACObject    *obh = StartRTA();
  int8         comp_result = ERIC;
  ValidateNode(NO);
  
  comp_result = IsValid() 
                ? Tnodeptr->CompareSortKey(sort_key1.GetData(),
                                           sort_key2.GetData())
                : ERIC;

  obh->StopReadTA(NO);
  return(comp_result);
}

/******************************************************************************/
/**
\brief  CompareType - Check properties for comparability

        The  function  checks  the  comparability  for  the data of two property
        handles.  Usually  property  handles  are  considered as comparable when
        they  have the same  type. When requesting  data convertion (passing YES
        for  convert)  the  function  checks,  whether  the types are comparable
        after conversion.

\return term - Termination code

\param  prop_hdl - Property Handle
\param  convert - Conversion option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareType"

logical PropertyHandle :: CompareType (PropertyHandle &prop_hdl, logical convert )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
  ValidateNode(NO);
  prop_hdl.ValidateNode(NO);
  
  term = IsValid() && prop_hdl.IsValid()
         ? Tnodeptr->CompareType(prop_hdl.Tnodeptr,convert)
         : YES;

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Contains - Does property contain text

        The  function  checks,  wether  the  instance  for the selected property
        handle  contains  the  text  passed  in reg_string. The function returns
        true (YES), when the text has been found.
        This  version supports simple string expressions as 'string", '*string',
        'string*'  and '*string*'.  When not  beginning or terminting the search
        string  with an '*', the text must be  at the beginning or at the end of
        a word. Searching for 'string' will search for whole words, only. 
        compareble,  i.e. when the collection is  unordered or when the property
        handle is invalid.

\return cond - Return value
/******************************************************************************/
/**
\brief  i00 - Search for text in instance

        When  the instance is a structures  instance, the function is called for
        all  attributes and MEMO fields in  the selected instance. Otherwise the
        data in the attribute or MEMO field is checked.

\param  reg_string - Regular string expression
\param  case_opt - Case sensitive
\param  conv_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Contains"

logical PropertyHandle :: Contains (char *reg_string, logical case_opt, logical conv_opt )
{
  ACObject    *obh = StartRTA();
  char        *str = NULL;
  logical      term = YES;

  if ( conv_opt )
    if ( str = ReplaceControlSequences(reg_string,UNDEF,YES) )
      reg_string = str;
    
  term = IsSelected() || IsMemo()
         ? Tnodeptr->Contains(reg_string,case_opt) 
         : NO;
  if ( str )
    free(str);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - Search for text in property

        The  function  searches  for  the  text  in  the  property  passed  in 
        'prop_path'.  This implementation has been  provided for convinience. It
        does the same as prop_path.Contains(reg_string).

\param  reg_string - Regular string expression
\param  prop_path - Property path
\param  case_opt - Case sensitive
\param  conv_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Contains"

logical PropertyHandle :: Contains (char *reg_string, char *prop_path, logical case_opt, logical conv_opt )
{

  return( GetPropertyHandle(prop_path)->Contains(reg_string,case_opt,conv_opt) );

}

/******************************************************************************/
/**
\brief  ConvertToWinChar - Converts ASCII character into Windows compatible ANSI character set

        The  function converts  ASCII character  in a  text property handle into
        Windows  compatible ANSI character.  The data is  updated in-place and a
        data modification is signaled.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToWinChar"

logical PropertyHandle :: ConvertToWinChar ( )
{
  fmcb                   *fmcbptr;
  void                   *areaptr;
  logical                 term    = NO;
BEGINSEQ
  if ( !(areaptr = &ProvideArea()) )                 ERROR
    
  if ( !(fmcbptr = Tnodeptr->GetInstFieldDef()) )    ERROR
  if ( !IsText() )                                   ERROR
  
  gvtxans((uchar *)areaptr,fmcbptr->fmcbsize);
  if ( Modify() )                                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy - Copy instance

        The  function allows copying instances from one collection into another.
        The  function creates a  new instance that  is filled with the data from
        the  source  instance.  The  function  allows  copying instances between
        collections in different databases. 
        The  source handle must point to a selected instance that is copied into
        the  target handle collection. The target property handle must be opened
        for write access. 
        Source  and target property handle may refer to collections of different
        types.  Properties of the copied instances  are copied by name. Names of
        property  handles in base structured are considered without prefix. When
        the  target collection is  weak-typed, the type  for the target instance
        must be set by the application before copying the instance (SetType()).
        When  the  instance  to  be  copied  does  already  exist  in the target
        collection,  which  is  determined  according to the sort order selected
        for  the target collection, different replace options ({r. PIREPL}) will
        control  the  copy  behaviour  (replopt).  Copying  an existing instance
        without  requesting replacement of existing  instances will result in an
        error.  When  no  unique  sort  order  has  been  selected instances are
        considered as not existing and are copied always. 
        Copying  instances includes copying  related collections (references and
        relationships).  Only primary  relationships (not  defined as secondary)
        are  copied  to  avoid  unlimited  recursions.  When  copyinf  related 
        collection  the  replace  option  is  passed  to  the  subsequent  copy 
        operations. 
        The  copy type  supports a  two phase  copy process. Normally copying an
        instance  owning  parts  and  primary  relationships are copied at once.
        Sometimes  this  may  lead  to  logical  problems since it is not always
        possible  to  ensure  that  base  collections  are copied before copying
        primary  relationships based on it. Since  this leads to incomplete copy
        operations  a two phase copy can be  used copying first the owning parts
        (REPL_instance)  and later with  a second call  of the copy function the
        primary relationships (REPL_relationship). 
        When  Copy terminates succesfully the copied instance is selected in the
        target  property handle  and the  instance is returned. When terminating
        with errors the function returns an emty instance.

\return instance - Instance area
/******************************************************************************/
/**
\brief  i00 - Copy selected instance

        The  function  copies  the  selected  instance  from the source property
        handle to the target property handle.

\param  source_handle - Source property handle
\param  replopt - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

Instance PropertyHandle :: Copy (PropertyHandle &source_handle, PIREPL replopt, PIREPL copy_type )
{

  return ( Copy(source_handle,Key(),replopt,copy_type) );

}

/******************************************************************************/
/**
\brief  i01 - Copy and rename

        The  implementation copies the selected  instance to the target property
        handle.  The sort key  of the instance  according to the settings in the
        target  property handle is changed to the passed key value. When the new
        key  value  does  already  exist  in  the  target  collection  and  the 
        collection  index requires unique  keys, no instance  will be copied and
        the  function  returns  NULL,  as  long  as  the replace option does not
        explicitly allow overwriting the instance. .

\param  source_handle - Source property handle
\param  new_key - New key for the instance
\param  replopt - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

Instance PropertyHandle :: Copy (PropertyHandle &source_handle, Key new_key, PIREPL replopt, PIREPL copy_type )
{

  return ( Copy(source_handle,new_key,AUTO,replopt,copy_type) );

}

/******************************************************************************/
/**
\brief  i02 - Copy to position

        This  implementation  copies  the  selected  instance  from  the  source
        instance  at the position passed in  set_pos_w in the target collection.
        When  the  passed  position  is  greater  that the collection count, the
        position  is  changed  to  the  number  of  instances  in  the  target 
        collection.  When  passing  AUTO,  the instance is positioned infront of
        the  selected  instance  in  the  target  collection  (if an instance is
        selected) or appended at the end of the list, otherwise.
        When  the collection is ordered, the  position passed is ignored and the
        instance is inserted according to the key value in the source instance.

\param  source_handle - Source property handle
\param  set_pos0 - Position in collection
\param  replopt - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

Instance PropertyHandle :: Copy (PropertyHandle &source_handle, int32 set_pos0, PIREPL replopt, PIREPL copy_type )
{

  return ( Copy(source_handle,Key(),set_pos0,replopt,copy_type) );


}

/******************************************************************************/
/**
\brief  i03 - 



\param  source_handle - Source property handle
\param  new_key - New key for the instance
\param  set_pos0 - Position in collection
\param  replopt - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

Instance PropertyHandle :: Copy (PropertyHandle &source_handle, Key new_key, int32 set_pos0, PIREPL replopt, PIREPL copy_type )
{
  ACObject    *obh = StartRTA();
  Instance     ph_inst;
  if ( !ValidateNode(YES) && source_handle.IsPositioned() )
    if ( Tnodeptr->CopyInst(source_handle.Tnodeptr,replopt,
                            copy_type,new_key.GetData(),set_pos0,YES) )
       ph_inst = Tnodeptr->GetArea();

  obh->StopReadTA(NO);
  return(ph_inst);
}

/******************************************************************************/
/**
\brief  CopyData - Copy data from an instance area

        The  function  copies  the  data  from the instance area passed into the
        selected instance of the property handle.

\return term - Termination code
/******************************************************************************/
/**
\brief  i00 - Copy attributes from the instance passed

        The  structure of the instance area  must correspond to the structure of
        the property handle.
        Passing 'switchopt' YES will store the instance immediately.

\param  instance - Instance area
\param  switchopt - Unselct option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyData"

logical PropertyHandle :: CopyData (Instance instance, logical switchopt )
{
  ACObject    *obh = StartRTA();
  DBFieldDef  *field_def;
  void        *datarea;
  logical      term = NO;
BEGINSEQ
  if ( !(datarea   = &ProvideArea()) )               ERROR
  if ( !(field_def = Tnodeptr->GetInstFieldDef()) )  ERROR
  
  if ( Tnodeptr->CheckModify() )                     ERROR
  
  if ( field_def->fmcbbase() )
    memcpy(datarea,instance.GetData(),field_def->fmcbbyte);
  else
  {
    if ( !field_def->fmcbsmcb )                      SDBERR(99)
    field_def->fmcbsmcb->CopyInstance((char *)datarea,field_def->fmcbsmcb,(char *)instance.GetData(),AUTO);
    if ( Tnodeptr->PrepareGenAttribute() )           ERROR
    field_def->fmcbsmcb->CopyInstance((char *)datarea,field_def->fmcbsmcb,(char *)instance.GetData(),AUTO);
    if ( Tnodeptr->ResetGenAttribute() )             ERROR
  }
  
  if ( !Tnodeptr->Modify(AUTO) )                     ERROR
  Tnodeptr->Store();
  if ( Save(NO,switchopt) )                          ERROR

//  if ( switchopt )  // waere optimaler im Save()
//    ToTop();

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - Copy instance data from source instance

        The  implementation copies  the data  from the  source instance into the
        target  instance. All direct properties (attributes and base structures)
        are  copied by name.  References and relationships  are copied, when not
        yet  existing  or  when  replace  opt  REPL_local  (for  references)  or
        REPL_all (for references and relationships) has been defined.
        When  the target is sorted, the sort  key is not copied from the source.
        When  the  target  is  not  sorted,  but an ident-key is defined for the
        structure, the ident-key remains unchanged.
        The  target instance will  not be initialized,  i.e. fields not existing
        in the source instance are not changed.

\param  source_handle - Source property handle
\param  replopt - Replace option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyData"

logical PropertyHandle :: CopyData (PropertyHandle &source_handle, PIREPL replopt )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
BEGINSEQ
  if ( ValidateNode(YES) )                          ERROR
  if ( source_handle.ValidateNode(YES) )            ERROR
  
  term = IsValid() && source_handle.IsValid()
         ? Tnodeptr->CopyInstance(source_handle.Tnodeptr,replopt,NO) ? NO : YES
         : NULL;

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  CopyDescription - Create a copy for the property description

        The  function  creates  a  copy  for the property definition that can be
        modified  in the  application. Do  never modify the description profided
        by the system.

\return term - Termination code

\param  prop_def - Property definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDescription"

logical PropertyHandle :: CopyDescription (DBFieldDef *prop_def )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( GetValid() )
    term = Tnodeptr->CopyDescription(prop_def);

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  CopyHandle - Create a copy of the property handle

        The  function creates  a copy  of the  property handle when being called
        with  a property handle  reference. A copy  of a property handle has its
        own  cursor but  refers to  the same  data source (collection, instance,
        value).
        When  passing  a  property  handle  pointer the function creates another
        property  handle  that  shares  the  data source and the cursor with its
        origin.  In this case  changing the selection  in the origin or the copy
        will always affect the other handle as well.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyHandle"

logical PropertyHandle :: CopyHandle (PropertyHandle &prop_hdl )
{
  logical    term = NO;
BEGINSEQ
  if ( !prop_hdl.IsValid(NO) )                       ERROR
    
  Close();

  if ( Open(prop_hdl) )                              ERROR
RECOVER
  Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  property_handle - Pointer to a property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyHandle"

logical PropertyHandle :: CopyHandle (PropertyHandle *property_handle )
{

  return ( property_handle->IsValid(NO) 
           ? RegisterNode(property_handle->get_nodeptr())
           : RegisterNode(NULL) );

}

/******************************************************************************/
/**
\brief  CopyInst - Copy transient instance

        The  function  allows  copying  a  transient  instance  into  the  the 
        collection  referenced  by  the  property  handle. Source and target may
        have  different structure definitions. Properties are copied by property
        names.  Type conversion  is performed  when necessary. After copying the
        attributes  the function tries  to locate the  instance according to the
        sort  key  or  the  ident  key  (if  no order is defined). Otherwise the
        function  tries to locate the instance  in the base collection (if there
        is  any). When the instance does already exist in the collection it will
        be  overwritten according to the replace options. Otherwise the instance
        is added to the collection.

\return targinst - Traget instance

\param  srceinst - Source instance
\param  srcesmcb - Pointer to general structure definition
\param  replopt - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInst"

Instance PropertyHandle :: CopyInst (Instance srceinst, smcb *srcesmcb, PIREPL replopt, PIREPL copy_type )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->CopyInst(&srceinst,srcesmcb,replopt,copy_type,NULL);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  CopyInstance - Copy Instance

        Copy  data  to  instance  area.  If an instance is selected the function
        will cancel the instance.
        Called internally, only.

\return term - Termination code

\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstance"

logical PropertyHandle :: CopyInstance (Instance instance )
{
  ACObject    *obh = StartRTA();
  void        *datarea;
  DBStructDef *struct_def;
  DBFieldDef  *field_def;
  logical      term = NO;
BEGINSEQ
  if ( ValidateNode(YES) )                           ERROR
  
  if ( !nodeptr->get_nodeinst() || 
       !(datarea = nodeptr->get_nodeinst()->get_iselarea()) || 
       !instance.GetData() )                         ERROR
       
  if ( !(field_def = Tnodeptr->GetInstFieldDef()) )  ERROR
  
  if ( field_def->fmcbbase() )
    memcpy(datarea,instance.GetData(),field_def->fmcbbyte);
  else
  {
    if ( !(struct_def = Tnodeptr->GetCurrentTypeDef()) ) 
                                                     SDBERR(99)
    struct_def->CopyInstance((char *)datarea,struct_def,(char *)instance.GetData(),AUTO);
  }

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  CopyInstanceArea - 



\return term - Termination code

\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstanceArea"

logical PropertyHandle :: CopyInstanceArea (PropertyHandle &prophdl )
{
  logical         term = NO;
BEGINSEQ
  if ( !prophdl.IsValid() )                          ERROR
  
  ProvideNode();
  if ( nodeptr->get_nodetype() == NT_Node && prophdl.Inherits(*this) )
  {
    if ( Tnodeptr->CopyInstanceArea(prophdl.GetNode()) )
                                                     ERROR
  }  
  else
    SetValue(prophdl);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopySet - Copy collection

        The  function  copies  all  instances  of  the  source collection to the
        target  collection. The  function works  well for multiple references as
        well  as  for  single  references.  The function cannot be used for MEMO
        fields. 
        The target Property Handle must be opened in unpdate mode (PI_Write). 
        Source  and target need not to refer to the same object type. Attributes
        and  references are copied  by property name,  i.e. they are assigned by
        looking  for  the  same  property  name  in  the  target  instance. Data
        conversin  is  performed  automatically  if possible. This includes also
        convertind imbedded instances into references and reverse.
        The  target collection is not  emptied automatically. Existing instances
        in  the target  are replaced  according to  the replace option passed to
        the function.
        When  successfull the function returns the number of instances copied to
        the  target collection (including 0 when the source was empty). When the
        function  has  terminated  because  of  an  error  it returns AUTO (-1).
        Source  and  target  handle  are  not  positioned  after terminating the
        function.

\return count - Number of entries
/******************************************************************************/
/**
\brief  i0 - 



\param  csource_handle - Source property handle
\param  replopt - Replace option
\param  copy_type - Copy type
\param  inverse_check - Check inverse reference
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopySet"

int32 PropertyHandle :: CopySet (const PropertyHandle &csource_handle, PIREPL replopt, PIREPL copy_type, logical inverse_check )
{
  ACObject    *obh = StartRTA();
  int32        count = ERIC;
  if ( !ValidateNode(YES) && !csource_handle.ValidateNode(YES) )
    count = Tnodeptr->CopySet(csource_handle.Tnodeptr,inverse_check,replopt,copy_type);


  obh->StopReadTA(NO);
  return(count);
}

/******************************************************************************/
/**
\brief  CreatePIHandle - Create property handle for set operations



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pi_liste - List of collection handles
\param  count - Number of entries
\param  operation - Operation to be performed
\param  sk_opt - Sort key option
\param  transient_w - Transient option
\param  key_name_w - Key name for conversion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePIHandle"

logical PropertyHandle :: CreatePIHandle (PropertyHandle **pi_liste, int32 count, int16 operation, char sk_opt, logical transient_w, char *key_name_w )
{
  DictionaryHandle    dictptr;
  int32                indx0;
  char               *strname = NULL;
  char                strnames[ID_SIZE+1];
  char               *keyname = NULL;
  smcb               *keysmcb;
  logical             wk_opt  = NO;
  logical             term    = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !count )                                      SDBERR(99)
  
  if ( nodeptr && Tnodeptr )
  {
    strname = Tnodeptr->GetSMCB()->smcbname;         SDBCERR
  }
   
  if ( key_name_w && *key_name_w )
  {
    sk_opt = YES;
    keyname = key_name_w;
  }
   
  for ( indx0 = 0; indx0 < count; indx0++ )
  {
    if ( pi_liste[indx0]->ValidateNode(YES) )           ERROR
    if ( !strname )
    {
      strname = pi_liste[indx0]->GetStructDef()->smcbname;
      wk_opt  = pi_liste[indx0]->IsWeakTyped();
    }
    else if ( !sk_opt )
      if ( memcmp(strname,pi_liste[indx0]->get_nodeptr()->GetSMCB()->smcbname,ID_SIZE) )
                                                     SDBERR(171)
    if ( sk_opt )
    {
      if ( !( sk_opt == YES && (keysmcb = pi_liste[indx0]->GetSortKeySMCB()) ) && 
           !(keysmcb = pi_liste[indx0]->GetKeySMCB())        )
      {
        SDBEV1(pi_liste[indx0]->GetDescription(NO)->fmcbname,ID_SIZE);
                                                     SDBERR(172)
      }
      if ( !keyname )
        keyname = keysmcb->smcbname;
//      else Vergleichbarkeit der schluessel pruefen
//        if ( memcmp(keyname,keysmcb->smcbname,ID_SIZE) )  SDBERR(173)
    }
  }
  
  if ( !nodeptr )
  {
    gvtxbts(strnames,strname,ID_SIZE);
    if ( transient_w )
    {
      if ( Open(pi_liste[0]->GetObjectHandle(),strnames,PI_Write,transient_w,keyname) )
                                                     ERROR
    }
    else
    {
      if ( Open(pi_liste[0]->GetObjectHandle(),strnames,keyname,NULL,wk_opt,NO) )
                                                     ERROR
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  obhandle - 
\param  dbfielddef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePIHandle"

logical PropertyHandle :: CreatePIHandle (DBObjectHandle &obhandle, DBFieldDef *dbfielddef )
{
  logical          term = NO;
  PropertyHandle   phtemp;

BEGINSEQ
  if ( !this )                                       ERROR
  if ( IsValid() )                                   LEAVESEQ
  phtemp = obhandle.CreateTempPropertyHandle(dbfielddef);
  *this = phtemp;
  if ( !nodeptr )                                    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  pibref - Reference to collection handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePIHandle"

logical PropertyHandle :: CreatePIHandle (PropertyHandle &pibref )
{
  DBObjectHandle   obhandle = pibref.GetObjectHandle();
  PropertyHandle   phtemp;
  logical          term = NO;
BEGINSEQ
  if ( pibref.ValidateNode(YES) )                    ERROR
  
  if ( nodeptr || !(obhandle = pibref.GetObjectHandle()) )   
                                                     LEAVESEQ
  phtemp = obhandle.CreateTempPropertyHandle(pibref);
  *this = phtemp;
  if ( !nodeptr )                                    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  pibref - Reference to collection handle
\param  grouping_rule - Grouping rule
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePIHandle"

logical PropertyHandle :: CreatePIHandle (PropertyHandle &pibref, char *grouping_rule )
{
  DBObjectHandle  obhandle = pibref.GetObjectHandle();
  PropertyHandle  phtemp;
  logical          term = NO;
BEGINSEQ
  if ( pibref.ValidateNode(YES) )                    ERROR
  
  if ( nodeptr || !(obhandle = pibref.GetObjectHandle()) )   
                                                     LEAVESEQ
  phtemp  = obhandle.CreateTempPropertyHandle(pibref,grouping_rule);
  *this = phtemp;
  if ( !nodeptr )                                    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateTempExtent - Creates a temporary extent

        This  function  can  be  used  to open a property handle for a transient
        collection  property  (transient  reference).  The  property must have a
        definition  that has been provided by  the constructor or an appropriate
        open function. 
        The  function creates a  temporary collection with  the structure of the
        transient  reference property.   The property  handle is opened in write
        mode,  always. If the collection is  already opened the function returns
        without  error.   You  can  reset  the  transient  reference  using  the
        ResetTransientProperty() function.
        The  function  returns  an  error  (YES) if the property handle does not
        define a transient reference.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  obhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

logical PropertyHandle :: CreateTempExtent (DBObjectHandle &obhandle )
{
  DBFieldDef  *field_def;
  PropertyHandle phtemp;
  logical      term = NO;
BEGINSEQ
  if ( !IsValid(NO) || !obhandle.IsOpened() )          ERROR
    
  if ( !(field_def = nodeptr->GetFieldDef()) )       ERROR
  if ( !IsTransient() || field_def->fmcbrlev != R_REFR )   
                                                     ERROR

  if ( Tnodeptr )                                    LEAVESEQ // transien reference already opened
  phtemp = obhandle.CreateTempPropertyHandle(field_def);
  SetTransientProperty(phtemp); 
  if ( !Tnodeptr )                                   ERROR
  Tnodeptr->Release((ObjectReferenceHandle *)this);  // node gehört der transienten Reference
  
  if ( Tnodeptr->get_highnod() )
    GetPropertyContext()->set_high_ctx(Tnodeptr->get_highnod()->GetInstContext());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prophdl_ref - Reference to Property handle
\param  extnames_w - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

logical PropertyHandle :: CreateTempExtent (PropertyHandle &prophdl_ref, char *extnames_w )
{
  DBFieldDef             *field_def;
  logical                 term = YES;
BEGINSEQ
  if ( !this || (nodeptr && !IsValid()) || 
       !prophdl_ref.IsValid() )                      ERROR
  Close();
  
  if ( CreatePIHandle(prophdl_ref) )                 ERROR
  
  if ( !(field_def = nodeptr->GetFieldDef()) )       ERROR 
  if ( field_def->fmcbrlev != R_REFR )               ERROR

  if ( !GetArea() && AllocateArea() )                ERROR
  
  if ( nodeptr->get_highnod() )
    GetPropertyContext()->set_high_ctx(nodeptr->get_highnod()->GetInstContext());


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - Delete/remove instance from collection

        The  function  removes  the  selected  instance from the collection. Whe
        passing  a key or a position the  function selects the instance with the
        passed  key  or  the  given  position  before  removing  it  from  the 
        collection.  Deleting by key  is possible only  when a sort order with a
        unique  key  has  been  selected.  For  removing  an  instance  from  a 
        collection  the  property  handle  must  be  opened  in  write mode. For
        deleting  the instance the selected instance  must be available in write
        mode as well.  
        Removing  an  instance  from  a  collection  will delete the instance as
        well,  when the collection is owning  the instance or when the instances
        in  the  collection  do  depend  on the collection. You may also request
        deleting the instance by passing YES for the del_dep parameter. 
        Removing  an instance  from a  collection it will maintain automatically
        inverse  references. Moreover, the instance  is removed from all derived
        collections  (subsets). This means the  instances might be deleted also,
        when being dependent on one of the derived collections. 
        When  deleting the instance  derived instances are  deleted as well. All
        inverse relationships and subset relationships are maintained.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  A00 - 



\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical PropertyHandle :: Delete (PropertyHandle &prop_hdl )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  Key          key;
  if ( (key = GetKeyFromParm(prop_hdl)).GetData() )
    term = Delete(key);
  else if ( prop_hdl.IsNumeric() )  
    term = Delete(prop_hdl.GetInt());


  obh->StopReadTA(NO);
  return(YES);
}

/******************************************************************************/
/**
\brief  ByKey - Delete instance by key

        The  function  deletes  an  instance  by  key. When no instance with the
        passed key can be located, the function terminates with error.

\param  sort_key - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical PropertyHandle :: Delete (Key sort_key )
{
  ACObject    *obh = StartRTA();
  logical      term;
  term = !ValidateNode(YES)
         ? Tnodeptr->Delete(sort_key.GetData()) 
         : YES;

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  OnPosition - Delete instance by position

        The  function  deletes  the  instance  at  the  position  passed  to the
        function  (set_pos0_w).  When  AUTO  is  passed  the current instance is
        deleted. Dependent instances are usually deleted as well (del_dep=YES). 
        When  passing NO, depending  instances are not  deleted, as long as they
        are not owned by the current instance.

\param  set_pos0_w - Position in collection
\param  del_dep - Delete dependent instances
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical PropertyHandle :: Delete (int32 set_pos0_w, logical del_dep, logical del_inst )
{
  ACObject    *obh = StartRTA();
  logical      term;
  term = !ValidateNode(YES)
         ? Tnodeptr->Delete(set_pos0_w,YES,del_dep,del_inst) 
         : YES;
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteIndexEntry - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  set_pos0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteIndexEntry"

logical PropertyHandle :: DeleteIndexEntry (int32 set_pos0 )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
  if ( ValidateNode(NO) )
  {
    if ( set_pos0 >= 0 )
      GetKey(set_pos0);
    term = Tnodeptr->DeleteIndexEntry();
  }
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteSet - Delete/remove all instance in a collection

        The  function removes  all instances  from the collection. Instances are
        removed/deleted  as  described  in  the  Delete()  function.  When  the 
        finction fails the collection remains unchanged.

\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  del_dep - Delete dependent instances
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSet"

logical PropertyHandle :: DeleteSet (logical del_dep )
{
  ACObject    *obh = StartRTA();
  logical      term;
  term = !ValidateNode(YES)
         ? Tnodeptr->DeleteSet(YES,del_dep) 
         : YES;

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Dereference - Dereference collection handle

        The  function returns a dereferenced property handle. The Area is shared
        with  the  Area  of  the  original handle and the instance is associated
        with the collection of the original handle.

\return prop_hdl - Property Handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Dereference"

PropertyHandle *PropertyHandle :: Dereference ( )
{
  PropertyHandle    *prop_hdl = NULL;
  if ( !IsCollection() )
    prop_hdl = new PropertyHandle(this);
  else
  {
    prop_hdl = new PropertyHandle(GetDescription(),Instance(GetArea()));
    prop_hdl->get_nodeptr()->Connect(nodeptr);
  }


  return(prop_hdl);
}

/******************************************************************************/
/**
\brief  DisableKeyCheck - Disable key check

        The function disables the key check feature for the property handle.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableKeyCheck"

logical PropertyHandle :: DisableKeyCheck ( )
{

  return( IsValid() 
          ? Tnodeptr->DisableKeyCheck() 
          : YES );

}

/******************************************************************************/
/**
\brief  Distinct - 



\return prophdl_ref - Reference to Property handle
/******************************************************************************/
/**
\brief  i0 - 



\param  prophdl_ref - Reference to Property handle
\param  key_name_w - Key name for conversion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Distinct"

PropertyHandle &PropertyHandle :: Distinct (PropertyHandle &prophdl_ref, char *key_name_w )
{
  ACObject         *obh;
  PropertyHandle   *ph_list[] = {&prophdl_ref};

BEGINSEQ
  if ( key_name_w && !*key_name_w )
    key_name_w = NULL;
    
  if ( CreatePIHandle(ph_list,1,UNDEF,NO,NO,key_name_w) )   ERROR
  
  obh = StartRTA();
  Tnodeptr->Distinct(prophdl_ref.Tnodeptr);
  obh->StopReadTA(NO);

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  key_name_w - Key name for conversion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Distinct"

PropertyHandle &PropertyHandle :: Distinct (char *key_name_w )
{

  return( PropertyHandle().Distinct(*this,key_name_w));

}

/******************************************************************************/
/**
\brief  i03 - 



\param  prophdl_ref - Reference to Property handle
\param  key_name - Key name
\param  exectype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Distinct"

PropertyHandle &PropertyHandle :: Distinct (PropertyHandle &prophdl_ref, char *key_name, ExecutionTypes exectype )
{
  ACObject         *obh;
  PropertyHandle   *ph_list[] = {&prophdl_ref};
BEGINSEQ
  if ( !prophdl_ref.IsCollection() )                 LEAVESEQ
  
  if ( key_name && !*key_name )
    key_name = NULL;
    
  switch ( exectype )
  {
    case ET_Initialize : 
      Close();
      if ( CreatePIHandle(ph_list,1,UNDEF,NO,NO,key_name) )
                                                     ERROR
      GetDescription(NO)->set_set_operation(YES);
      break;
    
    case ET_First : 
      prophdl_ref.ToTop();
      obh = StartRTA();
      Tnodeptr->Distinct(prophdl_ref.Tnodeptr);
      obh->StopReadTA(NO);
      Get(FIRST_INSTANCE);
      break;
    
    case ET_Next : 
      Position(1);
      break;
    
    default :  
      Distinct(prophdl_ref,key_name); 
  }
RECOVER
  Close();
ENDSEQ
  return(*this);
}

/******************************************************************************/
/**
\brief  Duplicate - Duplicate instance

        You  can use duplicate to create a  new version of the selected instance
        in the same collection. 
        Duplicate  should  be  used  only,  if  the instance to be copied has no
        shared  base instances or if all shared base instances are identified by
        the  selected sort  key for  the instance.  If this  is not the case the
        system  trys to create  appropriate base instances  with refering to the
        original  base instance except base  instances identified by __AUTOIDENT
        or  __IDENTITY,  i.e.  Duplicate()  will  not  copy  automatic  keys but
        creates new base instances with new keys. 
        l,  when the collection is owning the  instance or when the instances in
        the  collection  do  depend  on  the  collection.  You  may also request
        deleting the instance by passing YES for the del_dep parameter. 
        Removing  an instance  from a  collection it will maintain automatically
        inverse  references. Moreover, the instance  is removed from all derived
        collections  (subsets). This means the  instances might be deleted also,
        when being dependent on one of the derived collections. 
        When  deleting the instance  derived instances are  deleted as well. All
        inverse relationships and subset relationships are maintained.

\return instance - Instance area
-------------------------------------------------------------------------------
\brief  A00 - 



\param  set_pos0 - Position in collection
\param  replopt - Replace option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Duplicate"

Instance PropertyHandle :: Duplicate (int32 set_pos0, PIREPL replopt )
{

BEGINSEQ
  SDBERR(999)

RECOVER

ENDSEQ
  return Instance();
}

/******************************************************************************/
/**
\brief  Key - 



\param  ident_key - Ident key value
\param  replopt - Replace option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Duplicate"

Instance PropertyHandle :: Duplicate (Key ident_key, PIREPL replopt )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( IsPositioned() )
    instance = Tnodeptr->Duplicate(ident_key.GetData(),replopt);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  EnableKeyCheck - Enable key check

        The  function enables key check  for evaluating filter expressions. This
        function  can be  called to  improve performance  for key functions that
        select  instances  from  a  collection  by  expression  or  context. The
        function  can  be  used  only,  when  the decision can  be made based on
        properties,  which are  key components  for the selected key. Otherwise,
        the   check   might   return   incorrect   result,  since all properties
        (attributes),  whiche are not key components, are initialized with their
        initial value when checking the instance.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableKeyCheck"

logical PropertyHandle :: EnableKeyCheck ( )
{

  return( IsValid() 
          ? Tnodeptr->EnableKeyCheck() 
          : YES );

}

/******************************************************************************/
/**
\brief  Execute - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical PropertyHandle :: Execute (ParmList *parmlist )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
  if ( !ValidateNode(NO) )
    term = Tnodeptr->Execute(parmlist);  


  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical PropertyHandle :: Execute ( )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
  if ( !ValidateNode(YES) )
    term = Tnodeptr->Execute(NULL);  


  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteExpression - Execute expression

        Execute  expression  allows  running  inline  expresions  or  persistent
        expressions.  When running  an inline  expression containing one or more
        statements,  the  expression  must  be  enclosed  in  {}.  The result is
        returned  as  property  handle,  which  allows  an  expression returning
        elementary or complex instances as well as instance collections.
        When  calling  a  persistent  expression stored in the resource database
        the expression name must be preceeded by the scope declarator (::).

\return prophdl - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  res_obhandle - 
\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteExpression"

PropertyHandle PropertyHandle :: ExecuteExpression (DBObjectHandle &res_obhandle, char *expression )
{
  ACObject       *obh  = StartRTA();
  PropertyHandle  ph;
  Operation       op;
BEGINSEQ
  ValidateNode(YES);
  if ( !IsValid() )                                 ERROR
      
  op.SetCallingObject(this);
  if ( !op.ProvExpression(Tnodeptr->GetDictionary(),
                          res_obhandle.get_obhandle(),
                          Tnodeptr->GetObjectHandle(),
                          expression) )
    if ( !op.Execute(Tnodeptr->GetObjectHandle(),NULL) )
    {
      ph.Open(&op);
      if ( ph.IsValid() )
        ph.get_nodeptr()->CopyDescription(NULL);
    }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(&ph);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  res_obhandle - 
\param  obhandle - 
\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteExpression"

PropertyHandle PropertyHandle :: ExecuteExpression (DBObjectHandle &res_obhandle, DBObjectHandle &obhandle, char *expression )
{
  ACObject       *obh  = StartRTA();
  PropertyHandle  ph;
  Operation       op;
BEGINSEQ
  ValidateNode(YES);
  if ( !IsValid() )                                  ERROR
      
  op.SetCallingObject(this);
  if ( !op.ProvExpression(obhandle.GetDictionary().get_dictionary(),
                          res_obhandle.get_obhandle(),
                          obhandle.get_obhandle(),
                          expression) )
    if ( !op.Execute(obhandle.get_obhandle(),NULL) )
      ph.Open(&op);

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(&ph);
}

/******************************************************************************/
/**
\brief  ExecuteInstanceAction - Execute action on instance level

        The  function calls an  action that is  defined in the structure context
        of the current instance. The function is executed on the server side.
        The  action may use the SetActionResult() function to pass the result of
        the  action to the client application.  The result can be retrieved from
        the client application using the function GetActionResult().

\return term - Termination code

\param  action_name - 
\param  parm_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteInstanceAction"

logical PropertyHandle :: ExecuteInstanceAction (char *action_name, char *parm_string )
{
  ACObject    *obh = StartRTA();
  logical      term;
  if ( IsValid() )
    Tnodeptr->set_result_string("",UNDEF);
    
  term = IsPositioned()
           ? Tnodeptr->ExecStrCtxFunc(action_name,parm_string)
           : YES;


  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ExecutePropertyAction - Execute action on property (collection) level

        The  function calls an action that  is defined in theproperty context of
        the property handle. The function is executed on the server side.
        The  action may use the SetActionResult() function to pass the result of
        the  action to the client application.  The result can be retrieved from
        the client application using the function GetActionResult().

\return term - Termination code

\param  action_name - 
\param  parm_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecutePropertyAction"

logical PropertyHandle :: ExecutePropertyAction (char *action_name, char *parm_string )
{
  ACObject    *obh = StartRTA();
  logical      term;
  if ( IsValid() )
    Tnodeptr->set_result_string("",UNDEF);
    
  term = !ValidateNode(NO)
         ? Tnodeptr->ExecPropCtxFunc(action_name,parm_string) 
         : YES;


  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Exist - 



\return cond - Return value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical PropertyHandle :: Exist ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
BEGINSEQ
  if ( ValidateNode(NO) )                           ERROR
  cond = Tnodeptr->Exist();


RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  ExtractKey - Extract ident key value

        The  function extracts  the ident  key value  according to the structure
        definition of the property handle. 
        When  no instance has been passed the function extracts the key from the
        currently  selected instance.  If no  instance has  been selected in the
        property  handle the function will set  the cursor to the first instance
        (if  possible).  When  no  instance could be selected (empty datasource)
        the function returns an empty key. 
        When  a  key  area  has  been  passed  in the key parameter the function
        returns  the key in the passed key area. When no key or an empty key has
        been  passed  the  returned  key  area refers to an internal area, which
        should  not be modified by the application. This area is valid until the
        next ODABA interface function has been called.
        When  the key to be extracted is the __IDENTITY key, an instance must be
        selected  in  the  property  handle  or  the  structure  must  have  an 
        __IDENTITY attribute. Otherwise, the function returns NULL.

\return ret_key - Key value
-------------------------------------------------------------------------------
\brief  i0 - Extracting ident key

        This  implementation extracts the ident key  from the selected or passed
        instance.

\param  ident_key_w - Ident key value
\param  instance_w - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

Key PropertyHandle :: ExtractKey (Key ident_key_w, Instance instance_w )
{
  ACObject    *obh = StartRTA();
  Key          key;
BEGINSEQ
  ValidateNode(YES);
  if ( !IsValid() )                                 ERROR

  key = Tnodeptr->ExtractKey(ident_key_w.GetData(),instance_w.GetData());


RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  i01 - Extract any key

        The  function extracts the key according to the key name passed. The key
        name must be one of the keys defined for the structure.

\param  key_name - Key name
\param  key - Key value
\param  instance_w - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

Key PropertyHandle :: ExtractKey (char *key_name, Key key, Instance instance_w )
{
  ACObject    *obh = StartRTA();
  Key          nkey;
  smcb        *smcbptr;
  kcb         *kcbptr = NULL;
BEGINSEQ
  ValidateNode(YES);
  
  if ( !IsValid() )                                  ERROR
  if ( !(smcbptr = Tnodeptr->GetSMCB()) )            SDBERR(79)
  if ( !(kcbptr = smcbptr->GetKCB(key_name)) )       SDBERR(79)

  if ( IsValid() )
    nkey = Tnodeptr->ExtractKey(key.GetData(),kcbptr,instance_w.GetData());


RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(nkey);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  key_name - Key name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

Key PropertyHandle :: ExtractKey (char *key_name )
{
  ACObject    *obh = StartRTA();
  Key          nkey;
  smcb        *smcbptr;
  kcb         *kcbptr = NULL;
BEGINSEQ
  ValidateNode(YES);
  
  if ( !IsValid() )                                  ERROR
  if ( !(smcbptr = Tnodeptr->GetSMCB()) )            SDBERR(79)

  if ( key_name && *key_name )
  {
    if ( !(kcbptr = smcbptr->GetKCB(key_name)) )     SDBERR(79)
    nkey = Tnodeptr->ExtractKey(NULL,kcbptr,NULL);
  }
  else
    nkey = Tnodeptr->ExtractKey(NULL,NULL);


RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(nkey);
}

/******************************************************************************/
/**
\brief  ExtractSortKey - Extract sort key value

        The  function extracts the key value  according to the curent sort order
        (index). 
        When  no instance has been passed the function extracts the key from the
        currently  selected instance.  If no  instance has  been selected in the
        property  handle the function will set  the cursor to the first instance
        (if  possible).  When  no  instance could be selected (empty datasource)
        the function returns an empty key. 
        When  a  key  area  has  been  passed  in the key parameter the function
        returns  the key in the passed key area. When no key or an empty key has
        been  passed  the  returned  key  area refers to an internal area, which
        should  not be modified by the application. This area is valid until the
        next ODABA interface function has been called.

\return ret_key - Key value
-------------------------------------------------------------------------------
\brief  i0 - 



\param  sort_key - Sort key value
\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractSortKey"

Key PropertyHandle :: ExtractSortKey (Key sort_key, Instance instance )
{
  ACObject    *obh = StartRTA();
  Key          key;
BEGINSEQ
  ValidateNode(YES);
  if ( !IsValid() )                                 ERROR

  key = Tnodeptr->ExtractSortKey(sort_key.GetData(),instance.GetData());

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  sort_key_w - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractSortKey"

Key PropertyHandle :: ExtractSortKey (Key sort_key_w )
{
  ACObject    *obh = StartRTA();
  Key          key;
  ValidateNode(YES);
  
  if ( IsValid() )
    key = Tnodeptr->ExtractSortKey(sort_key_w.GetData(),NULL);

  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  Fill - Fill instance from external one

        The  function copies  all fields  including references from the instance
        passed to the function into the selected instance.

\return term - Termination code

\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical PropertyHandle :: Fill (Instance instance )
{
  ACObject    *obh = StartRTA();
  logical      term;
  term = !ValidateNode(YES) 
         ? Tnodeptr->FillAll(instance.GetData())
         : YES;

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  FillData - Fill instance from external one

        The  function  copies  all  fields  without references from the instance
        passed to the function into the selected instance.

\return term - Termination code

\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

logical PropertyHandle :: FillData (Instance instance )
{
  ACObject    *obh = StartRTA();
  logical      term;
  term = !ValidateNode(YES)
         ? Tnodeptr->FillData(instance.GetData())
         : YES;

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  FirstKey - Locate first key

        The  function  locates  the  first  sort key in the index. When the data
        source  is  unordered  the  function  locates  the  first  instance  and
        extracts the ident key.  
        The  returned key area  refers to an  internal area, which should not be
        modified  by the  application. This  area is  valid until the next ODABA
        interface function has been called.

\return sort_key - Sort key value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstKey"

Key PropertyHandle :: FirstKey ( )
{
  ACObject    *obh = StartRTA();
  Key          key;
  if ( !ValidateNode(YES) )
    key = Tnodeptr->FirstKey(); 

  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  Format - Get formatted string

        The  function  returns  a  formatted  string,  where  place  holders are
        replaced  by  values  of  the  current instance or values evaluated from
        expressions.  The  function  requires  a  selected  instance.  When  no 
        instance is selected, the function returns NULL.
        The  function returns a  NULL terminated string  in the property handles
        work  area.  This  might  be  destroyed  after calling the next property
        handle function with the current property handle.

\return string - String area
/******************************************************************************/
/**
\brief  i0 - 



\param  fstring - Format string
\param  parm_list - Parameter list
\param  parm_count - Number of parameters
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Format"

char *PropertyHandle :: Format (char *fstring, char **parm_list, int16 parm_count )
{
  ACObject    *obh = StartRTA();
  char        *string = NULL;
  if ( IsValid() )
    string = Tnodeptr->Format(fstring,parm_list,parm_count);

  obh->StopReadTA(NO);
  return(string);
}

/******************************************************************************/
/**
\brief  Get - Get property instance

        The  Get() function  allows selecting  an instance  in a property handle
        collection  by key or position. The function  can also be used to locate
        an  instance  in  an  array  attribute  or  to  get  a  single attribute
        instance.  Before a new instance is selected the curent selection in the
        property  handle is cancelled. in case  of instance modifications on the
        previously  selected instance  those are  saved automatically. Selecting
        an  instance will also cancel the selection of all subordinated property
        handles. 
        The  function  returns  the  instance  that  has  been  selected  in the
        property  handle  when  is  has been executed successfully. Otherwise it
        returns an empty instance.

\return instance - Instance area
-------------------------------------------------------------------------------
\brief  A00 - Get instance by value in the property handle

        When  passing  the  value  for  locating an instance in a collection via
        property  hanndle, Get() is  called as get  by key or index depending on
        the data type defined in the property handle. 
        When  the value property handle passes a structured instance of the same
        or  a specialized type as the instance  to be selected, the key value is
        extracted  from the  instance passed  in the  property handle and get by
        key is used.
        When  passing  a  text  value  (STRING,  MEMO or CHAR), the text data is
        considered  as string key  where key komponents  are separated by |. You
        cannot pass a structured key (Key) my means of property handles. 
        If  not the key or instant version is used the 'get by position' version
        is  called. Non-integer numerical  values are rounded  to the next lower
        integer number.

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

Instance PropertyHandle :: Get (PropertyHandle &prop_hdl )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  Key          key;
  if ( (key = GetKeyFromParm(prop_hdl)).GetData() )
    instance = Get(key);
  else 
    instance = Get(prop_hdl.GetInt());
  

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  AtPosition - Get Instance by index position

        Reading  an instance by  position is locating  the instance on the given
        location  in  the  selected  index  (sort  order). Thus, the result will
        change  usually  when  changing  the  selected index for the collection.
        Using  index positions for reading is also a weak point when indexes are
        updated  simultaneously,  since  the  index  position  might change when
        other  users insert or remove entries from  the index. To avoid this you
        may  use  the  LockSet()  function,  that locks the complete collection.
        Access  by position,  however, is  a comfortable  way browsing through a
        collection.  Access by position cannot be used for LOID or GUID property
        handles.  Passing a number  to an LOID  handle interpretes the number as
        local object identity. 
        For  a  path  property  Get()  by  position  automatically  changes  the
        selection  for higher properties in the  path when the end of collection
        is signaled an a level that is not the top level for the path property. 
        Passing  AUTO  as  position  the function returns the instance currently
        selected  in  the  property  handle.  When  no  instance is selected the
        function  returns the first instance in the collection. When an instance
        is  selected in the property handle and the current access mode does not
        correspond  to the required  access mode, the  function will re-read the
        instance.  Thus, the function can be used to update the access mode when
        the  selected instance  was write  protected. Selections in subordinated
        property handles are canceled when re-reading the instance.

\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

Instance PropertyHandle :: Get (int32 set_pos0_w )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->Get(set_pos0_w);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  ByKey - Get instance by key value

        When  reading  an  instance  by  key,  this  is considered as key in the
        currently  selected index (SetOrder()). When the  key cannor be found in
        the  index the function  returns an empty  instance. It is also possible
        to  locate an  instance by  key in  an unordered collection, when it has
        been  marked as  unique (no  duplicate instances).  In this case the key
        must  be  passed  according  to  the structure of the ident key. The key
        must be passed according to the internal key structure. 
        The  key can also be  an LOID or a  GUID string when the property handle
        has  been opened for  reading by local  object identities (__LOID) or by
        global unique identifiers (__GUID).
        When  positioning the instance for a  path property the key must consist
        of all sort keys along the path. 
        n  automatically changes the selection for higher properties in the path
        when  the end of collection  is signaled an a  level that is not the top
        level for the path property. 
        Passing  AUTO  as  position  the function returns the instance currently
        selected  in  the  property  handle.  When  no  instance is selected the
        function  returns the first instance in the collection. When an instance
        is  selected in the property handle and the current access mode does not
        correspond  to the required  access mode, the  function will re-read the
        instance.  Thus, the function can be used to update the access mode when
        the  selected instance  was write  protected. Selections in subordinated
        property handles are canceled when re-reading the instance.

\param  sort_key - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

Instance PropertyHandle :: Get (Key sort_key )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->Get(sort_key.GetData()); 

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  GetActionResult - Get result from last action executed

        The  function  returns  the  resultstring from the last action executed.
        The  result string is  available until the  next action call, only. When
        the action does not return a result the function returns NULL.

\return result_string - Result string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActionResult"

char *PropertyHandle :: GetActionResult ( )
{

  return ( IsValid() 
           ? (char *)Tnodeptr->get_nstring() 
           : NULL );


}

/******************************************************************************/
/**
\brief  GetArea - Get Instance area

        The  function  returns  the  instance  area  for the property handle. In
        contrast  to  GetInstance()  the  function  returns the instance area as
        (char  *) pointer regardless  on whether an  instance is selected in the
        property handle or not.
        The  function will always return a data area when the propertyhandle has
        a  valid  description.  Hence  it  cannot be used for checking whether a
        data  area  is  available.  For  checking  whether  a data area has been
        allocated use HasData().

\return inst_area - Instance area
-------------------------------------------------------------------------------
\brief  i0 - Provide area for current property handle

        The function returns the area for the current property handle.

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetArea"

char *PropertyHandle :: GetArea (char chkopt ) const
{
  ACObject    *obh = StartRTA();
  char        *area = NULL;
  if ( chkopt )
    ValidateNode(YES);
  
  if ( IsValid() )
    area = (char *)Tnodeptr->GetArea();

  obh->StopReadTA(NO);
  return(area);
}

/******************************************************************************/
/**
\brief  i01 - Provide area for subsequent property

        The  function tries to  locate the passed  property and returns the area
        for  this propertyinstance when the property exist. The function returns
        an error, when NULL or an empty property path is passed.

\param  prop_path - Property path
\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetArea"

char *PropertyHandle :: GetArea (char *prop_path, char chkopt ) const
{
  ACObject    *obh = StartRTA();
  char        *area = NULL;
  if ( chkopt )
    ValidateNode(YES);
  
  if ( IsValid() )
    area = (char *)Tnodeptr->GetArea(prop_path);

  obh->StopReadTA(NO);
  return(area);
}

/******************************************************************************/
/**
\brief  GetAttribute - Get attribute according to position

        The  function returns the  name of the  attribute according to the given
        index.  The  attribute  index  corresponds  to  the  definition  of  the
        structure.  Attributes  returned  are  always  attributes  with  basic 
        (elementary) types. 
        Attributes  in  base  structures  or imbedded structures are returned as
        property  pathes  (e.g.  address.city  when  address  is  a  structured 
        attribute  in person). The leading part for base structures (usually the
        structure  name) is  displayed only  when passing  YES for the full_path
        option (default: NO). 
        Generic  attributes  can  be  considered as references or as attributes.
        The  generic option defines whether generic attributes are considered as
        attibutes (default: YES).
        If  there  are  no  attributes  defined  for  the structure the function
        returns  NULL. When an attribute with the given index has been found the
        function returns the property path in the fldpath.
        The  function  returns  the  path  in communication area of the property
        handle.  This  area  is  destroyed  when calling the next PropertyHandle
        function.

\return fldpath - Property path

\param  indx0 - Position in collection
\param  full_path - Full path
\param  generic - Generic attruibute option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttribute"

char *PropertyHandle :: GetAttribute (int32 indx0, logical full_path, logical generic )
{
  ACObject    *obh = StartRTA();
  char        *string = NULL;
BEGINSEQ
  if ( ValidateNode(NO) )                           ERROR
  string = Tnodeptr->GetAttribute(indx0,full_path,generic);

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(string);
}

/******************************************************************************/
/**
\brief  GetBaseProperty - Get collection handle for base collection

        The  function returns  the base  collection property  handle when a base
        collection  has  been  defined  for  the  collection  (relationship  or 
        extent). Otherwise the function returns NULL.
        The  returned property handle  is a sub-handle  for the current property
        handle,  i.e. the base collection will change automatically whenever the
        collection in the current property handle changes.

\return property_handle - Pointer to a property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseProperty"

PropertyHandle *PropertyHandle :: GetBaseProperty ( )
{
  ACObject    *obh = StartRTA();
  PropertyHandle *ph = NULL;
BEGINSEQ
  ValidateNode(NO);
  if ( !IsValid() )                                  ERROR
  
  ph = (PropertyHandle *)Tnodeptr->GetBaseNode();
  if ( !ph->IsValid() )                              ERROR
  

RECOVER
  ph = NULL;
ENDSEQ
  obh->StopReadTA(NO);
  return(ph);
}

/******************************************************************************/
/**
\brief  GetBufferInstance - Read instance from Buffer

        The  function  reads  an  instance  from the property handle buffer. The
        function  returns the  instance according  to the buffer position indx0.
        The  first instance in the buffer is  addressed by 0. Usually the buffer
        index is not identical with the position in the collection.

\return instance - Instance area

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBufferInstance"

Instance PropertyHandle :: GetBufferInstance (int32 indx0 )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->GetBufferInstance(indx0);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  GetCollectionID - Returns local collection identity

        Collections  in  ODABA  have  a  unique  identity  like instances, which
        allows identifying a collection within a database.

\return coll_id - Unique collection identifier

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollectionID"

int32 PropertyHandle :: GetCollectionID ( )
{
  ACObject    *obh = StartRTA();
  int32        id = UNDEF;
  if ( !ValidateNode(NO) )
    id = Tnodeptr->GetCollectionID();

  obh->StopReadTA(NO);
  return(id);
}

/******************************************************************************/
/**
\brief  GetCollectionProperty - Get parent collection property handle

        The  function searches  for the  next higher collection property handle.
        When  the property handle is a top handle or a transient property handle
        the function returns NULL.

\return property_handle - Pointer to a property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollectionProperty"

PropertyHandle *PropertyHandle :: GetCollectionProperty ( )
{
  ACObject       *obh = StartRTA();
  PropertyHandle *ph  = NULL;
BEGINSEQ
  ValidateNode(NO);
  if ( !IsValid() )                                 ERROR

  ph = (PropertyHandle *)Tnodeptr->GetHighPIPointer();


RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(ph);
}

/******************************************************************************/
/**
\brief  GetCount - Get number of instances stored for property

        The  functio returns the  number of instances  stored in the collection.
        Since  some indexes store multiple references to instances (array index)
        or  do not store all instances in the index, the function returns rather
        the  number of references  in the index  than the number of instances in
        the  collection.  Usually  these  numbers  are,  however,  identical. To
        ensure  that  you  get  the  collection  cout you may select the default
        order (SetOrder()).

\return count - Number of entries
/******************************************************************************/
/**
\brief  i - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 PropertyHandle :: GetCount ( )
{
  ACObject    *obh = StartRTA();
  int32        count = ERIC;
  if ( !ValidateNode(NO) )
    count = Tnodeptr->GetCount();



  obh->StopReadTA(NO);
  return(count);
}

/******************************************************************************/
/**
\brief  GetCurrentIndex - Get cursor position

        The  function returns the position of the currently selected instance in
        the  collection  according  to  the  selected  sort  order. The function
        returns  a  value  when  an  instance  has  been located in the property
        handle  (e.g. LocateKey())  regardles whether  the instance has been red
        or not.
        Since  the position might change when  instances are inserted or removed
        from  the  collection  the  current  index  can  be  used  for accessing
        instances (Get(indx0)) in a limited way (e.g. within a transaction).

\return index_pos - Position in the collection according to current sort order
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentIndex"

int32 PropertyHandle :: GetCurrentIndex ( )
{
  ACObject    *obh = StartRTA();
  int32        index = AUTO;
  if ( Exist() )
    index = Tnodeptr->GetCurrentIndex();

  obh->StopReadTA(NO);
  return(index);
}

/******************************************************************************/
/**
\brief  GetCurrentSize - Get size for selected instance

        The  function  usually  returns  the  same  as  GetSize.  For weak typed
        collections,  however,  the  function  returns  the size of the selected
        instance in staed of the defined type for the collection.

\return size - Size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentSize"

uint32 PropertyHandle :: GetCurrentSize ( )
{
  ACObject    *obh = StartRTA();
  int32        size = UNDEF;
  ValidateNode(NO);
  
  if ( IsValid() )
    size = IsCollection()  
           ? Tnodeptr->GetCurrentTypeDef()->GetInstLength(NO) 
           : Tnodeptr->GetSizeOf();
  obh->StopReadTA(NO);
  return(size);
}

/******************************************************************************/
/**
\brief  GetCurrentType - Get type for selected instance

        The  function  usually  returns  the  same  as  GetType.  For weak typed
        collections,  however,  the  function  returns  the type of the selected
        instance in staed of the defined type for the collection.

\return type_name - Type name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentType"

char *PropertyHandle :: GetCurrentType ( )
{
  ACObject    *obh = StartRTA();
  char        *types = NULL;
  if (! ValidateNode(NO) )
    types = Tnodeptr->GetCurrentType();
  else
    types = GetType();

  obh->StopReadTA(NO);
  return(types);
}

/******************************************************************************/
/**
\brief  GetCurrentTypeDef - Get current type definition

        The  function  usually  returns  the  same  as  GetType.  For weak typed
        collections,  however, the  function returns  the type definition of the
        selected instance in staed of the defined type for the collection.

\return strdef - Structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentTypeDef"

DBStructDef *PropertyHandle :: GetCurrentTypeDef ( )
{
  ACObject    *obh = StartRTA();
  DBStructDef *strdef = NULL;
  if ( !ValidateNode(NO) )
    strdef = Tnodeptr->GetCurrentTypeDef();
  else
    strdef = GetStructDef();

  obh->StopReadTA(NO);
  return(strdef);
}

/******************************************************************************/
/**
\brief  GetDBField - Provide property handle

        internal use

\return property_handle - Pointer to a property handle

\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBField"

PropertyHandle PropertyHandle :: GetDBField (char *prop_path )
{
  PropertyHandle    *property_handle = NULL;
  property_handle = GetPropertyHandle(prop_path);
  return(property_handle ? property_handle->get_nodeptr() 
                         : (node *)NULL);
}

/******************************************************************************/
/**
\brief  GetDBHandle - Get database handle

        The  function  returns  the  database  handle  for  the current property
        handle.

\return dbhandle - Pointer to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBHandle"

DatabaseHandle &PropertyHandle :: GetDBHandle ( )
{
static         DatabaseHandle   stat_dbhandle;
  ACObject    *obhandle = NULL;
  return ( IsValid() && (obhandle = Tnodeptr->GetObjectHandle())
           ? *obhandle->GetDBHandle()->GetDatabaseHandle() 
           : stat_dbhandle );

}

/******************************************************************************/
/**
\brief  GetDate - Get Date value for property handle

        The  function returns the date value  for the current property handle or
        for the attribute passed in prop_path.

\return date_val - Date value
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDate"

dbdt PropertyHandle :: GetDate ( )
{

  return( IsSelected() 
          ? Tnodeptr->dbf::GetDate() 
          : dbdt() );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDate"

dbdt PropertyHandle :: GetDate (char *prop_path )
{

//  return( GetPropertyHandle(prop_path)->GetDate());
  return( IsSelected() 
          ? Tnodeptr->GetDate(prop_path) 
          : dbdt() );

}

/******************************************************************************/
/**
\brief  GetDateTime - Get property instance as time stamp (date/time)

        The  function  returns  the  date/time  value  for  the current property
        handle or for the attribute passed in prop_path.

\return datetime_val - Date-Time value
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDateTime"

dttm PropertyHandle :: GetDateTime ( )
{

  return ( IsSelected() 
           ? Tnodeptr->dbf::GetDateTime() 
           : dttm() );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDateTime"

dttm PropertyHandle :: GetDateTime (char *prop_path )
{

  return ( IsSelected() 
           ? Tnodeptr->GetDateTime(prop_path) 
           : dttm() );

}

/******************************************************************************/
/**
\brief  GetDay - 



\return int_val - Integer value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDay"

int32 PropertyHandle :: GetDay ( )
{

  return( IsSelected() 
          ? Tnodeptr->dbf::GetDate().GetDay() 
          : 0 );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDay"

int32 PropertyHandle :: GetDay (char *prop_path )
{

//  return( GetPropertyHandle(prop_path)->GetDate());
  return( IsSelected() 
          ? Tnodeptr->GetDate(prop_path).GetDay()
          : 0 );

}

/******************************************************************************/
/**
\brief  GetDescription - Get property definition

        The  function returns the field definition  for the forperty handle. The
        field  definition described the  structure of the  instance area for the
        property handle.
        If  the property handle  is a collection  the field definition describes
        one  instance of the collection according to the defined structure. This
        is different from the field definition of the property handle itself.

\return prop_def - Property definition

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDescription"

DBFieldDef *PropertyHandle :: GetDescription (char chkopt ) const
{
  ACObject    *obh = StartRTA();
  DBFieldDef  *flddef = NULL;
  if ( chkopt )
    ValidateNode(NO);
  
  if ( IsValid() )
    flddef = Tnodeptr->GetInstFieldDef();

  obh->StopReadTA(NO);
  return(flddef);
}

/******************************************************************************/
/**
\brief  GetDictionary - Get dictionary handle

        The  function  returns  the  dictionary  handle for the current property
        handle.

\return dictptr - Dictionary handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDictionary"

DictionaryHandle &PropertyHandle :: GetDictionary ( )
{
static         DictionaryHandle   stat_dicthdl;
  Dictionary  *dictptr;
  return ( IsValid() && (dictptr = Tnodeptr->GetDictionary())
           ? *dictptr->GetDictionaryHandle() 
           : stat_dicthdl );


}

/******************************************************************************/
/**
\brief  GetDimension - Provide field dimension

        The function returns the property dimension.
        In case of an error the function returns -1 (AUTO).

\return dimension - Dimension

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDimension"

int32 PropertyHandle :: GetDimension ( ) const
{
  ACObject    *obh = StartRTA();
  int32        dim = AUTO;
BEGINSEQ
  ValidateNode(NO);
  if ( !IsValid() )                                 ERROR
  
  dim = Tnodeptr->GetDimension();

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(dim);
}

/******************************************************************************/
/**
\brief  GetDouble - Get property instance as double value

        The  function returns the  value for the  current property handle or for
        the attribute passed in prop_path as double value .

\return dbl_value - Double value
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDouble"

double PropertyHandle :: GetDouble ( )
{

  return ( IsSelected() 
           ? Tnodeptr->dbf::GetDouble()
           : 0  );


}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDouble"

double PropertyHandle :: GetDouble (char *prop_path )
{

//  return( GetPropertyHandle(prop_path)->GetDouble());
  return ( IsSelected() 
           ? Tnodeptr->GetDouble(prop_path)
           : 0  );


}

/******************************************************************************/
/**
\brief  GetExtInstModCount - 



\return modcount - Modification count
-------------------------------------------------------------------------------
\brief  i - 



\param  objid - Local object identity (LOID)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInstModCount"

int16 PropertyHandle :: GetExtInstModCount (int32 objid )
{

  return ( GetObjectHandle().GetExtInstModCount(objid) );


}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInstModCount"

int16 PropertyHandle :: GetExtInstModCount ( )
{
  int32           objid = UNDEF;
  return ( (objid = GetID(AUTO)) ? GetExtInstModCount(objid)
                                 : UNDEF );  



}

/******************************************************************************/
/**
\brief  GetExtentName - Get extent name for collection

        The  function returns the  name or path  for the base collection (extent
        name  or  property  path).  When  no  ase collectin has been defined the
        function returns NULL.

\return extname - Extent name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentName"

char *PropertyHandle :: GetExtentName ( )
{
  ACObject    *obh = StartRTA();
  char        *names = NULL;
  ValidateNode(NO);
  
  if ( IsValid() )
    names = Tnodeptr->GetExtentName();

  obh->StopReadTA(NO);
  return(names);
}

/******************************************************************************/
/**
\brief  GetField - Get Field definition

        The  function returns the field definition for the property. In contrast
        to  GetFieldDef() for transient fields the function returns the original
        definition of the transient reference or property.

\return field - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetField"

fld *PropertyHandle :: GetField ( )
{

  return ( IsValid()
           ? nodeptr
           : NULL   );

}

/******************************************************************************/
/**
\brief  GetFieldDef - Get field definition for the property

        The  function  returns  the  field  definition  for  the property handle
        (which  differs  in  case  of  collection  properties  from the instance
        definition, which is returned by GetDescription()).

\return prop_def - Property definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldDef"

DBFieldDef *PropertyHandle :: GetFieldDef ( )
{
  ACObject    *obh = StartRTA();
  DBFieldDef  *flddef = NULL;
  ValidateNode(NO);
  
  if ( IsValid() )
    flddef = Tnodeptr->GetFieldDef();

  obh->StopReadTA(NO);
  return(flddef);
}

/******************************************************************************/
/**
\brief  GetGUID - Get global identity string for the current instance

        The  function  returns  the  global  instance  identity  (GUID)  for the
        current  instance. This identity is  unique within all ODABA2 databases.
        GUIDs  are  available  for  instances  that  are  derived  directly  or 
        indirectly  from  __OBJECT.  When  auto-build  (GUID)  is  set  for  the
        structure  the GUID is generated  when creating the instance. Otherwhise
        it  has  to  be  provided  using  ProvideGUID().  When  no GUID has been
        defined  for  the  structure  (not  derived  from __OBJECT) the function
        returns  the local object identity (LOID),  which is a unique identifier
        within the database. 
        If  no instance  is available  or no  global identity has been generated
        for the current instance the function returns NULL. 
        The  function returns a global instance  identity also when the property
        handle  refers to a new instance where  the global identity has been set
        explicitely.  Thus, e.g.  when copying  instances you  might ask for the
        global identity that has been shipped with the source instance.
        The  GUID is passed in the internal result area and valid until the next
        property handle function call.

\return guid_string - 
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGUID"

char *PropertyHandle :: GetGUID ( )
{
  ACObject    *obh = StartRTA();
  char        *guid = NULL;
  if ( IsPositioned() )
    guid = Tnodeptr->GetGUID();

  obh->StopReadTA(NO);
  if (guid) return guid;
  else return "";
  
}

/******************************************************************************/
/**
\brief  GetGenAttrType - Get generic attribute type

        The  functio returns the  internal type value  of the generic attribute,
        that has been selected as current attribute type (SetGenAttribute()).

\return attrtype - Type of generic attribute

\param  w_propnames - Property path or name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttrType"

int32 PropertyHandle :: GetGenAttrType (char *w_propnames )
{
  ACObject    *obh = StartRTA();
  int32        attr_type = UNDEF;
  ValidateNode(NO);
  
  if ( IsValid() )
    attr_type = Tnodeptr->GetGenAttrType(w_propnames);

  obh->StopReadTA(NO);
  return(attr_type);
}

/******************************************************************************/
/**
\brief  GetGenOrderType - Get current type for generic sort order of collection handle

        When  the key  of the  currently selected  sort order contains a generic
        attribute  the index is  generic as well.  In this case setting the sort
        order  implies setting it  to a specific  type of the generic attribute.
        This  function  returns  the  internal  type  number  for  the  generic 
        attribute type selected for the given sort order (SetOrder()).

\return attrtype - Type of generic attribute

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenOrderType"

int32 PropertyHandle :: GetGenOrderType ( )
{
  ACObject    *obh = StartRTA();
  int32        order_type = UNDEF;
  ValidateNode(NO);
  
  if ( IsValid() )
    order_type = Tnodeptr->GetGenOrderType();

  obh->StopReadTA(NO);
  return(order_type);
}

/******************************************************************************/
/**
\brief  GetGlobalID - Get global ID

        The  function returns the local object ID (LOID) when the instance could
        be  found in the base collection (global  extent). When no key is passed
        the  instance is searched with the  key from the internal instance. When
        passing  a key  and an  instance is  selected in the property handle the
        instance wil be unselected.

\return objid - Local object identity (LOID)
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalID"

int64 PropertyHandle :: GetGlobalID ( )
{
  ACObject    *obh = StartRTA();
  int32        objid = UNDEF;
  objid = ( IsValid() 
            ? Tnodeptr->GetGlobalID().get_ebsnum()
            : UNDEF );

  obh->StopReadTA(NO);
  return(objid);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  skey - Sort key
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalID"

int64 PropertyHandle :: GetGlobalID (Key skey )
{
  ACObject    *obh = StartRTA();
  node        *nodptr;
  int32        objid = UNDEF;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
           
  PropertyHandle  ph(*this);
  nodptr = ph.GetNode();
  
  nodptr->ToTop();
  if ( nodptr->InitInstance(NULL) )                  ERROR
    
  if ( nodptr->GetSortKeyLength() )
    SetSortKey(skey,Instance(nodptr->get_nodeinst()->get_iselarea()));
  else
    SetKey(skey,Instance(nodptr->get_nodeinst()->get_iselarea()));

  objid = ph.GetGlobalID();
RECOVER
  objid = UNDEF;
ENDSEQ
  obh->StopReadTA(NO);
  return(objid);
}

/******************************************************************************/
/**
\brief  GetHierarchyPath - Get Accesspath for property handle hierarchy

        The  function returns an access path for the ptoperty hierachy according
        to  the current selection. The path  starts with the top property handle
        and  ends  with  the  current  property handle. The path returned can be
        used  with PropertyHandle::Open() to re-locate an instance selected in a
        property handle hierarchy.

\return string - String area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHierarchyPath"

char *PropertyHandle :: GetHierarchyPath ( )
{

  return ( IsValid() 
           ? Tnodeptr-> GetPathString() 
           : NULL                       );

}

/******************************************************************************/
/**
\brief  GetHours - 



\return int_val - Integer value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHours"

int32 PropertyHandle :: GetHours ( )
{

  return ( IsSelected() 
           ? Tnodeptr->dbf::GetTime().GetHour() 
           : 0 );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHours"

int32 PropertyHandle :: GetHours (char *prop_path )
{

  return ( IsSelected() 
           ? Tnodeptr->GetTime(prop_path).GetHour()
           : 0 );
//  return( GetPropertyHandle(prop_path)->GetTime());

}

/******************************************************************************/
/**
\brief  GetID - Get local object identity

        Old version (see GetLOID)

\return objid - Local object identity (LOID)
-------------------------------------------------------------------------------
\brief  AtPosition - 



\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

uint64 PropertyHandle :: GetID (int32 set_pos0_w )
{

  return ( GetLOID(set_pos0_w) );


}

/******************************************************************************/
/**
\brief  ByKey - 



\param  sort_key - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

uint64 PropertyHandle :: GetID (Key sort_key )
{

  return ( GetLOID(sort_key) );


}

/******************************************************************************/
/**
\brief  GetIdentity - Get property identity string

        The  function builds  an identity  string for  a property in a structure
        instance: 
        loid|property_path[index] 
        The   id-string   is   a   local   database   identity for the instance.
        'property_path'  is  the  path  that  identifies  a  property within the
        instance.  When  the  property  is  an  array  the  element  position is
        indicated  by the index.  Index numbers may  also appear within the path
        (e.g.  when supporting upto three addresses for a person a property path
        for 'place" could look like:
        199879899|address[2].place
        The  identity  string  is  returned  in an internal area when no area is
        passed  (id_string). Otherwise the area passed in string should have 513
        bytes, but at least the maximum expected string size +1.
        If  there  is  no  instance  selected in the (upper) collection property
        handle  the  function  returns  NULL.  If  no  id_string  is  passed the
        function  returns the path in communication area of the property handle.
        This area is destroyed when calling the next PropertyHandle function.

\return id_string - Identity string

\param  id_string - Identity string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentity"

char *PropertyHandle :: GetIdentity (char *id_string )
{
  ACObject    *obh = StartRTA();
  char        *id = NULL;
  if ( !ValidateNode(NO) )
    id = Tnodeptr->GetIdentity(id_string,YES);

  obh->StopReadTA(NO);
  return(id);
}

/******************************************************************************/
/**
\brief  GetIndexName - Name of the current index

        The  function returns the  index name of  the index for the n-th (indx0)
        index  (sort order for collection). The  function returns NULL, if indx0
        is  equal  or  larger  than  the  number  of  indexes  defined  for  the
        collection.

\return index_name - Index name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndexName"

char *PropertyHandle :: GetIndexName (int32 indx0 )
{

  return( GetFieldDef()->GetIndexName(indx0) );

}

/******************************************************************************/
/**
\brief  GetInitArea - Provide initialized instance area

        The  function provides an  initialised instance of  the type defined for
        the  property handle. For weak typed  collection the type depends on the
        last  type  accessed  by  the  property  handle or the type set with the
        SetType()  function. Calling  the function  for an attribute will return
        an initialized attribute instance.
        When  the property handle has selected an instance the current selection
        is  cancelled (after saving changes made  to the selected instance). You
        may  fill attributes and initialise single references but you cannot add
        instances to collections in an initialised instance. 
        For  storing  the  instance  to  the  database  you  must call the Add()
        function  for the property handle. Changes  made to the instance are not
        saved  automatically  when  changing  the  selection  for  the  property
        handle.  Since  no  instance  is  selected  in the property handle after
        GetInitArea()  you  cannot  assign  values  to  subordinated  property 
        handles.

\return instance - Instance area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInitArea"

Instance PropertyHandle :: GetInitArea ( )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->GetInitInstance(NO);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  GetInitInstance - Provide initialised instance

        The  function provides an  initialised instance of  the type defined for
        the  property handle. For weak typed  collection the type depends on the
        last  type  accessed  by  the  property  handle or the type set with the
        SetType()  function. Calling  the function  for an attribute will return
        an initialized attribute instance.
        When  the property handle has selected an instance the current selection
        is  cancelled ( after saving changes made to the selected instance). You
        may  fill attributes and initialise single references but you cannot add
        instances to collections in an initialised instance. 
        The  instance  can  be  stored  to  the  database  by calling the Save()
        function  for  the  property  handle.  Changes  made to the instance are
        saved  automatically  when  changing  the  selection  for  the  property
        handle.  To  avoid  storing  the  instance  to  the  database it must be
        explicitly cancelled.

\return instance - Instance area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInitInstance"

Instance PropertyHandle :: GetInitInstance ( )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->GetInitInstance(YES);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  GetInst - Create database instance from external instance

        Used internally, only.

\return instance - Instance area

\param  extinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInst"

Instance PropertyHandle :: GetInst (char *extinst )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->GetExtInst(extinst);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  GetInstModCount - 



\return modcount - Modification count

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 PropertyHandle :: GetInstModCount ( )
{
  ACObject    *obh = StartRTA();
  int32        mcount = UNDEF;
  if ( IsPositioned() )
    mcount = Tnodeptr->GetInstModCount();

  obh->StopReadTA(NO);
  return(mcount);
}

/******************************************************************************/
/**
\brief  GetInstance - Get current instance

        The  function returns the  current instance. If  no instance is selected
        the  function returns an empty instance area (instance.GetData() returns
        NULL).

\return instance - Instance area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

Instance PropertyHandle :: GetInstance ( ) const
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( IsPositioned() )
    instance = ProvideArea();

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  GetInstanceContext - Get Instance Context

        The  function  returns  the  Instance  context  for the client or server
        depending on where the property handle is being created.

\return structctx - Structure context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstanceContext"

CTX_Structure *PropertyHandle :: GetInstanceContext ( )
{
  ACObject    *obh = StartRTA();
  CTX_Structure *context = NULL;
  ValidateNode(YES);
  
  if ( IsValid() )
    context = Tnodeptr->GetInstContext();


  obh->StopReadTA(NO);
  return(context);
}

/******************************************************************************/
/**
\brief  GetInt - Get property instance as integer value

        The  function returns the integer value  for the current property handle
        or  for  the  attribute  passed  in prop_path. When the field definition
        refers  to the value with decimal precisions the value returned contains
        only  the  part  before  the  decimal  point. To get the exact value use
        GetNormalized().

\return int_val - Integer value
-------------------------------------------------------------------------------
\brief  i0 - Get ineger value for current property

        This  implementation provides an integer value for the selected property
        handle.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInt"

int32 PropertyHandle :: GetInt ( )
{

  return ( IsSelected() 
           ? Tnodeptr->dbf::GetInt() 
           : 0 );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInt"

int32 PropertyHandle :: GetInt (char *prop_path )
{
  int32          result = 0;
  if ( IsSelected() )
  {
    if ( !memcmp(prop_path,"__IDENTITY",10) || 
         !memcmp(prop_path,"__LOID",6)         )
      result = GetID();
    else
      result = Tnodeptr->GetInt(prop_path);
  }

  return(result);
}

/******************************************************************************/
/**
\brief  GetIntValue - Get property instance as integer value

        The  function returns the integer value  for the current property handle
        or  for  the  attribute  passed  in prop_path. When the field definition
        refers  to the value with decimal precisions the value returned contains
        only  the  part  before  the  decimal  point. To get the exact value use
        GetNormalized().
        In  contrast to GetInt(),  no instance must  be selected in the property
        handle.

\return int_val - Integer value
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIntValue"

int32 PropertyHandle :: GetIntValue ( )
{
  ACObject    *obh = StartRTA();
  int32        intval = 0;
  ValidateNode(YES);
  
  if ( IsValid() )
    intval = Tnodeptr->dbf::GetInt();

  obh->StopReadTA(NO);
  return(intval);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIntValue"

int32 PropertyHandle :: GetIntValue (char *prop_path )
{
  ACObject    *obh = StartRTA();
  int32        intval = 0;
  ValidateNode(YES);
  
  if ( IsValid() )
  {
    if ( !memcmp(prop_path,"__IDENTITY",10) || 
         !memcmp(prop_path,"__LOID",6)         )
      intval = GetID();
    else
      intval = Tnodeptr->GetInt(prop_path);
  }
  obh->StopReadTA(NO);
  return(intval);
}

/******************************************************************************/
/**
\brief  GetKey - 



\return key - Key value
/******************************************************************************/
/**
\brief  i0 - 



\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

Key PropertyHandle :: GetKey (int32 set_pos0_w )
{
  ACObject    *obh = StartRTA();
  Key          key;
  if ( !ValidateNode(YES) )
    key = Tnodeptr->GetKey(set_pos0_w);

  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  GetKeyFromParm - Get String key from parameter



\return key - Key value

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyFromParm"

Key PropertyHandle :: GetKeyFromParm (PropertyHandle &prop_hdl )
{
  ACObject    *obh = StartRTA();
  Key          key;
  char        *targ_str;
  char        *srce_str;
  if ( prop_hdl.IsText() || prop_hdl.IsEnumeration() )
    key = StringToKey(prop_hdl.GetString());
  else if ( (targ_str = GetCurrentType())  && (srce_str = prop_hdl.GetCurrentType()) &&
            (!strcmp(targ_str,srce_str)    || prop_hdl.IsBasedOn(targ_str) )         &&
            prop_hdl.IsPositioned()                  )
    key = ExtractSortKey(NULL,prop_hdl.Get());
  

  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  GetKeyLength - Get ident key length

        The function returns the identifying key length.

\return key_len - Size for internal key

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 PropertyHandle :: GetKeyLength ( )
{
  ACObject    *obh = StartRTA();
  int16        klen = UNDEF;
  ValidateNode(NO);
  
  if ( IsValid() )
    klen = Tnodeptr->GetKeyLength();

  obh->StopReadTA(NO);
  return(klen);
}

/******************************************************************************/
/**
\brief  GetKeySMCB - Get ident key definition

        The  function returns the structure defintion for a key defintion of the
        structure  defined for the  property handle. This  is not necessaryly an
        index  or sort key of the  collection referenced by the property handle.
        When  no key  is passed  the function  returns the key definition of the
        identifying key.

\return smcbptr - 

\param  key_name_w - Key name for conversion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeySMCB"

smcb *PropertyHandle :: GetKeySMCB (char *key_name_w )
{
  ACObject    *obh = StartRTA();
  smcb        *smcbptr = NULL;
  ValidateNode(NO);
  
  if ( IsValid() )
    smcbptr = Tnodeptr->GetKeySMCB(key_name_w);

  obh->StopReadTA(NO);
  return(smcbptr);
}

/******************************************************************************/
/**
\brief  GetLOID - Get instance identity (LOID)

        The  function  returns  the  local  object  identity  for  the  instance
        selected  in  the  property  handle.  When  no  instance is selected the
        function returns 0. 
        When  passing a  key or  a position  the instance acording to the passed
        key or position is selected before retrieving the LOID.

\return objid - Local object identity (LOID)
-------------------------------------------------------------------------------
\brief  A00 - 



\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLOID"

int64 PropertyHandle :: GetLOID (int32 set_pos0_w )
{
  ACObject    *obh = StartRTA();
  int64        id = UNDEF;
  if ( !ValidateNode(NO) )
    id = Tnodeptr->GetID(set_pos0_w,YES,YES).get_ebsnum();

  obh->StopReadTA(NO);
  return(id);
}

/******************************************************************************/
/**
\brief  ByKey - 



\param  sort_key - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLOID"

int64 PropertyHandle :: GetLOID (Key sort_key )
{
  ACObject    *obh = StartRTA();
  int32        id = UNDEF;
  if ( !ValidateNode(YES) )
    id = Tnodeptr->GetID(sort_key.GetData(),YES,YES).get_ebsnum();

  obh->StopReadTA(NO);
  return(id);
}

/******************************************************************************/
/**
\brief  GetMinutes - 



\return int_val - Integer value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMinutes"

int32 PropertyHandle :: GetMinutes ( )
{

  return ( IsSelected() 
           ? Tnodeptr->dbf::GetTime().GetMinute() 
           : 0 );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMinutes"

int32 PropertyHandle :: GetMinutes (char *prop_path )
{

  return ( IsSelected() 
           ? Tnodeptr->GetTime(prop_path).GetMinute()
           : 0 );
//  return( GetPropertyHandle(prop_path)->GetTime());

}

/******************************************************************************/
/**
\brief  GetMode - 



\return mode - Access mode

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMode"

PIACC PropertyHandle :: GetMode ( )
{
  ACObject    *obh = StartRTA();
  PIACC        accmode = PI_undefined;
  ValidateNode(NO);
  
  if ( IsValid() )
    accmode = Tnodeptr->GetMode();

  obh->StopReadTA(NO);
  return(accmode);
}

/******************************************************************************/
/**
\brief  GetMonth - 



\return int_val - Integer value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMonth"

int32 PropertyHandle :: GetMonth ( )
{

  return( IsSelected() 
          ? Tnodeptr->dbf::GetDate().GetMonth() 
          : 0 );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMonth"

int32 PropertyHandle :: GetMonth (char *prop_path )
{

//  return( GetPropertyHandle(prop_path)->GetDate());
  return( IsSelected() 
          ? Tnodeptr->GetDate(prop_path).GetMonth()
          : 0 );

}

/******************************************************************************/
/**
\brief  GetNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNode"

node *PropertyHandle :: GetNode ( )
{

  return ( IsValid() ? Tnodeptr : NULL );

}

/******************************************************************************/
/**
\brief  GetNormalized - Get normalized integer value

        The  function  can  be  used  for  getting  integer  values with decimal
        precisions  from  INT  or  unsigned  INT attributes.  When defining a an
        attribute  with two decimals, referring to  the value 1, which is stored
        inernally  as  100  (1.00),  will  result in 1. Using GetNormalized will
        result in 100 instead.

\return long_val - Integer value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNormalized"

int32 PropertyHandle :: GetNormalized ( )
{
  DBFieldDef  *fmcbptr = GetDescription();

 return( !fmcbptr || (fmcbptr->fmcbityp != T_INT && fmcbptr->fmcbityp != T_UINT) 
          ? ULONGMAX
          : Tnodeptr->GetNormalized() );


}

/******************************************************************************/
/**
\brief  GetOPNode - 



\return op_node - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOPNode"

OPBase *PropertyHandle :: GetOPNode ( )
{

  return ( this && nodeptr && nodeptr->IsValid() 
           ? nodeptr->GetOPNode() : NULL );

}

/******************************************************************************/
/**
\brief  GetObjectHandle - Get Database Object handle

        The  function  returns  the  Database  Object  Handle  for  the property
        handle.  When  referring  to  transient fields, which are not associated
        with a database object, the function returns NULL.
        For  transient  fields  the  function returns the database object handle
        that  is associated with the parent instance and not the database object
        handle  of the associated  collection, which might  in some cases belong
        to another database object.

\return obj_handle - Database Object Handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectHandle"

DBObjectHandle &PropertyHandle :: GetObjectHandle ( )
{
static         DBObjectHandle   stat_obhandle;

  return ( IsValid(NO) 
           ? *(DBObjectHandle *)nodeptr->GetObjectHandlePtr() 
           : stat_obhandle );

}

/******************************************************************************/
/**
\brief  GetOrigin - Get associated property handle

        The  function  returns  an  ID  that identifies the origin of a property
        handle.  For  transient  property  handles  thie  is  the origin for the
        associated  property handle.  For copy  handles it  is the origin of the
        copy.
        The  function returns UNDEF (0) when the handle is not opened or when no
        property handle is associated with a transient property handle.

\return prophdl_id - Handle identifier

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOrigin"

int64 PropertyHandle :: GetOrigin ( )
{

  return ( IsValid() 
           ? (int64)Tnodeptr->GetOrigin()
           : UNDEF  );

}

/******************************************************************************/
/**
\brief  GetParentProperty - Get high property

        The  function  returns  the  next  higher  property  handle.  The handle
        returnd  might share its cursor other  handles in the application, which
        asked  for  the  parent  property  handle.  To get a private copy of the
        parent property handle you can use the copy constructor:
        ph(*GetParentProperty());
        GetParentProperty()  returns a  so-called static  property handle, which
        is  not  able  to  react  on  type  changes in upper weak-typed property
        handles.  To  avoid  problems  with  static property handles (error 348)
        create a dynamic property handle as described above or by with
        ph(GetParentProperty());
        The  parent property handle is the next higher handle in the application
        hierarchy,  which  mught  differ  from  the  structural  hierarchy, i.e.
        usually  you will get the property handle as parent, which has been used
        for  opening  or  cintructing  the current property handle. An exception
        are static property handles, which always return its structural parent.

\return property_handle - Pointer to a property handle
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParentProperty"

PropertyHandle *PropertyHandle :: GetParentProperty ( )
{
  ACObject    *obh = StartRTA();
  PropertyHandle *ph = NULL;
  ValidateNode(NO);
  
  if ( IsValid() && Tnodeptr->get_nodenode() )
    ph = (PropertyHandle *)Tnodeptr->get_nodenode_ptr();

  obh->StopReadTA(NO);
  return(ph);
}

/******************************************************************************/
/**
\brief  GetPathElement - 



\return property_handle - Pointer to a property handle

\param  path_element - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathElement"

PropertyHandle *PropertyHandle :: GetPathElement (char *path_element )
{

  return( IsValid() 
          ? Tnodeptr->GetPathElement(path_element)
          : NULL );  




}

/******************************************************************************/
/**
\brief  GetPrivilege - Get access privilege for reference

        The function returns the access privilege for the property.

\return prvmode - Access privilege for property

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrivilege"

PIADEF PropertyHandle :: GetPrivilege ( )
{
  DBFieldDef *field_def;
  return ( (field_def = GetDescription()) 
           ? field_def->get_privilege() 
           : PI_unknown );

}

/******************************************************************************/
/**
\brief  GetPropertyContext - Get property context

        The  function  returns  the  property  context  for the client or server
        depending on where the property handle is being created.

\return propctx - Property context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyContext"

CTX_Property *PropertyHandle :: GetPropertyContext ( )
{
  ACObject    *obh = StartRTA();
  CTX_Property *prop_ctx = NULL;
  ValidateNode(NO);
  
  if ( IsValid() )
    prop_ctx = Tnodeptr->GetContext();


  obh->StopReadTA(NO);
  return(prop_ctx);
}

/******************************************************************************/
/**
\brief  GetPropertyHandle - Get property handle

        The  function  returns  the  property  handle for the selected path. The
        function  handles  property  pathes  within  a  structure instance (e.g.
        'direction.city',  where  city  is  a  member  of the imbedded 'Address'
        structure  of  direction)  as  well  as  pathes  that include references
        ('mother.name',  where mother is a reference  to a persons mother). When
        defining  pathes  that  include  references  thous  references  shout be
        single  referenced (dimension = 1) since  the path will locate the first
        instance for the parent(s), only. 
        When  referring to transient  references you must  take into accont thet
        the  data source referenced by the transient reference may change during
        processing.  This includes the  type of referenced  instances as well as
        the referenced collection or instance.
        When  using the  GetPropertyHandle function  instead of using a property
        handle  constructor you will  share the cursor  and the data source with
        other property handles provided with this function.
        For  creating  a  shared  subordinated  property  handle you can use the
        constructor in combination with the GetPropertyHandle() function:
        PropertyHandle    ph(parent.GetPropertyHandle(prop_path));
        or the corresponding Open() function.
        GetPropertyHandle  returns a so-called static  property handle, which is
        not  able to react on type changes in upper weak-typed property handles.
        To  avoid  problems  with  static  property handles (error 348) create a
        shared property handle as described above.

\return property_handle - Pointer to a property handle
/******************************************************************************/
/**
\brief  i00 - 



\param  prop_path - Property path
\param  is_transient - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *PropertyHandle :: GetPropertyHandle (char *prop_path, logical *is_transient )
{
  ACObject       *obh = StartRTA();
  node          **pnodeptr;
  PropertyHandle *ph  = NULL;
  node           *npt;
BEGINSEQ
  ValidateNode(YES);
  
  if ( !IsValid() )                                 ERROR
           
  if ( !prop_path )
  {
    if ( nodeptr->get_nodetype() == NT_ACTransientReference )
    {
      if ( !(pnodeptr = ((ACTransientReference *)nodeptr)->GetNodePtr()) )     
                                                     ERROR
      ph = (PropertyHandle *)pnodeptr;
      if ( is_transient )
        *is_transient = YES;
    }
    else
      ph = this;
    LEAVESEQ
  }

  npt = Tnodeptr;
  if ( *prop_path == '.' )
  {
    while ( *(++prop_path) == '.' )
    {
      npt = *npt->GetHighPIPointer();
      if ( !npt || !npt->IsValid() )                ERROR
    }
  }
           
  ph = (PropertyHandle *)npt->GetNodePtr(prop_path,is_transient); 
    

RECOVER
  ph = NULL;
ENDSEQ
  obh->StopReadTA(NO);
  return(ph);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *PropertyHandle :: GetPropertyHandle (char *prop_path )
{
  logical       transient = NO;
  return( GetPropertyHandle(prop_path,&transient) );

}

/******************************************************************************/
/**
\brief  GetPropertyPath - Get property path for property handle

        The  property path defines  the path from  the parent property handle to
        the current one.

\return peoperty_path - Property path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyPath"

char *PropertyHandle :: GetPropertyPath ( )
{

  return ( IsValid() 
           ? Tnodeptr->get_prop_path()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetRefModCount - Get collection update count

        The  function returns  an internal  modification count for a collection.
        This  allows checking whether the collection has been updated by another
        user   or   application   by   adding   or   deleting instances from teh
        collection,  since  each  update  will  increase  the modification count
        stored in the database. 
        Since  the modification count  is rotating (starting  again with 1 after
        reaching  255) this is  not a save  indication. Thus, it is suggested to
        use server event handler for reacting on changes.

\return modcount - Modification count

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefModCount"

int16 PropertyHandle :: GetRefModCount ( )
{
  ACObject    *obh = StartRTA();
  int32        mcount = UNDEF;
  if ( !ValidateNode(NO) )
    mcount = Tnodeptr->GetRefModCount();

  obh->StopReadTA(NO);
  return(mcount);
}

/******************************************************************************/
/**
\brief  GetReference - Get reference from structure definition

        The  function returns the name of  the reference or relationship (except
        MEMO  fields that are  considered as attributes)  according to the given
        index.  The  reference  index  corresponds  to  the  definition  of  the
        structure. 
        References  in  base  structures  or imbedded structures are returned as
        property  pathes  (e.g.  address.city  when  address  is  a  structured 
        attribute  in person  and city  is a  reference in address). The leading
        part  for base structures (usually the structure name) is displayed only
        when passing YES for the full_path option. 
        Generic  attributes  can  be  considered as references or as attributes.
        The  generic option defines whether generic attributes are considered as
        references.
        If  there  are  noreferences  defined  for  the  structure  the function
        returns  NULL. When an reference with the given index has been found the
        function returns the property path in the fldpath.
        The  function  returns  the  path  in communication area of the property
        handle.  This  area  is  destroyed  when calling the next PropertyHandle
        function.

\return prop_path - Property path

\param  indx0 - Position in collection
\param  full_path - Full path
\param  generic - Generic attruibute option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReference"

char *PropertyHandle :: GetReference (int32 indx0, logical full_path, logical generic )
{
  ACObject    *obh = StartRTA();
  char        *prop_path = NULL;
  ValidateNode(NO);
  
  if ( IsValid() )
    prop_path = Tnodeptr->GetReference(indx0,full_path,generic);

  obh->StopReadTA(NO);
  return(prop_path);
}

/******************************************************************************/
/**
\brief  GetRelative - Get relative instance

        The  function returns an instance according  to the relative position in
        a  collection, which  is restricted  by a  filter condition or a context
        selection  handler. The position passed to  the collection refers to the
        n.th  available  instance.  Instances  skipped  because  of  the  filter
        condition are not counted.

\return instance - Instance area
/******************************************************************************/
/**
\brief  i01 - 



\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelative"

Instance PropertyHandle :: GetRelative (int32 set_pos0_w )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->GetRelative(set_pos0_w);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  GetRelativeCount - Get relative count

        The  function returns the  relative number of  instances in a collection
        with  a filter condition or context  based filters. The function returns
        the  number  of  instances,  that  are  available  in  the  restricted 
        collection.

\return count - Number of entries
/******************************************************************************/
/**
\brief  i - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelativeCount"

int32 PropertyHandle :: GetRelativeCount ( )
{
  ACObject    *obh = StartRTA();
  int32        count = ERIC;
  if ( !ValidateNode(YES) )
    count = Tnodeptr->GetRelativeCount();



  obh->StopReadTA(NO);
  return(count);
}

/******************************************************************************/
/**
\brief  GetRelativeIndex - Get relativ position of current or last instance

        The  function  returns  the  relative  position  of  the current or last
        instance.  This may differ from the  absolute (current) position in case
        of filter conditions or selection by context handlers. 
        When  no instance is selected or when  no relative position is known for
        the  instance  currently  selected  (e.g.  when  selected  by  key), the
        function  returna AUTO. When passing  last_opt YES, the function returns
        the last relative index found for the property handle.
        The  relative  index  is  updated  only,  when  using  the GetRelative()
        function for accessing the collection.

\return lindx0 - Position in collection
/******************************************************************************/
/**
\brief  i - 



\param  last_opt - Retuns last relative index
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelativeIndex"

int32 PropertyHandle :: GetRelativeIndex (logical last_opt )
{
  ACObject    *obh = StartRTA();
  int32        index = AUTO;
  if ( !ValidateNode(YES) )
    index = Tnodeptr->GetRelativeIndex(last_opt,YES);



  obh->StopReadTA(NO);
  return(index);
}

/******************************************************************************/
/**
\brief  GetSeconds - 



\return int_val - Integer value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSeconds"

int32 PropertyHandle :: GetSeconds ( )
{

  return ( IsSelected() 
           ? Tnodeptr->dbf::GetTime().GetSecond() 
           : 0 );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSeconds"

int32 PropertyHandle :: GetSeconds (char *prop_path )
{

  return ( IsSelected() 
           ? Tnodeptr->GetTime(prop_path).GetSecond()
           : 0 );
//  return( GetPropertyHandle(prop_path)->GetTime());

}

/******************************************************************************/
/**
\brief  GetSelectedKey - Get selected key value

        The  function returns the  key value for  the selected instance. When no
        instance  is selected  the function  returns the  value for the selected
        key,  which  might  have  been  located wit the LocateKey() or NextKey()
        function. 
        When  neither a key nor an instance is selected, the function returns an
        empty key instance.

\return sort_key - Sort key value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSelectedKey"

Key PropertyHandle :: GetSelectedKey ( )
{
  ACObject    *obh = StartRTA();
  Key          key;
  if ( !ValidateNode(YES) )
    key = Tnodeptr->GetSelectedKey();

  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  GetSize - Get instance size

        The function returns the size allocated for the instance.

\return inst_len - Size of returned instance

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

int32 PropertyHandle :: GetSize ( )
{
  DBFieldDef *field_def;
  return ( (field_def = GetDescription()) 
           ?  field_def->fmcbbyte 
           :  UNDEF );

}

/******************************************************************************/
/**
\brief  GetSizeOf - Get size of instance in collection handle

        The  function  returns  the  size  allocated  for  the  instances of the
        property  handle (for  weak typed  the size  for the selected type). For
        MEMO fields the function returns the maximum size of the MEMO field.

\return inst_len - Size of returned instance

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSizeOf"

int32 PropertyHandle :: GetSizeOf ( )
{
  DBFieldDef *field_def;
  return ( (field_def = GetDescription()) 
           ?  field_def->fmcbsize 
           :  UNDEF );

}

/******************************************************************************/
/**
\brief  GetSortKey - 



\return keyname - Name of sort key

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKey"

char *PropertyHandle :: GetSortKey ( )
{
  ACObject    *obh = StartRTA();
  char        *key;
  ValidateNode(YES);
  
  if ( IsValid() )
    key = Tnodeptr->GetSortKey();

  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  GetSortKeyLength - Get sort key length

        The  function  returns  the  length  of  the selected sort key. When the
        collection is unordered the function returns 0.

\return key_len - Size for internal key

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeyLength"

int16 PropertyHandle :: GetSortKeyLength ( )
{
  ACObject    *obh = StartRTA();
  int32        klen = UNDEF;
  ValidateNode(NO);
  
  if ( IsValid() )
    klen = Tnodeptr->GetSortKeyLength();

  obh->StopReadTA(NO);
  return(klen);
}

/******************************************************************************/
/**
\brief  GetSortKeySMCB - 



\return smcbptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *PropertyHandle :: GetSortKeySMCB ( )
{
  ACObject    *obh = StartRTA();
  smcb        *smcbptr = NULL;
  ValidateNode(NO);
  
  if ( IsValid() )
    smcbptr = Tnodeptr->GetSortKeySMCB();

  obh->StopReadTA(NO);
  return(smcbptr);
}

/******************************************************************************/
/**
\brief  GetString - Get text data

        The  function returns the text part for data stored as XML or HTML text.
        When  the data  does not  contain XML  or HTML, the function returns the
        same result as GetString().

\return string - String area
-------------------------------------------------------------------------------
\brief  i0 - Get string for current property

        The function returns the string value for the current property.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *PropertyHandle :: GetString ( )
{
  ACObject     *obh = StartRTA();
  char         *result = "";
BEGINSEQ
  if ( !IsSelected() )
  {
    if ( IsMemo(NO) || IsAutoSelection() )
      Get(FIRST_INSTANCE);
    if ( !IsSelected(NO) )                           ERROR
  }
  result = Tnodeptr->GetString();

RECOVER
  result = "";
ENDSEQ
  obh->StopReadTA(NO);
  return(result);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *PropertyHandle :: GetString (char *prop_path )
{
  ACObject     *obh = StartRTA();
  char         *result = "";
  char          string[13];


BEGINSEQ
  if ( !IsValid() )                                  ERROR

  if ( prop_path && 
       (!memcmp(prop_path,"__IDENTITY",10) || 
        !memcmp(prop_path,"__LOID",6)        )  )
  {
    gvtxltoa(GetID(),string,10);
    SetActionResult(string);
    result = GetActionResult();
  }
  else if ( !memcmp(prop_path,"__GUID",6) )
    result = GetGUID();
  else if ( !memcmp(prop_path,"__TYPE",6) )
    result = GetCurrentType();
  else
    result = Tnodeptr->GetString(prop_path);
//  result = GetPropertyHandle(prop_path)->GetString();

RECOVER
  result = "";
ENDSEQ
  obh->StopReadTA(NO);
  return(result);
}

/******************************************************************************/
/**
\brief  GetStringLength - Provide stringlength for instance

        The  function returns the maximum lengts of the string that results from
        converting the instance into a string.

\return size - Size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringLength"

uint32 PropertyHandle :: GetStringLength ( )
{
  DBFieldDef *field_def;
  return ( (field_def = GetDescription()) 
           ?  field_def->GetStringLength()
           :  UNDEF );


}

/******************************************************************************/
/**
\brief  GetStringValue - Get property instance as string value

        The  function returns the  string value for  the current property handle
        or  for  the  attribute  passed  in  prop_path. In addition to explicite
        properties  defined  for  the  structure  of  the  instance '__LOID' and
        '__GUID'  can be passed as property  path (prop_path) for retrieving the
        local  object  identifier  and  the  global  unique  identifier  for the
        instance.
        In  contrast  to  GetString()  the  no  instance must be selected in the
        property handle.

\return string - String area
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringValue"

char *PropertyHandle :: GetStringValue ( )
{
  ACObject    *obh = StartRTA();
  char        *area = "";
  if ( !IsSelected() )
    if ( IsMemo() )
      Get(FIRST_INSTANCE);
  
  if ( IsValid() )
    area = Tnodeptr->GetString();

  obh->StopReadTA(NO);
  return(area);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringValue"

char *PropertyHandle :: GetStringValue (char *prop_path )
{
  ACObject    *obh = StartRTA();
  char        *result = NULL;
  char         string[13];
  if ( !memcmp(prop_path,"__IDENTITY",10) || 
       !memcmp(prop_path,"__LOID",6)         )
  {
    gvtxltoa(GetID(),string,10);
    SetActionResult(string);
    result = GetActionResult();
  }
  else if ( !memcmp(prop_path,"__GUID",6) )
    result = GetGUID();
  else
    result = GetPropertyHandle(prop_path)->GetStringValue();

  obh->StopReadTA(NO);
  return(result);
}

/******************************************************************************/
/**
\brief  GetStructDef - Get structure definition

        The  function returns the structure definition  for the instances in the
        collection.  For  weak  typed  collection  the function returns the base
        structure definition defined for the weak typed collection.

\return struct_def - Pointer to generel structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *PropertyHandle :: GetStructDef ( ) const
{
  ACObject    *obh = StartRTA();
  DBStructDef *strdef = NULL;
  ValidateNode(NO);
  
  if ( IsValid() )
    strdef = Tnodeptr->GetStructDef();

  obh->StopReadTA(NO);
  return(strdef);
}

/******************************************************************************/
/**
\brief  GetSubString - 



\return string - String area
/******************************************************************************/
/**
\brief  i0 - 



\param  start_pos - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubString"

char *PropertyHandle :: GetSubString (int32 start_pos, int32 length )
{
  ACObject    *obh = StartRTA();
  NString      result;
  int32        curlen = 0;
  char        *string = "";
BEGINSEQ
  if ( !(string = Tnodeptr->GetString()) )           ERROR
  curlen = strlen(string);
  if ( curlen <= start_pos )                         ERROR

  if ( length == AUTO )
    length = curlen-start_pos;
    
  result = string+start_pos;
  Tnodeptr->set_result_string(result,length);

  string = Tnodeptr->get_nstring();
RECOVER
  string = "";
ENDSEQ
  obh->StopReadTA(NO);
  return(string);
}

/******************************************************************************/
/**
\brief  GetTNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTNode"

node *PropertyHandle :: GetTNode ( )
{

  return ( this && nodeptr ? Tnodeptr : NULL );

}

/******************************************************************************/
/**
\brief  GetText - 



\return string - String area
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetText"

char *PropertyHandle :: GetText ( )
{
  ACObject    *obh = StartRTA();
  logical      paragraph = NO;
  char         *result = "";
BEGINSEQ
  if ( !IsSelected() )
  {
    if ( IsMemo() || IsAutoSelection() )
      Get(FIRST_INSTANCE);
    if ( !IsSelected() )                             ERROR
  }
  if ( result = Tnodeptr->GetString() )
  {
    if ( *result != '<' )                            LEAVESEQ
    XMLString  xs(result,UNDEF);
    nodeptr->get_nstring() = "";
    if ( xs.GetTextData(nodeptr->get_nstring(),paragraph) )
                                                     ERROR
    result = nodeptr->get_nstring();
  }


RECOVER
  result = "";
ENDSEQ
  obh->StopReadTA(NO);
  return(result);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetText"

char *PropertyHandle :: GetText (char *prop_path )
{
  ACObject    *obh = StartRTA();
  char        *result = NULL;
  char         string[13];
  if ( !memcmp(prop_path,"__IDENTITY",10) || 
       !memcmp(prop_path,"__LOID",6)         )
  {
    gvtxltoa(GetID(),string,10);
    SetActionResult(string);
    result = GetActionResult();
  }
  else if ( !memcmp(prop_path,"__GUID",6) )
    result = GetGUID();
  else if ( !memcmp(prop_path,"__TYPE",6) )
    result = GetCurrentType();
  else
    result = GetPropertyHandle(prop_path)->GetText();

  obh->StopReadTA(NO);
  if (result) return result;
  else return "";
}

/******************************************************************************/
/**
\brief  GetTime - Get property instance as time value

        The  function returns the time value  for the current property handle or
        for the attribute passed in prop_path.

\return time_val - Time value
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

dbtm PropertyHandle :: GetTime ( )
{

  return ( IsSelected() 
           ? Tnodeptr->dbf::GetTime() 
           : dbtm() );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

dbtm PropertyHandle :: GetTime (char *prop_path )
{

  return ( IsSelected() 
           ? Tnodeptr->GetTime(prop_path) 
           : dbtm() );
//  return( GetPropertyHandle(prop_path)->GetTime());

}

/******************************************************************************/
/**
\brief  GetType - Get basic collection type

        The  function returns the type name for the instances in the collection.
        For  weak  typed  collection  the  function returns the name of the base
        structure defined for the weak typed collection.

\return strnames - Structure name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetType"

char *PropertyHandle :: GetType ( )
{
  ACObject    *obh = StartRTA();
  char        *types = NULL;
  ValidateNode(NO);
  
  if ( IsValid() )
    types = Tnodeptr->GetType();

  obh->StopReadTA(NO);
  return(types);
}

/******************************************************************************/
/**
\brief  GetValid - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValid"

logical PropertyHandle :: GetValid ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( !nodeptr )
    nodeptr = new node();
      
  if ( !nodeptr->IsValid() )                         ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  GetValue - Get instance value

        The  function returns the value for  the property instance. It should be
        used  for accessing attribute  handles. In contrast  to Get the function
        returns  an  instance  area  also  when  the  attribute  handle  is  not
        positioned (e.g. for the initial instance before creating an instance). 
        For  collection properties the function works  the same way as the Get()
        function  except when passing AUTO as index value. In this case GetValue
        returns the instance area also when no instance is selected. 
        When  accessing array attributes the  function returns the array element
        according to the passed index.

\return instance - Instance area

\param  lindx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValue"

Instance PropertyHandle :: GetValue (int32 lindx0 )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  ValidateNode(YES);
  
  if ( IsValid() )
    instance = Tnodeptr->GetValue(lindx0);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  GetVersion - Get version number for selected instance

        The  function  returns  the  version  number  for the instance selected.
        Since  instance  versions  are  created  only  in  case  of  updates the
        requested  version  in  the  property  handle  might  be higher than the
        version  returned  from  the  current instance. The function returns the
        version  number, only. Fo  determining the time  period you can call the
        ACObject::VersionIntervall() function when using database versions.

\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 PropertyHandle :: GetVersion ( )
{
  ACObject    *obh = StartRTA();
  uint16       version = USHORTMAX;
  ValidateNode(NO);
  
  if ( IsValid() )
    version = Tnodeptr->GetVersion();

  obh->StopReadTA(NO);
  return(version);
}

/******************************************************************************/
/**
\brief  GetYear - 



\return int_val - Integer value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetYear"

int32 PropertyHandle :: GetYear ( )
{

  return( IsSelected() 
          ? Tnodeptr->dbf::GetDate().GetYear() 
          : 0 );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetYear"

int32 PropertyHandle :: GetYear (char *prop_path )
{

//  return( GetPropertyHandle(prop_path)->GetDate());
  return( IsSelected() 
          ? Tnodeptr->GetDate(prop_path).GetYear()
          : 0 );

}

/******************************************************************************/
/**
\brief  Group - Grouping operation

        The  grouping  operation  allows  grouping  a  collection  of  instances
        according  to  a  condition,  key  or  list of attributes. The instances
        grouped  are collected  in a  property named  'partition', which has the
        same type as the input collection for the operation. 
        When  defining  conditional  values  in  the  grouping  rule,  a  string
        attribute  named 'value' is created for each output instance. Otherwise,
        the  output  contains  the  attributes  defined in the attribute list or
        composing  the  key.  When  passing  an ODABA OQL expression as grouping
        rule,  the  type  of  the  attribute  in  the target depends on the type
        returned by the expression.
        When  defining conditional  values, the  instance is associated with the
        first  value,  that  matches  the  condition  when passing distinct YES.
        Otherwise,  the instance is associated with  each value that matches the
        condition, which might create duplicates. 
        When  the calling property  handle refers to  a non empty collection all
        instances  are removed before performing the operation. When the calling
        property  handle is  empty the  function creates  a temporary extend for
        storing  the  result.  You  may  change  the  buffer size for the target
        property  handle to increase  the performance of  the operation. This is
        not necessary, when you group by sort key. 
        ot  able to react on type  changes in upper weak-typed property handles.
        To  avoid  problems  with  static  property handles (error 348) create a
        shared property handle as described above.

\return result_ref - Result property hadle

\param  prophdl_ref - Reference to Property handle
\param  grouping_rule - Grouping rule
\param  distinct - Distinct option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Group"

PropertyHandle &PropertyHandle :: Group (PropertyHandle &prophdl_ref, char *grouping_rule, logical distinct )
{
  ACObject    *obh = StartRTA();

BEGINSEQ
  if ( !this || (nodeptr && 
                 ( !nodeptr->IsValid() || 
                  (Tnodeptr && !Tnodeptr->IsValid()))) ) ERROR
//  if ( CreatePIHandle(prophdl_ref,distinct) )            ERROR
  
//  Tnodeptr->Group(prophdl_ref.Tnodeptr,grouping_rule,AUTO);
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  HasData - 



\return cond - Return value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasData"

logical PropertyHandle :: HasData ( )
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( IsValid() )
    cond = Tnodeptr->IsCollection()  
           ? IsPositioned()
           : ((dbf *)Tnodeptr)->GetArea() != NULL;

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  HasDescription - Is property handle dirty

        The  function checks,  whether the  selection or  instance in a property
        handle  has been changed.  This happens in  client/server mode, when the
        selection  or instance  in a  property handle  on the serverside differs
        from the selection or instance on the client side. 
        Usually,  the client automatically submits  a refresh, when the instance
        is  dirty after a client server  action, e.g. after executing an action.
        The  application  can  avoid  the  refrech  by  resetting the dirty flag
        (ResetDirty()).

\return cond - Return value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasDescription"

logical PropertyHandle :: HasDescription ( )
{

  return( GetDescription() ? YES : NO );

}

/******************************************************************************/
/**
\brief  HasGenericAttributes - Does the instance have generic attributes

        The  function  returns  true  (YES)  when  the  instance  has  generic 
        attributes and false (NO) otherwise.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasGenericAttributes"

logical PropertyHandle :: HasGenericAttributes ( )
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->HasGenAttribute();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  HasIndex - Does a collection have an index?

        The  fucntion checks whether an index is defined for the property handle
        or  not. When  an index  is defined  this does not necessarily mean that
        the  collection is ordered,  since there are  also indexes for unordered
        collections.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasIndex"

logical PropertyHandle :: HasIndex ( )
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->HasIndex();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  Inherits - 



\return cond - Return value
-------------------------------------------------------------------------------
\brief  A00 - 



\param  strnames - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Inherits"

logical PropertyHandle :: Inherits (char *strnames )
{
  ACObject    *obh = StartRTA();
  char               *type;
  char                string[ID_SIZE+1];
  logical             cond = YES;
BEGINSEQ
  ValidateNode(NO);
  
  if ( !IsValid() )                                  ERROR
  cond =  Tnodeptr->Inherits(strnames);
  

RECOVER
  cond = NO;
ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  From - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Inherits"

logical PropertyHandle :: Inherits (PropertyHandle &prophdl )
{
  ACObject           *obh = StartRTA();
  logical             cond = YES;
BEGINSEQ
  prophdl.ValidateNode(NO);
  if ( !prophdl.IsValid() )                          ERROR

  cond = Inherits(prophdl.GetCurrentType());
RECOVER
  cond = NO;
ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  InitPropertyHandle - Init property handle

        The  function initilizes a property handle in a transient instance or in
        a  transient  instance  field.  The  field  must  have  been  defined as
        proprtty  handle  attribute  (e.g.  PI(Person)),  i.e.  as  generic type
        property handle field. 
        Passing an empty property handle will deinitilize the property handle.
        The  function returns  a pointer  to the  initialized property handle or
        NULL, when initializing was not possible.

\return property_handle - Pointer to a property handle

\param  prop_path - Property path
\param  property_handle - Pointer to a property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitPropertyHandle"

PropertyHandle *PropertyHandle :: InitPropertyHandle (char *prop_path, PropertyHandle *property_handle )
{
  PropertyHandle     *ph = NULL;
BEGINSEQ
  if ( ph = GetPropertyHandle(prop_path) )
    if ( ph->Open(property_handle) )                 ERROR

RECOVER
  ph = NULL;
ENDSEQ
  return(ph);
}

/******************************************************************************/
/**
\brief  InitResult - Init property handle for result of an operation



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  operand1 - 
\param  operand2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical PropertyHandle :: InitResult (PropertyHandle &operand1, PropertyHandle &operand2 )
{

  return( IsValid() && operand1.IsValid() && operand2.IsValid()
          ? Tnodeptr->InitResult(operand1.get_nodeptr(),operand2.get_nodeptr())
          : YES );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  dictptr - Dictionary handle
\param  type - 
\param  size - Size
\param  precision - Precision
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical PropertyHandle :: InitResult (DictionaryHandle &dictptr, char *type, uint32 size, uint16 precision )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsValid() )
    term = Tnodeptr->InitResult(dictptr.get_dictionary(),type,size,precision);

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  InitValue - 



\return term - Termination code

\param  dicthdl - 
\param  co - 
\param  variables - 
\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitValue"

logical PropertyHandle :: InitValue (DictionaryHandle &dicthdl, PropertyHandle *co, ParmList *variables, ParmList *parameters )
{
  ACObject               *obh = StartRTA();
  DBFieldDef             *flddef;
  ExpressionReference    *expr_ref;
  logical                 term = NO;
BEGINSEQ
  if ( !IsValid() || !(flddef = Tnodeptr->GetInstFieldDef()) ||
       !(expr_ref = flddef->get_initval_expr())   )  ERROR

  expr_ref->GetExpressionDecl(dicthdl.get_dictionary());
  expr_ref->Execute(*this,co,variables,parameters);
  
  

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - Initialise instance area

        The  function  initializes  the  area  of  the  passed instance with the
        defined  default  values.  When  no  instance  is  passed  the  internal
        instance area for the property handle instance is initialized.
        This  function does  not work  for simple  property handles (e.g. string
        property  handle  as  PH("string")).  For  initializing  simple property
        handle    you    must    explicitly    pass    the    instance    area  
        (ph.Initialize(ph.GetArea()).

\return term - Termination code

\param  instance_w - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical PropertyHandle :: Initialize (Instance instance_w )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(YES);
  
  if ( IsValid() )
    term = Tnodeptr->InitInstance(&instance_w);

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  InsertString - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  string - String area
\param  position - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertString"

logical PropertyHandle :: InsertString (char *string, int32 position )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ProvideArea();
  
  if ( IsValid() )
    term = Tnodeptr->InsertString(string,position);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  InsertTerminator - Insert line terminator for large text fields

        The  function inserts the  terminator string (string)  at the end of the
        text field.

\return term - Termination code

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertTerminator"

logical PropertyHandle :: InsertTerminator (char *string )
{
  ACObject    *obh = StartRTA();
  fmcb        *fmcbptr = GetDescription();
  void        *datarea;
  char        *pos = NULL;
  logical      str_opt = YES;
  int          len;
  logical      term = NO;
BEGINSEQ
  if ( !(datarea = GetArea()) )                      ERROR
  if ( !fmcbptr || !string || !*string)              ERROR
  
  SDBEV1(string,UNDEF);
  if ( (len = strlen(string)) > fmcbptr->fmcbsize )  SDBERR(219)
    
  switch ( fmcbptr->fmcbityp )
  {
    case T_CHAR   : pos = ((char *)datarea) + MIN(gvtutle((char *)datarea,fmcbptr->fmcbsize),fmcbptr->fmcbsize-len);
                    str_opt = NO;
                    break;
    case T_STRING : 
    case T_MEMO   : pos = strlen((char *)datarea) + len > fmcbptr->fmcbsize 
                          ? ((char *)datarea) + fmcbptr->fmcbsize-len
                          : ((char *)datarea) + strlen((char *)datarea);
                    break;
    default       : SDBEV1("InsertTerminator",UNDEF)
                    SDBEV2(fmcbptr->fmcbname,sizeof(fmcbptr->fmcbname))
                    SDBERR(220)
  }
  if ( str_opt )
    strcpy(pos,string);
  else
    memcpy(pos,string,len);
RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  InstanceInserted - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceInserted"

logical PropertyHandle :: InstanceInserted ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( IsPositioned() )
    cond = Tnodeptr->InstanceInserted();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  InstanceToString - Convert Instance to string

        The  function  converts  the  selected instance into string format. Only
        attributes and MEMO fields are converted.

\return string - String area
/******************************************************************************/
/**
\brief  i01 - 



\param  string_sep - String separator
\param  field_sep - Field separator
\param  block_sep - 
\param  empty_string - String for empty values
\param  skip_trans - Skip transient fields
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceToString"

char *PropertyHandle :: InstanceToString (char *string_sep, char *field_sep, char *block_sep, char *empty_string, logical skip_trans )
{
  ACObject    *obh = StartRTA();
  char         *string = NULL;
  ValidateNode(YES);
  
  if ( IsValid() )
    string = Tnodeptr->InstanceToString(string_sep,field_sep,block_sep,empty_string,skip_trans);

  obh->StopReadTA(NO);
  return(string);
}

/******************************************************************************/
/**
\brief  Intersect - Intersect collections

        The  result collection contains all instances that are contained in each
        operand  collections. The existence  of an instance  in a collection can
        be  checked based on the  sort key (passing YES  for ik_opt) or on local
        identities  (LOID). Using the LOID is save but comparing the key is much
        faster. Hence, the key check should be used whenever possible. 
        Calling  the function with one operator creates the intersection between
        the  calling  and  the  passed  collection  and stores the result in the
        calling  collection.  Otherwise  the  operation  is  performed  with the
        passed  operands storing the result in  the collection referenced by the
        calling  property handle. When  the calling property  handle refers to a
        non  empty  collection  all  instances are removed before performing the
        operation.  When  the  calling  property  handle  is  empty the function
        creates a temporary extend for storing the result.

\return result_ref - Result property hadle
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_hdl1 - First Property handle
\param  prop_hdl2 - Second Property handle
\param  sk_opt - Sort key option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Intersect"

PropertyHandle &PropertyHandle :: Intersect (PropertyHandle &prop_hdl1, PropertyHandle &prop_hdl2, char sk_opt )
{
  PropertyHandle   *ph_list[] = {&prop_hdl1,&prop_hdl2};
  Intersect(ph_list,2,sk_opt);
  return(*this);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  ph_list - List of property handles
\param  count - Number of entries
\param  sk_opt - Sort key option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Intersect"

PropertyHandle &PropertyHandle :: Intersect (PropertyHandle **ph_list, int32 count, char sk_opt )
{
  ACObject    *obh = NULL;
  int32        indx0 = 0;
BEGINSEQ
  if ( !this || (nodeptr && !nodeptr->IsValid()) 
             || (nodeptr && Tnodeptr && !Tnodeptr->IsValid()) ) 
                                                     ERROR
  if ( CreatePIHandle(ph_list,count,UNDEF,sk_opt))   ERROR

  obh = StartRTA();
  Tnodeptr->Intersect(ph_list,count,sk_opt);
  obh->StopReadTA(NO);

RECOVER

ENDSEQ
  return(*this);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  prophdl_ref - Reference to Property handle
\param  sk_opt - Sort key option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Intersect"

PropertyHandle &PropertyHandle :: Intersect (PropertyHandle &prophdl_ref, char sk_opt )
{
  ACObject    *obh = StartRTA();

BEGINSEQ
  if ( ValidateNode(YES) || prophdl_ref.ValidateNode(YES) )
                                                     ERROR
  Tnodeptr->Intersect(prophdl_ref.Tnodeptr,sk_opt);
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Is - Is property handle the same

        The  function  compares  the  handle  cursors referenced in the property
        handles.  When the  cursors in  both property  handles are the same, the
        function returns YES (true). 
        Property  handles are the same, when the  refer to the same cursor, i.e.
        when  using the pointer  constructor, but are  different, when using the
        copy constructor: 
        prophdl.Is(PropertyHandle(&ürophdl)) is true
        prophdl.Is(PropertyHandle(ürophdl)) is false
        The  cursor in the property handle  may change for subordinated property
        handles,  when  the  parent  property  handle  is  weak or un-typed. The
        cursor is updated before comparing.

\return term - Termination code

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Is"

logical PropertyHandle :: Is (PropertyHandle &prop_hdl )
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  prop_hdl.ValidateNode(NO);
  
  cond = this == &prop_hdl || (!this && !prop_hdl.nodeptr) ||
         (this && &prop_hdl && nodeptr == prop_hdl.nodeptr) 
         ? YES : NO;
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsA - 



\return cond - Return value
/******************************************************************************/
/**
\brief  i0 - 



\param  strnames - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsA"

logical PropertyHandle :: IsA (char *strnames )
{
  ACObject    *obh  = StartRTA();
  char        *type = NULL;
  char         string[ID_SIZE+1];
  logical      cond = YES;
BEGINSEQ
  ValidateNode(NO);
  
  if ( !IsValid() )                                 ERROR

  if ( !(type = Tnodeptr->GetCurrentType()) )       ERROR
  gvtxbts(string,strnames,ID_SIZE);
  if ( strcmp(string,type) )                        ERROR
RECOVER
  cond = NO;
ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsActive - Is property an active property

        An  active  property  is  a  property  that  is able to react on events.
        Active  properties  are  treated  in  a  special  way  since  events are
        generated for several occations.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActive"

logical PropertyHandle :: IsActive ( ) const
{
  DBFieldDef  *field_def = GetDescription();
  return ( field_def && field_def->GetResourceID() > 0 ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsAttribute - Is property an attribute?

        The  function returns whether the property handle refers to an attribute
        (YES)  or  not  (NO).  The  functio  returns  also  NO  for  shared base
        structure  instances, which are considered  rather as relationships than
        attributes.  Imbedded base structure  instances are, however, considered
        as  attributes.  The  function  returns  NO also for generic attributes,
        which are considered as references.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttribute"

logical PropertyHandle :: IsAttribute ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->IsAttribute();


  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsAutoSelection - Is auto selection enabled

        The  function  returns,  whether  auto  selection  is  enabled  for  the
        property  handle.  Auto-selection  is  enabled, when a fixed position or
        key  value  has  been  set  for  the property handle for selection (e.g.
        using a path like 'children(0) or children('Paul')).

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAutoSelection"

logical PropertyHandle :: IsAutoSelection ( ) const
{
  logical              cond = YES;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  if ( Tnodeptr->IsAutoPosition() )                  LEAVESEQ
  
  if ( Tnodeptr->get_nodetype() != NT_ACPathNode )   ERROR
  if ( Tnodeptr->IsCollection() )                    ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsBasedOn - 



\return cond - Return value

\param  strnames - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasedOn"

logical PropertyHandle :: IsBasedOn (char *strnames ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->IsBasedOn(strnames);

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsBasetypeProperty - Is property member of the base type

        The  function  checks  for  members  of weak typed instances whether the
        property is part of the common base type (YES) or not (NO).

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasetypeProperty"

logical PropertyHandle :: IsBasetypeProperty ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->IsBasetypeProperty();


  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsBasicType - Is the type of the PropertyHandle an elementary one ?

        The  Type  of  the  Property  Handle  is  either  a  basic  type  or  an
        enumeration  or a structure. The function  returns YES when the property
        refers to a basic type and NO otherwise.
        ndle   for   selection   (e.g.   using   a   path   like 'children(0) or
        children('Paul')).

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasicType"

logical PropertyHandle :: IsBasicType ( ) const
{
  DBFieldDef  *field_def;
  return ( (field_def = GetDescription()) &&
           field_def->fmcbityp < 0 
           ? YES 
           : NO );



}

/******************************************************************************/
/**
\brief  IsClient - Is property handle a client handle

        The  function returns whether the property handle has been created for a
        client  or a local application. The function returns NO, when the handle
        has been created on the server side in a client server environment.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsClient"

logical PropertyHandle :: IsClient ( ) const
{

  return( IsValid() 
          ? Tnodeptr->IsClientNode()
          : NO );  


}

/******************************************************************************/
/**
\brief  IsCollection - Is property a collection or reference?

        The  function returns whether the property handle refers to a collection
        (YES)  or not  (NO). References  and relationships are always considered
        as collections, as well as generic attributes, extents and views.

\return cond - Return value

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCollection"

logical PropertyHandle :: IsCollection (char chkopt ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( chkopt )
    ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->IsCollection();


  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsCollectionUpdate - Can collection be updated

        The  function  returns  whether  the  collection  can  be  updated, i.e.
        whether  instances can be added, renamed  or removed or deleted from the
        collection (YES) or not (NO).

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCollectionUpdate"

logical PropertyHandle :: IsCollectionUpdate ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
BEGINSEQ
  if ( ValidateNode(NO) )                           ERROR
  cond = Tnodeptr->CanUpdateCollection();

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsCopyHandle - Is property handle a copy handle

        The  function returns whether the property handle is a copy from another
        handle  (YES) or not (NO). Copy handles  are created based on a property
        handle  but using an  own cursor. Copy  handles are closed automatically
        when its origin is closed.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCopyHandle"

logical PropertyHandle :: IsCopyHandle ( ) const
{

  return( IsValid() 
          ? Tnodeptr->IsCopyNode()
          : NO );  


}

/******************************************************************************/
/**
\brief  IsDirty - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDirty"

logical PropertyHandle :: IsDirty ( )
{

  return( IsValid() ? Tnodeptr->get_bnode()->IsDirty() : NO);

}

/******************************************************************************/
/**
\brief  IsEmpty - Is property instance empty?

        The  function returns whether the property  handle is empty (YES) or not
        (NO).  A property is considered as emty  when it is a collection with no
        instances or (if it is not a collection) when:
        - the value is false (LOGICAL)
        - the value is 0 (INT, REAL, Enumeration, DATE, TIME, DATETIME)
        - the value is 0, ' ' oder 'N' (CHAR, STRING,CCHAR,MEMO)
        - when all values for a structured instance are empty

\return cond - Return value
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical PropertyHandle :: IsEmpty ( ) const
{

  return( !IsTrue() );

}

/******************************************************************************/
/**
\brief  IsEnumeration - Is the type of the PropertyHandle an enumeration ?

        The  Type  of  the  property  handle  is  either  a  basic  type  or  an
        enumeration  or a structure.The function  returns true when the property
        handle refers to an enumeration.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnumeration"

logical PropertyHandle :: IsEnumeration ( ) const
{
  ACObject    *obh = StartRTA();
  smcb        *smcbptr;
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid() )
    if ( smcbptr = Tnodeptr->GetSMCB() )
      if ( smcbptr->smcbstyp == ST_CODE )
        cond = YES;

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsGenericAttribute - Is property a generic attribute?

        The  function returns true  (YES), when the  property handle refers to a
        generic attribute and NO otherwise.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGenericAttribute"

logical PropertyHandle :: IsGenericAttribute ( )
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->IsGenericAttribute();


  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsInitInstance - In instance initialized instance

        When  the instance has been provided with the GetInitInstance() function
        the  instance  has  not  yet  been  created  and  access  is limited for
        sub-ordinated  property  handles.  The  function  returns  whether  the 
        selected  instance in the property handle  is an initialised instance or
        not.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInitInstance"

logical PropertyHandle :: IsInitInstance ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( IsValid() )
    cond = Tnodeptr->IsInitInstance();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsMemo - Check property type for memo field

        The  function  returns  true  (YES)  when the property refers to a large
        text field (MEMO).

\return cond - Return value

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsMemo"

logical PropertyHandle :: IsMemo (char chkopt ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( chkopt )
    ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->IsMemo();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsModified - Has property unsafed modifications ?

        The  function returns whether the instance in thr property Handle or any
        subordinated instance was modified, but not yet saved.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsModified"

logical PropertyHandle :: IsModified ( )
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( IsSelected() )
    cond = Tnodeptr->IsModified();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsNewInstance - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewInstance"

logical PropertyHandle :: IsNewInstance ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( IsPositioned() )
    cond = Tnodeptr->IsNewInstance();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsNumeric - Check property type for numeric

        The  functio  returns  true  (YES)  when the property handle describes a
        numeric value (INT, UINT, REAL).

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNumeric"

logical PropertyHandle :: IsNumeric ( ) const
{
  logical     cond = YES;
  DBFieldDef *field_def = GetDescription();
BEGINSEQ
  if ( !field_def )                                  ERROR
    
  switch ( field_def->fmcbityp ) 
  {
    case T_UINT :
    case T_INT  : 
//  case T_BIT  : 
    case T_REAL : LEAVESEQ
    default     : ERROR
  }

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsOldInstance - Is old instance

        The  function returns whether  the instance is  an old instance (YES) or
        not (NO). 
        (-> IsNewInstance()).

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOldInstance"

logical PropertyHandle :: IsOldInstance ( ) const
{

  return ( !IsNewInstance() );

}

/******************************************************************************/
/**
\brief  IsOwner - Is Property Handle owner of the data source

        The  function returns true  (YES), when the  property handle is the only
        user  of  the  data  source  handle, i.e. when the data source handle is
        closed when closing the property handle.
        Whe  the  data  source  is  shared by several property handles, the data
        source  handle is shared by several  property handles, the last property
        handle  closed will destroy  the data source  handle. as long as several
        property  handles share  the data  source handle,  no property handle is
        considered as owner.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOwner"

logical PropertyHandle :: IsOwner ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( !nodeptr )                                    ERROR

  if ( nodeptr->get_use_count() > 1 )                ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsPathExpression - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPathExpression"

logical PropertyHandle :: IsPathExpression ( )
{
  ACObject    *obh = StartRTA();
  logical      cond = YES;
  if ( IsValid() )
    cond = Tnodeptr->IsPathExpression();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsPositioned - Is instance positioned

        The  function  checks  whether  there  is  an  instance selected for the
        property  handle. The  function returns  YES if  an existing instance is
        selected,  NO otherwise. When the property handle refers to an attribute
        with  a  parent  property  handle  it  returns  the  state of the parent
        instance. 
        When  an instance has been provided using the GetInitInstance() function
        the  property handle is not positioned. For checking whether an existing
        or  new instance  is selected  or not,  the IsSelected() function can be
        used.

\return cond - Return value

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical PropertyHandle :: IsPositioned (char chkopt ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
BEGINSEQ
  if ( chkopt && ValidateNode(NO) )                  ERROR
           
  if ( IsValid() )
    cond = Tnodeptr->IsPositioned();

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsReadOnly - Is property read only

        There  are several  reasons for  properties getting the read-only state.
        An  attribute is read-only when the instance  it belongs to has been set
        to  read-only for some  reason (used by  another user, cannot be updated
        by  current user  or others).  Collections are  usually set to read-only
        when  the instance the collection belongs to  has been set to read only,
        but  they  might  also  be  persistent  write protected (e.g. when being
        locked  in  workspaces).  Since  MEMO  fields  are  stored  as  separate
        instances,  a  MEMO  field  can  be  read-only  even  thought the parent
        instance  can  be  updated  (e.g.  when  being locked in a transaction).
        Moreover,  any property can be set to  read-only by means of the context
        function SetReadOnly() in the application. 
        Attributes  and  MEMO  fields  with  read-only  state cannot be updated.
        Collection  properties  that  are  read-only  do  not  allow  inserting,
        renaming or removing instances from the collection.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical PropertyHandle :: IsReadOnly ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(YES);
  
  if ( IsValid() )
    cond = nodeptr->IsReadOnly();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsSelected - Is instance selected

        The  function  checks  whether  there  is  an  instance selected for the
        property  handle.  The  function  returns  YES  if  an  instance (new or
        existing)  is selected, NO otherwise. When the property handle refers to
        an  attribute with a parent property handle  it returns the state of the
        parent instance. 
        In  constrast to the IsPositioned()  function here instances, which have
        been  provided using  the GetInitInstance()  function, are considered as
        selected as well.

\return cond - Return value

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical PropertyHandle :: IsSelected (char chkopt ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
BEGINSEQ
  if ( chkopt && ValidateNode(YES) )                 ERROR
           
  if ( IsValid() )
    cond = Tnodeptr->IsSelected();

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsSensitive - Is property handle sensitive against modifications

        A  sensitive property is a property that  is part of keys used in global
        indexes.  In ODABA  modifications on  indexes will  lock the index until
        the  transaction is  terminated. Thus,  updating sensitive properties in
        long  transactions  may  cause  uncomfortable lock situations. Sensitive
        properties should not be allowed being updated in long transactions.

\return cond - Return value
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSensitive"

logical PropertyHandle :: IsSensitive ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(YES);
  
  if ( IsValid() )
    cond = nodeptr->IsSensitive();


  obh->StopReadTA(NO);
  return(cond);


}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSensitive"

logical PropertyHandle :: IsSensitive (char *prop_path ) const
{
  PropertyHandle      *ph = (PropertyHandle *)this;
  if ( prop_path && *prop_path )
    ph = ph->GPH(prop_path);
  
  return( ph->IsSensitive() );

}

/******************************************************************************/
/**
\brief  IsServer - Is property handle a server handle

        The  function returns whether the property handle has been created for a
        server  or a local application. The function returns NO, when the handle
        has been created on the client side in a client server application.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsServer"

logical PropertyHandle :: IsServer ( ) const
{
  logical                 term = NO;
  return( IsValid() 
          ? Tnodeptr->IsServerNode()
          : NO );  

  return(term);
}

/******************************************************************************/
/**
\brief  IsShareBaseHandle - Is property handle for base structure

        The  function  returns  whether  the  property  handle  is a handling an
        independent  (shared)   base  structure  (YES) or not (NO). The function
        returns  NO for all other property handles, imbedded base structures and
        in case of error.

\return cond - Return value

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsShareBaseHandle"

logical PropertyHandle :: IsShareBaseHandle (char chkopt ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( chkopt )
    ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->get_nodetype() == NT_ACShareBase;

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsStructure - Is the type of the PropertyHandle a defined Structure ?

        The  function returns true (YES) if the type of the property handle is a
        structure  and false (NO) if the type  of the property handle is a basic
        type or an enumeration.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsStructure"

logical PropertyHandle :: IsStructure ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  DBStructDef *strdef = NULL;
  if ( (strdef = GetStructDef()) && 
       strdef->smcbstyp != ST_BASE && strdef->smcbstyp != ST_CODE )
    cond = YES;

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsText - Check property type for text

        The  function checks whether  the propertyhandle refers  to a text field
        (YES)  or not (NO). Text fields are  fields with type CHAR, MEMO, STRING
        and CCHAR.

\return cond - Return value

\param  chkopt - Check option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsText"

logical PropertyHandle :: IsText (char chkopt ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( chkopt )
    ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->IsText();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsTransient - Is property transient

        Attributes  as  well  as  references  might  be  defined  as  transient 
        properties. Transient properties are filled by the application.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTransient"

logical PropertyHandle :: IsTransient ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid(NO) )
    cond = nodeptr->IsTransient();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsTrue - Is value for property TRUE?

        The  function returns whether  the property handle  is empty (NO) or not
        (YES). (see IsEmpty()).
        are filled by the application.

\return cond - Return value
/******************************************************************************/
/**
\brief  i - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTrue"

logical PropertyHandle :: IsTrue ( ) const
{
  ACObject    *obh = StartRTA();
  node        *npt;
  fmcb        *fmcbptr;
  int32        long_val;
  logical    cond = YES;
BEGINSEQ
  if ( IsCollection() )
  {
    cond = Tnodeptr->GetCount() > 0 ? YES : NO;      LEAVESEQ
  }

  if ( !ProvideArea() )                              ERROR
  
  if ( !(fmcbptr = GetDescription(NO)) )             ERROR
  if ( !(npt = Tnodeptr) )                           ERROR
    
  switch ( fmcbptr->fmcbityp ) 
  {
    case T_NONE   :
    case T_VOID   :
    case UNDEF    : if ( fmcbptr->fmcbrlev > 0 )     SDBERR(154)
                    if ( !npt->GetArea() )           ERROR
                    memcpy(&long_val,npt->GetArea(),sizeof(int32));  
                    if ( !long_val )                 ERROR
                    break;    
    case T_UINT   : 
    case T_INT    : 
    case T_REAL   : 
    case T_BIT    : 
    case T_DATE   : 
    case T_TIME   : 
    case T_DATETIME: 
    case T_LO     : if ( !npt->IsTrue() )            ERROR
                    break;    
    case T_GUID   : if ( ((guid *)npt->GetArea())->IsEmpty() ) 
                                                     ERROR
                    break;    
    case T_CHAR   : 
    case T_CCHAR  : 
    case T_STRING : if ( !*npt->GetString() )        ERROR
                    break;
    default       :  switch( fmcbptr->fmcbrlev )
                     {
                       case R_GENERIC :
                       case R_INTERN  :
                       case R_DIRECT  : if ( fmcbptr->fmcbsmcb )
                                        {
                                          if ( fmcbptr->fmcbsmcb->IsEmpty((char *)npt->GetArea()) )
                                                     ERROR
                                        }
                                        else if ( !npt->IsTrue() )
                                                     ERROR
                                        break;    
                       default        :              SDBERR(154)
                     }
  }
RECOVER
  cond = NO;
ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTrue"

logical PropertyHandle :: IsTrue (char *prop_path ) const
{
  PropertyHandle *ph = (PropertyHandle *)this;
  if ( prop_path && *prop_path )
    ph = ((PropertyHandle *)this)->GPH(prop_path);
  
  return ( ph->IsTrue() );

}

/******************************************************************************/
/**
\brief  IsTyped - Is instance typed?

        The  function returns  YES when  the property  handle is valid and not a
        VOID or week typed reference. Otherwise the function returns NO.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTyped"

logical PropertyHandle :: IsTyped ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  DBFieldDef  *field_def;
  if ( (field_def = GetDescription()) )
    cond = !field_def->get_weak_typed() &&
           memcmp(field_def->fmcbname,"VOID ",5);

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsUserHandle - Is property handle user-defined

        The  function returns,  whether a  property handle is user-defined (i.e.
        constructed  by the application) or not (i.e. contructed by the system).
        You  may turn a system handle into a user handle by calling the property
        handle  contructor, i.e.  a property  handle is  considered being a user
        handle  as  soon  as  there  is at least one application property handle
        referring to the property handle (see also 'Pointer-Constructor').
        Note,  that  GetPropertyHandle(),  which  returns  a  property  handle 
        pointer, does not change a system handle into a user handle.
        In  many  cases,  context  functions  should be called for user handles,
        only, to avoid unecessary function calls for internal processes.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUserHandle"

logical PropertyHandle :: IsUserHandle ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( IsValid() )
    cond = Tnodeptr->IsUserHandle();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsValid - Check for valid property handle

        The  function checks whether the property  handle is valid. The function
        does not check whether the handle is opened (see {\b {.r Check}()}.
        This  function should be called when the application is not sure whether
        the handle is correct or not.

\return cond - Return value

\param  topt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical PropertyHandle :: IsValid (logical topt ) const
{

  return ( this && nodeptr && nodeptr->IsValid() &&
           ( ( topt &&   Tnodeptr && Tnodeptr->IsValid()  ) ||
             (!topt && (!Tnodeptr || Tnodeptr->IsValid()) ) ) );


}

/******************************************************************************/
/**
\brief  IsValidText - Checks text fields for valid characters

        The  function  validates  a  text  according to the characters passed in
        string.  If the property handle does not refer to a text filed or if the
        text  contains other characters than defined  in the string the function
        returns false (NO).

\return cond - Return value

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValidText"

logical PropertyHandle :: IsValidText (char *string ) const
{
  ACObject    *obh = StartRTA();
  char        *area = (char *)GetInstance().GetData();
  int          len;
  fmcb                   *fmcbptr;
  logical                 cond = YES;
BEGINSEQ
  if ( !IsText() || !area )                         ERROR
  
  fmcbptr = GetDescription();
  len = fmcbptr->fmcbityp == T_CHAR || fmcbptr->fmcbityp == T_CCHAR 
        ? GetDescription()->fmcbsize
        : strlen(area);
  
  if ( !::IsValid(area,len,string) )                 ERROR


RECOVER
  cond = NO;
ENDSEQ
  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsVariableType - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsVariableType"

logical PropertyHandle :: IsVariableType ( )
{

  return ( IsValid() 
           ? Tnodeptr->IsTypeVariable() 
           : YES );

}

/******************************************************************************/
/**
\brief  IsWeakTyped - Is reference weak typed

        The  function returns YES  if the reference  or collection is defined as
        weak  typed. In this case the type of instances may change from instance
        to  instance. All instances in the reference  are bases on a common base
        structure. 
        The   type   of   the   common   base   structure  can be retrieved with
        GetStructDef().  The  type  for  the  selected instance can be retrieved
        with GetCurrentType(). 
        Befor  inserting  a  new  instance  to a weak-typed refererence the type
        must be set with SetType().

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWeakTyped"

logical PropertyHandle :: IsWeakTyped ( ) const
{
  DBFieldDef  *field_def;
  return ( (field_def = GetDescription())
           ?  field_def->get_weak_typed() 
           :  NO );



}

/******************************************************************************/
/**
\brief  IsWrite - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWrite"

logical PropertyHandle :: IsWrite ( ) const
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  if ( IsSelected() )
    cond = Tnodeptr->IsWrite();

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  KeyToString - Convert internal key to string

        The  passed key will be converted  from the internal key instance format
        into  an extended SDF string. As  field separator '|' is used. Structure
        levels  are enclosed in  '{}'. Normally the  key passed is assumed to be
        structured  according to the  sort key selected  for the property handle
        or  according to the  identifying key (when  no sort key is defined). It
        is, however, also possible to pass a valid key name for conversion.

\return key_string - String area for key

\param  key_string - String area for key
\param  key_val - Internal key value
\param  key_name_w - Key name for conversion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyToString"

char *PropertyHandle :: KeyToString (Key key_string, Key key_val, char *key_name_w )
{
  ACObject    *obh = StartRTA();
  char         *string = NULL;
  ValidateNode(YES);
  
  if ( IsValid() )
    string = Tnodeptr->KeyToString(key_string.GetData(),key_val.GetData(),key_name_w); 

  obh->StopReadTA(NO);
  return(string);
}

/******************************************************************************/
/**
\brief  Locate - Locate object by identity

        The  function is searching for an instance with the given local identity
        (LOID)  in the collection  of the property  handle. The function returns
        NO  when the  instance could  be located.  The function returns an error
        (YES)  in case  of an  error or  when the  instance is not member of the
        collection.
        When  passing YES for read_opt the  instance is selected in the property
        handle.   Otherwise   it   is   located,   only   and   can be read with
        Get(CUR_INSTANCE). 
        pe must be set with SetType().

\return term - Termination code

\param  obident - Instance identity
\param  read_opt - Read option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical PropertyHandle :: Locate (int64 obident, logical read_opt )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  term = ( IsValid() 
           ? Tnodeptr->Locate(obident,read_opt)
           : YES );
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  LocateIndex - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  A00 - 



\param  set_pos0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateIndex"

logical PropertyHandle :: LocateIndex (int32 set_pos0 )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);

  term = ( IsValid() 
           ? Tnodeptr->LocateIndex(set_pos0)
           : YES );
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Variable - 



\param  prop_hdl - Property Handle
\param  exact_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateIndex"

logical PropertyHandle :: LocateIndex (PropertyHandle &prop_hdl, logical exact_w )
{
  Key             key;
  if ( (key = GetKeyFromParm(prop_hdl)).GetData() )
    return ( LocateKey(key,exact_w) );
  else
    return(YES);


}

/******************************************************************************/
/**
\brief  LocateKey - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  A00 - Lokate key by key value

        This  implementation  locates  the  key  by  means  of the key structure
        passed  to  the  function.  The  key  must  be  passed  according to the
        structure of the key including trailing blaks.

\param  sort_key - Sort key value
\param  exact_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical PropertyHandle :: LocateKey (Key sort_key, logical exact_w )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  term = ( IsValid() 
           ? Tnodeptr->LocateKey(sort_key,exact_w)
           : YES );
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Variable - Lokate instance by property handle

        When  the property  handle contains  a string  value, the string will be
        converted  into  a  key  for  locating  the  instance. When the property
        handle  refers to a complex instance of the  same type or a base type of
        the  current type in the property handle, the instance key in the passed
        property handle is used for locating the key. 
        When  the  property  handle  contains  a  numeric  value, no instance is
        located.

\param  prop_hdl - Property Handle
\param  exact_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical PropertyHandle :: LocateKey (PropertyHandle &prop_hdl, logical exact_w )
{
  Key             key;
  if ( (key = GetKeyFromParm(prop_hdl)).GetData() )
    return ( LocateKey(key,exact_w) );
  else
    return(YES);


}

/******************************************************************************/
/**
\brief  LocatePath - Locate path for path collection handle

        The  function  ensures  that  all  property  handles  in a hierarchy are
        positioned,  i.e. an instance is selected for all upper property handles
        and  the calling handle itself. If no instance is selected in any handle
        in  the hierarchy the  function automatically tries  to locate the first
        instance for those property handles.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocatePath"

logical PropertyHandle :: LocatePath ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  term = ( IsValid() 
           ? Tnodeptr->LocatePath()
           : YES );
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Lock - Lock instance

        This  function  allows  locking  the  selected  instance of the property
        handle  within  the  application.  As  long as the instance is locked no
        other  user is  able to  access the  instance. Instances for shared base
        structures  are not  automatically included  in the  locking and must be
        locked  separately. Locked instances can  be unlocked using the Unlock()
        function.  They  are  automatically  unlocked,  when another instance is
        selected in the property handle. 
        The  function returns NO when the instance has been locked successfully.
        It  returns  en  error  (YES)  when  the  instance  is already locked by
        another  application,  when  no  instance  is  selected  in the property
        handle or when an error occurred.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical PropertyHandle :: Lock ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsPositioned() )
    term = Tnodeptr->Lock();

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  LockSet - Lock collection

        This  function  allows  locking  a  collection  handle  referenced  in a
        collection  property  handle  within  the  application.  As  long as the
        collection  is locked  no other  user is  able to access the collection.
        Locked  collection can  be unlocked  using the UnlockSet() function. The
        collection  is  automatically  unlocked,  when  the  property  handle is
        closed or another instance is selected in the upper property handle. 
        The   function   returns   NO   when   the   collection  has been locked
        successfully.  It returns en error (YES)  when the collection is already
        locked  by  another  application,  when  no  instance is selected in the
        upper property handle (when existing) or when an error occurred.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockSet"

logical PropertyHandle :: LockSet ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( !ValidateNode(NO) )
    term = Tnodeptr->LockSet();

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  MarkUnused - Mark property handle as unused

        When  referring a property  handle recursively this  may result in never
        deleting  the  resources  allocated  with the property handle. Recursive
        references  to  property  handles  may  happen  when  setting  transient
        references  (SetTransientProperty())  to  an  upper  property handle. In
        this  case  the  programm  has  to  mark  the property handle as unused.
        Property  handles marked as  unused must be  marked as used before being
        closed or replaced (CopyHandle()).
        Using  this  function  improperly  (e.g.  after  constructing a property
        handle)  may  release  the  resources  allocated  to the property handle
        immediately.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MarkUnused"

void PropertyHandle :: MarkUnused ( )
{

  if ( IsValid(NO) && Tnodeptr )
    Tnodeptr->Release((ObjectReferenceHandle *)this);


}

/******************************************************************************/
/**
\brief  MarkUsed - Mark property handle as used

        A  property  handle  should  be  marked  as  used before being closed or
        replaced in a recursive reference.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MarkUsed"

void PropertyHandle :: MarkUsed ( )
{

  if ( IsValid(NO) && Tnodeptr )
    Tnodeptr->Reserve((ObjectReferenceHandle *)this);


}

/******************************************************************************/
/**
\brief  Minus - Substract collections

        The  result collection  contains all  instances that  exist in the first
        but  not in the second operand  collection. The existence of an instance
        in  a collection can be  checked based on the  sort key (passing YES for
        ik_opt)  or  on  local  identities  (LOID).  Using  the LOID is save but
        comparing  the key is  much faster. Hence,  the key check should be used
        whenever possible. 
        Calling   the   function   with   one   operator  creates the difference
        collcetion   between   the   calling   (first   operand)  and the passed
        collection and stores the result in the calling collection. 
        Otherwise  the operation is performed with the passed operand collectios
        storing  the result in the collection referenced by the calling property
        handle.  When  the  calling  property  handle  refers  to  a  non  empty
        collection  all instances  are removed  before performing the operation.
        When  the  calling  property  handle  is  empty  the  function creates a
        temporary extend for storing the result.

\return result_ref - Result property hadle
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_hdl1 - First Property handle
\param  prop_hdl2 - Second Property handle
\param  sk_opt - Sort key option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Minus"

PropertyHandle &PropertyHandle :: Minus (PropertyHandle &prop_hdl1, PropertyHandle &prop_hdl2, char sk_opt )
{
  ACObject    *obh;
  PropertyHandle   *ph_list[] = {&prop_hdl1,&prop_hdl2};
BEGINSEQ
  if ( !this || (nodeptr && !nodeptr->IsValid()) 
             || (nodeptr && Tnodeptr && !Tnodeptr->IsValid()) ) 
                                                     ERROR
  if ( CreatePIHandle(ph_list,2,UNDEF,sk_opt) )      ERROR
  
  obh = StartRTA();
  Tnodeptr->Minus(prop_hdl1.Tnodeptr,prop_hdl2.Tnodeptr,sk_opt);
  obh->StopReadTA(NO);

RECOVER

ENDSEQ
  return(*this);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  prophdl_ref - Reference to Property handle
\param  sk_opt - Sort key option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Minus"

PropertyHandle &PropertyHandle :: Minus (PropertyHandle &prophdl_ref, char sk_opt )
{
  ACObject    *obh = StartRTA();


BEGINSEQ
  if ( ValidateNode(YES) || prophdl_ref.ValidateNode(YES) )
                                                     ERROR
  Tnodeptr->Minus(prophdl_ref.Tnodeptr,sk_opt);
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Modify - Mark property as modified

        The  function  marks  the  instance  selected  in the property handle as
        modified.  This is usually done automatically  when assigning a value to
        a  property handle. When, however, writing data directly to the instance
        the  Modify()  function  must  be  called  to register the modification.
        Otherwise the modification will not be stored to the database. 
        The  function returns NO when executed successfully. When no instance is
        selected or in case of an error the function returns an error (YES).

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

logical PropertyHandle :: Modify ( )
{

  return ( IsValid() 
           ? !Tnodeptr->Modify()
           : YES );

}

/******************************************************************************/
/**
\brief  Move - Move instance to another collection

        The   function   moves   an   instance   from   the   source  collection
        (source_handle)  to the collection of  the current property handle. This
        is  the  only  way,  to  move  dependent  or  owned  instances  from one
        collection  to  another  one.  It  is  also a save way to copy instances
        avoiding  duplicate  key  problems,  that  may  result  from the inverse
        reference  for  local  collections.  The  function  allows  also  moving
        instances between distinct sub-collections of an extent. 
        When  the type of source and target  instance is the same and when both,
        source  and  target  property  handle  have  been  opened  for  the same
        database  handle, the instance is removed from the source collection and
        inserted  into the target collection. In this case the instance does not
        change  the local and global identity. When the two collection differ in
        type,  the instance is  copied from the  source to the target collection
        and removed/deleted from the source collection afterwards.
        When   replacing   existing   instances   is   required  the instance is
        identified  in the target collection by  key according to the sort order
        set  for the target collection.  When a unique sort  order is set and an
        instance  with the same  key as the  source instance does already exist,
        the  instance  is  removed/deleted  from  the  target  collection before
        moving the source instance to the target collection.
        The  function returns an instance handle to the instance selected in the
        property  handle  (instance  moved).  The  function  returns  an  empty 
        instance handle, when the it terminates with error.

\return instance - Instance area
-------------------------------------------------------------------------------
\brief  i00 - Move without rename

        The  function  moves  the  instance  without renaming. When the instance
        exists in the target collection the function returns an error.

\param  source_handle - Source property handle
\param  replopt - Replace option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

Instance PropertyHandle :: Move (PropertyHandle &source_handle, PIREPL replopt )
{

  return ( Move(source_handle,Key(),replopt) );

}

/******************************************************************************/
/**
\brief  i01 - Move with rename

        The  function allows renaming an instance  while moving it to the target
        collection.  When  the  new  key  does  already  exist  in  the  target 
        collection the instance is overwritten depending on the replace option.

\param  source_handle - Source property handle
\param  new_key - New key for the instance
\param  replopt - Replace option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

Instance PropertyHandle :: Move (PropertyHandle &source_handle, Key new_key, PIREPL replopt )
{
  ACObject    *obh = StartRTA();
  Instance     ph_inst;
  if ( !ValidateNode(YES) && source_handle.IsPositioned() )
    if ( Tnodeptr->Move(source_handle.Tnodeptr,replopt,
                            new_key.GetData(),YES) )
       ph_inst = Tnodeptr->GetArea();

  obh->StopReadTA(NO);
  return(ph_inst);
}

/******************************************************************************/
/**
\brief  MoveDown - Move instance down

        In  an unordered  collection or  in a  collection ordered by __AUTOIDENT
        the  position  of  an  instance  can  be  moved  up  or down. Moving the
        instance  down in an unordered position  will change the position of the
        instance,  only. Mowing  it down  in a  collction ordered by __AUTOIDENT
        will update the identifying number of the instance.
        The  function will  not change  the position  for instances in any other
        type of collection.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveDown"

logical PropertyHandle :: MoveDown ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( !ValidateNode(YES) )
    term = Tnodeptr->MoveDown();

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  MoveUp - Move instance one position up

        In  an unordered  collection or  in a  collection ordered by __AUTOIDENT
        the  position  of  an  instance  can  be  moved  up  or down. Moving the
        instance  up in  an unordered  position will  change the position of the
        instance,  only. Mowing it up in a collction ordered by __AUTOIDENT will
        update the identifying number of the instance.
        The  function will  not change  the position  for instances in any other
        type of collection.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveUp"

logical PropertyHandle :: MoveUp ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( !ValidateNode(YES) )
    term = Tnodeptr->MoveUp();

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  NextKey - Locate next key

        The  function  tries  to  locate  the next key according to the selected
        order  starting from  the selected  or located  instance. When passing a
        key  the instance with this  key or the next  lower (if not existing) is
        the  starting point. The  function locates the  key next to the starting
        point.  The function returns the next key located or an empty Key handle
        in  case  of  an  error.  When calling the function for indexes allowing
        duplicate key values, NextKey returns also duplicates. 
        The  instance is located but not selected in the property handle. It cen
        be  selected  calling  Get(CUR_INSTANCE)  after calling NextKey(). Since
        the  function is  not reading  instances but  parsing the index only, it
        provides  fast access to the keys of a collection. For PropertyHandle of
        type VOID the function always terminates with error.
        Passing  a  switch_level  allows  defining  the last key components that
        must  alter. This allows  e.g. reading all  instances for key duplicates
        when fixing the lats key component.

\return skey - Sort key

\param  sort_key_w - Sort key value
\param  switch_level - Number of fixed key component
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextKey"

Key PropertyHandle :: NextKey (Key sort_key_w, int16 switch_level )
{
  ACObject    *obh = StartRTA();
  Key          key;
  if ( !ValidateNode(NO) )
    key = Tnodeptr->NextKey(sort_key_w,switch_level);

  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  NoWrite - Is instance write protected?

        The  function  returns  whether  the  instan  can be updated (NO) or not
        (YES). 
        (-> IsWrite())

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NoWrite"

logical PropertyHandle :: NoWrite ( )
{

  return ( !IsWrite() );

}

/******************************************************************************/
/**
\brief  Open - Open property handle

        Open  property  handle  opens  a  property  handle  for  a persistent or
        transient  data source. A  data source is  a collection, object instance
        or  an elementary database field. A data  source contains the data for a
        property  of a specific object. Usually property handles are opened when
        constructimg  them. You can, hawever, create an unopened property handle
        using  the dummy constructor (without  parameters) or by closing another
        property handle. 
        If  the property handle to be opened is a subsequent property handle the
        parend  must  be  opened.  The  datasource  provided  in  the subsequent
        property  handle  depends  on  the  parents  property  handle  current 
        selection  and  will  be  provided  automatically  whenever  the  parent
        property handle changes its current selection.
        You  can open static property handles  for constants or other elementary
        data  sources  as  well  as  for  structured  instances  or  transient 
        collections using the appropriate open function.
        When  applying the  Open() function  to a  property handle that has been
        opened  previously  the  handle  is closes implicitely before reopening.
        You  cannot  reopen  property  handles  that  have  been  provided  with
        GetPropertyHandle(). 
        When  creating a copy handle sort order and selected instance are set in
        the copy handle as well.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  A00 - Open an undefined property handle

        The  function  opens  an  undefined  and unbound property handle. Before
        using the property handle definition and instance area must be set.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open ( )
{

BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  nodeptr = new node();
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  BigInt - 



\param  int64_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (int64 int64_val )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(int64_val)) )            SDBERR(95)
                                                     SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Boolean - Open property handle for a logical value

        The  function  opens  an  unbound  property  handle  for a logical value
        (LOGICAL).

\param  logval - Logical value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (logical logval )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(logval)) )               SDBERR(95)
                                                     SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Child - Open subordinated property handle

        The  function  openes  a  subordinated  property handle of the instance.
        Since  the  property  handlels  for  instance properties are part of the
        instance  the  function  creates  a  copy  handle with an own cursor. It
        behaves,  however,  like  a  normal  subordinated  property handle, that
        depends  on  the  selection  in  the  upper property handle (if there is
        any).

\param  prop_hdl - Property Handle
\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (PropertyHandle &prop_hdl, char *prop_path )
{
  ACObject    *obh  = NULL;
  logical      term = NO;
BEGINSEQ
statistics2.Start();
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  obh = prop_hdl.StartRTA();
  if ( OpenAccessPath(prop_hdl,prop_path,NULL,YES) )  ERROR
  
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
statistics2.Stop();
  return(term);
}

/******************************************************************************/
/**
\brief  ChildReference - Open subordinated property handle

        The  constructor  provides  a  subordinated  property  handle  of  the 
        instance.  Since  property  handlels  for  an  instance  are part of the
        instance  the function provides  a property handle  that shares area and
        cursor  with  the  property  handle  in  the  instance.  As subordinated
        property  handle  it  depends  on  the  selection  in the upper property
        handle (if there is any).

\param  property_handle - Pointer to a property handle
\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (PropertyHandle *property_handle, char *prop_path )
{
  ACObject    *obh  = NULL;
  logical      term = NO;
BEGINSEQ
statistics2.Start();
  if ( !this )                                       SDBERR(9) 
  if ( nodeptr )
    Close();
  
  obh = property_handle->StartRTA();
  if ( OpenAccessPath(*property_handle,prop_path,NULL,NO) )
                                                     ERROR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
statistics2.Stop();
  return(term);
}

/******************************************************************************/
/**
\brief  Copy - Open non sharing copy for a property handle

        The  function  opens  a  copy  of the passed property handle with an own
        cursor and an own instance area.

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh  = NULL;
  logical      term = NO;
BEGINSEQ
statistics2.Start();
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
    
  if ( !cprop_hdl.IsValid(NO) )                       ERROR
  
  obh = cprop_hdl.StartRTA();
  ((PropertyHandle *)&cprop_hdl)->GetObjectHandle().ResetError();
     
  nodeptr = cprop_hdl.get_nodeptr()->CreateCopy();
  nodeptr->SetPIRef(this);     

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
statistics2.Stop();
  return(term);
}

/******************************************************************************/
/**
\brief  Date - Open property handle for a date value

        The function opens an unbound property handle for a date value (DATE).

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (dbdt date_val )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(date_val)) )             SDBERR(95)
                                                     SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Extent - Open extent property handle

        The  function opens a property handle  for a global collection (extent).
        The  extent  name  passed  may  contain  symbolic  references  to system
        variables  (e.g. "%EXT_PREF%Pers")  which are  resolved according to the
        current  setting of the  referenced system variables.  A key name can be
        passed  to  set  the  sort  order  for the property handle. If no key is
        passed the sort order is set to the default order. 
        You  may open a  transient extent that  stores data only in main storage
        by passing the transient_w option.

\param  object_handle - Database Object handle
\param  extnames - Extent name
\param  accopt - Access option
\param  transient_w - Transient option
\param  key_name_w - Key name for conversion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DBObjectHandle &object_handle, char *extnames, PIACC accopt, logical transient_w, char *key_name_w )
{
  ACObject         *obh       = NULL;
  DBExtend         *dbext     = NULL;
  DBStructDef      *strdef    = NULL;
  DictionaryHandle &dictptr   = object_handle.GetDictionary();
  char              ext_names[4096];
  NodeTypes         node_type = NT_undefined;
  logical           overload  = NO;
  logical           extadd    = NO;
  logical           term      = NO;
BEGINSEQ
statistics2.Start();
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
    
  if ( !object_handle.IsValid() )                    ERROR
  (obh = object_handle.get_obhandle())->StartReadTA();
  object_handle.ResetError();
    
  if ( !extnames )                                   SDBERR(68)
  
  if ( strlen(extnames) > sizeof(ext_names)-1 )      SDBERR(99)
  gvtxbts(ext_names,extnames,sizeof(ext_names)-1);
  ReplaceSysVariable(ext_names,sizeof(ext_names)-1);
  if ( !strcmp(ext_names,"__LOID") )
    strcpy(ext_names,"VOID");
  object_handle->SetErrorVariables(ext_names);
  
  if ( transient_w )
  {
    node_type = NT_ACTransient;
    accopt = PI_Write;
    
    if ( !(strdef = GetDictionary()->GetStructDef(ext_names)) )
                                                     ERROR
    if ( !(nodeptr = new ACTransient(object_handle.get_obhandle(),strdef,key_name_w)) )
                                                     SDBERR(95)
                                                     SDBCERR
    LEAVESEQ    
  }
  
  if ( OpenAccessPath(object_handle,ext_names,NULL,accopt) ) 
                                                     ERROR
  nodeptr->SetPIRef(this);
RECOVER
  Close();
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
statistics2.Stop();
  return(term);

}

/******************************************************************************/
/**
\brief  Float - Open property handle for a double value

        The  function  opens  an  unbound  property  handle  for  a double value
        (REAL).

\param  dbl_value - Double value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (double dbl_value )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(dbl_value)) )            SDBERR(95)
                                                     SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Integer - Open property handle for a 32-bit integer value

        The   function   opens   an   unbound   property   handle for a platform
        independent 32-bit integer value (int32).

\param  int_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (int32 int_val )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(int_val)) )              SDBERR(95)
                                                     SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reference - Open a sharing copy for a property handle

        The  function opens a copy of the passed property handle that shares the
        instance area and cursor with its origin.

\param  property_handle - Pointer to a property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (PropertyHandle *property_handle )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  
  if ( property_handle )
    property_handle->GetObjectHandle().ResetError();
  
  if ( CopyHandle(property_handle) )                 ERROR
  
  if ( !property_handle )                            LEAVESEQ
    
  if ( !property_handle->get_nodeptr() )             ERROR
    
  if ( !property_handle->get_nodeptr()->get_use_count() ) // referenced node is going to be destructed
    nodeptr->ResetUseCount();


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SizedString - Open property handle for a string value

        The  function  opens  an  unbound  property  handle  for  a string value
        (STRING). The area is set to the string pointer passed to the function.

\param  string - String area
\param  string_len - String length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (char *string, int32 string_len )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(string,string_len)) )    SDBERR(95)
                                                     SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  String - Open property handle for a string value

        The  function  opens  an  unbound  property  handle  for  a string value
        (STRING).  The area is  allocated with the  size of the string passed to
        the  constructor. The string  is copied into  the instance area owned by
        the  property handle. To enable dynamical resize featur for the property
        handle use the SetDynLength() function.

\param  string - String area
\param  conv_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (char *string, logical conv_opt )
{
  char                   *str  = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( conv_opt )
    if ( str = ReplaceControlSequences(string,UNDEF,YES) )
      string = str;
    
  if ( !(nodeptr = new node(string)) )               SDBERR(95)
                                                     SDBCERR
RECOVER
  term = YES;
ENDSEQ
  if ( str )
    free(str);
  return(term);
}

/******************************************************************************/
/**
\brief  Time - OPen property handle for a time value

        The function opens an unbound property handle for a time value (TIME).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (dbtm time_val )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(time_val)) )             SDBERR(95)
                                                     SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Timestamp - Open property handle for a date/time value

        The  function  opens  an  unbound  property handle for a date/time value
        (DATETIME).

\param  datetime_val - Date-Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (dttm datetime_val )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(datetime_val)) )         SDBERR(95)
                                                     SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  d3 - 



\param  prop_hdl - Property Handle
\param  parm_data - 
\param  open_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (PropertyHandle &prop_hdl, BNFData *parm_data, logical open_opt )
{
  ACObject    *obh  = NULL;
  logical      term = NO;
BEGINSEQ
statistics2.Start();
  if ( !this )                                       SDBERR(9) 
  if ( nodeptr )
    Close();
  
  obh = prop_hdl.StartRTA();
  if ( OpenAccessPath(prop_hdl,parm_data,NULL,open_opt) ) 
                                                     ERROR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
statistics2.Stop();
  return(term);
}

/******************************************************************************/
/**
\brief  d5 - Open property handle for temporary extent

        The  function opens a property handle for a temporary extent for storing
        results  of set operations.  Temporary extents are  stored in a separate
        temporary file and are available only as long as the process runs.

\param  object_handle - Database Object handle
\param  strnames - Structure name
\param  keyname - Name of sort key
\param  baseexts_w - Name for base extent
\param  weak_opt_w - Weak-typed option
\param  own_opt_w - Owning collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DBObjectHandle &object_handle, char *strnames, char *keyname, char *baseexts_w, logical weak_opt_w, logical own_opt_w )
{
  ACObject *obh     = NULL;
  char     *extname = NULL;
  char      extnames[ID_SIZE+1];
  logical   term    = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !object_handle.IsValid() )                    ERROR
  (obh = object_handle.get_obhandle())->StartReadTA();
  object_handle.ResetError();
    
  if ( !(extname = object_handle.GetDictionary().CreateTempExtent(strnames,NULL,keyname,baseexts_w,weak_opt_w,own_opt_w)) )
                                                     ERROR
  gvtxbts(extnames,extname,ID_SIZE);
  if ( Open(object_handle,extnames,PI_Write) )       ERROR

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  d6 - 



\param  object_handle - Database Object handle
\param  parm_data - 
\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DBObjectHandle &object_handle, BNFData *parm_data, PIACC accopt )
{
  ACObject    *obh  = NULL;
  logical      term = NO;
BEGINSEQ
statistics2.Start();
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
    
  if ( !object_handle.IsValid() )                    ERROR
  (obh = object_handle.get_obhandle())->StartReadTA();
  object_handle.ResetError();
  
  if ( OpenAccessPath(object_handle,parm_data,NULL,accopt) ) 
                                                     ERROR
  nodeptr->SetPIRef(this);
    


RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
statistics2.Stop();
  return(term);
}

/******************************************************************************/
/**
\brief  d9 - Open operation property handle

        Operation  property  handles  can  be  opened  in  order to define a set
        operation  as sub-ordinated property  handle. Operation property handles
        can  be  used  within  path  properties  acting  like  a normal property
        handle,  except that one  cannot create new  instances. Depending to the
        operation  type  operation  property  handle  pass  instance by instance
        (e.g.  where) or do calculate the complete result set before passing the
        first instance.

\param  prop_hdl - Property Handle
\param  op_code - 
\param  rule - OPeration rule
\param  operenv_w - 
\param  access_mode - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (PropertyHandle &prop_hdl, ST_OpCodes op_code, char *rule, OperEnvironment *operenv_w, PIACC access_mode )
{
  ACObject   *obh    = NULL;
  node       *nodptr = prop_hdl.GetNode();
  logical     term   = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9) 
  if ( nodeptr )
    Close();
  
  if ( !prop_hdl.IsValid() )                         ERROR
  obh = prop_hdl.StartRTA();
  prop_hdl.GetObjectHandle().ResetError();
  
  if ( !(nodeptr = node::CreateOperationNode(NULL,nodptr,op_code,rule,operenv_w,access_mode)) )
                                                     ERROR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  d9a - Open operation property handle (top)

        Operation  property  handles  can  be  opened  in  order to define a set
        operation.  As  top-handle,  the  number  of  setoperations, that can be
        defind,  is limited to FROM (product). Operation property handles can be
        used  within path properties  acting like a  normal property handle. The
        top  operation property  handle passes  instance by instance on request.
        Sequential forward access is the most efficient one.

\param  object_handle - Database Object handle
\param  op_code - 
\param  rule - OPeration rule
\param  operenv_w - 
\param  access_mode - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DBObjectHandle &object_handle, ST_OpCodes op_code, char *rule, OperEnvironment *operenv_w, PIACC access_mode )
{
  ACObject     *obh  = NULL;
  logical       term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9) 
  if ( nodeptr )
    Close();
  
  if ( !object_handle.IsValid() )                    ERROR
  (obh = object_handle.get_obhandle())->StartReadTA();
  object_handle.ResetError();
  
  if ( !(nodeptr = node::CreateOperationNode(obh,NULL,op_code,rule,operenv_w,access_mode)) )
                                                     ERROR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  d9b - 



\param  prop_hdl - Property Handle
\param  op_code - 
\param  parm_data - 
\param  operenv_w - 
\param  access_mode - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (PropertyHandle &prop_hdl, ST_OpCodes op_code, BNFData *parm_data, OperEnvironment *operenv_w, PIACC access_mode )
{
  ACObject     *obh    = NULL;
  node         *nodptr = prop_hdl.GetNode();
  logical       term   = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9) 
  if ( nodeptr )
    Close();
  
  if ( !prop_hdl.IsValid() )                         ERROR
  obh = prop_hdl.StartRTA();
  prop_hdl.GetObjectHandle().ResetError();
  
  if ( !(nodeptr = node::CreateOperationNode(NULL,nodptr,op_code,parm_data,operenv_w,access_mode)) )
                                                     ERROR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  d9c - 



\param  object_handle - Database Object handle
\param  op_code - 
\param  parm_data - 
\param  operenv_w - 
\param  access_mode - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DBObjectHandle &object_handle, ST_OpCodes op_code, BNFData *parm_data, OperEnvironment *operenv_w, PIACC access_mode )
{
  ACObject             *obh  = NULL;
  logical               term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9) 
  if ( nodeptr )
    Close();
  
  if ( !object_handle.IsValid() )                    ERROR
  (obh  = object_handle.get_obhandle())->StartReadTA();
  object_handle.ResetError();
  
  if ( !(nodeptr = node::CreateOperationNode(obh,NULL,op_code,parm_data,operenv_w,access_mode)) )
                                                     ERROR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - Open subordinated property handle

        The  function opens a  subordinated property handle  for an unbound data
        instance  (a data instance  that is not  connected to the database). The
        property  handle has no connection to  the database and does not support
        database access functions. 
        The  data area is the  data area of the  property in the instance passed
        to  the function. If  no instance is  passed, no data area is allocated.
        This can be done later using the SetInstance() function.

\param  struct_def - Pointer to generel structure definition
\param  prop_names - Property name
\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DBStructDef *struct_def, char *prop_names, Instance instance )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(struct_def,prop_names,instance.GetData())) )
                                                     SDBERR(95)
                                                     SDBCERR
  nodeptr->SetPIRef(this);  
  ValidateNode(NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i11 - Open an unbound property handle

        The  function opens  an unbound  property handle  according to the field
        definition  (field_def) passed to the  constructor. An initial value can
        be  passed as string value to initialize the data area allocated for the
        property handle.

\param  dictptr - Dictionary handle
\param  field_def - Property definition
\param  init_string - Initial value
\param  init_opt - Initialize option
\param  const_opt - Constant Option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DictionaryHandle &dictptr, DBFieldDef *field_def, char *init_string, logical init_opt, logical const_opt )
{
  Dictionary  *dictionary = dictptr.get_dictionary();
  logical      term       = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  if ( !dictionary )                                 SDBERR(520)
  
  if ( !(nodeptr = new node(dictionary,field_def,
                            init_string,init_opt,const_opt)) )
                                                     SDBERR(95)
                                                     SDBCERR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i12 - Open an unbound property handle

        The  function  opens  an  unbound  property handle according to the type
        passed  in  typenames  and  the  properties  passsed to the function. An
        initial  value can be passed as string value to initialize the data area
        allocated for the property handle.

\param  dictptr - Dictionary handle
\param  prop_names - Property name
\param  typenames - Type name
\param  ref_level - Reference level
\param  size - Size
\param  precision - Precision
\param  dimension - Dimension
\param  init_string - Initial value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DictionaryHandle &dictptr, char *prop_names, char *typenames, SDB_RLEV ref_level, uint32 size, uint16 precision, uint32 dimension, char *init_string )
{
  Dictionary  *dictionary = dictptr.get_dictionary();
  logical      term       = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  if ( !dictionary )                                 SDBERR(520)
  
  TypeKey   tkey(dictionary,typenames);
  if ( !(nodeptr = new node(dictionary,prop_names,
                            tkey.Name(),tkey.GetID(),ref_level,size,precision,
                            dimension,init_string)) )
                                                     SDBERR(95)
                                                     SDBCERR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i13 - Open an unbound property handle with type name

        The  function  opens  an  unbound  property handle according to the type
        passed in typenames.

\param  dictptr - Dictionary handle
\param  typenames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DictionaryHandle &dictptr, char *typenames )
{
  Dictionary  *dictionary = dictptr.get_dictionary();
  logical      term       = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  if ( !dictionary )                                 SDBERR(520)
  
  if ( !(nodeptr = new node(dictionary,typenames)) ) SDBERR(95)
                                                     SDBCERR
  nodeptr->SetPIRef(this);   

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i20 - Open an unbound property handle with structure definition

        The  function  opens  an  unbound  property  handle  for an unbound data
        instance  (a data instance  that is not  connected to the database). The
        property  handle has no connection to  the database and does not support
        database access functions. 
        The  instance passed to the function  (instance) is set as instance area
        for  the property handle, i.e. the handle  shares the data area with the
        application.

\param  strdef - Structure definition
\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DBStructDef *strdef, Instance instance )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !(nodeptr = new node(strdef,&instance)) )     SDBERR(95)
                                                     SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i21 - Open an unbound property handle

        The  function opens  an unbound  property handle  according to the field
        definition  (field_def) passed to the  constructor. An initial value can
        be  passed according  to the  type of  the property handle to initialize
        the data area allocated for the property handle.

\param  field_def - Property definition
\param  initinst - Initializing instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical PropertyHandle :: Open (DBFieldDef *field_def, Instance initinst )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  nodeptr = field_def->get_by_reference()
            ? new ACTransientReference(NULL,field_def,NULL,PI_undefined)
            : new node(field_def,&initinst);
                                                     SDBCERR
  nodeptr->SetPIRef(this);   
  ValidateNode(NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenAccessPath - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 



\param  prop_hdl - Property Handle
\param  path_prop - 
\param  operenv - 
\param  open_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenAccessPath"

logical PropertyHandle :: OpenAccessPath (PropertyHandle &prop_hdl, char *path_prop, OperEnvironment *operenv, logical open_opt )
{
  DictionaryHandle   &dictptr    = prop_hdl.GetDictionary();
  PropertyHandle     *ph_ptr;
  BNFData            *bnf_data   = NULL;
  char               *expression = NULL;
  node               *npt;
  logical             subnode;
  logical             term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
    
  if ( !prop_hdl.IsValid() )                         ERROR
  prop_hdl.GetObjectHandle().ResetError();
  if ( !path_prop || !*path_prop )                   SDBERR(109)
  prop_hdl.GetNode()->GetObjectHandle()->SetErrorVariables(path_prop);
  
  if ( !dictptr )
  {
    if ( !(ph_ptr = prop_hdl.GetPropertyHandle(path_prop)) )
                                                     ERROR
    CopyHandle(ph_ptr);
    subnode = YES;
  }
  else
  {
    npt = prop_hdl.GetNode();
    if ( *path_prop == '.' )
    {
      while ( *(++path_prop) == '.' )
      {
        npt = *npt->GetHighPIPointer();
        if ( !npt || !npt->IsValid() )               ERROR
      }
    }
    
    if ( !(bnf_data = dictptr->ParseExpression(path_prop,"simple_op",&expression)) )
                                                     ERROR
    if ( OpenAccessPath(npt,bnf_data,operenv,open_opt) )     ERROR
    if ( !nodeptr )                                  ERROR
    
    if ( nodeptr->get_nodetype() != NT_ACOPView )
    {
      delete bnf_data;
      free(expression);
    }
//    else
//      ((ACPath *)nodeptr)->set_expression(expression);
  }

RECOVER
  if ( bnf_data )
    delete bnf_data;
  if ( expression )
    free(expression);
  Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_hdl - Property Handle
\param  parm_data - 
\param  operenv - 
\param  open_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenAccessPath"

logical PropertyHandle :: OpenAccessPath (PropertyHandle &prop_hdl, BNFData *parm_data, OperEnvironment *operenv, logical open_opt )
{

  return( OpenAccessPath(prop_hdl.GetNode(),parm_data,operenv,
                         open_opt) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  nodptr - 
\param  parm_data - 
\param  operenv - 
\param  open_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenAccessPath"

logical PropertyHandle :: OpenAccessPath (node *nodptr, BNFData *parm_data, OperEnvironment *operenv, logical open_opt )
{
  ACObject         *obhandle     = nodptr->GetObjectHandle();
  FunctionTypes     path_type    = FT_undefined;
  node            **pnodeptr     = NULL;
  node             *acc_node     = NULL;
  char             *string       = NULL;
  BNFData          *bdata        = NULL;
  logical           is_transient = NO;
  int8              path_opt     = NO;
  logical           term         = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !parm_data )                                  SDBERR(99)
  
  if ( ((BNFExpData *)parm_data)->IsPropertyPath(obhandle,nodptr->GetCurrentTypeDef(),operenv,path_type,path_opt) 
       && (path_type == FT_Property || path_type == FT_MetaAttribute) )  // beginning with property name
  {
    if ( path_opt < 1 ) // Property path: a, a.b 
    {
      if ( pnodeptr = nodptr->GetNodePtr(parm_data->StringValue(),operenv,path_type,nodptr->GetMode()) ) 
      {
        if ( acc_node = *pnodeptr )
        {
          if ( acc_node->stsctrans() )
            nodeptr = acc_node;
          else
          {
            if ( open_opt )
            {
              PropertyHandle  ph(acc_node);
              Open(ph);
            }
            else 
              RegisterNode(acc_node);
          }
        }
      }
    }
    else              // Path property: a().b, a.b[2], a(x>3).c
      nodeptr = nodptr->CreatePathNode(parm_data,operenv);
  }
  else
    nodeptr  = nodptr->CreateAccessPath(parm_data,operenv);
  
  if ( !nodeptr )                                     ERROR
  

RECOVER
  term = YES;
ENDSEQ
  if ( string )
    free(string);
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  object_handle - Database Object handle
\param  path_prop - 
\param  operenv - 
\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenAccessPath"

logical PropertyHandle :: OpenAccessPath (DBObjectHandle &object_handle, char *path_prop, OperEnvironment *operenv, PIACC accopt )
{
  DictionaryHandle   &dictptr    = object_handle.GetDictionary();
  BNFData            *bnf_data   = NULL;
  char               *expression = NULL;
  DBExtend           *dbext;
  logical             term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !object_handle.IsValid() )                    ERROR
  if ( !path_prop || !*path_prop )                   SDBERR(109)
  object_handle->SetErrorVariables(path_prop);
  
  if ( !strcmp(path_prop,"__GUID") )
    path_prop = "__OBJECT";
  else if ( !strcmp(path_prop,"__LOID") )
    path_prop = "VOID";
  
  if ( !dictptr )                                    ERROR
/*
  if ( (dbext = dictptr->ProvideExtendDef(path_prop)) &&  
       dbext->fmcbsmcb                               &&
       dbext->fmcbsmcb->smcbatyp == AT_CODE             )   // enumeration
  {
    if ( !(nodeptr = new CSNode(object_handle.get_object_handle(),path_prop,accopt))) SDBERR(95)
                                                     SDBCERR
  }
  else 
*/
  if ( !(bnf_data = dictptr->ParseExpression(path_prop,"simple_op",&expression)) )
                                                     ERROR
  if ( OpenAccessPath(object_handle,bnf_data,operenv,accopt) )
                                                     ERROR
  if ( nodeptr->get_nodetype() != NT_ACOPView )
  {
    delete bnf_data;
    free(expression);
  }
//  else
//    ((ACPath *)nodeptr)->set_expression(expression);

RECOVER
  delete bnf_data;
  if ( expression )
    free(expression);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i04 - 



\param  object_handle - Database Object handle
\param  parm_data - 
\param  operenv - 
\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenAccessPath"

logical PropertyHandle :: OpenAccessPath (DBObjectHandle &object_handle, BNFData *parm_data, OperEnvironment *operenv, PIACC accopt )
{
  ACObject          *obh      = object_handle.get_obhandle();
  FunctionTypes     path_type = FT_undefined;
  char              *string   = NULL;
  BNFData           *bdata    = NULL;
  int8               path_opt = NO;
  logical            term     = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
  
  if ( !object_handle.IsValid() )                    ERROR
  object_handle->SetErrorVariables(parm_data->StringValue());
  
  if ( parm_data->IsValue("VOID") ) // a
  {
    if ( !(nodeptr = obh->CreateNode(parm_data->StringValue(),accopt)) )
                                                    ERROR
    LEAVESEQ
  }
  // like "a" 
  if ( ((BNFExpData *)parm_data)->IsPropertyPath(obh,NULL,operenv,path_type,path_opt) 
       && (path_type == FT_Extent || path_type == FT_Variable || 
           path_type == FT_Global || path_type == FT_Parameter  ) )
  {
    if ( parm_data->IsSymbol("pname") ) // a
    {
      if ( !(nodeptr = obh->CreateNode(parm_data->StringValue(),accopt)) )
                                                     ERROR
    }
    else
    {
      if ( !object_handle.IsServer() ) // expression and path nodes are sent to server
        nodeptr = obh->CreatePathNode(parm_data->StringValue(),operenv,accopt);     
      // (a,b) or (a.b)
      else if ( bdata = ((BNFExpData *)parm_data)->GetElementaryView() )
      {   
        string = strdup(bdata->StringValue());
//      nodeptr = new ACElmView(obh,NULL,string,accopt);
      }
      // like "a.b" or "a[2].b(0)" but not "a"
      else if ( !path_opt )  // like "a.b" but not "a"
      {
        nodeptr = obh->GetNodePtr(parm_data->StringValue(),operenv,path_type,accopt);
      }
      else         // like "a[2].b(0)" 
        nodeptr = obh->CreatePathNode(parm_data,operenv,accopt);
    }
  }
  
  SDBCERR
  
  if ( !nodeptr )       
  {                 
    nodeptr = new ACPath(obh,NULL,parm_data,operenv,accopt);
    SDBCERR
  }

RECOVER
  delete nodeptr;
  nodeptr = NULL;       
  term    = YES;
ENDSEQ
  if ( string )
    free(string);
  return(term);
}

/******************************************************************************/
/**
\brief  OpenHierarchy - Open hierarchy property handle

        The  function  opens  a  hierarchy  property  handle,  which  creates  a
        property  handle for bottom property handle. The function will duplicate
        the  complete hierarchy including the  top property handle. The function
        copies  the  selectins  from  the  source  hierarchy,  i.e.  the  result
        contains the same selected instance as the source hierarchy. 
        The  function returns a property handle for the collection in the bottom
        property  handle. Upper parent property  handle, which have been created
        by  the function,  will be  destructed automatically when destroying the
        bottom  property handle. When  no top property  handle is passed or when
        the  top  property  handle  is  not  part  of  the source hierarchy, the
        returned  hierarchy ends with the extent  property handle for the bottom
        property handle. 
        You  may  access  upper  property  handles  by referring parent property
        handle  with   the  GetParentProperty()  function. Since all parents are
        copies,  you  may  change  the  selection  in  any parent handle without
        danger. 
        When  passing  true  (YES)  for  path option, the function will turn the
        property  hierarchy into  a path  property, which automatically iterates
        on higher levels.
        When  the  source  handle  is  opened  in  write mode or when any of the
        property  handles in  the hierarchy  are opened  in write mode, the copy
        might  refer to  a write  protected instance.  You can use the Refresh()
        function  to  remove  the  write  protection,  after instances have been
        released in the other hierarchy. 
        The  root for  the hierarchy  it the  top handle of the hierarchy. Since
        this  is  a  copy  handle,  the  complete hierarchy will be closed, when
        closing   the   origin   handle   (or   the   extend node) implicitly or
        explicitly.
        Depending  on  the  copy_selection  option the selection from the source
        path  is copies as well, i.e. the  property handles in the hierarchy are
        positioned to the same instance as in the appropriate source handle.

\return term - Termination code

\param  bottom_ph - Lowest property handle
\param  top_ph - Highest property handle
\param  path_opt - Path oprtion
\param  accmode - Access mode
\param  copy_selection - Copy selection for property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenHierarchy"

logical PropertyHandle :: OpenHierarchy (PropertyHandle *bottom_ph, PropertyHandle *top_ph, logical path_opt, PIACC accmode, logical copy_selection )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(9)
  if ( nodeptr )
    Close();
    
  if ( !bottom_ph->IsValid(NO) )                     ERROR
  bottom_ph->GetObjectHandle().ResetError();
     
  if ( bottom_ph->nodeptr->Check(YES,NO) )           ERROR
  
  if ( !(nodeptr = bottom_ph->nodeptr->PathCreateCopy(top_ph ? top_ph->nodeptr : NULL, accmode, copy_selection)) )
                                                     ERROR
  nodeptr->SetPIRef(this);   // muß nicht registriert werden. 18.9.00, warum? 3.2.01
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OwnsData - Owns data area

        The  function  returns  whether  the  property handle owns its data area
        YES) or whether the area is shared with another property handle (NO).

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OwnsData"

logical PropertyHandle :: OwnsData ( )
{
  ACObject    *obh = StartRTA();
  logical      cond = NO;
  ValidateNode(NO);
  
  if ( IsValid() )
    cond = Tnodeptr->get_flddaloc(); 

  obh->StopReadTA(NO);
  return(cond);
}

/******************************************************************************/
/**
\brief  Position - Select an instance relative to the current selection

        The  function  allow  selecting  an instance relatively to the currently
        selected  instance. Thus the function allows selecting the next instance
        in   the   collection   as   Position(1)   or   the previous instance as
        Position(-1). 
        The  function returns  NO when  the instance  could be selected. When no
        instance  could be selected or an error occurred the function returns an
        error (YES).

\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  count - Number of entries
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical PropertyHandle :: Position (int32 count )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
BEGINSEQ
  if ( ValidateNode(YES) )                           ERROR
  
  if ( !IsAttribute() || IsCollection(NO) )
    term = Tnodeptr->Position(count) == AUTO ? YES : NO;
  else if ( IsNumeric() )  
    *this = (int32)(GetInt()+count);   // for i++ (i.Position(1))
  else                                               ERROR
RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  PositionTop - Position parent collections

        The  function  selectes  an  instance  (first  instance)  for  all upper
        property  handles  that  are  not  positioned.  The  selection  for  the
        property handle itself remains unchanged.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionTop"

logical PropertyHandle :: PositionTop ( )
{
  ACObject        *obh = StartRTA();
  node            *new_node;
  logical          term = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  if ( !Tnodeptr->get_nodenode() )                   LEAVESEQ
  if ( !(new_node = nodeptr->PositionTop_intern()) ) ERROR
  if ( new_node != nodeptr ) 
    RegisterNode(new_node);
  
  if ( !Tnodeptr->get_nodenode()->IsSelected() )     ERROR

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Power - Raise to power of

        The  power  function  is  supported  for numerical data, only. If passed
        property  handle is not numerical the  function tries to convert it into
        a  numerical value.  If no  conversion is  possible the operation fails.
        The  function calculates the value of  the property handle raised to the
        power of the passed value. 
        The   result   is   returned   in   a   property  handle that is created
        temporarily.  You can  assign the  result to  another property handle or
        performing further operations.

\return result_handle - 

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Power"

PropertyHandle PropertyHandle :: Power (PropertyHandle &prop_hdl )
{
  ACObject    *obh = StartRTA();
  PropertyHandle    result_field;
BEGINSEQ
  if ( !ProvideArea() || !prop_hdl.ProvideArea() )   ERROR
  SDBEV5("Power",UNDEF)
  
  switch ( GetDescription(NO)->fmcbityp ) 
  {
    case T_UINT   : 
    case T_INT    : 
    case T_REAL   : DBF_REAL->Power(nodeptr,prop_hdl.get_nodeptr());
                    break;
//  case T_BIT  :
                    break;
    default     :                                    SDBERR(154)
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(result_field.get_nodeptr());
}

/******************************************************************************/
/**
\brief  PropertyHandle - Constructor

        The  property  handle  constructor  creates and openes a property handle
        for  a  persistent  or  transient  data  source.  A  data  source  is  a
        collection,  object  instance  or  an  elementary database field. A data
        source  contains the  data for  a property  of a specific object. Except
        for  the  dummy  constructor  (no  parameter) property handle are opened
        when  being constructed  sucessfully. To  check teh  success you can use
        the IsValid() or Check() function. 
        Cunstructing  a subsequent property handle  (passing the parent property
        handle  and  the  property  name  to the constructor) the parend must be
        opened.  The  datasource  provided  in  the  subsequent  property handle
        depends  on the  parents property  handle current  selection and will be
        provided  automatically whenever the parent  property handle changes its
        current selection.
        You  can  create  static  property  handles  for  constants  or  other 
        elementary  data  sources  as  well  as  for  structured  instances  or 
        transient collections using the appropriate constructur function.

-------------------------------------------------------------------------------
\brief  c1 - Create non sharing copy for a property handle

        The  constructor creates  a copy  of the  passed property handle with an
        own cursor and an own instance area.

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (const PropertyHandle &cprop_hdl )
                     :   nodeptr(NULL)

{

  Open(cprop_hdl);


}

/******************************************************************************/
/**
\brief  c2 - Create a sharing copy for a property handle

        The  constructor  creates  a  copy  of  the  passed property handle that
        shares the instance area and cursor with its origin.

\param  property_handle - Pointer to a property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (PropertyHandle *property_handle )
                     :   nodeptr(NULL)

{

  Open(property_handle);


}

/******************************************************************************/
/**
\brief  d0 - Create copy handle

        The  constructor  creates  a  copy  property handle that shares area and
        cursor with the handle passed as nodeptr.

\param  nodptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (node *nodptr )
                     :   nodeptr(NULL)

{

  RegisterNode(nodptr);

}

/******************************************************************************/
/**
\brief  d1 - Create subordinated property handle

        The  constructor  provides  a  subordinated  property  handle  of  the 
        instance.  Since the property handlels  for instance properties are part
        of  the instance the function creates a  copy handle with an own cursor.
        It  behaves, however,  like a  normal subordinated property handle, that
        depends  on  the  selection  in  the  upper property handle (if there is
        any).

\param  prophdl_ref - Reference to Property handle
\param  prop_names - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (PropertyHandle &prophdl_ref, char *prop_names )
                     :   nodeptr(NULL)

{

  Open(prophdl_ref,prop_names);


}

/******************************************************************************/
/**
\brief  d2 - Create subordinated property handle

        The  constructor  provides  a  subordinated  property  handle  of  the 
        instance.  Since  property  handlels  for  an  instance  are part of the
        instance  the function provides  a property handle  that shares area and
        cursor  with  the  property  handle  in  the  instance.  As subordinated
        property  handle  it  depends  on  the  selection  in the upper property
        handle (if there is any).

\param  property_handle - Pointer to a property handle
\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (PropertyHandle *property_handle, char *prop_path )
                     :   nodeptr(NULL)

{

  Open(property_handle,prop_path);

}

/******************************************************************************/
/**
\brief  d3 - Create extent property handle

        The  constructor  creates  a  property  handle  for  a global collection
        (extent).  The  extent  name  passed  may contain symbolic references to
        system  variables (e.g.  "%EXT_PREF%Pers") which  are resolved according
        to the current setting of the referenced system variables.

\param  object_handle - Database Object handle
\param  extnames - Extent name
\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DBObjectHandle &object_handle, char *extnames, PIACC accopt )
                     :   nodeptr(NULL)

{

  Open(object_handle,extnames,accopt);

}

/******************************************************************************/
/**
\brief  d4 - Create extent property handle

        The  constructor  creates  a  property  handle  for  a global collection
        (extent).  The  extent  name  passed  may contain symbolic references to
        system  variables (e.g.  "%EXT_PREF%Pers") which  are resolved according
        to  the current setting  of the referenced  system variables. A key name
        can  be passed to set the sort order  for the property handle. If no key
        is passed (NULL) the sort order is set to the default order.

\param  object_handle - Database Object handle
\param  extnames - Extent name
\param  keynames - Key name
\param  accopt - Access option
\param  transient_w - Transient option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DBObjectHandle &object_handle, char *extnames, char *keynames, PIACC accopt, logical transient_w )
                     :   nodeptr(NULL)

{

  if ( !Open(object_handle,extnames,accopt,transient_w,keynames) )
    SetOrder(keynames);

}

/******************************************************************************/
/**
\brief  d5 - Create property handle for temporary extent

        The  constructor creates  a property  handle for  a temporary extent for
        storing  results of  set operations.  Temporary extents  are stored in a
        separate  temporary file and  are available only  as long as the process
        runs.

\param  object_handle - Database Object handle
\param  strnames - Structure name
\param  keyname - Name of sort key
\param  baseexts_w - Name for base extent
\param  weak_opt_w - Weak-typed option
\param  own_opt_w - Owning collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DBObjectHandle &object_handle, char *strnames, char *keyname, char *baseexts_w, logical weak_opt_w, logical own_opt_w )
                     :   nodeptr(NULL)

{

  Open(object_handle,strnames,keyname,baseexts_w,weak_opt_w,own_opt_w);


}

/******************************************************************************/
/**
\brief  d9 - Operation Property Handle

        Operation  property  handles  can  be  created  in order to define a set
        operation  as sub-ordinated property  handle. Operation property handles
        can  be  used  within  path  properties  acting  like  a normal property
        handle.  Depending to the operation  type operation property handle pass
        instance  by instance (e.g.  where) or do  calculate the complete result
        set  before passing the first instance. Sequential forward access is the
        most efficient one.

\param  prop_hdl - Property Handle
\param  op_code - 
\param  rule - OPeration rule
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (PropertyHandle &prop_hdl, ST_OpCodes op_code, char *rule )
                     :   nodeptr(NULL)

{

  Open(prop_hdl,op_code,rule);

}

/******************************************************************************/
/**
\brief  d9a - Operation Property Handle

        Operation  property  handles  can  be  created  in order to define a set
        operation.  As  top-handle,  the  number  of  setoperations, that can be
        defind,  is limited to FROM (product). Operation property handles can be
        used  within path properties  acting like a  normal property handle. The
        top  operation property  handle passes  instance by instance on request.
        Sequential forward access is the most efficient one.

\param  object_handle - Database Object handle
\param  op_code - 
\param  rule - OPeration rule
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DBObjectHandle &object_handle, ST_OpCodes op_code, char *rule )
                     :   nodeptr(NULL)

{

  Open(object_handle,op_code,rule);

}

/******************************************************************************/
/**
\brief  d9b - 



\param  prop_hdl - Property Handle
\param  op_code - 
\param  parm_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (PropertyHandle &prop_hdl, ST_OpCodes op_code, BNFData *parm_data )
                     :   nodeptr(NULL)

{

  Open(prop_hdl,op_code,parm_data);

}

/******************************************************************************/
/**
\brief  d9c - 



\param  object_handle - Database Object handle
\param  op_code - 
\param  parm_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DBObjectHandle &object_handle, ST_OpCodes op_code, BNFData *parm_data )
                     :   nodeptr(NULL)

{

  Open(object_handle,op_code,parm_data);

}

/******************************************************************************/
/**
\brief  i01 - Create subordinated property handle

        The  constructor creates  a subordinated  property handle for an unbound
        data  instance (a data instance that  is not connected to the database).
        The  property  handle  has  no  connection  to the database and does not
        support database access functions. 
        The  data area is the  data area of the  property in the instance passed
        to  the function. If  no instance is  passed, no data area is allocated.
        This can be done later using the SetInstance() function.

\param  strdef - Structure definition
\param  prop_names - Property name
\param  instance_w - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DBStructDef *strdef, char *prop_names, Instance instance_w )
                     :   nodeptr(NULL)

{

  Open(strdef,prop_names,instance_w);


}

/******************************************************************************/
/**
\brief  i11 - Create unbound property handle

        The  constructor  creates  an  unbound  property handle according to the
        field  definition  (field_def)  passed  to  the  constructor. An initial
        value  can  be  passed  as  string  value  to  initialize  the data area
        allocated for the property handle.

\param  dictptr - Dictionary handle
\param  field_def - Property definition
\param  init_string - Initial value
\param  init_opt - Initialize option
\param  const_opt - Constant Option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DictionaryHandle &dictptr, DBFieldDef *field_def, char *init_string, logical init_opt, logical const_opt )
                     :   nodeptr(NULL)

{

  Open(dictptr,field_def,init_string,init_opt,const_opt);


}

/******************************************************************************/
/**
\brief  i12 - Create an unbound property handle

        The  constructor  creates  an  unbound  property handle according to the
        type  passed in typenames and the properties passsed to the function. An
        initial  value can be passed as string value to initialize the data area
        allocated for the property handle.

\param  dictptr - Dictionary handle
\param  prop_names - Property name
\param  typenames - Type name
\param  ref_level - Reference level
\param  size - Size
\param  precision - Precision
\param  dimension - Dimension
\param  init_string - Initial value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DictionaryHandle &dictptr, char *prop_names, char *typenames, SDB_RLEV ref_level, uint32 size, uint16 precision, uint32 dimension, char *init_string )
                     :   nodeptr(NULL)

{

  Open(dictptr,prop_names,typenames,ref_level,size,precision,
       dimension,init_string);

}

/******************************************************************************/
/**
\brief  i13 - Create an unbound property handle with type name

        The  constructor  creates  an  unbound  property handle according to the
        type passed in typenames.

\param  dictptr - Dictionary handle
\param  typenames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DictionaryHandle &dictptr, char *typenames )
                     :   nodeptr(NULL)

{

  Open(dictptr,typenames);


}

/******************************************************************************/
/**
\brief  i20 - Create an unbound property handle with structure definition

        The  constructor creates an unbound property  handle for an unbound data
        instance  (a data instance  that is not  connected to the database). The
        property  handle has no connection to  the database and does not support
        database access functions. 
        The  instance passed to the function  (instance) is set as instance area
        for  the property handle, i.e. the handle  shares the data area with the
        application.

\param  strdef - Structure definition
\param  instance_w - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DBStructDef *strdef, Instance instance_w )
                     :   nodeptr(NULL)

{

  Open(strdef,instance_w);


}

/******************************************************************************/
/**
\brief  i21 - Create an unbound property handle

        The  constructor  creates  an  unbound  property handle according to the
        field  definition  (field_def)  passed  to  the  constructor. An initial
        value  can  be  passed  according  to the type of the property handle to
        initialize the data area allocated for the property handle.

\param  field_def - Property definition
\param  initinst - Initializing instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (DBFieldDef *field_def, Instance initinst )
                     :   nodeptr(NULL)

{

  Open(field_def,initinst);


}

/******************************************************************************/
/**
\brief  u1 - Create property handle for an integer value

        The  constructor creates an unbound property handle for an integer value
        (INT).

\param  int_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (int32 int_val )
                     :   nodeptr(NULL)

{

  Open(int_val);

}

/******************************************************************************/
/**
\brief  u2 - Create property handle for a string value

        The  constructor creates an  unbound property handle  for a string value
        (STRING).  The area is  allocated with the  size of the string passed to
        the  constructor. The string  is copied into  the instance area owned by
        the  property handle. To enable dynamical resize featur for the property
        handle use the SetDynLength() function.

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (char *string )
                     :   nodeptr(NULL)

{

  Open(string);


}

/******************************************************************************/
/**
\brief  u3 - Create property handle for a string value

        The  constructor creates an  unbound property handle  for a string value
        (STRING). The area is set to the string pointer passed to the function.

\param  string - String area
\param  string_len - String length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (char *string, int32 string_len )
                     :   nodeptr(NULL)

{

  Open(string,string_len);


}

/******************************************************************************/
/**
\brief  u4 - Create property handle for a double value

        The  constructor creates an  unbound property handle  for a double value
        (REAL).

\param  dbl_value - Double value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (double dbl_value )
                     :   nodeptr(NULL)

{

  Open(dbl_value);



}

/******************************************************************************/
/**
\brief  u5 - Create property handle for a date value

        The  constructor  creates  an  unbound  property handle for a date value
        (DATE).

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (dbdt date_val )
                     :   nodeptr(NULL)

{

  Open(date_val);


}

/******************************************************************************/
/**
\brief  u6 - Create property handle for a time value

        The  constructor  creates  an  unbound  property handle for a time value
        (TIME).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (dbtm time_val )
                     :   nodeptr(NULL)

{

  Open(time_val);


}

/******************************************************************************/
/**
\brief  u7 - Create property handle for a date/time value

        The  constructor  creates  an  unbound  property  handle for a date/time
        value (DATETIME).

\param  datetime_val - Date-Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (dttm datetime_val )
                     :   nodeptr(NULL)

{

  Open(datetime_val);


}

/******************************************************************************/
/**
\brief  u8 - Create property handle for a logical value

        The  constructor creates an unbound property  handle for a logical value
        (LOGICAL).

\param  logval - Logical value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle (logical logval )
                     :   nodeptr(NULL)

{

  Open(logval);


}

/******************************************************************************/
/**
\brief  x1 - Dummy constructor

        The function creates an empty property handle without handle pointer.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyHandle"

     PropertyHandle :: PropertyHandle ( )
                     :   nodeptr(NULL)

{




}

/******************************************************************************/
/**
\brief  ProvGenAttribute - Provide generic attributes for new instance

        When  reading  an  instance  containing  generic  attributes the generic
        attributes  according to the selected type  are provided in the instance
        only  when already  existing, i.e.  reading an  instance will not create
        missing  generic attributes.  To provide  generic attributes in any case
        this  function can be called that creates missing generic attributes for
        the read instance.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvGenAttribute"

logical PropertyHandle :: ProvGenAttribute ( )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
  if ( IsPositioned() )
    term = Tnodeptr->ProvGenAttribute();

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Provide - Provide instance

        The  Provide()  function  allows  selecting  an  instance  in a property
        handle  collection by key or position that must not necessarily exist in
        the  collection. The provide function checks whether the instance exists
        in  the collection (Get()).  If not existing  the instance is created in
        the collection (-> Add()) and selected.

\return instance - Instance area
-------------------------------------------------------------------------------
\brief  A00 - Provide instance by property

        The  function  checks  whether  the  property  handle passes a numerical
        value  or not. When  passing a numerical  value the function provides an
        instance  at the position according to the number passed in the property
        handle  (->  "Provide  instance  at position"). When the property handle
        contains  text data, the value in  the property handle is interpreted as
        string  key, which will  be converted into  key and provides an instance
        by key value (-> "Provide instance by key value").
        When  the property handle refers to a  complex instance of the same type
        or  a base type of the current type in the property handle, the instance
        key in the passed property handle is used for locating the key.

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

Instance PropertyHandle :: Provide (PropertyHandle &prop_hdl )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  Key          key;
  if ( (key = GetKeyFromParm(prop_hdl)).GetData() )
    instance = Provide(key);
  else if ( prop_hdl.IsNumeric() )  
    instance = Provide(prop_hdl.GetInt());


  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  AtPosition - Provide instance at position

        The  function tries to  provide an instance  at a certain position. When
        no  instance  exist  at  the  location passed in set_pos_w, the function
        creates  an  instance  by  position  (->  Add():  "Create  Instance  at 
        position").

\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

Instance PropertyHandle :: Provide (int32 set_pos0_w )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->Provide(set_pos0_w);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  ByKey - Provide intsance by key value

        The  function tries to provide an instance  with the passed sort key (or
        ident-key  for unordered  collections). When  no instance exist with the
        key  passed in sort_key,  the function creates  an instance by key value
        (-> Add(): "Add Instance by key value").

\param  sort_key - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

Instance PropertyHandle :: Provide (Key sort_key )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->Provide(sort_key.GetData()); 

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  i03 - Provide instance by character key

        This  function  is  supported  because  of  compatibility  reasons  and 
        operates as the "Provide instance by key value" function.

\param  charkey - Key area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

Instance PropertyHandle :: Provide (char *charkey )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->Provide(charkey); 

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  i2 - Provide intsance by instance

        The  function  extracts  the  sort  key (for ordered collections) or the
        ident-key  (for unordered collections) and  tries to locate the instance
        in  the collection with  the extracted key  value. When no such instance
        exists  the function adds an instance  to the collection (-> Add(): "Add
        instance").

\param  initinst - Initializing instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

Instance PropertyHandle :: Provide (Instance initinst )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->Provide(initinst.GetData());

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  ProvideArea - Provide instance area

        The  function  provides  the  instance  area  for  a  selected  property
        instance.  When no instance is selected  in the upper property handle or
        when  no  instance  is  selected  in  a  collection  handle the function
        returns an empty instance.

\return instance - Instance area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideArea"

Instance PropertyHandle :: ProvideArea ( ) const
{
  ACObject    *obh = StartRTA();
  void        *datarea = NULL;
BEGINSEQ
  if ( ValidateNode(YES) )                          ERROR
    
  datarea = Tnodeptr->ProvideArea();

RECOVER
  datarea = NULL;
ENDSEQ
  obh->StopReadTA(NO);
  return(datarea);
}

/******************************************************************************/
/**
\brief  ProvideGUID - Provide Global Instance Identifier (GUID)

        Usually  the  GUID  is  generated  when  the insatnce is created. It is,
        however,  also  possibbe  to  create  GUIDs  on  demand  by  not setting
        autogenerating  GUIDs  in  the  structure or collection definition. This
        function  allows explicitely  generating a  GUID as  long as no GUID has
        been  generated  for  the  instance.  When  the  ID  already exists, the
        function returns the current GUID without generating a new one.
        For  building  a  GUID  for  a  structure instance the structure must be
        derived  from __OBJECT. Since ProvideGUID is locking the __OBJECT extent
        it should not be used in long transactions.

\return guid_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideGUID"

char *PropertyHandle :: ProvideGUID ( )
{
  ACObject    *obh = StartRTA();
  char         *string = NULL;
  if ( IsPositioned() )
  {
    string = Tnodeptr->ProvideGUID(); 
    if ( Tnodeptr->stscmod() )
    {
      Tnodeptr->stsrmod();
      Tnodeptr->Modify();
    }
  }
  obh->StopReadTA(NO);
  return(string);
}

/******************************************************************************/
/**
\brief  ProvideGlobal - Provide instance outside the transaction

        The  function works the same way  as the Provide() function, except that
        global  instances  are  created  outside  the  transaction  when not yet
        existing.  When  not  running  in  a transactions the function works the
        same way as Add(). 
        Creating  global  instances  in  a  transaction prevents all other users
        from   creating   global   instances   for   the   same extent until the
        transaction  is  closed,  since  the  index for the global collection is
        locked  until  terminating  the  transaction.  Especially  when creating
        instances  via  local  collections  that are based on global collections
        (extents)  uncomfortable  locks  may  block  the  system.  In  this case
        ProvideGlobal() should be used instead of Provide(). 
        Using  ProvideGlobal()  for  creating  a  new instance the instance will
        resist in the global collection also when rolling back the transaction.

\return instance - Instance area
-------------------------------------------------------------------------------
\brief  A00 - 



\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideGlobal"

Instance PropertyHandle :: ProvideGlobal (PropertyHandle &prop_hdl )
{

  return ( prop_hdl.IsText()
           ? ProvideGlobal(StringToKey(prop_hdl.GetString()))
           : ProvideGlobal(prop_hdl.GetInt())  );


}

/******************************************************************************/
/**
\brief  AtPosition - 



\param  set_pos0_w - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideGlobal"

Instance PropertyHandle :: ProvideGlobal (int32 set_pos0_w )
{

  return ( !ValidateNode(YES)
           ? Instance(Tnodeptr->Provide(set_pos0_w,YES))
           : Instance() );


}

/******************************************************************************/
/**
\brief  ByKey - 



\param  sort_key - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideGlobal"

Instance PropertyHandle :: ProvideGlobal (Key sort_key )
{

  return ( !ValidateNode(YES)
           ? Instance(Tnodeptr->Provide(sort_key.GetData(),YES)) 
           : Instance() );


}

/******************************************************************************/
/**
\brief  i03 - 



\param  charkey - Key area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideGlobal"

Instance PropertyHandle :: ProvideGlobal (char *charkey )
{

  return ( !ValidateNode(YES)
           ? Instance(Tnodeptr->Provide(charkey,YES)) 
           : Instance() );


}

/******************************************************************************/
/**
\brief  i2 - 



\param  initinst - Initializing instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideGlobal"

Instance PropertyHandle :: ProvideGlobal (Instance initinst )
{
  ACObject    *obh = StartRTA();
  Instance     instance;
  if ( !ValidateNode(YES) )
    instance = Tnodeptr->Provide(initinst.GetData(),YES);

  obh->StopReadTA(NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  ProvideNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideNode"

node *PropertyHandle :: ProvideNode ( )
{
  node      *nodptr = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( nodeptr )
  {
    if ( !nodeptr->IsValid() )                       ERROR
    nodptr = nodeptr;
    LEAVESEQ
  }

  if ( !(nodeptr = new node()) )                     SDBERR(95)
  nodptr = nodeptr;

RECOVER

ENDSEQ
  return(nodptr);
}

/******************************************************************************/
/**
\brief  ProvideOperation - Provide operation handle

        To  avoid reopening of  an operation handle  for the same expression you
        can  search for an operation handle by using this function. The function
        returns  the operation  handle for  the given  expression if it has been
        ceated already. If not the function creates an operation handle.

\return operation_handle - 

\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideOperation"

OperationHandle *PropertyHandle :: ProvideOperation (char *expression )
{
  ACObject    *obh = StartRTA();
  OperationHandle   *operation_handle = NULL;
BEGINSEQ
  ValidateNode(YES);
  
  if ( !IsValid() )                                    ERROR
  
  if ( operation_handle = (OperationHandle *)nodeptr->GetOperationPtr(expression) )
                                                     LEAVESEQ
// fuer calling object gilt                                                     
// ph-pointer ist irrelevant, nodeptr muss stimmen
// aber: das ph, mit dem das OperationHandle konstruiert wurde, 
// gibt dieses frei, auch wenn der node noch nicht freigegeben wird (use_count > 0)
  
  operation_handle = new OperationHandle(*this);
  DictionaryHandle  dict(nodeptr->GetDictionary());
  DBObjectHandle    dbo (nodeptr->GetObjectHandle());
  DBObjectHandle    rdbo;
  if ( operation_handle->ProvideExpression(dict,rdbo,dbo,expression) )  
                                                     ERROR

  operation_handle = (OperationHandle *)nodeptr->GetOperationPtr(expression);

RECOVER
  delete operation_handle;
  operation_handle = NULL;
ENDSEQ
  obh->StopReadTA(NO);
  return(operation_handle);
}

/******************************************************************************/
/**
\brief  ReadBuffer - Fill instance buffer from position

        The  function explicitly fills the buffer instances. the position of the
        first  instance to be  read is passed  in set_pos0. The function removes
        all  buffer  instances  located  in  the  buffer and refills the buffer.
        Passing   CURRENT_INSTANCE as  next position  (default) the buffer reads
        instances  beginning with the current position which has been set by the
        last  Get() or  LocateKey() function.  When no  instance is selected the
        buffer is filled beginning with the first instance. 
        When  reading the last instances in a collection the buffer might not be
        filled  completely.  The  number  of  instances  read into the buffer is
        returned from the function.

\return instcount - Number of instances read into buffer

\param  set_pos0 - Position in collection
\param  direction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadBuffer"

int16 PropertyHandle :: ReadBuffer (int32 set_pos0, int16 direction )
{
  ACObject    *obh = StartRTA();
  int16        bufnum = ERIC;
  if ( !ValidateNode(YES) )
    bufnum = Tnodeptr->ReadBuffer(set_pos0,direction);

  obh->StopReadTA(NO);
  return(bufnum);
}

/******************************************************************************/
/**
\brief  Refresh - Refresh selected instance

        The  function  checks  whether  the  parent  of  the  property handle is
        positioned.  If not, the function trys  to position the parent hierarchy
        (PositionTop()). 
        If  the  parent  handle  is  positioned  and  the  property is an active
        property the function generates a server event (Refresh).

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical PropertyHandle :: Refresh ( )
{
  ACObject    *obh = StartRTA();
  node          *parent;
  logical        term = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
    
  if ( Tnodeptr && (parent = Tnodeptr->get_highnod()) &&       
       !parent->IsPositioned() )
  {
    PropertyHandle  ph(parent);
    if ( ph.PositionTop() || !ph.Get(AUTO) )         ERROR
  }      
    
  term = Tnodeptr->GenerateEvent(DBO_Refresh) ;

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return (term);
}

/******************************************************************************/
/**
\brief  RegisterHandle - Register property handle

        The  property  handle  is  registered  for  being notified when an event
        happens  on  the  allocated  resources  (index  or  instance). This is a
        precondition for receiving server events.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterHandle"

logical PropertyHandle :: RegisterHandle ( )
{

  return( IsValid() 
          ? Tnodeptr->RegisterHandle(NULL)
          : YES );

}

/******************************************************************************/
/**
\brief  RegisterNode - Register node in property handle



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterNode"

logical PropertyHandle :: RegisterNode (node *nodptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this || (nodeptr && !nodeptr->IsValid()) )   ERROR
  
  if ( nodeptr == nodptr )                           LEAVESEQ
  
  if ( nodeptr )
    Close();

  if ( nodptr )
  {
    if ( !nodptr->IsValid() )                        ERROR
    nodeptr = nodptr;
    nodeptr->Reserve((ObjectReferenceHandle *)this);
    nodeptr->SetPIRef(this);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterNode"

logical PropertyHandle :: RegisterNode (PropertyHandle &prop_hdl )
{

  return( RegisterNode(prop_hdl.get_nodeptr()) );

}

/******************************************************************************/
/**
\brief  ReleaseBuffer - Release instance buffer

        The  function will  release the  allocated buffer.  All instances in teh
        buffer  are  released  and  buffer  access  functions  cannot  be called
        anymore until allocating a buffer again.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseBuffer"

logical PropertyHandle :: ReleaseBuffer ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->ReleaseBuffer();

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveFromCollection - Remove instance from collection

        This  function  removes  the  selected  instance  from  a  collection. 
        Sometimes,  instances  cannot  be  deleted  because of an error. In this
        case,  this function can be used,  to remove inconsistent instances from
        a  collection anyhow. It must be possible  to locate the instance in the
        index  (by key or position). After  locating the instance, this function
        will remove the instance. 
        The  function does not maintain related  collections and will not delete
        the instance physically.

\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveFromCollection"

logical PropertyHandle :: RemoveFromCollection ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(YES);
  
  if ( IsValid() )
    term = Tnodeptr->RemoveFromCollection();

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveString - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  string - String area
\param  position - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveString"

logical PropertyHandle :: RemoveString (char *string, int32 position, int32 len )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ProvideArea();
  
  if ( IsValid() )
    term = Tnodeptr->RemoveString(string,position,len);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveTerminator - Remove line terminator from large text fields

        The  function removes the terminator string (string) from the end of the
        text field.

\return term - Termination code

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveTerminator"

logical PropertyHandle :: RemoveTerminator (char *string )
{
  ACObject    *obh = StartRTA();
  fmcb        *fmcbptr = GetDescription();
  void        *datarea;
  char        *pos = NULL;
  logical      str_opt = YES;
  int          len;
  logical      term = NO;
BEGINSEQ
  if ( !(datarea = GetArea()) )                      ERROR
  if ( !fmcbptr || !string || !*string)              ERROR
  
  SDBEV1(string,UNDEF);
  if ( (len = strlen(string)) > fmcbptr->fmcbsize )  SDBERR(219)
    
  switch ( fmcbptr->fmcbityp )
  {
    case T_CHAR   : pos = ((char *)datarea) + MIN(gvtutle((char *)datarea,fmcbptr->fmcbsize),fmcbptr->fmcbsize) - len;
                    str_opt = NO;
                    break;
    case T_STRING : 
    case T_MEMO   : pos = strlen((char *)datarea) > fmcbptr->fmcbsize 
                          ? ((char *)datarea) + fmcbptr->fmcbsize - len
                          : ((char *)datarea) + strlen((char *)datarea) - len;
                    break;
    default       : SDBEV1("RemoveTerminator",UNDEF)
                    SDBEV2(fmcbptr->fmcbname,sizeof(fmcbptr->fmcbname))
                    SDBERR(220)
  }
  
  if ( pos >= (char *)datarea && !memcmp(pos,string,len) )
    memset(pos,str_opt ? 0 : ' ',len);
RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Rename - Rename instance

        The  rename function allows  changig the sort  key value of the selected
        instance. After changig the key value the instance is stored. 
        The  effect is the same as changing  the key attributes in the instance,
        unless that no knowledge about the key attributes is required.
        The  function  returns  an  error  (YES) when no instance is selected or
        when

\return term - Termination code

\param  new_key - New key for the instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Rename"

logical PropertyHandle :: Rename (Key new_key )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsPositioned() )
    term = Tnodeptr->Rename(new_key.GetData());
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  RepairIndex - Repair Index

        The  function  repairs  the  index  for  the collection  in the property
        handle.  When no key  name is passed,  the currently selected index will
        be  repaired.  Messages  about  repair  actions are written to the error
        log-file. 
        The  function  wil  remove  index  entries  pointing to invalid indanced
        (deleted). It repairs also index tree information in large indexes.

\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  key_name_w - Key name for conversion
\param  attrstr_w - Attribute type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RepairIndex"

logical PropertyHandle :: RepairIndex (char *key_name_w, char *attrstr_w )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsValid() )
    term = Tnodeptr->RepairIndex(key_name_w,attrstr_w);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceString - Replace system variable value

        The  function allows  replacing text  strings in  a text field. When the
        property  handle  refers  to  a  text field defined strings as passed in
        old_str can be replaced by the text passen in new_str. 
        When  the  function  is  called  for  persistent fields the updated text
        causes  a modification and  will be stored  into the database. Hence, it
        might  be better to create a copy of the property and replacing the text
        in the copy.

\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  old_str - Old string value
\param  new_str - New string value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceString"

logical PropertyHandle :: ReplaceString (char *old_str, char *new_str )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ProvideArea();
  
  if ( IsValid() )
    term = Tnodeptr->Replace(old_str,new_str);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceSysVariables - Replace system variable

        The  function  allows  replacing  system  variable  references in a text
        field.  When the  property handle  refers to  a text field that contains
        references  to  system  variables  (e.g.  "...%SYSVAR1%  ....")  those 
        references  are be replaced by the text currently set for the referenced
        system   variable   (in   an   ini-file   or   by   the  application (->
        SetSysVariable())). 
        When  the  function  is  called  for  persistent fields the updated text
        causes  a modification and  will be stored  into the database. Hence, it
        might  be better to create a copy of the property and replacing the text
        in the copy.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSysVariables"

logical PropertyHandle :: ReplaceSysVariables ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ProvideArea();
  
  if ( IsValid() )
    term = Tnodeptr->ReplaceSysVar();
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - Reset instance

        The  function resets the current selection  in the property handle, i.e.
        the   selection   is   cancelled   without   storing   the  last updates
        (->Cancel()).  Since  the  function  is  cancelling  the  selection  all
        subordinated property handles will cancel the selection as well. 
        Than  the  function  will  re-read  the  instance  from  the  database 
        (->Get()). Subordinated property handles remain in the unselect state.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical PropertyHandle :: Reset ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsPositioned() || IsDirty() )
    term = Tnodeptr->Reset();
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ResetDirty - Set property handle to dirty

        The  function marks  the property  handle as  dirty. This information is
        passed  to  the  client,  when  being  set on the server side (e.g. in a
        context  function  when  executing  an instance or property action). The
        client  will refresh the  peoperty handle state  as soon as this becomes
        possible, i.e. when calling the next client/server function.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetDirty"

void PropertyHandle :: ResetDirty ( )
{
  ACObject    *obh = StartRTA(); 

  if ( IsValid() )
    Tnodeptr->get_bnode()->SetDirty(NO);

  obh->StopReadTA(NO);
}

/******************************************************************************/
/**
\brief  ResetInstanceEventHandler - 




\param  event_link - Event link
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceEventHandler"

void PropertyHandle :: ResetInstanceEventHandler (EventLink *event_link )
{

  if ( IsValid() )
    Tnodeptr->ResetInstanceEventHandler(event_link);

}

/******************************************************************************/
/**
\brief  ResetInstanceProcessHandler - 




\param  event_link - Event link
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceProcessHandler"

void PropertyHandle :: ResetInstanceProcessHandler (EventLink *event_link )
{

  if ( IsValid() )
    Tnodeptr->ResetInstanceProcessHandler(event_link);

}

/******************************************************************************/
/**
\brief  ResetPropertyEventHandler - 




\param  event_link - Event link
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyEventHandler"

void PropertyHandle :: ResetPropertyEventHandler (EventLink *event_link )
{

  if ( IsValid() )
    Tnodeptr->ResetPropertyEventHandler(event_link);

}

/******************************************************************************/
/**
\brief  ResetPropertyProcessHandler - 




\param  event_link - Event link
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyProcessHandler"

void PropertyHandle :: ResetPropertyProcessHandler (EventLink *event_link )
{

  if ( IsValid() )
    Tnodeptr->ResetPropertyProcessHandler(event_link);

}

/******************************************************************************/
/**
\brief  ResetSelection - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSelection"

logical PropertyHandle :: ResetSelection ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->ResetExpression();
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ResetTransientProperty - Reset transient property handle

        The  function  releases  the  associated property handle for a transient
        property  handle.  The  associated  handle  will  be  released  for  the
        original  transient property handle and all  its copies. If there are no
        more  users registered for  the property handle  the access node will be
        destroyed.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetTransientProperty"

logical PropertyHandle :: ResetTransientProperty ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsValid(NO) )
    term = nodeptr->SetTransientProperty(NULL);

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ResetWProtect - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical PropertyHandle :: ResetWProtect ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsPositioned() )
    term = Tnodeptr->ResetWProtect();
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ReturnHandle - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReturnHandle"

node *PropertyHandle :: ReturnHandle ( )
{

  return ( IsValid(NO) ? nodeptr : NULL );


}

/******************************************************************************/
/**
\brief  Save - Store instance

        The  function stores all modification made  on the selected instance and
        updates  made  on  instances  in subordinated property handles. Within a
        transaction  the the function will write  the updates to the transaction
        buffer.  Modifications are  stored to  the database when the transaction
        is closed (Commit()).
        The  function is called automatically when  changing the selection for a
        property handle and modifications have been made on the instance.

\return term - Termination code
/******************************************************************************/
/**
\brief  i00 - 



\param  savopt - Store option
\param  switchopt - Unselct option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical PropertyHandle :: Save (char savopt, logical switchopt )
{
  ACObject    *obh = StartRTA();
  logical    term = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  if ( !Tnodeptr->get_nodeinst() )                   LEAVESEQ
    
  if ( Tnodeptr->Save(switchopt,savopt,YES) )        ERROR
RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SearchText - Search string in property

        This  function  performs  a  string  search  for a text property. If the
        property  is not a text property (-> IsText()) the function returns AUTO
        (-1).

\return curpos - 

\param  string - String area
\param  curpos - 
\param  case_opt - Case sensitive
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchText"

int32 PropertyHandle :: SearchText (char *string, int32 curpos, logical case_opt )
{
  ACObject    *obh = StartRTA();

BEGINSEQ
  ProvideArea();
  
  if ( !IsValid() )                                  ERROR
    
  curpos = Tnodeptr->Search(string,curpos,case_opt);

RECOVER
  curpos = AUTO;
ENDSEQ
  obh->StopReadTA(NO);
  return(curpos);
}

/******************************************************************************/
/**
\brief  Select - Create a subset from a collection

        The  result collection contains the instances from the passed collection
        that  return  true  (YES)  for  the  expression  passed  to  the  select
        function.  The expression passed must define  a valid expression for the
        structure of the passed collection. 
        The  operation is performed  with the passed  operand storing the result
        in  the collection referenced  by the calling  property handle. When the
        calling  property handle refers to a  non empty collection all instances
        are  removed before performing the  operation. When the calling property
        handle  is empty the function creates a temporary extend for storing the
        result.

\return result_ref - Result property hadle

\param  prophdl_ref - Reference to Property handle
\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Select"

PropertyHandle &PropertyHandle :: Select (PropertyHandle &prophdl_ref, char *expression )
{
  ACObject  *obh = prophdl_ref.StartRTA();

BEGINSEQ
  if ( !this || (nodeptr && 
                 ( !nodeptr->IsValid() || 
                  (Tnodeptr && !Tnodeptr->IsValid()))) ) ERROR
  if ( CreatePIHandle(prophdl_ref) )                     ERROR
  
  Tnodeptr->Select(prophdl_ref.Tnodeptr,expression,AUTO);
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  SetActionResult - Set result string

        The  function allows  setting a  result string  for the property handle.
        The  result string  can be  retrieved with the GetActionResult function.
        Thus  you can pass the result of any action also to a client application
        while  the  action  is  running  on  the server. The result is passed as
        string,  i.e. the  result must  not contain  any 0-characters except the
        terminating 0.


\param  result_string - Result string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionResult"

void PropertyHandle :: SetActionResult (char *result_string )
{
  int saveerr = SDBERROR;

  if ( IsValid() )
    Tnodeptr->set_result_string(result_string,UNDEF);

  if ( saveerr )
    SDBISET(saveerr);


}

/******************************************************************************/
/**
\brief  SetArea - Set area pointer for property instance

        The  function  can  be  used  for property handles referring to internal
        data  (transient fields) to allocate an  instance area. The data area is
        not   owned   by   the   property   handle   in   this case and will not
        automatically freed when closing the property handle. 
        Do  not use this functions for  subordinated property handles that refer
        to  properties  in  instances.  This will disconnect the property handle
        from its instance data.

\return instance - Instance area

\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetArea"

Instance PropertyHandle :: SetArea (void *datarea )
{

  return ( IsValid()
           ? Instance(Tnodeptr->SetArea(datarea))
           : Instance() );

}

/******************************************************************************/
/**
\brief  SetContextVariables - Set context variables

        Somtimes  the  behaviour  of  an  object  is context dependent (e.g. the
        language  set defines  the language  displayed in an generic attribute).
        Usually  the context  is set  automatically when  accessing objects in a
        certain  hierarchy.  Some  applications,  however,  do access objects by
        instance  identity  (LOID).  In  this  case  the  context  is  usually 
        undefined.  To set the proper context  information the function can send
        a context string that passes context parameters to the property handle.
        The  context information  passed in  the variable  string is sent to the
        structure  and  to  the  property  context.  To  process  the  context 
        information  the  SetContextVariables()  function  must be overloaded in
        the appropriate context classes.

\return term - Termination code

\param  context_string - Context string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContextVariables"

logical PropertyHandle :: SetContextVariables (char *context_string )
{
  ACObject    *obh = StartRTA();
  logical      term = NO;
BEGINSEQ
  ValidateNode(YES);
  
  if ( !IsValid() )                                  ERROR
    
  if ( Tnodeptr->Save(NO,NO,NO) )                    ERROR
    
  term = Tnodeptr->SetContextVariables(context_string);
  Tnodeptr->Reset();
RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetDescription - Set definition for property

        The  function  can  be  used  for property handles referring to internal
        data  (transient  fields)  to  allocate  a description (DBFieldDef). The
        description  is not owned  by the property  handle in this case and will
        not automatically freed when closing the property handle. 
        Do  not use this functions for  subordinated property handles that refer
        to properties in instances.

-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_def - Property definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDescription"

void PropertyHandle :: SetDescription (DBFieldDef *prop_def )
{

  if ( GetValid() )
    Tnodeptr->SetDescription(prop_def);


}

/******************************************************************************/
/**
\brief  i01 - 



\param  fmcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDescription"

void PropertyHandle :: SetDescription (fmcb *fmcbptr )
{

  if ( GetValid() )
    ((dbf *)Tnodeptr)->SetDescription(fmcbptr);

}

/******************************************************************************/
/**
\brief  SetDirty - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDirty"

void PropertyHandle :: SetDirty ( )
{
  ACObject    *obh = StartRTA(); 

  if ( IsValid() )
    Tnodeptr->get_bnode()->SetDirty(YES);

  obh->StopReadTA(NO);
}

/******************************************************************************/
/**
\brief  SetDynLength - Activate dynamic length handling

        The  function activates dynamical  size correction for  the data area of
        the  property  handle.  When  assigning  a value that is larger then the
        data  area the data area will  increase automatically instead of cutting
        the value.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDynLength"

logical PropertyHandle :: SetDynLength ( )
{

  return ( IsValid()
           ? Tnodeptr->SetDynLength()
           : YES );

}

/******************************************************************************/
/**
\brief  SetGenAttribute - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  attrstr - Attribute type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical PropertyHandle :: SetGenAttribute (char *attrstr )
{

  return ( SetGenAttribute_intern(NULL,UNDEF,attrstr) );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  attrtype - Type of generic attribute
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical PropertyHandle :: SetGenAttribute (int attrtype )
{

  return ( SetGenAttribute_intern(NULL,attrtype,NULL) );

}

/******************************************************************************/
/**
\brief  i2 - 



\param  attrstr - Attribute type
\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical PropertyHandle :: SetGenAttribute (char *attrstr, char *prop_path )
{

  return ( SetGenAttribute_intern(prop_path,UNDEF,attrstr) );

}

/******************************************************************************/
/**
\brief  i3 - 



\param  attrtype - Type of generic attribute
\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical PropertyHandle :: SetGenAttribute (int attrtype, char *prop_path )
{

  return ( SetGenAttribute_intern(prop_path,attrtype,NULL) );

}

/******************************************************************************/
/**
\brief  SetGenAttribute_intern - 



\return term - Termination code

\param  prop_path - Property path
\param  attrtype - Type of generic attribute
\param  attrstr - Attribute type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute_intern"

logical PropertyHandle :: SetGenAttribute_intern (char *prop_path, int attrtype, char *attrstr )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(YES);
  
  if ( IsValid() )
    term = Tnodeptr->SetGenAttribute(prop_path,attrtype,attrstr);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetInstance - Set basic instance for property

        The  function locates the  area for the  property handle in an instance.
        When  defining  internal  structured  instances this allows locating the
        property  instance within a structure instance. This function should not
        be  called  for  property  handles  in  database  instances since it may
        disconnect the property handle from the database instance.

\return instptr - 

\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

Instance PropertyHandle :: SetInstance (Instance instance )
{

  return ( IsValid()
           ? Instance(Tnodeptr->SetInstance(&instance))
           : Instance() );

}

/******************************************************************************/
/**
\brief  SetInstanceAction - Register action in the instance context

        The  function  adds  an  action  to the instance context of the property
        handle.  The instance action, which is not defined in the data model, is
        available  in  the  instance  context  for  the current property handle,
        only, but not for all instance contexts of this type.

\return term - Termination code

\param  action - Simple Action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceAction"

logical PropertyHandle :: SetInstanceAction (SimpleAction *action )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(YES);
  
  if ( IsValid() )
    term = Tnodeptr->SetInstAction(action);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetInstanceEventHandler - Set Instance Event Handler

        Instance  event  handlers  can  be  used as an alternative way to handle
        server  notifications independent on implemented  context classes. To be
        notified  from the server the property  handle must be registered on the
        server (RegisterPropertyHandle(). 
        When  setting  event  handlers  in  addition  to a context class handler
        function,   the   context   class   handler   is   executed prior to the
        application  handlers. When  the context  class handler returns an error
        (YES),  the  application  handlers  are  not  executed.  Execution  of 
        application  handlers  is  also  stopped,  when  the  first  application
        handler returns an eror (YES). 
        The  event handler is passed as an  event link that consists of an event
        handler  function and a class instance. The handler is called later with
        the instance of the event handler class set in the event link.
        When  adding  several  instance  event  handlers, they are called in the
        sequence  as being added to the property handle. Handlers can be removed
        using the ResetInstanceEventHandler() function.


\param  event_link - Event link
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceEventHandler"

void PropertyHandle :: SetInstanceEventHandler (EventLink *event_link )
{

  if ( IsValid() )
    Tnodeptr->SetInstanceEventHandler(event_link);

}

/******************************************************************************/
/**
\brief  SetInstanceProcessHandler - Activate Instance process event handler

        Instance  process  event  handler  can  be used as an alternative way to
        handle  instance database events within  an instance (structure) context
        class.  In  contrast  to  database  event  handler  functions in context
        classes,  event  handler  can  be  installed  in any application without
        defining  specific  context  classes.  This  allows  handling  different
        instances with the one event handler. 
        When  setting  event  handlers  in  addition  to a context class handler
        function  the context class handler is executed prior to the application
        handlers.  When the  context class  handler returns  an error (YES), the
        application  handlers  are  not  executed.  Execution  of  application 
        handlers  is also stopped, when the first application handler returns an
        eror (YES). 
        The  event handler is passed as an  event link that consists of an event
        handler  function and a class instance. The handler is called later with
        the instance of the event handler class set in the event link.
        When  adding several instance process event handlers, they are called in
        the  sequence  as  being  added  to the property handle. Handlers can be
        removed using the ResetInstanceProcessHandler() function.


\param  event_link - Event link
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceProcessHandler"

void PropertyHandle :: SetInstanceProcessHandler (EventLink *event_link )
{

  if ( IsValid() )
    Tnodeptr->SetInstanceProcessHandler(event_link);

}

/******************************************************************************/
/**
\brief  SetKey - Move ident key value to instance

        The  passed  key  value  is  stored  to  the component attributes of the
        identifying  key in the instance. When passing an empty instance the key
        is  stored  in  the  selected  instance  of the property handle. When no
        insztance  is passed or  selected or when  no identifying key is defined
        for the structure the function returns an error (YES).

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  ident_key - Ident key value
\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical PropertyHandle :: SetKey (Key ident_key, Instance instance )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(YES);
  
  if ( IsValid() )
    term = Tnodeptr->SetKey(ident_key.GetData(),instance.GetData());

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ident_key - Ident key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical PropertyHandle :: SetKey (Key ident_key )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(YES);
  
  if ( IsValid() )
    term = Tnodeptr->SetKey(ident_key.GetData(),NULL);

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetModified - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetModified"

void PropertyHandle :: SetModified ( )
{
  ACObject    *obh = StartRTA(); 

  if ( IsValid() )
    Tnodeptr->Modify();

  obh->StopReadTA(NO);
}

/******************************************************************************/
/**
\brief  SetNormalized - Set normalized value in attribute

        The  function  can  be  used  for  storing  integer  values with decimal
        precisions  in  INT  or  unsigned  INT  attributes.   When defining a an
        attribute  with two decimals, assigning 1 will result inernally into 100
        (1.00).  Assigning  the  value  using  SetNormalized  will  result  in 1
        (0.01).

\return term - Termination code

\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNormalized"

logical PropertyHandle :: SetNormalized (int32 long_val )
{
  ACObject    *obh = StartRTA();
  DBFieldDef *fmcbptr = GetDescription();
  logical     term    = NO;
BEGINSEQ
  if ( !fmcbptr || (fmcbptr->fmcbityp != T_INT && fmcbptr->fmcbityp != T_UINT) )
                                                     ERROR
  
  if ( GetNormalized() == long_val )                 LEAVESEQ
    
  if ( !Tnodeptr->Modify() )                         ERROR
  Tnodeptr->SetNormalized(long_val); 
  Tnodeptr->Store();

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetOrder - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 



\param  key_name_w - Key name for conversion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical PropertyHandle :: SetOrder (char *key_name_w )
{

  return ( SetOrder_intern(key_name_w,UNDEF,NULL) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  key_name - Key name
\param  attrtype - Type of generic attribute
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical PropertyHandle :: SetOrder (char *key_name, int attrtype )
{

  return ( SetOrder_intern(key_name,attrtype,NULL) );


}

/******************************************************************************/
/**
\brief  i02 - 



\param  key_name - Key name
\param  attrstr - Attribute type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical PropertyHandle :: SetOrder (char *key_name, char *attrstr )
{

  if ( attrstr && !*attrstr )
    attrstr = NULL;

  return ( SetOrder_intern(key_name,UNDEF,attrstr) );



}

/******************************************************************************/
/**
\brief  i03 - 



\param  key_name - Key name
\param  attrtype - Type of generic attribute
\param  attrstr - Attribute type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical PropertyHandle :: SetOrder (char *key_name, int attrtype, char *attrstr )
{

  return ( SetOrder_intern(key_name,attrtype,attrstr) );


}

/******************************************************************************/
/**
\brief  SetOrder_intern - 



\return term - Termination code

\param  key_name - Key name
\param  attrtype - Type of generic attribute
\param  attrstr - Attribute type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder_intern"

logical PropertyHandle :: SetOrder_intern (char *key_name, int attrtype, char *attrstr )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->SetOrder(key_name,attrtype,attrstr);

  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetPropertyAction - Register action in the property contect

        The  function  adds  an  action  to the property context of the property
        handle.  The property action, which is not defined in the data model, is
        available  in  the  instance  context  for  the current property handle,
        only, but not for all instance contexts of this type.

\return term - Termination code

\param  action - Simple Action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyAction"

logical PropertyHandle :: SetPropertyAction (SimpleAction *action )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->SetAction(action);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetPropertyEventHandler - Set Property Event Handler

        Property  event  handlers  can  be  used as an alternative way to handle
        server  notifications independent on implemented  context classes. To be
        notified  from the server the property  handle must be registered on the
        server (RegisterPropertyHandle()). 
        When  setting  event  handlers  in  addition  to a context class handler
        function,   the   context   class   handler   is   executed prior to the
        application  handlers. When  the context  class handler returns an error
        (YES),  the  application  handlers  are  not  executed.  Execution  of 
        application  handlers  is  also  stopped,  when  the  first  application
        handler returns an eror (YES). 
        The  event handler is passed as an  event link that consists of an event
        handler  function and a class instance. The handler is called later with
        the instance of the event handler class set in the event link.
        When  adding  several  property  event  handlers, they are called in the
        sequence  as being added to the property handle. Handlers can be removed
        using the ResetPropertyEventHandler() function.


\param  event_link - Event link
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyEventHandler"

void PropertyHandle :: SetPropertyEventHandler (EventLink *event_link )
{

  if ( IsValid() )
    Tnodeptr->SetPropertyEventHandler(event_link);

}

/******************************************************************************/
/**
\brief  SetPropertyProcessHandler - Activate proeprty process event handler

        Property  process  event  handlers  can  be  used  as an alternative for
        handling  instance database  events context  class handlers. In contrast
        to  database  event  handler  functions  in context classes, application
        event  handler  can  be  installed  in  any application without defining
        specific  context classes. This allows handling different instances with
        one event handler. 
        When  setting  event  handlers  in  addition  to a context class handler
        function  the context class handler is executed prior to the application
        handlers.  When the  context class  handler returns  an error (YES), the
        application  handlers  are  not  executed.  Execution  of  application 
        handlers  is also stopped, when the first application handler returns an
        eror (YES). 
        The  event handler is passed as an  event link that consists of an event
        handler  function and a class instance. The handler is called later with
        the instance of the event handler class set in the event link.
        When  adding several property process event handlers, they are called in
        the  sequence  as  being  added  to the property handle. Handlers can be
        removed using the ResetPropertyProcessHandler() function.


\param  event_link - Event link
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyProcessHandler"

void PropertyHandle :: SetPropertyProcessHandler (EventLink *event_link )
{

  if ( IsValid() )
    Tnodeptr->SetPropertyProcessHandler(event_link);

}

/******************************************************************************/
/**
\brief  SetSelection - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 



\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSelection"

logical PropertyHandle :: SetSelection (char *expression )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->SetExpression(expression);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSelection"

logical PropertyHandle :: SetSelection (BNFData *bdata )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  // server side, only
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->SetExpression(bdata);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetSortKey - Store sort key value to instance

        The  passed  key  value  is  stored  to  the component attributes of the
        selected  sort key in  the instance. When  passing an empty instance the
        key  is stored in the selected instance  of the property handle. When no
        instance  is passed or selected  or when no sort  key is defined for the
        structure the function returns an error (YES).

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  sort_key - Sort key value
\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSortKey"

logical PropertyHandle :: SetSortKey (Key sort_key, Instance instance )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(YES);
  
  if ( IsValid() )
    term = Tnodeptr->SetSortKey(sort_key.GetData(),instance.GetData());
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  sort_key - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSortKey"

logical PropertyHandle :: SetSortKey (Key sort_key )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(YES);
  
  if ( IsValid() )
    term = Tnodeptr->SetSortKey(sort_key.GetData(),NULL);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetTransientProperty - Setting property handle for transient property (reference)

        This  function sets the current handle  for a transient property handle.
        The  function  will  not  create  a  copy  of  the  property handle. The
        associated handle is registered, only. 
        When  a  copy  of  the  referenced  property  handle  is  required  the 
        application  has to create the copy  befor setting it. After associating
        the  copy  for  the  referenced  property  handle  it  can be destroyed.
        Because  it is  registered in  the transient  property handle it will be
        destroyed  when  resetting  the  transient  reference  or  when  setting
        another property handle for the same transient reference.
        When  creating  a  copy  of  a transient reference the copy will get the
        same  referenced handle. All referened property handles for the original
        transient  property  handle  and  all  its  copies  will be updated when
        setting  a  new  property  handle  for  the  original transient property
        handle or one of its copies. 
        Transient  property  handles  are  destroyed automatically when they are
        placed  in a persistent object instance  and this instance is destroyed.
        When,   however,   referring   recursively   to   a   property handle by
        associating  a  parent  or  higher  property  handle with a subordinated
        property  handle this may result in  never deleting the access node. Use
        MarkUsed() and MarkUnused() for handeling this situation.
        You   can   release   the   associated   property   handle   using   the
        ResetTransientProperty() function.

\return term - Termination code

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransientProperty"

logical PropertyHandle :: SetTransientProperty (PropertyHandle &prop_hdl )
{

  return ( IsValid(NO) 
           ? nodeptr->SetTransientProperty(prop_hdl.IsValid() ? prop_hdl.Tnodeptr : NULL)
           : YES );


}

/******************************************************************************/
/**
\brief  SetType - Set type for weak-typed collection

        Before  creating a new instance for  a weak-typed collection the type of
        the  instance to be inserted  has to be set  in the property handle. The
        type  of instance to  be created is  passe as structure name (strnames).
        This  setting  might  be  reset  when  reading  the next instance in the
        collection.

\return term - Termination code

\param  strnames - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

logical PropertyHandle :: SetType (char *strnames )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->SetType(strnames);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetUpdate - 



\return term - Termination code

\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUpdate"

logical PropertyHandle :: SetUpdate (logical check_update )
{
  logical                 term = NO;
BEGINSEQ
  if ( check_update )
  {
    if ( !Tnodeptr->Modify(NO) )                      ERROR
    Tnodeptr->Store();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetValue - 



\return result_ref - Result property hadle
-------------------------------------------------------------------------------
\brief  A00 - 



\param  cprop_hdl - Property Handle
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (const PropertyHandle &cprop_hdl, logical check_update )
{
  ACObject    *obh = StartRTA();

BEGINSEQ
  if ( !this )                                      ERROR
  cprop_hdl.ValidateNode(YES);
  if ( !cprop_hdl.IsValid(NO) )                     ERROR
  
  if ( !nodeptr )
    RegisterNode(cprop_hdl.get_nodeptr());
  if ( nodeptr == cprop_hdl.get_nodeptr() )         LEAVESEQ // 16.2.2004 geht nicht beim übernehmen von CollectionHandles
  
  ValidateNode(YES);
  if ( Tnodeptr->SetValue(((PropertyHandle *)&cprop_hdl)->GetTNode(),check_update) )
                                                    ERROR

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  BigInt - 



\param  int64_val - 
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (int64 int64_val, logical check_update )
{
  ACObject  *obh = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open(int64_val);
  else
  {
    obh = StartRTA();  
    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = int64_val;
    if ( SetUpdate(check_update) )                   ERROR
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Boolean - 



\param  logval - Logical value
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (logical logval, logical check_update )
{
  ACObject  *obh = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open(logval);
  else
  {
    obh = StartRTA();  
    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = logval; 
    if ( SetUpdate(check_update) )                   ERROR
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Date - 



\param  date_val - Date value
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (dbdt date_val, logical check_update )
{
  ACObject  *obh = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open(date_val);
  else
  {
    obh = StartRTA();  
    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = date_val; 
    if ( SetUpdate(check_update) )                   ERROR
  }
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Float - 



\param  dbl_value - Double value
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (double dbl_value, logical check_update )
{
  ACObject  *obh= NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open(dbl_value);
  else
  {
    obh = StartRTA();  
    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = dbl_value;
    if ( SetUpdate(check_update) )                   ERROR
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Integer - 



\param  long_val - Integer value
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (int32 long_val, logical check_update )
{
  ACObject  *obh = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open(long_val);
  else
  {
    obh = StartRTA();  
    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = long_val;
    if ( SetUpdate(check_update) )                   ERROR
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  String - 



\param  string - String area
\param  check_update - 
\param  conv_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (char *string, logical check_update, logical conv_opt )
{
  char      *str = NULL;
  ACObject  *obh = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open(string);
  else
  {
    obh = StartRTA();  
    
    if ( conv_opt )
      if ( str = ReplaceControlSequences(string,UNDEF,YES) )
        string = str;

    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = string; 
    if ( SetUpdate(check_update) )                   ERROR
  }
RECOVER

ENDSEQ
  if ( str )
    free(str);
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Time - 



\param  time_val - Time value
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (dbtm time_val, logical check_update )
{
  ACObject  *obh = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open(time_val);
  else
  {
    obh = StartRTA();  
    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = time_val; 
    if ( SetUpdate(check_update) )                   ERROR
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Timestamp - 



\param  datetime_val - Date-Time value
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (dttm datetime_val, logical check_update )
{
  ACObject  *obh = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open(datetime_val);
  else
  {
    obh = StartRTA();  
    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = datetime_val;
    if ( SetUpdate(check_update) )                   ERROR
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  i5 - 



\param  short_val - 
\param  check_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

PropertyHandle &PropertyHandle :: SetValue (int16 short_val, logical check_update )
{
  ACObject  *obh = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !nodeptr )
    Open((int32)short_val);
  else
  {
    obh = StartRTA();  
    if ( CheckUpdate(check_update) )                 ERROR
    *(fld *)Tnodeptr = (int32)short_val;
    if ( SetUpdate(check_update) )                   ERROR
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  SetVersion - Set instance version to be provided by the collection handle

        The  function allows  changing the  version for  a property handle. This
        allows  providing  older  instance  versions  that  are  stored  for the
        instance selected. 
        Passing  CUR_VERSION will reset  the version to  the current version for
        the property handle.

\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical PropertyHandle :: SetVersion (uint16 version_nr )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->SetVersion(version_nr);
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetWProtect - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical PropertyHandle :: SetWProtect ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsPositioned()  )
    term = Tnodeptr->SetWProtect();
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  StartRTA - Start read transaction

        Starting  a read transaction will cache  all system events generated for
        external  registered application resources  (RegisterHandle()). The last
        event  for  each  event  class  is cashed. Caching a higher class events
        will  remove lower class events. The level  of an event class is defined
        by its enumeration value. 
        Cached  events  will  be  released,  when  the  last read transaction is
        closed.  Read transactions  are registered  on the database object level
        and can be created here for convinience.

\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartRTA"

ACObject *PropertyHandle :: StartRTA ( ) const
{
  ACObject  *obhandle = NULL;


BEGINSEQ
  if ( !this || !nodeptr || !nodeptr->IsValid() )     ERROR

  obhandle = nodeptr->StartReadTA();

RECOVER

ENDSEQ
  return(obhandle);
}

/******************************************************************************/
/**
\brief  StopRTA - Stop read transction

        Termininating  the  last  read  transaction  for  a database object will
        release  events  in  the  event  cache and emits those to the registered
        event  handlers.  Note,  that  start  read  transactions  are  summed up
        regardled  from the property handle, which  was called for startiong the
        read transaction.

\return cond - Return value

\param  ta_started - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopRTA"

logical PropertyHandle :: StopRTA (logical ta_started ) const
{
  logical                 cond = YES;
BEGINSEQ
  if ( !ta_started )                                 LEAVESEQ
  if ( !this || !nodeptr || !nodeptr->IsValid() )    ERROR

  nodeptr->StopReadTA(NO);
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  StoreData - Store instance data to property handle

        The  passed  instance  is  stored  to  the  structure  attributes of the
        selected  instance. When no instance is  selected or located or when the
        instance is not writeable the function returns an error (YES).

\return term - Termination code

\param  instance - Instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreData"

logical PropertyHandle :: StoreData (Instance instance )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsValid() )
    term = nodeptr->StoreData(instance.GetData());
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  StringToKey - Convert string to internal key

        The  passed key will  be converted from  an extended SDF string into the
        internal  key instance format. As field  separator in the string key '|'
        is  assumed.  Structure  levels  are  enclosed in '{}'. Normally the key
        passed  is assumed to  be structured according  to the sort key selected
        for  the property  handle or  according to  the identifying key (when no
        sort  key is defined). It is, however, also possible to pass a valid key
        name for conversion.

\return key_val - Internal key value

\param  key_string - String area for key
\param  key_name_w - Key name for conversion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringToKey"

Key PropertyHandle :: StringToKey (Key key_string, char *key_name_w )
{
  ACObject    *obh = StartRTA();
  Key          key;
  ValidateNode(YES);
  
  if ( IsValid() )
    key = Key(Tnodeptr->StringToKey(key_string.GetData(),key_name_w));
  obh->StopReadTA(NO);
  return(key);
}

/******************************************************************************/
/**
\brief  ToTop - 



\return term - Termination code
/******************************************************************************/
/**
\brief  i - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToTop"

logical PropertyHandle :: ToTop ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  ValidateNode(NO);
  
  if ( IsValid() )
    term = Tnodeptr->ToTop();
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  Union - Union two collections

        The   result   collection   contains   the   instancesfrom   all operand
        collections.  When passing no for the distict option the result contains
        also  duplicates.  Otherwise  duplicates  are  not  stored in the result
        collection.  Duplicates are determined by means of sort key (passing YES
        for  ik_opt)  or  local  identities  (LOID).  Using the LOID is save but
        comparing  the key is  much faster. Hence,  the key check should be used
        whenever possible.

\return result_ref - Result property hadle
-------------------------------------------------------------------------------
\brief  i0 - Binary union

        This  implementation builds the union from the two collections passed to
        the  operation. The result is stored in the collection referenced by the
        calling  property handle. When  the calling property  handle refers to a
        non  empty  collection  all  instances are removed before performing the
        operation.  When  the  calling  property  handle  is  empty the function
        creates a temporary extend for storing the result.

\param  prop_hdl1 - First Property handle
\param  prop_hdl2 - Second Property handle
\param  sk_opt - Sort key option
\param  distinct - Distinct option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Union"

PropertyHandle &PropertyHandle :: Union (PropertyHandle &prop_hdl1, PropertyHandle &prop_hdl2, char sk_opt, logical distinct )
{
  PropertyHandle   *ph_list[] = {&prop_hdl1,&prop_hdl2};
  Union(ph_list,2,sk_opt,distinct);
  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - Union list of collections

        This  implementation builds the union from all collections passed to the
        operation.  The  result  is  stored  in the collection referenced by the
        calling  property handle. When  the calling property  handle refers to a
        non  empty  collection  all  instances are removed before performing the
        operation.  When  the  calling  property  handle  is  empty the function
        creates a temporary extend for storing the result.

\param  ph_list - List of property handles
\param  count - Number of entries
\param  sk_opt - Sort key option
\param  distinct - Distinct option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Union"

PropertyHandle &PropertyHandle :: Union (PropertyHandle **ph_list, int32 count, char sk_opt, logical distinct )
{
  ACObject    *obh   = NULL;
  int32        indx0 = 0;

BEGINSEQ
  if ( !this || (nodeptr && !nodeptr->IsValid()) 
             || (nodeptr && Tnodeptr && !Tnodeptr->IsValid()) ) 
                                                     ERROR
  if ( CreatePIHandle(ph_list,count,UNDEF,sk_opt))   ERROR
  
  obh = StartRTA();
  Tnodeptr->Union(ph_list,count,sk_opt,distinct);
  obh->StopReadTA(NO);

RECOVER

ENDSEQ
  return(*this);
}

/******************************************************************************/
/**
\brief  i02 - Union inplace

        Calling  the  function  with  one  property  handle  creates  the  union
        collection  is built from the calling  and the passed collection and the
        result  is  stored  in  the  calling  collection.  This  will change the
        collection for the calliung proiperty handle.

\param  prophdl_ref - Reference to Property handle
\param  sk_opt - Sort key option
\param  distinct - Distinct option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Union"

PropertyHandle &PropertyHandle :: Union (PropertyHandle &prophdl_ref, char sk_opt, logical distinct )
{
  ACObject    *obh = StartRTA();

BEGINSEQ
  if ( ValidateNode(YES) || prophdl_ref.ValidateNode(YES) )
                                                     ERROR
  Tnodeptr->Union(prophdl_ref.Tnodeptr,sk_opt,distinct);
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  Unlock - Unlock instance

        This  function  allows  unlocking  the selected instance of the property
        handle  after it has been locked  (-> Lock()). Instances for shared base
        structures  are not automatically included in  the unlocking and must be
        unlocked separately when being locked separately.  
        The   function   returns   NO   when   the   instance  has been unlocked
        successfully.  It  returns  en  error  (YES)  when  the  instance is not
        locked,  when  no  instance  is  selected in the property handle or when
        another error occurred.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical PropertyHandle :: Unlock ( )
{
  ACObject    *obh = StartRTA();
  logical      term = YES;
  if ( IsPositioned() )
    term = Tnodeptr->Unlock() ;
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  UnlockSet - Unlock collection

        This  function  allows  unlocking  a  collection  handle referenced in a
        collection  property handle that has been  locked (-> Lock()) within the
        application.
        The  function  returns  NO  when  the  collection  has  been  unlocked 
        successfully.  It  returns  en  error  (YES) when the collection has not
        been  locked, when no instance is  selected in the upper property handle
        (when existing) or when another error occurred.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockSet"

logical PropertyHandle :: UnlockSet ( )
{

  return( IsValid() 
          ? Tnodeptr->UnlockSet(NO) 
          : YES );

}

/******************************************************************************/
/**
\brief  UnregisterHandle - Unregister property handle

        The  property handle  is unregistered  for being  notified when an event
        happens on the allocated resources (index or instance).

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterHandle"

logical PropertyHandle :: UnregisterHandle ( )
{

  return( IsValid() 
          ? Tnodeptr->UnregisterHandle()
          : YES );

}

/******************************************************************************/
/**
\brief  ValidateNode - Checks whetehr the Namdle is valid

        Usually   a   property   handle   is   valid   when   it has been opened
        successfully.  When one of the upper  handles, however, is weak typed or
        untyped  the handle  may become  invalid when  changing the selection in
        the upper node.

\return term - Termination code

\param  provide_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidateNode"

logical PropertyHandle :: ValidateNode (logical provide_inst ) const
{
  ACObject               *obh      = StartRTA();
  node                   *new_node = NULL;
  char                   *key_name = NULL;
  int32                   attrtype = 0;
  logical                 term     = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR

  if ( !(new_node = nodeptr->ValidateNode(YES)) )    ERROR
  
  if ( new_node != nodeptr ) 
  {
    // nodes, die mit GPH oder GetParentProperty geholt wurden, können nicht wandern
    if ( nodeptr->LocatePIRef((PropertyHandle *)this) )                  
                                                     SDBERR(348)
    // ggf. besser im iRefresh() aufgehoben
    ((bnode *)new_node)->CopyEventHandler(Bnodeptr);
    if ( key_name = Tnodeptr->GetSortKey() )
      attrtype = Tnodeptr->GetGenOrderType();
    ((PropertyHandle *)this)->RegisterNode(new_node);
    if ( key_name && IsValid() )
      Tnodeptr->SetOrder(key_name,attrtype,NULL);      

    if ( !nodeptr->get_highnod()->IsPositioned() && 
         !nodeptr->get_highnod()->IsInitInstance() ) ERROR
  }
  if ( !Tnodeptr )                                   ERROR
  if ( provide_inst && !Tnodeptr->get_nodeinst() )
    Tnodeptr->Check(YES,NO);

RECOVER
  term = YES;
ENDSEQ
  obh->StopReadTA(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  get_nodeptr - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_nodeptr"

node *PropertyHandle :: get_nodeptr ( ) const
{

  return(this ? nodeptr : NULL);

}

/******************************************************************************/
/**
\brief  operator! - Negation operator for logical values

        The  NOT operation converts the operand into LOGICAL, when required, and
        returns, whether the result is not true.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!"

logical PropertyHandle :: operator! ( )
{

  SDBEV5("!",UNDEF)
  return(!IsTrue());

}

/******************************************************************************/
/**
\brief  operator!= - Compare two property instances (not equal)

        The  operation  compares  the  two  operands and returns false (NO) when
        they are identical and true (YES) otherwise.

\return cond - Return value
-------------------------------------------------------------------------------
\brief  i0 - Compare with other property handle

        This  operator compares the value in  the property handle with the value
        in  the  passed  property  handle.  Data  conversion   is performed when
        required.

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical PropertyHandle :: operator!= (const PropertyHandle &cprop_hdl )
{
  logical                 cond = YES;
  SDBEV5("!=",UNDEF)
  switch ( Compare(cprop_hdl) )
  {
    case   0 : cond = NO;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = YES;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - Compare with string value

        This  operator compares the value in  the property handle with the value
        in  the passed string. Data conversion  is performed for the string when
        required.

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical PropertyHandle :: operator!= (char *string )
{
  logical                 cond = YES;
  switch ( Compare(string) )
  {
    case   0 : cond = NO;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = YES;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i02 - Compare with 32-bit integer value

        This  operator compares the value in the property handle with the passed
        integer  value. Data conversion  is performed for  the passed value when
        required.

\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical PropertyHandle :: operator!= (int32 long_val )
{
  logical                 cond = YES;
  switch ( Compare(long_val) )
  {
    case   0 : cond = NO;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = YES;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i03 - Compare with double value

        This  operator compares the value in the property handle with the passed
        double  float value. Data  conversion is performed  for the passed value
        when required.

\param  double_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical PropertyHandle :: operator!= (double double_val )
{
  logical                 cond = YES;
  switch ( Compare(double_val) )
  {
    case   0 : cond = NO;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = YES;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i04 - Compare with date value

        This  operator compares the value in the property handle with the passed
        date  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  date  values  to  string  values  may  result  in
        different  string  values  for  the  same  date  value  depending on the
        national  setting. Hence, string values should not be compared with date
        values.  In this case it is more  appropriate to compare the date values
        directly ( ph.GetDate() != date_val).

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical PropertyHandle :: operator!= (dbdt date_val )
{
  logical                 cond = YES;
  switch ( Compare(date_val) )
  {
    case   0 : cond = NO;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = YES;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i05 - Compare with time value

        This  operator compares the value in the property handle with the passed
        time  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  time  values  to  string  values  may  result  in
        different  string  values  for  the  same  time  value  depending on the
        national  setting. Hence, string values should not be compared with time
        values.  In this case it is more  appropriate to compare the time values
        directly ( ph.GetTime() != time_val).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical PropertyHandle :: operator!= (dbtm time_val )
{
  logical                 cond = YES;
  switch ( Compare(time_val) )
  {
    case   0 : cond = NO;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = YES;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i06 - Compare property handles

        This  operator  compares  the  property handles, i.e. the cursor objects
        referenced  by the  property handle.  Property handles are considered as
        equal, when they refer to the same cursor.

\param  property_handle - Pointer to a property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical PropertyHandle :: operator!= (PropertyHandle *property_handle )
{

  return ( property_handle && this 
           ? property_handle->get_nodeptr() != nodeptr ? YES : NO
           : YES );
  //j: &&this new since 060217

}

/******************************************************************************/
/**
\brief  operator% - Remaining part for integer division

        The  modulo  operation  is  supported  for  numerical data, only. If the
        second  operand is  not compatible  with the  first operand the function
        tries  to convert the second operand into the type of the first operand.
        If  no conversion is possible the operation fails. The operator provides
        the  remaining part  of a  division of  the first operator by the second
        one.  
        The   result   is   returned   in   a   property  handle that is created
        temporarily.  You can  assign the  result to  another property handle or
        performing further operations.

\return result_handle - 

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator%"

PropertyHandle PropertyHandle :: operator% (PropertyHandle &prop_hdl )
{
  ACObject    *obh = StartRTA();
  PropertyHandle  result_field;
BEGINSEQ
  if ( !ProvideArea() || !prop_hdl.ProvideArea() )   ERROR
  SDBEV5("%",UNDEF)
  
  switch ( GetDescription(NO)->fmcbityp ) 
  {
    case T_UINT   : 
    case T_INT    : DBF_INT->Modulo(Tnodeptr,prop_hdl.GetTNode());
                    break;
    case T_REAL   : DBF_REAL->Modulo(Tnodeptr,prop_hdl.GetTNode());
                    break;
//  case T_BIT  :
    default     :                                    SDBERR(154)
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(result_field.get_nodeptr());
}

/******************************************************************************/
/**
\brief  operator& - AND operator (or intersect)

        The  intersect operation is  supported for collections,  only. It can be
        used instead of the Intersect function (Intersect(operand1,operand2)).  
        The   result   is   returned   in   a   property  handle that is created
        temporarily.  You can  assign the  result to  another property handle or
        performing further operations.

\return result_handle - 

\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator&"

PropertyHandle PropertyHandle :: operator& (PropertyHandle &prophdl_ref )
{
  PropertyHandle          result_field;
  SDBEV5("&",UNDEF)
  return( result_field.Intersect(*this,prophdl_ref,YES).get_nodeptr() );

}

/******************************************************************************/
/**
\brief  operator&& - Logical AND operation

        The  operator  returns  true  (YES)  if  both  operands  are true and NO
        otherwise.
        (-> IsTrue())

\return cond - Return value

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator&&"

logical PropertyHandle :: operator&& (const PropertyHandle &cprop_hdl )
{

  SDBEV5("&&",UNDEF)
  return ( IsTrue() && cprop_hdl.IsTrue());  


}

/******************************************************************************/
/**
\brief  operator&= - AND operator (intersect collections)

        The  operator returns the  result of an  intersec operation in the first
        operand.
        (-> operator&)

\return result_ref - Result property hadle

\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator&="

PropertyHandle &PropertyHandle :: operator&= (PropertyHandle &prophdl_ref )
{

  SDBEV5("&=",UNDEF)
  return( Intersect(prophdl_ref,YES) );

}

/******************************************************************************/
/**
\brief  operator() - Locate instance

        The  operator  can  be  used  to locate an instance instead of the Get()
        function.
        (-> Get())

\return instance - Instance area
-------------------------------------------------------------------------------
\brief  i0 - 



\param  set_pos0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

Instance PropertyHandle :: operator() (int32 set_pos0 )
{

  SDBEV5("()",UNDEF)
  return( Get(set_pos0) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

Instance PropertyHandle :: operator() (PropertyHandle &prop_hdl )
{

  SDBEV5("()",UNDEF)
  return( Get(prop_hdl) );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  sort_key - Sort key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

Instance PropertyHandle :: operator() (Key sort_key )
{

  return( Get(sort_key) );

}

/******************************************************************************/
/**
\brief  operator* - Multiply two properties

        The  multiplication operation is supported for some types, only. The way
        the  operation is performed depends on the type of the first operand. If
        the  second  operand  is  not  compatible  with  the  first  operand the
        function  tries to convert the second operand into the type of the first
        operand. If no conversion is possible the operation fails. 
        1. Numerical data
        The operator multiplies the second operand with the first one. 
        5. Logical
        The multiplication returns the result of an and operation
        The   result   is   returned   in   a   property  handle that is created
        temporarily.  You can  assign the  result to  another property handle or
        performing further operations.

\return result_handle - 

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator*"

PropertyHandle PropertyHandle :: operator* (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh = StartRTA();
  PropertyHandle  result_field;
BEGINSEQ
  if ( !ProvideArea() || !cprop_hdl.ProvideArea() )   ERROR
  SDBEV5("*",UNDEF)
  
  switch ( GetDescription(NO)->fmcbityp ) 
  {
    case T_UINT   : 
    case T_INT    : 
    case T_REAL   : DBF_REAL->Multiply(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode());
                    break;
//  case T_BIT  :
    case T_LO     : *(char *)result_field.get_nodeptr()->GetArea() = (*this && cprop_hdl);    
                    break;
    default     :                                    SDBERR(154)
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(result_field.get_nodeptr());
}

/******************************************************************************/
/**
\brief  operator*= - Multiply and assign result to first operator

        The  operator  returns  the  result  of  a  multiplication  in the first
        operand.
        (-> operator*)

\return result_ref - Result property hadle

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator*="

PropertyHandle &PropertyHandle :: operator*= (const PropertyHandle &cprop_hdl )
{


  return(*this = *this * cprop_hdl);
}

/******************************************************************************/
/**
\brief  operator+ - Sum two properties

        The  sum operation performed  depends on the  type of the first operand.
        If  the  second  operand  is  not  compatible with the first operand the
        function  tries to convert the second operand into the type of the first
        operand. If no conversion is possible the operation fails. 
        1. Numerical data
        The operator adds the second operand to the first one. 
        2. Text data
        The  operator concatenates  the second  operand to  the first operand 1,
        i.e. "Paul " + "Miller" = "Paul Miller".
        3. Collections
        The Union operation is performed as operand1.Union(operand2)
        4. Time fields
        For date and time you may add only integer.  
        5. Logical
        The substract operation returns the result of an or operation
        The   result   is   returned   in   a   property  handle that is created
        temporarily.  You can  assign the  result to  another property handle or
        performing further operations.

\return result_handle - 

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

PropertyHandle PropertyHandle :: operator+ (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh = StartRTA();
  DBIndex     *order;
  PropertyHandle  result_field;
  logical         distinct = NO;
BEGINSEQ
  SDBEV5("+",UNDEF)
  
  if ( !cprop_hdl.get_nodeptr() )                    LEAVESEQ
  if ( !nodeptr )
  {
    ProvideNode();
    *this = cprop_hdl;
    LEAVESEQ
  }

  if ( ProvideArea() && cprop_hdl.ProvideArea() )
    switch ( GetDescription(NO)->fmcbityp ) 
    {
      case T_UINT   : 
      case T_INT    : 
      case T_REAL   : DBF_REAL->Add(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode());
                      LEAVESEQ
  //  case T_BIT    : später wie INT
      case T_CHAR   : 
      case T_CCHAR  : 
      case T_STRING : DBF_CHAR->Add(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode());
                      LEAVESEQ
      case T_DATE   : DBF_DATE->Add(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode()); 
                      LEAVESEQ
      case T_TIME   : DBF_TIME->Add(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode());
                      LEAVESEQ
      case T_DATETIME:DBF_DATETIME->Add(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode()); 
                      LEAVESEQ
      case T_LO     : if ( !result_field.IsValid() )
                        result_field.Open((logical)NO);
                      *(char *)result_field.get_nodeptr()->GetArea() = (*this || cprop_hdl);
                      LEAVESEQ
      case T_NONE   :
      case T_VOID   :
      case T_GUID   : 
      case T_MEMO   : 
      case T_BLOB   : 
      case UNDEF    :
      default       : ;
    }
    
  if ( !IsCollection() || !cprop_hdl.IsCollection() ) SDBERR(154)
  if ( (order = nodeptr->GetDBIndex()) && order->get_unique() )
    distinct = YES;
  result_field.Union(*this,*(PropertyHandle *)&cprop_hdl,YES,distinct);

// für Bereiche sollte das ganze in einer Schleife laufen und jeder Wert behandelt werden.
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(result_field.get_nodeptr());
}

/******************************************************************************/
/**
\brief  operator++ - Position cursor on next instance

        The increment operation performed depends on the type of the operand.  
        1. Numerical data
        The operator increments the value by 1. 
        2. Collections
        The  operation tries to  locate the next  instance in the collection. If
        no  iinstance  is  selected  it  locates  the  first  instance  n  the 
        collection. 
        The result is returned in the operand.

\return result_ref - Result property hadle
-------------------------------------------------------------------------------
\brief  i0 - 



\param  - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator++"

PropertyHandle &PropertyHandle :: operator++ (int  )
{

  SDBEV5("++",UNDEF)
  Position(+1);
  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator++"

PropertyHandle &PropertyHandle :: operator++ ( )
{

  SDBEV5("++",UNDEF)
  Position(+1);
  return(*this);
}

/******************************************************************************/
/**
\brief  operator+= - Sum and assign result to first operator

        The operator returns the sum of the two operands in the first operand.
        (-> operator+)

\return result_ref - Result property hadle

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

PropertyHandle &PropertyHandle :: operator+= (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh = StartRTA();
  DBIndex        *order;
  logical         distinct = NO;
  if ( IsCollection() && cprop_hdl.IsCollection() ) 
  {
    if ( (order = Tnodeptr->GetDBIndex()) && order->get_unique() )
      distinct = YES;
    Union((PropertyHandle &)cprop_hdl,YES,distinct);
  }
  else
    *this = *this + cprop_hdl;
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  operator- - Subtract properties

        The  substract  operation  performed  depends  on  the type of the first
        operand.  If the second operand is not compatible with the first operand
        the  function tries to  convert the second  operand into the type of the
        first operand. If no conversion is possible the operation fails. 
        1. Numerical data
        The operator substract the second operand from the first one. 
        2. Text data
        The  operator  removes  all  occurences  of operand 2 in operand 1, i.e.
        "Paul Miller" - "aul" = "P Miller".
        3. Collections
        The Minus operation is performed as operand1.Minus(operand2)
        4. Time fields
        For  date  and  time  you  may substract integer or time values. values,
        only.  Substracting an integer  results in a  new time value of the same
        type  (operand1).  Substracting  a  time  value  results  in  an integer
        containing the distance between the time balues. 
        5. Logical
        The substract operation returns the result of an exclusive or operation
        The   result   is   returned   in   a   property  handle that is created
        temporarily.  You can  assign the  result to  another property handle or
        performing further operations.

\return result_handle - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-"

PropertyHandle PropertyHandle :: operator- (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh = StartRTA();
  PropertyHandle  result_field;
BEGINSEQ
  SDBEV5("-",UNDEF)
  
  if ( ProvideArea() && cprop_hdl.ProvideArea() )
    switch ( GetDescription(NO)->fmcbityp ) 
    {
      case T_UINT   : 
      case T_INT    : 
      case T_REAL   : DBF_REAL->Substract(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode());
                      LEAVESEQ
  //  case T_BIT    : später wie INT
      case T_CHAR   : 
      case T_CCHAR  : 
      case T_STRING : DBF_CHAR->Substract(Tnodeptr,((PropertyHandle *)&cprop_hdl)->get_nodeptr());
                      LEAVESEQ
      case T_DATE   : DBF_DATE->Substract(nodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode()); 
                      LEAVESEQ
      case T_TIME   : DBF_TIME->Substract(nodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode());
                      LEAVESEQ
    case T_DATETIME : DBF_DATETIME->Substract(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode()); 
                      LEAVESEQ
      case T_LO     : *(char *)result_field.get_nodeptr()->GetArea() = (*this ^ cprop_hdl);
                      LEAVESEQ
      case T_BLOB   :
      case T_GUID   :
      case T_MEMO   :
      case T_NONE   :
      case T_VOID   :
      case UNDEF    :
      default       : ;
    }
  
  if ( !IsCollection() || !cprop_hdl.IsCollection() ) SDBERR(154)
  result_field.Minus(*this,*(PropertyHandle *)&cprop_hdl);

// für Bereiche sollte das ganze in einer Schleife laufen und jeder Wert behandelt werden.
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(result_field.get_nodeptr());
}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-"

PropertyHandle PropertyHandle :: operator- ( )
{
  ACObject    *obh = StartRTA();
  PropertyHandle  result_field;
BEGINSEQ
  if ( !ProvideArea() )                               ERROR
  SDBEV1("-",UNDEF)
  
  switch ( GetDescription()->fmcbityp ) 
  {
    case T_UINT   : 
    case T_INT    : DBF_INT->Substract(nodeptr);
                    break;
    case T_REAL   : DBF_REAL->Substract(nodeptr);
                    break;
//  case T_BIT    : später wie INT
    case T_CHAR   : 
    case T_CCHAR  : 
    case T_STRING : DBF_CHAR->Substract(nodeptr);
                    break;
    case T_MEMO   : // s.o. (hier muß für das Result ein STRING-Feld erzeugt werden)
                    break;
    case T_LO     : *(char *)result_field.get_nodeptr()->GetArea() = !(*this);
                    break;
    case T_BLOB   :
    case T_GUID   :
    case T_DATE   : 
    case T_TIME   : 
    case T_DATETIME:
    case T_NONE   :
    case T_VOID   :
    case UNDEF    :
    default       :   SDBERR(154)
  }
// für Bereiche sollte das ganze in einer Schleife laufen und jeder Wert behandelt werden.
RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(result_field);
}

/******************************************************************************/
/**
\brief  operator-- - Position cursor on previous instance

        The decrement operation performed depends on the type of the operand.  
        1. Numerical data
        The operator decrements the value by 1. 
        2. Collections
        The  operation tries to locate the  prevoius instance in the collection.
        If  no  iinstance  is  selected  it  locates  the  last  instance  n the
        collection. 
        The result is returned in the operand.

\return result_ref - Result property hadle
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator--"

PropertyHandle &PropertyHandle :: operator-- ( )
{

  SDBEV5("--",UNDEF)
  Position(-1);

  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator--"

PropertyHandle &PropertyHandle :: operator-- (int  )
{

  SDBEV5("--",UNDEF)
  Position(-1);

  return(*this);
}

/******************************************************************************/
/**
\brief  operator-= - Subtract and assign result to first operator

        The  operator  returns  the  difference  of  the  first  and  the second
        operator in the first operand.
        (-> operator-)

\return result_ref - Result property hadle

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-="

PropertyHandle &PropertyHandle :: operator-= (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh = StartRTA();

  if ( IsCollection() && cprop_hdl.IsCollection() ) 
    Minus((PropertyHandle &)cprop_hdl);
  else
    *this = *this - cprop_hdl;
  obh->StopReadTA(NO);
  return(*this);
}

/******************************************************************************/
/**
\brief  operator/ - Devide proprties

        The  division operation  is supported  for numerical  data, only. If the
        second  operand is  not compatible  with the  first operand the function
        tries  to convert the second operand into the type of the first operand.
        If  no conversion is possible the  operation fails. The operator devides
        the first operand by the second one. 
        The   result   is   returned   in   a   property  handle that is created
        temporarily.  You can  assign the  result to  another property handle or
        performing further operations.

\return result_handle - 

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator/"

PropertyHandle PropertyHandle :: operator/ (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh = StartRTA();
  PropertyHandle  result_field;
BEGINSEQ
  if ( !ProvideArea() || !cprop_hdl.ProvideArea() )   ERROR
  SDBEV5("/",UNDEF)
  
  switch ( GetDescription(NO)->fmcbityp ) 
  {
    case T_UINT   : 
    case T_INT    : 
    case T_REAL   : DBF_REAL->Divide(Tnodeptr,((PropertyHandle *)&cprop_hdl)->GetTNode());
                    break;
//  case T_BIT  :
                    break;
    default     :                                    SDBERR(154)
  }

RECOVER

ENDSEQ
  obh->StopReadTA(NO);
  return(result_field.get_nodeptr());
}

/******************************************************************************/
/**
\brief  operator/= - Divide and assign result to first operator

        The operator returns the result of a division in the first operand.
        (-> operator/)

\return result_ref - Result property hadle

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator/="

PropertyHandle &PropertyHandle :: operator/= (const PropertyHandle &cprop_hdl )
{


  return(*this = *this / cprop_hdl);
}

/******************************************************************************/
/**
\brief  operator< - Compare two property instances (less)

        The  operation compares the two operands and returns true (YES) when the
        first  operand  is  smaller  than  the  second  operand  and  false (NO)
        otherwise.

\return cond - Return value
-------------------------------------------------------------------------------
\brief  i0 - Compare with other property handle

        This  operator compares the value in  the property handle with the value
        in  the  passed  property  handle.  Data  conversion   is performed when
        required.

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical PropertyHandle :: operator< (PropertyHandle &prop_hdl )
{
  logical                 cond = YES;
  SDBEV5("<",UNDEF)
  switch ( Compare(prop_hdl) )
  {
    case  -1 : cond = YES;
               break;
    case   0 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - Compare with string value

        This  operator compares the value in  the property handle with the value
        in  the passed string. Data conversion  is performed for the string when
        required.

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical PropertyHandle :: operator< (char *string )
{
  logical                 cond = YES;
  switch ( Compare(string) )
  {
    case  -1 : cond = YES;
               break;
    case   0 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i02 - Compare with 32-bit integer value

        This  operator compares the value in the property handle with the passed
        integer  value. Data conversion  is performed for  the passed value when
        required.

\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical PropertyHandle :: operator< (int32 long_val )
{
  logical                 cond = YES;
  switch ( Compare(long_val) )
  {
    case  -1 : cond = YES;
               break;
    case   0 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i03 - Compare with double value

        This  operator compares the value in the property handle with the passed
        double  float value. Data  conversion is performed  for the passed value
        when required.

\param  double_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical PropertyHandle :: operator< (double double_val )
{
  logical                 cond = YES;
  switch ( Compare(double_val) )
  {
    case  -1 : cond = YES;
               break;
    case   0 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i04 - Compare with date value

        This  operator compares the value in the property handle with the passed
        date  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  date  values  to  string  values  may  result  in
        different  string  values  for  the  same  date  value  depending on the
        national  setting. Hence, string values should not be compared with date
        values.  In this case it is more  appropriate to compare the date values
        directly ( ph.GetDate() < date_val)

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical PropertyHandle :: operator< (dbdt date_val )
{
  logical                 cond = YES;
  switch ( Compare(date_val) )
  {
    case  -1 : cond = YES;
               break;
    case   0 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i05 - Compare with time value

        This  operator compares the value in the property handle with the passed
        time  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  time  values  to  string  values  may  result  in
        different  string  values  for  the  same  time  value  depending on the
        national  setting. Hence, string values should not be compared with time
        values.  In this case it is more  appropriate to compare the time values
        directly ( ph.GetTime() < time_val).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical PropertyHandle :: operator< (dbtm time_val )
{
  logical                 cond = YES;
  switch ( Compare(time_val) )
  {
    case  -1 : cond = YES;
               break;
    case   0 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  operator<< - 



\return result_handle - 

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<<"

PropertyHandle PropertyHandle :: operator<< (const PropertyHandle &cprop_hdl )
{
  ACObject    *obh = StartRTA();
  DBIndex        *order;
  PropertyHandle *operand = (PropertyHandle *)&cprop_hdl;
  PropertyHandle  result_field;
  PropertyHandle *result = this;
  logical         distinct = NO;
BEGINSEQ
  SDBEV5("<<",UNDEF)
  
  if ( !cprop_hdl.get_nodeptr() )                    LEAVESEQ
  if ( !nodeptr )
  {
    ProvideNode();
    *this = cprop_hdl;
    LEAVESEQ
  }

  if ( ProvideArea() && cprop_hdl.ProvideArea() )
    switch ( GetDescription(NO)->fmcbityp ) 
    {
      case T_UINT   : 
      case T_INT    : 
      case T_REAL   : *this = Tnodeptr->dbf::GetInt() << operand->GetInt();
                      LEAVESEQ
  //  case T_BIT    : später wie INT
      case T_CHAR   : 
      case T_CCHAR  : 
      case T_STRING : AppendString(operand->GetString());
                      LEAVESEQ
      case T_DATE   : 
      case T_TIME   : 
      case T_DATETIME:
      case T_LO     : 
      case T_NONE   :
      case T_VOID   :
      case T_GUID   : 
      case T_MEMO   : 
      case T_BLOB   : 
      case UNDEF    :
      default       : ;
    }
    
  if ( !IsCollection() || !operand->IsCollection() ) SDBERR(154)
  if ( (order = nodeptr->GetDBIndex()) && order->get_unique() )
    distinct = YES;
  Union(*operand,YES,distinct);

// für Bereiche sollte das ganze in einer Schleife laufen und jeder Wert behandelt werden.
RECOVER
  result = &result_field;
ENDSEQ
  obh->StopReadTA(NO);
  return(*result);
}

/******************************************************************************/
/**
\brief  operator<= - Compare two property instances (less or equal)

        The  operation compares the two operands and returns true (YES) when the
        first  operand is smaller than or equal  to the second operand and false
        (NO) otherwise.

\return cond - Return value
-------------------------------------------------------------------------------
\brief  i0 - Compare with other property handle

        This  operator compares the value in  the property handle with the value
        in  the  passed  property  handle.  Data  conversion   is performed when
        required.

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical PropertyHandle :: operator<= (PropertyHandle &prop_hdl )
{
  logical                 cond = YES;
  SDBEV5("<=",UNDEF)
  switch ( Compare(prop_hdl) )
  {
    case   0 : 
    case  -1 : cond = YES;
               break;
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - Compare with string value

        This  operator compares the value in  the property handle with the value
        in  the passed string. Data conversion  is performed for the string when
        required.

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical PropertyHandle :: operator<= (char *string )
{
  logical                 cond = YES;
  switch ( Compare(string) )
  {
    case   0 : 
    case  -1 : cond = YES;
               break;
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i02 - Compare with 32-bit integer value

        This  operator compares the value in the property handle with the passed
        integer  value. Data conversion  is performed for  the passed value when
        required.

\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical PropertyHandle :: operator<= (int32 long_val )
{
  logical                 cond = YES;
  switch ( Compare(long_val) )
  {
    case   0 : 
    case  -1 : cond = YES;
               break;
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i03 - Compare with time value

        This  operator compares the value in the property handle with the passed
        time  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  time  values  to  string  values  may  result  in
        different  string  values  for  the  same  time  value  depending on the
        national  setting. Hence, string values should not be compared with time
        values.  In this case it is more  appropriate to compare the time values
        directly ( ph.GetTime() <= time_val).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical PropertyHandle :: operator<= (dbtm time_val )
{
  logical                 cond = YES;
  switch ( Compare(time_val) )
  {
    case   0 : 
    case  -1 : cond = YES;
               break;
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i04 - Compare with date value

        This  operator compares the value in the property handle with the passed
        date  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  date  values  to  string  values  may  result  in
        different  string  values  for  the  same  date  value  depending on the
        national  setting. Hence, string values should not be compared with date
        values.  In this case it is more  appropriate to compare the date values
        directly ( ph.GetDate() <= date_val).

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical PropertyHandle :: operator<= (dbdt date_val )
{
  logical                 cond = YES;
  switch ( Compare(date_val) )
  {
    case   0 : 
    case  -1 : cond = YES;
               break;
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i05 - Compare with double value

        This  operator compares the value in the property handle with the passed
        double  float value. Data  conversion is performed  for the passed value
        when required.

\param  double_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical PropertyHandle :: operator<= (double double_val )
{
  logical                 cond = YES;
  switch ( Compare(double_val) )
  {
    case   0 : 
    case  -1 : cond = YES;
               break;
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  operator= - Assign property instances

        The  assignment operator allows assigning  values of property handles to
        each  other. The  way the  operation is  performed depends mainly on the
        first operand:
        1. First operand is (not opened)
        The  function copies the  handle pointer from  the second operand to the
        first operand.
        (-> CopyHandle(property_handle))
        2. Collection 
        When  both,  the  first  and  the  second operator, are collections, the
        instances  in the  first collection  are deleted  and the instances from
        the second collection are copied to the first collection. 
        3. Instance or value
        if  the  first  operand  refers  to  an  instance  or value the function
        converts  the  instance  or  value  from  the  second  operand  into the
        instance  of the first  operand. If the  second operand is a collection,
        the  selected instance in  this collection is  copied. If no instance is
        selected  in the second operand the function tries to select an instance
        in  the second  operand for  performing the operation. Copying instances
        is  done by assigning all properties  with the same name. Copying values
        will perform automatic data conversion when necessary. 
        The  operand allows also assigning values  to a property handle. In this
        case  (second operand  is a  value and  not a property handle) the first
        operand  must refer to a value or  instance. The value is converted when
        necessary.
        When  no instance is available in  the second operand, the first operand
        remains  unchanged.  Hence,  it  is  sugested  to  initialize  the first
        operand before assigning uncertain values.

\return result_ref - Result property hadle
-------------------------------------------------------------------------------
\brief  BigInt - 



\param  int64_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (int64 int64_val )
{

  return( SetValue(int64_val,YES) );

}

/******************************************************************************/
/**
\brief  Boolean - 



\param  logval - Logical value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (logical logval )
{

  return( SetValue(logval,YES) );

}

/******************************************************************************/
/**
\brief  Date - 



\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (dbdt date_val )
{

  return( SetValue(date_val,YES) );

}

/******************************************************************************/
/**
\brief  Float - 



\param  dbl_value - Double value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (double dbl_value )
{

  return( SetValue(dbl_value,YES) );

}

/******************************************************************************/
/**
\brief  Integer - 



\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (int32 long_val )
{

  return( SetValue(long_val,YES) );

}

/******************************************************************************/
/**
\brief  PH - 



\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (const PropertyHandle &cprop_hdl )
{

  return( SetValue(cprop_hdl,YES) );

}

/******************************************************************************/
/**
\brief  ShortInt - 



\param  short_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (int16 short_val )
{

  return( SetValue(short_val,YES) );

}

/******************************************************************************/
/**
\brief  String - 



\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (char *string )
{

  return( SetValue(string,YES) );

}

/******************************************************************************/
/**
\brief  Time - 



\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (dbtm time_val )
{

  return( SetValue(time_val,YES) );

}

/******************************************************************************/
/**
\brief  Timestamp - 



\param  datetime_val - Date-Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

PropertyHandle &PropertyHandle :: operator= (dttm datetime_val )
{

  return( SetValue(datetime_val,YES) );

}

/******************************************************************************/
/**
\brief  operator== - Compare two property instances (equal)

        The  operation compares the two operands and returns true (YES) when the
        first  operand  is  equal  to  then  the  second  operand and false (NO)
        otherwise.

\return cond - Return value
-------------------------------------------------------------------------------
\brief  i0 - Compare with other property handle

        This  operator compares the value in  the property handle with the value
        in  the  passed  property  handle.  Data  conversion   is performed when
        required.

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical PropertyHandle :: operator== (const PropertyHandle &cprop_hdl )
{
  logical                 cond = YES;
  switch ( Compare(cprop_hdl) )
  {
    case   0 : cond = YES;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - Compare with string value

        This  operator compares the value in  the property handle with the value
        in  the passed string. Data conversion  is performed for the string when
        required.

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical PropertyHandle :: operator== (char *string )
{
  logical                 cond = YES;
  switch ( Compare(string) )
  {
    case   0 : cond = YES;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i02 - Compare with 32-bit integer value

        This  operator compares the value in the property handle with the passed
        integer  value. Data conversion  is performed for  the passed value when
        required.

\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical PropertyHandle :: operator== (int32 long_val )
{
  logical                 cond = YES;
  switch ( Compare(long_val) )
  {
    case   0 : cond = YES;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i03 - Compare with double value

        This  operator compares the value in the property handle with the passed
        double  float value. Data  conversion is performed  for the passed value
        when required.

\param  double_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical PropertyHandle :: operator== (double double_val )
{
  logical                 cond = YES;
  switch ( Compare(double_val) )
  {
    case   0 : cond = YES;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i04 - Compare with date value

        This  operator compares the value in the property handle with the passed
        date  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  date  values  to  string  values  may  result  in
        different  string  values  for  the  same  date  value  depending on the
        national  setting. Hence, string values should not be compared with date
        values.  In this case it is more  appropriate to compare the date values
        directly ( ph.GetDate() == date_val).

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical PropertyHandle :: operator== (dbdt date_val )
{
  logical                 cond = YES;
  switch ( Compare(date_val) )
  {
    case   0 : cond = YES;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i05 - Compare with time value

        This  operator compares the value in the property handle with the passed
        time  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  time  values  to  string  values  may  result  in
        different  string  values  for  the  same  time  value  depending on the
        national  setting. Hence, string values should not be compared with time
        values.  In this case it is more  appropriate to compare the time values
        directly ( ph.GetTime() == time_val).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical PropertyHandle :: operator== (dbtm time_val )
{
  logical                 cond = YES;
  switch ( Compare(time_val) )
  {
    case   0 : cond = YES;
               break;
    case  -1 : 
    case   1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i06 - Compare property handles

        This  operator  compares  the  property handles, i.e. the cursor objects
        referenced  by the  property handle.  Property handles are considered as
        equal, when they refer to the same cursor.

\param  property_handle - Pointer to a property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical PropertyHandle :: operator== (PropertyHandle *property_handle )
{

  return ( property_handle 
           ? property_handle->get_nodeptr() == nodeptr ? YES : NO
           : NO );

}

/******************************************************************************/
/**
\brief  operator> - Compare two property instances (greater)

        The  operation compares the two operands and returns true (YES) when the
        first  operand  is  greater  than  the  second  operand  and  false (NO)
        otherwise.

\return cond - Return value
-------------------------------------------------------------------------------
\brief  i0 - Compare with other property handle

        This  operator compares the value in  the property handle with the value
        in  the  passed  property  handle.  Data  conversion   is performed when
        required.

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical PropertyHandle :: operator> (PropertyHandle &prop_hdl )
{
  logical                 cond = YES;
  SDBEV5(">",UNDEF)
  switch ( Compare(prop_hdl) )
  {
    case   1 : cond = YES;
               break;
    case   0 : 
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - Compare with string value

        This  operator compares the value in  the property handle with the value
        in  the passed string. Data conversion  is performed for the string when
        required.

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical PropertyHandle :: operator> (char *string )
{
  logical                 cond = YES;
  switch ( Compare(string) )
  {
    case   1 : cond = YES;
               break;
    case   0 : 
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i02 - Compare with 32-bit integer value

        This  operator compares the value in the property handle with the passed
        integer  value. Data conversion  is performed for  the passed value when
        required.

\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical PropertyHandle :: operator> (int32 long_val )
{
  logical                 cond = YES;
  switch ( Compare(long_val) )
  {
    case   1 : cond = YES;
               break;
    case   0 : 
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i03 - Compare with double value

        This  operator compares the value in the property handle with the passed
        double  float value. Data  conversion is performed  for the passed value
        when required.

\param  double_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical PropertyHandle :: operator> (double double_val )
{
  logical                 cond = YES;
  switch ( Compare(double_val) )
  {
    case   1 : cond = YES;
               break;
    case   0 : 
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i04 - Compare with date value

        This  operator compares the value in the property handle with the passed
        date  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  date  values  to  string  values  may  result  in
        different  string  values  for  the  same  date  value  depending on the
        national  setting. Hence, string values should not be compared with date
        values.  In this case it is more  appropriate to compare the date values
        directly ( ph.GetDate() > date_val).

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical PropertyHandle :: operator> (dbdt date_val )
{
  logical                 cond = YES;
  switch ( Compare(date_val) )
  {
    case   1 : cond = YES;
               break;
    case   0 : 
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i05 - Compare with time value

        This  operator compares the value in the property handle with the passed
        time  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  time  values  to  string  values  may  result  in
        different  string  values  for  the  same  time  value  depending on the
        national  setting. Hence, string values should not be compared with time
        values.  In this case it is more  appropriate to compare the time values
        directly ( ph.GetTime() > time_val).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical PropertyHandle :: operator> (dbtm time_val )
{
  logical                 cond = YES;
  switch ( Compare(time_val) )
  {
    case   1 : cond = YES;
               break;
    case   0 : 
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  operator>= - Compare two property instances (greater or equal)

        The  operation compares the two operands and returns true (YES) when the
        first  operand is equal to or greater  than the second operand and false
        (NO) otherwise.

\return cond - Return value
-------------------------------------------------------------------------------
\brief  i0 - Compare with other property handle

        This  operator compares the value in  the property handle with the value
        in  the  passed  property  handle.  Data  conversion   is performed when
        required.

\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical PropertyHandle :: operator>= (PropertyHandle &prop_hdl )
{
  logical                 cond = YES;
  SDBEV5(">=",UNDEF)
  switch ( Compare(prop_hdl) )
  {
    case   0 : 
    case   1 : cond = YES;
               break;
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - Compare with string value

        This  operator compares the value in  the property handle with the value
        in  the passed string. Data conversion  is performed for the string when
        required.

\param  string - String area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical PropertyHandle :: operator>= (char *string )
{
  logical                 cond = YES;
  switch ( Compare(string) )
  {
    case   0 : 
    case   1 : cond = YES;
               break;
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i02 - Compare with 32-bit integer value

        This  operator compares the value in the property handle with the passed
        integer  value. Data conversion  is performed for  the passed value when
        required.

\param  long_val - Integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical PropertyHandle :: operator>= (int32 long_val )
{
  logical                 cond = YES;
  switch ( Compare(long_val) )
  {
    case   0 : 
    case   1 : cond = YES;
               break;
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i03 - Compare with double value

        This  operator compares the value in the property handle with the passed
        double  float value. Data  conversion is performed  for the passed value
        when required.

\param  double_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical PropertyHandle :: operator>= (double double_val )
{
  logical                 cond = YES;
  switch ( Compare(double_val) )
  {
    case   0 : 
    case   1 : cond = YES;
               break;
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i04 - Compare with time value

        This  operator compares the value in the property handle with the passed
        time  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  time  values  to  string  values  may  result  in
        different  string  values  for  the  same  time  value  depending on the
        national  setting. Hence, string values should not be compared with time
        values.  In this case it is more  appropriate to compare the time values
        directly ( ph.GetTime() >= time_val).

\param  time_val - Time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical PropertyHandle :: operator>= (dbtm time_val )
{
  logical                 cond = YES;
  switch ( Compare(time_val) )
  {
    case   0 : 
    case   1 : cond = YES;
               break;
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  i05 - Compare with date value

        This  operator compares the value in the property handle with the passed
        date  value.  Data  conversion  is  performed  for the passed value when
        required.  Converting  date  values  to  string  values  may  result  in
        different  string  values  for  the  same  date  value  depending on the
        national  setting. Hence, string values should not be compared with date
        values.  In this case it is more  appropriate to compare the date values
        directly ( ph.GetDate() >= date_val).

\param  date_val - Date value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical PropertyHandle :: operator>= (dbdt date_val )
{
  logical                 cond = YES;
  switch ( Compare(date_val) )
  {
    case   0 : 
    case   1 : cond = YES;
               break;
    case  -1 : 
    case -99 : 
               
    default  : cond = NO;
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  operator>> - 



\return result_handle - 

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>>"

PropertyHandle PropertyHandle :: operator>> (const PropertyHandle &cprop_hdl )
{
  ACObject       *obh = StartRTA();
  DBIndex        *order;
  PropertyHandle *operand = (PropertyHandle *)&cprop_hdl;
  PropertyHandle  result_field;
  PropertyHandle *result = this;
  logical         distinct = NO;
BEGINSEQ
  SDBEV5(">>",UNDEF)
  
  if ( !cprop_hdl.get_nodeptr() )                    LEAVESEQ
  if ( !nodeptr )
  {
    ProvideNode();
    *this = cprop_hdl;
    LEAVESEQ
  }

  if ( ProvideArea() && cprop_hdl.ProvideArea() )
    switch ( GetDescription(NO)->fmcbityp ) 
    {
      case T_UINT   : 
      case T_INT    : 
      case T_REAL   : *this = Tnodeptr->dbf::GetInt() >> operand->GetInt();
                      LEAVESEQ
  //  case T_BIT    : später wie INT
      case T_CHAR   : 
      case T_CCHAR  : 
      case T_STRING : operand->AppendString(GetString());
                      result = operand;
                      LEAVESEQ
      case T_DATE   : 
      case T_TIME   : 
      case T_DATETIME:
      case T_LO     : 
      case T_NONE   :
      case T_VOID   :
      case T_GUID   : 
      case T_MEMO   : 
      case T_BLOB   : 
      case UNDEF    :
      default       : ;
    }
    
  if ( !IsCollection() || !operand->IsCollection() ) SDBERR(154)
  if ( (order = nodeptr->GetDBIndex()) && order->get_unique() )
    distinct = YES;
  operand->Union(*this,YES,distinct);
  result = operand;

// für Bereiche sollte das ganze in einer Schleife laufen und jeder Wert behandelt werden.
RECOVER
  result = &result_field;
ENDSEQ
  obh->StopReadTA(NO);
  return(*result);
}

/******************************************************************************/
/**
\brief  operator[] - Locate property instance

        The  operator  can  be  used  to  provide  an  instance  instead  of the
        Provide() function.
        (-> Provide())

\return result_ref - Result property hadle
-------------------------------------------------------------------------------
\brief  i0 - 



\param  set_pos0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator[]"

PropertyHandle &PropertyHandle :: operator[] (int32 set_pos0 )
{

  SDBEV5("[]",UNDEF)
  Provide(set_pos0);
  return(*this);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator[]"

PropertyHandle &PropertyHandle :: operator[] (PropertyHandle &prop_hdl )
{

  SDBEV5("[]",UNDEF)
  Provide(prop_hdl);
  return(*this);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  skey - Sort key
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator[]"

PropertyHandle &PropertyHandle :: operator[] (Key skey )
{

  SDBEV5("[]",UNDEF)
  Provide(skey);
  return(*this);
}

/******************************************************************************/
/**
\brief  operator^ - Exclusive OR operation

        The  operator returns true (YES) if exactly  one of the operands is true
        and NO otherwise.
        (-> IsTrue())

\return cond - Return value

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator^"

logical PropertyHandle :: operator^ (const PropertyHandle &cprop_hdl ) const
{

  SDBEV5("^",UNDEF)
  return ( IsTrue() ^ cprop_hdl.IsTrue());

}

/******************************************************************************/
/**
\brief  operator| - OR operation (union set for collections)

        The  union operation is supported for  collections, only. It can be used
        instead of the Union() function (Union(operand1,operand2)).  
        The   result   is   returned   in   a   property  handle that is created
        temporarily.  You can  assign the  result to  another property handle or
        performing further operations.

\return result_handle - 

\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator|"

PropertyHandle PropertyHandle :: operator| (PropertyHandle &prophdl_ref )
{
  PropertyHandle          result_field;
  SDBEV5("|",UNDEF)
  return( result_field.Union(*this,prophdl_ref,YES,NO).get_nodeptr() );


}

/******************************************************************************/
/**
\brief  operator|= - OR operation (union set for collections)

        The  operator  returns  the  result  of  a  union operation in the first
        operand.
        (-> operator|)

\return result_ref - Result property hadle

\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator|="

PropertyHandle &PropertyHandle :: operator|= (PropertyHandle &prophdl_ref )
{

  SDBEV5("|=",UNDEF)
  return( Union(prophdl_ref,YES,NO) );


}

/******************************************************************************/
/**
\brief  operator|| - Logical OR operation

        The  operator returns true (YES)  if one of the  operands is true and NO
        otherwise.
        (-> IsTrue())

\return cond - Return value

\param  cprop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator||"

logical PropertyHandle :: operator|| (const PropertyHandle &cprop_hdl )
{

  SDBEV5("||",UNDEF)
  return ( IsTrue() || cprop_hdl.IsTrue());  


}

/******************************************************************************/
/**
\brief  set_nodeptr - Set Node pointer




\param  nodptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_nodeptr"

void PropertyHandle :: set_nodeptr (node *nodptr )
{

  nodeptr = nodptr;

}

/******************************************************************************/
/**
\brief  ~PropertyHandle - Destructor

        The  function  will  close  the  property  handle and destroy the handle
        object.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~PropertyHandle"

     PropertyHandle :: ~PropertyHandle ( )
{

  Close();

}


