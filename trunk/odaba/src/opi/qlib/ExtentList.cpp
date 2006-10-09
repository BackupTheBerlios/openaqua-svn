/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExtentList

\brief    


\date     $Date: 2006/03/12 19:10:29,37 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExtentList"

#include  <pdefault.h>
#include  <sEB_Number.hpp>
#include  <sExtentList.hpp>


/******************************************************************************/
/**
\brief  get_extent_name - 


\return extname - Extent name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_extent_name"

char *ExtentList :: get_extent_name ( )
{


  return(extent_name);
}

/******************************************************************************/
/**
\brief  get_main_base - 


\return mbnumber - Main base number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_main_base"

int16 ExtentList :: get_main_base ( )
{


  return(((EB_Number *)&identity)->GetMBIdent());
}


