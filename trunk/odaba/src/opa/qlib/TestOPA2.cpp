/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    TestOPA2

\brief    


\date     $Date: 2006/03/12 19:18:15,40 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TestOPA2"

#include  <trace.h>
#include  <popa7.h>
#include  <sTestOPA2.hpp>


/******************************************************************************/
/**
\brief  Test0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Test0"

void __cdecl TestOPA2 :: Test0 ( )
{
  char     name[16];
  char    *instptr;
  int32     i = 0;
  Dictionary   dict("l:\\opa2\\tst\\test.dct",PI_Write);  
  PI(mem)  struct_pi(&dict,"SDB_Structure",PI_Write,YES);
  SDB_LIST_ON

BEGINSEQ
  SDBCERR
//  dict.StartTA(YES);
  if ( !struct_pi.GetCount() )
  {
    dict.StartTA(NO,100);
    while ( i++ < 1000 )
    {
      gvtxitp((char *)memset(name,'9',16),i,16);
      if ( !struct_pi.Add(name) )                     ERROR
    }
    dict.StopTA();
  }
  else
    while ( (struct_pi++).Exist() )
    {
      instptr = struct_pi->memo;
      (fld)struct_pi.GetField("smceiksm") = struct_pi.ExtractKey();
      struct_pi.Modify();                             SDBCERR
    }
  
//  dict.StopTA();

RECOVER

ENDSEQ
  SDB_LIST_OFF
}

/******************************************************************************/
/**
\brief  Test1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Test1"

void __cdecl TestOPA2 :: Test1 ( )
{
  char     name[16];
  char    *instptr;
  int32     i = 0;
  pmem    *memb_pi;

BEGINSEQ
  Dictionary   dict("l:\\opa2\\tst\\test.dct",PI_Write);  

  PI(mem)  struct_pi(&dict,"SDB_Structure",PI_Write,YES);
                                                     SDBCERR
  instptr = struct_pi("0000000000000008")->memo;      SDBCERR
  memb_pi = struct_pi.GetPIPointer("smcepdde");

  if ( !memb_pi->GetCount() )
    while ( i++ < 10 )
    {
      memb_pi->Add(i-1);
      gvtxltp((char *)memset(name,'9',16),i,16);
      (fld)memb_pi->GetField("SDB_Property").GetField("SDB_Member").GetField("sys_ident") = name;
      memb_pi->Modify();                               SDBCERR
    }
  else
    while ( ((*memb_pi)++).Exist() )
    {
      instptr = (*memb_pi)->memo;
      (fld)memb_pi->GetField("SDB_Property").GetField("SDB_Member").GetField("ddetype") = memb_pi->ExtractKey();
      memb_pi->Modify();                             SDBCERR
    }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Test2 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Test2"

void __cdecl TestOPA2 :: Test2 ( )
{
  char     string[16];
  int32     count = 0;
  char     name[16];
  PI(mem) *extd_pi;
  char    *instptr;
  int32     i = 0;
  pmem    *extb_pi;

BEGINSEQ
  Dictionary   dict("l:\\opa2\\tst\\test.dct",PI_Write);  

  PI(mem)  ext_pi(&dict,"SDB_Extend",PI_Write,YES);   SDBCERR
  
  instptr = ext_pi["0000000000000012"].memo;          SDBCERR
  extd_pi = ext_pi.GetPIPointer("sexderi");

  if ( !extd_pi->GetCount() )
    while ( i++ < 5 )
    {
      gvtxltp((char *)memset(name,'9',16),i,16);
      extd_pi->Add(name);
    }
  else
    while ( ((*extd_pi)++).Exist() )
    {
      instptr = (*extd_pi)->memo;
      count = extd_pi->GetPIPointer("sexbase")->GetCount();
                                                       SDBCERR
    }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Test3 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Test3"

void __cdecl TestOPA2 :: Test3 ( )
{
  char      *instptr;
BEGINSEQ
  Dictionary   dict("l:\\opa2\\tst\\opa2.tst",PI_Write);  

  PI(mem)  struct_pi(&dict,"SDB_Structure",PI_Write,YES);
                                                      SDBCERR
  while ( (struct_pi++).Exist() )
    instptr = struct_pi->memo;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Test4 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Test4"

void __cdecl TestOPA2 :: Test4 ( )
{
  char       wname[16];
  char      *swninst;
  char      *fxtinst;
  char      *text;
  PI(mem)   *fxt_pi;
  PI(mem)   *txt_pi;
  char       indx0 = 0;
BEGINSEQ
  Dictionary   dict("l:\\opa2\\tst\\opa2.tst",PI_Write,YES);  

  PI(mem)  swn_pi(&dict,"swn",PI_Write);           SDBCERR
  gvtxstb(wname,"ODC_FunctImp",16);
  
  if ( swninst = (char *)swn_pi(wname) )
  {
     fxt_pi = swn_pi.GetPIPointer("swnfxt");
     while ( fxtinst = (char *)(*fxt_pi)(indx0++) )
     {
       txt_pi = fxt_pi->GetPIPointer("fxttext");
       text   = (char *)(*txt_pi)(0L);
     }
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Test5 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Test5"

void __cdecl TestOPA2 :: Test5 ( )
{



}


