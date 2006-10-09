/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBVProperty

\brief    Property definition for view


\date     $Date: 2006/03/12 19:17:14,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBVProperty"

#include  <popa7.h>
#include  <sDBViewDef.hpp>
#include  <sPropAllocation.hpp>
#include  <snode.hpp>
#include  <sDBVProperty.hpp>


/******************************************************************************/
/**
\brief  CreateAllocation - 


\return prop_alloc -

\param  source_node -
\param  target_node -
\param  view_name - View name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAllocation"

PropAllocation *DBVProperty :: CreateAllocation (node *source_node, node *target_node, char *view_name )
{
  PropAllocation         *prop_allocation = NULL;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(source,UNDEF)
  SDBEV2(name,ID_SIZE)
  SDBEV3(view_name,ID_SIZE)
  
  prop_allocation = new PropAllocation(source_node,target_node,name,source,type,size);
  if ( SDBERROR )                                    SDBERR(555)

RECOVER
  delete prop_allocation;
  prop_allocation = NULL;
ENDSEQ
  return(prop_allocation);
}

/******************************************************************************/
/**
\brief  DBVProperty - Konstruktor


-------------------------------------------------------------------------------
\brief i0


\param  prop_name -
\param  source_path -
\param  source_type - Source type
\param  size_w - Field size
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBVProperty"

                        DBVProperty :: DBVProperty (char *prop_name, char *source_path, ADT_Types source_type, int32 size_w )
                     :   source(source_path ? strdup(source_path) : NULL),
  type(source_type),
  size(size_w),
  view_definition(NULL)
{

  if ( prop_name )
    gvtxstb(name,prop_name,ID_SIZE);

}

/******************************************************************************/
/**
\brief i01


\param  prop_name -
\param  view_def - Internal view definition
\param  source_type - Source type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBVProperty"

                        DBVProperty :: DBVProperty (char *prop_name, DBViewDef &view_def, ADT_Types source_type )
                     :   source(NULL),
  type(source_type),
  size(UNDEF),
  view_definition(NULL)
{

  if ( prop_name )
    gvtxstb(name,prop_name,ID_SIZE);
  view_definition = new DBViewDef(view_def);

}

/******************************************************************************/
/**
\brief  ~DBVProperty - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBVProperty"

                        DBVProperty :: ~DBVProperty ( )
{

  if ( source )
    free(source);
  source = NULL;
  delete view_definition;
  view_definition = NULL;

}


