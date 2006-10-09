/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    OBH_ListEntry

\brief    


\date     $Date: 2006/03/12 19:17:58,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OBH_ListEntry"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sOBH_ListEntry.hpp>


/******************************************************************************/
/**
\brief  OBH_ListEntry - 



\param  obhandle - Database Object handle
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBH_ListEntry"

                        OBH_ListEntry :: OBH_ListEntry (ACObject *obhandle, uint16 version_nr )
                     : version(version_nr),
  ob_handle(obhandle)
{



}

/******************************************************************************/
/**
\brief  set_version - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_version"

void OBH_ListEntry :: set_version (uint16 version_nr )
{

  version = version_nr;

}


