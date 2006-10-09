/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ListNode

\brief    


\date     $Date: 2006/03/12 19:21:44,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ListNode"

#include  <pdefault.h>
#include  <sListNode.hpp>
#include  <sListNode.hpp>


/******************************************************************************/
/**
\brief  Create

\return lnodeptr

\param  lnode -
\param  nMax -
\param  cbElement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

ListNode *__cdecl ListNode :: Create (ListNode* &lnode, uint32 nMax, uint32 cbElement )
{
  ListNode* p = (ListNode*) new unsigned char[sizeof(ListNode) + nMax * cbElement];

  p->pNext = lnode;
  lnode = p;

  return (p);
}

/******************************************************************************/
/**
\brief  FreeDataChain


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeDataChain"

void ListNode :: FreeDataChain ( )
{
  ListNode* p = this;

  while (p != NULL)
  {
    unsigned char *bytes = (unsigned char *) p;
    ListNode      *pNext = p->pNext;
    delete[] bytes;
    p = pNext;
  }

}

/******************************************************************************/
/**
\brief  data

\return area -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "data"

void *ListNode :: data ( )
{

  return this+1;

}


