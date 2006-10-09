/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DiffListBuffer

\brief    


\date     $Date: 2006/03/12 19:17:22,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DiffListBuffer"

#include  <popa7.h>
#include  <idbd.h>
#include  <sLACObject.hpp>
#include  <sieh.hpp>
#include  <sDiffListBuffer.hpp>


/******************************************************************************/
/**
\brief  DiffListBuffer - 


-------------------------------------------------------------------------------
\brief i0


\param  lobhandle -
\param  wslevel -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiffListBuffer"

                        DiffListBuffer :: DiffListBuffer (LACObject *lobhandle, uint8 wslevel )
                     : exdBuffer (lobhandle,32,UNDEF,0,0,NO,NO),
  ws_level(wslevel),
  temp_entnr(0)
{

  locate_exact = YES;

}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiffListBuffer"

                        DiffListBuffer :: DiffListBuffer ( )
                     : exdBuffer (NULL,UNDEF,UNDEF,0,0,NO,NO),
  ws_level(UNDEF),
  temp_entnr(0)
{

  locate_exact = YES;

}

/******************************************************************************/
/**
\brief  ProvideEXD - 


\return exd_area -

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEXD"

exd *DiffListBuffer :: ProvideEXD (EB_Number entnr )
{
  logical newentry = entnr.IsEmpty(ob_handle->get_pif());
  exd    *exdptr = NULL;
BEGINSEQ
//  Lock();  srt-lock: sowas brauchen wir vielleicht, da sonst die temp_entnr vermurkst werden kann
  
  if ( newentry )
  {
    entnr = --temp_entnr;
    entnr.ToPIF(ob_handle->get_pif());
  }
  if ( !(exdptr = Locate(entnr,0,IDB_MVLF,IEH)) )    ERROR    
  exdptr->LockUntilReserveInstance();

RECOVER
  exdptr = NULL;
ENDSEQ
//  Unlock();
  return(exdptr);
}

/******************************************************************************/
/**
\brief  ~DiffListBuffer - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DiffListBuffer"

                        DiffListBuffer :: ~DiffListBuffer ( )
{



}


