/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cDSCTopicEdit

\brief    


\date     $Date: 2006/04/24 13:34:19,26 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cDSCTopicEdit"

#include  <pdesign.h>
#include  <scDSCTopicEdit.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cDSCTopicEdit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cDSCTopicEdit();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoBeforeFillData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 cDSCTopicEdit :: DoBeforeFillData ( )
{
  PropertyHandle     *prophdl   = GetPropertyHandle();
  logical             term    = NO;
BEGINSEQ
  if ( !prophdl->GetParentProperty()->IsPositioned() )
                                                     ERROR
                                                     
  if ( prophdl->IsTrue() )                           LEAVESEQ
  if ( prophdl->GetDimension() != 1 )                LEAVESEQ

  prophdl->Add(Key::NewAutoident());                 P_SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cDSCTopicEdit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cDSCTopicEdit"

                        cDSCTopicEdit :: cDSCTopicEdit ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cDSCTopicEdit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cDSCTopicEdit"

                        cDSCTopicEdit :: ~cDSCTopicEdit ( )
{



}


