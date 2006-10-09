/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    ctr



\date     $Date: 2006/05/31 18:26:37,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ctr"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <scte.hpp>
#include  <ssrt.hpp>
#include  <sctr.hpp>


/******************************************************************************/
/**
\brief  Initialize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ctr :: Initialize ( )
{
  ctrlen  = sizeof(ctr)-1;
  ctrecnt = 0;
}

/******************************************************************************/
/**
\brief  Reorganize

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reorganize"

logical ctr :: Reorganize ( )
{
  char    *newentry = new char[ctrlen];
  srt      table(ctrecnt,sizeof(cte),8,1,'I',newentry+6,NO);
  uint32   pos;
  cte     *cteptr;
  int16    indx = 1;

  memcpy(newentry,this,pos = ctrecnt*sizeof(cte)+6);
  table.srtsor(1,8,'C');

  while ( cteptr = (cte *)table.srtigt(indx++) )
  {
    memcpy(newentry+pos,((char *)this)+cteptr->get_ctepos(),cteptr->get_ctelen());
    cteptr->SetPosition(pos);
    pos += cteptr->get_ctelen();
  }

  memcpy(this,newentry,ctrlen);
  delete newentry;
  return(NO);
}

/******************************************************************************/
/**
\brief  ReorganizeOld

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReorganizeOld"

logical ctr :: ReorganizeOld ( )
{
  char  *oldentry = new char[ctrlen];
  srt    table(ctrecnt,sizeof(cte),8,1,'C',oldentry+6,NO);
  int32   pos;
  cte   *cteptr;
  int16  indx = 1;

  memcpy(oldentry,this,pos = ctrecnt*sizeof(cte)+6);
  table.srtsor(1,8,'I');

  while ( cteptr = (cte *)table.srtigt(indx++) )
  {
    memcpy(oldentry+pos,((char *)this)+cteptr->get_ctepos(),cteptr->get_ctelen());
    cteptr->SetPosition(pos);
    pos += cteptr->get_ctelen();
  }

  memcpy(this,oldentry,ctrlen);
  delete oldentry;
  return(NO);
}

/******************************************************************************/
/**
\brief  ctrget

\return cteptr
-------------------------------------------------------------------------------
\brief  CTRGET


\param  indx0 - Position in collection
\param  pif
\param  cteenty
\param  version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ctrget"

cte *ctr :: ctrget (int32 indx0, logical pif, cte &cteenty, uint16 version )
{
  cte     *cteptr = (cte *)&ctrtable;
  // this implementation is used for upgrate to version 4, only
  cteenty = *cteptr;
  if ( version < 4 )  // old version
  {
    cteptr = (cte *)(&ctrtable + indx0*12 - 4);
    cteenty.SetNumber(PIFToLong(*(((int32 *)cteptr)+1),pif));
    cteenty.SetLength(PIFToLong(cteptr->get_ctelen(),pif));
    cteenty.SetPosition(PIFToLong(cteptr->get_ctepos(),pif));
    cteptr = &cteenty;
  }
  else
  {
    cteptr += indx0;
    cteptr->FromPIF(pif);
  }
  
  return (cteptr);
}

/******************************************************************************/
/**
\brief  i01


\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ctrget"

cte *ctr :: ctrget (int32 indx0 )
{
  return(((cte *)&ctrtable)+indx0);
}


