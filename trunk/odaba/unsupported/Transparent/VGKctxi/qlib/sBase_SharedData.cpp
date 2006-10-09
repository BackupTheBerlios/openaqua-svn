/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sBase_SharedData

\brief    


\date     $Date: 2006/06/29 20:33:08,26 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sBase_SharedData"

#include  <pvgkctxi.h>
#include  <ivgkbi.h>
#include  <ssBase_SharedData.hpp>


/******************************************************************************/
/**
\brief  InitKey - 


\return term - Abbruchbedingung

\param  prop_path - 
\param  extnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitKey"

logical sBase_SharedData :: InitKey (char *prop_path, char *extnames )
{
  PropertyHandle    *ph        = GetPropertyHandle();
  PropertyHandle    *kennung   = ph->GPH("kennung");
  PropertyHandle    *id        = ph->GPH(prop_path);
  char               idkey[16];
BEGINSEQ
  if ( kennung->IsEmpty() )
    kennung->SetValue(::GetEigentuemerKennung(),NO);
    
  if ( extnames && id->IsEmpty() )
  {
    id->SetValue(1,NO);  

    PropertyHandle    all(ph->GetObjectHandle(),extnames,PI_Read);
                                                    SDBCERR
    all.SetOrder("ik_kennung");
    memset(idkey,0,sizeof(idkey));
    *idkey = *kennung->GetString();
    if ( !all.LocateKey(Key(idkey)) )
      all.Position(-1);
    else
      all.Get(LAST_INSTANCE);
    if ( all.IsPositioned() )
      if ( *all.GPH("kennung") == *kennung )
        id->SetValue(all.GPH(prop_path)->GetInt()+1,NO);  
  }

RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  sBase_SharedData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sBase_SharedData"

     sBase_SharedData :: sBase_SharedData ( )
                     : CTX_Structure()
{



}

/******************************************************************************/
/**
\brief  ~sBase_SharedData - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sBase_SharedData"

     sBase_SharedData :: ~sBase_SharedData ( )
{



}


