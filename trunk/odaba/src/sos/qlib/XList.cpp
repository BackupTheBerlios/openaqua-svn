/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    XList



\date     $Date: 2006/04/26 22:26:45,14 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XList"

#include  <pdefault.h>
#include  <cdllist.h>
#include  <sDLList.hpp>
#include  <sXList.hpp>


/******************************************************************************/
/**
\brief  AddHead


\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddHead"

void XList :: AddHead (void *entptr )
{

BEGINSEQ
  if ( !this || !entptr )                           ERROR
  
  if ( !listobj && !object_ref )
  {
    object_ref = entptr;
    if ( pos = (POSITION)object_ref )
      top = bottom = 0;    
  }
  else 
  {
    if ( !listobj )
      UpgradeList();
    QuList::AddHead(entptr);
  }
RECOVER
ENDSEQ

}

/******************************************************************************/
/**
\brief  AddTail


\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddTail"

void XList :: AddTail (void *entptr )
{

BEGINSEQ
  if ( !this || !entptr )                           ERROR
  
  if ( !listobj && !object_ref )
  {
    object_ref = entptr;
    if ( pos = (POSITION)object_ref )
      top = bottom = 0;    
  }
  else 
  {
    if ( !listobj )
      UpgradeList();
    QuList::AddTail(entptr);
  }
RECOVER
ENDSEQ

}

/******************************************************************************/
/**
\brief  Clear

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical XList :: Clear ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  
  object_ref = NULL;
  while ( RemoveTail() ) ;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy

\return term

\param  xlist_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical XList :: Copy (XList &xlist_ref )
{
  void      *object = NULL;
  logical    term   = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  xlist_ref.GoTop();
  while ( object = xlist_ref.GetNext() )
    AddTail(object);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Find

\return intval

\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

int XList :: Find (void *entptr )
{
  logical   cond = YES;
BEGINSEQ
  if ( !this || !entptr )                           ERROR

  if ( listobj )
    cond = QuList::Find(entptr);
  else
  {
    if ( object_ref != entptr )                     ERROR
    pos = (POSITION)object_ref;
    bottom = top = 0; 
  }
RECOVER
  if ( this )
  {
    pos = (POSITION)NULL;
    top = 1; 
  }
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  FindIndex

\return intval

\param  int_indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindIndex"

int XList :: FindIndex (int int_indx0 )
{
  logical   cond = YES;
BEGINSEQ
  if ( !this )                                      ERROR

  if ( listobj )
    cond = QuList::FindIndex(int_indx0);
  else
  {
    if ( !object_ref || int_indx0 != 0 )            ERROR
    pos = (POSITION)object_ref;
    bottom = top = 0; 
  }
RECOVER
  if ( this )
  {
    pos = (POSITION)NULL;
    top = 1; 
  }
  cond = NO;

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  FindTail

\return intval

\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindTail"

int XList :: FindTail (void *entptr )
{
  logical   cond = YES;
BEGINSEQ
  if ( !this || !entptr )                           ERROR

  if ( listobj )
    cond = QuList::FindTail(entptr);
  else
  {
    if ( object_ref != entptr )                     ERROR
    pos = (POSITION)object_ref;
    bottom = top = 0; 
  }
RECOVER
  if ( this )
  {
    pos = (POSITION)NULL;
    top = 1; 
  }
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Get

\return entptrr - 

\param  indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

VOID_PtrRef XList :: Get (int32 indx0 )
{

  FindIndex(indx0);
  return(GetAt());

}

/******************************************************************************/
/**
\brief  GetAt

\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAt"

VOID_PtrRef XList :: GetAt ( )
{

  return (   !this             ? extnull
           : listobj           ? QuList::GetAt()
           : object_ref && pos ? object_ref
                               : extnull         );

}

/******************************************************************************/
/**
\brief  GetCount

\return ecnt

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int XList :: GetCount ( )
{

  return (   !this      ? 0
           : listobj    ? QuList::GetCount()
           : object_ref ? 1
                        : 0                   );

}

/******************************************************************************/
/**
\brief  GetHead

\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHead"

VOID_PtrRef XList :: GetHead ( )
{

BEGINSEQ
  if ( !this )                                      ERROR
  
  if ( listobj )
    return ( QuList::GetHead() );
  else
  {
    top = bottom = 0;
    if ( !(pos = (POSITION)object_ref) )
      top = 1;
  }
RECOVER
ENDSEQ
  return(GetAt());
}

/******************************************************************************/
/**
\brief  GetNext

\return entptrr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNext"

VOID_PtrRef XList :: GetNext ( )
{

  if ( !this || bottom ) 
    return(extnull);

  if ( listobj )
    return(QuList::GetNext());
  else
  {
    if ( !pos ) 
      top = 1;

    if ( top ) 
    { 
      top = 0; 
      return(GetHead()); 
    }

    pos    = (POSITION)NULL; 
    bottom = 1;
    return(GetAt());
  }


}

/******************************************************************************/
/**
\brief  GetObjectInst

\return entptrr - 

\param  int_indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectInst"

VOID_PtrRef XList :: GetObjectInst (int int_indx0 )
{

  FindIndex(int_indx0);
  return(GetAt());
}

/******************************************************************************/
/**
\brief  GetPosition

\return int_indx0

\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

int32 XList :: GetPosition (void *entptr )
{
  int32                   int_indx0 = 0;
BEGINSEQ
  if ( !this && !entptr )                            ERROR

  if ( listobj )
    int_indx0 = QuList::GetPosition(entptr);
  else
  {
    if ( entptr != object_ref )                      ERROR
    pos = (POSITION)object_ref;
    bottom = top = 0; 
  }
RECOVER
  if ( this )
  {
    pos = (POSITION)NULL;
    top = 1; 
  }
  int_indx0 = AUTO;
ENDSEQ
  return(int_indx0);
}

/******************************************************************************/
/**
\brief  GetPrev

\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrev"

VOID_PtrRef XList :: GetPrev ( )
{

  if ( !this || top ) 
    return(extnull);

  if ( listobj )
    return(QuList::GetPrev());
  else
  {
    if ( !pos ) 
      bottom = 1;

    if ( bottom ) 
    { 
      bottom = 0; 
      return(GetTail()); 
    }

    pos = (POSITION)NULL; 
    top = 1;
    return(GetAt());
  }


}

/******************************************************************************/
/**
\brief  GetTail

\return entptrr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTail"

VOID_PtrRef XList :: GetTail ( )
{

BEGINSEQ
  if ( !this )                                      ERROR

  if ( listobj )
    return( QuList::GetTail() );
  else
  {
    top = bottom = 0; 
    if ( !(pos = (POSITION)object_ref) )
      bottom = 1; 
  }

RECOVER
ENDSEQ
  return(GetAt());
}

/******************************************************************************/
/**
\brief  GoBottom


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoBottom"

void XList :: GoBottom ( )
{
BEGINSEQ
  if ( !this )                                      ERROR

  if ( listobj )
    QuList::GoBottom();
  else
  {
    pos = (POSITION)object_ref;
    top    = 0; 
    bottom = 1; 
  }
RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  GoTop


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoTop"

void XList :: GoTop ( )
{
BEGINSEQ
  if ( !this )                                      ERROR

  if ( listobj )
    QuList::GoTop();
  else
  {
    pos = (POSITION)object_ref;
    top    = 1; 
    bottom = 0; 
  }
RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  Initialize

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical XList :: Initialize ( )
{
  logical                 term = NO;
  QuList::Initialize();
  object_ref = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  Insert


\param  entptr - 
\param  int_indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

void XList :: Insert (void *entptr, int int_indx0 )
{
  int        count = GetCount();
BEGINSEQ
  if ( !ListObject(YES) )                           ERROR
  
  if ( !count )
  {  
    AddHead(entptr);
    LEAVESEQ
  }
  
  if ( int_indx0 >= count )
  {
    AddTail(entptr);
    LEAVESEQ
  }
  
  if ( FindIndex(int_indx0) )
  {
    InsertBefore(entptr);
    LEAVESEQ
  }

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  InsertAfter


\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertAfter"

void XList :: InsertAfter (void *entptr )
{
BEGINSEQ
  if ( !this || !entptr )                                 ERROR
  
  if ( listobj )
    QuList::InsertAfter(entptr);
  else
    AddTail(entptr);

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  InsertBefore


\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertBefore"

void XList :: InsertBefore (void *entptr )
{
BEGINSEQ
  if ( !this || !entptr )                                 ERROR
  
  if ( listobj )
    QuList::InsertBefore(entptr);
  else
    AddHead(entptr);

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  Remove

\return entptr - 
-------------------------------------------------------------------------------
\brief  i0


\param  int_indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *XList :: Remove (int int_indx0 )
{
  void       *entptr = NULL;
BEGINSEQ
  if ( !FindIndex(int_indx0) )                       ERROR
    
  entptr = RemoveAt();
RECOVER

ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  i01


\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *XList :: Remove (void *entptr )
{

BEGINSEQ
  if ( !FindTail(entptr) )                       ERROR
    
  entptr = RemoveAt();
RECOVER
  entptr = NULL;
ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  RemoveAt

\return entptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAt"

void *XList :: RemoveAt ( )
{
  static void *ext_null = NULL;
  void        *entptr   = ext_null;

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( listobj )
    entptr = QuList::RemoveAt();
  else if ( object_ref && pos )
  {
    entptr = object_ref;
    object_ref = NULL;
  
    pos    = NULL;
    bottom = 0;
    top    = 1;
  }


RECOVER
ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  RemoveHead

\return entptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveHead"

void *XList :: RemoveHead ( )
{
  static void *ext_null = NULL;
  void        *entptr   = ext_null;

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( listobj )
    entptr = QuList::RemoveHead();
  else if ( object_ref )
  {
    entptr = object_ref;
    object_ref = NULL;
  
    pos    = NULL;
    bottom = 0;
    top    = 1;
  }
RECOVER
ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  RemoveTail

\return entptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveTail"

void *XList :: RemoveTail ( )
{
  static void *ext_null = NULL;
  void        *entptr   = ext_null;

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( listobj )
    entptr = QuList::RemoveTail();
  else if ( object_ref )
  {
    entptr = object_ref;
    object_ref = NULL;
  
    pos    = NULL;
    bottom = 1;
    top    = 0;
  }
RECOVER
ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  SetAt


\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAt"

void XList :: SetAt (void *entptr )
{
  if ( this && pos )
  {
    if ( listobj )   
      QuList::SetAt(entptr);
    else
      pos = (POSITION)(object_ref = entptr);
  }
}

/******************************************************************************/
/**
\brief  UpgradeList

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpgradeList"

logical XList :: UpgradeList ( )
{
  logical      term = NO;
BEGINSEQ
  if ( listobj )                                    ERROR
  
  QuList::AddTail(object_ref);
  object_ref = NULL;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  XList

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XList"

                        XList :: XList ( )
                     : QuList(0),
  object_ref(NULL)
{

}

/******************************************************************************/
/**
\brief  i1


\param  xlist_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XList"

                        XList :: XList (XList &xlist_ref )
                     : QuList(xlist_ref),
  object_ref(xlist_ref.get_object_ref())
{

}

/******************************************************************************/
/**
\brief  operator=

\return rlist

\param  xlist
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

QuList &XList :: operator= (XList &xlist )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  *(QuList *)this = xlist;
  object_ref = xlist.get_object_ref();
RECOVER
ENDSEQ
  return(*this);
}

/******************************************************************************/
/**
\brief  ~XList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~XList"

                        XList :: ~XList ( )
{

}


