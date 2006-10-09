/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    s_err



\date     $Date: 2006/03/12 19:35:57,04 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "s_err"

#include  <padkctxi.h>
#include  <ss_err.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc -

\param  strctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 s_err :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new s_err();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreated

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical s_err :: DBCreated ( )
{

  return( SetupResRef() );

}

/******************************************************************************/
/**
\brief  DBRead

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical s_err :: DBRead ( )
{
  logical                 term = NO;
// sollte wieder rein, wenn alle Datenbanken aktualisiert wurden, 
// um Autokorrektur zu machen
//  if ( GetPropertyHandle()->IsWrite() )
//    term = SetupResRef();
  return(term);
}

/******************************************************************************/
/**
\brief  DBStore

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStore"

logical s_err :: DBStore ( )
{

  return( SetupResRef() );

}

/******************************************************************************/
/**
\brief  SetupResRef

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupResRef"

logical s_err :: SetupResRef ( )
{
  PropertyHandle         *ph = GPH("resource_ref");
  logical                 term = NO;
BEGINSEQ
  if ( !ph )                                         ERROR

  if ( ph->Get(FIRST_INSTANCE) )                     LEAVESEQ

  ph->Add(0);
  ph->GPH("description")->Provide(0);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  s_err


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "s_err"

                        s_err :: s_err ( )
                     : CTX_Structure ()
{



}

/******************************************************************************/
/**
\brief  ~s_err


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~s_err"

                        s_err :: ~s_err ( )
{



}


