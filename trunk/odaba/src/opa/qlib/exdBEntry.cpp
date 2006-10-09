/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    exdBEntry

\brief    


\date     $Date: 2006/03/12 19:18:50,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "exdBEntry"

#include  <popa7.h>
#include  <sCSLHandleList.hpp>
#include  <sacb.hpp>
#include  <sexd.hpp>
#include  <sexdBEntry.hpp>


/******************************************************************************/
/**
\brief  Deinit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinit"

void exdBEntry :: Deinit ( )
{

  delete inst_area;
  inst_area = NULL;

}

/******************************************************************************/
/**
\brief  Init - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

void exdBEntry :: Init ( )
{

  inst_area = NULL;

}


