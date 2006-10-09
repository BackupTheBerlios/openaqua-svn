/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    ExtentListEntry

\brief    


\date     $Date: 2006/08/26 11:51:50,62 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExtentListEntry"

#include  <pdefault.h>
#include  <sEB_Number.hpp>
#include  <sExtentListEntry.hpp>


/******************************************************************************/
/**
\brief  get_extent_name - 



\return extname - Extent name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_extent_name"

char *ExtentListEntry :: get_extent_name ( )
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

int16 ExtentListEntry :: get_main_base ( )
{


  return(((EB_Number *)&identity)->GetMBIdent());
}


