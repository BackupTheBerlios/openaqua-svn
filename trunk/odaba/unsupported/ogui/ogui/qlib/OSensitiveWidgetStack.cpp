/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSensitiveWidgetStack

\brief    


\date     $Date: 2006/03/13 21:36:14,14 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSensitiveWidgetStack"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sOSlotRouter.hpp>
#include  <sOSensitiveWidgetStack.hpp>


/******************************************************************************/
/**
\brief  OSensitiveWidgetStack - 


\return term -

\param  pQWidget -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSensitiveWidgetStack"

                        OSensitiveWidgetStack :: OSensitiveWidgetStack (QWidget *pQWidget )
                     : QWidgetStack ( pQWidget ),
  routers()
{

  routers.setAutoDelete(YES);

}

/******************************************************************************/
/**
\brief  RegisterWidget - 


\return term -

\param  iID -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterWidget"

OSlotRouter *OSensitiveWidgetStack :: RegisterWidget (int iID )
{

class OSWS_SlotRouter : public OSlotRouter
{
public:
  int id;
  OSensitiveWidgetStack* sws; 
  virtual void Fire() { sws->Select( id ); }
};
OSWS_SlotRouter* sr= (OSWS_SlotRouter*) routers.find( iID );
if( !sr )
{
  sr= new OSWS_SlotRouter();
  sr->id= iID;
  sr->sws= this;
  routers.insert( iID, sr );
}
return sr;


}

/******************************************************************************/
/**
\brief  Select - 



\param  iID -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Select"

void OSensitiveWidgetStack :: Select (int iID )
{

if( !widget( iID ) )
{
  //TODO: code for calling signals which will build widget
}
raiseWidget( iID );


}


