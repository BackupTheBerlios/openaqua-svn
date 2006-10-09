/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    s_err



\date     $Date: 2006/03/12 19:35:38,15 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   s_err_HPP
#define   s_err_HPP

class     s_err;

class  s_err :public CTX_Structure
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical DBCreated ( );
public     : virtual                             logical DBRead ( );
public     : virtual                             logical DBStore ( );
public     :                                     logical SetupResRef ( );
public     :                                                             s_err ( );
public     :                                                             ~s_err ( );
};

#endif
