/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OFrameStyle



\date     $Date: 2006/04/28 17:15:00,26 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OFrameStyle_HPP
#define   OFrameStyle_HPP

class     OFrameStyle;

class     PropertyHandle;
#include  <cADK_WinType.h>
#include  <sOPersistent.hpp>
#include  <sOResource.hpp>
#pragma pack(4)

class  OFrameStyle :public OPersistent
{
protected  :         ADK_WinType                                  winType;                                                   
protected  :         logical                                      title;                                                     
protected  :         logical                                      minmax;                                                    
protected  :         logical                                      close;                                                     
protected  :         logical                                      move;                                                      
protected  :         logical                                      resize;                                                    
protected  :         logical                                      systemModal;                                               
protected  :         logical                                      smallTitle;                                                
protected  :         logical                                      topAlways;                                                 

public     :
public     :                                        logical HasClose ( ) const;
public     :                                        logical HasMinmax ( ) const;
public     :                                        logical HasMove ( ) const;
public     :                                        logical HasResize ( );
public     :                                        logical HasSmallTitle ( ) const;
public     :                                        logical HasTitle ( ) const;
public     :                                        logical IsSimpleWindow ( );
public     :                                        logical IsSystemModal ( ) const;
public     :                                        logical IsTopAlways ( ) const;
public     :                                             OFrameStyle ( );
public     :                                             OFrameStyle (OPersistent bcOPersistent, ADK_WinType vADK_WinType, logical has_title, logical has_minmax, logical has_close, logical can_move, logical can_resize, logical is_systemModal, logical has_smallTitle, logical is_alwaysontop );
public     : virtual                                logical Read (PropertyHandle *ph );
public     :                                        ADK_WinType WinType (ADK_WinType vADK_WinType ) const;
};

#pragma pack()
#endif
