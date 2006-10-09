/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OVerLayout

\brief    


\date     $Date: 2006/03/13 21:34:50,64 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OVerLayout_HPP
#define   OVerLayout_HPP

class     OVerLayout;

class  OVerLayout :public QVBoxLayout
{
protected  :         QVBoxLayout                                 *top;                                                       
protected  :         QVBoxLayout                                 *bottom;                                                    

public     :
                     QVBoxLayout                                 *get_top() { return(top); }
                     QVBoxLayout                                 *get_bottom() { return(bottom); }
public     :                                                             OVerLayout (Qt::AlignmentFlag hor_align, int spacing_w=AUTO );
public     : virtual                                                     ~OVerLayout ( );
};

#endif
