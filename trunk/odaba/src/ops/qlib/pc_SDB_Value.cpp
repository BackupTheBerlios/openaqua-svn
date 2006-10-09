/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    pc_SDB_Value

\brief    


\date     $Date: 2006/08/28 20:31:54,31 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Value"

#include  <pops7.h>
#include  <spc_SDB_Value.hpp>


/******************************************************************************/
/**
\brief  ContainsZeroValue - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ContainsZeroValue"

logical pc_SDB_Value :: ContainsZeroValue ( )
{
  PropertyHandle  *code  = NULL;
  int32            indx0 = 0;
  logical          cond  = YES;
BEGINSEQ
  if ( !GetCount() > 0 )                            ERROR
  if ( !(code = GPH("__AUTOIDENT")) )               ERROR
  
  pc_SDB_Value  sub_values(GPH("sub_values"));
  
  while ( Get(indx0++) )
  {
    if ( !code->GetInt() )                          LEAVESEQ
    if ( sub_values.ContainsZeroValue() )           LEAVESEQ
  }
  
  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  SetupCopySet - 


\return term - 

\param  srce_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCopySet"

logical pc_SDB_Value :: SetupCopySet (PropertyHandle *srce_ph )
{
  int32       indx0 = 0;
  logical     term  = NO;
BEGINSEQ
  if ( !pc_SDB_Value(srce_ph).ContainsZeroValue() ) LEAVESEQ
  
  PropertyHandle  *srce_code       = srce_ph->GPH("__AUTOIDENT");
  PropertyHandle  *targ_code       = GPH("__AUTOIDENT");
  PropertyHandle  *srce_sub_values = srce_ph->GPH("sub_values");
  pc_SDB_Value     targ_sub_values(GPH("sub_values"));
  
  DeleteSet();
  while ( srce_ph->Get(indx0++) )
  {
    if ( !Copy(*srce_ph,REPL_local,REPL_all) )      ERROR
    *targ_code = *srce_code;
    if ( targ_sub_values.SetupCopySet(srce_sub_values) )
      term = YES;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_Value - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Value"

     pc_SDB_Value :: pc_SDB_Value (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


