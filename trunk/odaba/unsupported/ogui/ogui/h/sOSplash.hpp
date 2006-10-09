/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OSplash



\date     $Date: 2006/04/26 11:30:25,95 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSplash_HPP
#define   OSplash_HPP

class     OSplash;

class  OSplash :public QSplashScreen
{

public     :
public     :         OGUIImpExp                  void Message (QString qsText );
public     :         OGUIImpExp                                          OSplash (QString qsText );
public     :         OGUIImpExp                  void Wait (QWidget *pQWidget );
public     : virtual OGUIImpExp                                          ~OSplash ( );
};

#endif
