/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    DActionList

\brief    


\date     $Date: 2006/08/30 17:30:28,30 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DActionList_HPP
#define   DActionList_HPP

class     DActionList;

#ifndef   BTI_DAction_HPP
#define   BTI_DAction_HPP
#include  <sDAction.hpp>
#include  <sBTI.h>
#endif
#include  <sBinTree.hpp>
class  DActionList :public BTI(DAction)
{
protected  :         BinTree                                      action_tree;                                               // 

public     :
                     BinTree                                     &get_action_tree() { return(action_tree); }
public     :                                             DActionList ( );
public     :                                             ~DActionList ( );
};

#endif
