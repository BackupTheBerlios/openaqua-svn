/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    NodeStack

\brief    


\date     $Date: 2006/08/25 13:26:55,40 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "NodeStack"

#include  <popa7.h>
#include  <snode.hpp>
#include  <sNodeStack.hpp>


/******************************************************************************/
/**
\brief  Get - 


\return nodeptr - 

\param  position - Position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

node *NodeStack :: Get (int32 position )
{

  return( GetAt(position == AUTO ? GetSize()-1 : position) );

}

/******************************************************************************/
/**
\brief  NodeStack - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NodeStack"

     NodeStack :: NodeStack ( )
                     : DPA(node) (),
  current_position(0)
{



}

/******************************************************************************/
/**
\brief  Pop - 


\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pop"

node *NodeStack :: Pop (int32 count )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( count <= 0 )                                  LEAVESEQ
    
  while ( count-- )
    nodeptr = Pop();

ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pop"

node *NodeStack :: Pop ( )
{
  int32                   use_count;
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( GetSize() < 1 )                               SDBERR(99)
    
  if ( nodeptr = (node *)GetLast() )
  {
    use_count = nodeptr->get_use_count();
    nodeptr->node::Release(NULL);
    if ( use_count <= 1 )
      nodeptr = NULL;
  }
  RemoveLast(1);

RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Push - 


\return position - Position

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Push"

int32 NodeStack :: Push (node *nodeptr )
{
  int32                   position = 0;
  if ( nodeptr )
    nodeptr->Reserve(NULL);
  
  position = Add(nodeptr);

  return(position);
}

/******************************************************************************/
/**
\brief  Set - 


\return term - Termination code

\param  nodeptr - 
\param  position - Position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Set"

logical NodeStack :: Set (node *nodeptr, int32 position )
{
  node                   *nodptr;
  logical                 term = NO;
BEGINSEQ
  if ( position >= GetSize() )                       ERROR
    
  if ( nodptr = GetAt(position) )
    nodptr->Release(NULL);
  
  if ( nodeptr )
    nodeptr->Reserve(NULL);

  ElementAt(position) = nodeptr;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~NodeStack - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~NodeStack"

     NodeStack :: ~NodeStack ( )
{

  Pop( GetSize() );

}


