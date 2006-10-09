/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OResource



\date     $Date: 2006/05/01 18:48:11,81 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OResource"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sPropertyHandle.hpp>
#include  <sResourceCache.hpp>
#include  <sTProjectManager.hpp>
#include  <sOResource.hpp>

int32 ores_count = 0;
int32 ores_total = 0;

/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OResource :: CastPointer (char *typenames )
{
  return (   !typenames                     ? NULL
           : !strcmp(typenames,"OResource") ? this
                                            : NULL );

}

/******************************************************************************/
/**
\brief  Deleting

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deleting"

logical OResource :: Deleting ( )
{
  logical                 cond = invalid == -1 ? YES : NO;
  invalid = -1;
  return(cond);
}

/******************************************************************************/
/**
\brief  Invalidate


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Invalidate"

void OResource :: Invalidate ( )
{

  invalid = YES;

}

/******************************************************************************/
/**
\brief  OResource

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OResource"

     OResource :: OResource ( )
                     : OPersistent (),
ObjectInfo(),
  use_count(0),
  in_cache(NO),
  invalid(YES)

{

  memset(sys_ident,0,sizeof(sys_ident));
  memset(contextClass,0,sizeof(contextClass));

ores_count++;
ores_total++;
}

/******************************************************************************/
/**
\brief  i01


\param  bcOPersistent
\param  ssys_ident
\param  scontextClass
\param  ires_id
\param  iuse_count
\param  iin_cache
\param  iinvalid
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OResource"

     OResource :: OResource (OPersistent bcOPersistent, char *ssys_ident, char *scontextClass, int32 ires_id, int32 iuse_count, int8 iin_cache, int8 iinvalid )
                     : OPersistent (res_id),
ObjectInfo(),
  res_id(ires_id),
  use_count(iuse_count),
  in_cache(iin_cache),
  invalid(iinvalid)

{
  memset(sys_ident,0,sizeof(sys_ident));
  memset(contextClass,0,sizeof(contextClass));
  // bad things such [mem|str]copys... history forces us
  // try to build a version that uses std::string
  // it should be possible..
  strncpy(sys_ident,ssys_ident,sizeof(sys_ident)-1);
  strncpy(contextClass,scontextClass,sizeof(contextClass)-1);
  /*
   "OResource("
   +        ADK_Persistent::Generate()
   + ", " + sys_ident
?   + ", " + ::SDB_Resoucre.resource_ref.context_class.smceclas.sys_ident || NULL
?   + ", " + ::SDB_Resoucre.resource_ref.__AUTOIDENT || 0
   + ", " + ?? use_count
   + ", " + ?? in_cache
   + ", NO" // invalid
   + ")";
  */
}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OResource :: Read (PropertyHandle *ph )
{
  PropertyHandle   *rr;
  PropertyHandle   *ep;
  logical           term = NO;
  OPersistent::Read(ph);
  
  strcpy(sys_ident,ph->GetString("sys_ident"));
  
  if ( ph->Inherits("SDB_Resource") )
    if ( rr = PHREF(ph->GPH("resource_ref")) )
      if ( ep = PHREF(rr->GPH("context_class")) )
      {
        res_id = rr->GetInt("__AUTOIDENT");
        if ( ep = PHREF(ep->GPH("smceclas")) )
          strcpy(contextClass,ep->GetString("sys_ident"));
        else
          memset(contextClass,0,sizeof(contextClass));
      }    
      
  invalid = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  Release


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

void OResource :: Release ( )
{

  if ( this )
  {
    if ( in_cache )
    {
      if ( --use_count <= 0 )
      {
        if ( invalid == YES )
          TProjectManager::TPM->Cache(in_cache)->DeleteEntry(this);
        else
          use_count = 0;
      }
    }
    else if ( !Deleting() )
      delete this;
  }

}

/******************************************************************************/
/**
\brief  Reserve


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

void OResource :: Reserve ( )
{

  if ( this && in_cache )
    use_count++;

}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OResource :: Reset ( )
{

  memset(sys_ident,0,sizeof(sys_ident));
  memset(contextClass,0,sizeof(contextClass));
  
  res_id  = 0;
  if ( !invalid )
    invalid = YES;
  
  if ( !in_cache )
    Release();


}

/******************************************************************************/
/**
\brief  Resource

\return pOResource

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Resource"

OResource *OResource :: Resource ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  operator=

\return rOResource

\param  rOResource
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

OResource &OResource :: operator= (OResource &rOResource )
{

  *(OPersistent *)this = rOResource;
  strcpy(sys_ident,rOResource.get_sys_ident());
  strcpy(contextClass,rOResource.get_contextClass());
  res_id = rOResource.get_res_id();

// in_cache, invalid und use_count dürfen nicht überschrieben werden !!!
  return(*this);
}

/******************************************************************************/
/**
\brief  set_in_cache


\param  cache_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_in_cache"

void OResource :: set_in_cache (logical cache_opt )
{

  in_cache = cache_opt;

}

/******************************************************************************/
/**
\brief  set_name


\param  name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_name"

void OResource :: set_name (char *name )
{
  if ( name )
    strncpy(sys_ident,name,ID_SIZE);
  else
    *sys_ident = 0;

}

/******************************************************************************/
/**
\brief  set_res_id


\param  resource_id
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_res_id"

void OResource :: set_res_id (int resource_id )
{
  res_id = resource_id;

}

/******************************************************************************/
/**
\brief  ~OResource

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OResource"

     OResource :: ~OResource ( )
{

BEGINSEQ
if ( in_cache )
OADIIERR(99)

  if ( !Deleting() )
    Reset();
RECOVER

ENDSEQ
ores_count--;
}


