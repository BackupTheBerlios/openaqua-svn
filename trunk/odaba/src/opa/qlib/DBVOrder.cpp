/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBVOrder

\brief    Order defintion for a view collection


\date     $Date: 2006/03/12 19:17:14,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBVOrder"

#include  <popa7.h>
#include  <snode.hpp>
#include  <sDBVOrder.hpp>


/******************************************************************************/
/**
\brief  DBVOrder - Konstruktor



\param  property_path -
\param  sort_key_name - Sort key name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBVOrder"

                        DBVOrder :: DBVOrder (char *property_path, char *sort_key_name )
                     : prop_path(property_path ? strdup(property_path) : NULL)
{

  if ( sort_key_name )
    gvtxstb(sort_key,sort_key_name,ID_SIZE);

}

/******************************************************************************/
/**
\brief  SetOrder - Set order for view collection


\return term - Termination code

\param  nodeptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical DBVOrder :: SetOrder (node *nodeptr )
{
  node                  **coll_node;
  char                   *ppath;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(sort_key,ID_SIZE)
  SDBEV2(prop_path,UNDEF)
  SDBEV3(nodeptr->GetCurrentType(),ID_SIZE)
  
// wir nehmen erst einmal nur den letzten Teil vom Path, da die
// eingebetteten und Basisstrukturangaben im Pfad nicht sauber 
// in der View berücksichtigt werden
  coll_node = &nodeptr;
  if ( (ppath = (prop_path && (ppath = STRSearchChar(prop_path,'.',YES))) ? ++ppath : prop_path) && *ppath )
    if ( !(coll_node = nodeptr->GetNodePtr(ppath)) || !*coll_node )
                                                     SDBERR(553)
 
  if ( (*coll_node)->SetOrder(sort_key,UNDEF,NULL) ) SDBERR(553)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~DBVOrder - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBVOrder"

                        DBVOrder :: ~DBVOrder ( )
{

  if ( prop_path )
    free(prop_path);
  prop_path = NULL;



}


