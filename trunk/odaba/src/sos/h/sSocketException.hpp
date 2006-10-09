/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    SocketException



\date     $Date: 2006/05/15 20:47:44,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SocketException_HPP
#define   SocketException_HPP

class     SocketException;

#include  <standard.hpp>
class  SocketException
{
protected  :         std_string                                   exception_text;                                            

public     :
                     std_string                                  &get_exception_text() { return(exception_text); }
public     :                                             SocketException (std_string SException )                     : exception_text(SException)
{
}

public     :                                        std_string description ( ){

  return exception_text;

}

public     :                                             ~SocketException ( ){


}

};

#endif
