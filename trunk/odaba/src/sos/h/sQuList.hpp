/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    QuList

\brief    


\date     $Date: 2006/08/02 20:01:02,67 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   QuList_HPP
#define   QuList_HPP

#include "csosdll.h"
class     QuList;

#define  VOID_PtrRef                               void  *&
class     DLList;
#include  <sQuList.hpp>
#pragma pack(8)

#include "padcstd.h"
//#include "coguidll.h"
//#include "codaba2.h"
//#include "cqt.h"

class  QuList
{
protected  :         POSITION                                     pos;                                                       // 
protected  :         int                                          mlist;                                                     // 
protected  :         void                                        *extnull;                                                   // 
protected  :         char                                         top;                                                       // 
protected  :         char                                         bottom;                                                    // 
protected  :         DLList                                      *listobj;                                                   // 

public     :
public     :                  SOSImpExp             void AddHead (void *entptr );
public     :                  SOSImpExp             void AddTail (void *entptr );
public     :                  SOSImpExp             logical Clear ( );
public     :                  SOSImpExp             logical Copy (QuList &rlist );
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
public     :                                        DLList *ListObject (logical provide );
public     :                  SOSImpExp                  QuList ( );
public     :                  SOSImpExp                  QuList (uint16 blockcount );
public     :                  SOSImpExp                  QuList (QuList &rlist );
public     :                                        void ReleaseList ( );
public     :                  SOSImpExp             void *Remove (int int_indx0 );
public     :                  SOSImpExp             void *Remove (void *entptr );
public     :                  SOSImpExp             void *RemoveAt ( );
public     :                  SOSImpExp             void *RemoveHead ( );
public     :                  SOSImpExp             void *RemoveTail ( );
public     :                  SOSImpExp             void *ReplaceAt (void *entptr );
public     :                  SOSImpExp             void SetAt (void *entptr );
public     :                                        void __Decrease ( );
public     :                                        void __Increase ( );
public     : static           SOSImpExp             int32 __cdecl __TraceList (int64 max_count );
public     :                  SOSImpExp             QuList &operator= (QuList &rlist );
public     :                  SOSImpExp                  ~QuList ( );
};

#pragma pack()
#endif
