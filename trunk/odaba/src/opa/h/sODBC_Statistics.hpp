/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_Statistics

\brief    


\date     $Date: 2006/03/12 19:13:41,70 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODBC_Statistics_HPP
#define   ODBC_Statistics_HPP

class     ODBC_Statistics;

#pragma pack(4)

class  ODBC_Statistics
{
protected  :         char                                         TABLE_QUALIFIER[128];                                      //
protected  :         char                                         TABLE_OWNER[128];                                          //
protected  :         char                                         TABLE_NAME[32];                                            //
protected  :         int16                                        NON_UNIQUE;                                                //
protected  :         char                                         INDEX_QUALIFIER[32];                                       //
protected  :         char                                         INDEX_NAME[32];                                            //
protected  :         int16                                        TYPE;                                                      //
protected  :         int16                                        SEQ_IN_INDEX;                                              //
protected  :         char                                         COLUMN_NAME[128];                                          //
protected  :         char                                         COLLATION;                                                 //
protected  :         int32                                        CARDINALITY;                                               //
protected  :         int32                                        PAGES;                                                     //
protected  :         char                                         FILTER_CONDITION[128];                                     //

public     :
                     char                                        *get_TABLE_QUALIFIER() { return(TABLE_QUALIFIER); }
                     char                                        *get_TABLE_OWNER() { return(TABLE_OWNER); }
                     char                                        *get_TABLE_NAME() { return(TABLE_NAME); }
                     int16                                        get_NON_UNIQUE() { return(NON_UNIQUE); }
                     char                                        *get_INDEX_QUALIFIER() { return(INDEX_QUALIFIER); }
                     char                                        *get_INDEX_NAME() { return(INDEX_NAME); }
                     int16                                        get_TYPE() { return(TYPE); }
                     int16                                        get_SEQ_IN_INDEX() { return(SEQ_IN_INDEX); }
                     char                                        *get_COLUMN_NAME() { return(COLUMN_NAME); }
                     char                                         get_COLLATION() { return(COLLATION); }
                     int32                                        get_CARDINALITY() { return(CARDINALITY); }
                     int32                                        get_PAGES() { return(PAGES); }
                     char                                        *get_FILTER_CONDITION() { return(FILTER_CONDITION); }
public     :                                     void set_CLMN_NAME (char *name );
public     :                                     void set_INDX_FLT (char *flt_cond );
public     :                                     void set_INDX_QN (char *qualifier, char *name );
public     :                                     void set_INDX_TSCCP (int16 idx_type, int16 seqnr, char collation, int32 card, int32 pages );
public     :                                     void set_UNIQUE (logical is_unique );
};

#pragma pack()
#endif
