/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pRegions_StyleAction

\brief    


\date     $Date: 2006/03/12 19:35:27,75 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pRegions_StyleAction_HPP
#define   pRegions_StyleAction_HPP

class     pRegions_StyleAction;

class  pRegions_StyleAction :public CTX_Property
{

public     :
public     :                                     int32 Create (CTX_Property **propctx_ptrp );
public     : virtual                             logical DBInserted ( );
public     :                                                             pRegions_StyleAction ( );
public     :                                                             ~pRegions_StyleAction ( );
};

#endif
