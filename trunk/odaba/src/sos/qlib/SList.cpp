/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    SList

\brief    


\date     $Date: 2006/06/13 12:39:26,79 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SList"

#include  <pdefault.h>
#include  <cdllist.h>
#ifndef   LIST_VOID_Ptr_HPP
#define   LIST_VOID_Ptr_HPP
#include  <sLIST.h>
#endif
#include  <sSList.hpp>


/******************************************************************************/
/**
\brief  AddHead - 



\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddHead"

void SList :: AddHead (void *entptr )
{

BEGINSEQ
if(!this || !listobj)                               ERROR
listobj->push_front(entptr);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  AddTail - 



\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddTail"

void SList :: AddTail (void *entptr )
{

BEGINSEQ
if(!this || !listobj)                               ERROR
listobj->push_back(entptr);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Clear - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical SList :: Clear ( )
{
  logical                 term = NO;
BEGINSEQ
if(!this || !listobj)                               ERROR
listobj->clear();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy - 


\return term - 

\param  rslist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical SList :: Copy (SList &rslist )
{
  void                   *object;
  logical                 term = NO;
BEGINSEQ
  if(!this || !listobj)                               ERROR    
  rslist.GoTop();
  while ( object = rslist.GetNext() )
    AddTail(object);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Find - 


\return intval - 

\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

int SList :: Find (void *entptr )
{
  logical   cond = NO;
  std::list<void*>::iterator it;
BEGINSEQ
if(!this || !listobj)                               ERROR
  for( it = listobj->begin(); it != listobj->end() && !cond; it++)
    if( *it == entptr )
      cond = YES;

current = it;

RECOVER
  if ( this ){
    top = 1;
    if(listobj)  current = listobj->begin();
  }
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  FindIndex - 


\return intval - 

\param  int_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindIndex"

int SList :: FindIndex (int int_indx0 )
{
  logical   cond = YES;
  LIST(void*)::iterator it;
BEGINSEQ
if(!this || !listobj)                               ERROR
current = listobj->begin();
if( int_indx0<0 )                                   ERROR
for( it = listobj->begin(); it != listobj->end() && int_indx0 ; it++ )
  int_indx0--;
cond = it!=listobj->end();
current = it;

RECOVER
  if ( this ){
    top = 1; 
    if( listobj )  current = listobj->begin();
  }

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  FindTail - 


\return intval - 

\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindTail"

int SList :: FindTail (void *entptr )
{
  logical   cond = NO;
  LIST(void*)::iterator it;
BEGINSEQ
if(!this || !listobj)                               ERROR
  for( it = listobj->end(); it != listobj->begin() && !cond; it--)
    if( *it == entptr)
      cond = YES;
current = it;

RECOVER
  if ( this )
    top = 1;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Get - 


\return entptrr - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

VOID_PtrRef SList :: Get (int32 indx0 )
{

  FindIndex(indx0);
  return(GetAt());

}

/******************************************************************************/
/**
\brief  GetAt - 


\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAt"

VOID_PtrRef SList :: GetAt ( )
{
void* entptr = extnull;
BEGINSEQ
if( this && listobj )                               ERROR
if( current != listobj->end())                      ERROR
entptr = *current;
RECOVER

ENDSEQ
 return entptr;
}

/******************************************************************************/
/**
\brief  GetCount - 


\return ecnt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int SList :: GetCount ( )
{
int isize = 0;
BEGINSEQ
if(!this || !listobj)                               ERROR
isize = listobj->size();
RECOVER

ENDSEQ
return isize;
}

/******************************************************************************/
/**
\brief  GetHead - 


\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHead"

VOID_PtrRef SList :: GetHead ( )
{

BEGINSEQ
if(!this || !listobj)                               ERROR
current = listobj->begin();
top = current == listobj->end();
RECOVER

ENDSEQ
  return(GetAt());
}

/******************************************************************************/
/**
\brief  GetNext - 


\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNext"

VOID_PtrRef SList :: GetNext ( )
{

BEGINSEQ
if(!this || !listobj)                               ERROR
if ( current == listobj->end())                     ERROR
    
  if ( top && current == listobj->begin() ) 
    top=0; 
  else
    current++;

RECOVER
  top = 1;
ENDSEQ
  return(GetAt());
}

/******************************************************************************/
/**
\brief  GetObjectInst - 


\return entptrr - 

\param  int_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectInst"

VOID_PtrRef SList :: GetObjectInst (int int_indx0 )
{

  FindIndex(int_indx0);
  return(GetAt());
}

/******************************************************************************/
/**
\brief  GetPosition - 


\return int_indx0 - 

\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

int32 SList :: GetPosition (void *entptr )
{
  int32                   int_indx0 = 0;
  LIST(void*)::iterator   it;
BEGINSEQ
  if ( !this || !listobj )                          ERROR
  for( it = listobj->begin(); it != listobj->end(); it++){
    if( *it == entptr )
      LEAVESEQ;
    int_indx0++;
  }
  ERROR

RECOVER
  int_indx0 = AUTO;
ENDSEQ
  return(int_indx0);
}

/******************************************************************************/
/**
\brief  GetPrev - 


\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrev"

VOID_PtrRef SList :: GetPrev ( )
{

BEGINSEQ
  if ( !this )                                      ERROR
  current--;
RECOVER

ENDSEQ
  return GetAt();
}

/******************************************************************************/
/**
\brief  GetTail - 


\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTail"

VOID_PtrRef SList :: GetTail ( )
{

BEGINSEQ
  if( !this || !listobj)                            ERROR
  current = listobj->end();
  current--;
RECOVER

ENDSEQ
  return(GetAt());
}

/******************************************************************************/
/**
\brief  GoBottom - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoBottom"

void SList :: GoBottom ( )
{

BEGINSEQ
  if ( !this || !listobj )                          ERROR
  current = listobj->end();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  GoTop - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoTop"

void SList :: GoTop ( )
{

BEGINSEQ
  if ( !this || listobj )                           ERROR
  top     = 1; 
  current = listobj->begin();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical SList :: Initialize ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this  )                                     ERROR
  extnull = NULL;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Insert - 



\param  entptr - 
\param  int_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

void SList :: Insert (void *entptr, int int_indx0 )
{
  int        count = GetCount();
BEGINSEQ
  if ( !this  )                                     ERROR
  
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
\brief  InsertAfter - 



\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertAfter"

void SList :: InsertAfter (void *entptr )
{
  LIST(void*)::iterator it;
BEGINSEQ
if ( !this || listobj )                           ERROR
it = current;
it++;
listobj->insert( it, entptr );

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  InsertBefore - 



\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertBefore"

void SList :: InsertBefore (void *entptr )
{

BEGINSEQ
if( !this || !listobj )                             ERROR
listobj->insert( current, entptr );

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  IsOwner - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOwner"

logical SList :: IsOwner ( )
{

  return ( this ? mlist : NO );

}

/******************************************************************************/
/**
\brief  Remove - 


\return entptr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  int_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *SList :: Remove (int int_indx0 )
{
  void       *entptr = NULL;
BEGINSEQ
  if ( !this || !listobj )                          ERROR
  if ( !FindIndex(int_indx0) )                      ERROR
  entptr = GetAt();
  listobj->erase(current);
RECOVER

ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *SList :: Remove (void *entptr )
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
\brief  RemoveAt - 


\return entptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAt"

void *SList :: RemoveAt ( )
{
  void      *entptr = GetAt();

BEGINSEQ
  if ( !this || !listobj )                          ERROR
  listobj->erase(current);
RECOVER

ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  RemoveHead - 


\return entptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveHead"

void *SList :: RemoveHead ( )
{
  void      *entptr = extnull;
BEGINSEQ
  if ( !this || !listobj )                          ERROR
  entptr  = GetHead();
  listobj->pop_front();
RECOVER

ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  RemoveTail - 


\return entptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveTail"

void *SList :: RemoveTail ( )
{
  void      *entptr = extnull;
BEGINSEQ
  if ( !this || !listobj )                          ERROR
  entptr = GetTail();
  listobj->pop_back();
RECOVER

ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  SList - 


-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SList"

     SList :: SList ( )
                     :   mlist(1),
  extnull(NULL),
  top(0),
  listobj(new std::list<void*>())
{



}

/******************************************************************************/
/**
\brief  i02 - 


\param  blockcount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SList"

     SList :: SList (uint16 blockcount )
                     :   mlist(1),
  extnull(NULL),
  top(0),
  listobj(NULL)
{

  if ( blockcount > 0 )
    listobj = new std::list<void*>(blockcount);


}

/******************************************************************************/
/**
\brief  i1 - 


\param  rslist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SList"

     SList :: SList (SList &rslist )
                     :   mlist(0),
  extnull(NULL),
  top(0),
  listobj(rslist.listobj)
{



}

/******************************************************************************/
/**
\brief  SetAt - 



\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAt"

void SList :: SetAt (void *entptr )
{

BEGINSEQ
  if ( !this || !listobj )                          ERROR
  *current = entptr;


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  operator= - 


\return rslist - 

\param  rslist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

SList &SList :: operator= (SList &rslist )
{

BEGINSEQ
  if ( !this )                                       ERROR

  if ( mlist && listobj ) 
  {  
    delete listobj;  
    listobj = NULL;
  } 
 
  mlist    = NO;
  extnull  = NULL;
  
  top      = rslist.top;
  listobj  = rslist.listobj;

RECOVER

ENDSEQ
  return(*this);
}

/******************************************************************************/
/**
\brief  ~SList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SList"

     SList :: ~SList ( )
{

  if ( mlist )
  { 
    delete listobj;
    listobj = NULL;
  }


}


