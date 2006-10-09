/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OActionList



\date     $Date: 2006/05/02 14:22:37,23 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OActionList_HPP
#define   OActionList_HPP

class     OActionList;

class     DPixmap;
class     ODataWidget;
class     OEHAction;
class     OIconSet;
class  OActionList :public QList<QAction *>
{

public     :
public     :                                        void Clear ( );
public     :                                        void DeleteOEHActions ( );
public     :                                        OEHAction *FindAction (char *act_names, char *loid, logical on_top_w=YES );
public     :                                        OEHAction *FindAction (OEHAction *pOEHAction );
public     :                                        OEHAction *FindNextAction (char *act_names, char *loid, OEHAction *pOEHAction, logical on_top_w=YES );
public     :                                        OEHAction *FirstAction ( );
public     : static                                 OEHAction *__cdecl GetAction (QAction *pQAction );
public     :                                        logical IsActionDisabled (char *act_names, char *loid );
public     :                                        logical IsActionGrouped (char *act_names, char *loid );
public     :                                        logical IsActionSeparated (char *act_names, char *loid );
public     :                                        logical IsActionToggled (char *act_names, char *loid );
public     :                                        logical IsActionVisible (char *act_names, char *loid );
public     :                                             OActionList (QList<QAction *> *pQListQAction );
public     :                                             OActionList ( );
public     :                                             OActionList (const OActionList &pOActionList );
public     :                                             OActionList (const QList<QAction *> &rQListQAction );
public     :                                        logical RemoveAction (OEHAction *pOEHAction );
public     :                                        logical SetActionDisabled (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionGrouped (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionIcon (char *act_names, char *loid, char *text, OIconSet *pOIcon );
public     :                                        logical SetActionSeparated (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionShortcut (char *act_names, char *loid, char *string );
public     :                                        logical SetActionText (char *act_names, char *loid, char *text, char *tip, char *status_tip, char *what );
public     :                                        logical SetActionToggled (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionVisible (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionWidget (char *act_names, char *loid, ODataWidget *pODataWidget );
};

#endif
