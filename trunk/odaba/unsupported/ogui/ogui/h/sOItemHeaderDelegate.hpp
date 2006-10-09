/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OItemHeaderDelegate

\brief    


\date     $Date: 2006/03/13 21:34:19,14 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OItemHeaderDelegate_HPP
#define   OItemHeaderDelegate_HPP

class     OItemHeaderDelegate;

class     OHeaderView;
class  OItemHeaderDelegate :public QItemDelegate
{
protected  :         OHeaderView                                 *header;                                                    

public     :
                     OHeaderView                                 *get_header() { return(header); }
public     :                                                             OItemHeaderDelegate (OHeaderView *pOHeaderView );
public     : virtual                             QSize sizeHint (const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const;
public     : virtual                                                     ~OItemHeaderDelegate ( );
};

#endif
