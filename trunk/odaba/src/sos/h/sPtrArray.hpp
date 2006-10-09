/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    PtrArray

\brief    


\date     $Date: 2006/03/12 19:20:11,84 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PtrArray_HPP
#define   PtrArray_HPP

class     PtrArray;

#include  <sPtrArray.hpp>
#pragma pack(8)

class  PtrArray
{
protected  :         void                                       **m_pData;                                                   
protected  :         int32                                        m_nSize;                                                   
protected  :         int32                                        m_nMaxSize;                                                
protected  :         int32                                        m_nGrowBy;                                                 

public     :
                     void                                       **get_m_pData() { return(m_pData); }
                     int32                                        get_m_nMaxSize() { return(m_nMaxSize); }
                     int32                                        get_m_nGrowBy() { return(m_nGrowBy); }
public     :         SOS7ImpExp                  int32 Add (void *newElement );
public     :         SOS7ImpExp                  int32 Append (PtrArray &ptrasrc );
public     :         SOS7ImpExp                  void Clear ( );
public     :         SOS7ImpExp                  void Copy (PtrArray &ptrasrc );
public     :         SOS7ImpExp                  void* &ElementAt (int32 nIndex );
public     :                                     void FreeExtra ( );
public     :         SOS7ImpExp                  void *GetAt (int32 nIndex ) const;
public     :         SOS7ImpExp                  void **GetData ( );
public     :         SOS7ImpExp                  void *GetLast ( ) const;
public     :         SOS7ImpExp                  int32 GetSize ( ) const;
public     :                                     int32 GetUpperBound ( ) const;
public     :         SOS7ImpExp                  void InsertAt (int32 nIndex, void *newElement, int32 nCount );
public     :         SOS7ImpExp                  void InsertAt (int32 nIndex, void *newElement );
public     :         SOS7ImpExp                                          PtrArray ( );
public     :         SOS7ImpExp                                          PtrArray (int32 intlen );
public     :         SOS7ImpExp                  void RemoveAll ( );
public     :         SOS7ImpExp                  void RemoveAt (int32 nIndex, int32 nCount );
public     :         SOS7ImpExp                  void RemoveLast (int32 nCount );
public     :         SOS7ImpExp                  void SetAt (int32 nIndex, void *newElement );
public     :         SOS7ImpExp                  void SetAtGrow (int32 nIndex, void *newElement );
public     :         SOS7ImpExp                  void SetSize (int32 nNewSize, int32 nGrowBy );
public     :         SOS7ImpExp                  void SetSize (int32 nNewSize );
public     :         SOS7ImpExp                  void* &operator[] (int32 nIndex );
public     :         SOS7ImpExp                                          ~PtrArray ( );
};

#pragma pack()
#endif
