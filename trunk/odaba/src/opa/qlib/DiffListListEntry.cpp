/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DiffListListEntry

\brief    


\date     $Date: 2006/03/12 19:17:23,46 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DiffListListEntry"

#include  <popa7.h>
#include  <sDifferenceList.hpp>
#include  <sDiffListListEntry.hpp>


/******************************************************************************/
/**
\brief  DiffListListEntry - 



\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiffListListEntry"

                        DiffListListEntry :: DiffListListEntry (DifferenceList *dlist_ptr )
                     : entnr(dlist_ptr->GetEBINumber()),
  diff_list(dlist_ptr)
{



}

/******************************************************************************/
/**
\brief  get_diff_list - 


\return dlist_ptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_diff_list"

DifferenceList *DiffListListEntry :: get_diff_list ( )
{

  return ( this ? diff_list : NULL );

}


