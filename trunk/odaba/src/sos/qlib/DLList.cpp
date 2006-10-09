/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    DLList

\brief    


\date     $Date: 2006/08/02 20:00:42,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DLList"

#include  <pdefault.h>
#include  <cdllist.h>
#include  <sListNode.hpp>
#include  <sDLList.hpp>


/******************************************************************************/
/**
\brief  AddHead - 



\return pos - 

\param  newElement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddHead"

POSITION DLList :: AddHead (void *newElement )
{
  DLLNode* pNewNode = NewNode(NULL, m_pNodeHead);

  pNewNode->data = newElement;
  if (m_pNodeHead != NULL)
    m_pNodeHead->pPrev = pNewNode;
  else
    m_pNodeTail = pNewNode;
  m_pNodeHead = pNewNode;
  

  return (POSITION) pNewNode;
}

/******************************************************************************/
/**
\brief  AddTail - 



\return pos - 

\param  newElement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddTail"

POSITION DLList :: AddTail (void *newElement )
{
  DLLNode* pNewNode = NewNode(m_pNodeTail, NULL);

  pNewNode->data = newElement;
  
  if (m_pNodeTail != NULL)
    m_pNodeTail->pNext = pNewNode;
  else
    m_pNodeHead = pNewNode;
  
  m_pNodeTail = pNewNode;

  return (POSITION) pNewNode;

}

/******************************************************************************/
/**
\brief  DLList - 




\param  nBlockSize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLList"

     DLList :: DLList (int32 nBlockSize )
{

  m_nCount = 0;
  m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
  m_pBlocks = NULL;
  m_nBlockSize = nBlockSize;


}

/******************************************************************************/
/**
\brief  Find - 



\return pos - 

\param  searchValue - 
\param  startAfter - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

POSITION DLList :: Find (void *searchValue, POSITION startAfter ) const
{
  DLLNode* pNode = (DLLNode*) startAfter;

  if ( m_nCount )
  {    
    for ( pNode = !pNode ? m_pNodeHead : pNode->pNext;
          pNode != NULL; 
          pNode = pNode->pNext )
      if (pNode->data == searchValue)
        return (POSITION) pNode;
  }
  return NULL;
  



}

/******************************************************************************/
/**
\brief  FindIndex - 



\return pos - 

\param  nIndex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindIndex"

POSITION DLList :: FindIndex (int32 nIndex ) const
{
  DLLNode* pNode = m_pNodeHead;

  if (nIndex >= m_nCount || nIndex < 0)
    return NULL;

  while (nIndex--)
  {
    pNode = pNode->pNext;
  }

  return (POSITION) pNode;

}

/******************************************************************************/
/**
\brief  FindTail - 



\return pos - 

\param  searchValue - 
\param  startBefore - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindTail"

POSITION DLList :: FindTail (void *searchValue, POSITION startBefore ) const
{
  DLLNode* pNode = (DLLNode*) startBefore;

  if ( m_nCount )
  {    
    for ( pNode = !pNode ? m_pNodeTail : pNode->pPrev;
          pNode != NULL; 
          pNode = pNode->pPrev )
      if (pNode->data == searchValue)
        return (POSITION) pNode;
  }
  return NULL;


}

/******************************************************************************/
/**
\brief  FreeNode - 




\param  pNode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeNode"

void DLList :: FreeNode (DLLNode *pNode )
{

  pNode->pNext = m_pNodeFree;
  m_pNodeFree = pNode;
  m_nCount--;
  
  if (m_nCount == 0)
    RemoveAll();


}

/******************************************************************************/
/**
\brief  InsertAfter - 



\return pos - 

\param  position - 
\param  newElement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertAfter"

POSITION DLList :: InsertAfter (POSITION position, void *newElement )
{
  DLLNode* pOldNode = (DLLNode*) position;
  DLLNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);

  if (position == NULL)
    return AddTail(newElement);
  
  pNewNode->data = newElement;

  if (pOldNode->pNext != NULL)
  {
    pOldNode->pNext->pPrev = pNewNode;
  }
  else
  {
    m_pNodeTail = pNewNode;
  }
  
  pOldNode->pNext = pNewNode;

  return (POSITION) pNewNode;

}

/******************************************************************************/
/**
\brief  InsertBefore - 



\return pos - 

\param  position - 
\param  newElement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertBefore"

POSITION DLList :: InsertBefore (POSITION position, void *newElement )
{
  DLLNode* pOldNode;
  DLLNode* pNewNode;

  if (position == NULL)
    return AddHead(newElement);
  
  pOldNode = (DLLNode*) position;
  pNewNode = NewNode(pOldNode->pPrev, pOldNode);
  
  if (position == NULL)
    return AddHead(newElement);

  pNewNode->data = newElement;

  if (pOldNode->pPrev != NULL)
  {
    pOldNode->pPrev->pNext = pNewNode;
  }
  else
  {
    m_pNodeHead = pNewNode;
  }
  pOldNode->pPrev = pNewNode;

  return (POSITION) pNewNode;

}

/******************************************************************************/
/**
\brief  NewNode - 



\return pNode - 

\param  pPrev - 
\param  pNext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewNode"

DLLNode *DLList :: NewNode (DLLNode *pPrev, DLLNode *pNext )
{
  DLLNode         *pNode;
  if (m_pNodeFree == NULL)
  {
    ListNode* pNewBlock = ListNode::Create(m_pBlocks, m_nBlockSize, sizeof(DLLNode));
    pNode = (DLLNode*) pNewBlock->data();
    pNode += m_nBlockSize - 1;
    for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
    {
      pNode->pNext = m_pNodeFree;
      m_pNodeFree = pNode;
    }
  }

  pNode = m_pNodeFree;
  m_pNodeFree = m_pNodeFree->pNext;
  pNode->pPrev = pPrev;
  pNode->pNext = pNext;
  m_nCount++;

  pNode->data = 0;

  return(pNode);
}

/******************************************************************************/
/**
\brief  RemoveAll - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAll"

void DLList :: RemoveAll ( )
{

  m_nCount = 0;
  m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
  if ( m_pBlocks )
    m_pBlocks->FreeDataChain();
  m_pBlocks = NULL;


}

/******************************************************************************/
/**
\brief  RemoveAt - 




\param  position - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAt"

void DLList :: RemoveAt (POSITION position )
{
  DLLNode* pOldNode = (DLLNode*) position;

  if (pOldNode == m_pNodeHead)
  {
    m_pNodeHead = pOldNode->pNext;
  }
  else
  {
    pOldNode->pPrev->pNext = pOldNode->pNext;
  }
  if (pOldNode == m_pNodeTail)
  {
    m_pNodeTail = pOldNode->pPrev;
  }
  else
  {
    pOldNode->pNext->pPrev = pOldNode->pPrev;
  }
  
  FreeNode(pOldNode);


}

/******************************************************************************/
/**
\brief  RemoveHead - 



\return area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveHead"

void *DLList :: RemoveHead ( )
{
  DLLNode* pOldNode = m_pNodeHead;
  void* returnValue = pOldNode->data;

  m_pNodeHead = pOldNode->pNext;
  if (m_pNodeHead != NULL)
    m_pNodeHead->pPrev = NULL;
  else
    m_pNodeTail = NULL;
  
  FreeNode(pOldNode);

  return returnValue;

}

/******************************************************************************/
/**
\brief  RemoveTail - 



\return area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveTail"

void *DLList :: RemoveTail ( )
{
  DLLNode* pOldNode = m_pNodeTail;
  void* returnValue = pOldNode->data;

  m_pNodeTail = pOldNode->pPrev;
  if (m_pNodeTail != NULL)
    m_pNodeTail->pNext = NULL;
  else
    m_pNodeHead = NULL;
  
  FreeNode(pOldNode);

  return returnValue;

}

/******************************************************************************/
/**
\brief  SetAt - 




\param  position - 
\param  newElement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAt"

void DLList :: SetAt (POSITION position, void *newElement )
{
  DLLNode* pNode = (DLLNode*) position;

  pNode->data = newElement; 


}

/******************************************************************************/
/**
\brief  ~DLList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DLList"

     DLList :: ~DLList ( )
{

  RemoveAll();

}


