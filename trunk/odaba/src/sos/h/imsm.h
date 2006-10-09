/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    msm



\date     $Date: 2006/05/01 18:14:31,31 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   msm_H
#define   msm_H
#include "csosdll.h"


#if defined (__cplusplus)
  extern "C" {
#endif

SOSImpExp          int __cdecl msmcl (void **pscbptrp );
SOSImpExp          uint32 __cdecl msmcs (void **areaptr, uint32 lsize );
SOSImpExp          int __cdecl msmfs (void **areaptr );
SOSImpExp          void *__cdecl msmgs (uint32 lsize );
SOSImpExp          void *__cdecl msmop (int16 psize, logical emsopt );
                   uint32 __cdecl msmsize (void *area );

#if defined (__cplusplus)
             }
#endif
#endif
