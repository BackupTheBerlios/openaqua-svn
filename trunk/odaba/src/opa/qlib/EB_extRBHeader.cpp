/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extRBHeader

\brief    


\date     $Date: 2006/03/12 19:17:30,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_extRBHeader"

#include  <popa7.h>
#include  <cRBHdr.h>
class     RBHdr;
#include  <iNetConversion.h>
#include  <sEB_extRBHeader.hpp>


/******************************************************************************/
/**
\brief  CheckUserID - 


\return term - Termination code

\param  user_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckUserID"

logical EB_extRBHeader :: CheckUserID (char *user_name )
{
  char                    user[sizeof(user_id)];
  logical                 term = NO;
BEGINSEQ
  if ( user_id[0] <= ' ' )                           LEAVESEQ
  if ( !user_name )                                  ERROR
    
  gvtxstb(user,user_name,sizeof(user));
  if ( memcmp(user_id,user,sizeof(user)) )           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ConvertTo3

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertTo3"

logical EB_extRBHeader :: ConvertTo3 ( )
{
  RBHdr                  *old_header;
  logical                 term = NO;
  old_header = (RBHdr *)malloc(sizeof(EB_extRBHeader));
  memcpy(old_header,(EB_extRBHeader *)this,sizeof(EB_extRBHeader));

  EB_extMBHeader::ConvertTo3(old_header);
  
  if ( get_version() < 3 )
  {
    memcpy(user_id,old_header->user_id,sizeof(user_id));
    mb_count = PIFToShort(old_header->mb_count,platform_indep);
    work_spaces = old_header->work_spaces;
  }
  else
    mb_count = PIFToShort(mb_count,platform_indep);

  free(old_header);

  return(term);
}

/******************************************************************************/
/**
\brief  EB_extRBHeader - 



\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_extRBHeader"

                        EB_extRBHeader :: EB_extRBHeader (uint16 len )
                     :   EB_extMBHeader(len),
  mb_count(1),
  work_spaces()
{

  memset(user_id,' ' ,sizeof(user_id));

}

/******************************************************************************/
/**
\brief  FromPIF - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void EB_extRBHeader :: FromPIF ( )
{
  int16         sval;
  EB_extMBHeader::FromPIF();
  
  set_mb_count(PIFToShort(get_mb_count(),platform_indep));


}

/******************************************************************************/
/**
\brief  ToPIF - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void EB_extRBHeader :: ToPIF ( )
{
  int16         sval;
  EB_extMBHeader::ToPIF();
  
  set_mb_count(ShortToPIF(get_mb_count(),platform_indep));
  


}

/******************************************************************************/
/**
\brief  get_mb_count - 


\return mb_count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_mb_count"

int16 EB_extRBHeader :: get_mb_count ( )
{
  int16         sval;
  LoadShort(sval,&mb_count)

  return(sval);
}

/******************************************************************************/
/**
\brief  set_mb_count - 



\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_mb_count"

void EB_extRBHeader :: set_mb_count (int32 count )
{
  int16       sval = MAX(0,count);
  StoreShort(&mb_count,sval)


}

/******************************************************************************/
/**
\brief  set_user_id - 



\param  user_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_user_id"

void EB_extRBHeader :: set_user_id (char *user_name )
{

  gvtxstb(user_id,user_name,sizeof(user_id));

}


