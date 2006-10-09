/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    ODB_Definition



\date     $Date: 2006/04/28 14:51:28,54 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODB_Definition"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sPropertyHandle.hpp>
#include  <sODB_Definition.hpp>


/******************************************************************************/
/**
\brief  GetAccessMode

\return acc_opt

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccessMode"

PIACC ODB_Definition :: GetAccessMode ( )
{

  return ( !GetPath() ? PI_undefined :
           writeMode  ? PI_Write
                      : PI_Read         );



}

/******************************************************************************/
/**
\brief  GetPath

\return string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPath"

char *ODB_Definition :: GetPath ( )
{

  return ( !dbPath || *dbPath == '*' ? NULL : dbPath );


}

/******************************************************************************/
/**
\brief  ODB_Definition

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODB_Definition"

     ODB_Definition :: ODB_Definition ( )
                     : OPersistent (),
  dbPath(NULL),
  netOpt(YES),
  writeMode(YES)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOPersistent
\param  dbPath
\param  netOpt
\param  writeMode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODB_Definition"

     ODB_Definition :: ODB_Definition (OPersistent bcOPersistent, char *dbPath, logical netOpt, logical writeMode )
                     : OPersistent (bcOPersistent),
  dbPath(NULL), //strdup
  netOpt(netOpt),
  writeMode(writeMode)
{
if(dbPath && *dbPath)
  this->dbPath = strdup(dbPath);
/*
  "ODB_Definition("
  +        ADK_Persistent::Generate()
  + ", \"" + db_path + "\""
  + ", " + net_opt
  + ", " + write_mode
  + ")";
*/
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

logical ODB_Definition :: Read (PropertyHandle *ph )
{
  char         *str;
  logical       term = NO;
  OPersistent::Read(ph);

  if ( (str = ph->GetString("db_path")) && *str )
    dbPath = strdup(str);
  
  netOpt    = ph->GetInt("net_opt");
  writeMode = ph->GetInt("write_mode");
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void ODB_Definition :: Reset ( )
{

  if ( dbPath )
    free(dbPath);
  dbPath = NULL;

}

/******************************************************************************/
/**
\brief  ~ODB_Definition


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODB_Definition"

     ODB_Definition :: ~ODB_Definition ( )
{
  Reset();
}


