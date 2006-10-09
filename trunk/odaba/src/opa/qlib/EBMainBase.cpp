/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBMainBase

\brief    


\date     $Date: 2006/03/12 19:17:26,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EBMainBase"

#include  <popa7.h>
#include  <sEBSubBase.hpp>
#include  <iNetConversion.h>
#include  <sEBMainBase.hpp>


/******************************************************************************/
/**
\brief  EBMainBase - 



\param  filename - File name for DataArea file
\param  server - Name for MainBase server
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EBMainBase"

                        EBMainBase :: EBMainBase (char *filename, char *server )
                     :   EBSubBase(filename), next_mb(0)
{

  if ( server )
    memcpy(server_name,server,16);
  else
    memset(server_name,' ',16);

}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void EBMainBase :: FromPIF (logical pif )
{

  EBSubBase::FromPIF(pif);
  
  next_mb = PIFToBig(next_mb,pif);


}

/******************************************************************************/
/**
\brief  SetNext - 


\return position - Position

\param  nextpos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNext"

int64 EBMainBase :: SetNext (int64 nextpos )
{

  StoreBigInt(&next_mb,nextpos);
  return ( nextpos );

}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void EBMainBase :: ToPIF (logical pif )
{

  EBSubBase::ToPIF(pif);
  
  next_mb = BigToPIF(next_mb,pif);


}

/******************************************************************************/
/**
\brief  get_next_mb - 


\return position - Position

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_next_mb"

int64 EBMainBase :: get_next_mb ( )
{
  uint32                    spos;
  uint64                    position = 0;
  switch ( version_flag )
  {
    case 1  : LoadLong(spos,(int32 *)(((char *)&next_mb)-8));
              position = spos;
              break;
    case 2  : LoadBigInt(position,&next_mb);
              break;
    default : LoadLong(spos,((char *)this)+80);
              position = spos;
  }
  return(position);
}


