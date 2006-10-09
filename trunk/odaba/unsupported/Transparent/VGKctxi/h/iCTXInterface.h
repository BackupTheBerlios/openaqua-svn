/********************************* Class Declaration ***************************/
/**
\package  VGKctxi
\class    CTXInterface



\date     $Date: 2006/05/16 12:06:13,50 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTXInterface_H
#define   CTXInterface_H

class     CTX_Base;

#if defined (__cplusplus)
  extern "C" {
#endif

VGKctxiImpExp      CTX_Base *__cdecl CreateContext (int32 resid );

#if defined (__cplusplus)
             }
#endif
#endif
