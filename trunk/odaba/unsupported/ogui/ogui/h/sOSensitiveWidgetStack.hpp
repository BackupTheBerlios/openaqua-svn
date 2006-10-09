/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSensitiveWidgetStack

\brief    


\date     $Date: 2006/03/13 21:34:36,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSensitiveWidgetStack_HPP
#define   OSensitiveWidgetStack_HPP

class     OSensitiveWidgetStack;

class     OSlotRouter;
class  OSensitiveWidgetStack :public QWidgetStack
{
protected  :         QIntDict<OSlotRouter>                        routers;                                                   

public     :
public     :         OGUI7ImpExp                                         OSensitiveWidgetStack (QWidget *pQWidget );
public     :         OGUI7ImpExp                 OSlotRouter *RegisterWidget (int iID );
public     :         OGUI7ImpExp                 void Select (int iID );
};

#endif
