/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    sODS_Description



\date     $Date: 2006/03/12 19:35:37,73 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sODS_Description_HPP
#define   sODS_Description_HPP

class     sODS_Description;

class  sODS_Description :public CTX_Structure
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical DBCreated ( );
public     : virtual                             logical DBRead ( );
public     : virtual                             logical DBStore ( );
public     :                                     logical SetupResRef ( );
public     :                                                             sODS_Description ( );
public     :                                                             ~sODS_Description ( );
};

#endif
