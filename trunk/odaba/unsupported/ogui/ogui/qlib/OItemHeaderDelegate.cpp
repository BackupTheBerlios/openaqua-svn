/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OItemHeaderDelegate

\brief    


\date     $Date: 2006/03/13 21:35:55,82 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OItemHeaderDelegate"

#include  <pogui7.h>
#include  <sOHeaderView.hpp>
#include  <sOItemHeaderDelegate.hpp>


/******************************************************************************/
/**
\brief  OItemHeaderDelegate - 



\param  pOHeaderView -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OItemHeaderDelegate"

                        OItemHeaderDelegate :: OItemHeaderDelegate (OHeaderView *pOHeaderView )
                     : QItemDelegate (pOHeaderView),
  header(pOHeaderView)
{



}

/******************************************************************************/
/**
\brief  sizeHint - 


\return size -

\param  crQStyleOptionViewItem -
\param  model_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sizeHint"

QSize OItemHeaderDelegate :: sizeHint (const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const
{
  QSize    qsize = QItemDelegate::sizeHint(crQStyleOptionViewItem,model_index);
  if ( header->orientation() == Qt::Horizontal )  
    qsize.setHeight(1);    

  return(qsize);
}

/******************************************************************************/
/**
\brief  ~OItemHeaderDelegate - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OItemHeaderDelegate"

                        OItemHeaderDelegate :: ~OItemHeaderDelegate ( )
{



}


