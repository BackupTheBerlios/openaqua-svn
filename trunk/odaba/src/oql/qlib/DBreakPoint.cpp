/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    DBreakPoint

\brief    


\date     $Date: 2006/04/13 12:54:55,50 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBreakPoint"

#include  <poql.h>
#include  <sDBreakPoint.hpp>


/******************************************************************************/
/**
\brief  DBreakPoint - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBreakPoint"

                        DBreakPoint :: DBreakPoint ( )
                     : auto_proc(NULL)
{



}

/******************************************************************************/
/**
\brief  SetAutoRun


\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoRun"

void DBreakPoint :: SetAutoRun (char *name )
{

  if ( auto_proc )
    free(auto_proc);
  auto_proc = NULL;

  if ( name && *name )
    auto_proc = strdup(name);

}

/******************************************************************************/
/**
\brief  ~DBreakPoint - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBreakPoint"

                        DBreakPoint :: ~DBreakPoint ( )
{

  SetAutoRun(NULL);

}


