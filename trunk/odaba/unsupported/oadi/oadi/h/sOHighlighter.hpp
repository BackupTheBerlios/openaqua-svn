/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OHighlighter



\date     $Date: 2006/04/28 16:46:56,12 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OHighlighter_HPP
#define   OHighlighter_HPP

class     OHighlighter;

#ifndef   DLL_OHighlightRule_HPP
#define   DLL_OHighlightRule_HPP
#include  <sOHighlightRule.hpp>
#include  <sDLL.h>
#endif
class     PropertyHandle;
#include  <sOResource.hpp>
class  OHighlighter :public OResource
{
protected  :         DLL(OHighlightRule)                          rules;                                                     

public     :
                     DLL(OHighlightRule)                         &get_rules() { return(rules); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OHighlighter ( );
public     :                                             OHighlighter (OResource bcOResource, DLL(OHighlightRule) *rules );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OHighlighter ( );
};

#endif
