/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Leistung

\brief    


\date     $Date: 2006/07/03 13:12:37,60 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Leistung"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Leistung.hpp>


/******************************************************************************/
/**
\brief  Import - 


\return term - Abbruchbedingung

\param  typ_string - 
\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Import"

logical pc0_Leistung :: Import (char *typ_string, PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical           term = NO;
BEGINSEQ
  if ( Provide(typ_string,imp_globals) )            ERROR

  *GPH("wert")     = *source_ph;
  *GPH("imported") = YES;
  
  if ( Save(typ_string,imp_globals) )               ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportGliedertaxen - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportGliedertaxen"

logical pc0_Leistung :: ImportGliedertaxen (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
  Import("Fuss"                 ,source_ph->GPH("Gliedertaxe_fuss"),imp_globals);
  Import("GrosseZehe"           ,source_ph->GPH("Gliedertaxe_grosse_zehe"),imp_globals);
  Import("Zehen"                ,source_ph->GPH("Gliedertaxe_zehen"),imp_globals);
  Import("VerlustGehoer_ein_Ohr",source_ph->GPH("Gliedertaxe_verlust_gehoer_ein_ohr"),imp_globals);
  Import("VerlustStimme"        ,source_ph->GPH("Gliedertaxe_verlust_stimme"),imp_globals);
  Import("OberhalbEllenbogen"   ,source_ph->GPH("Gliedertaxe_oberhalb_ellenbogen"),imp_globals);
  Import("UnterhalbEllenbogen"  ,source_ph->GPH("Gliedertaxe_unterhalb_ellenbogen"),imp_globals);
  Import("Hand"                 ,source_ph->GPH("Gliedertaxe_Hand"),imp_globals);
  Import("Daumen"               ,source_ph->GPH("Gliedertaxe_Daumen"),imp_globals);
  Import("Zeigefinger"          ,source_ph->GPH("Gliedertaxe_Zeigefinger"),imp_globals);
  Import("Finger"               ,source_ph->GPH("Gliedertaxe_Finger"),imp_globals);
  Import("BeinOberschenkel"     ,source_ph->GPH("Gliedertaxe_bein_oberschenkel"),imp_globals);
  Import("BeinKnie"             ,source_ph->GPH("Gliedertaxe_bein_knie"),imp_globals);
  Import("BeinUnterschenkel"    ,source_ph->GPH("Gliedertaxe_bein_unterschenkel"),imp_globals);


  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Leistung - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Leistung"

     pc0_Leistung :: pc0_Leistung (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


