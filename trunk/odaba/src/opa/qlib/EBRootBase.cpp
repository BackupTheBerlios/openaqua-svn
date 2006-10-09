/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBRootBase

\brief    


\date     $Date: 2006/03/12 19:17:26,43 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EBRootBase"

#include  <popa7.h>
#include  <sEBMainBase.hpp>
#include  <sEBRootBase.hpp>


/******************************************************************************/
/**
\brief  EBRootBase - 



\param  filename - File name for DataArea file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EBRootBase"

                        EBRootBase :: EBRootBase (char *filename )
                     :   EBMainBase(filename,NULL)
{



}

/******************************************************************************/
/**
\brief  FromPif - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPif"

void EBRootBase :: FromPif (logical pif )
{

  EBMainBase::FromPIF(pif);


}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void EBRootBase :: ToPIF (logical pif )
{

  EBMainBase::ToPIF(pif);


}


