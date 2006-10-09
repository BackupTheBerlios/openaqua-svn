/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    StructAccess

\brief    


\date     $Date: 2006/03/12 19:18:12,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "StructAccess"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sACObject.hpp>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sEB_Number.hpp>
#include  <sRefAccess.hpp>
#include  <sexd.hpp>
#include  <sisel.hpp>
#include  <sStructAccess.hpp>


/******************************************************************************/
/**
\brief  CreateInstance - 


\return exdarea -

\param  mbnumber - MainBase number
\param  clnumb -
\param  instlen -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

exd *StructAccess :: CreateInstance (int16 mbnumber, EB_Number clnumb, int32 instlen, uint16 version_nr )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetEXD - 


\return exdptr -
-------------------------------------------------------------------------------
\brief i0


\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEXD"

exd *StructAccess :: GetEXD (exd *exdarea )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief i1


\param  entnr -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEXD"

exd *StructAccess :: GetEXD (EB_Number entnr, uint16 version_nr )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetInstLength - 


\return instlen -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstLength"

int32 StructAccess :: GetInstLength ( )
{


  return(struct_def ? struct_def->GetLength() : 0);
}

/******************************************************************************/
/**
\brief  GetInstance - 


\return exdarea -
-------------------------------------------------------------------------------
\brief i0


\param  ebsnum -
\param  clnumb -
\param  instptr -
\param  exdarea -
\param  instlen -
\param  version -
\param  p_update -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

exd *StructAccess :: GetInstance (EB_Number ebsnum, EB_Number clnumb, void *instptr, exd *exdarea, int32 instlen, uint16 version, logical *p_update )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief i1


\param  instptr -
\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

exd *StructAccess :: GetInstance (void *instptr, exd *exdarea )
{

BEGINSEQ
  if ( !exdarea )                                    ERROR
  
  if ( exdarea->Read() )                             ERROR
  
  struct_def->ExtToInt((char *)instptr,exdarea->GetInstance(),pif);

RECOVER
  exdarea = NULL;
ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  GetRefAccess - 


\return ref_acc

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefAccess"

RefAccess *StructAccess :: GetRefAccess ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  ILock - 


\return term - Termination code

\param  wait -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical StructAccess :: ILock (logical wait )
{

  ref_lock.ILock(wait);

  return(NO);
}

/******************************************************************************/
/**
\brief  IUnlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical StructAccess :: IUnlock ( )
{

  ref_lock.IUnlock();

  return(NO);
}

/******************************************************************************/
/**
\brief  PutInstance - 


\return term - Termination code

\param  instptr -
\param  exdarea -
\param  instlen -
\param  refresh_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PutInstance"

logical StructAccess :: PutInstance (void *instptr, exd *exdarea, int32 instlen, logical refresh_opt )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  SetPIF


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPIF"

void StructAccess :: SetPIF ( )
{

  pif = YES;

}

/******************************************************************************/
/**
\brief  StructAccess - 


-------------------------------------------------------------------------------
\brief i0


\param  strdefptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructAccess"

                        StructAccess :: StructAccess (DBStructDef *strdefptr )
                     :   struct_def(strdefptr),
  instarea(NULL),
  ref_lock(YES),
  pif(NO)
{



}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructAccess"

                        StructAccess :: StructAccess ( )
                     :   struct_def(NULL),
  instarea(NULL),
  ref_lock(YES),
  pif(NO)
{



}

/******************************************************************************/
/**
\brief  ~StructAccess - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~StructAccess"

                        StructAccess :: ~StructAccess ( )
{



}


