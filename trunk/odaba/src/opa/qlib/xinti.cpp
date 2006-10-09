/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    xinti

\brief    


\date     $Date: 2006/03/12 19:19:36,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "xinti"

#include  <popa7.h>
#include  <sDBStructDef.hpp>
#include  <snode.hpp>
#include  <sxinti.hpp>


/******************************************************************************/
/**
\brief  IsPositioned - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical xinti :: IsPositioned ( )
{

  return( inst_index >= 0 ? YES : NO );


}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void xinti :: Reset ( )
{

  inst_index = AUTO;

}

/******************************************************************************/
/**
\brief  xinti - Konstruktor


-------------------------------------------------------------------------------
\brief i0


\param  nodeptr -
\param  mspool -
\param  strdefptr -
\param  instptr -
\param  crt_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xinti"

                        xinti :: xinti (node *nodeptr, void *mspool, DBStructDef *strdefptr, void *instptr, logical crt_opt )
                     : binti (nodeptr,mspool,strdefptr,instptr,crt_opt)
{



}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xinti"

                        xinti :: xinti ( )
                     : binti ()
{



}

/******************************************************************************/
/**
\brief  ~xinti - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~xinti"

                        xinti :: ~xinti ( )
{



}


