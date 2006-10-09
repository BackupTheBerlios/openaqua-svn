/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CSLLHandleList

\brief    


\date     $Date: 2006/03/12 19:12:38,48 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSLLHandleList_HPP
#define   CSLLHandleList_HPP

class     CSLLHandleList;

#include  <sDLL.h>
class     CSLHandleList;
class     CSLHandleList;
class     CS_Message;
class     EntryEvent;
class     acb;
#pragma pack(8)

class  CSLLHandleList
{
protected  :         DLL(CSLHandleList)                          *handle_lists;                                              //

public     :
                     DLL(CSLHandleList)                          *get_handle_lists() { return(handle_lists); }
public     :                                     logical Add (CSLHandleList *llcs_handle );
public     :                                                             CSLLHandleList ( );
public     :                                     void Close ( );
public     :                                     logical GenerateEvent (EntryEvent *ev_ptr );
public     :                                     CSLHandleList *Remove (CSLHandleList *llcs_handle );
public     :                                                             ~CSLLHandleList ( );
};

#pragma pack()
#endif
