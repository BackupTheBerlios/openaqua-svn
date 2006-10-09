/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ieh

\brief    


\date     $Date: 2006/03/12 19:18:53,45 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ieh"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sieh.hpp>
#include  <sieh.hpp>


/******************************************************************************/
/**
\brief  Copy - 


\return iehptr -

\param  iehptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

ieh *ieh :: Copy (ieh *iehptr )
{

BEGINSEQ
  if ( !iehptr )
    if ( !(iehptr = (ieh *)new char[iehlen+IEH]) )
                                                     SDBERR(95)
  memcpy(iehptr,this,iehlen+IEH);
RECOVER

ENDSEQ
  return(iehptr);
}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void ieh :: FromPIF (logical pif )
{

  iehlen = PIFToLong(iehlen,pif);
  iehsid = PIFToShort(iehsid,pif);

}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void ieh :: ToPIF (logical pif )
{

  iehlen = LongToPIF(iehlen,pif);
  iehsid = ShortToPIF(iehsid,pif);

}

/******************************************************************************/
/**
\brief  ieh - 


-------------------------------------------------------------------------------
\brief IEH_


\param  strid -
\param  orgtyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ieh"

                        ieh :: ieh (int16 strid, int16 orgtyp )
                     : iehlen(UNDEF), iehsid(strid), iehtyp(orgtyp), iehver(UNDEF)
{



}

/******************************************************************************/
/**
\brief IEH_DUM


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ieh"

                        ieh :: ieh ( )
                     : iehlen(UNDEF), iehsid(UNDEF), iehtyp(UNDEF), iehver(UNDEF)

{



}

/******************************************************************************/
/**
\brief i2


\param  iehref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ieh"

                        ieh :: ieh (ieh &iehref )
                     : iehlen(iehref.get_iehlen()),
  iehsid(iehref.get_iehsid()),
  iehtyp(iehref.get_iehtyp()),
  iehver(iehref.get_iehver())
{



}

/******************************************************************************/
/**
\brief  set_iehsid - 



\param  sid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_iehsid"

void ieh :: set_iehsid (int16 sid )
{

  iehsid = sid;

}

/******************************************************************************/
/**
\brief  set_iehver - 



\param  version -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_iehver"

void ieh :: set_iehver (uint16 version )
{

  iehver = (char)version;

}


