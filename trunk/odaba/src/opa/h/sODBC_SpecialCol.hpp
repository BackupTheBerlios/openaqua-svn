/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_SpecialCol

\brief    


\date     $Date: 2006/03/12 19:13:41,48 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODBC_SpecialCol_HPP
#define   ODBC_SpecialCol_HPP

class     ODBC_SpecialCol;

#pragma pack(4)

class  ODBC_SpecialCol
{
protected  :         int16                                        SCOPE;                                                     //
protected  :         char                                         COLUMN_NAME[128];                                          //
protected  :         int16                                        DATA_TYPE;                                                 //
protected  :         char                                         TYPE_NAME[128];                                            //
protected  :         int32                                        PRECISION;                                                 //
protected  :         int32                                        LENGTH;                                                    //
protected  :         int16                                        SCALE;                                                     //
protected  :         int16                                        PSEUDO_COLUMN;                                             //

public     :
                     int16                                        get_SCOPE() { return(SCOPE); }
                     char                                        *get_COLUMN_NAME() { return(COLUMN_NAME); }
                     int16                                        get_DATA_TYPE() { return(DATA_TYPE); }
                     char                                        *get_TYPE_NAME() { return(TYPE_NAME); }
                     int32                                        get_PRECISION() { return(PRECISION); }
                     int32                                        get_LENGTH() { return(LENGTH); }
                     int16                                        get_SCALE() { return(SCALE); }
                     int16                                        get_PSEUDO_COLUMN() { return(PSEUDO_COLUMN); }
public     :                                     void set_CLMN_NAME (char *name );
public     :                                     void set_DATA_TYPE (int16 sqltype );
public     :                                     void set_LPS (int32 length, int32 precision, int16 scale );
public     :                                     void set_PSEUDO (char is_pseudo );
public     :                                     void set_SCOPE (int16 scope );
public     :                                     void set_TYPE_NAME (char *name );
};

#pragma pack()
#endif
