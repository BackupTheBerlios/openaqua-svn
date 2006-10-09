/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OTreeLayout

\brief    Tree Layout definition
          A  tree layout definition  describes a list  consisting of a number of
          regions  (different horizontal areas orthogonal to columns). Thus, you
          may  display in one list the  children (first region) and the accounts
          (second  region) of a person. The  column structure for each region is
          described  by a list layout (OListLayout) for each region. Each region
          is  described as tree layout (OTreeLayout)  and may have any number of
          sub-regions,  which  might  have  sub regions again etc. Thus, complex
          hierarchical  tree structures  can be  defined, which can be displayed
          in a tree view.

\date     $Date: 2006/08/26 17:42:03,35 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OTreeLayout"

#include  <pogui7.h>
#ifndef   DLL_OTreeLayout_HPP
#define   DLL_OTreeLayout_HPP
#include  <sOTreeLayout.hpp>
#include  <sDLL.h>
#endif
#include  <sOTreeLayout.hpp>
#include  <sOTreeLayout.hpp>


/******************************************************************************/
/**
\brief  AddRegion - 



\return pOTreeLayout - Tree layout definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  is_collection - Is referenced path pointing to a collection
\param  strname - 
\param  sort_index_name - 
\param  prop_type - Property path  type
\param  accmode_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddRegion"

OTreeLayout *OTreeLayout :: AddRegion (char *prop_path, logical is_collection, char *strname, char *sort_index_name, ODSPropertyType prop_type, PIACC accmode_w )
{
  OTreeLayout      *reg_layout = NULL;
BEGINSEQ
  SetDirty();
  if ( !regions )
  {
    if ( !(regions = new DLL(OTreeLayout)) )         OGUIERR(95)
    owns_sub_regions = YES;
  }
  
  if ( !(reg_layout = new OTreeLayout(this)) )       OGUIERR(95)
  regions->AddTail(reg_layout);
  
  reg_layout->set_intern_id(TopRegion()->IncreaseID());  // by default reagions are not recursive
  reg_layout->set_parent(this);
  reg_layout->SetPath(prop_path,strname,is_collection,
                      sort_index_name,prop_type,accmode_w);

RECOVER

ENDSEQ
  return(reg_layout);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  parent_id - 
\param  prop_path - Property path
\param  is_collection - Is referenced path pointing to a collection
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddRegion"

OTreeLayout *OTreeLayout :: AddRegion (int32 parent_id, char *prop_path, logical is_collection, ODSPropertyType prop_type )
{

  return( FindRegion(parent_id)->AddRegion(prop_path,is_collection,NULL,NULL,prop_type) );

}

/******************************************************************************/
/**
\brief  AddSubRegions - Reuse sub-regions from another OTreeLeyout

        The  function takes  over the  sub-region list from another OTreeLayout.
        This layout should be a parent of the current one.

\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddSubRegions"

logical OTreeLayout :: AddSubRegions (int id )
{

  return ( this ? AddSubRegions(GetTreeLayout()->LocateID(id)) : YES );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  tree_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddSubRegions"

logical OTreeLayout :: AddSubRegions (OTreeLayout *tree_layout )
{
  logical       term = NO;
BEGINSEQ
  SetDirty();
  RemoveSubRegions(NO);
  
  if ( !tree_layout )                                OGUIERR(99)
  regions = tree_layout->get_regions();
  columns = tree_layout->get_columns();



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FindColumn - 



\return pOListLayout - 

\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindColumn"

OListLayout *OTreeLayout :: FindColumn (int32 region_id, int32 column_id )
{
  OListLayout         *region = FindRegion(region_id);
  OListLayout         *column = NULL;
 if ( region )
   column = region->FindColumn(column_id);
  return(column);
}

/******************************************************************************/
/**
\brief  FindRegion - 



\return pOTreeLayout - Tree layout definition

\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindRegion"

OTreeLayout *OTreeLayout :: FindRegion (int32 region_id )
{
  OTreeLayout          *pOTreeLayout = this;
BEGINSEQ
  if ( !this || !region_id || region_id == intern_id )
                                                     LEAVESEQ
  if ( !owns_sub_regions )                           ERROR
  
  regions->GoTop();
  while ( pOTreeLayout = regions->GetNext() )
    if ( pOTreeLayout = pOTreeLayout->FindRegion(region_id) )
                                                     LEAVESEQ
  ERROR

RECOVER
  pOTreeLayout = NULL;
ENDSEQ
  return(pOTreeLayout);
}

/******************************************************************************/
/**
\brief  GetSubRegionCount - 



\return count - 

\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubRegionCount"

int OTreeLayout :: GetSubRegionCount (int32 region_id )
{
  OTreeLayout          *pOTreeLayout = FindRegion(region_id);
  return( pOTreeLayout ? pOTreeLayout->regions->GetCount() : UNDEF);



}

/******************************************************************************/
/**
\brief  GetTreeLayout - 



\return pOTreeLayout - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTreeLayout"

OTreeLayout *OTreeLayout :: GetTreeLayout ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  IncreaseID - 



\return column_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IncreaseID"

int32 OTreeLayout :: IncreaseID ( )
{

  return(++last_id);

}

/******************************************************************************/
/**
\brief  IsRecursive - 



\return cond - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRecursive"

logical OTreeLayout :: IsRecursive (int id )
{

  return( this && parent 
          ? parent->get_intern_id() == id 
            ? YES 
            : parent->GetTreeLayout()->IsRecursive(id)
          : NO );


}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRecursive"

logical OTreeLayout :: IsRecursive ( )
{

  return( IsRecursive(intern_id) );

}

/******************************************************************************/
/**
\brief  LocateID - 



\return tree_layout - 

\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateID"

OTreeLayout *OTreeLayout :: LocateID (int id )
{

  return (   !this             ? NULL
           : intern_id == id   ? this
           : parent->GetTreeLayout()->LocateID(id)     );

}

/******************************************************************************/
/**
\brief  OTreeLayout - Construct tree layout

        There  are several constructors for simple  data areas (as edit control)
        or  very complex data areas as for  tree view. The objects passed to the
        tree layout are copied.

-------------------------------------------------------------------------------
\brief  i0 - 



\param  pOTreeLayout - Tree layout definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeLayout"

     OTreeLayout :: OTreeLayout (OTreeLayout *pOTreeLayout )
                     : OListLayout(pOTreeLayout),
  regions(NULL),
  qColorBase(),
  bColorBase(false),
  owns_sub_regions(NO),
  dirty(YES)


{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  pOListLayout - 
\param  oprop_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeLayout"

     OTreeLayout :: OTreeLayout (OListLayout *pOListLayout, ODSPropPath *oprop_path )
                     : OListLayout (pOListLayout,oprop_path),
  regions(NULL),
  qColorBase(),
  bColorBase(),
  dirty(YES),
  owns_sub_regions(NO)

{



}

/******************************************************************************/
/**
\brief  i02 - 



\param  list_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeLayout"

     OTreeLayout :: OTreeLayout (OListLayout *list_layout )
                     : OListLayout (*list_layout),
  regions(NULL),
  qColorBase(),
  bColorBase(),
  dirty(YES),
  owns_sub_regions(NO)

{



}

/******************************************************************************/
/**
\brief  Region - Get region layout

        The  function  retuerns  the  region layout (OTreeLayout) for the region
        with the index number passed (firts region has number 0).

\return tree_layout - 

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Region"

OTreeLayout *OTreeLayout :: Region (int index )
{

  return (   index >= 0 
           ? regions ? regions->GetObjectInst(index) 
                     : NULL 
           : NULL           );

}

/******************************************************************************/
/**
\brief  RemoveSubRegions - 




\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveSubRegions"

void OTreeLayout :: RemoveSubRegions (logical reset_columns )
{
  OTreeLayout     *region;
  SetDirty();
  if ( regions && owns_sub_regions )
  {
    while ( region = regions->RemoveTail() )
      delete region;
    delete regions;

    if ( reset_columns )
      RemoveColumns();
  }
  else if ( reset_columns )
    columns = NULL;

  regions          = NULL;
  owns_sub_regions = NO;


}

/******************************************************************************/
/**
\brief  ReplaceSubRegions - 



\return pOTreeLayout - Tree layout definition
-------------------------------------------------------------------------------
\brief  i01 - 



\param  parent_id - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSubRegions"

OTreeLayout *OTreeLayout :: ReplaceSubRegions (int32 parent_id, int32 region_id )
{

  return( FindRegion(parent_id)->ReplaceSubRegions(region_id) );

}

/******************************************************************************/
/**
\brief  i03 - 



\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSubRegions"

OTreeLayout *OTreeLayout :: ReplaceSubRegions (int32 region_id )
{
  OTreeLayout   *region = TopRegion()->FindRegion(region_id);
  if ( region )
    AddSubRegions(region);

  set_intern_id(region_id);
  return(region);
}

/******************************************************************************/
/**
\brief  ResetRegion - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  parent_id - 
\param  region_id - 
\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetRegion"

logical OTreeLayout :: ResetRegion (int32 parent_id, int32 region_id, logical reset_columns )
{
  OTreeLayout     *pOTreeLayout;
  logical          term = NO;
BEGINSEQ
  if ( !(pOTreeLayout = FindRegion(parent_id)) )     ERROR

  if ( pOTreeLayout->ResetRegion(region_id,reset_columns) )       
                                                     ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  region_id - 
\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetRegion"

logical OTreeLayout :: ResetRegion (int32 region_id, logical reset_columns )
{
  OTreeLayout     *pOTreeLayout;
  logical          term = NO;
BEGINSEQ
  SetDirty();
  if ( !region_id )
    RemoveSubRegions(reset_columns);
  else
  {
    regions->GoTop();
    while ( pOTreeLayout = regions->GetNext() )
    {
      if ( pOTreeLayout->intern_id == intern_id )
      {
        regions->Remove(pOTreeLayout);
        if ( owns_sub_regions )
          delete pOTreeLayout;                                  
        LEAVESEQ
      }
    }  
  }  
  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupLastID - 




\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupLastID"

void OTreeLayout :: SetupLastID (int id )
{

  if ( id > last_id )
    last_id = id;

}

/******************************************************************************/
/**
\brief  TopRegion - 



\return pOTreeLayout - Tree layout definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TopRegion"

OTreeLayout *OTreeLayout :: TopRegion ( )
{

  return( this && parent ? parent->GetTreeLayout()->TopRegion() : this );



}

/******************************************************************************/
/**
\brief  reset_dirty - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "reset_dirty"

void OTreeLayout :: reset_dirty ( )
{

  dirty = NO;

}

/******************************************************************************/
/**
\brief  set_dirty - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_dirty"

void OTreeLayout :: set_dirty ( )
{

  dirty = YES;

}

/******************************************************************************/
/**
\brief  set_parent - 




\param  tree_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_parent"

void OTreeLayout :: set_parent (OTreeLayout *tree_layout )
{

  parent = tree_layout;

}

/******************************************************************************/
/**
\brief  ~OTreeLayout - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OTreeLayout"

     OTreeLayout :: ~OTreeLayout ( )
{

  RemoveSubRegions(YES);


}


