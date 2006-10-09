/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OPersistent



\date     $Date: 2006/04/30 14:54:40,26 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPersistent"

#include  <poadi.h>
#include  <sOPersistent.hpp>


/******************************************************************************/
/**
\brief  OPersistent

\return term
/******************************************************************************/
/**
\brief  i01


\param  res_id
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPersistent"

     OPersistent :: OPersistent (int32 res_id )
                     : OBasePersistent(res_id)
{
/*
  "OPersistent("
  + ADK_Persistent::Generate()
  + ")";
*/
}


