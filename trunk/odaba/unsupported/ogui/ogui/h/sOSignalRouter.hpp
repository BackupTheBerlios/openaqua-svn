/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSignalRouter

\brief    


\date     $Date: 2006/03/13 21:34:37,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSignalRouter_HPP
#define   OSignalRouter_HPP

class     OSignalRouter;

class  OSignalRouter :public QObject
{
protected  :                                                      Q_OBJECT;                                                  

public     :
public     :                                     signals: void Fire ( );
public     :                                                             OSignalRouter (QObject *pQObject_NULL=NULL );
public     :                                     void FireFire ( ){

  Fire();

}

};

#endif
