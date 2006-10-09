/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBViewGroupCase

\brief    Group Case


\date     $Date: 2006/03/12 19:13:06,65 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBViewGroupCase_HPP
#define   DBViewGroupCase_HPP

class     DBViewGroupCase;

class  DBViewGroupCase
{
protected  :         char                                         name[128];                                                 
protected  :         int32                                        code;                                                      
protected  :         char                                        *condition;                                                 

public     :
                     char                                        *get_name() { return(name); }
                     int32                                        get_code() { return(code); }
                     char                                        *get_condition() { return(condition); }
public     :                                                             DBViewGroupCase (char *namestr, int32 value, char *expression );
public     :                                                             DBViewGroupCase (BNFData *bnf_data );
public     :                                                             ~DBViewGroupCase ( );
};

#endif
