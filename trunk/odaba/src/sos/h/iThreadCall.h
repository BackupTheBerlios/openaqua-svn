/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ThreadCall

\brief    


\date     $Date: 2006/03/12 19:20:18,78 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ThreadCall_H
#define   ThreadCall_H


#if defined (__cplusplus)
  extern "C" {
#endif

                   thrdfnctype __cdecl ExecuteThread (void *flnkinst );
                   thrdfnctype __cdecl ExecuteThreadS (void *flnkinst );
                   thrdfnctype __cdecl ExecuteThreadT (void *threadlnk_inst );

#if defined (__cplusplus)
             }
#endif
#endif
