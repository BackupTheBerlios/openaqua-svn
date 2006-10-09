/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    RootBaseEntry



\date     $Date: 2006/05/31 18:30:00,18 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "RootBaseEntry"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sdb_RootBase.hpp>
#include  <sRootBaseEntry.hpp>


/******************************************************************************/
/**
\brief  RootBaseEntry


\param  db_id
\param  rootbase - 
\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RootBaseEntry"

     RootBaseEntry :: RootBaseEntry (char *db_id, db_RootBase *rootbase, char *cpath )
                     :   root_base(rootbase)
{
  memset(database_id,0,sizeof(database_id));
  memset(database_path,0,sizeof(database_path));
  
  if ( cpath )
    strncpy(database_path,cpath,sizeof(database_path)-1);
    
  if ( db_id )
    memcpy(database_id,db_id,sizeof(database_id));
}

/******************************************************************************/
/**
\brief  ~RootBaseEntry


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~RootBaseEntry"

     RootBaseEntry :: ~RootBaseEntry ( )
{
}


