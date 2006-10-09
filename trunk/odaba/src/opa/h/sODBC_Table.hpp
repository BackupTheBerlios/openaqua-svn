/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_Table

\brief    


\date     $Date: 2006/03/12 19:13:41,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODBC_Table_HPP
#define   ODBC_Table_HPP

class     ODBC_Table;

#pragma pack(4)

class  ODBC_Table
{
protected  :         char                                         TABLE_QUALIFIER[32];                                       //
protected  :         char                                         TABLE_OWNER[32];                                           //
protected  :         char                                         TABLE_NAME[32];                                            //
protected  :         char                                         TABLE_TYPE[32];                                            //
protected  :         char                                         REMARKS[254];                                              //

public     :
                     char                                        *get_TABLE_QUALIFIER() { return(TABLE_QUALIFIER); }
                     char                                        *get_TABLE_OWNER() { return(TABLE_OWNER); }
                     char                                        *get_TABLE_NAME() { return(TABLE_NAME); }
                     char                                        *get_TABLE_TYPE() { return(TABLE_TYPE); }
                     char                                        *get_REMARKS() { return(REMARKS); }
public     :                                     void set_TBL_QNO (char *qualifier, char *name, char *owner );
public     :                                     void set_TBL_REMARKS (char *description );
public     :                                     void set_TBL_TYPE (char *tbl_type );
};

#pragma pack()
#endif
