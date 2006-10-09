/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    intPair

\brief    


\date     $Date: 2006/03/12 19:20:48,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   intPair_HPP
#define   intPair_HPP

class     intPair;

#ifndef   PAIR_int32_HPP
#define   PAIR_int32_HPP
#include  <sPAIR.h>
#endif
class  intPair :public PAIR(int32)
{

public     :
public     :         SOS7ImpExp                                          intPair (const int32 &int1c, const int32 &int2c );
public     :         SOS7ImpExp                                          intPair ( );
};

#endif
