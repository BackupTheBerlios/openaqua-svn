/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sNotiz

\brief    


\date     $Date: 2006/07/10 13:25:38,26 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sNotiz"

#include  <pvgkctxi.h>
#include  <ssNotiz.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sNotiz :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sNotiz();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBInitialize - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInitialize"

logical sNotiz :: DBInitialize ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  dttm              datetime;
  datetime.SetCurrent();
  ph->GPH("datum")->SetValue(datetime,NO);

  return(NO);
}

/******************************************************************************/
/**
\brief  DBModify - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBModify"

logical sNotiz :: DBModify ( )
{
  PropertyHandle   *ph = GetPropertyHandle();

BEGINSEQ
  if ( UserState2() )                                LEAVESEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !strcmp(ph->GetPropertyPath(),"NotizWiedervorlage") )   
                                                    LEAVESEQ
  PropertyHandle  old_wv(ph->GetStructDef(),"wiedervorlage",GetOldInstance());
  PropertyHandle  old_typ(ph->GetStructDef(),"typ",GetOldInstance());
  PropertyHandle *wiedervorlage = ph->GPH("wiedervorlage");
  PropertyHandle *typ = ph->GPH("typ");
  
  if ( *typ != old_typ )
    InitWV();

  if (  *wiedervorlage != old_wv &&
         (wiedervorlage->IsEmpty() || old_wv.IsEmpty()) ) 
    SetUserState1(YES);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  DBStored - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStored"

logical sNotiz :: DBStored ( )
{
  PropertyHandle   *ph      = GetPropertyHandle();
  logical           del_opt = UNDEF;
BEGINSEQ
  if ( !ph->IsServer() )                            LEAVESEQ
  if ( !UserState1() )                              LEAVESEQ
  SetUserState1(NO);
  
  del_opt = ph->GPH("wiedervorlage")->IsEmpty();
  
  PropertyHandle   notizen_wv(ph->GetDBHandle(),"NotizWiedervorlage",PI_Write);
                                                    SDBCERR
  if ( notizen_wv.Get(ph->ExtractKey()) )
  {
    if ( !del_opt )                                 LEAVESEQ
    notizen_wv.Delete();
  }
  else
  {
    if ( del_opt )                                  LEAVESEQ
    notizen_wv.AddReference(*ph);
  }
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  InitWV - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitWV"

logical sNotiz :: InitWV ( )
{
  PropertyHandle   *ph      = GetPropertyHandle();
  SetUserState2(YES);   // do not react on DBModified event
  PH(ph,typ)
  PH(ph,wiedervorlage)
  
  if ( typ == "Wiedervorlage" && wiedervorlage.IsEmpty() ) // automatismus bleibt fraglich, wenn zuviel. dann raus!
  {
    dbdt     curdate;
    curdate.SetDate();
    curdate += 7;
    wiedervorlage = curdate;
  }
  SetUserState2(NO);

  return(NO);
}

/******************************************************************************/
/**
\brief  sNotiz - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sNotiz"

     sNotiz :: sNotiz ( )
                     : CTX_Structure()
{



}


