/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/08/26 17:24:30,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OTreeLayout_HPP
#define   OTreeLayout_HPP

class     OTreeLayout;

#include  <sDLL.h>
class     OTreeLayout;
class     OTreeLayout;
#include  <cADK_DataReferenceType.h>
#include  <cODSPropertyType.h>
#include  <sODSPropPath.hpp>
#include  <sOListLayout.hpp>
class  OTreeLayout :public OListLayout
{
protected  :         DLL(OTreeLayout)                            *regions;                                                   // Sub-regions
public     :         QColor                                       qColorBase;                                                // 
protected  :         logical                                      bColorBase;                                                // 
protected  :         logical                                      owns_sub_regions;                                          // Sub region owner
protected  :         logical                                      dirty;                                                     // 
protected  :         int32                                        last_id;                                                   // Internal identification of the region

public     :
                     DLL(OTreeLayout)                            *get_regions() { return(regions); }
                     logical                                      get_owns_sub_regions() { return(owns_sub_regions); }
                     logical                                      get_dirty() { return(dirty); }
                     int32                                        get_last_id() { return(last_id); }
public     :                  OGUIImpExp            OTreeLayout *AddRegion (char *prop_path, logical is_collection, char *strname, char *sort_index_name, ODSPropertyType prop_type=PT_undefined, PIACC accmode_w=PI_Update );
public     :                  OGUIImpExp            OTreeLayout *AddRegion (int32 parent_id, char *prop_path, logical is_collection, ODSPropertyType prop_type=PT_undefined );
public     :                  OGUIImpExp            logical AddSubRegions (int id );
public     :                  OGUIImpExp            logical AddSubRegions (OTreeLayout *tree_layout );
public     :                                        OListLayout *FindColumn (int32 region_id, int32 column_id );
public     :                                        OTreeLayout *FindRegion (int32 region_id );
public     :                                        int GetSubRegionCount (int32 region_id );
public     : virtual                                OTreeLayout *GetTreeLayout ( );
public     :                                        int32 IncreaseID ( );
public     :                  OGUIImpExp            logical IsRecursive (int id );
public     :                  OGUIImpExp            logical IsRecursive ( );
public     :                  OGUIImpExp            OTreeLayout *LocateID (int id );
public     :                  OGUIImpExp                 OTreeLayout (OTreeLayout *pOTreeLayout );
public     :                  OGUIImpExp                 OTreeLayout (OListLayout *pOListLayout, ODSPropPath *oprop_path );
public     :                  OGUIImpExp                 OTreeLayout (OListLayout *list_layout );
public     :                  OGUIImpExp            OTreeLayout *Region (int index );
public     :                                        void RemoveSubRegions (logical reset_columns );
public     :                  OGUIImpExp            OTreeLayout *ReplaceSubRegions (int32 parent_id, int32 region_id );
public     :                  OGUIImpExp            OTreeLayout *ReplaceSubRegions (int32 region_id );
public     :                                        logical ResetRegion (int32 parent_id, int32 region_id, logical reset_columns );
public     :                                        logical ResetRegion (int32 region_id, logical reset_columns );
public     :                                        void SetupLastID (int id );
public     :                                        OTreeLayout *TopRegion ( );
public     :                                        void reset_dirty ( );
public     :                                        void set_dirty ( );
public     :                                        void set_parent (OTreeLayout *tree_layout );
public     :                  OGUIImpExp                 ~OTreeLayout ( );
};

#endif
