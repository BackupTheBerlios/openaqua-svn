/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    PtrArray

\brief    


\date     $Date: 2006/03/12 19:21:53,06 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "PtrArray"

#include  <pdefault.h>
#include  <sPtrArray.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return intlen -

\param  newElement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

int32 PtrArray :: Add (void *newElement )
{

  int nIndex = m_nSize;
  SetAtGrow(nIndex, newElement);


  return (nIndex); 

}

/******************************************************************************/
/**
\brief  Append - 


\return intlen -

\param  ptrasrc -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

int32 PtrArray :: Append (PtrArray &ptrasrc )
{
  int nOldSize = m_nSize;

  SetSize(m_nSize + ptrasrc.m_nSize);

  memcpy(m_pData + nOldSize, ptrasrc.m_pData, ptrasrc.m_nSize * sizeof(void*));


  return (nOldSize);

}

/******************************************************************************/
/**
\brief  Clear - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void PtrArray :: Clear ( )
{

  RemoveAll();

}

/******************************************************************************/
/**
\brief  Copy - 



\param  ptrasrc -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

void PtrArray :: Copy (PtrArray &ptrasrc )
{

  SetSize(ptrasrc.m_nSize);

  memcpy(m_pData, ptrasrc.m_pData, ptrasrc.m_nSize * sizeof(void*));


}

/******************************************************************************/
/**
\brief  ElementAt - 


\return area -

\param  nIndex -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ElementAt"

void* &PtrArray :: ElementAt (int32 nIndex )
{
  static  void  *nullptr = NULL;
  return (   nIndex >= 0 && m_nSize > nIndex 
           ? m_pData[nIndex] 
           : nullptr );


}

/******************************************************************************/
/**
\brief  FreeExtra


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeExtra"

void PtrArray :: FreeExtra ( )
{

  if (m_nSize != m_nMaxSize)
  {
    // shrink to desired size
    void** pNewData = NULL;
    if (m_nSize != 0)
    {
      pNewData = (void**) new BYTE[m_nSize * sizeof(void*)];
      // copy new data from old
      memcpy(pNewData, m_pData, m_nSize * sizeof(void*));
    }

    // get rid of old stuff (note: no destructors called)
    delete[] (BYTE*)m_pData;
    m_pData = pNewData;
    m_nMaxSize = m_nSize;
  }


}

/******************************************************************************/
/**
\brief  GetAt - 


\return area -

\param  nIndex -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAt"

void *PtrArray :: GetAt (int32 nIndex ) const
{

  return (   nIndex >= 0 && m_nSize > nIndex 
           ? m_pData[nIndex] 
           : NULL );


}

/******************************************************************************/
/**
\brief  GetData - 


\return areaptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

void **PtrArray :: GetData ( )
{


return ((void**)m_pData);

}

/******************************************************************************/
/**
\brief  GetLast

\return area -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLast"

void *PtrArray :: GetLast ( ) const
{


  return ( m_nSize > 0 ? m_pData[m_nSize-1] : NULL );

}

/******************************************************************************/
/**
\brief  GetSize - 


\return intlen -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

int32 PtrArray :: GetSize ( ) const
{


return (this ? m_nSize : 0);

}

/******************************************************************************/
/**
\brief  GetUpperBound

\return intlen -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUpperBound"

int32 PtrArray :: GetUpperBound ( ) const
{


  return (m_nSize-1);

}

/******************************************************************************/
/**
\brief  InsertAt - 


-------------------------------------------------------------------------------
\brief i0


\param  nIndex -
\param  newElement -
\param  nCount -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertAt"

void PtrArray :: InsertAt (int32 nIndex, void *newElement, int32 nCount )
{

BEGINSEQ
  if ( nIndex < 0 )                                  ERROR
    
  if (nIndex >= m_nSize)
  {
    // adding after the end of the array
    SetSize(nIndex + nCount);  // grow so nIndex is valid
  }
  else
  {
    // inserting in the middle of the array
    int nOldSize = m_nSize;
    SetSize(m_nSize + nCount);  // grow it to new size
    // shift old data up to fill gap
    memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
    (nOldSize-nIndex) * sizeof(void*));

    // re-init slots we copied from

    memset(&m_pData[nIndex], 0, nCount * sizeof(void*));

  }

  // copy elements into the empty space
  while (nCount--)
  m_pData[nIndex++] = newElement;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i1


\param  nIndex -
\param  newElement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertAt"

void PtrArray :: InsertAt (int32 nIndex, void *newElement )
{

InsertAt(nIndex, newElement, 1);

}

/******************************************************************************/
/**
\brief  PtrArray

-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PtrArray"

                        PtrArray :: PtrArray ( )
                     : m_pData(NULL),
  m_nSize(0),
  m_nMaxSize(0),
  m_nGrowBy(0)
{



}

/******************************************************************************/
/**
\brief i1


\param  intlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PtrArray"

                        PtrArray :: PtrArray (int32 intlen )
                     : m_pData(NULL),
  m_nSize(0),
  m_nMaxSize(0),
  m_nGrowBy(0)
{

  if (intlen > 0)
    SetAtGrow(--intlen, NULL);

}

/******************************************************************************/
/**
\brief  RemoveAll - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAll"

void PtrArray :: RemoveAll ( )
{

  SetSize(0);


}

/******************************************************************************/
/**
\brief  RemoveAt - 



\param  nIndex -
\param  nCount -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAt"

void PtrArray :: RemoveAt (int32 nIndex, int32 nCount )
{

  // just remove a range
  int nMoveCount = m_nSize - (nIndex + nCount);

  if (nMoveCount)
    memmove(&m_pData[nIndex], &m_pData[nIndex + nCount],
            nMoveCount * sizeof(void*));
  m_nSize -= nCount;


}

/******************************************************************************/
/**
\brief  RemoveLast


\param  nCount -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveLast"

void PtrArray :: RemoveLast (int32 nCount )
{

  // just remove a range
  RemoveAt(m_nSize-nCount,nCount);


}

/******************************************************************************/
/**
\brief  SetAt - 



\param  nIndex -
\param  newElement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAt"

void PtrArray :: SetAt (int32 nIndex, void *newElement )
{

  if ( nIndex >= 0 && m_nSize > nIndex )
    m_pData[nIndex] = newElement;


}

/******************************************************************************/
/**
\brief  SetAtGrow - 



\param  nIndex -
\param  newElement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAtGrow"

void PtrArray :: SetAtGrow (int32 nIndex, void *newElement )
{

  if ( nIndex >= 0 )
  {
    if ( nIndex >= m_nSize )
      SetSize(nIndex+1);
    m_pData[nIndex] = newElement;
  }


}

/******************************************************************************/
/**
\brief  SetSize - 


-------------------------------------------------------------------------------
\brief i0


\param  nNewSize -
\param  nGrowBy -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void PtrArray :: SetSize (int32 nNewSize, int32 nGrowBy )
{

  if (nGrowBy != -1)
    m_nGrowBy = nGrowBy;  // set new size

  if (nNewSize == 0)
  {
    // shrink to nothing
    delete[] (BYTE*)m_pData;
    m_pData = NULL;
    m_nSize = m_nMaxSize = 0;
  }
  else if (m_pData == NULL)
  {
    // create one with exact size
   
    m_pData = (void**) new BYTE[nNewSize * sizeof(void*)];

    memset(m_pData, 0, nNewSize * sizeof(void*));  // zero fill

    m_nSize = m_nMaxSize = nNewSize;
  }
  else if (nNewSize <= m_nMaxSize)
  {
    // it fits
    if (nNewSize > m_nSize)
    {
      // initialize the new elements

      memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(void*));

    }

    m_nSize = nNewSize;
  }
  else
  {
    // otherwise, grow array
    int nGrowBy = m_nGrowBy;
    if (nGrowBy == 0)
    {
      // heuristically determine growth when nGrowBy == 0
      //  (this avoids heap fragmentation in many situations)
      nGrowBy = MIN(1024, MAX(4, m_nSize / 8));
    }
    int nNewMax;
    if (nNewSize < m_nMaxSize + nGrowBy)
      nNewMax = m_nMaxSize + nGrowBy;  // granularity
    else
      nNewMax = nNewSize;  // no slush

    void** pNewData = (void**) new BYTE[nNewMax * sizeof(void*)];

    // copy new data from old
    memcpy(pNewData, m_pData, m_nSize * sizeof(void*));

    // construct remaining elements
    memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(void*));


    // get rid of old stuff (note: no destructors called)
    delete[] (BYTE*)m_pData;
    m_pData = pNewData;
    m_nSize = nNewSize;
    m_nMaxSize = nNewMax;
  }


}

/******************************************************************************/
/**
\brief i1


\param  nNewSize -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void PtrArray :: SetSize (int32 nNewSize )
{

SetSize(nNewSize, -1);

}

/******************************************************************************/
/**
\brief  operator[] - 


\return area -

\param  nIndex -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator[]"

void* &PtrArray :: operator[] (int32 nIndex )
{


  return ElementAt(nIndex);

}

/******************************************************************************/
/**
\brief  ~PtrArray


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~PtrArray"

                        PtrArray :: ~PtrArray ( )
{

  delete[] (BYTE*)m_pData;


}


