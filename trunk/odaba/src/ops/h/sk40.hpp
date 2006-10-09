/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    k40

\brief    


\date     $Date: 2006/03/13 21:30:14,57 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   k40_HPP
#define   k40_HPP

class     k40;

#pragma pack(4)

class  k40
{
protected  :         char                                         sys_ident[40];                                             //

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
};

#pragma pack()
#endif
