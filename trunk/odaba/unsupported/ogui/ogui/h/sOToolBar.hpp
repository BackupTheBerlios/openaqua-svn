/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
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

\date     $Date: 2006/03/13 21:34:46,54 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OToolBar_HPP
#define   OToolBar_HPP

class     OToolBar;

class     ODS;
class     OEHAction;
#include  <sODataWidget.hpp>
class  OToolBar :public QToolBar,
public ODataWidget
{
protected  :         OEHAction                                   *toolbar_action;                                            //

public     :
                     OEHAction                                   *get_toolbar_action() { return(toolbar_action); }
public     :                                     void Initialize ( );
public     :         OGUI7ImpExp                                         OToolBar (ODataWidget *pODataWidget, ODataWidget *oODataWidget, const QString &qscLabel );
public     :         OGUI7ImpExp                                         OToolBar (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL );
public     :                                     logical SetupActions (OEHAction *action );
public     :                                     QWidget *WidgetQ ( );
};

#endif
