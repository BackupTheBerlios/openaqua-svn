/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODLLIterator

\brief    


\date     $Date: 2006/03/13 21:33:52,25 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODLLIterator_HPP
#define   ODLLIterator_HPP


class     ODLLIterator;
#include  <sODLLItem.hpp>
#pragma pack(4)

template < class T, class O, class L >
class  ODLLIterator
{
public     :         ODLLIterator                                *prev;                                                      //
public     :         ODLLIterator                                *next;                                                      //
protected  :         const L                                     *list;                                                      //
protected  :         T                                           *current;                                                   //
protected  :         int64                                        timetag;                                                   //
protected  :         int                                          direction;                                                 //

public     :
public     :                                     void First ( ){

direction= +1;

current= list->first;

if( timetag >= 0 )
  while( current && L::item( current )->timetag >= timetag ) 
    current= (T*) L::item( current )->next;


}

public     :                                     void Last ( ){

direction= -1;

current= list->last;

if( timetag >= 0 )
  while( current && L::item( current )->timetag >= timetag ) 
    current= (T*) L::item( current )->prev;


}

public     :                                                             ODLLIterator (const L *pcL, logical fSkipNew )                     : prev(0),
  next(0),
  list(pcL),
  current(pcL->first),
  timetag(0),
  direction(1)
{

timetag= pcL->subscribe( this );
if( !fSkipNew ) timetag= -1;

}

public     :                                     T *operator++ (int dummy ){

direction= +1;

T* c= current;
current= c ? (T*) L::item( c )->next : 0;

if( timetag >= 0 )
  while( current && L::item( current )->timetag >= timetag ) 
    current= (T*) L::item( current )->next;
    
return c;


}

public     :                                     T *operator-- (int dummy ){

direction= -1;

T* c= current;
current= c ? (T*) L::item( c )->prev : 0;

if( timetag >= 0 )
  while( current && L::item( current )->timetag >= timetag ) 
    current= (T*) L::item( current )->prev;
    
return c;

}

public     :                                     void respectClear ( ){

current= 0;

}

public     :                                     void respectRemoved (T *pT ){

if( current == pT ) 
{
  if( direction >= 0 ) (*this)++;
  else (*this)--;
}

}

public     :                                                             ~ODLLIterator ( ){

if( list ) list->unsubscribe( this );

}

};

#pragma pack()
#endif
