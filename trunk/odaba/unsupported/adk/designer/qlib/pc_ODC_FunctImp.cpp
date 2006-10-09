/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc_ODC_FunctImp

\brief    


\date     $Date: 2006/04/24 15:37:05,69 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_FunctImp"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ODC_PFunction.hpp>
#include  <spc_ODC_FunctImp.hpp>


/******************************************************************************/
/**
\brief  ExistDescription

\return cond - 

\param  names
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistDescription"

logical pc_ODC_FunctImp :: ExistDescription (char *names )
{
  PropertyHandle  *parent  = GetParentProperty();
  logical          cond    = YES;
BEGINSEQ
  if ( !IsPositioned() )                            ERROR
  if ( !parent )                                    ERROR
  if ( !parent->IsA("ODC_PFunction") )              ERROR  

  PropertyHandle   impl_descr_copy(*parent->GPH("implementation_descr"));
  PropertyHandle phnames(names);
  if ( !impl_descr_copy.Get(phnames) )
                                                    ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

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

MethodTypes pc_ODC_FunctImp :: GetImplementationType (CTX_GUIBase *ctxptr, logical setup_opt )
{
  PropertyHandle  *parent  = GetParentProperty();
  MethodTypes      imptype = MT_Undefined;
BEGINSEQ
  if ( !parent )                                    ERROR
  if ( !parent->IsA("ODC_PFunction") )              ERROR  

  pc_ODC_PFunction   pfunct_pc(parent);
  imptype = pfunct_pc.GetImplementationType(ctxptr,setup_opt);



RECOVER

ENDSEQ
  return(imptype);
}

/******************************************************************************/
/**
\brief  InitializeImplementations

\return term - 

\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeImplementations"

logical pc_ODC_FunctImp :: InitializeImplementations (PropertyHandle *source_ph )
{
  PropertyHandle *parms        = GPH("parameters");
  PropertyHandle *source_parms = source_ph->GPH("parameters");
  PropertyHandle *start_code   = GPH("start_code");
  PropertyHandle *error_code   = GPH("error_code");
  PropertyHandle *term_code    = GPH("term_code");
  PropertyHandle *memb_ph      = GetParentProperty()->GPH("SDB_Member");
  PropertyHandle *retval_name  = GetParentProperty()->GPH("retval_name");
  PropertyHandle *ddeinit      = GetParentProperty()->GPH("ddeinit");
  PropertyHandle *errorcase    = GetParentProperty()->GPH("errorcase");
  PropertyHandle  ret_ph;
  int32           indx0        = 0;
  std::string     data("");
  logical         term         = NO;
  while ( source_ph->Get(indx0++) )
  {
    Provide(source_ph->ExtractSortKey());
    parms->CopySet(*source_parms);
    
    if ( *retval_name->GetString() > ' ' )
    {
      data = "  ";
      if ( !memb_ph->ExecuteInstanceAction("DataTypeCString",NULL) )
      {
        data.append(memb_ph->GetActionResult());
        data.append("   ");
      }
      data.append(retval_name->GetString());
      if ( *ddeinit->GetString() > ' ' )
      {
        data.append(" = ");
        data.append(ddeinit->GetString());
      }
      data.append(";");
      *start_code = (char *)data.c_str();
      
      if ( *errorcase->GetString() > ' ' )
      {
        data = "  ";
        data.append(retval_name->GetString());
        data.append(" = ");
        data.append(errorcase->GetString());
        data.append(";");
        *error_code = (char *)data.c_str();
      }

      data = "  ";
      data.append("return(");
      data.append(retval_name->GetString());
      data.append(");");
      *term_code = (char *)data.c_str();
    }    
    
    Save();    
  }

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

logical pc_ODC_FunctImp :: IsConstructor ( )
{

  pc_ODC_PFunction   pfunct_pc(GetParentProperty());
  return ( pfunct_pc.IsConstructor() );

}

/******************************************************************************/
/**
\brief  SetupCodeBlocks

\return term - 

\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCodeBlocks"

logical pc_ODC_FunctImp :: SetupCodeBlocks (CTX_GUIBase *ctxptr )
{
  logical     started = NO;
  logical     term    = NO;
BEGINSEQ
  started = StartRTA() ? YES : NO;
  
  if ( GetImplementationType(ctxptr,YES) != MT_CPPFunction )
                                                    LEAVESEQ
// die action bekommt glob_opt   (YES,NO,AUTO) und
//                    glob_ident (ident des impl-templates)
// koennten hier ueber Dialog abgefragt werden
// ggf. zusaetzlich   replace
//                    replace_parms

  if ( ExecuteInstanceAction("SetupCodeBlocks","AUTO") )
                                                    ERROR
RECOVER
  term = YES;
ENDSEQ
  StopRTA(started);
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ODC_FunctImp - 



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_FunctImp"

                        pc_ODC_FunctImp :: pc_ODC_FunctImp (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}


