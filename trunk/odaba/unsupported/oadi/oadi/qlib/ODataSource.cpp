/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    ODataSource

\brief    


\date     $Date: 2006/07/29 14:08:30,92 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODataSource"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODataSource.hpp>
#include  <ioadii.h>
#include  <sODataSource.hpp>


/******************************************************************************/
/**
\brief  GetPath - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPath"

const char *ODataSource :: GetPath ( )
{
  const char        *prop_path = NULL;
BEGINSEQ
  if ( !dataReference || dataReference[0] == '*' )   LEAVESEQ
    
  switch ( referenceType )
  {
    case DRT_PropertyPath   : if ( !strcmp(dataReference,"__SORTKEY" ) )
                                LEAVESEQ
    case DRT_ResExtent      :
    case DRT_Extent         :
    case DRT_Enumeration    :
    case DRT_SystemVariable : 
    case DRT_UserDefined    : 
    case DRT_undefined      : prop_path = dataReference;
                              break;
    case DRT_View           :
    default                 : OADIERR(105);
  }

RECOVER
  prop_path = NULL;
ENDSEQ
  return(prop_path);
}

/******************************************************************************/
/**
\brief  GetPathType - 



\return prop_type - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathType"

ODSPropertyType ODataSource :: GetPathType ( )
{
  ODSPropertyType     prop_type = GetPropPathType(dataReference,referenceType);
  if ( use_copy && (prop_type == PT_Property || prop_type == PT_Self) )
    prop_type = PT_CopyProperty;

  return(prop_type);
}

/******************************************************************************/
/**
\brief  ODataSource - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODataSource"

     ODataSource :: ODataSource ( )
                     : OPersistent (),
  referenceType(DRT_undefined),
  accmode(PI_undefined),
  dataReference(NULL),
  baseCollection(NULL),
  structureName(NULL),
  sortOrder(NULL),
  isCollection(NO),
  use_key(NO),
  use_copy(NO),
  index(0),
  dataPH()
{




}

/******************************************************************************/
/**
\brief  i01 - 



\param  bcOPersistent - 
\param  adk_reference_type - 
\param  accmode - 
\param  dataReference - 
\param  baseCollection - 
\param  structureName - 
\param  sortOrder - 
\param  isCollection - 
\param  use_key - 
\param  use_copy - 
\param  index - 
\param  dataPH - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODataSource"

     ODataSource :: ODataSource (OPersistent bcOPersistent, int64 adk_reference_type, PIACC accmode, char *dataReference, char *baseCollection, char *structureName, char *sortOrder, logical isCollection, logical use_key, logical use_copy, int index, PropertyHandle dataPH )
                     : OPersistent (bcOPersistent),
  referenceType(referenceType),
  accmode(accmode),
  dataReference(NULL), //strdup
  baseCollection(NULL),//strdup
  structureName(NULL), //strdup
  sortOrder(NULL),     //strdup
  isCollection(isCollection),
  use_key(use_key),
  use_copy(use_copy),
  index(index),
  dataPH(dataPH)
{

  set_dataReference(dataReference);
  set_baseCollection(baseCollection);
  set_structureName(structureName);
  set_sortOrder(sortOrder);
    
/*
  "ODataSource("
  +        ADK_Persistent::Generate()
  + ", " + reference_type
  + ", " + access_mode
  + ", \"" + data_reference + "\""
  + ", \"" + base_collection + "\""
  + ", \"" + structure_name + "\""
  + ", \"" + sort_order + "\""
  + ", " + is_collection 
  + ", " + use_key
  + ", " + use_copy
  + ", " + set_index
  + ", " ?? PH
  + ")";
  
  
*/

}

