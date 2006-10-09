/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OSTime

\brief    


\date     $Date: 2006/06/20 12:55:14,26 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSTime"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOSTime.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSTime :: CastPointer (char *typenames )
{

  return (   !typenames                      ? NULL
           : !strcmp(typenames,"OSTime")     ? this
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

int32 OSTime :: CreateInstance (void **instptrp )
{

  *instptrp = new OSTime();
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

char *OSTime :: GetObjectType ( )
{

  return("OSTime");

}

/******************************************************************************/
/**
\brief  OSTime - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSTime"

     OSTime :: OSTime ( )
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
#define    MOD_ID  "OSTime"

     OSTime :: OSTime (OStyle bcOStyle )
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

void OSTime :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSTime - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSTime"

     OSTime :: ~OSTime ( )
{

  if ( !Deleting() )
    Reset();

}


