/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cDelegateEventHandling

\brief    


\date     $Date: 2006/03/12 19:36:22,75 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cDelegateEventHandling_HPP
#define   cDelegateEventHandling_HPP

class     cDelegateEventHandling;

class  cDelegateEventHandling :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                                             cDelegateEventHandling ( );
public     : virtual                                                     ~cDelegateEventHandling ( );
};

#endif
