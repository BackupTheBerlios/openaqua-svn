/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ParmString

\brief    


\date     $Date: 2006/03/12 19:13:44,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ParmString_HPP
#define   ParmString_HPP

class     ParmString;

#pragma pack(8)

class  ParmString
{
protected  :         char                                         sys_ident[40];                                             //
protected  :         char                                         value[81];                                                 //

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     char                                        *get_value() { return(value); }
};

#pragma pack()
#endif
