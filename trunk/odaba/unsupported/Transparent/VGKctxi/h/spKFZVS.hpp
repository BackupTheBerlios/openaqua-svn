/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pKFZVS

\brief    


\date     $Date: 2006/07/06 14:53:11,57 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pKFZVS_HPP
#define   pKFZVS_HPP

class     pKFZVS;

#include  <sCTX_Property.hpp>
#include  <spVS_base.hpp>
class  pKFZVS :public pVS_base
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetSparte ( );
public     :                                             pKFZVS ( );
public     : virtual                                     ~pKFZVS ( );
};

#endif
