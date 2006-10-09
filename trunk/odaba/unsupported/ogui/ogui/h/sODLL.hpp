/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODLL

\brief    Double linked list
          This  class supports a sort of fast double linked list. Entries in the
          list  are directly linked, which  requires a member dllLink (ODLLItem)
          in  the  linked  entry.  The  linked  entry  must  not be derived from
          ODLLItem. 
          es and outer widgets for certain controls.
          Complex  controls  are  collecting  the  events  from  all  associated
          controls  and sending  the events  to the parent. Subordinated complex
          controls  as labes do not handle  events explicitly but sending events
          to  the  parent,  the  control  owning the label. You may set an event
          handler  for the control,  which receives all  events collected by the
          control (see OEH).

\date     $Date: 2006/03/13 21:33:51,71 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODLL_HPP
#define   ODLL_HPP


#include  <sODLLItem.hpp>
#include  <sODLLIterator.hpp>
#pragma pack(4)

template < class T, class O=T >
class  ODLL
{
public     :         typedef ODLL<T,O>                            M;                                                         //
protected  :         typedef int                                  (*Compare)( void*, T*);                                    //
public     :         T                                           *first;                                                     //
public     :         T                                           *last;                                                      //
public     :         typedef ODLLIterator<T,O,M>                  Iterator;                                                  //
protected  :         int                                          count;                                                     //
protected  :         T                                           *current;                                                   //
protected  :         int                                          currentIdx;                                                //
protected  :         int64                                        timetag;                                                   //
protected  :         Iterator                                    *iterators;                                                 //

public     :
public     :                                     void Append (T *pT ){
  ODLLItem     *t;
  count++;
  
  current    = 0;
  t          = item(pT);
  t->timetag = timetag;
  t->next    = 0;

  if ( t->prev = last )
    last = (T*)(item(last)->next = pT);
  else
    first = last = pT;


}

public     :                                     logical BinarySearch (Compare vCompare, void *pData, int align ){
  int            l    = 0;
  int            h    = count - 1;
  int            i;
  int            c;
  logical        term = YES;
  while( l <= h )
  {
    i = (l+h)/2;
    c = (*vCompare)(pData,(*this)[i]);
    if ( c > 0 ) 
      l = i + 1;
    else if ( c < 0 ) 
      h = i - 1;
    else
    {
      term = NO;
      if ( align == 0 ) 
      { 
        l = h = i; 
        break; 
      }
      else if ( align > 0 ) 
        l = i + 1;
      else if ( align < 0 ) 
        h = i - 1;
    }
  }

  if ( term || align <= 0 ) 
    go(l);
  else 
    go(h);
  return(term);
}

public     :                                     void Clear ( ){
  Iterator   *it;
  first   = 0;
  last    = 0;
  count   = 0;
  current = 0;

  it = iterators;
  while ( it )
  {
    it->respectClear();
    it = it->next;
  }

}

public     :                                     int Count ( ) const{

  return count;

}

public     :                                     void Insert (T *pT ){
  ODLLItem   *t;
BEGINSEQ
  if ( !current )
  {
    Append(pT);
    LEAVESEQ
  }

  count++;

  t          = item(pT);
  t->timetag = timetag;
  t->next    = current;

  if ( t->prev = item(current)->prev )
    item((T*)t->prev)->next = pT;
  item(current)->prev = pT;

  if ( current == first ) 
    first = pT;
  current = pT;
ENDSEQ

}

public     :                                     void Insert (int index, T *pT ){

go( index );
Insert( pT );

}

public     :                                     Iterator Iterate (logical fSkipNew ) const{

  return Iterator(this,fSkipNew);

}

public     :                                     T *Next ( ) const{

  if ( !current ) 
    return 0;
  else 
    return (*this)[currentIdx + 1];


}

public     :                                                             ODLL ( )                     :   first(0),
  last(0),
  count(0),
  current(0),
  currentIdx(-1),
  timetag(0),
  iterators(0)
{



}

public     :                                     void Remove (T *pT ){
  Iterator  *it;
  ODLLItem  *t;
  T         *p;
  T         *n;

  count--;
  current = 0;

  it = iterators;
  while ( it )
  {
    it->respectRemoved(pT);
    it = it->next;
  }

  t = item(pT);
  p = (T*)item(pT)->prev;
  n = (T*)item(pT)->next;

  if ( p )
    item(p)->next = n;
  else
    first = n;
  
  if ( n )
    item(n)->prev = p;
  else
    last = p;
 
  t->prev = t->next = 0;


}

protected  :                                     void go (int index ) const{
  M   *that = (M*)this; // mutable
  T   *s;
  int  sd;
  int  df;
  int  dl;
  int  dcr;
  int  dc;

  if ( index < 0 || index >= count ) 
    that->current = 0;
  else
  {
    df  = index;
    dl  = count - index - 1;
    dcr = index - currentIdx;
    dc  = dcr < 0 ? -dcr : dcr;
  
    if ( current && dc < df && dc < dl ) 
    {
      s  = current;
      sd = dcr;
    }
    else if ( df < dl )
    {
      s  = first;
      sd = df;
    }
    else
    {
      s  = last;
      sd = -dl;
    }
  
    if ( sd < 0 )
    {
      do 
        s = (T*)item(s)->prev; 
      while ( ++sd );
    }
    else if ( sd > 0 )
    {
      do 
        s = (T*)item(s)->next; 
      while ( --sd );
    }
    
    that->current    = s;
    that->currentIdx = index;
  }

}

public     : static                              ODLLItem *__cdecl item (T *pT ){
  O   *o = pT; // implicit cast (safer than direct casting!!)

  return &o->dllLink;

}

public     :                                     T *operator[] (int index ) const{

  go(index);
  return current;

}

public     :                                     int64 subscribe (Iterator *pIterator ) const{
  M    *that = (M*)this; // mutable

  pIterator->prev = 0;
  pIterator->next = iterators;

  if ( iterators ) 
    iterators->prev = pIterator;

  that->iterators = pIterator;
  that->timetag++;
  return timetag;
}

public     :                                     void unsubscribe (Iterator *pIterator ) const{
  M   *that = (M*)this; // mutable

  if ( !pIterator->prev ) 
    that->iterators = pIterator->next;
  else 
    pIterator->prev->next = pIterator->next;

  if ( pIterator->next ) 
    pIterator->next->prev = pIterator->prev;


}

};

#pragma pack()
#endif
