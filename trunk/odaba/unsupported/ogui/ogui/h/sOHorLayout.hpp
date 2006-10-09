/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OHorLayout

\brief    


\date     $Date: 2006/03/13 21:34:18,15 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OHorLayout_HPP
#define   OHorLayout_HPP

class     OHorLayout;

class  OHorLayout :public QHBoxLayout
{
protected  :         QHBoxLayout                                 *left;                                                      //
protected  :         QHBoxLayout                                 *right;                                                     //

public     :
                     QHBoxLayout                                 *get_left() { return(left); }
                     QHBoxLayout                                 *get_right() { return(right); }
public     :                                                             OHorLayout (Qt::AlignmentFlag ver_align, int spacing_w=AUTO );
public     : virtual                                                     ~OHorLayout ( );
};

#endif
