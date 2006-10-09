/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODataLayoutRef

\brief    


\date     $Date: 2006/03/13 21:34:01,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODataLayoutRef_HPP
#define   ODataLayoutRef_HPP

class     ODataLayoutRef;

class     DPixmap;
#include  <sDFont.hpp>
#include  <sODataLayout.hpp>
class  ODataLayoutRef
{
protected  :         ODataLayout                                 *layout;                                                    //

public     :
                     ODataLayout                                 *get_layout() { return(layout); }
public     :         OGUI7ImpExp                 QColor *GetBackgroundColor ( );
public     :         OGUI7ImpExp                 QFont *GetFont ( );
public     :         OGUI7ImpExp                 char *GetHelp ( );
public     :         OGUI7ImpExp                 QIcon *GetIcon ( );
public     :         OGUI7ImpExp                 DFont GetLayout ( );
public     :         OGUI7ImpExp                 QColor *GetTextColor ( );
public     :         OGUI7ImpExp                 char *GetToolTip ( );
public     :                                     logical HasLayout ( );
public     :                                                             ODataLayoutRef (logical is_owner );
public     :                                     void ProvideDataLayout (logical is_owner );
public     :                                     void Reset ( );
public     :                                     void SetBackgroundColor (QColor *pQColor );
public     :         OGUI7ImpExp                 void SetFont (QFont *pQFont );
public     :         OGUI7ImpExp                 void SetHelp (char *string );
public     :         OGUI7ImpExp                 void SetIcon (QIcon *pQIcon );
public     :         OGUI7ImpExp                 void SetIcon (DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled );
public     :         OGUI7ImpExp                 void SetLayout (DFont *pDFont );
public     :         OGUI7ImpExp                 void SetTextColor (QColor *pQColor );
public     :         OGUI7ImpExp                 void SetToolTip (char *string );
public     :                                                             ~ODataLayoutRef ( );
};

#endif
