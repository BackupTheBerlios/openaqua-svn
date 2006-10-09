/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cOCdatasource

\brief    


\date     $Date: 2006/04/24 13:39:26,54 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cOCdatasource_HPP
#define   cOCdatasource_HPP

class     cOCdatasource;

class  cOCdatasource :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterSelect ( );
};

#endif
