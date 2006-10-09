/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    XList



\date     $Date: 2006/04/26 22:26:39,07 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XList_HPP
#define   XList_HPP

#include "csosdll.h"
class     XList;

#define  VOID_PtrRef                               void  *&
class     DLList;
#include  <sQuList.hpp>
#pragma pack(8)

class  XList :public QuList
{
protected  :         void                                        *object_ref;                                                

public     :
                     void                                        *get_object_ref() { return(object_ref); }
public     :         SOSImpExp                   void AddHead (void *entptr );
public     :         SOSImpExp                   void AddTail (void *entptr );
public     :         SOSImpExp                   logical Clear ( );
public     :         SOSImpExp                   logical Copy (XList &xlist_ref );
public     :         SOSImpExp                   int Find (void *entptr );
public     :         SOSImpExp                   int FindIndex (int int_indx0 );
public     :         SOSImpExp                   int FindTail (void *entptr );
public     :         SOSImpExp                   VOID_PtrRef Get (int32 indx0 );
public     :         SOSImpExp                   VOID_PtrRef GetAt ( );
public     :         SOSImpExp                   int GetCount ( );
public     :         SOSImpExp                   VOID_PtrRef GetHead ( );
public     :         SOSImpExp                   VOID_PtrRef GetNext ( );
public     :         SOSImpExp                   VOID_PtrRef GetObjectInst (int int_indx0 );
public     :         SOSImpExp                   int32 GetPosition (void *entptr );
public     :         SOSImpExp                   VOID_PtrRef GetPrev ( );
public     :         SOSImpExp                   VOID_PtrRef GetTail ( );
public     :         SOSImpExp                   void GoBottom ( );
public     :         SOSImpExp                   void GoTop ( );
public     :                                     logical Initialize ( );
public     :         SOSImpExp                   void Insert (void *entptr, int int_indx0 );
public     :         SOSImpExp                   void InsertAfter (void *entptr );
public     :         SOSImpExp                   void InsertBefore (void *entptr );
public     :         SOSImpExp                   void *Remove (int int_indx0 );
public     :         SOSImpExp                   void *Remove (void *entptr );
public     :         SOSImpExp                   void *RemoveAt ( );
public     :         SOSImpExp                   void *RemoveHead ( );
public     :         SOSImpExp                   void *RemoveTail ( );
public     :         SOSImpExp                   void SetAt (void *entptr );
public     :                                     logical UpgradeList ( );
public     :         SOSImpExp                                           XList ( );
public     :         SOSImpExp                                           XList (XList &xlist_ref );
public     :         SOSImpExp                   QuList &operator= (XList &xlist );
public     :         SOSImpExp                                           ~XList ( );
};

#pragma pack()
#endif
