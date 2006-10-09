/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSlotRouterExtended

\brief    


\date     $Date: 2006/03/13 21:34:40,96 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSlotRouterExtended_HPP
#define   OSlotRouterExtended_HPP

class     OSlotRouterExtended;

#include  <sOSlotRouter.hpp>
class  OSlotRouterExtended :public OSlotRouter
{
protected  :                                                      Q_OBJECT;                                                  //

public     :
public     :                                     public slots: void Append ( );
public     :                                     void Edit ( );
public     :                                                             OSlotRouterExtended (QObject *pQObject_NULL=NULL );
public     :                                     void doAppend ( );
public     :                                     void doEdit ( );
};

#endif
