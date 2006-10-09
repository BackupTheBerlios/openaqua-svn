/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODial

\brief    Dial
          The  ODial class provides a rounded  range control (like a speedometer
          or potentiometer).

          ODial  is  used  when  the  user  needs  to  control  a value within a
          program-definable   range,   and   the   range   either   wraps around
          (typically,  0..359  degrees)  or  the  dialog  layout  needs a square
          widget.

          Both  API- and UI-wise, the dial is  very similar to a slider. Indeed,
          when  wrapping() is  FALSE (the  default) there  is no real difference
          between  a slider  and a  dial. They  have the same signals, slots and
          member  functions, all of which do the  same things. Which one you use
          depends only on your taste and on the application.

\date     $Date: 2006/03/13 21:34:05,59 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODial_HPP
#define   ODial_HPP

class     ODial;

class     ODS;
class     ODataWidget;
#include  <sOEHControlValue.hpp>
class  ODial :public QDial,
public OEHControlValue
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    //
protected  :         logical                                      ignore;                                                    //

public     :
public     : virtual OGUI7ImpExp                 logical Activate ( );
public     :                                     public slots: void ClearData ( );
public     : virtual OGUI7ImpExp                 logical Deactivate (logical data_only=NO );
public     :                                     public slots: void FillData ( );
public     :                                     logical Initialize ( );
public     :         OGUI7ImpExp                                         ODial (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :         OGUI7ImpExp                                         ODial (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                     void SetReadOnly (logical fReadOnly );
public     :                                     QWidget *WidgetQ ( );
public     :                                     public slots: void storeToValue ( );
};

#endif
