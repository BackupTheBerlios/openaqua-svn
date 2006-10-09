/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_Property



\date     $Date: 2006/05/11 14:27:34,26 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Property"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sPropertyHandle.hpp>
#include  <iopsi.h>
#include  <spc_SDB_Property.hpp>


/******************************************************************************/
/**
\brief  CheckKeyField

\return term

\param  protocol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckKeyField"

logical pc_SDB_Property :: CheckKeyField (ErrorProtocol *protocol )
{
  logical     term = NO;
BEGINSEQ
  if ( GPH("ddestat")->IsTrue() )
  {
    protocol->Write(143,0);
    ERROR
  }
  if ( GPH("ddevirt")->IsTrue() )
  {
    protocol->Write(144,0);
    ERROR
  }
  if ( GPH("ddegent")->IsTrue() )
  {
    protocol->Write(145,0);
    ERROR
  }
  if ( GPH("reference_level")->GetInt() > 0 )
  {
    protocol->Write(146,0);
    ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Store

\return term

\param  dbflddef
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical pc_SDB_Property :: Store (DBFieldDef *dbflddef )
{
  logical   term = NO;
BEGINSEQ
  if ( pc_SDB_Member::Store(dbflddef) )               ERROR

  *GPH("ddetrans") = dbflddef->get_transient();
  *GPH("shared")   = NO;
  *GPH("version")  = UNDEF;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_Property


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Property"

     pc_SDB_Property :: pc_SDB_Property (PropertyHandle *prophdl )
                     : pc_SDB_Member(prophdl)
{
}


