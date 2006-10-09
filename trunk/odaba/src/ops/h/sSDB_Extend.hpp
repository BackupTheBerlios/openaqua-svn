/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_Extend

\brief    ODABA Extent
          Odaba  extents are specific collections, which allow storing instances
          on  a  database  object  level  in  an  ODABA  database.  Extents  are
          properties  of  database  objects  and  exist outside of any structure
          definition.  Extents are associated with a structure type, which might
          refer  to  VOID  type  for  untypical extends or to the base structure
          type  for  weak-typed  extents.  An  extent  may  define  one  or more
          indexes, but must have an identifying key index. 
          Typically,  there is  one extent  defined, which  does not have a base
          extents.  This is  called the  root extent,  which contains all global
          instances of the given type. 
          on on the instance is considered as event. 
          Special  events are  system events  that are  signaled by the database
          system  and usually indicate a change in  the process or life state of
          the  instance,  which  cannot  be  expressed  in  terms  of  pre-  and
          post-conditions. 
          Event  definitions  are  stored  globally  with  a unique name that is
          constructed  from the structure name, the  extent or property name and
          the  event name. This  allows referring to  an event from a far linked
          instance or registering instances for event observation. 
          When  an event is fired it can  be handled by an event handler defined
          in  the  causality  rule,  which  is  a  function, expression or other
          action again.

\date     $Date: 2006/03/13 21:30:08,37 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Extend_HPP
#define   SDB_Extend_HPP

class     SDB_Extend;

#ifndef   P_SDB_CodeSet_HPP
#define   P_SDB_CodeSet_HPP
#include  <sPI.hpp>
class       SDB_CodeSet;
PI_dcl     (SDB_CodeSet)
#endif
#ifndef   P_SDB_Extend_HPP
#define   P_SDB_Extend_HPP
#include  <sPI.hpp>
class       SDB_Extend;
PI_dcl     (SDB_Extend)
#endif
#ifndef   P_SDB_ODABA_Str_HPP
#define   P_SDB_ODABA_Str_HPP
#include  <sPI.hpp>
class       SDB_ODABA_Str;
PI_dcl     (SDB_ODABA_Str)
#endif
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Reference.hpp>
#pragma pack(8)

class  SDB_Extend :public SDB_Reference
{
protected  :         logical                                      controlled ATTR_ALIGN(4);                                  // Controlled extent
protected  :         logical                                      intersect;                                                 // Intersect relation
protected  :         logical                                      union_set;                                                 // Union relation
protected  :         logical                                      disjunct;                                                  // Distinct relation
protected  :         PI(SDB_Extend)                               sexbase;                                                   // Super sets for extent
protected  :         PI(SDB_Extend)                               sexderi;                                                   // Subset for extent
protected  :         PI(SDB_ODABA_Str)                            pstructure;                                                //

public     :
                     logical                                      get_controlled() { return(controlled); }
                     logical                                      get_intersect() { return(intersect); }
                     logical                                      get_union_set() { return(union_set); }
                     logical                                      get_disjunct() { return(disjunct); }
                     PI(SDB_Extend)                              &get_sexbase() { return(sexbase); }
                     PI(SDB_Extend)                              &get_sexderi() { return(sexderi); }
                     PI(SDB_ODABA_Str)                           &get_pstructure() { return(pstructure); }
public     :         OPS7ImpExp                  logical AddToODABAStr (PI(SDB_ODABA_Str) *pers_pi );
public     :         OPS7ImpExp                  logical Initialize (DatabaseHandle &dbhandle, char *strname );
public     :         OPS7ImpExp                  logical InitializeCSRoot ( );
public     : static  OPS7ImpExp                  logical __cdecl ProvideExtendDef (DatabaseHandle &dbhandle, char *extname, char *strname );
public     : static  OPS7ImpExp                  logical __cdecl ProvideStrRoot (DatabaseHandle &dbhandle, char *strname );
};

#pragma pack()
#endif
