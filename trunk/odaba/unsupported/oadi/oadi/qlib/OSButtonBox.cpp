/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OSButtonBox

\brief    


\date     $Date: 2006/06/20 12:55:32,15 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSButtonBox"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOSButtonBox.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSButtonBox :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"OSOSButtonBox") ? this
                                                : OStyle::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance - 


\return rc - 

\param  instptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OSButtonBox :: CreateInstance (void **instptrp )
{

  *instptrp = new OSButtonBox();
  return(0);

}

/******************************************************************************/
/**
\brief  GetObjectType - 


\return typenames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectType"

char *OSButtonBox :: GetObjectType ( )
{

  return("OSOSButtonBox");

}

/******************************************************************************/
/**
\brief  OSButtonBox - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSButtonBox"

     OSButtonBox :: OSButtonBox ( )
                     : OStyle ()
{



}

/******************************************************************************/
/**
\brief  i01 - 


\param  bcOStyle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSButtonBox"

     OSButtonBox :: OSButtonBox (OStyle bcOStyle )
                     : OStyle (bcOStyle)
{

/*
  "OSCheckBox("
  + ADK_Style::Generate()
  + ")";
*/

}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSButtonBox :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSButtonBox - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSButtonBox"

     OSButtonBox :: ~OSButtonBox ( )
{

  if ( !Deleting() )
    Reset();

}


