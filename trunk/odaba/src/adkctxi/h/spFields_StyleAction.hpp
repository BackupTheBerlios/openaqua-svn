/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pFields_StyleAction



\date     $Date: 2006/03/12 19:35:27,42 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pFields_StyleAction_HPP
#define   pFields_StyleAction_HPP

class     pFields_StyleAction;

class  pFields_StyleAction :public CTX_Property
{

public     :
public     :                                     int32 Create (CTX_Property **propctx_ptrp );
public     : virtual                             logical DBInserted ( );
public     :                                                             pFields_StyleAction ( );
public     :                                                             ~pFields_StyleAction ( );
};

#endif
