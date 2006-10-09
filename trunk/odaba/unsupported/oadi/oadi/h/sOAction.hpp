/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OAction



\date     $Date: 2006/04/30 16:05:39,10 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OAction_HPP
#define   OAction_HPP

class     OAction;

class     CTX_GUIBase;
class     OCAU_SimpleAction;
class     PropertyHandle;
class     TComponent;
#include  <sODataSourceHaving.hpp>
#include  <sOResource.hpp>
#pragma pack(4)

class  OAction :public OResource,
public ODataSourceHaving
{
protected  :         char                                         _class[41];                                                
protected  :         OCAU_SimpleAction                           *preHandler;                                                
protected  :         OCAU_SimpleAction                           *postHandler;                                               
protected  :         TComponent                                  *owner;                                                     

public     :
                     char                                        *get__class() { return(_class); }
                     TComponent                                  *get_owner() { return(owner); }
public     : virtual                                void *CastPointer (char *typenames );
public     : virtual                                char Execute (CTX_GUIBase *ctxptr );
public     :                                        logical ExecuteAction (CTX_GUIBase *ctxptr );
public     :                                             OAction ( );
public     :                                             OAction (OResource bcOResource, ODataSourceHaving bcODataSourceHaving, char *s_class, OCAU_SimpleAction *pOCAU_SimpleAction_preHandler, OCAU_SimpleAction *pOCAU_SimpleAction_postHandler, CTX_GUIBase *pCTX_GUIBase, logical brunning, logical bresult );
public     :                                        TComponent *Owner ( );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        logical SetProperties (char *class_names, logical as_collection, PropertyHandle *prophdl );
public     :                                        void xSetOwner (TComponent *pTComponent );
public     : virtual                                     ~OAction ( );
};

#pragma pack()
#endif
