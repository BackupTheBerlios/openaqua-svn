/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    SList

\brief    


\date     $Date: 2006/06/13 12:38:00,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SList_HPP
#define   SList_HPP

#include "csosdll.h"
class     SList;

#define  VOID_PtrRef                               void  *&
#include  <sLIST.h>
class     VOID_Ptr;
#include  <sSList.hpp>
#pragma pack(8)

class  SList
{
protected  :         int32                                        mlist;                                                     // 
protected  :         void                                        *extnull;                                                   // 
protected  :         logical                                      top;                                                       // 
protected  :         LIST(void*)                               *listobj;                                                   // 
protected  :         LIST(void*)::iterator                        current;                                                   // 

public     :
                     int32                                        get_mlist() { return(mlist); }
                     void                                        *get_extnull() { return(extnull); }
                     logical                                      get_top() { return(top); }
                     LIST(void*)::iterator                       &get_current() { return(current); }
public     :                  SOSImpExp             void AddHead (void *entptr );
public     :                  SOSImpExp             void AddTail (void *entptr );
public     :                  SOSImpExp             logical Clear ( );
public     :                  SOSImpExp             logical Copy (SList &rslist );
public     :                  SOSImpExp             int Find (void *entptr );
public     :                  SOSImpExp             int FindIndex (int int_indx0 );
public     :                  SOSImpExp             int FindTail (void *entptr );
public     :                  SOSImpExp             VOID_PtrRef Get (int32 indx0 );
public     :                  SOSImpExp             VOID_PtrRef GetAt ( );
public     :                  SOSImpExp             int GetCount ( );
public     :                  SOSImpExp             VOID_PtrRef GetHead ( );
public     :                  SOSImpExp             VOID_PtrRef GetNext ( );
public     :                  SOSImpExp             VOID_PtrRef GetObjectInst (int int_indx0 );
public     :                  SOSImpExp             int32 GetPosition (void *entptr );
public     :                  SOSImpExp             VOID_PtrRef GetPrev ( );
public     :                  SOSImpExp             VOID_PtrRef GetTail ( );
public     :                  SOSImpExp             void GoBottom ( );
public     :                  SOSImpExp             void GoTop ( );
public     :                                        logical Initialize ( );
public     :                  SOSImpExp             void Insert (void *entptr, int int_indx0 );
public     :                  SOSImpExp             void InsertAfter (void *entptr );
public     :                  SOSImpExp             void InsertBefore (void *entptr );
public     :                  SOSImpExp             logical IsOwner ( );
public     :                  SOSImpExp             void *Remove (int int_indx0 );
public     :                  SOSImpExp             void *Remove (void *entptr );
public     :                  SOSImpExp             void *RemoveAt ( );
public     :                  SOSImpExp             void *RemoveHead ( );
public     :                  SOSImpExp             void *RemoveTail ( );
public     :                  SOSImpExp                  SList ( );
public     :                  SOSImpExp                  SList (uint16 blockcount );
public     :                  SOSImpExp                  SList (SList &rslist );
public     :                  SOSImpExp             void SetAt (void *entptr );
public     :                  SOSImpExp             SList &operator= (SList &rslist );
public     :                  SOSImpExp                  ~SList ( );
};

#pragma pack()
#endif
