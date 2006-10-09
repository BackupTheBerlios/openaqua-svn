/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    VersionEntry

\brief    


\date     $Date: 2006/03/12 19:18:16,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "VersionEntry"

#include  <popa7.h>
#include  <sdttm.hpp>
#include  <sVersionEntry.hpp>


/******************************************************************************/
/**
\brief  VersionEntry - 



\param  version_nr - Internal version number
\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionEntry"

                        VersionEntry :: VersionEntry (uint16 version_nr, dttm timestamp )
                     : version(version_nr),
  time_stamp(timestamp)
{



}


