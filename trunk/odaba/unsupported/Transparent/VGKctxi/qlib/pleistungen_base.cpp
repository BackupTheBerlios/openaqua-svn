/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pleistungen_base

\brief    


\date     $Date: 2006/06/20 20:44:14,12 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pleistungen_base"

#include  <pvgkctxi.h>
#include  <spleistungen_base.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pleistungen_base :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new pleistungen_base();
  return(NO);


}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - Name der Funktion
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical pleistungen_base :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetupCollectionByTyp",ALINK(this,pleistungen_base,SetupCollectionByTyp)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    cfteptr->LINKINST(this);
    term = cfteptr->ActionCall();
  }
  else
    term = CTX_Property::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCollectionByTyp - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCollectionByTyp"

logical pleistungen_base :: SetupCollectionByTyp ( )
{
  PropertyHandle   *ph           = GetPropertyHandle();
  PropertyHandle   *typ          = NULL;
  PropertyHandle   *masseinheit  = NULL;
  PropertyHandle   *parent       = NULL;
  char             *string       = NULL;
  int32             value        = 0;
  int32             indx0        = 0;
  logical           is_action    = UNDEF;
  logical           term         = NO;
BEGINSEQ
  if ( !ph->IsServer() )                            LEAVESEQ
  if ( !(typ = ph->GPH("typ")) )                    LEAVESEQ
  if ( !(parent = ph->GetParentProperty()) )        ERROR
  is_action = parent->IsBasedOn("Action");

  if ( ph->IsBasedOn("Leistung") )
    masseinheit = ph->GPH("masseinheit");

  PropertyHandle   typs(ph->GetDictionary(),typ->GetType(),PI_Read);
                                                    SDBCERR
  while ( typs.Get(indx0++) )
    if ( ( value = typs.GetInt("code") ) &&
         ( value < 100 || (is_action && value < 200) || (!is_action && value >= 200)) )
    {
      ph->Provide(Key((char *)&value));
      if ( masseinheit && *(string = typs.GetString("display_name")) )
      {
        *masseinheit = string;
        ph->Save();
      }
    }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pleistungen_base - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pleistungen_base"

     pleistungen_base :: pleistungen_base ( )
                     : CTX_Property()
{



}

/******************************************************************************/
/**
\brief  ~pleistungen_base - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pleistungen_base"

     pleistungen_base :: ~pleistungen_base ( )
{



}