/******************************************************************************/
/**
\brief  Read - 



\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical ODataSource :: Read (PropertyHandle *ph )
{
  char           *str;
  logical         term = NO;
  OPersistent::Read(ph);

  (int&)referenceType = ph->GetInt("reference_type");
  (int&)accmode       = ph->GetInt("access_mode");
  isCollection        = ph->GetInt("is_collection");
  use_key             = ph->GetInt("use_key");
  use_copy            = ph->GetInt("use_copy");
  index               = ph->GetInt("set_index");

  if ( (str = ph->GetString("data_reference")) && *str )
    dataReference = strdup(str);
  if ( (str = ph->GetString("base_collection")) && *str )
    baseCollection = strdup(str);
  if ( (str = ph->GetString("structure_name")) && *str )
    structureName = strdup(str);
  if ( (str = ph->GetString("sort_order")) && *str )
    sortOrder = strdup(str);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void ODataSource :: Reset ( )
{

  if ( dataReference )
    free(dataReference);
  dataReference = NULL;
  
  if ( baseCollection )
    free(baseCollection);
  baseCollection = NULL;
  
  if ( structureName )
    free(structureName);
  structureName = NULL;
  
  if ( sortOrder )
    free(sortOrder);
  sortOrder = NULL;

  referenceType = DRT_undefined;
  accmode       = PI_undefined;
  isCollection  = NO;
  use_key       = NO;
  use_copy      = NO;
  index         = 0;


}

/******************************************************************************/
/**
\brief  SetEditProperty - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetEditProperty"

void ODataSource :: SetEditProperty ( )
{

  referenceType = DRT_PropertyPath;
  dataReference = "*";
  
  isCollection  = NO;
  index         = AUTO;
  


}

/******************************************************************************/
/**
\brief  SetProperties - 



\return term - 

\param  as_collection - 
\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProperties"

logical ODataSource :: SetProperties (logical as_collection, PropertyHandle *prophdl )
{
  char           *str;
  logical         term = NO;
  referenceType = DRT_UserDefined;
  dataReference = NULL;
  
  isCollection  = as_collection;
  index         = AUTO;
  
  accmode       = prophdl->GetMode();
  
  if ( str = prophdl->GetCurrentType() )
    structureName = strdup(str);
  
  dataPH.Open(prophdl);

  return(term);
}

/******************************************************************************/
/**
\brief  operator= - 



\return rODataSource - 

\param  rODataSource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

ODataSource &ODataSource :: operator= (ODataSource &rODataSource )
{

  *(OPersistent *)this = rODataSource;
  referenceType = rODataSource.referenceType;
  accmode       = rODataSource.accmode;
  isCollection  = rODataSource.isCollection;
  use_key       = rODataSource.use_key;
  use_copy      = rODataSource.use_copy;
  index         = rODataSource.index;
  dataPH        = rODataSource.dataPH;

  set_dataReference(rODataSource.dataReference);
  set_baseCollection(rODataSource.baseCollection);
  set_structureName(rODataSource.structureName);
  set_sortOrder(rODataSource.sortOrder);

  return(*this);
}

/******************************************************************************/
/**
\brief  set_baseCollection - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_baseCollection"

void ODataSource :: set_baseCollection (char *string )
{

  if ( baseCollection )
  {
    free(baseCollection);
    baseCollection = NULL;
  }
  if ( string && *string )
    baseCollection = strdup(string);

}

/******************************************************************************/
/**
\brief  set_dataReference - 




\param  prop_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_dataReference"

void ODataSource :: set_dataReference (char *prop_path )
{

  if ( dataReference )
  {
    free(dataReference);
    dataReference = NULL;
  }
  if ( prop_path && *prop_path )
    dataReference = strdup(prop_path);

}

/******************************************************************************/
/**
\brief  set_isCollection - 




\param  as_collection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_isCollection"

void ODataSource :: set_isCollection (logical as_collection )
{

  isCollection = as_collection;

}

/******************************************************************************/
/**
\brief  set_referenceType - 




\param  data_ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_referenceType"

void ODataSource :: set_referenceType (ADK_DataReferenceType data_ref_type )
{

  referenceType = data_ref_type;

}

/******************************************************************************/
/**
\brief  set_sortOrder - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_sortOrder"

void ODataSource :: set_sortOrder (char *string )
{

  if ( sortOrder )
  {
    free(sortOrder);
    sortOrder = NULL;
  }
  if ( string && *string)
    sortOrder = strdup(string);

}

/******************************************************************************/
/**
\brief  set_structureName - 




\param  strnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_structureName"

void ODataSource :: set_structureName (char *strnames )
{

  if ( structureName )
  {
    free(structureName);
    structureName = NULL;
  }
  if ( strnames && *strnames )
    structureName = strdup(strnames);

}

/******************************************************************************/
/**
\brief  ~ODataSource - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODataSource"

     ODataSource :: ~ODataSource ( )
{

  Reset();

}


