/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc_DataSource



\date     $Date: 2006/05/18 12:54:25,78 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_DataSource"

#include  <pdesign.h>
#include  <cutimac.h>
#include  <sDataSourceHandle.hpp>
#include  <spc_DataSource.hpp>


/******************************************************************************/
/**
\brief  CheckDataSource - 


\return term - 

\param  datasource
\param  new_name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDataSource"

logical pc_DataSource :: CheckDataSource (char *datasource, char *new_name )
{
  DBStructDef *smcbptr  = GetStructDef();
  PropertyHandle      dict_path(smcbptr,"dict_path",datasource);
  PropertyHandle      db_path(smcbptr,"db_path",datasource);
//  CTX_Project *context   = GetProjectContext();
  char         string[256];
  logical      term      = NO;
BEGINSEQ
/*
  P_SETEV2(dict_path.GetString(),0)
  if ( !IsFile(dict_path.GetString()) )              P_ERR(25)

  if ( !IsFile(db_path.GetString()) ) 
  {
    P_SETEV2(db_path.GetString(),0)
    if ( DBField(smcbptr,"acc_opt",datasource) != DBField("PI_Write") )
                                                     P_ERR(25)
    else
    {
      if ( GetDirectoryPath(db_path.GetString(),string) )
; //        context->DisplayMessage(26);
      else
      {
        P_SETEV2(string,0)
//         if ( !context->GetDecision(27) )             ERROR
        if ( MakePathDirectories(string) )              P_ERR(28)
      }    
    }
  }
*/
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckName - 


\return term - 

\param  datasource
\param  new_name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckName"

logical pc_DataSource :: CheckName (char *datasource, char *new_name )
{
  DBStructDef *smcbptr  = GetStructDef();
  PropertyHandle      name(smcbptr,"name",datasource);
  logical      term = NO;
BEGINSEQ
  if ( new_name )
    name = new_name;
  
  if ( name.IsEmpty() )                              P_ERR(10)
  P_SETEV1(name.GetString(),0)
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteDefinition

\return term - 

\param  datasource
\param  new_name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteDefinition"

logical pc_DataSource :: DeleteDefinition (char *datasource, char *new_name )
{
  logical                 term = NO;
BEGINSEQ
  if ( CheckName(datasource,new_name) )              ERROR
  if ( !Get(datasource) )                            P_ERR(15)
  if ( Delete() )
  {
    P_SDBCERR
    P_ERR(16)
  }
  


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitInstance - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0


\param  datasource
\param  db_def
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitInstance"

logical pc_DataSource :: InitInstance (char *datasource, DataSourceHandle *db_def )
{
  DBStructDef *smcbptr  = GetStructDef();
  logical      term    = NO;
  smcbptr->smcb::Initialize(datasource);
  
  PropertyHandle(smcbptr,"dict_path",datasource)      = db_def->dict_path;
  PropertyHandle(smcbptr,"db_path",datasource)        = db_def->db_path;
  PropertyHandle(smcbptr,"object_path",datasource)    = db_def->object_name;
  PropertyHandle(smcbptr,"extent",datasource)         = db_def->extent_name;

  PropertyHandle(smcbptr,"acc_opt",datasource)        = db_def->accmode;
  PropertyHandle(smcbptr,"net_opt",datasource)        = db_def->netopt;
  PropertyHandle(smcbptr,"version",datasource)        = db_def->version;
  PropertyHandle(smcbptr,"schema_version",datasource) = db_def->schema_version;
  PropertyHandle(smcbptr,"sys_appl",datasource)       = db_def->sys_appl;

  return(term);
}

/******************************************************************************/
/**
\brief  i1


\param  datasource
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitInstance"

logical pc_DataSource :: InitInstance (char *datasource )
{
  DBStructDef *smcbptr  = GetStructDef();
  DBField      name(smcbptr,"name",datasource);
  char        *source;
  logical      term    = NO;
BEGINSEQ
  P_SETEV1(name.GetString(),0)
  if ( !(source = (char *)Get(name.GetArea()).GetData()) ) P_ERR(15)
  
  smcbptr->CopyInstance(datasource,smcbptr,source);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SaveDefinition - 


\return term - 

\param  datasource
\param  new_name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveDefinition"

logical pc_DataSource :: SaveDefinition (char *datasource, char *new_name )
{
  logical     term    = NO;
BEGINSEQ
  if ( CheckName(datasource,new_name) )                  ERROR
  if ( CheckDataSource(datasource) )                     ERROR
  
  if ( !Get(datasource) )
  {
    if ( !Add((mem *)datasource) )                  
    {
      P_SDBCERR
      P_ERR(11)
    }
  }
  else
  {
//    if ( !GUIError()->GetDecision(12) )        ERROR
    if ( !CopyInst(datasource,GetStructDef(),REPL_local) )  
    {
      P_SDBCERR
      P_ERR(11)
    }
  }

  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup - 


\return term - 

\param  db_def
\param  datasource
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical pc_DataSource :: Setup (DataSourceHandle *db_def, char *datasource )
{
  DBStructDef *smcbptr  = GetStructDef();
  logical      term    = NO;
  strcpy(db_def->dict_path,PropertyHandle(smcbptr,"dict_path",datasource).GetString());
  strcpy(db_def->db_path,PropertyHandle(smcbptr,"db_path",datasource).GetString());
  strcpy(db_def->object_name,PropertyHandle(smcbptr,"object_path",datasource).GetString());
  strcpy(db_def->extent_name,PropertyHandle(smcbptr,"extent",datasource).GetString());

  db_def->accmode        = (PIACC)DBField(smcbptr,"acc_opt",datasource).GetInt();
  db_def->netopt         = PropertyHandle(smcbptr,"net_opt",datasource).IsTrue();
  db_def->version        = PropertyHandle(smcbptr,"version",datasource).GetInt();
  db_def->schema_version = PropertyHandle(smcbptr,"schema_version",datasource).GetInt();
  db_def->sys_appl       = *DBField(smcbptr,"sys_appl",datasource).GetArea();

  return(term);
}

/******************************************************************************/
/**
\brief  SetupForRCrtExt

\return term - 

\param  datasource
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupForRCrtExt"

logical pc_DataSource :: SetupForRCrtExt (char *datasource )
{
  DBStructDef *smcbptr  = GetStructDef();
  logical      term    = NO;
  PropertyHandle(smcbptr,"object_path",datasource)    = "";
  PropertyHandle(smcbptr,"acc_opt",datasource)        = PropertyHandle("PI_Write");
  PropertyHandle(smcbptr,"version",datasource)        = USHORTMAX;
  PropertyHandle(smcbptr,"schema_version",datasource) = USHORTMAX;

  return(term);
}

/******************************************************************************/
/**
\brief  pc_DataSource - Konstruktor



\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_DataSource"

     pc_DataSource :: pc_DataSource (DatabaseHandle &dbhandle )
                     : PropertyHandle (dbhandle,"DataSource",PI_Write)
{
BEGINSEQ
  P_SDBCERR
RECOVER
ENDSEQ
}


