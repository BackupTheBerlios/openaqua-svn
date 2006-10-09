/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CTXInterface

\brief    


\date     $Date: 2006/03/12 19:12:40,07 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTXInterface_H
#define   CTXInterface_H

class     CTX_DataBase;
class     CTX_Object;
class     CTX_Property;
class     CTX_Structure;

#if defined (__cplusplus)
  extern "C" {
#endif

                   CTX_DataBase *__cdecl CreateDBCtx (int32 resid );
                   CTX_Object *__cdecl CreateObjCtx ( );
                   CTX_Property *__cdecl CreatePropCtx (int32 resid );
                   CTX_Structure *__cdecl CreateStrCtx (int32 resid );

#if defined (__cplusplus)
             }
#endif
#endif
