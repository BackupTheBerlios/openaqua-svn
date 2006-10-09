/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHSlotRouter

\brief    


\date     $Date: 2006/03/13 21:34:15,85 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHSlotRouter_HPP
#define   OEHSlotRouter_HPP

class     OEHSlotRouter;

class     OEHControlData;
class  OEHSlotRouter :public QObject
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         OEHControlData                              *value;                                                     //

public     :
                     OEHControlData                              *get_value() { return(value); }
public     :                                     void ActivateColl ( );
public     :                                     void Connect (char *ods_signal, char *oeh_slot );
public     :                                     void Disconnect (char *ods_signal, char *oeh_slot );
public     :                                                             OEHSlotRouter (OEHControlData *pOEHControlData );
public     :                                     void Reconnect (char *ods_signal, char *oeh_slot, char *oeh_prev_slot );
public     :                                     public slots: void activateDesignMode (logical fDmode );
public     :                                     void activateValue ( );
public     :                                     void clearValue ( );
public     :                                     void closeValue ( );
public     :                                     public slots: void handleActivate ( );
public     :                                     public slots: void handleClose ( );
public     :                                     public slots: void handleOpen ( );
public     :                                     void insertedValue ( );
public     :                                     public slots: void listChange ( );
public     :                                     public slots: void listReset ( );
public     :                                     public slots: void listUpdate ( );
public     :                                     void loadValue ( );
public     :                                     void openValue ( );
public     :                                     void removedValue ( );
public     :                                     logical set_value (OEHControlData *pOEHControlData );
public     :                                     void updateValue ( );
public     :                                     public slots: void valueInsert ( );
public     :                                     public slots: void valueRemove ( );
public     :                                     public slots: void valueReset ( );
public     :                                     public slots: void valueSelect ( );
public     :                                     public slots: void valueUpdate ( );
public     :                                                             ~OEHSlotRouter ( );
};

#endif
