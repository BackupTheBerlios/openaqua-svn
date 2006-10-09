/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OCAU_Action



\date     $Date: 2006/04/28 19:16:28,56 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OCAU_Action_HPP
#define   OCAU_Action_HPP

class     OCAU_Action;

class     PropertyHandle;
#include  <sOCAU_Action.hpp>
#include  <sOCAU_SimpleAction.hpp>
#pragma pack(4)

class  OCAU_Action :public OCAU_SimpleAction
{
protected  :         OCAU_SimpleAction                           *pre_handler;                                               
protected  :         OCAU_SimpleAction                           *post_handler;                                              

public     :
                     OCAU_SimpleAction                           *get_pre_handler() { return(pre_handler); }
                     OCAU_SimpleAction                           *get_post_handler() { return(post_handler); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OCAU_Action ( );
public     :                                             OCAU_Action (OCAU_SimpleAction bcOCAU_SimpleAction, OCAU_SimpleAction *pre_handler, OCAU_SimpleAction *post_handler );
public     :                                        logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        bool operator== (OCAU_Action &rOCAU_Action );
public     : virtual                                     ~OCAU_Action ( );
};

#pragma pack()
#endif
