/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ObjectExt

\brief    Database object instance (external)
          When  creating a  database object  in the  database, a database object
          instance  is  created,  which  is  the  root  for  accessing  extents,
          sub-objects  and  other  resources  of  the  database  object.  This 
          structure  is  equivalent  to  SDB_ObjectID,  but defines the external
          presentation of a database object instance.

\date     $Date: 2006/03/13 21:30:21,14 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_ObjectExt"

#include  <pops7.h>
#include  <cSDBOExt.h>
#include  <sEB_Number.hpp>
#include  <iNetConversion.h>
#include  <sSDB_ObjectExt.hpp>


/******************************************************************************/
/**
\brief  ConvertTo6 - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertTo6"

void SDB_ObjectExt :: ConvertTo6 (logical pif )
{
  SDBOExt      *oldinst;
BEGINSEQ
  if ( PIFToShort(db_version,pif) == 6 )             LEAVESEQ
    
  oldinst = (SDBOExt *)malloc(sizeof(SDBOExt));
  memcpy(oldinst,this,sizeof(SDBOExt));

  object_id    = oldinst->object_id;
  derivates    = BigToPIF(PIFToLong(oldinst->derivates,pif),pif);
  extends      = BigToPIF(PIFToLong(oldinst->extends,pif),pif);
  version_list = BigToPIF(PIFToLong(oldinst->version_list,pif),pif);
  version      = oldinst->version;
  db_version   = ShortToPIF(6,pif);

ENDSEQ

}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void SDB_ObjectExt :: FromPIF (logical pif )
{

  object_id = PIFToLong(object_id,pif);
  version = PIFToShort(version,pif);


}

/******************************************************************************/
/**
\brief  InitVersion - 



\param  entnr -
\param  version_nr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitVersion"

void SDB_ObjectExt :: InitVersion (EB_Number entnr, uint16 version_nr )
{

  version_list = entnr;
  version      = version_nr;

}

/******************************************************************************/
/**
\brief  SDB_ObjectExt - 


-------------------------------------------------------------------------------
\brief  i0


\param  objid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_ObjectExt"

                        SDB_ObjectExt :: SDB_ObjectExt (int32 objid )
                     : object_id(objid), derivates(0), extends(0),
  version_list(0),
  version(0),
  db_version(6)
{



}

/******************************************************************************/
/**
\brief  i1


\param  extobj_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_ObjectExt"

                        SDB_ObjectExt :: SDB_ObjectExt (SDB_ObjectExt &extobj_ref )
                     : object_id(extobj_ref.get_object_id()),
 derivates(extobj_ref.get_derivates()),
 extends(extobj_ref.get_extends()),
 version_list(extobj_ref.get_version_list()),
 version(extobj_ref.get_version()),
 db_version(extobj_ref.get_db_version())

{



}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void SDB_ObjectExt :: ToPIF (logical pif )
{

  object_id = LongToPIF(object_id,pif);
  version = ShortToPIF(version,pif);


}


