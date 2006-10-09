/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UCA_CActionList

\brief    


\date     $Date: 2006/03/12 19:22:02,81 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UCA_CActionList"

#include  <pdefault.h>
#include  <sUCA_Action.hpp>
#include  <sUCA_CActionList.hpp>


/******************************************************************************/
/**
\brief  Search

\return cactptr

\param  acname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Search"

UCA_CAction *UCA_CActionList :: Search (char *acname )
{
  UCA_CAction   *cactptr = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  GoTop();
  while ( cactptr = GetNext() )
    if ( cactptr->get_action() &&               
         !memcmp(cactptr->get_action()->get_name(),acname,ID_SIZE) )
                                                     LEAVESEQ

RECOVER
  cactptr = NULL;
ENDSEQ
  return(cactptr);
}

/******************************************************************************/
/**
\brief  UCA_CActionList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UCA_CActionList"

                        UCA_CActionList :: UCA_CActionList ( )
                     : DLL(UCA_CAction) ()
{



}

/******************************************************************************/
/**
\brief  ~UCA_CActionList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~UCA_CActionList"

                        UCA_CActionList :: ~UCA_CActionList ( )
{
  UCA_CAction   *cactptr;
  while ( cactptr = RemoveTail() )
    delete cactptr;

}


