/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pColumns_StyleAction

\brief    


\date     $Date: 2006/03/12 19:35:27,10 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pColumns_StyleAction_HPP
#define   pColumns_StyleAction_HPP

class     pColumns_StyleAction;

class  pColumns_StyleAction :public CTX_Property
{

public     :
public     :                                     int32 Create (CTX_Property **propctx_ptrp );
public     : virtual                             logical DBInserted ( );
public     :                                                             pColumns_StyleAction ( );
public     :                                                             ~pColumns_StyleAction ( );
};

#endif
