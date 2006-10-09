/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSEdit



\date     $Date: 2006/04/28 16:54:13,51 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSEdit_HPP
#define   OSEdit_HPP

class     OSEdit;

class     OToolBox;
class     PropertyHandle;
#include  <sOHighlighter.hpp>
#include  <sOStyle.hpp>
#pragma pack(4)

class  OSEdit :public OStyle
{
protected  :         logical                                      multiLine;                                                 
protected  :         logical                                      rich_text;                                                 
protected  :         OHighlighter                                *highlighter;                                               
protected  :         OToolBox                                    *toolbar;                                                   
protected  :         logical                                      pass_word;                                                 
protected  :         logical                                      auto_hscrol;                                               
protected  :         logical                                      auto_vscrol;                                               
protected  :         logical                                      upper;                                                     
protected  :         logical                                      lower;                                                     

public     :
                     logical                                      get_multiLine() { return(multiLine); }
                     logical                                      get_rich_text() { return(rich_text); }
                     OHighlighter                                *get_highlighter() { return(highlighter); }
                     OToolBox                                    *get_toolbar() { return(toolbar); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                        logical HasHscrol ( );
public     :                                        logical HasPassword ( );
public     :                                        logical HasVscrol ( );
public     :                                             OSEdit ( );
public     :                                             OSEdit (OStyle bcOStyle, logical is_multiline, logical is_richtext, OHighlighter *pOHighlighter, OToolBox *pOToolBox, logical is_password, logical auto_hscroll, logical auto_vscroll, logical is_upper, logical is_lower );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSEdit ( );
};

#pragma pack()
#endif
