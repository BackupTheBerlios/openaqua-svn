/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_TypeInfo

\brief    


\date     $Date: 2006/03/12 19:13:42,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODBC_TypeInfo_HPP
#define   ODBC_TypeInfo_HPP

class     ODBC_TypeInfo;

#pragma pack(4)

class  ODBC_TypeInfo
{
protected  :         char                                         TYPE_NAME[128];                                            //
protected  :         int16                                        DATA_TYPE;                                                 //
protected  :         int32                                        PRECISION;                                                 //
protected  :         char                                         LITERAL_PREFIX[128];                                       //
protected  :         char                                         LITERAL_SUFFIX[128];                                       //
protected  :         char                                         CREATE_PARAMS[128];                                        //
protected  :         int16                                        NULLABLE;                                                  //
protected  :         int16                                        CASE_SENSITIVE;                                            //
protected  :         int16                                        SEARCHABLE;                                                //
protected  :         int16                                        UNSIGNED_ATTRIB;                                           //
protected  :         int16                                        MONEY;                                                     //
protected  :         int16                                        AUTO_INCREMENT;                                            //
protected  :         char                                         LOCAL_TYPE_NAME[128];                                      //
protected  :         int16                                        MINIMUM_SCALE;                                             //
protected  :         int16                                        MAXIMUM_SCALE;                                             //
protected  :         int16                                        sql_match;                                                 //

public     :
                     char                                        *get_TYPE_NAME() { return(TYPE_NAME); }
                     int16                                        get_DATA_TYPE() { return(DATA_TYPE); }
                     int32                                        get_PRECISION() { return(PRECISION); }
                     char                                        *get_LITERAL_PREFIX() { return(LITERAL_PREFIX); }
                     char                                        *get_LITERAL_SUFFIX() { return(LITERAL_SUFFIX); }
                     char                                        *get_CREATE_PARAMS() { return(CREATE_PARAMS); }
                     int16                                        get_NULLABLE() { return(NULLABLE); }
                     int16                                        get_CASE_SENSITIVE() { return(CASE_SENSITIVE); }
                     int16                                        get_SEARCHABLE() { return(SEARCHABLE); }
                     int16                                        get_UNSIGNED_ATTRIB() { return(UNSIGNED_ATTRIB); }
                     int16                                        get_MONEY() { return(MONEY); }
                     int16                                        get_AUTO_INCREMENT() { return(AUTO_INCREMENT); }
                     char                                        *get_LOCAL_TYPE_NAME() { return(LOCAL_TYPE_NAME); }
                     int16                                        get_MINIMUM_SCALE() { return(MINIMUM_SCALE); }
                     int16                                        get_MAXIMUM_SCALE() { return(MAXIMUM_SCALE); }
                     int16                                        get_sql_match() { return(sql_match); }
public     :                                                             ODBC_TypeInfo (char *name, int16 sqltype, int32 prec, char *prfx, char *suff, char *args, char isNULL, char isCS, char isSRCH, char isUNSD, char isMNY, char isAINC, int16 smin, int16 smax, int16 sqlish );
public     :                                     void set_LOCAL_NAME (char *name );
};

#pragma pack()
#endif
