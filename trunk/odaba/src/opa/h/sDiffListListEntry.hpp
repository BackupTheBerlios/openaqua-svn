/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DiffListListEntry

\brief    


\date     $Date: 2006/03/12 19:13:12,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DiffListListEntry_HPP
#define   DiffListListEntry_HPP

class     DiffListListEntry;

class     DifferenceList;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  DiffListListEntry
{
protected  :         EB_Number                                    entnr;                                                     
protected  :         DifferenceList                              *diff_list;                                                 

public     :
                     EB_Number                                   &get_entnr() { return(entnr); }
public     :                                                             DiffListListEntry (DifferenceList *dlist_ptr );
public     :                                     DifferenceList *get_diff_list ( );
};

#pragma pack()
#endif
