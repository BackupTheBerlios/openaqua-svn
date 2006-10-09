/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    CardLayoutIterator

\brief    


\date     $Date: 2006/04/10 17:55:58,68 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CardLayoutIterator"

#include  <pogui7.h>
#include  <sCardLayoutIterator.hpp>


/******************************************************************************/
/**
\brief  CardLayoutIterator - 



\param  pv_QLayoutItem - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CardLayoutIterator"

                        CardLayoutIterator :: CardLayoutIterator (std::vector<QLayoutItem*> *pv_QLayoutItem )
                     :   idx(0),
  list(pv_QLayoutItem)
{



}

/******************************************************************************/
/**
\brief  current - 


\return pQLayoutItem

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "current"

QLayoutItem *CardLayoutIterator :: current ( )
{

BEGINSEQ
  if ( !list )                                       ERROR
  return idx < list->size() ? (*list)[idx] : NULL;
RECOVER

ENDSEQ
  return NULL;
}

/******************************************************************************/
/**
\brief  next - 


\return pQLayoutItem

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "next"

QLayoutItem *CardLayoutIterator :: next ( )
{

  idx++; 
  return current();

}

/******************************************************************************/
/**
\brief  takeCurrent - 


\return pQLayoutItem - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "takeCurrent"

QLayoutItem *CardLayoutIterator :: takeCurrent ( )
{
  QLayoutItem* item;
BEGINSEQ
  if(!list)                                          ERROR
  item = (*list)[idx];
  list->erase(list->begin()+idx);
  return item;
RECOVER

ENDSEQ

}


