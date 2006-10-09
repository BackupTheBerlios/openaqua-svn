/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSWindow



\date     $Date: 2006/04/28 16:56:52,54 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSWindow_HPP
#define   OSWindow_HPP

class     OSWindow;

#include  <sOStyle.hpp>
#pragma pack(4)

class  OSWindow :public OStyle
{
protected  :         logical                                      workspace;                                                 
protected  :         logical                                      vscrol;                                                    
protected  :         logical                                      hscrol;                                                    

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                        logical HasHscrol ( );
public     :                                        logical HasVscrol ( );
public     :                                        logical IsWorkspace ( ) const;
public     :                                             OSWindow ( );
public     :                                             OSWindow (OStyle bcOStyle, logical is_workspace, logical vscroll, logical hscroll );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSWindow ( );
};

#pragma pack()
#endif
