/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/21|16:26:03,43}|(REF) - Context that communicates with the output area
\class    cColorRole

\brief    


\date     $Date: 2006/04/24 12:55:09,34 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cColorRole_HPP
#define   cColorRole_HPP

class     cColorRole;

class  cColorRole :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterSelect ( );
public     : virtual                             int8 DoBeforeFillData ( );
public     :                                     logical LocateBrush (logical store_opt );
};

#endif
