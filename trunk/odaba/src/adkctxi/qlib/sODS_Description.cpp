/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    sODS_Description



\date     $Date: 2006/03/12 19:35:56,45 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sODS_Description"

#include  <padkctxi.h>
#include  <ssODS_Description.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc -

\param  strctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sODS_Description :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sODS_Description();
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

logical sODS_Description :: DBCreated ( )
{

  return( SetupResRef() );

}

/******************************************************************************/
/**
\brief  DBRead - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical sODS_Description :: DBRead ( )
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
\brief  DBStore - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStore"

logical sODS_Description :: DBStore ( )
{

  return( SetupResRef() );

}

/******************************************************************************/
/**
\brief  SetupResRef - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupResRef"

logical sODS_Description :: SetupResRef ( )
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
\brief  sODS_Description - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sODS_Description"

                        sODS_Description :: sODS_Description ( )
                     : CTX_Structure ()
{



}

/******************************************************************************/
/**
\brief  ~sODS_Description - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sODS_Description"

                        sODS_Description :: ~sODS_Description ( )
{



}


