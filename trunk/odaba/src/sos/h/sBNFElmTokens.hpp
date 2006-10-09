/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BNFElmTokens

\brief    


\date     $Date: 2006/03/12 19:19:29,54 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFElmTokens_HPP
#define   BNFElmTokens_HPP

class     BNFElmTokens;

class     BNFParser;
#include  <sBNFSymbol.hpp>
class  BNFElmTokens
{
protected  :         BNFSymbol                                    tokens[256];                                               //

public     :
public     :                                                             BNFElmTokens (BNFParser *bparser );
public     :                                     BNFSymbol *Get (uint8 ctoken );
public     :                                     void Optimize ( );
public     :                                                             ~BNFElmTokens ( );
};

#endif
