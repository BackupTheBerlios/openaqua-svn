/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    DActionList

\brief    


\date     $Date: 2006/08/30 17:30:38,40 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DActionList"

#include  <pogui7.h>
#include  <sDActionList.hpp>


/******************************************************************************/
/**
\brief  DActionList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DActionList"

     DActionList :: DActionList ( )
                     : BTI(DAction)(NULL),
  action_tree(sizeof(DAction),0,ID_SIZE,'C',32)
{

  SetTree(&action_tree);

}

/******************************************************************************/
/**
\brief  ~DActionList - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DActionList"

     DActionList :: ~DActionList ( )
{
  DAction           *pDAction;
  while ( pDAction = RemoveTail() )
    delete pDAction;

  SetTree(NULL);

}


