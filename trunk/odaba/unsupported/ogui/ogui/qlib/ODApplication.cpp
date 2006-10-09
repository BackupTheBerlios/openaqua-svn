/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    ODApplication

\brief    GUI application
          This  object  presents  a  GUI  application.  Applications  might form
          hierarchies,   i.e.   an   application   may   have   any   number  of
          sub-applications.  An  application  is  associated  with  a  database 
          object,  which acts as data source  for the application. You may refer
          to  more than one database in an application, but the application data
          source is the standard data source for the application.

\date     $Date: 2006/04/18 10:41:44,06 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODApplication"

#include  <pogui7.h>
#ifndef   DLL_ODApplication_HPP
#define   DLL_ODApplication_HPP
#include  <sODApplication.hpp>
#include  <sDLL.h>
#endif
#include  <sODApplication.hpp>
#include  <sODControl.hpp>
#include  <sODataWidget.hpp>
#include  <sODApplication.hpp>


/******************************************************************************/
/**
\brief  AddApplication - Add sub-application
        The  function adds a sub-application to the list of sub-applications for
        the current application.

\return pOEHApplication - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddApplication"

ODApplication *ODApplication :: AddApplication (char *names )
{
  ODApplication      *appl = NULL;
BEGINSEQ
  if ( !sub_applications )
    if ( !(sub_applications = new DLL(ODApplication)) )
                                                     OGUIERR(95)
  if ( !(appl = new ODApplication(this,names)) )     OGUIERR(95)
  sub_applications->AddTail(appl);
RECOVER

ENDSEQ
  return(appl);
}

/******************************************************************************/
/**
\brief  ODApplication - Constructor



\param  pODControl - 
\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODApplication"

                        ODApplication :: ODApplication (ODControl *pODControl, char *names )
                     : ODWindow (pODControl,names),
  sub_applications(NULL)
{



}

/******************************************************************************/
/**
\brief  SetDataSource - Set application data source
        The  function allows setting the application data source. This is either
        an opened database object handle or a data source name.

\return term - 

\param  db_path - 
\param  accmode - 
\param  net_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical ODApplication :: SetDataSource (char *db_path, PIACC accmode, logical net_opt )
{
  logical                 term = NO;
  ODABAClient             oclient;

  return(term);
}

/******************************************************************************/
/**
\brief  ~ODApplication - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODApplication"

                        ODApplication :: ~ODApplication ( )
{
  ODApplication    *appl = NULL;
  if ( sub_applications )
    while ( appl = sub_applications->RemoveTail() )
      delete appl;

  delete sub_applications;
  sub_applications = NULL;

}


