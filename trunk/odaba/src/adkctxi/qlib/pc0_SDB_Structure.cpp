/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pc0_SDB_Structure



\date     $Date: 2006/05/23 13:07:13,39 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_SDB_Structure"

#include  <padkctxi.h>
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0_SDB_Member.hpp>
#include  <spc0_SDB_Structure.hpp>


/******************************************************************************/
/**
\brief  GetMember

\return prophdl - Property handle

\param  propnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMember"

PropertyHandle *pc0_SDB_Structure :: GetMember (char *propnames )
{
  PropertyHandle         *base_ph = GPH("smcebase");
  PropertyHandle         *prophdl = NULL;
  int32                   indx0   = 0;
  logical                 term    = NO;

BEGINSEQ
{  
  pc0_SDB_Member  mem_col(GPH("smcepdde"));
  if ( prophdl = mem_col.GetMember(propnames) )
  {
    member.CopyHandle(prophdl);                      LEAVESEQ
  }
}
{
  pc0_SDB_Member  mem_col(GPH("smcepref"));
  if ( prophdl = mem_col.GetMember(propnames) )
  {
    member.CopyHandle(prophdl);                      LEAVESEQ
  }
}
{
  pc0_SDB_Member  mem_col(GPH("smcershp"));
  if ( prophdl = mem_col.GetMember(propnames) )
  {
    member.CopyHandle(prophdl);                      LEAVESEQ
  }
}
{
  pc0_SDB_Member  mem_col(GPH("smcebase"));
  if ( prophdl = mem_col.GetMember(propnames) )
  {
    member.CopyHandle(prophdl);                      LEAVESEQ
  }
}
  
  pc0_SDB_Structure    structures(GetObjectHandle(),PI_Read);
  while ( base_ph->Get(indx0++) )
    if ( structures.Get(*base_ph->GPH("ddetype")) )
      if ( prophdl = structures.GetMember(propnames) )
      {
        CopyHandle(&structures); 
        member.CopyHandle(prophdl);                  LEAVESEQ
      }

  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(!term ? &member : NULL);
}

/******************************************************************************/
/**
\brief  pc0_SDB_Structure

-------------------------------------------------------------------------------
\brief  i0


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_SDB_Structure"

     pc0_SDB_Structure :: pc0_SDB_Structure (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl),
  member()
{
}

/******************************************************************************/
/**
\brief  i01


\param  obhandle
\param  accopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_SDB_Structure"

     pc0_SDB_Structure :: pc0_SDB_Structure (DBObjectHandle &obhandle, PIACC accopt )
                     : PropertyHandle (obhandle,"SDB_Structure",accopt),
  member()
{
}

/******************************************************************************/
/**
\brief  i02


\param  prophdl_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_SDB_Structure"

     pc0_SDB_Structure :: pc0_SDB_Structure (PropertyHandle &prophdl_ref )
                     : PropertyHandle (prophdl_ref),
  member()
{
}

/******************************************************************************/
/**
\brief  i03


\param  obhandle
\param  strnames
\param  accopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_SDB_Structure"

     pc0_SDB_Structure :: pc0_SDB_Structure (DBObjectHandle &obhandle, char *strnames, PIACC accopt )
                     : PropertyHandle (obhandle,strnames,accopt),
  member()
{
}


