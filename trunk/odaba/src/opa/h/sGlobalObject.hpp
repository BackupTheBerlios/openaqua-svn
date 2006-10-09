/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    GlobalObject

\brief    


\date     $Date: 2006/03/12 19:13:23,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   GlobalObject_HPP
#define   GlobalObject_HPP

class     GlobalObject;

class     LACObject;
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  GlobalObject
{
protected  :         RessourceLock                                object_lock;                                               
protected  :         LACObject                                   *object_ref;                                                

public     :
                     RessourceLock                               &get_object_lock() { return(object_lock); }
                     LACObject                                   *get_object_ref() { return(object_ref); }
public     :                                     LACObject *GetACObject ( );
public     :                                                             GlobalObject (LACObject *lobhandle );
public     :                                     logical Lock (logical wait );
public     :                                     void SetupContext (CTX_Base *highctx );
public     :                                     logical Unlock ( );
public     :                                                             ~GlobalObject ( );
};

#pragma pack()
#endif
