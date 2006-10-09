/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OSDate

\brief    


\date     $Date: 2006/06/20 12:55:04,20 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSDate"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOSDate.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSDate :: CastPointer (char *typenames )
{

  return (   !typenames                      ? NULL
           : !strcmp(typenames,"OSDate")     ? this
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

int32 OSDate :: CreateInstance (void **instptrp )
{

  *instptrp = new OSDate();
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

char *OSDate :: GetObjectType ( )
{

  return("OSDate");

}

/******************************************************************************/
/**
\brief  OSDate - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSDate"

     OSDate :: OSDate ( )
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
#define    MOD_ID  "OSDate"

     OSDate :: OSDate (OStyle bcOStyle )
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

void OSDate :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSDate - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSDate"

     OSDate :: ~OSDate ( )
{

  if ( !Deleting() )
    Reset();

}


