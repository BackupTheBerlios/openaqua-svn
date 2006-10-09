/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ADK_FieldControl__

\brief    


\date     $Date: 2006/03/12 19:37:37,31 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_FieldControl__"

#include  <pdesign.h>
#include  <cADK_DataReferenceType.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_FieldControl__.hpp>


/******************************************************************************/
/**
\brief  Check - 


\return term -

\param  start_id -
\param  recursive -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_ADK_FieldControl__ :: Check (int32 start_id, logical recursive )
{
  logical                 term = NO;
BEGINSEQ
  if ( IsInHierarchy(start_id) )                     LEAVESEQ
    
  if ( CheckElements(GPH("fields"),start_id,recursive) )
    term = YES;
  if ( CheckElements(GPH("regions"),start_id,recursive) )
    term = YES;
  if ( CheckElements(GPH("columns"),start_id,recursive) )
    term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckElements - 


\return term -

\param  prophdl - Property handle
\param  start_id -
\param  recursive -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckElements"

logical pc_ADK_FieldControl__ :: CheckElements (PropertyHandle *prophdl, int32 start_id, logical recursive )
{
  PropertyHandle         *fclass = GPH("class");
  PropertyHandle         *fc;
  char                   *data_source;
  int32                   indx0  = 0;
  logical                 err    = NO;
  logical                 term   = NO;
BEGINSEQ
  if ( !fclass->Get(0) )                             P_ERR(99)
  P_SETEV1(fclass->GetString("sys_ident"),UNDEF)
  
    
  while ( prophdl->Get(indx0++) )
  {
    err = NO;
    if ( prophdl->GetInt("auto_open") ) 
    {
      data_source = prophdl->GetString("data_ref.data_reference");
      switch ( prophdl->GetInt("data_ref.reference_type") )
      {
        case DRT_undefined    : if ( !data_source || !*data_source ) 
                                  break;  
        case DRT_PropertyPath : if ( strcmp(data_source,"*") )
                                  if ( err = CheckPropertyPath(data_source) )
                                    term = YES;
                                break;
        case DRT_Extent       : 
        case DRT_Enumeration  : if ( err = CheckExtent(data_source) )
                                  term = YES;
                                break;
        case DRT_View         : // CheckView
                                break;
        default : ;
      }
      if ( err )
      {
        P_SETEV1(fclass->GetString("sys_ident"),UNDEF)
        P_SETEV2(GetString("sys_ident"),UNDEF)
        P_DISPLAY(101);
      }

      if ( recursive && (fc = prophdl->GPH("field_control"))->Get(0) )
      {
        pc_ADK_FieldControl__  pc_fc(fc);
        if ( pc_fc.Check(start_id,recursive) )
          term = YES;
      }
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckExtent - 


\return term -

\param  data_source -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtent"

logical pc_ADK_FieldControl__ :: CheckExtent (char *data_source )
{
  PropertyHandle   *fclass = GPH("class");
  PropertyHandle   *sdb_struct = fclass->GPH("SDB_Structure");
  char             *type_names;
  logical           term = NO;
BEGINSEQ
  if ( !fclass->Get(0) )                             OADIERR(99)

  if ( sdb_struct->ExecuteInstanceAction("CheckExtentPath",data_source) )
                                                     ERROR
  if ( !(type_names = sdb_struct->GetActionResult()) || !*type_names )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckPropertyPath - 


\return term -

\param  data_source -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPropertyPath"

logical pc_ADK_FieldControl__ :: CheckPropertyPath (char *data_source )
{
  PropertyHandle   *fclass = GPH("class");
  PropertyHandle   *sdb_struct = fclass->GPH("SDB_Structure");
  char             *type_names;
  logical           term = NO;
BEGINSEQ
  if ( !fclass->Get(0) )                             OADIERR(99)

  if ( sdb_struct->ExecuteInstanceAction("CheckPropertyPath",data_source) )
                                                     ERROR
  if ( !(type_names = sdb_struct->GetActionResult()) || !*type_names )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitResourceDB - 


\return term -

\param  source_control -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical pc_ADK_FieldControl__ :: InitResourceDB (pc_ADK_FieldControl__ &source_control )
{
  logical                 term = NO;
BEGINSEQ
  if ( !source_control.Exist() )                     ERROR
  
  if ( *source_control.get_sys_ident().GetString() != '_' )
                                                     LEAVESEQ
  if ( Get(source_control.get_sys_ident()) )         LEAVESEQ
    
  Copy(source_control,REPL_none);                    SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsInHierarchy - 


\return cond -

\param  start_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInHierarchy"

logical pc_ADK_FieldControl__ :: IsInHierarchy (int32 start_id )
{
  PropertyHandle    *prophdl  = this;
  int32              my_id    = GetID();
  int32              check_id = my_id;
  logical            cond     = YES;
BEGINSEQ
  while ( prophdl && check_id != start_id )
  {
    prophdl = prophdl->GetParentProperty();
    if ( (check_id = prophdl->GetID()) == my_id )   LEAVESEQ
  }

  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  pc_ADK_FieldControl__ - Konstruktor



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_FieldControl__"

                        pc_ADK_FieldControl__ :: pc_ADK_FieldControl__ (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl),
  sys_ident(GPH("sys_ident"))
{



}


