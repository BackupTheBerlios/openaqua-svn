/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    acc



\date     $Date: 2006/05/09 13:53:11,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "acc"

#include  <pdefault.h>
#include  <sacc.hpp>
//#include  <sfmcb.hpp>
//#include  <ssmcb.hpp>



/******************************************************************************/
/**
\brief  Access

\return instptr - Structured instance
-------------------------------------------------------------------------------
\brief  ACCACC_I


\param  indx0
\param  string - String value
\param  maxlen
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Access"

char *acc :: Access (int32 indx0, char *string, int32 maxlen )
{
  return(NULL);
}

/******************************************************************************/
/**
\brief  DirToRef

\return term - Success

\param  targfmcb
\param  srcefmcb
\param  targ_fld
\param  srce_fld
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DirToRef"

logical acc :: DirToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targ_fld, void *srce_fld, int16 replace, int16 copy_type )
{
  return(NO);
}

/******************************************************************************/
/**
\brief  GetAccess

\return accptr

\param  atyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccess"

acc *acc :: GetAccess (int16 atyp )
{
  return( !atyp ? this : NULL);
}

/******************************************************************************/
/**
\brief  GetSortKeySMCB

\return smcbptr - Structure definition block

\param  fldnames - Field name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *acc :: GetSortKeySMCB (char *fldnames )
{
  return(NULL);
}

/******************************************************************************/
/**
\brief  RefToDir

\return term - Success

\param  targfmcb
\param  srcefmcb
\param  targ_fld
\param  srce_fld
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefToDir"

logical acc :: RefToDir (fmcb *targfmcb, fmcb *srcefmcb, void *targ_fld, void *srce_fld, int16 replace, int16 copy_type )
{
  return(NO);
}

/******************************************************************************/
/**
\brief  RefToRef

\return term - Success

\param  targfmcb
\param  srcefmcb
\param  targ_fld
\param  srce_fld
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefToRef"

logical acc :: RefToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targ_fld, void *srce_fld, int16 replace, int16 copy_type )
{
  return(NO);
}

/******************************************************************************/
/**
\brief  acc


\param  insind
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "acc"

     acc :: acc (logical insind )
                     : accinst(insind), acccntrd(0), acccntwt(0)

{
  SOSRESET

}

/******************************************************************************/
/**
\brief  acccntg

\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "acccntg"

int16 acc :: acccntg ( )
{
  return(acccntrd+acccntwt);
}

/******************************************************************************/
/**
\brief  accdcr

\return count - 

\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "accdcr"

int16 acc :: accdcr (char accopt )
{
  return( (acccntrd-=(accopt==RD)) + (acccntwt-=(accopt==WT)));
}

/******************************************************************************/
/**
\brief  accinc

\return count - 

\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "accinc"

int16 acc :: accinc (char accopt )
{
  return( (acccntrd+=(accopt==RD)) + (acccntwt+=(accopt==WT)));
}

/******************************************************************************/
/**
\brief  accinstc

\return accinst

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "accinstc"

logical acc :: accinstc ( )
{
  return(accinst);
}

/******************************************************************************/
/**
\brief  accinsts


\param  inststo
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "accinsts"

void acc :: accinsts (logical inststo )
{
  accinst = inststo;
}

/******************************************************************************/
/**
\brief  ~acc


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~acc"

     acc :: ~acc ( )
{

}


