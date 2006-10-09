/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OFunctAction



\date     $Date: 2006/04/30 16:05:55,34 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OFunctAction_HPP
#define   OFunctAction_HPP

class     OFunctAction;

class     CTX_GUIBase;
#include  <sOAction.hpp>
#pragma pack(4)

class  OFunctAction :public OAction
{
protected  :         char                                         function[41];                                              

public     :
                     char                                        *get_function() { return(function); }
public     : virtual                                void *CastPointer (char *typenames );
public     : virtual                                char Execute (CTX_GUIBase *ctxptr );
public     :                                             OFunctAction ( );
public     :                                        void SetFunction (char *fnames );
public     :                                        logical SetProperties (char *fname );
public     : virtual                                     ~OFunctAction ( );
};

#pragma pack()
#endif
