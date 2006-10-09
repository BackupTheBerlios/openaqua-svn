/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OToolBarList

\brief    


\date     $Date: 2006/03/13 21:34:46,98 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OToolBarList_HPP
#define   OToolBarList_HPP

class     OToolBarList;

class     OToolBar;
class  OToolBarList :public QList<OToolBar *>
{

public     :
public     :                                     OToolBar *FindToolBar (OEHAction *action );
public     :                                     OToolBar *Hide ( );
public     :                                                             OToolBarList ( );
public     :                                     OToolBar *Show ( );
public     :                                                             ~OToolBarList ( );
};

#endif
