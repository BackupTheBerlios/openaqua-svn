/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BNFElmTokens

\brief    


\date     $Date: 2006/03/12 19:21:10,73 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFElmTokens"

#include  <pdefault.h>
#include  <sBNFParser.hpp>
#include  <sBNFSymbol.hpp>
#include  <sBNFElmTokens.hpp>


/******************************************************************************/
/**
\brief  BNFElmTokens - 



\param  bparser -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFElmTokens"

                        BNFElmTokens :: BNFElmTokens (BNFParser *bparser )
                     : tokens()
{
  int           i;
  for ( i=0; i<256; i++ )
    tokens[i].Initialize(bparser,i);


}

/******************************************************************************/
/**
\brief  Get - 


\return bsymbol - BNF Symbol

\param  ctoken - Elementary token
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

BNFSymbol *BNFElmTokens :: Get (uint8 ctoken )
{

  return(&tokens[ctoken]);

}

/******************************************************************************/
/**
\brief  Optimize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Optimize"

void BNFElmTokens :: Optimize ( )
{
  int           i;
  for ( i=0; i<256; i++ )
    tokens[i].Optimize();


}

/******************************************************************************/
/**
\brief  ~BNFElmTokens - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFElmTokens"

                        BNFElmTokens :: ~BNFElmTokens ( )
{



}


