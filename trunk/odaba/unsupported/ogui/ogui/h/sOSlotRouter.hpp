/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSlotRouter

\brief    


\date     $Date: 2006/03/13 21:34:39,81 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSlotRouter_HPP
#define   OSlotRouter_HPP

class     OSlotRouter;

class  OSlotRouter :public QObject
{
protected  :                                                      Q_OBJECT;                                                  //

public     :
public     :         OGUI7ImpExp                                         OSlotRouter (QObject *pQObject_NULL=NULL );
public     :                                     public slots: void xFire ( );
};

#endif
