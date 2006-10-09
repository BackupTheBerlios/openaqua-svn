/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OAccel

\brief    


\date     $Date: 2006/03/13 21:33:44,01 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OAccel_HPP
#define   OAccel_HPP

class     OAccel;

class     OSlotRouter;
#include  <sOSlotRouterExtended.hpp>
class  OAccel :public QShortcut
{

public     :
public     :         OGUI7ImpExp                 void InitList (OSlotRouterExtended *pOSlotRouterE );
public     :         OGUI7ImpExp                 void InitMultiLine (OSlotRouterExtended *pOSlotRouterE );
public     :         OGUI7ImpExp                 void InitSingleLine (OSlotRouterExtended *pOSlotRouterE );
public     :                                                             OAccel (QWidget *pQWidget );
};

#endif
