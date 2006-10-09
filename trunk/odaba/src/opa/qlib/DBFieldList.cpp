/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBFieldList

\brief    


\date     $Date: 2006/06/04 13:59:09,59 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBFieldList"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sDBFieldList.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return dbfieldlist - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  dictptr - Dictionary handle
\param  strdef_ptr - Internal data structure definition
\param  pathes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

DBFieldList *__cdecl DBFieldList :: Create (Dictionary *dictptr, DBStructDef *strdef_ptr, char *pathes )
{
  DBFieldList  *dbfieldlist = NULL;
  DBExtend     *dbextdef;
  DBStructDef  *dbstrdef;
  DBFieldDef   *dbflddef;
  DBFieldDef   *db_field;
  logical       first;
  int16         count   = 1;
  int16         curindx = 0;
  int32          offset  = 0;
  char          workpath[256];
  char         *pathptr;
  char         *property;
BEGINSEQ
  memset(workpath,0,sizeof(workpath));
  strncpy(workpath,pathes,sizeof(workpath)-2);
  if ( !strtok(workpath,".,") )                      ERROR
  while ( strtok(NULL,".,") )
    count++;
  
  if ( !(dbfieldlist = new DBFieldList(count)))      SDBERR(95)
                                                     SDBCERR
  pathptr = strncpy(workpath,pathes,sizeof(workpath)-2);
  pathptr = strtok(pathptr,",");
  do
  {
    if ( *pathptr )
    {
      dbstrdef = strdef_ptr;
      first    = YES;
      property = pathptr;
      while ( (pathptr = property) && *pathptr )
      {
        if ( property = strchr(pathptr,'.') )
        {
          *property = 0;
          property++;
        }
        
        if ( !dbstrdef )
        {
          if ( !first )                              ERROR
          if ( !(dbextdef = dictptr->ProvideExtendDef(pathptr)) )
                                                     ERROR
          db_field = dbextdef;
        }
        else          
          if ( !(db_field = (DBFieldDef *)dbstrdef->SearchField(pathptr,&offset)) )
                                                     ERROR
        db_field->GetDBStruct(dictptr);
        switch ( db_field->fmcbrlev )
        {
          case R_REFR   : dbflddef  = dbfieldlist->GetEntry(++curindx);
                          *dbflddef = *db_field;
                          dbflddef->fmcbrlev = R_DIRECT;
                          dbflddef->fmcbdim  = 1;
                          dbflddef->set_resource(new DBResource(dictptr));
                          dbflddef->set_index_list(NULL);
                          dbflddef->CopyTopIndex(db_field);
                          dbflddef->set_static_field(first);
                          dbflddef->fmcbbstr = YES;           // consider as base structure
                          first = NO;
          case R_DIRECT : dbstrdef  = db_field->GetDBStruct();
                          break;
          default       : ERROR
        }
      }

    }
  } while (pathptr = strtok(NULL,",") );

  
  dbfieldlist->srtsetc(curindx);

RECOVER
  delete dbfieldlist;
  dbfieldlist = NULL;
ENDSEQ
  return(dbfieldlist);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  dictptr - Dictionary handle
\param  field_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

DBFieldList *__cdecl DBFieldList :: Create (Dictionary *dictptr, DBFieldDef *field_def )
{
  DBFieldDef             *dbflddef;
  DBFieldList            *dbfieldlist = NULL;
BEGINSEQ
  if ( !(dbfieldlist = new DBFieldList(1)))          SDBERR(95)
                                                     SDBCERR
  dbflddef  = dbfieldlist->GetEntry(1);
  *dbflddef = *field_def;
  dbflddef->fmcbrlev = R_DIRECT;
  dbflddef->fmcbdim  = 1;
  dbflddef->set_resource(new DBResource(dictptr));
  dbflddef->set_index_list(NULL);
  dbflddef->CopyTopIndex(field_def);
  dbflddef->set_static_field(YES);
  gvtxstb(dbflddef->fmcbname,"__local_view",ID_SIZE); 
  dbfieldlist->srtsetc(1);

RECOVER
  delete dbfieldlist;
  dbfieldlist = NULL;
ENDSEQ
  return(dbfieldlist);
}

/******************************************************************************/
/**
\brief  CreateField - 


\return fielddef - Internal field defintion
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateField"

DBFieldDef *DBFieldList :: CreateField ( )
{
  DBFieldDef        *fielddef = NULL;
  fielddef = (DBFieldDef *)srtfad();
  fielddef->Initialize();
  return(fielddef);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  lindx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateField"

DBFieldDef *DBFieldList :: CreateField (int32 lindx )
{
  DBFieldDef        *fielddef = NULL;
BEGINSEQ
  if ( srtiad(lindx,NULL) )                          ERROR

  fielddef = (DBFieldDef *)srtigt(lindx);
  fielddef->Initialize();

RECOVER

ENDSEQ
  return(fielddef);
}

/******************************************************************************/
/**
\brief  DBFieldList - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  memcnt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBFieldList"

     DBFieldList :: DBFieldList (int16 memcnt )
                     : FieldList((DBFieldDef *)
(memcnt ? msmgs(memcnt*sizeof(DBFieldDef)) : NULL),
sizeof(DBFieldDef),
memcnt)
{
  DBFieldDef   *fielddef;
//  DBFieldDef    initdef;
  int           indx = 1;
BEGINSEQ
  if ( memcnt && !GetTable() )                      SDBERR(95)
  
// führt zu exd::Setup 105
//  while ( fielddef = GetEntry(indx++) )
//    *fielddef = initdef;

  stssusr1();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBFieldList"

     DBFieldList :: DBFieldList ( )
                     : FieldList(NULL,sizeof(DBFieldDef),0)

{



}

/******************************************************************************/
/**
\brief  GetEntry - 


\return dbfield_ptr - Property definition

\param  indx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

DBFieldDef *DBFieldList :: GetEntry (int16 indx )
{

  return((DBFieldDef *)FieldList::GetEntry(indx));

}

/******************************************************************************/
/**
\brief  ~DBFieldList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBFieldList"

     DBFieldList :: ~DBFieldList ( )
{
  DBFieldDef   *fielddef;
  fmcb         *table = GetTable();
  int           indx  = 1;
  if ( stscusr1() && table )
  {
    while ( fielddef = GetEntry(indx++) )
      fielddef->Remove();
    
    msmfs((void **)&table);
    SetTable(table);
  }


}


