/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OStringList

\brief    


\date     $Date: 2006/03/13 21:36:16,87 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OStringList"

#include  <pogui7.h>
#include  <sPropertyHandle.hpp>
#include  <sOStringList.hpp>


/******************************************************************************/
/**
\brief  Fill - 


\return term -

\param  prophdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical OStringList :: Fill (PropertyHandle *prophdl )
{
  smcb                 *keydef;
  char                  keystr[1025];
  Key                   key;
  int32                 indx0 = 0;
  logical               skey = NO;
  logical               term = NO;
BEGINSEQ
  if ( keydef = prophdl->GetSortKeySMCB() )
    skey = YES;
  else
    if ( !(keydef = prophdl->GetKeySMCB()) )              ERROR
  
  while ( prophdl->Get(indx0++) )
  {
    key = skey ? prophdl->ExtractSortKey() : prophdl->ExtractKey();
    prophdl->KeyToString(keystr,key,keydef->smcbname);
    append(SZ2QS(keystr));
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OStringList - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OStringList"

                        OStringList :: OStringList ( )
                     : QStringList ()
{



}

/******************************************************************************/
/**
\brief  ProvideEmptyString - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEmptyString"

void OStringList :: ProvideEmptyString ( )
{

  if ( !contains(SZ2QS(EMPTY_STRING)) )
    append(SZ2QS(EMPTY_STRING));

//  if ( !contains(QString()) )
//    append(QString());


}

/******************************************************************************/
/**
\brief  ~OStringList - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OStringList"

                        OStringList :: ~OStringList ( )
{



}


