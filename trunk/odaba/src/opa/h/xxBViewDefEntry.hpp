/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBViewDefEntry

\brief    


\date     $Date: 2006/03/12 19:13:06,04 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBViewDefEntry_HPP
#define   DBViewDefEntry_HPP

class     DBViewDefEntry;

class     DBQOutput;
class     LDBQuery;
#include  <sDBViewDef.hpp>
#include  <sNString.hpp>
#pragma pack(8)

class  DBViewDefEntry
{
protected  :         int32                                        query_id;                                                  
protected  :         LDBQuery                                    *query_handle;                                              
protected  :         char                                         query_name[40];                                            
protected  :         char                                        *view_def;                                                  
protected  :         DBViewDef                                   *db_view_def;                                               
protected  :         DBQOutput                                   *query_output;                                              

public     :
                     int32                                        get_query_id() { return(query_id); }
                     LDBQuery                                    *get_query_handle() { return(query_handle); }
                     char                                        *get_query_name() { return(query_name); }
                     char                                        *get_view_def() { return(view_def); }
                     DBViewDef                                   *get_db_view_def() { return(db_view_def); }
                     DBQOutput                                   *get_query_output() { return(query_output); }
public     :                                     void Clear ( );
public     :                                                             DBViewDefEntry ( );
public     :                                                             DBViewDefEntry (LDBQuery *qhandle, int32 qid, char *view_definition );
public     :                                     char *Execute (NString &result_area, char *parm_string );
public     :                                     char GetSeparator (char *string, char default_sep );
public     :                                     logical Initialize (char *view_definition );
public     :                                     logical ReplaceParameters (char *parm_string );
public     :                                     DBQOutput *SetFields (LDBQuery *qhandle, char *field_list );
public     :                                     logical SetOutputOptions (LDBQuery *qhandle, char *options );
public     :                                     void Uninitialize ( );
};

#pragma pack()
#endif
