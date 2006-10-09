/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    sODC_FunctImp



\date     $Date: 2006/04/24 16:05:57,18 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sODC_FunctImp_HPP
#define   sODC_FunctImp_HPP

class     sODC_FunctImp;

#include  <sCTX_Structure.hpp>
class  sODC_FunctImp :public CTX_Structure
{

public     :
public     :                                     int32 Create (CTX_Structure **CTX_Structure_ptrp );
public     : virtual                             logical DBRead ( );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                     logical FillHeadLine ( );
public     :                                     logical FillHeadLineParmCallList ( );
public     :                                     logical GetParmCallList ( );
public     :                                     logical SetupCodeBlockOptions ( );
public     :                                     logical SetupCodeBlocks ( );
public     :                                     logical SetupInitCode ( );
public     :                                                             sODC_FunctImp ( );
public     : virtual                                                     ~sODC_FunctImp ( );
};

#endif
