/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSPropPath

\brief    ODS Property path


\date     $Date: 2006/03/13 21:35:29,00 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSPropPath"

#include  <pogui7.h>
#include  <sODSPropPath.hpp>


/******************************************************************************/
/**
\brief  GetOrder - 


\return keyname -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOrder"

char *ODSPropPath :: GetOrder ( )
{

  return( type != PT_Self ? order : NULL );

}

/******************************************************************************/
/**
\brief  IsReadOnly - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical ODSPropPath :: IsReadOnly ( )
{

  return( acc_mode <= PI_Read );

}

/******************************************************************************/
/**
\brief  IsUndefined - 


\return cond -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUndefined"

logical ODSPropPath :: IsUndefined ( )
{

  return( type == PT_undefined && !path );

}

/******************************************************************************/
/**
\brief  ODSPropPath - 


-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSPropPath"

                        ODSPropPath :: ODSPropPath ( )
                     :   path(NULL),
  struct_name(NULL),
  order(NULL),
  filter(NULL),
  acc_mode(PI_undefined),
  type(PT_undefined),
  collection(NO),
  selection(NO)
{



}

/******************************************************************************/
/**
\brief  i01


\param  prop_path - Property path
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSPropPath"

                        ODSPropPath :: ODSPropPath (char *prop_path, ODSPropertyType prop_type )
                     :   path(NULL),
  struct_name(NULL),
  order(NULL),
  filter(NULL),
  acc_mode(PI_undefined),
  type(prop_type),
  collection(NO),
  selection(NO)
{

  SetPath(prop_path,prop_type);


}

/******************************************************************************/
/**
\brief  i02


\param  rcODSPropPath -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSPropPath"

                        ODSPropPath :: ODSPropPath (const ODSPropPath &rcODSPropPath )
                     :   path(NULL),
  struct_name(NULL),
  order(NULL),
  filter(NULL),
  acc_mode(PI_undefined),
  type(PT_undefined),
  collection(NO),
  selection(NO)
{

  SetPath(rcODSPropPath);
  SetAccessMode(rcODSPropPath.acc_mode);
  SetCollection(rcODSPropPath.collection);
  SetFilter(rcODSPropPath.filter,rcODSPropPath.selection);

}

/******************************************************************************/
/**
\brief  Path - 


\return rODSPropPath -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Path"

ODSPropPath &ODSPropPath :: Path ( )
{

  return *this;   // kann auch anders angesprochen werden

}

/******************************************************************************/
/**
\brief  ResetPath - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPath"

void ODSPropPath :: ResetPath ( )
{

  if ( path )
    free(path);
  path = NULL;
  
  if ( filter ) 
    free(filter);
  filter = NULL;
  
  if ( struct_name )
    free(struct_name);
  struct_name = NULL;
  
  if ( order )
    free(order);
  order = NULL;
  
  type = PT_undefined;

}

/******************************************************************************/
/**
\brief  SetAccessMode - 



\param  accmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAccessMode"

void ODSPropPath :: SetAccessMode (PIACC accmode )
{

  acc_mode = accmode;

}

/******************************************************************************/
/**
\brief  SetCollection - 



\param  is_collection - Is referenced path pointing to a collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCollection"

void ODSPropPath :: SetCollection (logical is_collection )
{

  collection = is_collection;

}

/******************************************************************************/
/**
\brief  SetFilter


\param  expression -
\param  enable_opt - Enable option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

void ODSPropPath :: SetFilter (char *expression, logical enable_opt )
{

  if ( filter )
    free(filter);
  filter = NULL;

  selection = enable_opt;
  
  if ( expression )
  {
    filter    = strdup(expression);
    selection = YES;
  }


}

/******************************************************************************/
/**
\brief  SetOrder - 


\return term -

\param  sort_index_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical ODSPropPath :: SetOrder (char *sort_index_name )
{
  logical                 term = NO;
  if ( order )
    free(order);
  order = NULL;
  
  if ( sort_index_name && *sort_index_name )
    order = strdup(sort_index_name);
  

  return(term);
}

/******************************************************************************/
/**
\brief  SetPath - 


-------------------------------------------------------------------------------
\brief  i00


\param  prop_path - Property path
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

void ODSPropPath :: SetPath (char *prop_path, ODSPropertyType prop_type )
{

  SetPath(prop_path,NULL,NO,NULL,prop_type);


}

/******************************************************************************/
/**
\brief  i01


\param  rcODSPropPath -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

void ODSPropPath :: SetPath (const ODSPropPath &rcODSPropPath )
{

  SetPath(rcODSPropPath.path,rcODSPropPath.struct_name,rcODSPropPath.collection,
          rcODSPropPath.order,rcODSPropPath.type,rcODSPropPath.acc_mode);


}

/******************************************************************************/
/**
\brief  i02


\param  prop_path - Property path
\param  strname -
\param  is_collection - Is referenced path pointing to a collection
\param  sort_index_name -
\param  prop_type - Property path  type
\param  accmode_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

void ODSPropPath :: SetPath (char *prop_path, char *strname, logical is_collection, char *sort_index_name, ODSPropertyType prop_type, PIACC accmode_w )
{

  ResetPath();
  
  if ( prop_path )
    path = strdup(prop_path);

  SetStructure(strname);
  SetOrder(sort_index_name);
  
  type       = prop_type;
  acc_mode   = accmode_w;
  collection = type == PT_BaseCollection ? YES : is_collection;



}

/******************************************************************************/
/**
\brief  SetStructure - 



\param  strnames -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStructure"

void ODSPropPath :: SetStructure (char *strnames )
{

  if ( !struct_name && strnames && *strnames )
    struct_name = strdup(strnames);

}

/******************************************************************************/
/**
\brief  SetType - 



\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

void ODSPropPath :: SetType (ODSPropertyType prop_type )
{

  type = prop_type;


}

/******************************************************************************/
/**
\brief  operator== - 


\return cond -

\param  rODSPropPath -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical ODSPropPath :: operator== (ODSPropPath &rODSPropPath )
{
  logical                 term = NO;
  return ( type == rODSPropPath.type                                          &&
           ( !path  && !rODSPropPath.path ) ||
           (  path  &&  rODSPropPath.path  && !strcmp(path,rODSPropPath.path) ) && 
           ( !order && !rODSPropPath.order ) ||
           (  order &&  rODSPropPath.order && !strcmp(order,rODSPropPath.order) ) );
  return(term);
}

/******************************************************************************/
/**
\brief  ~ODSPropPath - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODSPropPath"

                        ODSPropPath :: ~ODSPropPath ( )
{

  ResetPath();

}


