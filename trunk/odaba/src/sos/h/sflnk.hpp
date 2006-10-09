/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    flnk

\brief    Function link
          The  class defines dynamic function links to any class that is derived
          from  the virtual base class vcls.  This allows calling functions from
          classes that are known at run-time, only. 
          "

\date     $Date: 2006/05/31 22:50:06,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   flnk_HPP
#define   flnk_HPP

class     flnk;
#include "csosdll.h"

class     UCA_Action;
class     vcls;
#include  <iThreadCall.h>
#include  <sflnk.hpp>
#pragma pack(8)

class  flnk
{
protected  :         vcls                                        *flnkinst;                                                  
protected  :         FCTP                                         flnkfct;                                                   

public     :
                     vcls                                        *get_flnkinst() { return(flnkinst); }
                     FCTP                                        &get_flnkfct() { return(flnkfct); }
public     :                  SOSImpExp             logical ActionCall ( );
public     :                  SOSImpExp             logical ActionCall (void *objptr );
public     :                  SOSImpExp             int32 Call (void *parm );
public     :                  SOSImpExp             int32 Call (void *objptr, void *parm );
public     :                  SOSImpExp             logical IsSet ( ) const;
public     :                  SOSImpExp             void SetInstance (vcls *vclsptr );
public     :                  SOSImpExp             thread_t ThreadCall ( );
public     :                  SOSImpExp             thread_t ThreadCallS ( );
public     :                  SOSImpExp             int32 VoidCall (void *parm );
public     :                  SOSImpExp                  flnk (vcls *vclsptr, FCTP funcptr );
public     :                  SOSImpExp                  flnk (vcls *vclsptr, ACTP actptri );
public     :                  SOSImpExp                  flnk (const flnk &flnk_ref );
public     :                  SOSImpExp                  flnk ( );
public     :                  SOSImpExp             logical operator! ( ) const;
public     :                  SOSImpExp             logical operator!= (const flnk &flnk_ref ) const;
public     :                  SOSImpExp             flnk &operator= (const flnk &flnk_ref );
public     :                  SOSImpExp             logical operator== (const flnk &flnk_ref ) const;
};

#pragma pack()
#endif
