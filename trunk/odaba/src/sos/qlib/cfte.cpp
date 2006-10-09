/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    cfte

\brief    


\date     $Date: 2006/03/12 19:22:10,04 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cfte"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <scfte.hpp>


/******************************************************************************/
/**
\brief  cfte

-------------------------------------------------------------------------------
\brief CFTE_


\param  fnames -
\param  flnkptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cfte"

                        cfte :: cfte (char *fnames, flnk flnkptr )
                     : flnk(flnkptr)

{

  gvtxstb(cftefnam,fnames,sizeof(cftefnam));


}

/******************************************************************************/
/**
\brief CFTE_DUM


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cfte"

                        cfte :: cfte ( )
                     : flnk()

{

  memset(cftefnam,0,sizeof(cftefnam));


}


