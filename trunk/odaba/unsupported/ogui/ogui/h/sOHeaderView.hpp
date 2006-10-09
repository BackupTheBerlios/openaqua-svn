/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OHeaderView

\brief    


\date     $Date: 2006/03/13 21:34:17,98 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OHeaderView_HPP
#define   OHeaderView_HPP

class     OHeaderView;

class     OListCtl;
class  OHeaderView :public QHeaderView
{
protected  :         OListCtl                                    *list_control;                                              
protected  :         int                                          size;                                                      
protected  :         logical                                      minimized;                                                 

public     :
                     OListCtl                                    *get_list_control() { return(list_control); }
                     int                                         &get_size() { return(size); }
                     logical                                      get_minimized() { return(minimized); }
public     :                                     void Minimize ( );
public     :                                                             OHeaderView (OListCtl *pOListCtl, Qt::Orientation qt_orientation, QHeaderView::ResizeMode qt_resize_mode );
public     :                                     void SetSize (int siz );
public     : virtual                             QSize sizeHint ( ) const;
public     :                                     int sizeHintForRowx (int row ) const;
public     :                                                             ~OHeaderView ( );
};

#endif
