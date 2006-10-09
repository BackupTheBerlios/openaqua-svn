/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    CLPosition

\brief    


\date     $Date: 2006/04/21 13:32:29,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CLPosition"

#include  <pogui7.h>
#include  <sCLPosition.hpp>


/******************************************************************************/
/**
\brief  CLPosition

\return 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLPosition"

                        CLPosition :: CLPosition ( )
                     : clnum(),
  clindex(),
  cluster(NULL),
  validread(NO),
  validwrite(NO)
{



}


