/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OElementStyle



\date     $Date: 2006/04/28 15:37:31,81 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OElementStyle_HPP
#define   OElementStyle_HPP

class     OElementStyle;

#include  <sDLL.h>
class     OEventAction;
class     OBitmap;
class     OCBitmap;
class     OElementStyle;
class     OFrameStyle;
class     OListLayout;
class     OTreeLayout;
class     OWidget;
class     PropertyHandle;
class     TControl;
#include  <sDMargin.hpp>
#include  <sDSize.hpp>
#include  <sOContextStyle.hpp>
#include  <sODLLItem.hpp>
#include  <sODataSource.hpp>
#include  <sOFont_.hpp>
#include  <sOLayout.hpp>
#include  <sOResource.hpp>
#include  <sOStyle.hpp>
#include  <sOStyleElement.hpp>
#pragma pack(4)

class  OElementStyle :public OStyleElement
{
protected  :         OStyle                                      *style;                                                     
protected  :         OLayout                                     *layout;                                                    
protected  :         OFont_                                      *font;                                                      
protected  :         OCBitmap                                    *bitmap;                                                    
protected  :         logical                                      concealed;                                                 

public     :
                     OStyle                                      *get_style() { return(style); }
                     OLayout                                     *get_layout() { return(layout); }
                     OFont_                                      *get_font() { return(font); }
                     OCBitmap                                    *get_bitmap() { return(bitmap); }
                     logical                                      get_concealed() { return(concealed); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        char *GetControlName ( );
public     :                                        ODataSource *GetDataSource ( );
public     :                                        OBitmap *GetEnabledBitmap ( );
public     : virtual                                DSize GetFrameSize (DSize dsize, DMargin &field_margin );
public     :                                        logical IsConcealed ( );
public     :                                        logical IsField ( );
public     :                                             OElementStyle ( );
public     :                                             OElementStyle (OStyleElement bcOStyleElement, OStyle *pOStyle, OLayout *pOLayout, OFont_ *pOFont_, OCBitmap *pOCBitmap, logical concealed );
public     : virtual                                TControl *OpenControl (char *typenames, TControl *tparent, OFrameStyle *pOFrameStyle, OResource *owner );
protected  : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        void ResetActions (DLL(OEventAction) *action_list );
public     :                                        void SetStyle (OStyle *pOStyle );
public     : virtual                                logical SetupListLayout (OListLayout *pOListLayout );
public     : virtual                                logical SetupTreeLayout (OTreeLayout *pOTreeLayout, logical recursive );
public     :                                        OStyle *Style ( ) const;
public     :                                        void setConcealed (logical f );
public     : virtual                                     ~OElementStyle ( );
};

#pragma pack()
#endif
