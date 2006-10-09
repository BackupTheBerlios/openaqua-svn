/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_PFunction

\brief    


\date     $Date: 2006/06/03 16:10:45,12 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_PFunction"

#include  <pfmodel.h>
#include  <cMethodTypes.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ODC_FunctImp.hpp>
#include  <spc_ODC_PFunction.hpp>


/******************************************************************************/
/**
\brief  AssociateRetval - 


\return term - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AssociateRetval"

logical pc_ODC_PFunction :: AssociateRetval (char *names )
{
  PropertyHandle  *retval = GPH("retval");
  logical          term   = NO;

BEGINSEQ
  if ( NoWrite() )                                   ERROR
  
  if ( !names )
    names = GPH("retval_name")->GetString();
    
  if ( !*names )                                     ERROR
  
  PropertyHandle   names_ph(names);
  PropertyHandle   variables(GetDBHandle(),"ODC_Variable",PI_Read);
                                                     SDBCERR
  if ( !variables.Get(names_ph) )                    LEAVESEQ
  
  if ( retval->Get(FIRST_INSTANCE) )
    retval->Delete();
  retval->Add(names_ph);                             SDBCERR
  
  Save();                                            SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DataTypeCString - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCString"

char *pc_ODC_PFunction :: DataTypeCString (NString &nstring )
{

  if ( IsConstructor() || IsDestructor() )
    nstring.Append(' ',5);
  else if ( GPH("ddetype")->IsEmpty() )
    nstring.Append("void ");
  else
    pc_SDB_Member::DataTypeCString(nstring,UNDEF);
  return(nstring);
}

/******************************************************************************/
/**
\brief  FunctionTypeCOMString - 


\return string - 

\param  nstring - 
\param  prototyp - 
\param  put_opt - 
\param  get_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FunctionTypeCOMString"

char *pc_ODC_PFunction :: FunctionTypeCOMString (NString &nstring, logical prototyp, logical put_opt, logical get_opt )
{
  PropertyHandle  *class_ph = NULL;
  nstring.Append("STDMETHODIMP ");
  
  if ( prototyp )
    nstring += " (";

  if ( !prototyp && (class_ph = GetImpClass(YES)) )
  {
    nstring += class_ph->GPH("sys_ident")->GetString();
    nstring.Append(" :: ");
  }
  
  if ( put_opt )
    nstring += "put_";
  else if ( get_opt )
    nstring += "get_";
  nstring += GPH("sys_ident")->GetString();
    
  if ( prototyp )
    nstring += " )";

  return(nstring);
}

/******************************************************************************/
/**
\brief  FunctionTypeCPPString - 


\return string - 

\param  nstring - 
\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FunctionTypeCPPString"

char *pc_ODC_PFunction :: FunctionTypeCPPString (NString &nstring, logical prototyp )
{
  PropertyHandle  *class_ph = NULL;
  logical          expr     = NO;
  if ( IsExpression() )
  {
    if ( GPH("ddevirt")->IsTrue() )
      nstring.Append("virtual ");
    if ( GPH("ddestat")->IsTrue() )
      nstring.Append("static ");
    expr = YES;
  }

  DataTypeCString(nstring);

  if ( !expr )
    if ( GPH("ddestat")->IsTrue() )
      nstring.Append("__cdecl ");

  if ( !prototyp && (class_ph = GetImpClass(YES)) )
  {
    nstring += class_ph->GPH("sys_ident")->GetString();
    nstring.Append(" :: ");
  }

  nstring += GPH("sys_ident")->GetString();

  return(nstring);
}

/******************************************************************************/
/**
\brief  FunctionTypeCString - 


\return string - 

\param  nstring - 
\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FunctionTypeCString"

char *pc_ODC_PFunction :: FunctionTypeCString (NString &nstring, logical prototyp )
{
  PropertyHandle  *class_ph = NULL;
  PropertyHandle  *ph = NULL;
  logical          expr     = NO;
  if ( IsExpression() )
  {
    if ( GPH("ddevirt")->IsTrue() )
      nstring.Append("virtual ");
    if ( GPH("ddestat")->IsTrue() )
      nstring.Append("static ");
    expr = YES;
  }

  DataTypeCString(nstring);
  nstring.Append("__cdecl ");
  if ( Inherits("ODC_Executable") )
  {
    ph = GPH("implementations");
    if ( ph->Get(0) )
      nstring += ph->GetString("sys_ident");
  }
  else
    nstring += GPH("sys_ident")->GetString();

  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCIFunctionName - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCIFunctionName"

char *pc_ODC_PFunction :: GetCIFunctionName (NString &nstring )
{

  GetCITypePreafix(nstring); 
  
  if ( IsConstructor() )
    nstring += "Construct";
  else if ( IsDestructor() )
    nstring += "Destruct";
  else 
    nstring += GPH("sys_ident")->GetString();
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCIReturnValue - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCIReturnValue"

char *pc_ODC_PFunction :: GetCIReturnValue (NString &nstring )
{

  if ( IsConstructor() )
    nstring.Append("void *");
  else if ( IsDestructor() )
    nstring.Append("void ");
  else 
  {
    if ( GPH("ddetype")->IsEmpty() )
      nstring.Append("void ");
    else  
    {
      if ( IsCIType() )
        nstring.Append("void *");  // muß nicht immer Pointer sein
      else  
        pc_SDB_Member::DataTypeCString(nstring,UNDEF);
    }
  }
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCITypePreafix - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCITypePreafix"

char *pc_ODC_PFunction :: GetCITypePreafix (NString &nstring )
{
  PropertyHandle   cif_ph("CInterface");
  PropertyHandle  *coll        = NULL;
  PropertyHandle  *class_ph    = NULL;
BEGINSEQ
  if ( !(class_ph = GetImpClass(YES)) )             ERROR

  PropertyHandle    inst_coll(GetDBHandle(),"InstCollection",PI_Read);
  if ( !inst_coll(cif_ph) )                          SDBERR(99)

  if ( (coll = inst_coll.GPH("collection"))->Get(*class_ph->GPH("sys_ident")) )
    nstring += coll->GPH("type")->GetString();
RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetExecutable - 


\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExecutable"

PropertyHandle *pc_ODC_PFunction :: GetExecutable ( )
{

  return ( Inherits("ODC_Executable") ? this : NULL );


}

/******************************************************************************/
/**
\brief  GetImpClass - 


\return prophdl - 

\param  pos_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImpClass"

PropertyHandle *pc_ODC_PFunction :: GetImpClass (logical pos_opt )
{
  PropertyHandle   *class_ph = GetParentProperty();
BEGINSEQ
  if ( class_ph->IsA("ODC_ImpClass") )              LEAVESEQ
  
  class_ph = GPH("classx");
  if ( !pos_opt )                                   LEAVESEQ
  
  if ( !class_ph->Get(FIRST_INSTANCE) )             ERROR
RECOVER
  class_ph = NULL;
ENDSEQ
  return(class_ph);
}

/******************************************************************************/
/**
\brief  HasActions - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasActions"

logical pc_ODC_PFunction :: HasActions ( )
{
  int32     curidx  = GetCurrentIndex();
  int32     indx0   = 0;
  logical   started = StartRTA() ? YES : NO;
  logical   cond    = YES;
BEGINSEQ
  while ( Get(indx0++) )
    if ( IsAction() )                               LEAVESEQ    

  ERROR
RECOVER
  cond = NO;
ENDSEQ
  if ( curidx != AUTO )
    Get(curidx);
  StopRTA(started);
  return(cond);
}

/******************************************************************************/
/**
\brief  HasExpressions - 


\return cond - 

\param  only_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasExpressions"

logical pc_ODC_PFunction :: HasExpressions (logical only_opt )
{
  int32     curidx  = GetCurrentIndex();
  int32     indx0   = 0;
  logical   started = StartRTA() ? YES : NO;
  logical   cond    = NO;
BEGINSEQ
  while ( Get(indx0++) )
    if ( IsExpression() )
    {
      cond = YES;
      if ( !only_opt )                              LEAVESEQ
    }
    else
      if ( only_opt )                               ERROR
    


RECOVER
  cond = NO;
ENDSEQ
  if ( curidx != AUTO )
    Get(curidx);
  StopRTA(started);
  return(cond);
}

/******************************************************************************/
/**
\brief  HasFunction - 


\return cond - 

\param  propnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasFunction"

logical pc_ODC_PFunction :: HasFunction (char *propnames )
{
  int32     curidx  = GetCurrentIndex();
  int32     indx0   = 0;
  logical   started = StartRTA() ? YES : NO;
  logical   cond    = YES;
  cond = LocateKey(StringToKey(propnames),YES) ? NO : YES;


  if ( curidx != AUTO )
    Get(curidx);
  StopRTA(started);
  return(cond);
}

/******************************************************************************/
/**
\brief  HasIFFunctions - 


\return cond - 

\param  if_imp_praefix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasIFFunctions"

logical pc_ODC_PFunction :: HasIFFunctions (char *if_imp_praefix )
{
  int32     curidx  = GetCurrentIndex();
  int32     indx0   = 0;
  logical   started = StartRTA() ? YES : NO;
  logical   cond    = YES;
BEGINSEQ
  while ( Get(indx0++) )
    if ( IsIFFunction(if_imp_praefix) )             LEAVESEQ

  ERROR
RECOVER
  cond = NO;
ENDSEQ
  if ( curidx != AUTO )
    Get(curidx);
  StopRTA(started);
  return(cond);
}

/******************************************************************************/
/**
\brief  InitRetval - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRetval"

logical pc_ODC_PFunction :: InitRetval ( )
{
  PropertyHandle  *retval          = GPH("retval");
  PropertyHandle   empty_string("");
  PropertyHandle   empty_num(0);
  PropertyHandle  *retval_name     = &empty_string;
  PropertyHandle  *ddetype         = &empty_string;
  PropertyHandle  *ddegent         = &empty_string;
  PropertyHandle  *ddeinit         = &empty_string;
  PropertyHandle  *ddesize         = &empty_num;
  PropertyHandle  *ddedim          = &empty_num;
  PropertyHandle  *ddeprec         = &empty_num;
  PropertyHandle  *reference_level = &empty_num;
  PropertyHandle  *const_val       = &empty_num;
  logical          term            = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  if ( retval->Get(FIRST_INSTANCE) )
  {
    retval_name     = retval->GPH("sys_ident");
    ddetype         = retval->GPH("ddetype");
    reference_level = retval->GPH("reference_level");
    ddeinit         = retval->GPH("ddeinit");
    ddegent         = retval->GPH("ddegent");
    ddesize         = retval->GPH("ddesize");
    ddedim          = retval->GPH("ddedim");
    ddeprec         = retval->GPH("ddeprec");
    const_val       = retval->GPH("const_val");
  }

  *GPH("retval_name")     = *retval_name;
  *GPH("ddetype")         = *ddetype;
  *GPH("reference_level") = *reference_level;
  *GPH("ddeinit")         = *ddeinit;
  *GPH("ddegent")         = *ddegent;
  *GPH("ddesize")         = *ddesize;
  *GPH("ddedim")          = *ddedim;
  *GPH("ddeprec")         = *ddeprec;
//  *GPH("const_val")     = *const_val;
    
  *GPH("errorcase") = (char*)(reference_level->GetInt() > 0 ? "NULL"               :
                              *ddetype != "LOGICAL"         ? ddetype->GetString() :
                              *ddeinit == "NO"              ? "YES" : "NO");

  Save();                                           SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsAction - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAction"

logical pc_ODC_PFunction :: IsAction ( )
{

  return ( GPH("action")->GetInt() ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsCIType - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCIType"

logical pc_ODC_PFunction :: IsCIType ( )
{
  PropertyHandle   cif_ph("CInterface");
  PropertyHandle  *coll = NULL;
  logical          cond = YES;
BEGINSEQ
  PropertyHandle    inst_coll(GetDBHandle(),"InstCollection",PI_Read);
  if ( !inst_coll(cif_ph) )                          SDBERR(99)
  
  coll = inst_coll.GPH("collection");
  if ( !coll->Get(*GPH("ddetype")) )                 ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsConst - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConst"

logical pc_ODC_PFunction :: IsConst ( )
{

  return (   IsPositioned() 
           ? GPH("const_val")->IsTrue()
           : NO );

}

/******************************************************************************/
/**
\brief  IsConstructor - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConstructor"

logical pc_ODC_PFunction :: IsConstructor ( )
{
  PropertyHandle   *class_ph = GetParentProperty();
  return (   IsPositioned() &&
             class_ph       &&
             *GPH("sys_ident") == *class_ph->GPH("sys_ident") 
           ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsDestructor - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDestructor"

logical pc_ODC_PFunction :: IsDestructor ( )
{

  return (   IsPositioned() && 
             *GPH("sys_ident")->GetString() == '~' 
           ? YES : NO );


}

/******************************************************************************/
/**
\brief  IsExpression - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExpression"

logical pc_ODC_PFunction :: IsExpression ( )
{

  return ( *GPH("imp_type") == "MT_OQLExpression" ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsIFFunction - 


\return cond - 

\param  if_imp_praefix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFFunction"

logical pc_ODC_PFunction :: IsIFFunction (char *if_imp_praefix )
{

  pc_ODC_FunctImp   impl_pc(GPH("implementations"));
  return(impl_pc.HasIFImplement(if_imp_praefix));


}

/******************************************************************************/
/**
\brief  SetLineCount - 


\return term - 

\param  linecnt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineCount"

logical pc_ODC_PFunction :: SetLineCount (int32 linecnt )
{
  PropertyHandle   *linecount = GPH("linecount");
  logical           term = NO;
BEGINSEQ
  if ( NoWrite() )                                   ERROR
  
  *linecount = linecnt;

  Save();                                            SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ODC_PFunction - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_PFunction"

     pc_ODC_PFunction :: pc_ODC_PFunction (PropertyHandle *prophdl )
                     : pc_SDB_Member (prophdl)
{



}


