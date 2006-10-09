/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OActionControl



\date     $Date: 2006/04/27 15:04:17,64 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OActionControl_HPP
#define   OActionControl_HPP

class     OActionControl;

class     OCAU_Action;
class     PropertyHandle;
#include  <sOElementStyle.hpp>
#pragma pack(4)

class  OActionControl :public OElementStyle
{
protected  :         OCAU_Action                                 *action;                                                    

public     :
                     OCAU_Action                                 *get_action() { return(action); }
public     :                                        OCAU_Action *Action ( ) const;
public     : virtual                                void *CastPointer (char *typenames );
public     :                                             OActionControl ( );
public     :                                             OActionControl (OElementStyle bcOElementStyle, OCAU_Action *pOCAU_Action );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OActionControl ( );
};

#pragma pack()
#endif
