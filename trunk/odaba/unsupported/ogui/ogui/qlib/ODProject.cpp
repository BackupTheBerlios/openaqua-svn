/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODProject

\brief    GUI project
          The  GUI project contains the project resources as sub-applications or
          dictionary and database.

\date     $Date: 2006/08/29 19:50:09,35 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODProject"

#include  <pogui7.h>
#include  <sODControl.hpp>
#include  <sODProject.hpp>


/******************************************************************************/
/**
\brief  ODProject - Konstruktor




\param  pODControl - 
\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODProject"

     ODProject :: ODProject (ODControl *pODControl, char *names )
                     : ODApplication (pODControl,names),
  dictionary(NULL)
{



}

/******************************************************************************/
/**
\brief  SetDictionary - Set dictionary

        The  dictionary  can  be  set  by passing a dictionary path or an opened
        dictionary handle.

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dict_handle - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDictionary"

logical ODProject :: SetDictionary (DictionaryHandle &dict_handle )
{
  logical                 term = NO;
  dictionary = dict_handle;

  controlWidget->GenerateEvent(DEV_Activated);

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  dict_path - Path to the dictionary location
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDictionary"

logical ODProject :: SetDictionary (char *dict_path, PIACC accmode )
{
  logical                 term = NO;
  ODABAClient             oclient;
BEGINSEQ
  
  if ( dictionary.Open(oclient
                      ,dict_path,accmode,YES) ) ERROR

  // database not yet opened
  controlWidget->GenerateEvent(DEV_Activated);

RECOVER
  dictionary.Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ODProject - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODProject"

     ODProject :: ~ODProject ( )
{



}


