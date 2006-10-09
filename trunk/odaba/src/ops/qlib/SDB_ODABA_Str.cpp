/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ODABA_Str

\brief    Persistent ODABA structures
          Persistent  ODABA structures  allow storing  structure instances in an
          ODABA   database.   Persistent   structures   a   specific   structure
          definition,  which extent  the intensional  features of a complex data
          type by extensional features. 
          The  persistent structure definition is the base for storing instances
          in  extents,  which  can  be  defined  as  property  of the persistent
          structure.

\date     $Date: 2006/03/13 21:30:21,04 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_ODABA_Str"

#include  <pops7.h>
#include  <sSDB_Extend.hpp>
#include  <sSDB_NameSpace.hpp>
#include  <sSDB_ODABA_Str.hpp>


/******************************************************************************/
/**
\brief  Initialize - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical SDB_ODABA_Str :: Initialize ( )
{
  logical   term = NO;

BEGINSEQ
  smceindp = YES;

  if ( *smceiksm != ' ' && !smceextd(sys_ident) )
  {
    if ( !smceextd.Add(sys_ident) )                  ERROR
    smceextd.Cancel();
    if ( SDB_Extend::ProvideStrRoot(smceextd.GetDBHandle(),sys_ident) ) 
                                                     ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SDB_ODABA_Str - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_ODABA_Str"

                        SDB_ODABA_Str :: SDB_ODABA_Str ( )
                     : SDB_Structure (),
  clustered(NO),
  smcemod(NO),
  smceindp(NO),
  smcefctd(NO),
  sb_number(UNDEF)
{



}


