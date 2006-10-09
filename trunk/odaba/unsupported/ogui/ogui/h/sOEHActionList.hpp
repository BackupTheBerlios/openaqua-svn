/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHActionList

\brief    


\date     $Date: 2006/03/13 21:34:09,46 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHActionList_HPP
#define   OEHActionList_HPP

class     OEHActionList;

#ifndef   DLL_OEHAction_HPP
#define   DLL_OEHAction_HPP
#include  <sOEHAction.hpp>
#include  <sDLL.h>
#endif
class     OEHAction;
class  OEHActionList :public QList<OEHAction *>
{

public     :
public     :                                     logical AddAction (OEHAction *action );
public     :                                     OEHAction *FindAction (char *act_names, char *loid, logical on_top_w=YES );
public     :                                                             OEHActionList ( );
public     :                                     logical RemoveAction (OEHAction *pOEHAction );
public     :                                     void SetIcons ( );
public     :                                     logical SetupGroup (QActionGroup *pQActionGroup );
};

#endif
