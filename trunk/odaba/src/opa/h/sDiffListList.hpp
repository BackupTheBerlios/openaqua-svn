/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DiffListList

\brief    


\date     $Date: 2006/03/12 19:13:12,54 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DiffListList_HPP
#define   DiffListList_HPP

class     DiffListList;

#ifndef   GSRT_DiffListListEntry_HPP
#define   GSRT_DiffListListEntry_HPP
#include  <sDiffListListEntry.hpp>
#include  <sGSRT.h>
#endif
class     DifferenceList;
class     LACObject;
class     TABuffer;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  DiffListList :public GSRT(DiffListListEntry)
{
protected  :         int16                                        level ATTR_ALIGN(4);                                       
protected  :         TABuffer                                    *transaction;                                               
protected  :         LACObject                                   *ob_handle;                                                 

public     :
                     int16                                        get_level() { return(level); }
                     TABuffer                                    *get_transaction() { return(transaction); }
                     LACObject                                   *get_ob_handle() { return(ob_handle); }
public     :                                     int32 Add (DifferenceList *dlist_ptr );
public     :                                     logical Clear ( );
public     :                                     DifferenceList *Delete (int32 lindex );
public     :                                                             DiffListList (LACObject *lobhandle, TABuffer *tabuffer );
public     :                                     DifferenceList *Locate (EB_Number entnum );
public     :                                     DifferenceList *Locate (int16 indx );
public     :                                     DifferenceList *Provide_vielleicht (DifferenceList *dlist_ptr );
public     :                                                             ~DiffListList ( );
};

#pragma pack()
#endif
