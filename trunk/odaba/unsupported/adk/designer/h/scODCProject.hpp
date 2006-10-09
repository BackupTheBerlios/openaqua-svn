/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cODCProject

\brief    


\date     $Date: 2006/04/24 13:41:58,04 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cODCProject_HPP
#define   cODCProject_HPP

class     cODCProject;

class  cODCProject :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterFillData ( );
public     : virtual                             int8 DoAfterHandleOpen ( );
public     : virtual                             int8 DoAfterSelect ( );
public     : virtual                             int8 DoBeforeDataSet ( );
public     :                                                             cODCProject ( );
public     : virtual                                                     ~cODCProject ( );
};

#endif
