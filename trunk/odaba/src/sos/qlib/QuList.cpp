/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    QuList

\brief    


\date     $Date: 2006/08/02 20:01:09,71 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "QuList"

#include  <pdefault.h>
#include  <cdllist.h>
#include  <cglbct.h>
#include  <sDLList.hpp>
#include  <sQuList.hpp>


/******************************************************************************/
/**
\brief  AddHead - Add List Entry at head of list

        The  function  add  a  list  entry  on  top of the list. The entry added
        becomes the current entry


\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddHead"

void QuList :: AddHead (void *entptr )
{

  if ( ListObject(YES) )
    if ( pos = listobj->AddHead(entptr) )
      top = bottom = 0;



}

/******************************************************************************/
/**
\brief  AddTail - 




\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddTail"

void QuList :: AddTail (void *entptr )
{

  if ( ListObject(YES) )
    if ( pos = listobj->AddTail(entptr) )
      top = bottom = 0;


}

/******************************************************************************/
/**
\brief  Clear - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical QuList :: Clear ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  
  while ( RemoveTail() ) ;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy - 



\return term - Success

\param  rlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical QuList :: Copy (QuList &rlist )
{
  void      *object = NULL;
  logical    term   = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  rlist.GoTop();
  while ( object = rlist.GetNext() )
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

int QuList :: Find (void *entptr )
{
  logical   cond = YES;
BEGINSEQ
  if ( !ListObject(NO) || !(pos = listobj->Find(entptr)) ) ERROR
    
  bottom = top = 0; 

RECOVER
  if ( this )
    top = 1;
  cond = NO;
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

int QuList :: FindIndex (int int_indx0 )
{
  logical   cond = YES;
BEGINSEQ
  if ( !ListObject(NO) || !(pos = listobj->FindIndex(int_indx0)) ) ERROR
    
  bottom = top = 0; 

RECOVER
  if ( this )
    top = 1; 
  cond = NO;

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

int QuList :: FindTail (void *entptr )
{
  logical   cond = YES;
BEGINSEQ
  if ( !ListObject(NO) || !(pos = listobj->FindTail(entptr)) ) ERROR
    
  bottom = top = 0; 

RECOVER
  if ( this )
    top = 1;
  cond = NO;
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

VOID_PtrRef QuList :: Get (int32 indx0 )
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

VOID_PtrRef QuList :: GetAt ( )
{
  static  void *ext_null = NULL;
  return ( ListObject(NO) && pos ? listobj->GetAt(pos) : ext_null );

}

/******************************************************************************/
/**
\brief  GetCount - 



\return ecnt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int QuList :: GetCount ( )
{

  return( this && listobj ? listobj->GetCount() : 0);

}

/******************************************************************************/
/**
\brief  GetHead - 



\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHead"

VOID_PtrRef QuList :: GetHead ( )
{

  if ( this )
  {
    top = bottom = 0;
  
    if ( listobj )
      if ( !(pos = listobj->GetHeadPosition()) )
        top = 1;
  }
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

VOID_PtrRef QuList :: GetNext ( )
{
  static  void *ext_null = NULL;
  if ( !ListObject(NO) || bottom ) 
    return(ext_null);
                        
  if ( !pos ) 
    top = 1;
    
  if ( top ) 
  { 
    top=0; 
    return(GetHead()); 
  }
  
  listobj->GetNext(pos);
  if ( !pos ) 
    bottom = 1;
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

VOID_PtrRef QuList :: GetObjectInst (int int_indx0 )
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

int32 QuList :: GetPosition (void *entptr )
{
  void                   *item = GetHead();
  int32                   int_indx0 = 0;
BEGINSEQ
  if ( !ListObject(NO) )                             ERROR
    
  while ( item != entptr && (item = GetNext()) )
    int_indx0++;

  if ( !item )                                       ERROR
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

VOID_PtrRef QuList :: GetPrev ( )
{
  static  void *ext_null = NULL;
  if ( !ListObject(NO) || top ) 
    return(ext_null);
  
  if ( !pos ) 
    bottom = 1;
  
  if ( bottom ) 
  { 
    bottom=0; 
    return(GetTail()); 
  }
  
  listobj->GetPrev(pos);
  if ( !pos ) 
    top = 1;
  return(GetAt());

}

/******************************************************************************/
/**
\brief  GetTail - 



\return entptrr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTail"

VOID_PtrRef QuList :: GetTail ( )
{

  if ( this )
  {
    top = bottom = 0;
  
    if ( listobj )
      if ( !(pos = listobj->GetTailPosition()) )
        bottom = 1;
  }
  return(GetAt());
}

/******************************************************************************/
/**
\brief  GoBottom - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoBottom"

void QuList :: GoBottom ( )
{

  if ( this )
  {
    top    = 0; 
    bottom = 1;  
    if ( listobj )
      pos    = listobj->GetTailPosition();
  }

}

/******************************************************************************/
/**
\brief  GoTop - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoTop"

void QuList :: GoTop ( )
{

  if ( this )
  {
    top    = 1; 
    bottom = 0; 
    if ( listobj )
      pos    = listobj->GetHeadPosition();
  }

}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical QuList :: Initialize ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this || listobj )                              ERROR
  
  pos     = NULL;
  mlist   = 1;
  extnull = NULL;
  top     = 0;
  bottom  = 0;

  ListObject(YES);


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

void QuList :: Insert (void *entptr, int int_indx0 )
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
\brief  InsertAfter - 




\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertAfter"

void QuList :: InsertAfter (void *entptr )
{

  if ( ListObject(YES) )   
    if ( pos = listobj->InsertAfter(pos,entptr) )
      top = bottom = 0;


}

/******************************************************************************/
/**
\brief  InsertBefore - 




\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertBefore"

void QuList :: InsertBefore (void *entptr )
{

  if ( ListObject(YES) )   
    if ( pos = listobj->InsertBefore(pos,entptr) )
      top = bottom = 0;


}

/******************************************************************************/
/**
\brief  IsOwner - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOwner"

logical QuList :: IsOwner ( )
{

  return ( this ? mlist : NO );

}

/******************************************************************************/
/**
\brief  ListObject - 



\return dll_list - 

\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListObject"

DLList *QuList :: ListObject (logical provide )
{

  if ( !this  )                                    
    return(NULL);
    
  if ( !listobj && provide )
  {
    mlist = 1;
    listobj = new DLList(10);
    lo_count++;     
  }
  return(listobj);


}

/******************************************************************************/
/**
\brief  QuList - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "QuList"

     QuList :: QuList ( )
                     :   pos(NULL),
  mlist(0),
  extnull(NULL),
  top(0),
  bottom(0),
  listobj(NULL)
{

__Increase();

}

/******************************************************************************/
/**
\brief  i02 - 



\param  blockcount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "QuList"

     QuList :: QuList (uint16 blockcount )
                     : pos(NULL),
  mlist(1),
  extnull(NULL),
  top(0),
  bottom(0),
  listobj(NULL)
{

  if ( blockcount > 0 )
  {
    listobj = new DLList(blockcount);
    lo_count++;
  }
__Increase();

}

/******************************************************************************/
/**
\brief  i1 - 



\param  rlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "QuList"

     QuList :: QuList (QuList &rlist )
                     :   pos(NULL),
  mlist(0),
  extnull(NULL),
  top(0),
  bottom(0),
  listobj(rlist.listobj)
{

__Increase();

}

/******************************************************************************/
/**
\brief  ReleaseList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseList"

void QuList :: ReleaseList ( )
{

  if ( mlist && listobj ) 
  {  
    delete listobj;  
    listobj = NULL;
    lo_count--;
  } 


}

/******************************************************************************/
/**
\brief  Remove - Remove antry from list



\return entptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  int_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *QuList :: Remove (int int_indx0 )
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
\brief  i01 - 



\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *QuList :: Remove (void *entptr )
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

void *QuList :: RemoveAt ( )
{
  void      *entptr = GetAt();

  if ( ListObject(NO) && entptr ) 
  { 
    listobj->RemoveAt(pos); 
    pos    = 0;
    bottom = 0;
    top    = 1;
  }

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

void *QuList :: RemoveHead ( )
{
  void      *entptr = extnull;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( listobj && !listobj->IsEmpty() )
    entptr = listobj->RemoveHead();

  pos    = 0;
  bottom = 0;
  top    = 1;
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

void *QuList :: RemoveTail ( )
{
  void      *entptr = extnull;
BEGINSEQ
  if ( !this )                                   ERROR
    
  if ( listobj && !listobj->IsEmpty() )
    entptr = listobj->RemoveTail();

  pos    = 0;
  bottom = 1;
  top    = 0;
RECOVER

ENDSEQ
  return(entptr);
}

/******************************************************************************/
/**
\brief  ReplaceAt - 



\return entptr - 

\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceAt"

void *QuList :: ReplaceAt (void *entptr )
{
  logical   cond = YES;
  if ( ListObject(NO) && entptr ) 
    entptr = listobj->ReplaceAt(pos,entptr); 
    

  return(entptr);
}

/******************************************************************************/
/**
\brief  SetAt - 




\param  entptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAt"

void QuList :: SetAt (void *entptr )
{

  if ( ListObject(NO) )
    listobj->SetAt(pos,entptr);


}

/******************************************************************************/
/**
\brief  __Decrease - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__Decrease"

void QuList :: __Decrease ( )
{

  dll_count--;
  
//  __all_dlls.Remove(this);


}

/******************************************************************************/
/**
\brief  __Increase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__Increase"

void QuList :: __Increase ( )
{

  dll_count++;

//  __all_dlls.AddTail(this);  


}

/******************************************************************************/
/**
\brief  __TraceList - 



\return count - 

\param  max_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__TraceList"

int32 __cdecl QuList :: __TraceList (int64 max_count )
{
  QuList                 *dllptr;
  dllptr = __all_dlls.GetTail();
  while ( dllptr && max_count-- )
    dllptr = __all_dlls.GetPrev();

// normalerweise ist der count 4 und drei dll's in der kette (globale listen)
  return(dll_count);
}

/******************************************************************************/
/**
\brief  operator= - 



\return rlist - 

\param  rlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

QuList &QuList :: operator= (QuList &rlist )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  ReleaseList();
 
  mlist    = NO;
  extnull  = NULL;
  
  pos      = rlist.pos;
  top      = rlist.top;
  bottom   = rlist.bottom;
  listobj  = rlist.listobj;
RECOVER

ENDSEQ
  return(*this);
}

/******************************************************************************/
/**
\brief  ~QuList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~QuList"

     QuList :: ~QuList ( )
{

  ReleaseList();
  
__Decrease();

}


