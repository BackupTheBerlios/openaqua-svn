/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecExchange

\brief    Data Exchange


\date     $Date: 2006/03/12 19:10:28,64 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExecExchange"

#include  <pdefault.h>
#include  <sUtilityHandle.hpp>
#include  <sExecExchange.hpp>


/******************************************************************************/
/**
\brief  ExecExchange - Constuctor


-------------------------------------------------------------------------------
\brief i0


\param  excnames -
\param  exp_opt -
\param  w_obhandle_c
\param  w_resdb_c
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecExchange"

                        ExecExchange :: ExecExchange (char *excnames, logical exp_opt, const DBObjectHandle &w_obhandle_c, const DatabaseHandle &w_resdb_c )
                     :   res_db(w_resdb_c),
  ob_handle(w_obhandle_c),
  exp_opt(exp_opt),
  owns_object(NO)
{
  int32             indx0 = 0;
  char              name[ID_SIZE];
  PropertyHandle   *extext_pi;
  ExecAlloc        *exec_alloc   = NULL;
  PropertyHandle   *intfield     = NULL;
  PropertyHandle   *extfield     = NULL;
  PropertyHandle   *exc_alloc_pi;
  char              int_name[513];
  char              ext_name[513];
BEGINSEQ
  if ( !ob_handle )
  {
    if ( !sdbuptr->sdbudat->dbhandle )                ERROR
    ob_handle.Open(sdbuptr->sdbudat->dbhandle,PI_Write);
    owns_object = YES; 
  }
  if ( !ob_handle )                                  ERROR
  ext_dbhandle.Open(ob_handle.GetDictionary(),PI_Write);
  
  
  if ( !res_db && !(res_db = sdbuptr->sdbures->dbhandle) )
                                                     SDBERR(99)
  PropertyHandle  exc_pi(res_db,"EXC_Exchange",PI_Read);    SDBCERR
  
  SDBEV1(excnames,ID_SIZE)
  if ( !exc_pi.Get(gvtxstb(name,excnames,ID_SIZE)) )      SDBERR(210)
  
  if ( !(exc_alloc_pi = exc_pi.GetPIPointer("allocations")) )
                                                     SDBERR(99)
  while ( exc_alloc_pi->Get(indx0++) )
    if ( (exp_opt  && exc_alloc_pi->GetPropertyHandle("export")->IsTrue()) ||
         (!exp_opt && exc_alloc_pi->GetPropertyHandle("import")->IsTrue())    )
    {
      extext_pi  =  exc_alloc_pi->GetPropertyHandle("ext_extent");
      if ( !extext_pi->Get(0L) )                     SDBERR(214)
      strcpy(ext_name,extext_pi->GetPropertyHandle("sys_ident")->GetString());
      strcpy(int_name,exc_alloc_pi->GetPropertyHandle("view_path")->GetString());
    
      if ( !ext_name || !int_name )                  SDBERR(99)
      
      SDBEV1(ext_name,ID_SIZE)
      SDBError().DisplayMessage(-210);
      if ( !(extfield = new PropertyHandle(ext_dbhandle,ext_name,exp_opt ? PI_Write : PI_Read)) )
                                                     SDBERR(95)
                                                     SDBCERR
      if ( !(intfield = new PropertyHandle(ob_handle,int_name,exp_opt ? PI_Read : PI_Write)) )
                                                     SDBERR(95)
                                                     SDBCERR
    
      if ( !(exec_alloc = new ExecAlloc(*exc_alloc_pi,intfield,extfield,YES)) )
                                                     SDBERR(95)
                                                     SDBCERR
      allocations.SetAtGrow(indx0-1,exec_alloc);
      exec_alloc = NULL;
      extfield   =  NULL;
      intfield   =  NULL;
    }
  
  SDBRESET
RECOVER
  if ( SDBERROR > 0 )
    SDBError().DisplayMessage();
  if ( !exec_alloc )
  {
    delete extfield;
    delete intfield;
  }
  delete exec_alloc;
  SDBISET(-99)
ENDSEQ

}

/******************************************************************************/
/**
\brief i1


\param  excnames -
\param  exp_opt -
\param  pi_handle -
\param  w_resdb_c
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecExchange"

                        ExecExchange :: ExecExchange (char *excnames, logical exp_opt, PropertyHandle &pi_handle, const DatabaseHandle &w_resdb_c )
                     : res_db(w_resdb_c),
  ob_handle(pi_handle.GetDBHandle(),PI_Write),
  exp_opt(exp_opt),
  owns_object(YES)
{
  int32             indx0 = 0;
  char              name[ID_SIZE];
  PropertyHandle   *extext_pi;
  ExecAlloc        *exec_alloc   = NULL;
  PropertyHandle   *intfield     = NULL;
  PropertyHandle   *extfield     = NULL;
  PropertyHandle   *exc_alloc_pi;
  char              int_name[513];
  char              ext_name[513];
  DBExtend         *ext_def;
BEGINSEQ
  if ( !ob_handle )                                  ERROR
  if ( ob_handle.IsServer() )
     ext_dbhandle = pi_handle.GetDBHandle();
  else  // in diesem Fall koennen wir keine temporaeren Indizees aufbauen
    ext_dbhandle.Open(ob_handle.GetDictionary(),PI_Write);
  
  if ( !res_db && !(res_db = sdbuptr->sdbures->dbhandle) )
                                                     SDBERR(99)
  
  PropertyHandle  exc_pi(res_db,"EXC_Exchange",PI_Read);    SDBCERR
  
  SDBEV1(excnames,ID_SIZE)
  if ( !exc_pi.Get(gvtxstb(name,excnames,ID_SIZE)) )      SDBERR(210)
  
  if ( !(exc_alloc_pi = exc_pi.GetPIPointer("allocations")) )
                                                     SDBERR(99)
  while ( exc_alloc_pi->Get(indx0++) )
    if ( (exp_opt  && exc_alloc_pi->GetPropertyHandle("export")->IsTrue()) ||
         (!exp_opt && exc_alloc_pi->GetPropertyHandle("import")->IsTrue())    )
    {
      extext_pi  =  exc_alloc_pi->GetPropertyHandle("ext_extent");
      if ( !extext_pi->Get(0L) )                     SDBERR(214)
      strcpy(ext_name,extext_pi->GetPropertyHandle("sys_ident")->GetString());
      strcpy(int_name,exc_alloc_pi->GetPropertyHandle("view_path")->GetString());
    
      if ( !ext_name || !int_name )                  SDBERR(99)
      
      SDBEV1(int_name,ID_SIZE)
      if ( !(ext_def = pi_handle.GetDictionary().ProvideExtentDef(int_name)) )
                                                     SDBERR(214)
      if ( memcmp(ext_def->fmcbtype,pi_handle.GetDescription()->fmcbtype,ID_SIZE) )
                                                     SDBERR(214)
      SDBEV1(ext_name,ID_SIZE)
      SDBError().DisplayMessage(-210);
      
      if ( !(intfield = new PropertyHandle(pi_handle)) )    SDBERR(95)
                                                     SDBCERR
  
      if ( !(extfield = new PropertyHandle(ext_dbhandle,ext_name,exp_opt ? PI_Write : PI_Read)) )
                                                     SDBERR(95)
                                                     SDBCERR
      if ( !(exec_alloc = new ExecAlloc(*exc_alloc_pi,intfield,extfield,YES)) )
                                                     SDBERR(95)
                                                     SDBCERR
      allocations.SetAtGrow(indx0-1,exec_alloc);
      exec_alloc = NULL;
      extfield   =  NULL;
      intfield   =  NULL;
    }
  
  SDBRESET
RECOVER
  SDBError().DisplayMessage();
  if ( !exec_alloc )
  {
    delete extfield;
    delete intfield;
  }
  delete exec_alloc;
  SDBISET(-99)
ENDSEQ

}

/******************************************************************************/
/**
\brief  Execute - Execute data exchange


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ExecExchange :: Execute ( )
{
  int32                    indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  SDBError().InsertStatField();
  
  while ( indx0 < allocations.GetSize() )
    if ( allocations[indx0++] )
      if ( allocations[indx0-1]->Execute(exp_opt) )  ERROR

  SDBError().RemoveStatField();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetExtExtentName - 


\return extname - Extent name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtExtentName"

char *ExecExchange :: GetExtExtentName (int32 indx0 )
{
  char                   *extname = NULL;
  if ( allocations.GetSize() > indx0 )
    extname = allocations[indx0]->get_ext_field().get_field()->GetExtentName();
  return(extname);
}

/******************************************************************************/
/**
\brief  GetIntExtentName - 


\return extname - Extent name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIntExtentName"

char *ExecExchange :: GetIntExtentName (int32 indx0 )
{
  char                   *extname = NULL;
  if ( allocations.GetSize() > indx0 )
    extname = allocations[indx0]->get_int_field().get_field()->GetExtentName();

  return(extname);
}

/******************************************************************************/
/**
\brief  ~ExecExchange - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ExecExchange"

                        ExecExchange :: ~ExecExchange ( )
{
  int32                    indx0 = 0;

  while ( indx0 < allocations.GetSize() )
    delete allocations[indx0++];

  if ( owns_object )
    ob_handle.Close();


}


