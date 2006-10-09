/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSButtonGroup



\date     $Date: 2006/04/28 16:53:19,79 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSButtonGroup"

#include  <poadi.h>
#include  <sPropertyHandle.hpp>
#include  <sOSButtonGroup.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSButtonGroup :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"OSButtonGroup") ? this
                                                : OStyle::CastPointer(typenames) );

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

int32 OSButtonGroup :: CreateInstance (void **instptrp )
{
  *instptrp = new OSButtonGroup();
  return(0);
}

/******************************************************************************/
/**
\brief  GetObjectType

\return typenames

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectType"

char *OSButtonGroup :: GetObjectType ( )
{

  return("OSButtonGroup");

}

/******************************************************************************/
/**
\brief  OSButtonGroup

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSButtonGroup"

     OSButtonGroup :: OSButtonGroup ( )
                     : OStyle (),
  vertical(NO),
  exclusive(NO)
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  vertical
\param  exclusive
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSButtonGroup"

     OSButtonGroup :: OSButtonGroup (OStyle bcOStyle, logical vertical, logical exclusive )
                     : OStyle (bcOStyle),
  vertical(vertical),
  exclusive(exclusive)
{
/*
  "OSButtonGroup("
  +        ADK_Style::Generate()
  + ", " + vertical
  + ", " + exclusive
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

logical OSButtonGroup :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  vertical = ph->GetInt("vertical");
  exclusive = ph->GetInt("exclusive");

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSButtonGroup :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSButtonGroup


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSButtonGroup"

     OSButtonGroup :: ~OSButtonGroup ( )
{

  if ( !Deleting() )
    Reset();

}


