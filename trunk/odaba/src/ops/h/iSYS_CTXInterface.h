/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SYS_CTXInterface

\brief    


\date     $Date: 2006/03/13 21:30:14,34 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SYS_CTXInterface_H
#define   SYS_CTXInterface_H

class     CTX_DataBase;
class     CTX_Object;
class     CTX_Property;
class     CTX_Structure;

#if defined (__cplusplus)
  extern "C" {
#endif

OPS7ImpExp         CTX_DataBase *__cdecl SYS_CreateDBCtx (int32 resid );
OPS7ImpExp         CTX_Object *__cdecl SYS_CreateObjCtx (int32 resid );
OPS7ImpExp         CTX_Property *__cdecl SYS_CreatePropCtx (int32 resid );
OPS7ImpExp         CTX_Structure *__cdecl SYS_CreateStrCtx (int32 resid );

#if defined (__cplusplus)
             }
#endif
#endif
