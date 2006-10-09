/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/05/11 13:18:59,57 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Key"

#include  <pops7.h>
#include  <sSDB_KeyComponent.hpp>
#include  <sSDB_Key.hpp>


/******************************************************************************/
/**
\brief  SDB_Key


\param  keynams
\param  keyfieldlist
\param  key_number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Key"

     SDB_Key :: SDB_Key (char *keynams, char **keyfieldlist, int16 key_number )
                     : SDB_Resource (),
  __AUTOIDENT(key_number),
  components(),
  structure()
{
  gvtxstb(sys_ident,keynams,ID_SIZE);

  components.set_nodeptr((node *)keyfieldlist);
}

/******************************************************************************/
/**
\brief  ~SDB_Key


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SDB_Key"

     SDB_Key :: ~SDB_Key ( )
{
  components.set_nodeptr(NULL);
}


