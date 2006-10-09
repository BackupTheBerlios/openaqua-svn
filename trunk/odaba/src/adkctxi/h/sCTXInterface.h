/********************************** Class Declaration ***************************/
/**
\package  AdkCtxi - 
\class    CTXInterface

\brief    


\date     $Date: 2006/03/06 12:55:05,92 $
\dbsource adk.dev - ODABA Version 9.0
*/
/*************************************************************************************/
#ifndef   CTXInterface_H
#define   CTXInterface_H


#if defined (__cplusplus)
  extern "C" {
#endif

                   CTX_DataBase *__cdecl CreateDBCtx (int32 resid );
                   CTX_Object *__cdecl CreateObjCtx (int32 resid );
                   CTX_Property *__cdecl CreatePropCtx (int32 resid );
                   CTX_Structure *__cdecl CreateStrCtx (int32 resid );

#if defined (__cplusplus)
             }
#endif
#endif
