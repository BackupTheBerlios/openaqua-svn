/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    icbe

\brief    


\date     $Date: 2006/03/12 19:18:53,32 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "icbe"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sicbe.hpp>


/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void icbe :: FromPIF (logical pif )
{

  icbelev = PIFToShort(icbelev,pif);

}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void icbe :: ToPIF (logical pif )
{

  icbelev = ShortToPIF(icbelev,pif);

}

/******************************************************************************/
/**
\brief  icbeini - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "icbeini"

void icbe :: icbeini ( )
{

  *(EB_Number *)this = 0;
  icbelev = 1;


}


