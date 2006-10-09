/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_RBHeader

\brief    


\date     $Date: 2006/03/12 19:17:29,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_RBHeader"

#include  <popa7.h>
#include  <sEBRootBase.hpp>
#include  <sEB_RBHeader.hpp>


/******************************************************************************/
/**
\brief  EB_RBHeader - 



\param  len -
\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_RBHeader"

                        EB_RBHeader :: EB_RBHeader (uint16 len, logical netopt )
                     : EB_MBHeader(len,netopt)

{

  memcpy(eb_ident+2,"RB",2);


}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical EB_RBHeader :: Reset ( )
{
  logical                 term = NO;
  EB_MBHeader::Reset();
  set_mb_count(1);
  get_work_spaces() = 0;

  set_next_position(get_header_length() + sizeof(EBRootBase));

  return(term);
}


