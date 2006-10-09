/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OProject



\date     $Date: 2006/04/28 16:51:50,31 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OProject"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOApplicationO.hpp>
#include  <sODataWidget.hpp>
#include  <sOFieldControl.hpp>
#include  <sOWidget.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sTWidgetControl.hpp>
#include  <sOProject.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OProject :: CastPointer (char *typenames )
{

  return (   !typenames                    ? NULL
           : !strcmp(typenames,"OProject") ? this
                                           : OApplication::CastPointer(typenames) );

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

int32 OProject :: CreateInstance (void **instptrp )
{

  *instptrp = new OProject();
  return(0);

}

/******************************************************************************/
/**
\brief  OProject

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OProject"

     OProject :: OProject ( )
                     : OApplication (),
  tpPath(NULL),
  queryLevel(),
  errorClass()
{

memset(errorClass,0,sizeof(errorClass));

}

/******************************************************************************/
/**
\brief  i01


\param  bcOApplication
\param  tpPath
\param  queryLevel
\param  errorClass
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OProject"

     OProject :: OProject (OApplication bcOApplication, char *tpPath, int16 queryLevel, char *errorClass )
                     : OApplication (bcOApplication),
  tpPath(NULL),
  queryLevel(queryLevel),
  errorClass()
{
memset(this->errorClass,0,sizeof(this->errorClass));

if(tpPath && *tpPath)
  this->tpPath = strdup(tpPath);
if(errorClass && *errorClass)
  strncpy(this->errorClass,errorClass,sizeof(this->errorClass));
/*
  "OProject("
  +        ADK_Application::Generate()
  + ", \"" + tp_path + "\""
  + ", " + query_level 
  + ", \"" + error_class + "\""
  + ")";
*/
}

/******************************************************************************/
/**
\brief  Open

\return pTControl

\param  tparent
\param  active_f
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

TControl *OProject :: Open (TControl *tparent, logical active_f )
{
  TControl     *tctrl;
BEGINSEQ
  if ( !(tctrl = OApplication::Open("OProject",tparent,active_f)) )
                                                     ERROR
  TProjectManager::TPM->SetMainWindow(this);

RECOVER

ENDSEQ
  return(tctrl);
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

logical OProject :: Read (PropertyHandle *ph )
{
  char       *str;
  logical     term = NO;
  OApplication::Read(ph);

// wer ist zustaendig fure die Logon-Applikationspruefung ?

  if ( (str = ph->GetString("tp_path")) && *str )
    tpPath = strdup(str);
  // TODO: OQueryLevel should be a Enum
  (int&)queryLevel = ph->GetInt("query_level");
  
  if ( (str = ph->GetString("error_class")) && *str )
    strncpy(errorClass,str,sizeof(errorClass)-1);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OProject :: Reset ( )
{
  memset(errorClass,0,sizeof(errorClass));
  
  if ( tpPath )
    free(tpPath);
  tpPath = NULL;

  OApplication::Reset();
}

/******************************************************************************/
/**
\brief  ~OProject


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OProject"

     OProject :: ~OProject ( )
{
  if ( !Deleting() )
    Reset();
}


