/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODeferrer

\brief    


\date     $Date: 2006/03/13 21:34:05,04 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODeferrer_HPP
#define   ODeferrer_HPP

class     ODeferrer;

class  ODeferrer :public QObject
{
protected  :         int                                          timerid;                                                   //

public     :
public     : virtual OGUI7ImpExp                 void Fire ( );
public     :         OGUI7ImpExp                                         ODeferrer (QObject *pQObject );
public     :         OGUI7ImpExp                 void timerEvent (QTimerEvent *pQTimerEvent );
};

#endif
