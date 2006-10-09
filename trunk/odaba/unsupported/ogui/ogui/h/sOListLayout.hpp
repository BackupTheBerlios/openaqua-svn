/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OListLayout

\brief    


\date     $Date: 2006/08/24 14:56:28,07 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OListLayout_HPP
#define   OListLayout_HPP

class     OListLayout;

#include  <sDLL.h>
class     OListLayout;
class     DPixmap;
class     OFont;
class     OIconSet;
class     OPixmap;
class     OTreeLayout;
#include  <cODSPropertyType.h>
#include  <sDFont.hpp>
#include  <sODSPropPath.hpp>
#include  <sODataLayoutRef.hpp>
#include  <sOListLayout.hpp>
#pragma pack(4)

class  OListLayout :public ODSPropPath,
public ODataLayoutRef
{
protected  :         OListLayout                                 *parent;                                                    // 
protected  :         int32                                        intern_id;                                                 // 
protected  :         DLL(OListLayout)                            *columns;                                                   // 
protected  :         int                                          width;                                                     // 
protected  :         int                                          widthGrowRate;                                             // 
protected  :         int                                          height;                                                    // 
protected  :         int                                          heightGrowRate;                                            // 
protected  :         int                                          header_width;                                              // 
protected  :         int                                          header_height;                                             // 
protected  :         char                                        *szStaticText;                                              // 

public     :
                     OListLayout                                 *get_parent() { return(parent); }
                     int32                                        get_intern_id() { return(intern_id); }
                     DLL(OListLayout)                            *get_columns() { return(columns); }
                     int                                         &get_width() { return(width); }
                     int                                         &get_widthGrowRate() { return(widthGrowRate); }
                     int                                         &get_height() { return(height); }
                     int                                         &get_heightGrowRate() { return(heightGrowRate); }
                     int                                         &get_header_width() { return(header_width); }
                     int                                         &get_header_height() { return(header_height); }
                     char                                        *get_szStaticText() { return(szStaticText); }
public     :                  OGUIImpExp            OListLayout *AddColumn ( );
public     :                  OGUIImpExp            OListLayout *AddColumn (char *prop_path, char *strname, logical is_collection, char *sort_index_name, ODSPropertyType prop_type=PT_undefined, PIACC accmode_w=PI_Update );
public     :                  OGUIImpExp            OListLayout *Column (int column );
public     :                                        int32 ColumnCount ( );
public     :                  OGUIImpExp            logical Copy (OListLayout *list_layout );
public     :                  OGUIImpExp            logical CopyColumns (OListLayout *list_layout );
public     :                                        logical DisplayHeader ( );
public     :                                        OListLayout *FindColumn (int32 column_id );
public     :                  OGUIImpExp            char *GetStaticText ( );
public     : virtual                                OTreeLayout *GetTreeLayout ( );
public     :                  OGUIImpExp                 OListLayout (OListLayout *pOListLayout );
public     :                  OGUIImpExp                 OListLayout (const OListLayout &rcOListLayout );
public     :                  OGUIImpExp                 OListLayout (OListLayout *pOListLayout, char *prop_path, int32 col_width, int32 grow_rate=0, ODSPropertyType prop_type=PT_undefined );
public     :                  OGUIImpExp                 OListLayout (OListLayout *pOListLayout, ODSPropPath *oprop_path );
public     :                                        logical RemoveColumn (int32 column_id );
public     :                  OGUIImpExp            void RemoveColumns ( );
public     :                                        void SetDirty ( );
public     :                  OGUIImpExp            logical SetFont (DFont *pDFont, int column_w=AUTO );
public     :                  OGUIImpExp            void SetHeaderSize (int32 col_width, int32 col_height );
public     :                  OGUIImpExp            void SetHeight (int32 col_height, int32 grow_rate=0 );
public     :                  OGUIImpExp            void SetStaticText (char *szText );
public     :                  OGUIImpExp            void SetWidth (int32 col_width, int32 grow_rate=0 );
public     :                  OGUIImpExp            void set_intern_id (int id );
public     :                                        void set_parent (OListLayout *list_layout );
public     : virtual                                void xx_Paint (const char &rcOListLayoutPS ) const;
public     :                  OGUIImpExp                 ~OListLayout ( );
};

#pragma pack()
#endif
