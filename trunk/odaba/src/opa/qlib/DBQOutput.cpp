/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBQOutput

\brief    View output driver


\date     $Date: 2006/07/12 19:17:12,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBQOutput"

#include  <popa7.h>
#include  <sDBStructDef.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sLDBQuery.hpp>
#include  <sNString.hpp>
#include  <sDBQOutput.hpp>


/******************************************************************************/
/**
\brief  Close - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical DBQOutput :: Close ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( data_source ? DSClose() : FClose() )            ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBQOutput - Konstruktor



-------------------------------------------------------------------------------
\brief  i0 - 



\param  cpath - Complete path
\param  line_sep - 
\param  field_sep - 
\param  string_sep - 
\param  head_line - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBQOutput"

     DBQOutput :: DBQOutput (char *cpath, char *line_sep, char *field_sep, char *string_sep, logical head_line )
                     :   data_source(NULL),
  file_path(NULL),
  line_separator(0x0A),
  field_separator(0x09),
  string_delimiter('"'),
  file_handle(NULL),
  db_struct_def(NULL),
  record_wa(NULL),
  record_area(NULL,1000),
  record_len(0),
  headline(NO),
  first_line(YES)

{

  if ( cpath && *cpath )         
    file_path = strdup(cpath);
  
  line_separator  = *line_sep;
  field_separator = *field_sep;
  string_delimiter= *string_sep;
  headline        = head_line;

}

/******************************************************************************/
/**
\brief  i01 - 



\param  qhandle - 
\param  ds_name - 
\param  extent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBQOutput"

     DBQOutput :: DBQOutput (LDBQuery *qhandle, char *ds_name, char *extent )
                     :   data_source(NULL),
  file_path(NULL),
  line_separator(0x0A),
  field_separator(0x09),
  string_delimiter('"'),
  file_handle(NULL),
  db_struct_def(NULL),
  record_wa(NULL),
  record_area(NULL,1000),
  record_len(0),
  headline(NO),
  first_line(YES)
{

BEGINSEQ
  data_source = new DataSourceHandle();
  
  if ( ds_name && *ds_name )
  {
    SDBEV1(ds_name,UNDEF)
    if ( !data_source->SetupVariables(ds_name) )     ERROR
    SetSysVariable("ACCESS_MODE","Write");  
  }
  else
  {
    SDBEV1(qhandle->data_source,UNDEF)
    data_source->SetDataSource(qhandle);
  }

  if ( data_source->Open(data_source->client,PI_Read) )
                                                     SDBERR(352)
  
  if ( extent && *extent )
    strncpy(data_source->extent_name,extent,sizeof(data_source->extent_name));


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  DSClose - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DSClose"

logical DBQOutput :: DSClose ( )
{
  logical                 term = NO;
  output_ph.Close();
  
  delete data_source;
  data_source = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  DSOpen - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DSOpen"

logical DBQOutput :: DSOpen ( )
{
  logical                 term = NO;
// PropertyHandle für Output-Extent öffnen
  return(term);
}

/******************************************************************************/
/**
\brief  DSWrite - 



\return term - Termination code

\param  result_area - 
\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DSWrite"

logical DBQOutput :: DSWrite (NString &result_area, PropertyHandle &prop_hdl )
{
  logical                 term = NO;
// copy selected instance to output_ph

//  if ( index == 1 )  // für den ersten
      result_area += data_source->data_source;   

  return(term);
}

/******************************************************************************/
/**
\brief  FClose - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FClose"

logical DBQOutput :: FClose ( )
{
  logical                 term = NO;
  if ( file_handle )
    fclose(file_handle);
  file_handle = NULL;

  delete record_wa;
  record_wa = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  FOpen - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FOpen"

logical DBQOutput :: FOpen ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( file_path && *file_path )
    if ( !(file_handle = fopen(file_path,"w")) )   SDBERR(351)
    
  record_len = db_struct_def->GetStringLength();
  record_wa  = new char[record_len];
  record_area = "";
  first_line = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FWrite - 



\return term - Termination code

\param  result_area - 
\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FWrite"

logical DBQOutput :: FWrite (NString &result_area, PropertyHandle &prop_hdl )
{
  DBStructDef    *dbstruct;
  DBFieldDef     *dbfield;
  fld             string_fld(record_wa,record_len);
  char           *instance;
  char           *work_ptr;
  int16           index = 0;
  logical         term = NO;
  instance = prop_hdl.GetArea();
  
  if ( headline == YES && first_line )
  {
    FWriteHeadline(result_area);
    first_line = NO;
  }
  record_area = "";
  
  while ( dbfield  = db_struct_def->GetEntry(++index) )
  {
    if ( dbfield->IsStructure() )
    {
      dbstruct = dbfield->GetDBStruct();
      dbstruct->ConvertToString(instance+dbfield->fmcbposn,record_wa,record_len);
    }
    else
    {
      switch ( dbfield->fmcbrlev )
      {
        case R_INTERN  :
        case R_DIRECT  :
        case R_GENERIC : work_ptr = instance+dbfield->fmcbposn;
                         break;
        case 1         : work_ptr = *(char **)(instance+dbfield->fmcbposn);
                         break;
        default        : work_ptr = "";
      }
      string_fld = fld(dbfield,work_ptr);
//    gvtsexc(record_wa,"\r\n","|",record_len);
    }
    FWriteField(record_wa,index==1 ? YES : NO);   
  }

  record_area += line_separator;
  if ( file_handle )
  {
    fwrite(record_area,strlen(record_area),1,file_handle);
    if ( index == 1 )
      result_area += file_path;   
  }
  else
    result_area += record_area;
  return(term);
}

/******************************************************************************/
/**
\brief  FWriteField - 



\return term - Termination code

\param  propstr - 
\param  first_rec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FWriteField"

logical DBQOutput :: FWriteField (char *propstr, logical first_rec )
{
  char           *pdpos;
  char           *sdpos;
  logical                 term = NO;
  if ( !first_rec )
    record_area += field_separator;
      
  if ( pdpos = STRSearchChar(propstr,string_delimiter,NO) )
  {
    record_area += string_delimiter;
    
    while ( sdpos = STRSearchChar(propstr,string_delimiter,NO) )
    {
      *sdpos   = 0;
      record_area += propstr;
      record_area += string_delimiter;
      record_area += string_delimiter;
      *sdpos   = string_delimiter;
      propstr  = sdpos + 1;
    }
  }
      
  record_area += propstr;
      
  if ( pdpos )
    record_area += string_delimiter;
  return(term);
}

/******************************************************************************/
/**
\brief  FWriteHeadline - 



\return term - Termination code

\param  result_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FWriteHeadline"

logical DBQOutput :: FWriteHeadline (NString &result_area )
{
  DBFieldDef     *dbfield;
  char            string[ID_SIZE+1];
  int16           index = 0;
  logical         term = NO;
  record_area = "";
  
  while ( dbfield  = db_struct_def->GetEntry(++index) )
  {
    gvtxbts(string,dbfield->fmcbname,ID_SIZE);
    FWriteField(string,index==1 ? YES : NO);   
  }

  record_area += line_separator;
  if ( file_handle )
  {
    fwrite(record_area,strlen(record_area),1,file_handle);
    if ( index == 1 )
      result_area += file_path;   
  }
  else
    result_area += record_area;
  return(term);
}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code

\param  struct_def - Pointer to generel structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DBQOutput :: Open (DBStructDef *struct_def )
{
  logical                 term = NO;
BEGINSEQ
  db_struct_def = struct_def;

  if ( data_source ? DSOpen() : FOpen() )            ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Write - 



\return term - Termination code

\param  result_area - 
\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical DBQOutput :: Write (NString &result_area, PropertyHandle &prop_hdl )
{
  logical                 term = NO;
BEGINSEQ
  if ( data_source ? DSWrite(result_area,prop_hdl) : FWrite(result_area,prop_hdl) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~DBQOutput - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBQOutput"

     DBQOutput :: ~DBQOutput ( )
{

  Close();

  if ( file_path )
    free(file_path);

  file_path = NULL;

}


