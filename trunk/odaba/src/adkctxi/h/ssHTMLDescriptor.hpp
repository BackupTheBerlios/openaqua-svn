/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    sHTMLDescriptor



\date     $Date: 2006/03/12 19:35:36,89 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sHTMLDescriptor_HPP
#define   sHTMLDescriptor_HPP

class     sHTMLDescriptor;

class  sHTMLDescriptor :public CTX_Structure
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical DBRead ( );
public     : virtual                             logical DBStore ( );
public     :                                     logical SetupClass ( );
public     :                                                             sHTMLDescriptor ( );
public     : virtual                                                     ~sHTMLDescriptor ( );
};

#endif
