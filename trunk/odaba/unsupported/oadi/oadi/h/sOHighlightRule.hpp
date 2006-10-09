/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OHighlightRule



\date     $Date: 2006/04/28 16:47:56,34 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OHighlightRule_HPP
#define   OHighlightRule_HPP

class     OHighlightRule;

#ifndef   DLL_OSyntaxClass_HPP
#define   DLL_OSyntaxClass_HPP
#include  <sOSyntaxClass.hpp>
#include  <sDLL.h>
#endif
class     OFont_;
class     PropertyHandle;
#include  <sOResource.hpp>
class  OHighlightRule :public OResource
{
protected  :         OFont_                                      *font;                                                      
protected  :         DLL(OSyntaxClass)                            syntax_classes;                                            

public     :
                     OFont_                                      *get_font() { return(font); }
                     DLL(OSyntaxClass)                           &get_syntax_classes() { return(syntax_classes); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OHighlightRule ( );
public     :                                             OHighlightRule (OResource bcOResource, OFont_ *pOFont_, DLL(OSyntaxClass) *syntax_classes );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                             ~OHighlightRule ( );
};

#endif
