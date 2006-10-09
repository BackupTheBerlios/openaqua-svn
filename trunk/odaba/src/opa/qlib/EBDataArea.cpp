/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBDataArea

\brief    


\date     $Date: 2006/03/12 19:17:25,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EBDataArea"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sEBDataArea.hpp>


/******************************************************************************/
/**
\brief  EBDataArea - 



\param  filename - File name for DataArea file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EBDataArea"

                        EBDataArea :: EBDataArea (char *filename )
                     : version_flag(2),
  next_da(0)

{

  memset(file_name,0,sizeof(file_name));

  if ( filename )
    gvtxbts(file_name,filename,sizeof(file_name));


}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void EBDataArea :: FromPIF (logical pif )
{

  next_da      = PIFToBig(next_da,pif);



}

/******************************************************************************/
/**
\brief  SetNext - 


\return position64 -

\param  position64 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNext"

int64 EBDataArea :: SetNext (uint64 position64 )
{
  int32        position = position64;
  StoreBigInt(&next_da,position);
  return ( position64 );

}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void EBDataArea :: ToPIF (logical pif )
{

  next_da      = BigToPIF(next_da,pif);



}

/******************************************************************************/
/**
\brief  get_next_da - 


\return position - Position

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_next_da"

int64 EBDataArea :: get_next_da ( )
{
  uint32                    spos;
  uint64                    position = 0;
  switch ( version_flag )
  {
    case 1  : LoadLong(spos,&next_da);
              position = spos;
              break;
    case 2  : LoadBigInt(position,&next_da);
              break;
    default : LoadLong(spos,((char *)this)+80);
              position = spos;
  }


  return(position);
}


