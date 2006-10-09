/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassCodeBase

\brief    Base class for all code edit controls


\date     $Date: 2006/06/01 16:42:54,64 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassCodeBase_HPP
#define   cClassCodeBase_HPP

class     cClassCodeBase;

#ifndef   VECTOR_intPair_HPP
#define   VECTOR_intPair_HPP
#include  <sintPair.hpp>
#include  <sVECTOR.h>
#endif
#include  <sRegExp.hpp>
#include  <scNotifyHighContext.hpp>
class  cClassCodeBase :public cNotifyHighContext
{
protected  :         RegExp                                       lines;                                                     // 
protected  :         std::string                                  data;                                                      // 
protected  :         VECTOR(intPair)                              matches;                                                   // 
protected  :         int                                          offset;                                                    // 

public     :
                     RegExp                                      &get_lines() { return(lines); }
                     std::string                                 &get_data() { return(data); }
                     VECTOR(intPair)                             &get_matches() { return(matches); }
                     int                                         &get_offset() { return(offset); }
public     :                                        logical ActivateClassInputHelp ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        logical DeleteLine ( );
public     : virtual                                int8 DoAfterHandleActivated ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical FindBalancedPar ( );
public     :                                        logical GetClassName ( );
public     :                                        logical GetCurrentOffset ( );
public     :                                        logical InsertBlock ( );
public     :                                        logical InsertExpression ( );
public     :                                        logical InsertSwitch ( );
public     :                                        logical ProvideData ( );
public     :                                             cClassCodeBase ( );
public     : virtual                                     ~cClassCodeBase ( );
};

#endif
