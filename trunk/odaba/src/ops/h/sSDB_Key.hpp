/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Key

\brief    Key definition
          A  key consists of a number  of structure attribute or key references.
          Keys  may also  refer to  transient attributes.  Keys may not refer to
          references or relationships. 
          When  referring to attribute arrays  or generic attributes, a multiple
          key  is  created,  which  creates  as  many key instances as there are
          array elements or generic attribute instances for each instance. 
          Specific  keys are  identity and  auto-ident keys. __IDENTITY keys are
          keys  that refer  to the  identity as  key attribute. Identity keys do
          not  have  components.  Auto-ident  keys  are keys, which have as only
          attribute  component  the  __AUTOIDENT  attribute.  Auto-ident  keys 
          provide automatic numbers for instances created in the collection.
          Key  components  may  define  ascending (default) or descending order.
          Since  this can be defined  on the level of  key components, it is not
          the  key  itself,  which  is  ascending or descending. Those modes can
          also  be mixed, which creates ascending/descending keys. Since this is
          not  an index feature,  several keys with  the same attributes must be
          defined  for  supporting  ascending  and descending orders at the same
          time.

\date     $Date: 2006/05/11 13:18:57,84 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Key_HPP
#define   SDB_Key_HPP

class     SDB_Key;

#ifndef   P_SDB_KeyComponent_HPP
#define   P_SDB_KeyComponent_HPP
#include  <sPI.hpp>
class       SDB_KeyComponent;
PI_dcl     (SDB_KeyComponent)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#include  <sSDB_Resource.hpp>
#pragma pack(8)

class  SDB_Key :public SDB_Resource
{
protected  :         int32                                        __AUTOIDENT;                                               // Internal key number
protected  :         PI(SDB_KeyComponent)                         components;                                                // Key components
protected  :         PI(SDB_Structure)                            structure;                                                 // Structure the key belongs to

public     :
                     int32                                        get___AUTOIDENT() { return(__AUTOIDENT); }
                     PI(SDB_KeyComponent)                        &get_components() { return(components); }
                     PI(SDB_Structure)                           &get_structure() { return(structure); }
public     :                  OPSImpExp                  SDB_Key (char *keynams, char **keyfieldlist, int16 key_number=0 );
public     :                  OPSImpExp                  ~SDB_Key ( );
};

#pragma pack()
#endif
