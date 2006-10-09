/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBQOutput

\brief    View output driver


\date     $Date: 2006/03/12 19:12:59,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBQOutput_HPP
#define   DBQOutput_HPP

class     DBQOutput;

class     DBStructDef;
class     DataSourceHandle;
class     LDBQuery;
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  DBQOutput
{
protected  :         DataSourceHandle                            *data_source;                                               
protected  :         char                                         extent_name[41];                                           
protected  :         char                                         data_source_name[41];                                      
protected  :         char                                        *file_path;                                                 
protected  :         char                                         line_separator;                                            
protected  :         char                                         field_separator;                                           
protected  :         char                                         string_delimiter;                                          
protected  :         FILE                                        *file_handle;                                               
protected  :         PropertyHandle                               output_ph;                                                 
protected  :         DBStructDef                                 *db_struct_def;                                             
protected  :         char                                        *record_wa;                                                 
protected  :         NString                                      record_area;                                               
protected  :         int32                                        record_len;                                                
protected  :         logical                                      headline;                                                  
protected  :         logical                                      first_line;                                                

public     :
                     DataSourceHandle                            *get_data_source() { return(data_source); }
                     char                                        *get_extent_name() { return(extent_name); }
                     char                                        *get_data_source_name() { return(data_source_name); }
                     char                                        *get_file_path() { return(file_path); }
                     char                                         get_line_separator() { return(line_separator); }
                     char                                         get_field_separator() { return(field_separator); }
                     char                                         get_string_delimiter() { return(string_delimiter); }
                     FILE                                        *get_file_handle() { return(file_handle); }
                     PropertyHandle                              &get_output_ph() { return(output_ph); }
                     DBStructDef                                 *get_db_struct_def() { return(db_struct_def); }
                     char                                        *get_record_wa() { return(record_wa); }
                     NString                                     &get_record_area() { return(record_area); }
                     int32                                        get_record_len() { return(record_len); }
                     logical                                      get_headline() { return(headline); }
                     logical                                      get_first_line() { return(first_line); }
public     :         opa7ImpExp                  logical Close ( );
public     :         opa7ImpExp                                          DBQOutput (char *cpath, char *line_sep, char *field_sep, char *string_sep, logical head_line );
public     :         opa7ImpExp                                          DBQOutput (LDBQuery *qhandle, char *ds_name, char *extent );
public     :                                     logical DSClose ( );
public     :                                     logical DSOpen ( );
public     :                                     logical DSWrite (NString &result_area, PropertyHandle &prop_hdl );
public     :                                     logical FClose ( );
public     :                                     logical FOpen ( );
public     :                                     logical FWrite (NString &result_area, PropertyHandle &prop_hdl );
public     :                                     logical FWriteField (char *propstr, logical first_rec );
public     :                                     logical FWriteHeadline (NString &result_area );
public     :         opa7ImpExp                  logical Open (DBStructDef *struct_def );
public     :         opa7ImpExp                  logical Write (NString &result_area, PropertyHandle &prop_hdl );
public     :         opa7ImpExp                                          ~DBQOutput ( );
};

#pragma pack()
#endif
