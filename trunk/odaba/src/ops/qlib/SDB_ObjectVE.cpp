/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ObjectVE

\brief    Database object version list entry
          A  database object version  list entry defines  the version number and
          the  validity period for the database object version. The presentation
          describes  the external  presentation of  a version  list entry in the
          database. 
          A  maximum  of  65000  versions  can be defined for a database object.
          Database  version entries  are stored  as linked entries, which allays
          allows defining a new database version entry.

\date     $Date: 2006/03/13 21:30:21,31 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_ObjectVE"

#include  <pops7.h>
#include  <iNetConversion.h>
#include  <sdttm.hpp>
#include  <sSDB_ObjectVE.hpp>


/******************************************************************************/
/**
\brief  FromPIF


\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void SDB_ObjectVE :: FromPIF (logical pif )
{
  dttm         temptime;
BEGINSEQ
  if ( !pif )                                        LEAVESEQ
    
  version_number = PIFToShort(version_number,pif);
  
  LoadLong(temptime.GetDate(),(char *)&time_stamp);
  LoadLong(temptime.GetTime(),((char *)&time_stamp)+4);
  temptime.FromPIF(pif);
  StoreLong((char *)&time_stamp,temptime.GetDate());
  StoreLong(((char *)&time_stamp)+4,temptime.GetTime());

ENDSEQ

}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void SDB_ObjectVE :: Reset ( )
{

  time_stamp = dttm();
  next_object_ve = 0;

}

/******************************************************************************/
/**
\brief  SDB_ObjectVE - 



\param  entnr -
\param  version_nr -
\param  timestamp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_ObjectVE"

                        SDB_ObjectVE :: SDB_ObjectVE (EB_Number entnr, uint16 version_nr, dttm timestamp )
                     :   version_number(version_nr),
  next_object_ve(entnr)
{

  memset(reserved,0,sizeof(reserved));
  set_time_stamp(timestamp);

}

/******************************************************************************/
/**
\brief  ToPIF


\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void SDB_ObjectVE :: ToPIF (logical pif )
{
  dttm         temptime;
BEGINSEQ
  if ( !pif )                                        LEAVESEQ
    
  version_number = ShortToPIF(version_number,pif);
  
  LoadLong(temptime.GetDate(),(char *)&time_stamp);
  LoadLong(temptime.GetTime(),((char *)&time_stamp)+4);
  temptime.ToPIF(pif);
  StoreLong((char *)&time_stamp,temptime.GetDate());
  StoreLong(((char *)&time_stamp)+4,temptime.GetTime());

ENDSEQ

}

/******************************************************************************/
/**
\brief  get_time_stamp - 


\return datetim -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_time_stamp"

dttm SDB_ObjectVE :: get_time_stamp ( )
{
 dttm       timestamp;
  memcpy(&timestamp,&time_stamp,sizeof(dttm));
  return(timestamp);

}

/******************************************************************************/
/**
\brief  set_time_stamp - 



\param  timestamp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_time_stamp"

void SDB_ObjectVE :: set_time_stamp (dttm timestamp )
{

  memcpy(&time_stamp,&timestamp,sizeof(dttm));

}


