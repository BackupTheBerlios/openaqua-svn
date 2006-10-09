/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSItemStatic

\brief    


\date     $Date: 2006/03/13 21:35:28,06 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSItemStatic"

#include  <pogui7.h>
#include  <sODSItem.hpp>
#include  <sODSItemStatic.hpp>


/******************************************************************************/
/**
\brief  Deinit - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinit"

logical ODSItemStatic :: Deinit ( )
{
  logical                 term = NO;
  delete root;
  root = NULL;

  return(term);
}

/******************************************************************************/
/**
\brief  Init - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

logical ODSItemStatic :: Init ( )
{
  logical                 term = NO;
  root = new ODSItem();
  root->Ref();
  return(term);
}

/******************************************************************************/
/**
\brief  ODSItemStatic - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItemStatic"

                        ODSItemStatic :: ODSItemStatic ( )
                     :   root(NULL),
  watcher(),
  items(),
  extentCache()
{



}

/******************************************************************************/
/**
\brief  checkItems - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "checkItems"

void __cdecl ODSItemStatic :: checkItems ( )
{

  ODSItem::checkItems();


}

/******************************************************************************/
/**
\brief  remove - 


\return term -

\param  pODSItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "remove"

logical ODSItemStatic :: remove (ODSItem *pODSItem )
{
  std::vector<ODSItem*>::iterator  it;
  logical                          term = NO;
BEGINSEQ
  for ( it = items.begin(); it != items.end(); it++ )
    if( (*it) == pODSItem )
    {
      items.erase(it);
      LEAVESEQ
    }
    
  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ODSItemStatic - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODSItemStatic"

                        ODSItemStatic :: ~ODSItemStatic ( )
{

  Deinit();

}


