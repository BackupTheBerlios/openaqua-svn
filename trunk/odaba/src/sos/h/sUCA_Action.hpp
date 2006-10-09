/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UCA_Action

\brief    


\date     $Date: 2006/03/12 19:20:20,81 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   UCA_Action_HPP
#define   UCA_Action_HPP

class     UCA_Action;

class     SimpleAction;
class     UCA_Action;
class     UCA_CAction;
#include  <cActionType.h>
#include  <sCTX_Base.hpp>
#pragma pack(8)

class  UCA_Action
{
protected  :         char                                         name[40];                                                  //
protected  :         CTX_Base                                    *context;                                                   //

public     :
                     char                                        *get_name() { return(name); }
                     CTX_Base                                    *get_context() { return(context); }
public     :         SOS7ImpExp                  logical CheckPermission ( );
public     : static  SOS7ImpExp                  UCA_Action *__cdecl Create (ActionType actype, char *acname, CTX_Base *ctxptr );
public     : virtual SOS7ImpExp                  logical Execute ( );
public     : virtual SOS7ImpExp                  logical Execute (CTX_Base *ctxptr );
public     :         SOS7ImpExp                                          UCA_Action (char *acname, CTX_Base *ctxptr );
public     :         SOS7ImpExp                  void set_context (CTX_Base *ctxptr );
public     : virtual SOS7ImpExp                                          ~UCA_Action ( );
};

#pragma pack()
#endif
