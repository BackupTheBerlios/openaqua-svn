/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    pc_ODC_ClassRef

\brief    


\date     $Date: 2006/03/13 21:30:41,85 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_ClassRef"

#include  <pfmodel.h>
#include  <cclrkey.h>
#include  <sODC_ImpClass.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc_ODC_ClassRef.hpp>


/******************************************************************************/
/**
\brief  SetCompRequest - 


\return term

\param  classname -
\param  cmod_level -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCompRequest"

logical pc_ODC_ClassRef :: SetCompRequest (char *classname, ClassModLevel cmod_level )
{
  TypeRefKey              key;
  char                   *keyptr;
  ODC_ClassRef           *class_ref;
  logical                 term = NO;
BEGINSEQ
// muss nach SDB_TypeRef, kann dort recursive arbeiten
/*
  memset(&key,' ',sizeof(key));
  memcpy(key.class_name,classname,ID_SIZE);
  
  if ( !(keyptr = NextKey((char *)&key)) )           ERROR

  PI(ODC_ImpClass) oci_pi(GetDBHandle(),"ODC_ImpClass",PI_Update);
                                                     SDBCERR

  do {
    memcpy(&key,keyptr,sizeof(key));
    if ( oci_pi(key.ref_class) )
    {
      class_ref = (ODC_ClassRef *)Get().GetData();
      if ( class_ref->get_code_level() > IRL_Pointer || class_ref->get_inc_level() > IRL_Pointer )
      {
        if ( cmod_level == CML_Intern && class_ref->get_inc_level() == IRL_SensiRef )
        {
          if ( oci_pi->get_mod_level() < CML_Intern )
          {
            oci_pi->SetModified(CML_Intern,NO);
            oci_pi.Modify();
            oci_pi.Save(YES);
            oci_pi->ResModLevel(GetDBHandle());
          }
          else
            oci_pi->SetCompileState(CPS_requested);
        }
        else
          oci_pi->SetCompileState(CPS_requested);
        oci_pi.Modify();
        oci_pi.Save(YES);
      }
    }
  } while ( (keyptr = NextKey()) && !memcmp(keyptr,classname,ID_SIZE) );
*/
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ODC_ClassRef - 


-------------------------------------------------------------------------------
\brief  i0


\param  dbhandle -
\param  accopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_ClassRef"

                        pc_ODC_ClassRef :: pc_ODC_ClassRef (DatabaseHandle &dbhandle, PIACC accopt )
                     : PropertyHandle (dbhandle,"SDB_TypeRef",accopt)
{



}

/******************************************************************************/
/**
\brief  i01


\param  pmemptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_ClassRef"

                        pc_ODC_ClassRef :: pc_ODC_ClassRef (PI(mem) *pmemptr )
                     : PropertyHandle (pmemptr)
{



}


