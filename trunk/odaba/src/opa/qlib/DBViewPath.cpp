/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBViewPath

\brief    


\date     $Date: 2006/08/25 15:14:12,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBViewPath"

#include  <popa7.h>
#include  <sBNFData.hpp>
#include  <sDBStructDef.hpp>
#include  <sODC_ViewPath.hpp>
#include  <sSDB_Structure.hpp>
#include  <sDBViewPath.hpp>


/******************************************************************************/
/**
\brief  DBViewPath - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  strdef - Structure definition
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewPath"

     DBViewPath :: DBViewPath (DBStructDef *strdef, PropertyHandle &ph )
                     : struct_def(strdef),
  path(NULL)
{

  Initialize(ph);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  strdef - Structure definition
\param  bnf_data - 
\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewPath"

     DBViewPath :: DBViewPath (DBStructDef *strdef, BNFData *bnf_data, int32 indx0 )
                     : struct_def(strdef),
  path(NULL)
{

  Initialize(bnf_data,indx0);

}

/******************************************************************************/
/**
\brief  i02 - 


\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewPath"

     DBViewPath :: DBViewPath (DBStructDef *strdef )
                     : struct_def(strdef),
  path(NULL)
{



}

/******************************************************************************/
/**
\brief  Initialize - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DBViewPath :: Initialize (PropertyHandle &ph )
{

  gvtxbts(name,ph.GetArea("sys_ident"),sizeof(name)-1);
  
  memcpy(struct_name,ph.GetArea("structure"),sizeof(struct_name));

  path = strdup(ph.GetString("path"));


}

/******************************************************************************/
/**
\brief  i01 - 


\param  bnf_data - 
\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DBViewPath :: Initialize (BNFData *bnf_data, int32 indx0 )
{
  BNFData             *oper;
  BNFData             *bdata;
BEGINSEQ
// parameter      := parm_spec | operand | *
// parm_spec      := [simple_type_spec] identifier assigned_value
// assigned_value := assign_op operand
// for view type definitions, the operand must be an access path. 
// The first element in the access path refers to the starting structure.
// strname.access_path
  
  SDBEV1(bdata->GetElement(0)->Name(),UNDEF)
  SDBEV1(bdata->GetElement(0)->StringValue(),UNDEF) 
  
  bdata = bnf_data->GetElement(0);
  switch ( bnf_data->GetSymbolCode("parm_spec","operand") )
  {
    case 1 : gvtxstb(name,bdata->GetElement("identifier")->StringValue(),ID_SIZE);
             oper = bdata->GetElement("assigned_value")->GetElement(1);
             break;
    case 2 : if ( bdata->IsSymbol("identifier") )
               gvtxstb(name,bdata->GetElement(0)->StringValue(),ID_SIZE);
             else
             {
               memset(name,' ',ID_SIZE);
               memcpy(name,"__TEMP9999",10);
               gvtxitp(name,indx0,10);       
             }
             oper = bdata;
             break;
    default:                                         SDBERR(444)
  }
  
  if ( oper->IsSymbol("identifier") )
    gvtxstb(struct_name,oper->GetElement(0)->StringValue(),ID_SIZE);
  else if ( oper->IsSymbol("access_path") )
  {
    gvtxstb(struct_name,oper->GetElement("path_element")->GetElement("identifier")->StringValue(),ID_SIZE);
    path = strdup(oper->GetElement("path_extensions")->StringValue()+1);
  }


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~DBViewPath - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBViewPath"

     DBViewPath :: ~DBViewPath ( )
{

  if ( path ) 
    free(path);
  path = NULL;

}


