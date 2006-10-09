/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    ENUM_Value



\date     $Date: 2006/04/13 15:07:48,32 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ENUM_Value"

#include  <pops7.h>
#include  <sENUM_Value.hpp>


/******************************************************************************/
/**
\brief  Clear


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void ENUM_Value :: Clear ( )
{

  type         = NULL;
  display_name = NULL;
  title        = NULL;
  description  = NULL;

}

/******************************************************************************/
/**
\brief  CreateSubList

\return term

\param  parent_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubList"

logical ENUM_Value :: CreateSubList (PropertyHandle *parent_ph )
{

  logical         term = NO;
BEGINSEQ
  if ( !parent_ph )                                 ERROR
  
  if ( !values.IsValid() )
    if ( values.Open(parent_ph,"values") )          ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ENUM_Value

-------------------------------------------------------------------------------
\brief  i0


\param  cval
\param  cname
\param  btype
\param  clabel
\param  ctitle
\param  cdescr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ENUM_Value"

                        ENUM_Value :: ENUM_Value (int32 cval, char *cname, char *btype, char *clabel, char *ctitle, char *cdescr )
                     :   id(0),
  code(0),
  type(NULL),
  display_name(NULL),
  title(NULL),
  description(NULL),
  values()
{

  Initialize(cval,cname,btype,clabel,ctitle,cdescr);

}

/******************************************************************************/
/**
\brief  i01


\param  val_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ENUM_Value"

                        ENUM_Value :: ENUM_Value (PropertyHandle *val_ph )
                     :   id(0),
  code(0),
  type(NULL),
  display_name(NULL),
  title(NULL),
  description(NULL),
  values()
{

  memset(name,0,sizeof(name));
  Initialize(val_ph);

}

/******************************************************************************/
/**
\brief  i02


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ENUM_Value"

                        ENUM_Value :: ENUM_Value ( )
                     :   id(0),
  code(0),
  type(NULL),
  display_name(NULL),
  title(NULL),
  description(NULL),
  values()
{

  memset(name,0,sizeof(name));



}

/******************************************************************************/
/**
\brief  Initialize

\return term
-------------------------------------------------------------------------------
\brief  i00


\param  val_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ENUM_Value :: Initialize (PropertyHandle *val_ph )
{
  char        *string;
  logical     term = NO;
  id           = val_ph->GetID();
  code         = val_ph->GetInt("__AUTOIDENT");
  memcpy(name,val_ph->GetArea("sys_ident"),ID_SIZE); 

  if ( string = val_ph->GetString("type") )
    type = strdup(string);
  
  PH(val_ph,resource_ref)
  if ( resource_ref.Get(0) ) 
  {
    PH(&resource_ref,description)
    if ( description.Get(0) ) 
    {
      if ( string = description.GetString("definition.label") )
        display_name = strdup(string);
      if ( string = description.GetString("definition.name") )
        title  = strdup(string);
      if ( string = description.GetString("definition.definition.characteristic") )
        title  = strdup(string);
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  cval
\param  cname
\param  btype
\param  clabel
\param  ctitle
\param  cdescr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ENUM_Value :: Initialize (int32 cval, char *cname, char *btype, char *clabel, char *ctitle, char *cdescr )
{
  logical   term = NO;
  code = cval;
  gvtxstb(name,cname ? cname : "",ID_SIZE); 

  if ( btype && *btype )
    type = strdup(btype);
  
  if ( clabel && *clabel )
    display_name = strdup(clabel);

  if ( ctitle && *ctitle )
    title = strdup(ctitle);

  if ( cdescr && *cdescr )
    description = strdup(cdescr);

  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseEntry

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

logical ENUM_Value :: ReleaseEntry ( )
{
  logical     term = NO;
  if ( display_name) 
    free(display_name);
  display_name = NULL;
  
  if ( title ) 
    free(title);
  title = NULL;
  
  if ( type ) 
    free(type);
  type = NULL;
  
  if ( description ) 
    free(description);
  description = NULL;
  

  return(term);
}

/******************************************************************************/
/**
\brief  ~ENUM_Value


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ENUM_Value"

                        ENUM_Value :: ~ENUM_Value ( )
{

  ReleaseEntry();

}


