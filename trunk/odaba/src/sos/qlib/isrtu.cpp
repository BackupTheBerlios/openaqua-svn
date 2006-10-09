/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    isrtu

\brief    


\date     $Date: 2006/03/12 19:22:37,25 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "isrtu"

#include  <pdefault.h>
#include  <sisrt_entry.hpp>
#include  <sisrtu.hpp>


/******************************************************************************/
/**
\brief  Clear - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void isrtu :: Clear ( )
{

  memset(srtenty,0,srtmaxe*srtelen);
  srtecnt = srtmaxe;
  
  count         = 0;
  current_index = 0;
    


}

/******************************************************************************/
/**
\brief  Count - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Count"

uint32 isrtu :: Count ( )
{

  return (count);

}

/******************************************************************************/
/**
\brief  FirstObject

\return objptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstObject"

void *isrtu :: FirstObject ( )
{

  current_index = 0;

  return ( NextObject() );


}

/******************************************************************************/
/**
\brief  GetIndex

\return lindxu -
-------------------------------------------------------------------------------
\brief i0


\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

uint32 isrtu :: GetIndex (void *objptr )
{
  isrt_entry *entry  = NULL;
  uint32      lindx0 = 0;
BEGINSEQ
  while ( entry = GetEntry(++lindx0) )
    if ( objptr == entry->datarea )                  LEAVESEQ 

ENDSEQ
  return(entry ? (lindx0 + start_index - 1) : 0);
}

/******************************************************************************/
/**
\brief i1


\param  ident -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

uint32 isrtu :: GetIndex (uint32 ident )
{
  isrt_entry *entry  = NULL;
  uint32      lindx0 = 0;

BEGINSEQ
  while ( entry = GetEntry(++lindx0) )
    if ( ident == entry->ident )                     LEAVESEQ

ENDSEQ
  return(entry ? (lindx0 + start_index - 1) : 0);
}

/******************************************************************************/
/**
\brief  GetItemID - 


\return ident -
-------------------------------------------------------------------------------
\brief i0


\param  lindxu -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetItemID"

uint32 isrtu :: GetItemID (uint32 lindxu )
{
  isrt_entry *entry  = NULL;
BEGINSEQ
  if ( !IsIndexValid(lindxu) )                       ERROR
  if ( !(entry = isrtuset(lindxu)) )                 ERROR

RECOVER

ENDSEQ
  return(entry ? entry->ident : 0);
}

/******************************************************************************/
/**
\brief i1


\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetItemID"

uint32 isrtu :: GetItemID (void *objptr )
{
  isrt_entry *entry  = NULL;
  uint32      lindx0 = 0;
BEGINSEQ
  while ( entry = GetEntry(++lindx0) )
    if ( objptr == entry->datarea )                  LEAVESEQ

ENDSEQ
  return(entry ? entry->ident : 0);
}

/******************************************************************************/
/**
\brief  GetObjectInst - 


\return objptr -

\param  lindxu -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectInst"

void *isrtu :: GetObjectInst (uint32 lindxu )
{
  isrt_entry *entry  = NULL;
BEGINSEQ
  if ( !IsIndexValid(lindxu) )                       ERROR
  if ( !(entry = isrtuset(lindxu)) )                 ERROR 

RECOVER

ENDSEQ
  return(entry ? entry->datarea : NULL);
}

/******************************************************************************/
/**
\brief  Insert - 


\return lindxu -
-------------------------------------------------------------------------------
\brief i0


\param  ident -
\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

uint32 isrtu :: Insert (uint32 ident, void *objptr )
{
  isrt_entry              entry(ident,objptr);

BEGINSEQ
  if ( !objptr )                                     ERROR

  if ( count >= (uint32)GetCount() )
  {
    if ( !(current_index = AddEntry(GetCount(),&entry)) )   
                                                     ERROR
  }
  else
  {
    current_index = 0;
    while ( GetObjectInst(start_index + (++current_index)) ) ;
    UpdateEntry(&entry,current_index);
  }  

  count++;

RECOVER
  current_index = 0;

ENDSEQ
  return(current_index ? (current_index + start_index) : 0);
}

/******************************************************************************/
/**
\brief i1


\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

uint32 isrtu :: Insert (void *objptr )
{

  return ( Insert(0,objptr) );

}

/******************************************************************************/
/**
\brief  IsIndexValid

\return cond - Return value

\param  lindxu -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIndexValid"

logical isrtu :: IsIndexValid (uint32 lindxu )
{
  isrt_entry *entry  = NULL;
BEGINSEQ
  if ( lindxu <= start_index )                       ERROR
   
  current_index = lindxu - start_index; 
  if ( !(entry = GetEntry(current_index)) )          ERROR

RECOVER

ENDSEQ
  return(entry && entry->datarea ? YES : NO);
}

/******************************************************************************/
/**
\brief  LastObject

\return objptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LastObject"

void *isrtu :: LastObject ( )
{

  current_index = srtecnt + 1;

  return ( PrevObject() );

}

/******************************************************************************/
/**
\brief  NextObject

\return objptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextObject"

void *isrtu :: NextObject ( )
{
  void       *objptr = NULL;
  while ( current_index < (uint32)srtecnt )
    if ( objptr = GetObjectInst(++current_index) )
      break;

  current_index = 0;
  return(objptr);
}

/******************************************************************************/
/**
\brief  PrevObject

\return objptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrevObject"

void *isrtu :: PrevObject ( )
{
  void       *objptr = NULL;
  while ( current_index )
    if ( objptr = GetObjectInst(--current_index) )
      break;
  return(objptr);
}

/******************************************************************************/
/**
\brief  Remove - 


\return objptr -

\param  lindxu -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *isrtu :: Remove (uint32 lindxu )
{
  isrt_entry *entry  = NULL;
BEGINSEQ
  if ( lindxu <= start_index )                       ERROR
  if ( !(entry = isrtuset(lindxu,0,NULL)) )          ERROR

RECOVER

ENDSEQ
  return(entry ? entry->datarea : NULL);
}

/******************************************************************************/
/**
\brief  Replace - 


\return objptr -
-------------------------------------------------------------------------------
\brief i0


\param  lindxu -
\param  ident -
\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

void *isrtu :: Replace (uint32 lindxu, uint32 ident, void *objptr )
{
  isrt_entry *entry  = NULL;
BEGINSEQ
  if ( !objptr )                                     ERROR
  if ( !IsIndexValid(lindxu) )                       ERROR
  if ( !(entry = isrtuset(lindxu,ident,objptr)) )    ERROR
RECOVER

ENDSEQ
  return(entry ? entry->datarea : NULL);
}

/******************************************************************************/
/**
\brief i1


\param  lindxu -
\param  ident -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

void *isrtu :: Replace (uint32 lindxu, uint32 ident )
{
  isrt_entry *entry  = NULL;
BEGINSEQ
  if ( !IsIndexValid(lindxu) )                       ERROR
  if ( !(entry = isrtuset(lindxu)) )                 ERROR

  entry->ident = ident;
RECOVER

ENDSEQ
  return(entry ? entry->datarea : NULL);
}

/******************************************************************************/
/**
\brief i2


\param  lindxu -
\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

void *isrtu :: Replace (uint32 lindxu, void *objptr )
{
  isrt_entry *entry  = NULL;
BEGINSEQ
  if ( !objptr )                                     ERROR
  if ( !IsIndexValid(lindxu) )                       ERROR
  if ( !(entry = isrtuset(lindxu)) )                 ERROR

  entry->datarea = objptr;
RECOVER

ENDSEQ
  return(entry ? entry->datarea : NULL);
}

/******************************************************************************/
/**
\brief  isrtu

-------------------------------------------------------------------------------
\brief i0


\param  start -
\param  maxe -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isrtu"

                        isrtu :: isrtu (uint32 start, int32 maxe )
                     : GSRT(isrt_entry)(maxe,sizeof(isrt_entry),
                 UNDEF,UNDEF,UNDEF,YES),
  start_index(start),
  current_index(0),
  count(0)
{

  Clear();


}

/******************************************************************************/
/**
\brief i1


\param  isrtu_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isrtu"

                        isrtu :: isrtu (const isrtu &isrtu_ref )
                     : GSRT(isrt_entry)(isrtu_ref.srtmaxe,
                 sizeof(isrt_entry),
                 UNDEF,UNDEF,UNDEF,YES),
  start_index  (isrtu_ref.start_index),
  current_index(isrtu_ref.current_index),
  count        (isrtu_ref.count)
{

  memcpy(srtenty,isrtu_ref.srtenty,srtmaxe*srtelen);
  srtecnt = srtmaxe;


}

/******************************************************************************/
/**
\brief  isrtuset

\return isrte_ptr -
-------------------------------------------------------------------------------
\brief i0


\param  lindxu -
\param  ident -
\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isrtuset"

isrt_entry *isrtu :: isrtuset (uint32 lindxu, uint32 ident, void *objptr )
{
  isrt_entry  *entry = NULL;
BEGINSEQ
  if ( !(entry = isrtuset(lindxu)) )                 ERROR
      
  if ( entry->datarea && !objptr )
    count--;
  if ( !entry->datarea && objptr )
    count++;
    
  entry->datarea = objptr;
  entry->ident   = ident;
RECOVER

ENDSEQ
  return(entry);
}

/******************************************************************************/
/**
\brief i1


\param  lindxu -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isrtuset"

isrt_entry *isrtu :: isrtuset (uint32 lindxu )
{
  isrt_entry  *entry = NULL;
BEGINSEQ
  current_index = lindxu - start_index; 
  if ( !(entry = GetEntry(current_index)) )          ERROR

RECOVER

ENDSEQ
  return(entry);
}

/******************************************************************************/
/**
\brief  ~isrtu


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~isrtu"

                        isrtu :: ~isrtu ( )
{



}


