/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DiffListEntry

\brief    


\date     $Date: 2006/03/12 19:17:22,89 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DiffListEntry"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sDiffListEntry.hpp>


/******************************************************************************/
/**
\brief  FromPIF


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void DiffListEntry :: FromPIF ( )
{

  ws_number = PIFToLong(ws_number,YES);

}

/******************************************************************************/
/**
\brief  GetKey - 


\return key -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *DiffListEntry :: GetKey ( )
{

  return(&key);

}

/******************************************************************************/
/**
\brief  IndexDifference - 


\return diff -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IndexDifference"

char DiffListEntry :: IndexDifference ( )
{

  return ( (add_ebi.IsEmpty() ? 0 : 1) - (del_ebi.IsEmpty() ? 0 : 1) );

}

/******************************************************************************/
/**
\brief  IndexDifferencePlus - 


\return diff -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IndexDifferencePlus"

char DiffListEntry :: IndexDifferencePlus ( )
{

  return ( add_ebi.IsEmpty() || del_ebi == add_ebi
           ? 0 
           : 1 );

}

/******************************************************************************/
/**
\brief  Init - 



\param  ws_num -
\param  skey -
\param  klen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

void DiffListEntry :: Init (int32 ws_num, char *skey, int16 klen )
{

  memset(this,0,DIFFLISTENTRY);
  ws_number = ws_num;

  if ( skey )
    memcpy(&key,skey,klen);
  else if ( klen )
    memset(&key,0,klen);


}

/******************************************************************************/
/**
\brief  ToPIF


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void DiffListEntry :: ToPIF ( )
{

  ws_number = LongToPIF(ws_number,YES);

}

/******************************************************************************/
/**
\brief  set_ws_number - 



\param  wsnumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ws_number"

void DiffListEntry :: set_ws_number (int32 wsnumber )
{

  ws_number = wsnumber;

}

/******************************************************************************/
/**
\brief  ~DiffListEntry - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DiffListEntry"

                        DiffListEntry :: ~DiffListEntry ( )
{



}


