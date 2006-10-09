/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OMenu



\date     $Date: 2006/04/28 16:50:40,82 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OMenu_HPP
#define   OMenu_HPP

class     OMenu;

class     PropertyHandle;
class     TControl;
#include  <sOEventAction.hpp>
#include  <sOEventActionControl.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOResource.hpp>
#include  <sOStyleElement.hpp>
#pragma pack(4)

class  OMenu :public OEventAction
{
protected  :         OFrameStyle                                  frameStyle;                                                

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OMenu ( );
public     :                                             OMenu (OEventAction bcOEventAction, OFrameStyle frameStyle );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OMenu ( );
};

#pragma pack()
#endif
