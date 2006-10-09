/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pc0_SDB_Member



\date     $Date: 2006/05/23 13:05:43,56 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_SDB_Member"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_SDB_Member.hpp>


/******************************************************************************/
/**
\brief  GetMember

\return prophdl - Property handle

\param  propnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMember"

PropertyHandle *pc0_SDB_Member :: GetMember (char *propnames )
{
  PropertyHandle         *sys_ident = GPH("sys_ident");
  PropertyHandle          prop_names(propnames);
  PropertyHandle         *prophdl   = NULL;
  int32                   indx0     = 0;
  while ( Get(indx0++) )
    if ( *sys_ident == prop_names )
    {
      prophdl = this;
      break;
    }

  return(prophdl);
}

/******************************************************************************/
/**
\brief  IsMultipleRef

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsMultipleRef"

logical pc0_SDB_Member :: IsMultipleRef ( )
{
  char           *meta_type = GetCurrentType();
  logical         cond      = YES;;
BEGINSEQ
  if ( strcmp(meta_type,"SDB_Reference")   &&
       strcmp(meta_type,"SDB_Relationship")    )     ERROR
  if ( GPH("ddedim")->GetInt() )                     ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  pc0_SDB_Member


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_SDB_Member"

     pc0_SDB_Member :: pc0_SDB_Member (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{
}


