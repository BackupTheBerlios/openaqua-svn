/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    SystemIO

\brief    


\date     $Date: 2006/08/27 20:29:02,15 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SystemIO_HPP
#define   SystemIO_HPP

class     SystemIO;

class     CTX_Base;
#include  <sNString.hpp>
class  SystemIO
{
protected  :         CTX_Base                                    *context;                                                   // 
protected  :         NString                                      nstring;                                                   // 

public     :
                     CTX_Base                                    *get_context() { return(context); }
                     NString                                     &get_nstring() { return(nstring); }
public     :                                        CTX_Base *GetContext ( );
public     :                                        char *Read (char *string );
public     : static                                 char *__cdecl ReadConsole (char *string );
public     :                                        void SetContext (CTX_Base *ctxptr );
public     :                                             SystemIO ( );
public     :                                        logical Write (char *string, logical clear_opt, logical flush_opt );
public     : static                                 logical __cdecl WriteConsole (char *string, logical clear_opt, logical flush_opt );
public     :                                             ~SystemIO ( );
};

#endif
