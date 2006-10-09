/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OBasePersistent



\date     $Date: 2006/04/30 14:49:55,18 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OBasePersistent"

#include  <poadi.h>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOBasePersistent.hpp>


/******************************************************************************/
/**
\brief  GetID

\return id

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

int OBasePersistent :: GetID ( )
{

  return(resID);

}

/******************************************************************************/
/**
\brief  GetPersistentDBHandle

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPersistentDBHandle"

DBObjectHandle OBasePersistent :: GetPersistentDBHandle ( )
{

  return (   resDB.IsValid() ? resDB : 
             !resID          ? TProjectManager::TPM->UCB()->sdbures->dbhandle
                             : DBObjectHandle()  );

}

/******************************************************************************/
/**
\brief  OBasePersistent

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBasePersistent"

     OBasePersistent :: OBasePersistent ( )
                     :   resDB(),
  resID(0)
{


}

/******************************************************************************/
/**
\brief  i01


\param  resID
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBasePersistent"

     OBasePersistent :: OBasePersistent (int resID )
                     :   resDB(),
  resID(resID)
{
/* 
  " OBasePersistent( "
  +        TBaseComponent::Generate()
  + ", " + GetID()
  + ")";
*/
}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OBasePersistent :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  resDB = ph->GetObjectHandle();
  resID = ph->GetID();

  return(term);
}

/******************************************************************************/
/**
\brief  SetID


\param  res_id
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetID"

void OBasePersistent :: SetID (int32 res_id )
{

  resID = res_id;

}

/******************************************************************************/
/**
\brief  SetProperties

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProperties"

logical OBasePersistent :: SetProperties ( )
{
  logical                 term = NO;
  resDB = TProjectManager::TPM->UCB()->sdbures->dbhandle;
  return(term);
}

/******************************************************************************/
/**
\brief  Setup

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical OBasePersistent :: Setup ( )
{
  logical                 term = NO;
  // read resDB from whoknowswhere

  return(term);
}

/******************************************************************************/
/**
\brief  ~OBasePersistent


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OBasePersistent"

     OBasePersistent :: ~OBasePersistent ( )
{
}


