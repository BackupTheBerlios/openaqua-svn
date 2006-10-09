/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    NBase

\brief    Base class for text and text array buffer
          The  buffer  is  allocating  dynamical  space for the text. It expands
          whenever  necessary.  The  buffer  guarantees  that  there is always a
          terminating 0 at the end of the buffer.

\date     $Date: 2006/07/28 11:53:15,46 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   NBase_HPP
#define   NBase_HPP

class     NBase;
#include "csosdll.h"

#pragma pack(8)

class  NBase
{
protected  :         int32                                        size;                                                      // 
protected  :         char                                        *area;                                                      // 

public     :
public     :                  SOSImpExp             char *GetArea ( );
public     :                  SOSImpExp             size_t GetSize ( );
public     :                                        void Initialize ( );
public     :                  SOSImpExp             logical IsEmpty ( );
public     :                  SOSImpExp                  NBase ( );
public     :                  SOSImpExp             logical Resize (size_t len, int32 res_val=0 );
public     :                  SOSImpExp             logical operator ! ( );
public     :                  SOSImpExp             NOTYPE operator char* ( );
public     :                  SOSImpExp                  ~NBase ( );
};

#pragma pack()
#endif
