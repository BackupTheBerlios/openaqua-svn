/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OIconSet

\brief    


\date     $Date: 2006/03/13 21:34:18,28 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OIconSet_HPP
#define   OIconSet_HPP

class     OIconSet;

class     DPixmap;
class  OIconSet :public QIcon
{

public     :
public     :                                                             OIconSet (DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled );
public     :                                                             OIconSet (QPixmap *pQPixmap_normal, QPixmap *pQPixmap_active, QPixmap *pQPixmap_disabled );
public     :                                                             OIconSet (std_string szName );
};

#endif
