/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DKey

\brief    


\date     $Date: 2006/03/13 21:33:36,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DKey_HPP
#define   DKey_HPP

class     DKey;

class  DKey
{
public     :         int32                                        key;                                                       //
public     :         int32                                        state;                                                     //
public     :         logical                                      released;                                                  

public     :
public     :         OGUI7ImpExp                                         DKey (int keycode, int keystate, logical keyreleased );
public     :         OGUI7ImpExp                 logical operator== (DKey &dkey );
public     :         OGUI7ImpExp                                         ~DKey ( );
};

#endif
