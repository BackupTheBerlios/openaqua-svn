/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OPixmap

\brief    


\date     $Date: 2006/03/13 21:34:29,46 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPixmap_HPP
#define   OPixmap_HPP

class     OPixmap;

#include  <sDPixmap.hpp>
class  OPixmap :public QPixmap
{
protected  :         char                                         name[40];                                                  //
public     :         logical                                      use_for_normal;                                            //
public     :         logical                                      use_for_active;                                            //
public     :         logical                                      use_for_disabled;                                          //

public     :
                     char                                        *get_name() { return(name); }
public     :                                     void FromDPixmap (DPixmap &rDPixmap );
public     :                                                             OPixmap ( );
public     :                                                             OPixmap (DPixmap &rDPixmap );
public     :                                                             OPixmap (OPixmap &rOPixmap );
public     :                                                             ~OPixmap ( );
};

#endif
