/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OHighlighter



\date     $Date: 2006/04/28 16:46:59,29 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OHighlighter"

#include  <poadi.h>
#include  <cmacros.h>
#ifndef   DLL_OHighlightRule_HPP
#define   DLL_OHighlightRule_HPP
#include  <sOHighlightRule.hpp>
#include  <sDLL.h>
#endif
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOHighlighter.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OHighlighter :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"OHighlighter") ? this
                                               : OResource::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OHighlighter :: CreateInstance (void **instptrp )
{
  *instptrp = new OHighlighter();
  return(0);
}

/******************************************************************************/
/**
\brief  OHighlighter

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OHighlighter"

     OHighlighter :: OHighlighter ( )
                     : OResource (),
  rules()
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOResource
\param  rules
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OHighlighter"

     OHighlighter :: OHighlighter (OResource bcOResource, DLL(OHighlightRule) *rules )
                     : OResource (bcOResource),
  rules()
{
  OHighlightRule *rule;
BEGINSEQ
  if(!rules)                                         ERROR
  rules->GoTop();
  while(rule = rules->GetNext())
    this->rules.AddTail(rule);
/*
  "OHighlighter("
  + ADK_Resource::Generate()
  + ", " + rules.GenerateList("rules")
  + ")";
*/
RECOVER
ENDSEQ
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

logical OHighlighter :: Read (PropertyHandle *ph )
{
  OHighlightRule         *rule;
  int32                   indx0 = 0;
  logical                 term = NO;
  OResource::Read(ph);
  
  ph = ph->GPH("rules");
  while ( ph->Get(indx0++) )
    if ( rule = CACHE_READ(ph,NULL,OHighlightRule) )
      rules.AddTail(rule);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OHighlighter :: Reset ( )
{
  OResource       *resource;
  while ( resource = rules.RemoveHead() )
    resource->Release();
    
  OResource::Reset();

}

/******************************************************************************/
/**
\brief  ~OHighlighter


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OHighlighter"

     OHighlighter :: ~OHighlighter ( )
{
  if ( !Deleting() )
    Reset();
}


