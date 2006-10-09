/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_SetIndex

\brief    External Index definition


\date     $Date: 2006/03/13 21:30:12,39 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_SetIndex_HPP
#define   SDB_SetIndex_HPP

class     SDB_SetIndex;

#include  <sEB_Number.hpp>
#pragma pack(8)

class  SDB_SetIndex
{
protected  :         char                                         sys_ident[40];                                             //
protected  :         EB_Number                                    skyrex;                                                    //

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     EB_Number                                   &get_skyrex() { return(skyrex); }
};

#pragma pack()
#endif
