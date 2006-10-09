/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    Context

\brief    


\date     $Date: 2006/03/13 21:30:06,64 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Context_H
#define   Context_H

class     CTX_Base;

#if defined (__cplusplus)
  extern "C" {
#endif

OPS7ImpExp         CTX_Base *__cdecl SysCreateContext (int32 resid );

#if defined (__cplusplus)
             }
#endif
#endif
