/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBSubBase

\brief    


\date     $Date: 2006/03/12 19:17:26,75 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EBSubBase"

#include  <popa7.h>
#include  <sEBDataArea.hpp>
#include  <iNetConversion.h>
#include  <sEBSubBase.hpp>


/******************************************************************************/
/**
\brief  EBSubBase - 



\param  filename - File name for DataArea file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EBSubBase"

                        EBSubBase :: EBSubBase (char *filename )
                     :   EBDataArea(filename), next_sb(0)
{



}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void EBSubBase :: FromPIF (logical pif )
{

  EBDataArea::FromPIF(pif);
  
  next_sb = PIFToBig(next_sb,pif);


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

uint64 EBSubBase :: SetNext (int64 nextpos )
{

  StoreBigInt(&next_sb,nextpos);
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

void EBSubBase :: ToPIF (logical pif )
{

  EBDataArea::ToPIF(pif);
  
  next_sb = BigToPIF(next_sb,pif);


}

/******************************************************************************/
/**
\brief  get_next_sb - 


\return position - Position

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_next_sb"

int64 EBSubBase :: get_next_sb ( )
{
  uint32                    spos;
  uint64                    position = 0;
  switch ( version_flag )
  {
    case 1  : LoadLong(spos,(int32 *)(((char *)&next_sb)-4));
              position = spos;
              break;
    case 2  : LoadBigInt(position,&next_sb);
              break;
    default : LoadLong(spos,((char *)this)+80);
              position = spos;
  }
  return(position);
}


