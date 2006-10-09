/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OLabelDefinition



\date     $Date: 2006/04/28 14:05:18,46 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OLabelDefinition_HPP
#define   OLabelDefinition_HPP

class     OLabelDefinition;

class     PropertyHandle;
#include  <cADK_HoriPos.h>
#include  <cADK_VertPos.h>
#include  <sDSize.hpp>
#include  <sOPersistent.hpp>
#pragma pack(4)

class  OLabelDefinition :public OPersistent
{
protected  :         logical                                      showLabel;                                                 
protected  :         ADK_HoriPos                                  horiPos;                                                   
protected  :         ADK_VertPos                                  vertPos;                                                   
protected  :         ADK_HoriPos                                  textPosition;                                              
protected  :         DSize                                        size;                                                      

public     :
public     :                                        logical HasShowLabel ( ) const;
public     :                                        ADK_HoriPos HoriPos (ADK_HoriPos vADK_HoriPos ) const;
public     :                                             OLabelDefinition ( );
public     :                                             OLabelDefinition (OPersistent bcOPersistent, logical showLabel, int16 horiPos, int16 vertPos, int16 textPosition, DSize dsize );
public     : virtual                                logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     :                                        const DSize &Size ( ) const;
public     :                                        ADK_HoriPos TextPosition (ADK_HoriPos vADK_HoriPos ) const;
public     :                                        ADK_VertPos VertPos (ADK_VertPos vADK_VertPos ) const;
};

#pragma pack()
#endif
