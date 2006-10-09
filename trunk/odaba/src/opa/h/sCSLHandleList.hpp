/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CSLHandleList

\brief    


\date     $Date: 2006/03/12 19:12:38,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSLHandleList_HPP
#define   CSLHandleList_HPP

class     CSLHandleList;

#include  <sDLL.h>
class     CSHandleList;
class     CSHandleList;
class     CS_Message;
class     EntryEvent;
class     acb;
#pragma pack(8)

class  CSLHandleList
{
protected  :         DLL(CSHandleList)                           *handle_lists;                                              //

public     :
                     DLL(CSHandleList)                           *get_handle_lists() { return(handle_lists); }
public     :                                     logical Add (CSHandleList *lcs_handle );
public     :                                                             CSLHandleList ( );
public     :                                     void Close ( );
public     :                                     logical GenerateEvent (EntryEvent *ev_ptr );
public     :                                     CSHandleList *Remove (CSHandleList *lcs_handle );
public     :                                                             ~CSLHandleList ( );
};

#pragma pack()
#endif
