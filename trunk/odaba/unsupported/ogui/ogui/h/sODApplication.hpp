/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODApplication

\brief    GUI application
          This  object  presents  a  GUI  application.  Applications  might form
          hierarchies,   i.e.   an   application   may   have   any   number  of
          sub-applications.  An  application  is  associated  with  a  database 
          object,  which acts as data source  for the application. You may refer
          to  more than one database in an application, but the application data
          source is the standard data source for the application.

\date     $Date: 2006/03/13 21:33:47,31 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODApplication_HPP
#define   ODApplication_HPP

class     ODApplication;

#include  <sDLL.h>
class     ODApplication;
class     ODApplication;
class     ODControl;
#include  <sDBObjectHandle.hpp>
#include  <sODWindow.hpp>
#include  <sODataWidget.hpp>
#include  <sOFrame.hpp>
class  ODApplication :public ODWindow
{
protected  :         DLL(ODApplication)                          *sub_applications;                                          //

public     :
                     DLL(ODApplication)                          *get_sub_applications() { return(sub_applications); }
public     :         OGUI7ImpExp                 ODApplication *AddApplication (char *names );
public     :         OGUI7ImpExp                                         ODApplication (ODControl *pODControl, char *names );
public     :         OGUI7ImpExp                 logical SetDataSource (char *db_path, PIACC accmode, logical net_opt );
public     :         OGUI7ImpExp                                         ~ODApplication ( );
};

#endif
