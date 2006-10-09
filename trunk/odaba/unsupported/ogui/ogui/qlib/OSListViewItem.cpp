/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSListViewItem

\brief    OSListViewItem
          When QListViewItem knows to less
          and 
          OListViewItem does to much
          you may consider using this class

\date     $Date: 2006/03/13 21:36:13,01 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSListViewItem"

#include  <pogui7.h>
#include  <sOSListViewItem.hpp>


/******************************************************************************/
/**
\brief  GetQListViewItem - 


\return pQTreeWidgetItem -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetQListViewItem"

QTreeWidgetItem *OSListViewItem :: GetQListViewItem ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  OSListViewItem - 


-------------------------------------------------------------------------------
\brief  i0


\param  pQTreeWidget -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSListViewItem"

                        OSListViewItem :: OSListViewItem (QTreeWidget *pQTreeWidget )
                     : QTreeWidgetItem (pQTreeWidget),
ItemData (0)
{



}

/******************************************************************************/
/**
\brief  i01


\param  pQTreeWidgetItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSListViewItem"

                        OSListViewItem :: OSListViewItem (QTreeWidgetItem *pQTreeWidgetItem )
                     : QTreeWidgetItem (pQTreeWidgetItem),
ItemData (0)
{



}

/******************************************************************************/
/**
\brief  ~OSListViewItem - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSListViewItem"

                        OSListViewItem :: ~OSListViewItem ( )
{



}


