/********************************* Class Declaration ***************************/
/**
\package  VGKctxi
\class    ss_Gesellschaft



\date     $Date: 2006/05/17 13:06:45,34 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ss_Gesellschaft_HPP
#define   ss_Gesellschaft_HPP

class     ss_Gesellschaft;

#include  <sCTX_Structure.hpp>
class  ss_Gesellschaft :public CTX_Structure
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreated ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical SetupCollectionsByTyp ( );
public     :                                             ss_Gesellschaft ( );
public     : virtual                                     ~ss_Gesellschaft ( );
};

#endif
