/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    kfc

\brief    


\date     $Date: 2006/03/12 19:22:39,70 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "kfc"

#include  <pdefault.h>
#include  <sfmcb.hpp>
#include  <skfc.hpp>


/******************************************************************************/
/**
\brief  Deinitialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

void kfc :: Deinitialize ( )
{

  if ( key_name )
    free(key_name);
  key_name = NULL;

}

/******************************************************************************/
/**
\brief  get_kc_name - 


\return keynames -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_kc_name"

char *kfc :: get_kc_name ( )
{

  return(key_name);

}

/******************************************************************************/
/**
\brief  kfc - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfc"

                        kfc :: kfc ( )
                     : fcb(),
 kfcfmcb(NULL),
 key_name(NULL)

{



}

/******************************************************************************/
/**
\brief  kfcesu - 


-------------------------------------------------------------------------------
\brief KFCESU


\param  fmcbptr - Field definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfcesu"

void kfc :: kfcesu (fmcb *fmcbptr )
{

  kfcfmcb = fmcbptr;
  fmcbptr->fmcbsensi = YES;


}

/******************************************************************************/
/**
\brief KFCESU_I


\param  fmcbptr - Field definition block
\param  struct_offset -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfcesu"

void kfc :: kfcesu (fmcb *fmcbptr, int32 struct_offset )
{

  kfcfmcb = fmcbptr;
  fmcbptr->fmcbsensi = YES;
  kfcpos  = struct_offset;


}

/******************************************************************************/
/**
\brief  kfckgt - 


\return term - Success

\param  instptr - Structured instance
\param  keyptr -
\param  w_indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfckgt"

logical kfc :: kfckgt (char *instptr, char *keyptr, int16 w_indx )
{
  fmcb     *targfmcb = fcbfmcb;
  fmcb     *srcefmcb = kfcfmcbg();
  int32     size     = srcefmcb->fmcbdim ? srcefmcb->fmcbbyte/srcefmcb->fmcbdim :
                                           srcefmcb->fmcbbyte;
  logical   term = NO;

BEGINSEQ
  if ( !instptr )                                    ERROR
    
  if ( targfmcb->fmcbvirt || !srcefmcb )             LEAVESEQ  // key nicht in Instanz
  
  if ( w_indx > (short int)srcefmcb->fmcbdim )       ERROR

  if ( srcefmcb->fmcbkgt(instptr+kfcpos+srcefmcb->fmcbposn+size*(w_indx-1),
                         keyptr +targfmcb->fmcbposn) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  kfckpt - 


\return term - Success

\param  instptr - Structured instance
\param  keyptr -
\param  w_indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfckpt"

logical kfc :: kfckpt (char *instptr, char *keyptr, int16 w_indx )
{
  fmcb     *targfmcb = fcbfmcb;
  fmcb     *srcefmcb = kfcfmcbg();
  logical   term = NO;

BEGINSEQ
  if ( targfmcb->fmcbvirt || !srcefmcb )             LEAVESEQ  // key nicht in Instanz
    
  if ( w_indx > (short int)srcefmcb->fmcbdim )       ERROR

  if ( srcefmcb->fmcbkpt(instptr+kfcpos+srcefmcb->fmcbposn+srcefmcb->fmcbbyte*(w_indx-1),
                         keyptr +targfmcb->fmcbposn) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  set_kc_name - 



\param  keynames -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_kc_name"

void kfc :: set_kc_name (char *keynames )
{

  if ( key_name )
  {
    free(key_name);
    key_name = NULL;
  }
  if ( keynames )
    key_name = strdup(keynames);

}

/******************************************************************************/
/**
\brief  ~kfc - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~kfc"

                        kfc :: ~kfc ( )
{

  Deinitialize();

}


