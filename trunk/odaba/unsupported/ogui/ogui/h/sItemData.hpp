/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ItemData

\brief    


\date     $Date: 2006/08/02 17:37:26,43 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ItemData_HPP
#define   ItemData_HPP

class     ItemData;

#include  <sDPA.h>
class     CellData;
#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     DPixmap;
class     ItemData;
class     ItemRegion;
class     ItemRegionList;
class     ItemTreeModel;
class     ODSList;
class     ODSRegion;
class     OFont;
class     PropertyHandle;
#include  <sCellData.hpp>
#include  <sDFont.hpp>
#include  <sODSItemInstState.hpp>
#include  <sODataLayoutRef.hpp>
#include  <sQModelIndex.hpp>
class  ItemData :public CellData
{
protected  :         ItemRegion                                  *region;                                                    // 
protected  :         ItemRegionList                              *children;                                                  // 
protected  :         int                                          row;                                                       // 
protected  :         DPA(CellData)                               *cells;                                                     // 
protected  :         char                                        *key_val;                                                   // 
protected  :         int8                                         heading;                                                   // 
protected  :         char                                         expanded;                                                  // 
protected  :         logical                                      checked;                                                   // 
protected  :         logical                                      is_updating;                                               // 

public     :
                     ItemRegion                                  *get_region() { return(region); }
                     ItemRegionList                              *get_children() { return(children); }
                     int                                         &get_row() { return(row); }
                     DPA(CellData)                               *get_cells() { return(cells); }
                     char                                        *get_key_val() { return(key_val); }
                     int8                                         get_heading() { return(heading); }
                     char                                         get_expanded() { return(expanded); }
                     logical                                      get_checked() { return(checked); }
                     logical                                      get_is_updating() { return(is_updating); }
public     :                                        CellData *Cell (int column );
public     :                                        ItemRegionList *Children ( );
public     :                                        QVariant GetCheckState ( );
public     :                                        void GetHierarchyPath (VECTOR(std_string) &string_list );
public     :                                        char *GetKey ( );
public     :                                        DFont GetLayout (int column );
public     :                                        ODataLayoutRef *GetLayoutRef (int column );
public     :                                        QModelIndex GetModelIndex ( );
public     :                                        PropertyHandle *Handle ( );
public     :                                        logical HasLayout (int column );
public     :                                        logical HierSync (logical block_opt );
public     :                                        logical HierSync ( );
public     :                                        logical IsChecked ( );
public     :                                        logical IsExpanding ( );
public     :                                        logical IsHeaderItem ( );
public     :                                        ItemData *IsItemDBIndex (int32 indx0 );
public     :                                        ItemData *IsItemKey (char *skey );
public     :                                        ItemData *IsItemLOID (int32 objid );
public     :                                        ItemData *IsItemRow (int index0 );
public     :                                        ItemData *IsItemValue (QString &pQString, int col );
public     :                                        logical IsStaticItem ( );
public     :                                             ItemData (ItemRegion *pItemRegion, int row_no );
public     :                                        ItemTreeModel *Model ( );
public     :                                        ItemData *Parent ( );
public     :                                        logical Position ( );
public     :                                        ODSRegion *Region ( );
public     :                                        ItemRegionList *RegionList ( );
public     :                                        void ResetChildData (logical chk_opt );
public     :                                        void SetExpanded (logical option );
public     :                                        void SetHeading ( );
public     :                                        logical SetIcon (QIcon *pQIcon, int column );
public     :                                        logical SetIcon (DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled, int column );
public     :                                        void SetKey (char *skey );
public     :                                        logical SetLayout (DFont *pDFont, int column );
public     :                                        void SetStatic (ItemRegionList *pItemRegionList );
public     :                                        logical Setup ( );
public     :                                        void ToggleChecked ( );
public     :                                        void UpdateChildData (logical chk_opt );
public     :                                        void set_is_updating (logical update_opt );
public     :                                        void set_row (int index0 );
public     :                                        void setup_lastIndex (int32 diff );
public     : virtual                                     ~ItemData ( );
};

#endif
