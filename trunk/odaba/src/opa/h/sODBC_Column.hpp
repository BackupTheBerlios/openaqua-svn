/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_Column

\brief    


\date     $Date: 2006/03/12 19:13:41,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODBC_Column_HPP
#define   ODBC_Column_HPP

class     ODBC_Column;

#pragma pack(4)

class  ODBC_Column
{
protected  :         char                                         TABLE_QUALIFIER[32];                                       //
protected  :         char                                         TABLE_OWNER[32];                                           //
protected  :         char                                         TABLE_NAME[32];                                            //
protected  :         char                                         COLUMN_NAME[128];                                          //
protected  :         int16                                        DATA_TYPE;                                                 //
protected  :         char                                         TYPE_NAME[128];                                            //
protected  :         int32                                        PRECISION;                                                 //
protected  :         int32                                        LENGTH;                                                    //
protected  :         int16                                        SCALE;                                                     //
protected  :         int16                                        RADIX;                                                     //
protected  :         int16                                        NULLABLE;                                                  //
protected  :         char                                         REMARKS[254];                                              //

public     :
                     char                                        *get_TABLE_QUALIFIER() { return(TABLE_QUALIFIER); }
                     char                                        *get_TABLE_OWNER() { return(TABLE_OWNER); }
                     char                                        *get_TABLE_NAME() { return(TABLE_NAME); }
                     char                                        *get_COLUMN_NAME() { return(COLUMN_NAME); }
                     int16                                        get_DATA_TYPE() { return(DATA_TYPE); }
                     char                                        *get_TYPE_NAME() { return(TYPE_NAME); }
                     int32                                        get_PRECISION() { return(PRECISION); }
                     int32                                        get_LENGTH() { return(LENGTH); }
                     int16                                        get_SCALE() { return(SCALE); }
                     int16                                        get_RADIX() { return(RADIX); }
                     int16                                        get_NULLABLE() { return(NULLABLE); }
                     char                                        *get_REMARKS() { return(REMARKS); }
public     :                                     void set_CLMN_NAME (char *name );
public     :                                     void set_DATA_TYPE (int16 sqltype );
public     :                                     void set_LPS (int32 length, int32 precision, int16 scale );
public     :                                     void set_NULLABLE (char is_nullable );
public     :                                     void set_RADIX (int16 radix );
public     :                                     void set_REMARKS (char *description );
public     :                                     void set_TBL_QNO (char *qualifier, char *name, char *owner );
public     :                                     void set_TYPE_NAME (char *name );
};

#pragma pack()
#endif
