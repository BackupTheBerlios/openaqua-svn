/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    vcls

\brief    Virtual class
          This  is an empty class that acts as base class for objects supporting
          dynamical  function  calls.  Depending  on  the  compiler  the  class 
          occupies no or one byte memory. 
          A  global count field (vcls_count) allows checking whether all objects
          have been desctructed at the end of a program.

\date     $Date: 2006/05/01 14:16:33,09 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   vcls_HPP
#define   vcls_HPP

#include "csosdll.h"
class     vcls;

#pragma pack(4)

class  vcls
{

public     :
public     :                  SOSImpExp             logical Wait ( );
public     :                  SOSImpExp                  vcls ( );
public     :                  SOSImpExp                  ~vcls ( );
};

#pragma pack()
#endif
