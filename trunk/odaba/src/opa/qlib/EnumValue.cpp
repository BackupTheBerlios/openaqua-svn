/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    EnumValue



\date     $Date: 2006/04/07 17:01:07,32 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EnumValue"

#include  <popa7.h>
#include  <sPropertyHandle.hpp>
#include  <sEnumValue.hpp>


/******************************************************************************/
/**
\brief  Initialize

-------------------------------------------------------------------------------
\brief  i00


\param  val_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void EnumValue :: Initialize (PropertyHandle *val_ph )
{
  char                *string;
  code         = val_ph->GetInt("__AUTOIDENT");
  memcpy(name,val_ph->GetArea("sys_ident"),ID_SIZE); 

  if ( string = val_ph->GetString("type") )
    basetype = strdup(string);
  
  PH(val_ph,resource_ref)
  if ( resource_ref.Get(0) ) 
  {
    PH(&resource_ref,description)
    if ( description.Get(0) ) 
    {
      if ( string = description.GetString("definition.label") )
        display_name = strdup(string);
      if ( string = description.GetString("definition.definition.title") )
        title  = strdup(string);
    }
  }

}

/******************************************************************************/
/**
\brief  i01


\param  cval - 
\param  cstring
\param  btype
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void EnumValue :: Initialize (int16 cval, char *cstring, char *btype )
{

  code = cval;
  gvtxstb(name,cstring ? cstring : "",ID_SIZE); 

  if ( btype && *btype )
    basetype = strdup(btype);
  


}

/******************************************************************************/
/**
\brief  ReleaseEntry


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

void EnumValue :: ReleaseEntry ( )
{

  if ( display_name) 
    free(display_name);
  display_name = NULL;
  
  if ( title ) 
    free(title);
  title = NULL;
  
  if ( basetype ) 
    free(basetype);
  basetype = NULL;
  


}


