/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    cftd



\date     $Date: 2006/04/28 18:39:16,23 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cftd"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <scftd.hpp>


/******************************************************************************/
/**
\brief  cftd

-------------------------------------------------------------------------------
\brief  i00


\param  fnames
\param  names - Name
\param  flnkptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cftd"

     cftd :: cftd (char *fnames, char *names, flnk flnkptr )
                     : cfte(fnames,flnkptr)
{
  gvtxstb(cftdfnam,names,sizeof(cftdfnam));
}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cftd"

     cftd :: cftd ( )
                     : cfte()
{
  memset(cftdfnam,0,sizeof(cftdfnam));
}


