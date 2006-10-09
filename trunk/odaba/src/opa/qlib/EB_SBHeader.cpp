/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_SBHeader

\brief    


\date     $Date: 2006/03/12 19:17:29,29 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_SBHeader"

#include  <popa7.h>
#include  <sEBSubBase.hpp>
#include  <sEB_SBHeader.hpp>


/******************************************************************************/
/**
\brief  EB_SBHeader - 



\param  len -
\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_SBHeader"

                        EB_SBHeader :: EB_SBHeader (uint16 len, logical netopt )
                     : EB_DAHeader(len,netopt), 
  buffer_size(UNDEF)
{

  memcpy(eb_ident+2,"SB",2);


}

/******************************************************************************/
/**
\brief  NextArea - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextArea"

void EB_SBHeader :: NextArea ( )
{

  if ( !get_act_da() )
    set_da_size(UNDEF);
  set_act_da(get_act_da()+1);
  stssmod();


}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical EB_SBHeader :: Reset ( )
{
  logical                 term = NO;
  EB_DAHeader::Reset();
  set_act_da(UNDEF);
  set_da_count(1);
  set_max_entry_size(UNDEF);

  set_next_position(get_header_length() + sizeof(EBSubBase));

  return(term);
}

/******************************************************************************/
/**
\brief  SetMaxEntry - 



\param  length -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMaxEntry"

void EB_SBHeader :: SetMaxEntry (int32 length )
{

  if ( length > get_max_entry_size() )
  {
    set_max_entry_size(length);
    stssmod();
  }

}


