/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODControlEventHandler

\brief    


\date     $Date: 2006/03/13 21:33:51,43 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODControlEventHandler_HPP
#define   ODControlEventHandler_HPP

class     ODControlEventHandler;

class     ODControl;
class  ODControlEventHandler :public vcls
{
protected  :         ODControl                                   *control;                                                   //

public     :
public     :                                                             ODControlEventHandler (ODControl *pODControl );
public     :                                                             ~ODControlEventHandler ( );
};

#endif
