/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cte

\brief    


\date     $Date: 2006/03/12 19:18:32,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cte"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <scte.hpp>


/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void cte :: FromPIF (logical pif )
{

  cteebsn.FromPIF(pif);
  ctelen = PIFToShort(ctelen,pif);
  ctepos = PIFToShort(ctepos,pif);


}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void cte :: ToPIF (logical pif )
{

  cteebsn.ToPIF(pif);
  ctelen = ShortToPIF(ctelen,pif);
  ctepos = ShortToPIF(ctepos,pif);


}


