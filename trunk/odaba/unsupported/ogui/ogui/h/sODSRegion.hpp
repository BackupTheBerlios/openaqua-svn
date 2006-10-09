/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ODSRegion

\brief    


\date     $Date: 2006/08/26 17:47:36,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSRegion_HPP
#define   ODSRegion_HPP

class     ODSRegion;

#define  _ACCEPT_PTR                               logical (QObject::*Accept)( ODS& )
#include  <sDLL.h>
class     ODSRegion;
#ifndef   VECTOR_int_HPP
#define   VECTOR_int_HPP
#include  <sVECTOR.h>
#endif
#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     ODSPropPath;
class     ODSRegion;
class     ODSTree;
class     OFont;
class     OListLayout;
class     OTreeLayout;
class     PropertyHandle;
#include  <sODSList.hpp>
#pragma pack(4)

class  ODSRegion :public ODSList
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         ODSTree                                     *tree;                                                      // 
protected  :         DLL(ODSRegion)                              *sub_regions;                                               // 
protected  :         logical                                      sub_regions_initialized;                                   // 
protected  :         logical                                      dirty;                                                     // 

public     :
                     ODSTree                                     *get_tree() { return(tree); }
                     DLL(ODSRegion)                              *get_sub_regions() { return(sub_regions); }
                     logical                                      get_sub_regions_initialized() { return(sub_regions_initialized); }
                     logical                                      get_dirty() { return(dirty); }
public     :                                        void Activate ( );
public     :                                        void BlockSignals (logical block_opt );
public     :                                        void Clear (logical reset_columns );
public     :                                        void Deactivate ( );
public     :                                        OTreeLayout *GetLayout ( );
public     :                                        PropertyHandle *GetPropertyHandle (ODSPropPath *pODSPropPath );
public     :                                        logical HasData ( );
public     :                                        logical HasSubRegions ( );
public     :                                             ODSRegion (ODSTree *pODSTree );
public     :                                        ODSRegion *ParentRegion ( );
public     :                                        ODSRegion *ParentRegion (ODSRegion *searchRegion );
public     :                                        logical RefreshRegion (int32 region_id );
public     :                  OGUIImpExp            ODSRegion *Region (int index );
public     : virtual                                ODSRegion *RegionODS ( );
public     :                                        void RemoveRegion (int32 parent_id, int32 region_id, logical reset_columns );
public     :                                        void ResetChildStates ( );
public     :                                        void ResetStates ( );
public     :                                        logical SetFilter (char *expression, logical enable_opt );
public     :                                        logical SetLayout (OTreeLayout *pOTreeLayout );
public     :                                        logical SetLayout ( );
public     :                                        logical SetupLayout ( );
public     :                                        logical UpdateTreeLayout (OTreeLayout *tree_layout );
public     :                                        void set_dirty (logical bdirty, logical brecursive );
public     : public slots:                          void slotCollectionChanged ( );
public     : public slots:                          void slotCollectionReset ( );
public     : public slots:                          void slotInstanceInserted ( );
public     : public slots:                          void slotInstanceRemoved ( );
public     : public slots:                          void slotInstanceSelected ( );
public     : public slots:                          void slotInstanceUpdated ( );
public     :                                             ~ODSRegion ( );
};

#pragma pack()
#endif
