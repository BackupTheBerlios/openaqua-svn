/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBViewDefEntry

\brief    


\date     $Date: 2006/03/12 19:17:15,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBViewDefEntry"

#include  <popa7.h>
#include  <sDBQOutput.hpp>
#include  <sDBViewDef.hpp>
#include  <sLDBQuery.hpp>
#include  <sguid.hpp>
#include  <sDBViewDefEntry.hpp>


/******************************************************************************/
/**
\brief  Clear - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void DBViewDefEntry :: Clear ( )
{

  Uninitialize();
  
  if ( view_def )
    free(view_def);
  view_def = NULL;

}

/******************************************************************************/
/**
\brief  DBViewDefEntry - Konstruktor


-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewDefEntry"

                        DBViewDefEntry :: DBViewDefEntry ( )
                     : query_handle(NULL),
  query_id(0),
  view_def(NULL),
  db_view_def(NULL),
  query_output(NULL)
{



}

/******************************************************************************/
/**
\brief i01


\param  qhandle -
\param  qid -
\param  view_definition - View definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewDefEntry"

                        DBViewDefEntry :: DBViewDefEntry (LDBQuery *qhandle, int32 qid, char *view_definition )
                     : query_handle(qhandle),
  query_id(qid),
  view_def(NULL),
  db_view_def(NULL),
  query_output(NULL)

{
  guid            view_id((int16)qid,(int32)this,qid);

  SDBRESET
  view_def = strdup(view_definition);
  STRExchange(view_def,"\r"," ",UNDEF);
  STRExchange(view_def,"\n"," ",UNDEF);
  view_id.GetString(query_name);
  


}

/******************************************************************************/
/**
\brief  Execute - 


\return result_area -

\param  result_area -
\param  parm_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char *DBViewDefEntry :: Execute (NString &result_area, char *parm_string )
{
  int32                    indx0 = 0;
  char                   *result;
BEGINSEQ
  result_area = "";
  if ( ReplaceParameters(parm_string) )              ERROR
  
  PropertyHandle   ph(query_handle->dbhandle,*db_view_def,PI_Read);
                                                     SDBCERR
// ggf ChangeBuffer()

  if ( query_output->Open(ph.GetStructDef()) )       ERROR
  while ( ph(indx0++) )
    query_output->Write(result_area,ph);

  result = result_area;
RECOVER
  result = NULL;
ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  GetSeparator - 


\return separator -

\param  string -
\param  default_sep -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSeparator"

char DBViewDefEntry :: GetSeparator (char *string, char default_sep )
{
  char             separator = default_sep;
BEGINSEQ
  if ( !string || !*string )                         ERROR
  if ( !memcmp(string,"0x",2) || !memcmp(string,"0X",2) )
  {
    separator = 0;
    if ( *(string += 2) )
      separator += gvtxhtn(*string) <<  4;
    if ( *(++string) )
      separator += gvtxhtn(*string);
    else
      separator >>= 4;
  }
  else if ( *string >= '0' && *string <= '9' )
    separator = atoi(string);
  else
    separator = *string;

RECOVER
  separator = default_sep;
ENDSEQ
  return ( separator );
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code

\param  view_definition - View definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBViewDefEntry :: Initialize (char *view_definition )
{
  char           *string;
  logical         term = NO;

BEGINSEQ
  SDBRESET

  if ( (string = GetKeyParm(view_definition,"From",YES,NO)) )
  {
    db_view_def = new DBViewDef(query_handle->dictionary,string,query_name,query_name);
    free(string);
  }
  else                                                 SDBERR(350)

  if ( (string = GetKeyParm(view_definition,"Select",YES,NO)) )
  {
    if ( SetFields(query_handle,string) )                   ERROR
    free(string);
  }
  else                                                 SDBERR(353)
  
  if ( (string = GetKeyParm(view_definition,"Within",YES,NO)) )
  {
    db_view_def->SetViewScope(string);
    free(string);
  }
  
  if ( (string = GetKeyParm(view_definition,"Having",YES,NO)) )
  {
    db_view_def->SetPostCondition(string);
    free(string);
  }
  
  if ( (string = GetKeyParm(view_definition,"Where",YES,NO)) )
  {
    db_view_def->SetPreCondition(string);
//    ... view_definition->SetPreConditions(string);
    free(string);
  }
  
  if ( (string = GetKeyParm(view_definition,"Order",YES,NO)) )
  {
//    ... view_definition->SetOrder(string);
    free(string);
  }
  
  if ( (string = GetKeyParm(view_definition,"To",YES,NO)) )
  {
    if ( SetOutputOptions(query_handle,string) )         ERROR
    free(string);
  }
  else
    if ( SetOutputOptions(query_handle,"") )             ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceParameters - 


\return term - Termination code

\param  parm_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceParameters"

logical DBViewDefEntry :: ReplaceParameters (char *parm_string )
{
  char           *string  = NULL;
  char           *name    = NULL;
  char           *expr    = NULL;
  char           *view_definition;
  int             parm_no = 0;
  int             len;
  logical         term = NO;
  Uninitialize();
  
  if ( parm_string )
  {
    PushSystemVariables();
  
    while ( string = GetPosParm(parm_string,++parm_no,';',YES) )
    {
      expr = GetParmKey(string,&name,YES,YES);
      if ( *name )
      {
        SetSysVariable(name,expr);
        free(name);
        name = NULL;
      }
      if ( expr )
        free(expr);
      free(string);
    }
  
    len =strlen(view_def)+4096;
    view_definition = new char[len];
  
    strcpy(view_definition,view_def);
    ReplaceSysVariable(view_definition,len);
    PopSystemVariables();
    
    term = Initialize(view_definition);
    delete view_definition;
  }
  else
    term = Initialize(view_def);
    

  return(term);
}

/******************************************************************************/
/**
\brief  SetFields - 


\return output -

\param  qhandle -
\param  field_list -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFields"

DBQOutput *DBViewDefEntry :: SetFields (LDBQuery *qhandle, char *field_list )
{
  char           *string  = NULL;
  char           *name    = NULL;
  char           *expr    = NULL;
  char           *source;
  int             parm_no = 0;
  char           *pos;
  int             size    = 0;
  ADT_Types       ftype   = ADT_PropertyPath;
  while ( string = GetPosParm(field_list,++parm_no,';',YES) )
  {
    expr = GetParmKey(string,&name,YES,YES);
    if ( *name )
    {
      source = expr && *expr ? expr : name;
        
      if ( *source == '{' )
        ftype = ADT_Expression;
      
      size = 0;
      if ( (pos = strchr(source,'(')) && GetExpressionEnd(pos,UNDEF,NO) )
      {
        *pos = 0;
        size = atol(pos+1);
      }
      
      db_view_def->AddProperty(name,source,ftype,size);   // der Name kann ggf. noch eine Size-Angabe enthalten name(100)
      free(name);
      name = NULL;
    }
    if ( expr )
      free(expr);
    free(string);
  }

  return(query_output);
}

/******************************************************************************/
/**
\brief  SetOutputOptions - 


\return term - Termination code

\param  qhandle -
\param  options -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOutputOptions"

logical DBViewDefEntry :: SetOutputOptions (LDBQuery *qhandle, char *options )
{
  char           *path    = NULL;
  char           *ds_name = NULL;
  char           *ex_name = NULL;
  char           *fs      = NULL;
  char           *ls      = NULL;
  char           *sd      = NULL;
  char           *hl      = NULL;
  char            field_sep[3];
  char            line_sep[3];
  char            string_sep[3];
  logical         term    = NO;
BEGINSEQ
  ds_name = GetKeyParm(view_def,"DataSource",YES,NO);
  ex_name = GetKeyParm(view_def,"Extent",YES,NO);
  
  if ( (ds_name && *ds_name) || (ex_name && *ex_name) )
  {
    query_output = new DBQOutput(qhandle,ds_name,ex_name);
                                                     SDBCERR
    if ( ds_name )
      free(ds_name);
    if ( ex_name )
      free(ex_name);
  }
  else
  {
    path = GetKeyParm(view_def,"Path",YES,NO);
    
    fs = GetKeyParm(view_def,"FieldSeparator",YES,NO);
    ls = GetKeyParm(view_def,"LineSeparator",YES,NO);
    sd = GetKeyParm(view_def,"StringDelimiter",YES,NO);
    hl = GetKeyParm(view_def,"Headline",YES,NO);
    
    memset(field_sep,0,sizeof(field_sep));
    *field_sep = GetSeparator(fs,'\t');
    memset(line_sep,0,sizeof(line_sep));
    *line_sep = GetSeparator(ls,'\n');
    memset(string_sep,0,sizeof(string_sep));
    *string_sep = GetSeparator(sd,'"');
    
    query_output = new DBQOutput(path,line_sep,field_sep,string_sep,
                                      (!hl || *hl == 'n' || *hl == 'N') ? NO : YES);
                                                     SDBCERR
    free(path);
    if ( fs )
      free(fs);
    if ( ls )
      free(ls);
    if ( sd )
      free(sd);
    if ( hl )
      free(hl);
  }

RECOVER
  delete query_output;
  query_output = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Uninitialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Uninitialize"

void DBViewDefEntry :: Uninitialize ( )
{

  delete query_output;
  query_output = NULL;

  delete db_view_def;
  db_view_def = NULL;



}


