/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OToolBar

\brief    
          --> GUIDELINE from chaunsee: (QT-Source)
          1.   Tool  Bars  should  contain only high-frequency functions.  Avoid
          putting  things  like  About  and  Exit  on a tool bar unless they are
          frequent functions.

          2.   All tool  bar buttons  must have  some keyboard access method (it
          can  be a menu or shortcut key or  a function in a dialog box that can
          be accessed through the keyboard).

          3.   Make  tool  bar  functions  as  efficient as possible (the common
          example  is to  Print in  Microsoft applications,  it doesn't bring up
          the Print dialog box, it prints immediately to the default printer).

          4.   Avoid turning tool bars into graphical  menu bars.  To me, a tool
          bar  should be efficient. Once you make almost all the items in a tool
          bar into graphical pull-down menus, you start to lose efficiency.

          5.   Make  sure  that  adjacent  icons are distinctive. There are some
          tool  bars where you  see a group  of 4-5 icons that represent related
          functions,  but they are so similar that you can't differentiate among
          them.
          These  tool  bars  are  often  a  poor  attempt  at  a  "common visual
          language".

          6.   Use any de facto standard icons of your platform (for windows use
          the  cut,  copy  and  paste  icons  provided  in  dev kits rather than
          designing your own).

          7.   Avoid  putting  a  highly  destructive  tool  bar  button (delete
          database)  by a safe, high-frequency button  (Find) -- this will yield
          1-0ff errors).

          8.   Tooltips  in  many  Microsoft  products simply reiterate the menu
          text  even  when  that  is  not  explanatory.   Consider  making  your
          tooltips  slightly more verbose and explanatory than the corresponding
          menu item.

          9.   Keep  the  tool  bar  as  stable  as  possible  when you click on
          different
          objects.  Consider  disabling  tool  bar  buttons  if they are used in
          most, but not all contexts.

          10.   If you have multiple tool  bars (like the Microsoft MMC snap-ins
          have),  put the most stable  tool bar to at  the left with less stable
          ones  to the right. This arrangement (stable to less stable) makes the
          tool bar somewhat more predictable.

          11.   Keep a single tool  bar to fewer than  20 items divided into 4-7
          groups of items.

\date     $Date: 2006/06/22 17:09:33,67 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OToolBar"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHActionList.hpp>
#include  <sOPopupMenu.hpp>
#include  <sOToolBar.hpp>


/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OToolBar :: Initialize ( )
{
  QSizePolicy  sp = sizePolicy();

  sp.setHorizontalPolicy(QSizePolicy::Expanding);
  sp.setVerticalPolicy(QSizePolicy::Fixed);
  resize(500,26);


}

/******************************************************************************/
/**
\brief  OToolBar - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  qscLabel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolBar"

     OToolBar :: OToolBar (ODataWidget *pODataWidget, ODataWidget *oODataWidget, const QString &qscLabel )
                     : QToolBar(qscLabel,
         pODataWidget ? pODataWidget->WidgetQ() 
                      : NULL ),
ODataWidget(pODataWidget,oODataWidget,YES),
  toolbar_action(NULL)
{

  Initialize();

}

/******************************************************************************/
/**
\brief  i01 - 


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolBar"

     OToolBar :: OToolBar (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w )
                     : QToolBar(pODataWidget ? pODataWidget->WidgetQ() 
                      : NULL),
ODataWidget(pODataWidget,oODataWidget,pODS_w),
  toolbar_action(NULL)
{

  Initialize();

}

/******************************************************************************/
/**
\brief  SetupActions - 


\return term - 

\param  action - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupActions"

logical OToolBar :: SetupActions (OEHAction *action )
{
  OEHAction     *oeh_action    = NULL;
  ODataWidget   *widget        = NULL;
  OPopupMenu    *menu          = NULL;
  QToolButton   *tool_button   = NULL;
  int            count         = 0;
  int            indx0         = 0;
  logical        term          = NO;
BEGINSEQ
  if(!action || !action->get_childs())               ERROR
  
  count = action->get_childs()->size();
  toolbar_action = action;
  WidgetQ()->setObjectName(action->GetName());

  while ( indx0 < count )
  {
    oeh_action = action->get_childs()->at(indx0++);
    if ( oeh_action->IsSeparated() )
      addSeparator();
    if (  !oeh_action->get_childs() 
        || oeh_action->get_childs()->size() <= 0 )
    {
      if (widget = oeh_action->get_widget() )
        addWidget(widget->WidgetQ());
      else
        addAction(oeh_action->get_qaction());
    }
    else if ( oeh_action->IsGrouped() )
      addActions(oeh_action->get_group()->actions());
    else
    {
      if ( !(menu = new OPopupMenu(this,this)) )     OGUIERR(95)
      menu->SetupActions(oeh_action);
      
      if ( !(tool_button = new QToolButton(this)) )  OGUIERR(95)
      tool_button->setPopupMode(oeh_action->GetName() ? QToolButton::MenuButtonPopup
                                                      : QToolButton::InstantPopup);
      tool_button->setMenu(menu);
      tool_button->setIcon(oeh_action->get_qaction()->icon());
      addWidget(tool_button);
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OToolBar :: WidgetQ ( )
{


  return(this);
}


