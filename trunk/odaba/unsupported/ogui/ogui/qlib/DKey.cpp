/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DKey

\brief    


\date     $Date: 2006/03/13 21:35:00,79 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DKey"

#include  <pogui7.h>
#include  <sDKey.hpp>


/******************************************************************************/
/**
\brief  DKey - Konstruktor



\param  keycode -
\param  keystate -
\param  keyreleased -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DKey"

                        DKey :: DKey (int keycode, int keystate, logical keyreleased )
                     :   key(keycode),
  state(keystate),
  released(keyreleased)
{



}

/******************************************************************************/
/**
\brief  operator==

\return term -

\param  dkey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical DKey :: operator== (DKey &dkey )
{

  return ( key      == dkey.key   &&
           state    == dkey.state &&
           released == dkey.released );

}

/******************************************************************************/
/**
\brief  ~DKey - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DKey"

                        DKey :: ~DKey ( )
{



}


