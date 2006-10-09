/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    PropAllocation

\brief    Property allocation vor view


\date     $Date: 2006/03/12 19:18:03,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "PropAllocation"

#include  <popa7.h>
#include  <sDBFieldDef.hpp>
#include  <sOperation.hpp>
#include  <snode.hpp>
#include  <sPropAllocation.hpp>


/******************************************************************************/
/**
\brief  Get - Get data from source


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical PropAllocation :: Get ( )
{
  PropertyHandle         *pi_ptr;
  char                    key[513];
  char                    string[513];
  logical                 term = NO;
BEGINSEQ
  switch ( type )
  {
    case ADT_PropertyPath   : if ( transient )
                              {
                                pi_ptr = source_inst.GetPropertyHandle(expression);
                                pi_ptr->PositionTop();
                                target_pi = *pi_ptr;
                              }
                              else
                              {
                                source_pi.Refresh();
                                if ( is_reference )
                                  target_pi.SetTransientProperty(source_pi);
                                else
                                  target_pi = source_pi;
                              }
                              break;
    case ADT_Expression     : if ( operation.Execute(NULL) )
                                                     SDBERR(556)
                              source_pi.CopyHandle(&operation.GetResult());
                              if ( is_reference )
                                target_pi.SetTransientProperty(source_pi);
                              else
                                target_pi = source_pi;
                              break;
    case ADT_SortKey        : if ( source_pi.ExtractSortKey(key).GetData() ||
                                   source_pi.ExtractKey(key).GetData() )
                                target_pi = key;
                              break;
    case ADT_SortKey_String : if ( source_pi.ExtractSortKey(key).GetData() ||
                                   source_pi.ExtractKey(key).GetData() )
                                target_pi = source_pi.KeyToString(string,key);
                              break;
    case ADT_GUID           : target_pi = source_pi.GetGUID();
                              break;
    case ADT_LOID           : target_pi = source_pi.GetLOID();
                              break;
    case ADT_Type           : target_pi = source_pi.GetCurrentType();
                              break;
    default                 :                        SDBERR(99)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetSourceFieldDef - Get view source field defintion


\return dbfielddef

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSourceFieldDef"

DBFieldDef *PropAllocation :: GetSourceFieldDef ( )
{
  DBFieldDef             *dbfielddef = NULL;
  switch ( type )
  {
    case ADT_SortKey        : dbfielddef = DBFieldDef::GetStaticFieldDef(T_CHAR);
                              break;
    case ADT_SortKey_String : 
    case ADT_GUID           : 
    case ADT_Type           : dbfielddef = DBFieldDef::GetStaticFieldDef(T_STRING);
                              break;
    case ADT_LOID           : dbfielddef = DBFieldDef::GetStaticFieldDef(T_INT);
                              break;
    default                 : if ( !(dbfielddef = source_pi.IsCollection() ? source_pi.GetFieldDef() : source_pi.GetDescription()) )
                                if ( type == ADT_Expression )
                                {
                                  if ( !(dbfielddef = operation.GetResult().GetDescription()) )
                                  dbfielddef = operation.get_operation()->GetRetvalDefinition();
                                }
 }
  return(dbfielddef);
}

/******************************************************************************/
/**
\brief  PropAllocation - Konstruktor



\param  source_node -
\param  target_node -
\param  prop_name -
\param  source_path -
\param  source_type - Source type
\param  size_w - Field size
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropAllocation"

                        PropAllocation :: PropAllocation (node *source_node, node *target_node, char *prop_name, char *source_path, ADT_Types source_type, int32 size_w )
                     : source_pi(),
  target_pi(),
  source_inst(),
  type(source_type),
  operation(),
  is_reference(NO),
  size(size_w),
  expression(NULL),
  transient(NO)

{
  PropertyHandle     target(target_node);
  PropertyHandle    *prophdl;
  char              *workstr = NULL;
  char              *expr_str;
  char              *last;
BEGINSEQ
  memcpy(name,prop_name,ID_SIZE);
  source_inst.RegisterNode(source_node);
  if ( source_path )
    expression = strdup(source_path);
  
  switch ( type )
  {
    case ADT_PropertyPath   : if ( DBStructDef::IsPathNode(source_path) )
                              {
                                if ( source_pi.Open(source_inst,source_path) )
                                                     SDBERR(555)
                              }
                              else
                              {
                                if ( !(prophdl = source_inst.GetPropertyHandle(source_path,&transient)) )
                                                     SDBERR(555)
                                source_pi.CopyHandle(prophdl);
                              }
                              if ( source_pi.IsCollection() )
                                is_reference = YES;
                              break;
    case ADT_Expression     : if ( operation.Open(source_inst) )
                                                     SDBERR(555)
                              if ( !source_path )    SDBERR(555)
                              workstr = strdup(source_path);
                              if ( *source_path == '{' )
                              if ( last = gvtsfbp(workstr,UNDEF) )
                              {
                                *(last-1) = ';';
                                if ( *last )
                                  *last = 0;
                                expr_str = workstr+1;
                              }
                              else
                                expr_str = source_path;
                              if ( operation.ProvideExpression(expr_str) )
                                                     SDBERR(555)
                              source_pi.CopyHandle(operation.get_operation());
                              if ( source_pi.IsCollection() )
                                is_reference = YES;
                              break;
    case ADT_SortKey        : 
    case ADT_SortKey_String : 
    case ADT_Type           : 
    case ADT_GUID           :
    case ADT_LOID           : source_pi.CopyHandle(&source_inst);
                              is_reference = NO;
                              break;
    default                 :                        SDBERR(99)
  }
  

RECOVER

ENDSEQ
  if ( workstr )
    free(workstr);
}

/******************************************************************************/
/**
\brief  Put - Write data to target


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Put"

logical PropAllocation :: Put ( )
{
  PropertyHandle         *pi_ptr;
  logical                 term = NO;
  if( type == ADT_PropertyPath && !is_reference )
  {
    if ( transient )
    {
      pi_ptr = source_inst.GetPropertyHandle(expression);
      pi_ptr->PositionTop();
      *pi_ptr = target_pi;
    }    
    else
      source_pi = target_pi;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetTarget - Set target property handle


\return term - Termination code

\param  nodeptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTarget"

logical PropAllocation :: SetTarget (node *nodeptr )
{
  PropertyHandle          instance(nodeptr);
  PropertyHandle         *prop_hdl;
  char                    names[ID_SIZE+1];
  logical                 term = NO;
  gvtxbts(names,name,ID_SIZE);
  if ( prop_hdl = instance.GetPropertyHandle(names) )
    target_pi.CopyHandle(prop_hdl);
  return(term);
}

/******************************************************************************/
/**
\brief  ~PropAllocation - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~PropAllocation"

                        PropAllocation :: ~PropAllocation ( )
{

  if ( expression )
    free(expression);
  expression = NULL;

}


