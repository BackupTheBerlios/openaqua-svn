/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OButton



\date     $Date: 2006/04/28 16:15:16,85 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OButton_HPP
#define   OButton_HPP

class     OButton;

class     PropertyHandle;
class     TControl;
#include  <sDPoint.hpp>
#include  <sOEventAction.hpp>
#include  <sOEventActionControl.hpp>
#include  <sOFrameStyle.hpp>
#pragma pack(4)

class  OButton :public OEventAction
{
protected  :         OFrameStyle                                  frameStyle;                                                
protected  :         logical                                      def_opt;                                                   

public     :
                     logical                                      get_def_opt() { return(def_opt); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OButton ( );
public     :                                             OButton (OEventAction bcOEventAction, OFrameStyle frameStyle, logical def_opt );
public     :                                        TControl *Open (TControl *tparent, logical active_f );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        void set_position (DPoint position );
public     : virtual                                     ~OButton ( );
};

#pragma pack()
#endif
