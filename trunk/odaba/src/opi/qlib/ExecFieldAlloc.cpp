/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecFieldAlloc

\brief    


\date     $Date: 2006/03/12 19:10:29,01 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExecFieldAlloc"

#include  <pdefault.h>
#include  <sExecAlloc.hpp>
#include  <sPropertyHandle.hpp>
#include  <sExecFieldAlloc.hpp>


/******************************************************************************/
/**
\brief  CopyCollection - 


\return term - Termination code

\param  targ_inst -
\param  srce_inst -
\param  exp_opt -
\param  new_inst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyCollection"

logical ExecFieldAlloc :: CopyCollection (void *targ_inst, void *srce_inst, logical exp_opt, logical new_inst )
{
  ExecField              *targ_ex  = exp_opt ? &ext_field : &int_field;
  ExecField              *srce_ex  = exp_opt ? &int_field : &ext_field;
  PropertyHandle                *targ_dbf = targ_ex->get_db_field();
  PropertyHandle                *srce_dbf = srce_ex->get_db_field();
  logical                 term     = NO;
BEGINSEQ
//  if ( !new_inst && !targ_dbf->IsCollection() ) wollte Nadja gern behalten
  if ( !targ_dbf->IsCollection() )
  {
    if ( new_inst )                                  LEAVESEQ
    term = CopyDirect(targ_inst,srce_inst,exp_opt);
  }
  else
  {
    if ( srce_ex->LocateInstance(srce_inst) )        LEAVESEQ
    if ( targ_ex->LocateInstance(targ_inst) )        LEAVESEQ
    term = struct_alloc->Execute(exp_opt);
  }
  

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyDirect - 


\return term - Termination code

\param  targ_inst -
\param  srce_inst -
\param  exp_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDirect"

logical ExecFieldAlloc :: CopyDirect (void *targ_inst, void *srce_inst, logical exp_opt )
{
  ExecField              *targ_ex  = exp_opt ? &ext_field : &int_field;
  ExecField              *srce_ex  = exp_opt ? &int_field : &ext_field;
  PropertyHandle                *targ_dbf = targ_ex->get_db_field();
  PropertyHandle                *srce_dbf = srce_ex->get_db_field();
  logical                 term     = NO;
BEGINSEQ
  if ( !targ_dbf->IsCollection() )
  {
    if ( srce_ex->LocateInstance(srce_inst) )        LEAVESEQ
    if ( targ_ex->LocateInstance(targ_inst) )        LEAVESEQ
    if ( !struct_alloc )
      *targ_dbf = *srce_dbf;  
    else
      term = struct_alloc->CopyDirect(&targ_dbf->GetValue(AUTO),&srce_dbf->Get(AUTO),exp_opt);
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecFieldAlloc - 


-------------------------------------------------------------------------------
\brief i0


\param  falloc_pi -
\param  intfield -
\param  extfield -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecFieldAlloc"

                        ExecFieldAlloc :: ExecFieldAlloc (PropertyHandle &falloc_pi, PropertyHandle *intfield, PropertyHandle *extfield )
                     : int_field(intfield,*falloc_pi.GetPropertyHandle("property")),
ext_field(extfield,*falloc_pi.GetPropertyHandle("attribute")),
  struct_alloc(NULL)
{
  fmcb                 *intfmcb;
  PropertyHandle       *alloc_pi;
BEGINSEQ
  if ( !(intfmcb = int_field.get_db_field()->GetDescription()) )
  {
    SDBEV1(intfield->GetDescription()->fmcbtype,ID_SIZE)
    SDBEV2(falloc_pi.GetPropertyHandle("property.name")->GetArea(),UNDEF)
                                                     SDBERR(212)
  }
  if ( !ext_field.get_db_field()->GetDescription() )
  {
    SDBEV1(extfield->GetDescription()->fmcbtype,ID_SIZE)
    SDBEV2(falloc_pi.GetPropertyHandle("attribute.name")->GetArea(),UNDEF)
                                                     SDBERR(212)
  }
  
  alloc_pi = falloc_pi.GetPIPointer("sub_allocation");
  if ( alloc_pi->Get(0L) )
  {
    if ( !(struct_alloc = new ExecAlloc(*alloc_pi,int_field.get_db_field(),
                                        ext_field.get_db_field()) ) )
                                                     SDBERR(95)
                                                     SDBCERR
  }
  else
    if ( intfmcb->fmcbrlev == R_REFR && intfmcb->fmcbityp != T_MEMO && intfmcb->fmcbityp != T_BLOB )
    {
      SDBEV1(intfield->GetDescription()->fmcbtype,ID_SIZE)
      SDBEV2(falloc_pi.GetPropertyHandle("property")->GetArea(),UNDEF)
      SDBERR(213)
    }
  
  SDBRESET

RECOVER
  if ( SDBERROR > 0 )
    SDBError().DisplayMessage();
  SDBISET(-99)
ENDSEQ

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecFieldAlloc"

                        ExecFieldAlloc :: ExecFieldAlloc ( )
                     : int_field(),
  ext_field(),
  struct_alloc(NULL)
{



}

/******************************************************************************/
/**
\brief  ~ExecFieldAlloc - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ExecFieldAlloc"

                        ExecFieldAlloc :: ~ExecFieldAlloc ( )
{

  delete struct_alloc;

}


