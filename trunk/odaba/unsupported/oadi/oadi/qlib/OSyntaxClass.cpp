/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSyntaxClass



\date     $Date: 2006/04/28 16:53:50,78 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSyntaxClass"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOSyntaxClass.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSyntaxClass :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"OSyntaxClass") ? this
           : !strcmp(typenames,"DSyntaxClass") ? (DSyntaxClass *)this
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

int32 OSyntaxClass :: CreateInstance (void **instptrp )
{
  *instptrp = new OSyntaxClass();
  return(0);
}

/******************************************************************************/
/**
\brief  OSyntaxClass

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSyntaxClass"

     OSyntaxClass :: OSyntaxClass ( )
                     : OResource (),
DSyntaxClass ()
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOResource
\param  bcDSyntaxClass
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSyntaxClass"

     OSyntaxClass :: OSyntaxClass (OResource bcOResource, DSyntaxClass bcDSyntaxClass )
                     : OResource (bcOResource),
DSyntaxClass (bcDSyntaxClass)
{
/*
  "OSyntaxClass("
  + ADK_Resource::Generate()
  + expressions.GenerateList()
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

logical OSyntaxClass :: Read (PropertyHandle *ph )
{
  char                   *string;
  int32                   indx0 = 0;
  logical                 term = NO;
  OResource::Read(ph);

  strcpy(class_name,sys_ident);
  ph = ph->GPH("expressions");
  while ( ph->Get(indx0++) )
    if ( (string = ph->GetString("expression")) && *string )
      expressions.AddTail(strdup(string));

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSyntaxClass :: Reset ( )
{
  OResource       *resource;
  DSyntaxClass::Reset();
  OResource::Reset();
}

/******************************************************************************/
/**
\brief  ~OSyntaxClass


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSyntaxClass"

     OSyntaxClass :: ~OSyntaxClass ( )
{
  if ( !Deleting() )
    Reset();
}


