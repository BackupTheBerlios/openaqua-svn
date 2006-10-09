/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    isrt

\brief    


\date     $Date: 2006/03/12 19:22:36,42 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "isrt"

#include  <pdefault.h>
#include  <csmcbmac.h>
#include  <sisrt.hpp>


/******************************************************************************/
/**
\brief  Copy - 


\return term - Success

\param  isrtref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical isrt :: Copy (const isrt &isrtref )
{
  isrt_entry       *entry;
  short             indx = 0;

  while ( entry = ((isrt *)&isrtref)->GetEntry(++indx) )
    AddEntry(entry);

  return(NO);
}

/******************************************************************************/
/**
\brief  Get - 


\return objptr -

\param  ident -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *isrt :: Get (uint32 ident ) const
{
  isrt_entry             *entry;
  return ( (entry = ((isrt *)this)->GetEntry((char *)&ident))
           ? entry->datarea
           : NULL                            );

}

/******************************************************************************/
/**
\brief  GetItemID - 


\return ident -
-------------------------------------------------------------------------------
\brief i0


\param  indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetItemID"

uint32 isrt :: GetItemID (int16 indx ) const
{
  isrt_entry         *entry;
  return( (entry = ((isrt *)this)->GetEntry(indx))
          ? entry->ident
          : 0                      );

}

/******************************************************************************/
/**
\brief i1


\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetItemID"

uint32 isrt :: GetItemID (void *objptr ) const
{
  isrt_entry         *entry;
  short               indx = 0;
  int                 id = 0;
  while ( !id && (entry = ((isrt *)this)->GetEntry(++indx)) )
    if ( entry->datarea == objptr )
      id = entry->ident;

  return(id);
}

/******************************************************************************/
/**
\brief  GetObjectInst - 


\return objptr -

\param  indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectInst"

void *isrt :: GetObjectInst (int16 indx ) const
{
  isrt_entry         *entry;
  return( (entry = ((isrt *)this)->GetEntry(indx))
          ? entry->datarea
          : NULL                      );

}

/******************************************************************************/
/**
\brief  Insert - 


\return ident -
-------------------------------------------------------------------------------
\brief i0


\param  ident -
\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

uint32 isrt :: Insert (uint32 ident, void *objptr )
{
  isrt_entry              entry(ident,objptr);
  return ( AddEntry(&entry) ? ident : 0 );

}

/******************************************************************************/
/**
\brief i1


\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

uint32 isrt :: Insert (void *objptr )
{
  uint32           ident = 0;
  ident = GetCount() ? GetEntry(GetCount())->ident+1 : 1;

  ident = Insert(ident,objptr);
  return(ident);
}

/******************************************************************************/
/**
\brief  Remove - 


\return objptr -

\param  ident -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *isrt :: Remove (uint32 ident )
{
  short                   indx;
  void                   *objptr = NULL;
BEGINSEQ
  if ( !(indx = FindEntry((void *)&ident)) )         ERROR
  
  objptr = GetEntry(indx)->datarea;
  DeleteEntry(indx);

RECOVER

ENDSEQ
  return(objptr);
}

/******************************************************************************/
/**
\brief  isrt - 


-------------------------------------------------------------------------------
\brief i0


\param  maxe -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isrt"

                        isrt :: isrt (int32 maxe )
                     : GSRT(isrt_entry)(maxe,
                 sizeof(isrt_entry),
                 4,1,'I',YES)
{



}

/******************************************************************************/
/**
\brief i1


\param  isrtref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isrt"

                        isrt :: isrt (const isrt &isrtref )
                     : GSRT(isrt_entry)(
       ((isrt *)&isrtref)->GetCount(),
       sizeof(isrt_entry),
       4,1,'I',YES)
{

  Copy(isrtref);

}

/******************************************************************************/
/**
\brief  operator!= - 


\return term - Success

\param  isrtref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical isrt :: operator!= (const isrt &isrtref ) const
{

  return( !(*this == isrtref) );

}

/******************************************************************************/
/**
\brief  operator= - 


\return isrtref -

\param  isrtref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

isrt &isrt :: operator= (const isrt &isrtref )
{

  Copy(isrtref);
  return(*this);
}

/******************************************************************************/
/**
\brief  operator== - 


\return cond - Return value

\param  isrtref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical isrt :: operator== (const isrt &isrtref ) const
{
  isrt_entry       *entry1;
  isrt_entry       *entry2;
  short             indx = 0;
  logical           cond = YES;
BEGINSEQ
  if ( ((isrt *)this)->GetCount() != ((isrt *)&isrtref)->GetCount() )
                                                     ERROR
    
  while ( (entry1 = ((isrt *)this)->GetEntry(++indx)) &&
          (entry2 = ((isrt *)&isrtref)->GetEntry(indx)) )
    if ( entry1 != entry2 )                          ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ~isrt - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~isrt"

                        isrt :: ~isrt ( )
{



}


