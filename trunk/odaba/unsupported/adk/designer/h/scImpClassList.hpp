/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cImpClassList

\brief    


\date     $Date: 2006/04/24 13:37:08,32 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cImpClassList_HPP
#define   cImpClassList_HPP

class     cImpClassList;

class  cImpClassList :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterHandleOpen ( );
public     : virtual                             int8 DoBeforeDataSet ( );
public     :                                                             cImpClassList ( );
public     : virtual                                                     ~cImpClassList ( );
};

#endif
