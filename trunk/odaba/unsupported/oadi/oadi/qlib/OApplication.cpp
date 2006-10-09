/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OApplication



\date     $Date: 2006/04/28 16:11:14,92 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OApplication"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOADKFactory.hpp>
#include  <sOApplication.hpp>
#include  <sOFieldControl.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOApplication.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OApplication :: CastPointer (char *typenames )
{

  return (   !typenames                             ? NULL
           : !strcmp(typenames,"OApplication")      ? this
           : !strcmp(typenames,"ODataSourceHaving") ? (ODataSourceHaving *)this
                                                    : OWindow::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OApplication :: CreateInstance (void **instptrp )
{
  *instptrp = new OApplication();
  return(0);
}

/******************************************************************************/
/**
\brief  FileTools

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FileTools"

logical OApplication :: FileTools ( )
{
  logical                 term = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  GetDAT

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDAT"

DataSourceHandle *OApplication :: GetDAT ( ) const
{

// *fixme*
  return TProjectManager::TPM->UCB()->sdbudat;

}

/******************************************************************************/
/**
\brief  GetRES

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRES"

DataSourceHandle *OApplication :: GetRES ( ) const
{

// *fixme*
  return TProjectManager::TPM->UCB()->sdbures;

}

/******************************************************************************/
/**
\brief  OApplication

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OApplication"

     OApplication :: OApplication ( )
                     : OWindow (),
  subApplications(),
  subApplicationsRead(NO),
  object(NULL),
  language(UNDEF),
  database()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOWindow
\param  bcODataSourceHaving
\param  subApplications
\param  subApplicationsRead
\param  sobject
\param  ilanguage
\param  odatabase
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OApplication"

     OApplication :: OApplication (OWindow bcOWindow, ODataSourceHaving bcODataSourceHaving, DLL(OApplication) subApplications, logical subApplicationsRead, char *sobject, int ilanguage, ODB_Definition odatabase )
                     :  OWindow(bcOWindow)
,ODataSourceHaving(bcODataSourceHaving)
,subApplications(subApplications)
,subApplicationsRead(subApplicationsRead)
,object(NULL) // strdup
,language(ilanguage)
,database(odatabase)
{
  if (sobject)
    object = strdup(sobject);
/*
  OApplication (" 
   +    ADK_Window::Generate() 
   + ", " + data_source.Generate()
   + ", " + subApplications + "
   + ", YES"   // subapplicationsread - always true
   + ", \"" + object + "\""
   + ", " + language
   + ", " + database.Generate()
   + ");"
*/
}

/******************************************************************************/
/**
\brief  Open

\return pTControl

\param  typenames
\param  tparent
\param  active_f
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

TControl *OApplication :: Open (char *typenames, TControl *tparent, logical active_f )
{
  TControl          *tcontrol;
  if ( !typenames )
    typenames = "OApplication";
    
  tcontrol = OWindow::Open(typenames,tparent,active_f);

//  ds->SetParent(GetDAT()->object_handle);

  return(tcontrol);
}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OApplication :: Read (PropertyHandle *ph )
{
  char          *str;
  logical        term = NO;
  OWindow::Read(ph); 

  database.Read(PHREF(ph->GPH("database")));
  dataSource.Read(PHREF(ph->GPH("data_source")));
  
  if ( (str = ph->GetString("object")) && *str )
    object = strdup(str);
    
  language = ph->GetInt("language");

  ReadSubApplications(ph);
  return(term);
}

/******************************************************************************/
/**
\brief  ReadSubApplications

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadSubApplications"

logical OApplication :: ReadSubApplications (PropertyHandle *ph )
{
  OApplication     *ai;
  long              indx0 = 0;
  logical           term  = NO;

BEGINSEQ
  if ( subApplicationsRead )                         LEAVESEQ
  subApplicationsRead = YES;

  ph = ph->GPH("sub_applications");
  while ( ph->Get(indx0++) )
    if ( ai = CACHE_READ(ph,NULL,OApplication) )
      subApplications.AddTail(ai);

ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OApplication :: Reset ( )
{
  OApplication    *appl;
  while ( appl = subApplications.RemoveTail() )
  {
    appl->Reset();
    appl->Release();
  }
  subApplicationsRead = NO;

  database.Reset();
  dataSource.Reset();
  
  if ( object )
    free(object);
  object = NULL;
  
  language = UNDEF;

  OWindow::Reset(); 

}

/******************************************************************************/
/**
\brief  SubApplicationByName

\return term

\param  rcdsName
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SubApplicationByName"

OApplication *OApplication :: SubApplicationByName (const DString &rcdsName )
{
  DLL(OApplication) cursor(subApplications);
  OApplication   *oappl = NULL;
BEGINSEQ
  cursor.GoTop();  
  while ( oappl = cursor.GetNext() )
    if ( oappl->get_fieldControl()->get_sys_ident() == rcdsName ) 
                                                     LEAVESEQ
  ERROR
RECOVER
  oappl = NULL;
ENDSEQ
  return(oappl);
}

/******************************************************************************/
/**
\brief  fieldControlPHName

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fieldControlPHName"

const char *OApplication :: fieldControlPHName ( ) const
{

  return "appl_control";

}

/******************************************************************************/
/**
\brief  ~OApplication


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OApplication"

     OApplication :: ~OApplication ( )
{

  if ( !Deleting() )
    Reset();
}


