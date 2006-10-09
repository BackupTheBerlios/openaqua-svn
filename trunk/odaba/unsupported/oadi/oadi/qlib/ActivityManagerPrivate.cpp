/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ActivityManagerPrivate

\brief    


\date     $Date: 2006/03/13 21:33:04,00 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ActivityManagerPrivate"

#include  <poadi.h>
#include  <sAH.hpp>
#include  <sActivityManagerPrivate.hpp>


/******************************************************************************/
/**
\brief  compareBefore - 


\return cmpval -

\param  phdl -
\param  pAH -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "compareBefore"

int __cdecl ActivityManagerPrivate :: compareBefore (void *phdl, AH *pAH )
{
  AH            *p= (AH *)phdl;

  return p->beforePos - pAH->beforePos;


}

/******************************************************************************/
/**
\brief  compareDo - 


\return cmpval -

\param  phdl -
\param  pAH -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "compareDo"

int __cdecl ActivityManagerPrivate :: compareDo (void *phdl, AH *pAH )
{
  AH            *p= (AH *)phdl;
  return p->doPos - pAH->doPos;


}


