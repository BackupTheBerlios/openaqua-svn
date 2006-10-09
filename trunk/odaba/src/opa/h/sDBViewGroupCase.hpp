/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    DBViewGroupCase

\brief    Group Case


\date     $Date: 2006/08/25 15:12:21,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBViewGroupCase_HPP
#define   DBViewGroupCase_HPP

class     DBViewGroupCase;

class  DBViewGroupCase
{
protected  :         char                                         name[128];                                                 // 
protected  :         int32                                        code;                                                      // 
protected  :         char                                        *condition;                                                 // 

public     :
                     char                                        *get_name() { return(name); }
                     int32                                        get_code() { return(code); }
                     char                                        *get_condition() { return(condition); }
public     :                                             DBViewGroupCase (char *namestr, int32 value, char *expression );
public     :                                             DBViewGroupCase (BNFData *bnf_data );
public     :                                             ~DBViewGroupCase ( );
};

#endif
