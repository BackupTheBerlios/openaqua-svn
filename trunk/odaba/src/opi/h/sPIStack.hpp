/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|17:41:08,71}|(REF)
\class    PIStack

\brief    Property handle stack
          A  property handle stack allows defining  a series of related property
          handles.  A Property handle stack can be defined for a property handle
          and  allows activating a  new and saving  the current handle using the
          Push()  function and re-activating the previous handle using the Pop()
          function.  Thus,  it  becomes  possible,  e.g.  defining a sequence of
          subsequent  selections  with  the  possibility  of  going  back to the
          prevoius level.

\date     $Date: 2006/04/20 19:16:04,65 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PIStack_HPP
#define   PIStack_HPP

#include "copadll.h"
class     PIStack;

class     NodeStack;
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  PIStack :public PropertyHandle
{
protected  :         NodeStack                                   *stack ATTR_ALIGN(4);                                       // 

public     :
                     NodeStack                                   *get_stack() { return(stack); }
public     :         OPIImpExp                   int32 Count ( );
public     :         OPIImpExp                                           PIStack (PropertyHandle *property_handle );
public     :         OPIImpExp                   logical Pop ( );
public     :         OPIImpExp                   void Push ( );
public     :         OPIImpExp                   void Push (PropertyHandle *property_handle );
public     :         OPIImpExp                                           ~PIStack ( );
};

#pragma pack()
#endif
