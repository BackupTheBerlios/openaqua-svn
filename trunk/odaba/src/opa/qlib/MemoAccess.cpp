/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    MemoAccess



\date     $Date: 2006/05/09 14:01:23,45 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "MemoAccess"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sfmcb.hpp>
#include  <sMemoAccess.hpp>


/******************************************************************************/
/**
\brief  Access

\return instptr - 

\param  lindx0 - 
\param  string - 
\param  maxlen - Size of the output buffer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Access"

char *MemoAccess :: Access (int32 lindx0, char *string, int32 maxlen )
{

  return((char *)void_pi.Get(lindx0).GetData());

}

/******************************************************************************/
/**
\brief  DirToRef

\return term - Termination code

\param  targfmcb - 
\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DirToRef"

logical MemoAccess :: DirToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, logical replace )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  MemoAccess


\param  obhandle - Database Object handle
\param  maxsize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MemoAccess"

     MemoAccess :: MemoAccess (ACObject *obhandle, int16 maxsize )
                     : acc (YES),
  void_pi(),
  max_size(maxsize)
{
  DBObjectHandle  obh(obhandle);

  void_pi.Open(obh,"VOID",PI_Read);
}

/******************************************************************************/
/**
\brief  RefToDir

\return term - Termination code

\param  targfmcb - 
\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefToDir"

logical MemoAccess :: RefToDir (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, logical replace )
{
  int32        indx0;
  logical     term = NO;
BEGINSEQ
  memcpy(&indx0,srcefld,sizeof(int32));
  if ( !srcefld || !targfld || !Access(indx0,NULL,0) )      ERROR
  
  if ( targfld )
    srcefmcb->fmcbsmcb->smcbacc->RefToDir(targfmcb,srcefmcb,(char *)targfld,(char *)&void_pi,replace);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RefToRef

\return term - Termination code

\param  targfmcb - 
\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefToRef"

logical MemoAccess :: RefToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, logical replace )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  ~MemoAccess


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~MemoAccess"

     MemoAccess :: ~MemoAccess ( )
{
}


