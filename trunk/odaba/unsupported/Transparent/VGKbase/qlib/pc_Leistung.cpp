/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_Leistung

\brief    


\date     $Date: 2006/07/21 12:08:24,35 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_Leistung"

#include  <pVGKbase.h>
#include  <spc_Leistung.hpp>


/******************************************************************************/
/**
\brief  GPHWert - 



\return prophdl - 

\param  typ_string - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GPHWert"

PropertyHandle *pc_Leistung :: GPHWert (char *typ_string, logical provide )
{
  PropertyHandle       typ(typ_string);
  PropertyHandle      *wert = GPH("wert");
BEGINSEQ
  if ( !Get(typ) )
  {
    if ( !provide )                                 ERROR
    Provide(typ);                                   SDBCERR
  }

RECOVER
  wert = NULL;
ENDSEQ
  return(wert);
}

/******************************************************************************/
/**
\brief  pc_Leistung - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_Leistung"

     pc_Leistung :: pc_Leistung (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


