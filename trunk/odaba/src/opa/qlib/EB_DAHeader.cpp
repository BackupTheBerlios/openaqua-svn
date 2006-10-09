/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    EB_DAHeader

\brief    


\date     $Date: 2006/04/13 16:42:11,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_DAHeader"

#include  <popa7.h>
#include  <fileacc.h>
#include  <sEBDataArea.hpp>
#include  <sEB_DAHeader.hpp>


/******************************************************************************/
/**
\brief  EB_DAHeader - 



\param  len - 
\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_DAHeader"

                        EB_DAHeader :: EB_DAHeader (uint16 len, logical netopt )
                     : EB_Header(len,netopt),
  temp_file(NULL)
{

  memcpy(eb_ident+2,"DA",2);


}

/******************************************************************************/
/**
\brief  IncreasePosition - 


\return term - Termination code

\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IncreasePosition"

logical EB_DAHeader :: IncreasePosition (int32 length )
{
  logical      term = NO;
BEGINSEQ
  if ( get_da_size() && length+get_next_position() > get_da_size() )   SDBERR(39)
  set_next_position(get_next_position()+length);
  stssmod();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical EB_DAHeader :: Reset ( )
{
  logical                 term = NO;
  EB_Header::Reset();
  set_next_position(get_header_length() + sizeof(EBDataArea));

  return(term);
}

/******************************************************************************/
/**
\brief  SetPosition - 



\param  position64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

void EB_DAHeader :: SetPosition (uint64 position64 )
{

  if ( position64 > get_next_position() )
  {
    set_next_position(position64);
    stssmod();
  }

}

/******************************************************************************/
/**
\brief  SetSize - 



\param  dasize64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void EB_DAHeader :: SetSize (int64 dasize64 )
{

  if ( !dasize64 || dasize64 > get_next_position() )
  {
    set_da_size(dasize64);
    stssmod();
  }

}

/******************************************************************************/
/**
\brief  SetVersion - 


\return term - Termination code

\param  new_version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical EB_DAHeader :: SetVersion (int16 new_version )
{
  logical    term = NO;
BEGINSEQ
  set_version(new_version);
  stssmod();
  if ( Write() )                                        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdatePosition - 


\return term - Termination code

\param  writeopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePosition"

logical EB_DAHeader :: UpdatePosition (logical writeopt )
{
  int64                 fillen = _filelengthi64(file_handle);
  logical               term = NO;
  if ( get_next_position() < fillen && !get_da_size() )
  {
    set_next_position(fillen);
    if ( writeopt )
    {
      stssmod();
      Write();
    }
  }
  return(term);
}


