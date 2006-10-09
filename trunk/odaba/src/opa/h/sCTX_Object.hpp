/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CTX_Object

\brief    Database Object Context
          The  Database  Object  context  allows  defining functionality that is
          executed  when  opening  or  closing  a  Database  Object.  The parent
          context  for an object context is  an object con-text (if the Database
          Object  is not the root Database  Object) or the database context (for
          the root Database Object).
          The   default   database   object   context   can   be overloaded by a
          application specific database context class.

\date     $Date: 2006/03/12 19:12:42,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Object_HPP
#define   CTX_Object_HPP

class     CTX_Object;

class     ACObject;
class     CTX_Base;
#include  <sCTX_DBBase.hpp>
#pragma pack(8)

class  CTX_Object :public CTX_DBBase
{
protected  :         ACObject                                    *object_handle ATTR_ALIGN(4);                               //

public     :
                     ACObject                                    *get_object_handle() { return(object_handle); }
public     :         opa7ImpExp                                          CTX_Object ( );
public     :         opa7ImpExp                  ODABAClient GetConnectionClient ( );
public     : virtual opa7ImpExp                  CTX_Types GetContextType ( );
public     :                                     void Initialize (ACObject *obhandle, CTX_Base *highctx );
public     : virtual opa7ImpExp                                          ~CTX_Object ( );
};

#pragma pack()
#endif
