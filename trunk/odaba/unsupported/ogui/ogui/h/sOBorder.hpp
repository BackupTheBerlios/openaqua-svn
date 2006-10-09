/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OBorder

\brief    


\date     $Date: 2006/03/13 21:33:44,87 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OBorder_HPP
#define   OBorder_HPP

class     OBorder;

class     DBorder;
class  OBorder
{
protected  :         QFrame::Shape                                type;                                                      //
protected  :         QFrame::Shadow                               shadow_type;                                               //
protected  :         int16                                        line_with;                                                 //
protected  :         int16                                        mid_line_with;                                             //

public     :
                     QFrame::Shape                               &get_type() { return(type); }
                     QFrame::Shadow                              &get_shadow_type() { return(shadow_type); }
                     int16                                        get_line_with() { return(line_with); }
                     int16                                        get_mid_line_with() { return(mid_line_with); }
public     :                                     void FromDBorder (DBorder *pDBorder );
public     :                                                             OBorder ( );
};

#endif
