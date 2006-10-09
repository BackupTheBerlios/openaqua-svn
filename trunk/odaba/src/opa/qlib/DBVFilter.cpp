/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBVFilter

\brief    Filter definition for the view


\date     $Date: 2006/03/12 19:17:14,70 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBVFilter"

#include  <popa7.h>
#include  <snode.hpp>
#include  <sDBVFilter.hpp>


/******************************************************************************/
/**
\brief  DBVFilter - Konstruktor



\param  property_path -
\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBVFilter"

                        DBVFilter :: DBVFilter (char *property_path, char *expression )
                     : prop_path(property_path ? strdup(property_path) : NULL),
expression(expression ? strdup(expression) : NULL)
{

 


}

/******************************************************************************/
/**
\brief  SetFilter - 


\return term - Termination code

\param  nodeptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical DBVFilter :: SetFilter (node *nodeptr )
{
  node                  **coll_node;
  char                   *ppath;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(expression,UNDEF)
  SDBEV2(prop_path,UNDEF)
  SDBEV3(nodeptr->GetCurrentType(),ID_SIZE)
  
// wir nehmen erst einmal nur den letzten Teil vom Path, da die
// eingebetteten und Basisstrukturangaben im Pfad nicht sauber 
// in der View berücksichtigt werden

  coll_node = &nodeptr;
  if ( (ppath = (prop_path && (ppath = STRSearchChar(prop_path,'.',YES))) ? ++ppath : prop_path) && *ppath )
    if ( !(coll_node = nodeptr->GetNodePtr(ppath)) || !*coll_node )
                                                     SDBERR(554)
 
  if ( (*coll_node)->SetExpression(expression) )     SDBERR(554)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~DBVFilter - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBVFilter"

                        DBVFilter :: ~DBVFilter ( )
{

  if ( prop_path )
    free(prop_path);
  prop_path = NULL;

  if ( expression )
    free(expression);
  expression = NULL;

}


