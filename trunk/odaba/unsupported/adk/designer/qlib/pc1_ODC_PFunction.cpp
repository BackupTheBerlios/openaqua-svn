/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_PFunction



\date     $Date: 2006/05/23 13:37:48,95 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc1_ODC_PFunction"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spODE.hpp>
#include  <spc1_ODC_FunctImp.hpp>
#include  <spc1_ODC_PFunction.hpp>


/******************************************************************************/
/**
\brief  GetImplementationType

\return method_type

\param  ctxptr - 
\param  setup_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImplementationType"

MethodTypes pc1_ODC_PFunction :: GetImplementationType (CTX_GUIBase *ctxptr, logical setup_opt )
{
  PropertyHandle   *imp_type    = GPH("imp_type");
  char             *type_string = NULL;
  MethodTypes       imptype     = MT_Undefined;
BEGINSEQ
  if ( !IsPositioned() )                            ERROR

  if ( !imp_type->GetInt() )
  {
    if ( NoWrite() )                                ERROR
    type_string = ODEContext(ctxptr)->GetOption("DefaultMethodType");
    *imp_type = (char*)(*type_string ? type_string : "MT_CPPFunction");
    Save();
  }

  imptype = (MethodTypes)imp_type->GetInt();

RECOVER

ENDSEQ
  return(imptype);
}

/******************************************************************************/
/**
\brief  InitializePFunction

\return cond - 
-------------------------------------------------------------------------------
\brief  i00


\param  impcls_ph
\param  ode_ctx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializePFunction"

logical pc1_ODC_PFunction :: InitializePFunction (PropertyHandle *impcls_ph, pODE *ode_ctx )
{
  PropertyHandle  *base      = NULL;
  char             keyarea[MAX_KEYLEN];
  logical          base_call = impcls_ph ? YES : NO;
  int32            indx0     = 0;
  logical          cond      = YES;
BEGINSEQ
  if ( NoWrite() )                                   ERROR
  
  if ( IsConstructor() )
  {
    cond = !ProvideConstructor();
    LEAVESEQ
  }
    
  if ( ode_ctx )
  {
    if ( !impcls_ph )
      impcls_ph = GetParentProperty();

    TypeKey   class_key(impcls_ph->GetString("sys_ident"),impcls_ph->GetInt("namespace_id"));
    base = impcls_ph->GPH("smcebase");
    
    while ( base->Get(indx0++) )
    {
      TypeKey   bc_key(base->GetString("sys_ident"),base->GetInt("namespace_id"));
      if ( ode_ctx->InitializePFunction(this,bc_key,YES) )
                                                     LEAVESEQ
      impcls_ph->Get(class_key.GetKey());
    }
    
    if ( base_call )                                 ERROR
  }
  if ( pc1_ODC_ImpClass(impcls_ph).InitFunction() )   ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i01


\param  func_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializePFunction"

logical pc1_ODC_PFunction :: InitializePFunction (PropertyHandle *func_ph )
{
  logical         term         = NO;
BEGINSEQ
  if ( NoWrite() || !func_ph->IsPositioned() )         ERROR

  CopyInstance(func_ph->Get());
//  *GPH("__GUID")   = "";
  *GPH("signal")     = NO;
  *GPH("slot")       = NO;
  *GPH("inter_face") = NO;
  *GPH("pure_funct") = NO;
  *GPH("export")     = NO;
  PropertyHandle *phimplementations = GPH("implementations");
  pc1_ODC_FunctImp(phimplementations).
     InitializeImplementations(func_ph->GPH("implementations"));
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsConstructor

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConstructor"

logical pc1_ODC_PFunction :: IsConstructor ( )
{
  PropertyHandle     *class_ph = GetParentProperty();
  logical             cond     = YES;
BEGINSEQ
  if ( !IsPositioned() )                            ERROR
  
  if ( *GPH("sys_ident") != *class_ph->GPH("sys_ident") )
                                                    ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsNewInstance

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewInstance"

logical pc1_ODC_PFunction :: IsNewInstance ( )
{
  PropertyHandle     *impls = GPH("implementations");
  logical             cond  = YES;
BEGINSEQ
  if ( impls->GetCount() )                           ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ProvideConstructor

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideConstructor"

logical pc1_ODC_PFunction :: ProvideConstructor ( )
{
  PropertyHandle *clsnames = GetParentProperty()->GPH("sys_ident");
  logical         term     = NO;
BEGINSEQ
  Provide(*clsnames);                                P_SDBCERR
  
  if ( ProvideImplementation() == YES )
    GPH("implementations")->ExecuteInstanceAction("SetupInitCode","NO");  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideDestructor

\return term - 

\param  virtual_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDestructor"

logical pc1_ODC_PFunction :: ProvideDestructor (logical virtual_opt )
{
  PropertyHandle *clsnames = GetParentProperty()->GPH("sys_ident");
  char            idkey[ID_SIZE];
  logical          term     = NO;
  *idkey = '~';
  gvtxstb(idkey+1,clsnames->GetString(),ID_SIZE-1);
  Provide(Key(idkey));
  *GPH("ddevirt") = virtual_opt;
  
  ProvideImplementation();

  return(term);
}

/******************************************************************************/
/**
\brief  ProvideImplementation

\return created

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideImplementation"

char pc1_ODC_PFunction :: ProvideImplementation ( )
{
  PropertyHandle     *impls   = GPH("implementations");
  logical             created = NO;
BEGINSEQ
  if ( impls->GetCount() )                           LEAVESEQ
  
  if ( NoWrite() )                                   ERROR
  PropertyHandle phi00("i00");
  impls->Add(phi00);                                 SDBCERR

  created = YES;
RECOVER
  created = AUTO;
ENDSEQ
  return(created);
}

/******************************************************************************/
/**
\brief  pc1_ODC_PFunction


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_ODC_PFunction"

     pc1_ODC_PFunction :: pc1_ODC_PFunction (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{
}


