/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    DLList

\brief    


\date     $Date: 2006/08/02 20:00:40,85 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DLList_HPP
#define   DLList_HPP

class     DLList;

class     ListNode;
#pragma pack(8)

class  DLList
{
protected  :         DLLNode                                     *m_pNodeHead;                                               // 
protected  :         DLLNode                                     *m_pNodeTail;                                               // 
protected  :         int32                                        m_nCount;                                                  // 
protected  :         DLLNode                                     *m_pNodeFree;                                               // 
protected  :         ListNode                                    *m_pBlocks;                                                 // 
protected  :         int32                                        m_nBlockSize;                                              // 

public     :
public     :                                        POSITION AddHead (void *newElement );
public     :                                        POSITION AddTail (void *newElement );
public     :                                             DLList (int32 nBlockSize );
public     :                                        POSITION Find (void *searchValue, POSITION startAfter=NULL ) const;
public     :                                        POSITION FindIndex (int32 nIndex ) const;
public     :                                        POSITION FindTail (void *searchValue, POSITION startBefore=NULL ) const;
public     :                                        void FreeNode (DLLNode *pNode );
public     :                                        POSITION InsertAfter (POSITION position, void *newElement );
public     :                                        POSITION InsertBefore (POSITION position, void *newElement );
public     :                                        DLLNode *NewNode (DLLNode *pPrev, DLLNode *pNext );
public     :                                        void RemoveAll ( );
public     :                                        void RemoveAt (POSITION position );
public     :                                        void *RemoveHead ( );
public     :                                        void *RemoveTail ( );
public     :                                        void SetAt (POSITION position, void *newElement );
public     :                                             ~DLList ( );
public     :                                        void* &GetAt (POSITION position ){
  DLLNode* pNode = (DLLNode*) position;
  static   void   *extnull = NULL;


  return ( m_nCount ? pNode->data : extnull); 

}

public     :                                        int32 GetCount ( ) const{


  return m_nCount;
}

public     :                                        void* &GetHead ( ){
  static   void   *extnull = NULL;
  return(m_nCount > 0 ? m_pNodeHead->data : extnull);

}

public     :                                        POSITION GetHeadPosition ( ) const{
  static   void   *extnull = NULL;

  return (POSITION) (m_nCount > 0 ? m_pNodeHead : extnull);
}

public     :                                        void* &GetNext (POSITION &rPosition ){
  DLLNode* pNode = (DLLNode*) rPosition;
  static   void   *extnull = NULL;

  rPosition = (POSITION) pNode->pNext;

  return ( m_nCount > 0 ? pNode->data : extnull ); 

}

public     :                                        void* &GetPrev (POSITION &rPosition ){
  DLLNode* pNode = (DLLNode*) rPosition;
  static   void   *extnull = NULL;

  rPosition = (POSITION) pNode->pPrev;

  return (m_nCount > 0 ? pNode->data : extnull); 

}

public     :                                        void* &GetTail ( ){
  static   void   *extnull = NULL;

  return(m_nCount > 0 ? m_pNodeTail->data : extnull);
}

public     :                                        POSITION GetTailPosition ( ) const{
  static   void   *extnull = NULL;

  return (POSITION) (m_nCount > 0 ? m_pNodeTail : extnull);
}

public     :                                        bool IsEmpty ( ){


  return m_nCount == 0;
}

public     :                                        void* &ReplaceAt (POSITION &rPosition, void *newElement ){
  DLLNode* pNode      = (DLLNode*) rPosition;
  void   * oldElement = NULL;

BEGINSEQ
  if ( !pNode )                                      ERROR

  oldElement = pNode->data;
  pNode->data = newElement;

RECOVER
  oldElement = NULL;
ENDSEQ
  return ( oldElement ); 

}

};

#pragma pack()
#endif
