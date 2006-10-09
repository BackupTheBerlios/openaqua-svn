/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/19|19:04:48,89}|(REF)
\class    sODC_PFunction

\brief    


\date     $Date: 2006/03/21 13:59:52,95 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sODC_PFunction_HPP
#define   sODC_PFunction_HPP

class     sODC_PFunction;

#include  <sCTX_Structure.hpp>
class  sODC_PFunction :public CTX_Structure
{

public     :
public     :                                     int32 Create (CTX_Structure **CTX_Structure_ptrp );
public     : virtual                             logical DBCreate ( );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                     logical SetLineCount ( );
public     :                                                             sODC_PFunction ( );
public     : virtual                                                     ~sODC_PFunction ( );
};

#endif
