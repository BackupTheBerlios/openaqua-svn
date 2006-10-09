/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OHighlightRule



\date     $Date: 2006/04/28 16:47:58,35 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OHighlightRule"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOFont_.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOHighlightRule.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OHighlightRule :: CastPointer (char *typenames )
{

  return (   !typenames                          ? NULL
           : !strcmp(typenames,"OHighlightRule") ? this
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

int32 OHighlightRule :: CreateInstance (void **instptrp )
{
  *instptrp = new OHighlightRule();
  return(0);
}

/******************************************************************************/
/**
\brief  OHighlightRule

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OHighlightRule"

     OHighlightRule :: OHighlightRule ( )
                     : OResource (),
  font(NULL),
  syntax_classes()
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOResource
\param  pOFont_
\param  syntax_classes
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OHighlightRule"

     OHighlightRule :: OHighlightRule (OResource bcOResource, OFont_ *pOFont_, DLL(OSyntaxClass) *syntax_classes )
                     : OResource (bcOResource),
  font(pOFont_),
  syntax_classes()
{
  OSyntaxClass *sc;
BEGINSEQ
  if(!syntax_classes)                                ERROR
  syntax_classes->GoTop();
  while(sc = syntax_classes->GetNext())
    this->syntax_classes.AddTail(sc);
/*
  "OHighlightRule("
  +        ADK_Resource::Generate()
  + ", " + font.Generate()
  + ", " + syntax_classes.GenerateList()
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

logical OHighlightRule :: Read (PropertyHandle *ph )
{
  OSyntaxClass           *synclass;
  int32                   indx0 = 0;
  logical                 term = NO;
  OResource::Read(ph);
  
  font = CACHE_READ(ph,"font",OFont_);
  
  ph = ph->GPH("syntax_classes");
  while ( ph->Get(indx0++) )
    if ( synclass = CACHE_READ(ph,NULL,OSyntaxClass) )
      syntax_classes.AddTail(synclass);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OHighlightRule :: Reset ( )
{
  OResource       *resource;
  font->Release();
  font = NULL;
  
  while ( resource = syntax_classes.RemoveHead() )
    resource->Release();
    
  OResource::Reset();

}

/******************************************************************************/
/**
\brief  ~OHighlightRule


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OHighlightRule"

     OHighlightRule :: ~OHighlightRule ( )
{
  if ( !Deleting() )
    Reset();
}


